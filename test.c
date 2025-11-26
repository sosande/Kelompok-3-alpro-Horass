/*
  kost_master.c
  SISTEM MANAJEMEN KOST (CLI) - Semua fitur digabung:
  - Manajemen penyewa (CRUD)
  - Transaksi (sewa/pendapatan/pengeluaran)
  - Laporan bulanan & visualisasi ASCII
  - Ringkasan cepat
  - Manajemen aset (CRUD) + depresiasi sederhana
  - Ringkasan sistem (menggabungkan laporan keuangan, aset, penghuni)
  Compile: gcc -o kost_master kost_master.c
  Run: ./kost_master
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STR 256
#define TENANT_FILE "tenants.csv"
#define TX_FILE "transactions.csv"
#define ASSET_FILE "assets.csv"
#define DATE_STR_LEN 20

/* ------------------------
   Tipe data & enum
   ------------------------ */
typedef enum {TX_RENT = 0, TX_INCOME = 1, TX_EXPENSE = 2} TxType;

typedef struct {
    int id;
    char name[MAX_STR];
    char room[MAX_STR];
    double monthly_rent;
    double deposit;
    int active; // 1 active, 0 inactive
} Tenant;

typedef struct {
    int id;
    int tenant_id; // 0 if not tied to a tenant
    char date[DATE_STR_LEN]; // YYYY-MM-DD
    TxType type;
    double amount;
    char note[MAX_STR];
} Transaction;

typedef struct {
    int id;
    char name[MAX_STR];
    char location[MAX_STR]; // kamar / fasilitas umum
    double value;           // harga beli
    char purchase_date[DATE_STR_LEN];
    double depreciation_rate; // %/year
    int active;
} Asset;

/* ------------------------
   Dynamic arrays global
   ------------------------ */
Tenant *tenants = NULL;
int tenants_count = 0, tenants_cap = 0;

Transaction *txs = NULL;
int tx_count = 0, tx_cap = 0;

Asset *assets = NULL;
int asset_count = 0, asset_cap = 0;

/* ------------------------
   Utilitas input / date
   ------------------------ */
void read_line(char *buf, int size) {
    if (fgets(buf, size, stdin)) {
        size_t len = strlen(buf);
        if (len && buf[len-1] == '\n') buf[len-1] = '\0';
    } else {
        buf[0] = '\0';
    }
}

void trim(char *s) {
    char *start = s;
    while (*start == ' ' || *start == '\t') start++;
    if (start != s) memmove(s, start, strlen(start)+1);
    int len = strlen(s);
    while (len > 0 && (s[len-1] == ' ' || s[len-1] == '\t')) s[--len] = '\0';
}

void today_str(char *buf, int size) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buf, size, "%04d-%02d-%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
}

/* ------------------------
   Dynamic ensure functions
   ------------------------ */
void ensure_tenants_capacity() {
    if (tenants_count >= tenants_cap) {
        tenants_cap = tenants_cap ? tenants_cap * 2 : 8;
        tenants = realloc(tenants, tenants_cap * sizeof(Tenant));
        if (!tenants) { perror("realloc tenants"); exit(1); }
    }
}

void ensure_tx_capacity() {
    if (tx_count >= tx_cap) {
        tx_cap = tx_cap ? tx_cap * 2 : 16;
        txs = realloc(txs, tx_cap * sizeof(Transaction));
        if (!txs) { perror("realloc txs"); exit(1); }
    }
}

void ensure_assets_capacity() {
    if (asset_count >= asset_cap) {
        asset_cap = asset_cap ? asset_cap * 2 : 8;
        assets = realloc(assets, asset_cap * sizeof(Asset));
        if (!assets) { perror("realloc assets"); exit(1); }
    }
}

/* ------------------------
   Next IDs
   ------------------------ */
int next_tenant_id() {
    int max = 0;
    for (int i=0;i<tenants_count;i++) if (tenants[i].id > max) max = tenants[i].id;
    return max + 1;
}
int next_tx_id() {
    int max = 0;
    for (int i=0;i<tx_count;i++) if (txs[i].id > max) max = txs[i].id;
    return max + 1;
}
int next_asset_id() {
    int max = 0;
    for (int i=0;i<asset_count;i++) if (assets[i].id > max) max = assets[i].id;
    return max + 1;
}

/* ------------------------
   CSV helpers: strip quotes
   ------------------------ */
char *stripquotes(char *s) {
    if (!s) return s;
    int len = strlen(s);
    // trim newline at end
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) { s[len-1] = '\0'; len--; }
    if (len >= 2 && s[0] == '"' && s[len-1] == '"') {
        s[len-1] = '\0';
        memmove(s, s+1, len-1);
    }
    return s;
}

/* ------------------------
   Persistence: tenants
   ------------------------ */
void save_tenants() {
    FILE *f = fopen(TENANT_FILE, "w");
    if (!f) { perror("save_tenants fopen"); return; }
    fprintf(f, "id,name,room,monthly_rent,deposit,active\n");
    for (int i=0;i<tenants_count;i++) {
        Tenant *t = &tenants[i];
        fprintf(f, "%d,\"%s\",\"%s\",%.2f,%.2f,%d\n",
                t->id, t->name, t->room, t->monthly_rent, t->deposit, t->active);
    }
    fclose(f);
}

void load_tenants() {
    FILE *f = fopen(TENANT_FILE, "r");
    if (!f) return;
    char line[1024];
    if (!fgets(line, sizeof(line), f)) { fclose(f); return; } // skip header
    while (fgets(line, sizeof(line), f)) {
        Tenant t; memset(&t,0,sizeof(Tenant));
        // naive CSV parse (expects known format)
        char *p = line;
        char *id_s = strtok(p, ",");
        char *name = strtok(NULL, ",");
        char *room = strtok(NULL, ",");
        char *rent = strtok(NULL, ",");
        char *deposit = strtok(NULL, ",");
        char *active = strtok(NULL, ",");
        if (!id_s || !name || !room || !rent || !deposit || !active) continue;
        t.id = atoi(id_s);
        stripquotes(name); stripquotes(room);
        strncpy(t.name, name, MAX_STR-1);
        strncpy(t.room, room, MAX_STR-1);
        t.monthly_rent = atof(rent);
        t.deposit = atof(deposit);
        t.active = atoi(active);
        ensure_tenants_capacity();
        tenants[tenants_count++] = t;
    }
    fclose(f);
}

/* ------------------------
   Persistence: transactions
   ------------------------ */
void save_txs() {
    FILE *f = fopen(TX_FILE, "w");
    if (!f) { perror("save_txs fopen"); return; }
    fprintf(f, "id,tenant_id,date,type,amount,note\n");
    for (int i=0;i<tx_count;i++) {
        Transaction *tr = &txs[i];
        fprintf(f, "%d,%d,%s,%d,%.2f,\"%s\"\n",
                tr->id, tr->tenant_id, tr->date, (int)tr->type, tr->amount, tr->note);
    }
    fclose(f);
}

void load_txs() {
    FILE *f = fopen(TX_FILE, "r");
    if (!f) return;
    char line[1024];
    if (!fgets(line, sizeof(line), f)) { fclose(f); return; } // header
    while (fgets(line, sizeof(line), f)) {
        Transaction tr; memset(&tr,0,sizeof(Transaction));
        char *p = line;
        char *id_s = strtok(p, ",");
        char *tid_s = strtok(NULL, ",");
        char *date = strtok(NULL, ",");
        char *type_s = strtok(NULL, ",");
        char *amount_s = strtok(NULL, ",");
        char *note = strtok(NULL, "\n");
        if (!id_s || !tid_s || !date || !type_s || !amount_s || !note) continue;
        tr.id = atoi(id_s);
        tr.tenant_id = atoi(tid_s);
        strncpy(tr.date, date, DATE_STR_LEN-1);
        tr.type = (TxType)atoi(type_s);
        tr.amount = atof(amount_s);
        stripquotes(note);
        strncpy(tr.note, note, MAX_STR-1);
        ensure_tx_capacity();
        txs[tx_count++] = tr;
    }
    fclose(f);
}

/* ------------------------
   Persistence: assets
   ------------------------ */
void save_assets() {
    FILE *f = fopen(ASSET_FILE, "w");
    if (!f) { perror("save_assets fopen"); return; }
    fprintf(f, "id,name,location,value,purchase_date,depreciation_rate,active\n");
    for (int i=0;i<asset_count;i++) {
        Asset *a = &assets[i];
        fprintf(f, "%d,\"%s\",\"%s\",%.2f,%s,%.2f,%d\n",
                a->id, a->name, a->location, a->value, a->purchase_date, a->depreciation_rate, a->active);
    }
    fclose(f);
}

void load_assets() {
    FILE *f = fopen(ASSET_FILE, "r");
    if (!f) return;
    char line[1024];
    if (!fgets(line, sizeof(line), f)) { fclose(f); return; } // header
    while (fgets(line, sizeof(line), f)) {
        Asset a; memset(&a,0,sizeof(Asset));
        char *p = line;
        char *id_s = strtok(p, ",");
        char *name = strtok(NULL, ",");
        char *loc = strtok(NULL, ",");
        char *value_s = strtok(NULL, ",");
        char *pdate = strtok(NULL, ",");
        char *dep_s = strtok(NULL, ",");
        char *active_s = strtok(NULL, ",");
        if (!id_s || !name || !loc || !value_s || !pdate || !dep_s || !active_s) continue;
        a.id = atoi(id_s);
        stripquotes(name); stripquotes(loc);
        strncpy(a.name, name, MAX_STR-1);
        strncpy(a.location, loc, MAX_STR-1);
        a.value = atof(value_s);
        strncpy(a.purchase_date, pdate, DATE_STR_LEN-1);
        a.depreciation_rate = atof(dep_s);
        a.active = atoi(active_s);
        ensure_assets_capacity();
        assets[asset_count++] = a;
    }
    fclose(f);
}

/* ------------------------
   Tenant operations
   ------------------------ */
Tenant *find_tenant_by_id(int id) {
    for (int i=0;i<tenants_count;i++) if (tenants[i].id == id) return &tenants[i];
    return NULL;
}

void add_tenant() {
    Tenant t; memset(&t,0,sizeof(Tenant));
    t.id = next_tenant_id();
    char buf[MAX_STR];
    printf("Nama penyewa: ");
    read_line(buf, MAX_STR); trim(buf); strncpy(t.name, buf, MAX_STR-1);
    printf("Nomor/kode kamar: ");
    read_line(buf, MAX_STR); trim(buf); strncpy(t.room, buf, MAX_STR-1);
    printf("Sewa bulanan (angka): ");
    read_line(buf, MAX_STR); t.monthly_rent = atof(buf);
    printf("Deposit (jika ada, 0 jika tidak): ");
    read_line(buf, MAX_STR); t.deposit = atof(buf);
    t.active = 1;
    ensure_tenants_capacity();
    tenants[tenants_count++] = t;
    printf("Penyewa ditambahkan dengan ID %d\n", t.id);
}

void list_tenants() {
    printf("Daftar penyewa:\n");
    printf("ID | Nama | Kamar | Sewa/bln | Deposit | Status\n");
    printf("-------------------------------------------------------------\n");
    for (int i=0;i<tenants_count;i++) {
        Tenant *t = &tenants[i];
        printf("%2d | %s | %s | %.2f | %.2f | %s\n",
               t->id, t->name, t->room, t->monthly_rent, t->deposit, t->active ? "Aktif" : "Non-aktif");
    }
}

void edit_tenant() {
    char buf[MAX_STR];
    printf("Masukkan ID penyewa yang ingin diedit: ");
    read_line(buf, MAX_STR);
    int id = atoi(buf);
    Tenant *t = find_tenant_by_id(id);
    if (!t) { printf("Penyewa ID %d tidak ditemukan.\n", id); return; }
    printf("Edit penyewa (kosong = tidak diubah)\n");
    printf("Nama saat ini: %s\nNama baru: ", t->name); read_line(buf, MAX_STR); trim(buf);
    if (strlen(buf)) strncpy(t->name, buf, MAX_STR-1);
    printf("Kamar saat ini: %s\nKamar baru: ", t->room); read_line(buf, MAX_STR); trim(buf);
    if (strlen(buf)) strncpy(t->room, buf, MAX_STR-1);
    printf("Sewa saat ini: %.2f\nSewa baru: ", t->monthly_rent); read_line(buf, MAX_STR); trim(buf);
    if (strlen(buf)) t->monthly_rent = atof(buf);
    printf("Deposit saat ini: %.2f\nDeposit baru: ", t->deposit); read_line(buf, MAX_STR); trim(buf);
    if (strlen(buf)) t->deposit = atof(buf);
    printf("Status saat ini: %s (1=aktif,0=non)\nStatus baru: ", t->active ? "Aktif":"Non-aktif"); read_line(buf, MAX_STR); trim(buf);
    if (strlen(buf)) t->active = atoi(buf);
    printf("Data penyewa ID %d diperbarui.\n", id);
}

void delete_tenant() {
    char buf[MAX_STR];
    printf("Masukkan ID penyewa yang ingin dihapus: ");
    read_line(buf, MAX_STR);
    int id = atoi(buf);
    int idx = -1;
    for (int i=0;i<tenants_count;i++) if (tenants[i].id == id) { idx = i; break; }
    if (idx == -1) { printf("Tidak ditemukan.\n"); return; }
    for (int i=idx;i<tenants_count-1;i++) tenants[i] = tenants[i+1];
    tenants_count--;
    printf("Penyewa ID %d dihapus.\n", id);
}

/* ------------------------
   Transaction operations
   ------------------------ */
void add_transaction() {
    char buf[MAX_STR];
    Transaction tr; memset(&tr,0,sizeof(Transaction));
    tr.id = next_tx_id();
    printf("Jenis transaksi (0=Sewa,1=Pendapatan lain,2=Pengeluaran): ");
    read_line(buf, MAX_STR); tr.type = (TxType)atoi(buf);
    printf("Masukkan tenant ID (0 jika bukan terkait tenant): ");
    read_line(buf, MAX_STR); tr.tenant_id = atoi(buf);
    printf("Tanggal (YYYY-MM-DD, kosong = hari ini): ");
    read_line(buf, MAX_STR); trim(buf);
    if (strlen(buf)) strncpy(tr.date, buf, DATE_STR_LEN-1); else today_str(tr.date, DATE_STR_LEN);
    printf("Jumlah (angka, tanpa pemisah): ");
    read_line(buf, MAX_STR); tr.amount = atof(buf);
    printf("Catatan: ");
    read_line(buf, MAX_STR); trim(buf); strncpy(tr.note, buf, MAX_STR-1);
    ensure_tx_capacity();
    txs[tx_count++] = tr;
    printf("Transaksi ditambahkan ID %d\n", tr.id);
}

void list_transactions() {
    printf("Daftar transaksi:\n");
    printf("ID | TenantID | Tanggal | Jenis | Jumlah | Catatan\n");
    printf("---------------------------------------------------------------\n");
    for (int i=0;i<tx_count;i++) {
        Transaction *tr = &txs[i];
        const char *jn = tr->type==TX_RENT?"Sewa":(tr->type==TX_INCOME?"Pendapatan":"Pengeluaran");
        printf("%2d | %7d | %10s | %8s | %.2f | %s\n",
               tr->id, tr->tenant_id, tr->date, jn, tr->amount, tr->note);
    }
}

/* compute tenant balance from transactions */
double tenant_balance(int tenant_id) {
    double sum = 0.0;
    for (int i=0;i<tx_count;i++) {
        Transaction *tr = &txs[i];
        if (tr->tenant_id == tenant_id) {
            if (tr->type == TX_EXPENSE) sum -= tr->amount;
            else sum += tr->amount;
        }
    }
    return sum;
}

void show_tenant_detail() {
    char buf[MAX_STR];
    printf("Masukkan ID penyewa: ");
    read_line(buf, MAX_STR);
    int id = atoi(buf);
    Tenant *t = find_tenant_by_id(id);
    if (!t) { printf("Tidak ditemukan.\n"); return; }
    printf("ID: %d\nNama: %s\nKamar: %s\nSewa/bulan: %.2f\nDeposit: %.2f\nStatus: %s\n",
           t->id, t->name, t->room, t->monthly_rent, t->deposit, t->active?"Aktif":"Non-aktif");
    printf("Saldo berdasarkan transaksi terkait: %.2f\n", tenant_balance(id));
    printf("Riwayat transaksi terkait:\n");
    printf("ID | Tanggal | Jenis | Jumlah | Catatan\n");
    for (int i=0;i<tx_count;i++) {
        Transaction *tr = &txs[i];
        if (tr->tenant_id == id) {
            const char *jn = tr->type==TX_RENT?"Sewa":(tr->type==TX_INCOME?"Pendapatan":"Pengeluaran");
            printf("%2d | %10s | %8s | %.2f | %s\n", tr->id, tr->date, jn, tr->amount, tr->note);
        }
    }
}

/* ------------------------
   Reporting: monthly totals
   ------------------------ */
typedef struct {
    char ym[8+1]; // YYYY-MM
    double income;
    double expense;
} MonthSummary;

int find_month_summary(MonthSummary *arr, int n, const char *ym) {
    for (int i=0;i<n;i++) if (strcmp(arr[i].ym, ym)==0) return i;
    return -1;
}

void format_ym_from_date(const char *date, char *out) {
    if (strlen(date) >= 7) {
        strncpy(out, date, 7);
        out[7] = '\0';
    } else {
        out[0] = '\0';
    }
}

void monthly_report_print_only_summary(MonthSummary *ms, int mcount) {
    printf("Bulan | Pemasukan | Pengeluaran | Laba(Rugi)\n");
    printf("-----------------------------------------------------\n");
    for (int i=0;i<mcount;i++) {
        double profit = ms[i].income - ms[i].expense;
        printf("%s | %.2f | %.2f | %.2f\n", ms[i].ym, ms[i].income, ms[i].expense, profit);
    }
}

void monthly_report() {
    if (tx_count == 0) { printf("Belum ada transaksi.\n"); return; }
    MonthSummary *ms = NULL;
    int mcount = 0, mcap = 0;
    for (int i=0;i<tx_count;i++) {
        char ym[8+1];
        format_ym_from_date(txs[i].date, ym);
        if (strlen(ym)==0) continue;
        int idx = find_month_summary(ms, mcount, ym);
        if (idx == -1) {
            if (mcount >= mcap) {
                mcap = mcap ? mcap*2 : 8;
                ms = realloc(ms, mcap * sizeof(MonthSummary));
                if (!ms) { perror("realloc ms"); exit(1); }
            }
            idx = mcount++;
            strcpy(ms[idx].ym, ym);
            ms[idx].income = 0;
            ms[idx].expense = 0;
        }
        if (txs[i].type == TX_EXPENSE) ms[idx].expense += txs[i].amount;
        else ms[idx].income += txs[i].amount;
    }
    // sort
    for (int i=0;i<mcount-1;i++) for (int j=i+1;j<mcount;j++)
        if (strcmp(ms[i].ym, ms[j].ym) > 0) { MonthSummary tmp = ms[i]; ms[i] = ms[j]; ms[j] = tmp; }

    printf("Laporan bulanan (YYYY-MM) :\n");
    monthly_report_print_only_summary(ms, mcount);

    // ASCII bar chart
    double maxv = 0;
    for (int i=0;i<mcount;i++) {
        if (ms[i].income > maxv) maxv = ms[i].income;
        if (ms[i].expense > maxv) maxv = ms[i].expense;
    }
    if (maxv > 0) {
        printf("\nVisualisasi (setiap # = ~1/40 dari nilai maksimal)\n");
        for (int i=0;i<mcount;i++) {
            int pin = (int)((ms[i].income / maxv) * 40.0 + 0.5);
            int pex = (int)((ms[i].expense / maxv) * 40.0 + 0.5);
            printf("%s IN:", ms[i].ym);
            for (int k=0;k<pin;k++) putchar('#');
            printf(" (%.2f)\n", ms[i].income);
            printf("     EX:");
            for (int k=0;k<pex;k++) putchar('*');
            printf(" (%.2f)\n", ms[i].expense);
            printf("\n");
        }
    }
    free(ms);
}

/* Quick summary: totals */
void quick_summary() {
    double income = 0, expense = 0;
    for (int i=0;i<tx_count;i++) {
        if (txs[i].type == TX_EXPENSE) expense += txs[i].amount;
        else income += txs[i].amount;
    }
    printf("Ringkasan: Total pemasukan = %.2f | Total pengeluaran = %.2f | Laba bersih = %.2f\n",
           income, expense, income - expense);
}

/* ------------------------
   Asset operations
   ------------------------ */
void add_asset() {
    Asset a; memset(&a,0,sizeof(a));
    a.id = next_asset_id();
    char buf[MAX_STR];
    printf("Nama aset: "); read_line(buf, MAX_STR); trim(buf); strncpy(a.name, buf, MAX_STR-1);
    printf("Lokasi (misal: Kamar A1 / Umum): "); read_line(buf, MAX_STR); trim(buf); strncpy(a.location, buf, MAX_STR-1);
    printf("Harga beli: "); read_line(buf, MAX_STR); a.value = atof(buf);
    printf("Tanggal beli (YYYY-MM-DD, kosong=hari ini): "); read_line(buf, MAX_STR); trim(buf);
    if (strlen(buf)) strncpy(a.purchase_date, buf, DATE_STR_LEN-1); else today_str(a.purchase_date, DATE_STR_LEN);
    printf("Depresiasi per tahun (%%): "); read_line(buf, MAX_STR); a.depreciation_rate = atof(buf);
    a.active = 1;
    ensure_assets_capacity();
    assets[asset_count++] = a;
    printf("✔ Aset ditambahkan, ID=%d\n", a.id);
}

void list_assets() {
    printf("Daftar aset:\n");
    printf("ID | Nama | Lokasi | Nilai | Tgl Beli | Depresiasi | Status\n");
    printf("-----------------------------------------------------------------\n");
    for (int i=0;i<asset_count;i++)
        printf("%2d | %s | %s | %.2f | %s | %.2f%% | %s\n",
            assets[i].id, assets[i].name, assets[i].location,
            assets[i].value, assets[i].purchase_date,
            assets[i].depreciation_rate, assets[i].active ? "Aktif" : "Non");
}

void edit_asset() {
    char buf[MAX_STR];
    printf("ID aset yang diedit: "); read_line(buf, MAX_STR);
    int id = atoi(buf);
    for (int i=0;i<asset_count;i++) {
        if (assets[i].id == id) {
            printf("Nama baru (kosong=biarkan): "); read_line(buf, MAX_STR); trim(buf); if(strlen(buf)) strncpy(assets[i].name, buf, MAX_STR-1);
            printf("Lokasi baru: "); read_line(buf, MAX_STR); trim(buf); if(strlen(buf)) strncpy(assets[i].location, buf, MAX_STR-1);
            printf("Nilai baru: "); read_line(buf, MAX_STR); trim(buf); if(strlen(buf)) assets[i].value = atof(buf);
            printf("Depresiasi baru %%: "); read_line(buf, MAX_STR); trim(buf); if(strlen(buf)) assets[i].depreciation_rate = atof(buf);
            printf("Status (1=Aktif,0=Non): "); read_line(buf, MAX_STR); trim(buf); if(strlen(buf)) assets[i].active = atoi(buf);
            printf("✔ Aset %d diperbarui\n", id);
            return;
        }
    }
    printf("❌ Aset tidak ditemukan\n");
}

void delete_asset() {
    char buf[MAX_STR];
    printf("ID aset yang dihapus: "); read_line(buf, MAX_STR);
    int id = atoi(buf);
    for (int i=0;i<asset_count;i++) {
        if (assets[i].id == id) {
            for (int j=i;j<asset_count-1;j++) assets[j] = assets[j+1];
            asset_count--;
            printf("🗑 Aset %d terhapus\n", id);
            return;
        }
    }
    printf("❌ Tidak ditemukan\n");
}

/* Asset summary: total nilai aset aktif & simple depreciated value estimate */
double years_between_dates(const char *from, const char *to) {
    struct tm tm_from = {0}, tm_to = {0};
    if (sscanf(from, "%d-%d-%d", &tm_from.tm_year, &tm_from.tm_mon, &tm_from.tm_mday) != 3) return 0;
    if (sscanf(to, "%d-%d-%d", &tm_to.tm_year, &tm_to.tm_mon, &tm_to.tm_mday) != 3) return 0;
    tm_from.tm_year -= 1900; tm_from.tm_mon -= 1;
    tm_to.tm_year -= 1900; tm_to.tm_mon -= 1;
    time_t tfrom = mktime(&tm_from);
    time_t tto = mktime(&tm_to);
    if (tfrom == (time_t)-1 || tto == (time_t)-1) return 0;
    double days = difftime(tto, tfrom) / (60*60*24);
    return days / 365.25;
}

void asset_summary() {
    double total = 0;
    char today[DATE_STR_LEN]; today_str(today, DATE_STR_LEN);
    double total_depreciated = 0;
    int active_assets = 0;
    for (int i=0;i<asset_count;i++) {
        if (assets[i].active) {
            active_assets++;
            total += assets[i].value;
            double yrs = years_between_dates(assets[i].purchase_date, today);
            if (yrs < 0) yrs = 0;
            double dep = assets[i].value * (assets[i].depreciation_rate/100.0) * yrs;
            double current = assets[i].value - dep;
            if (current < 0) current = 0;
            total_depreciated += current;
        }
    }
    printf("Total aset aktif: %d\n", active_assets);
    printf("Total nilai aset (book value): Rp %.2f\n", total);
    printf("Estimasi nilai setelah depresiasi (perkiraan): Rp %.2f\n", total_depreciated);
}

/* ------------------------
   System summary (gabungan)
   ------------------------ */
void system_summary() {
    double total_income = 0.0, total_expense = 0.0;
    for (int i=0;i<tx_count;i++) {
        if (txs[i].type == TX_EXPENSE) total_expense += txs[i].amount;
        else total_income += txs[i].amount;
    }

    int active_tenants = 0;
    for (int i=0;i<tenants_count;i++) if (tenants[i].active) active_tenants++;

    int total_rooms = tenants_count; // asumed number of registered rooms = tenants entries
    double occupancy_rate = 0.0;
    if (total_rooms > 0) occupancy_rate = ((double)active_tenants / (double)total_rooms) * 100.0;

    double total_asset_value = 0.0;
    double total_asset_value_depr = 0.0;
    char today[DATE_STR_LEN]; today_str(today, DATE_STR_LEN);
    int active_assets = 0;
    for (int i=0;i<asset_count;i++) {
        if (assets[i].active) {
            active_assets++;
            total_asset_value += assets[i].value;
            double yrs = years_between_dates(assets[i].purchase_date, today);
            if (yrs < 0) yrs = 0;
            double dep = assets[i].value * (assets[i].depreciation_rate/100.0) * yrs;
            double current = assets[i].value - dep;
            if (current < 0) current = 0;
            total_asset_value_depr += current;
        }
    }

    double balance = total_income - total_expense;

    printf("\n===========================================================\n");
    printf("              📊  RINGKASAN SISTEM KOST  📊\n");
    printf("===========================================================\n");
    printf("👥 Jumlah Penghuni Terdaftar   : %d\n", tenants_count);
    printf("👥 Jumlah Penghuni Aktif       : %d\n", active_tenants);
    printf("🏠 Total Kamar (terdaftar)     : %d\n", total_rooms);
    printf("📈 Occupancy Rate              : %.2f%%\n", occupancy_rate);
    printf("-----------------------------------------------------------\n");
    printf("💼 Total Pemasukan (all time)  : Rp %.2f\n", total_income);
    printf("🧾 Total Pengeluaran (all time): Rp %.2f\n", total_expense);
    printf("💰 Saldo / Laba Bersih         : Rp %.2f\n", balance);
    printf("Jumlah transaksi              : %d\n", tx_count);
    printf("-----------------------------------------------------------\n");
    printf("🏛️  Total Aset Aktif          : %d\n", active_assets);
    printf("🏷️  Total Nilai Aset (book)   : Rp %.2f\n", total_asset_value);
    printf("🏷️  Estimasi Nilai Aset saat ini : Rp %.2f\n", total_asset_value_depr);
    printf("Jumlah aset                   : %d\n", asset_count);
    printf("-----------------------------------------------------------\n");
    if (balance >= 0)
        printf("🔥 Status Keuangan           : PROFIT (Laba)\n");
    else
        printf("⚠️  Status Keuangan           : LOSS (Rugi)\n");
    printf("===========================================================\n\n");

    // Additionally show last few months summary if transactions exist
    if (tx_count > 0) {
        printf("Laporan bulanan ringkasan (semua bulan tercatat):\n");
        monthly_report();
    }
}

/* ------------------------
   Menu & main
   ------------------------ */
void show_menu() {
    printf("\n=== SISTEM MANAJEMEN KOST (CLI) ===\n");
    printf("1. Tambah penyewa\n");
    printf("2. Daftar penyewa\n");
    printf("3. Edit penyewa\n");
    printf("4. Hapus penyewa\n");
    printf("5. Tambah transaksi (sewa/pendapatan/pengeluaran)\n");
    printf("6. Daftar transaksi\n");
    printf("7. Detail penyewa (saldo + riwayat)\n");
    printf("8. Laporan bulanan\n");
    printf("9. Ringkasan cepat\n");
    printf("10. Tambah aset kost\n");
    printf("11. Daftar aset\n");
    printf("12. Edit aset\n");
    printf("13. Hapus aset\n");
    printf("14. Ringkasan aset\n");
    printf("15. Ringkasan Laporan Lengkap (Keuangan + Aset + Penghuni)\n");
    printf("0. Simpan dan keluar\n");
    printf("Pilihan: ");
}

void load_data() {
    load_tenants();
    load_txs();
    load_assets();
}

void save_data() {
    save_tenants();
    save_txs();
    save_assets();
    printf("Data disimpan ke %s, %s, %s\n", TENANT_FILE, TX_FILE, ASSET_FILE);
}

/* Optional demo seed (uncomment inside main if needed) */
void seed_demo() {
    if (tenants_count > 0 || tx_count > 0 || asset_count > 0) return;
    Tenant t1 = {1, "Andi", "A1", 750000.0, 750000.0, 1};
    Tenant t2 = {2, "Budi", "B2", 650000.0, 650000.0, 1};
    ensure_tenants_capacity(); tenants[tenants_count++] = t1;
    ensure_tenants_capacity(); tenants[tenants_count++] = t2;
    Transaction tr1 = {1,1,"2025-10-01",TX_RENT,750000.0,"Sewa Oktober"};
    Transaction tr2 = {2,2,"2025-10-02",TX_RENT,650000.0,"Sewa Oktober"};
    Transaction tr3 = {3,0,"2025-10-05",TX_EXPENSE,200000.0,"Listrik"};
    ensure_tx_capacity(); txs[tx_count++] = tr1;
    ensure_tx_capacity(); txs[tx_count++] = tr2;
    ensure_tx_capacity(); txs[tx_count++] = tr3;
    Asset a1 = {1, "Kulkas", "Dapur Umum", 2500000.0, "2024-01-01", 10.0, 1};
    Asset a2 = {2, "Kasur", "Kamar A1", 800000.0, "2023-06-15", 15.0, 1};
    ensure_assets_capacity(); assets[asset_count++] = a1;
    ensure_assets_capacity(); assets[asset_count++] = a2;
}

/* Main loop */
int main() {
    load_data();
    // seed_demo(); // jika ingin data contoh, uncomment
    char choice[16];
    while (1) {
        show_menu();
        read_line(choice, sizeof(choice));
        if (strlen(choice) == 0) continue;
        int c = atoi(choice);
        switch (c) {
            case 1: add_tenant(); break;
            case 2: list_tenants(); break;
            case 3: edit_tenant(); break;
            case 4: delete_tenant(); break;
            case 5: add_transaction(); break;
            case 6: list_transactions(); break;
            case 7: show_tenant_detail(); break;
            case 8: monthly_report(); break;
            case 9: quick_summary(); break;
            case 10: add_asset(); break;
            case 11: list_assets(); break;
            case 12: edit_asset(); break;
            case 13: delete_asset(); break;
            case 14: asset_summary(); break;
            case 15: system_summary(); break;
            case 0:
                save_data();
                printf("Keluar. Terima kasih.\n");
                free(tenants); free(txs); free(assets);
                exit(0);
            default:
                printf("Pilihan tidak dikenal.\n");
        }
    }
    return 0;
}
