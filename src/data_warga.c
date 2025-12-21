#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h" 
#include "../include/data_warga.h"

// ambil data variable dari file main.c 
extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;

void tambahWarga() {
   Penduduk p;

    // 1. Cek apakah database penuh
    if (jumlahWarga >= MAX_WARGA) {
        printf("[KESALAHAN] Database warga sudah penuh.\n");
        jedaLayar();
        return;
    }

    bersihkanLayar();
    printf("=== TAMBAH DATA WARGA BARU ===\n");

    // 2. Input NIK
    printf("NIK (16 digit): ");
    scanf("%16s", p.nik);

    // 3. Validasi NIK
    int count = strlen(p.nik);

    if (count != 16) {
        printf("[KESALAHAN] NIK harus 16 digit.\n");
        jedaLayar();
        return;
    }

    if (cekNIKTerdaftar(p.nik)) {
        printf("[KESALAHAN] NIK sudah terdaftar.\n");
        jedaLayar();
        return;
    }
    
    // Input data lainnya
    printf("Nama Lengkap        : ");
    scanf(" %[^\n]", p.namaLengkap);

    printf("Tempat Lahir        : ");
    scanf(" %[^\n]", p.tempatLahir);

    printf("Tanggal Lahir (DD MM YYYY): ");
    scanf("%d %d %d", 
          &p.tglLahir.hari, 
          &p.tglLahir.bulan, 
          &p.tglLahir.tahun);

    printf("Jenis Kelamin       : ");
    scanf(" %[^\n]", p.jenisKelamin);

    printf("Alamat              : ");
    scanf(" %[^\n]", p.alamat);

    printf("RT                  : ");
    scanf("%d", &p.rt);

    printf("RW                  : ");
    scanf("%d", &p.rw);

    printf("Agama               : ");
    scanf(" %[^\n]", p.agama);

    printf("Status Perkawinan   : ");
    scanf(" %[^\n]", p.statusPerkawinan);

    printf("Pekerjaan           : ");
    scanf(" %[^\n]", p.pekerjaan);

    // warga otomatis aktif
    strcpy(p.statusWarga, "Aktif");

    // 4. Simpan ke array
    dataWarga[jumlahWarga] = p;
    jumlahWarga++;

    printf("\n[SUKSES] Data warga berhasil ditambahkan.\n");
    jedaLayar();
}

void lihatDaftarWarga() {
    bersihkanLayar();
    printf("=== DAFTAR DATA WARGA ===\n");

    if (jumlahWarga == 0) {
        printf("[INFO] Belum ada data warga.\n");
        jedaLayar();
        return;
    }

    printf("----------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-16s | %-20s | %-12s | %-15s | %-10s |\n",
           "No", "NIK", "Nama", "Kelamin", "Pekerjaan", "Status");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahWarga; i++) {
        printf("| %-3d | %-16s | %-20s | %-12s | %-15s | %-10s |\n",
               i + 1,
               dataWarga[i].nik,
               dataWarga[i].namaLengkap,
               dataWarga[i].jenisKelamin,
               dataWarga[i].pekerjaan,
               dataWarga[i].statusWarga);
    }

    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Total Warga: %d orang\n", jumlahWarga);

    jedaLayar();
}

void detailWarga(char* nik) {
    int index = -1;

    // Cari index warga berdasarkan NIK
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nik) == 0) {
            index = i;
            break;
        }
    }

    bersihkanLayar();

    if (index == -1) {
        printf("=== DETAIL DATA WARGA ===\n");
        printf("[KESALAHAN] Data warga dengan NIK '%s' tidak ditemukan.\n", nik);
        jedaLayar();
        return;
    }

    Penduduk p = dataWarga[index];

    printf("================================= DETAIL DATA WARGA =================================\n");
    printf("NIK              : %-16s\n", p.nik);
    printf("Nama Lengkap     : %-40s\n", p.namaLengkap);
    printf("Tempat/Tgl Lahir : %s, %02d-%02d-%04d\n",
           p.tempatLahir,
           p.tglLahir.hari,
           p.tglLahir.bulan,
           p.tglLahir.tahun);
    printf("Jenis Kelamin    : %-20s\n", p.jenisKelamin);
    printf("Alamat           : %-60s\n", p.alamat);
    printf("RT / RW          : %02d / %02d\n", p.rt, p.rw);
    printf("Agama            : %-20s\n", p.agama);
    printf("Status Kawin     : %-20s\n", p.statusPerkawinan);
    printf("Pekerjaan        : %-30s\n", p.pekerjaan);
    printf("Status Warga     : %-20s\n", p.statusWarga);
    printf("======================================================================================\n");

    jedaLayar();
}


void cariWarga() {
    char input[100];
    int index = -1;
    // minta input NIK atau Nama
    printf("Masukkan NIK atau Nama Warga: ");
    scanf("%s", input);
    // cari data warga dengan nik atau nama
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, input) == 0 || strcmp(dataWarga[i].namaLengkap, input) == 0) {
            index = i;
            break;
        }
    }
    // tampilkan detail warga jika ditemukan
    if (index != -1) {
        detailWarga(dataWarga[index].nik);
    } else {
        printf("[KESALAHAN] Data warga tidak ditemukan.\n");
        jedaLayar();
    }
}

void editWarga() {
    char nik[17];
    int index = -1;
    int pilihan;
    char buffer[100]; 

    bersihkanLayar();
    printf("======================================================================================\n");
    printf("                                  EDIT DATA WARGA                                     \n");
    printf("======================================================================================\n");
    printf("Masukkan NIK Warga yang ingin diedit: ");
    scanf("%s", nik);

    // 1. CARI DATA
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nik) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\n[ERROR] Data warga dengan NIK '%s' tidak ditemukan.\n", nik);
        jedaLayar();
        return;
    }

    // 2. TAMPILKAN DATA SAAT INI (PREVIEW)
    Penduduk *p = &dataWarga[index]; 

    printf("\n--- DATA SAAT INI ---\n");
    printf("1. Nama Lengkap  : %s\n", p->namaLengkap);
    printf("2. TTL           : %s, %02d-%02d-%d\n", p->tempatLahir, p->tglLahir.hari, p->tglLahir.bulan, p->tglLahir.tahun);
    printf("3. Alamat Lengkap: %s, RT %03d / RW %03d\n", p->alamat, p->rt, p->rw);
    printf("4. Agama         : %s\n", p->agama);
    printf("5. Pekerjaan     : %s\n", p->pekerjaan);
    printf("6. Status Kawin  : %s\n", p->statusPerkawinan);
    printf("7. Status Warga  : %s\n", p->statusWarga);
    printf("--------------------------------------------------------------------------------------\n");
    printf("[INFO] NIK tidak dapat diubah demi keamanan data.\n");
    printf("--------------------------------------------------------------------------------------\n");

    // 3. MENU PILIHAN
    printf("\nBagian mana yang ingin diubah? [1-7] atau [0] Batal: ");
    scanf("%d", &pilihan);

    if (pilihan == 0) {
        printf("\n[INFO] Edit dibatalkan.\n");
        jedaLayar();
        return;
    }

    // 4. LOGIKA EDIT
    printf("\n>> Masukkan Data Baru:\n");

    switch (pilihan) {
        case 1: // NAMA
            printf("Nama Lengkap Baru: ");
            scanf(" %[^\n]", p->namaLengkap);
            break;

        case 2: // TTL
            printf("Tempat Lahir : ");
            scanf(" %[^\n]", p->tempatLahir);
            printf("Tanggal (DD) : "); scanf("%d", &p->tglLahir.hari);
            printf("Bulan   (MM) : "); scanf("%d", &p->tglLahir.bulan);
            printf("Tahun   (YYYY): "); scanf("%d", &p->tglLahir.tahun);
            break;

        case 3: // ALAMAT 
            printf("Nama Jalan/Dusun: ");
            scanf(" %[^\n]", p->alamat);
            printf("RT Baru (Angka) : "); scanf("%d", &p->rt);
            printf("RW Baru (Angka) : "); scanf("%d", &p->rw);
            break;

        case 4: // AGAMA
            printf("Agama: ");
            scanf(" %[^\n]", p->agama);
            break;

        case 5: // PEKERJAAN
            printf("Pekerjaan: ");
            scanf(" %[^\n]", p->pekerjaan);
            break;

        case 6: // STATUS PERKAWINAN 
            printf("Status Kawin: ");
            scanf(" %[^\n]", p->statusPerkawinan);
            break;

        case 7: // STATUS WARGA
            printf("Status Warga (Aktif/Pindah/Meninggal): ");
            scanf(" %[^\n]", p->statusWarga);
            break;

        default:
            printf("\n[ERROR] Pilihan tidak valid!\n");
            jedaLayar();
            return;
    }

    printf("\n[SUKSES] Data berhasil diperbarui!\n");
    
    jedaLayar();
}

void hapusWarga() {
    char nik[17] = "";
    char konfirmasi;
    int index = -1;

    bersihkanLayar();
    printf("================================= HAPUS DATA WARGA =================================\n");
    printf("Masukkan NIK Target: ");
    scanf("%s", nik);
    printf("--------------------------------------------------------------------------------------\n");

    // Cari data warga
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nik) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("[KESALAHAN] Data warga dengan NIK '%s' tidak ditemukan.\n", nik);
        printf("======================================================================================\n");
        jedaLayar();
        return;
    }

    Penduduk p = dataWarga[index];

    // Tampilkan ringkasan data
    printf("DATA WARGA DITEMUKAN\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("NIK          : %-16s\n", p.nik);
    printf("Nama Lengkap : %-40s\n", p.namaLengkap);
    printf("Alamat       : %-60s\n", p.alamat);
    printf("Status Warga : %-20s\n", p.statusWarga);
    printf("--------------------------------------------------------------------------------------\n");

    printf("[PERINGATAN] Data yang dihapus tidak dapat dikembalikan.\n");
    printf("Apakah Anda yakin ingin menghapus data ini? (Y/N): ");
    scanf(" %c", &konfirmasi);

    if (konfirmasi == 'Y' || konfirmasi == 'y') {
        for (int i = index; i < jumlahWarga - 1; i++) {
            dataWarga[i] = dataWarga[i + 1];
        }

        jumlahWarga--;
        printf("\n[SUKSES] Data warga atas nama %-40s telah dihapus.\n", p.namaLengkap);
    } else {
        printf("\n[INFO] Penghapusan data dibatalkan oleh pengguna.\n");
    }

    printf("======================================================================================\n");
    jedaLayar();
}

int cekNIKTerdaftar(char* nikCek) {
    // untuk mengecek apakah nik sudah terdaftar atau belum
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nikCek) == 0) {
            return 1; // Ada
        }
    }
    return 0; // Tidak ada
}

void menuDataWarga() {
    int pilihan;

    do {
        bersihkanLayar();
        printf("================================ MENU KELOLA DATA WARGA ================================\n");
        printf("[1] Tambah Warga Baru\n");
        printf("[2] Lihat Daftar Warga\n");
        printf("[3] Cari & Detail Warga\n");
        printf("[4] Edit Data Warga\n");
        printf("[5] Hapus Warga\n");
        printf("[0] Kembali ke Menu Utama\n");
        printf("--------------------------------------------------------------------------------------\n");
        printf("Pilihan: ");

        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tambahWarga(); break;
            case 2: lihatDaftarWarga(); break;
            case 3: cariWarga(); break;
            case 4: editWarga(); break;
            case 5: hapusWarga(); break;
            case 0:
                printf("\n[INFO] Kembali ke menu utama...\n");
                jedaLayar();
                break;
            default:
                printf("\n[KESALAHAN] Pilihan menu tidak valid.\n");
                jedaLayar();
        }
    } while (pilihan != 0);
}
