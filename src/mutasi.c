#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/mutasi.h"

extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;
extern Mutasi dataMutasi[MAX_MUTASI];
extern int jumlahMutasi;

// Helper: Cek apakah NIK sudah dipakai
int cekNIKDuplikat(char* nik) {
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nik) == 0) return 1;
    }
    return 0;
}

void pindahDatang() { 
    Penduduk p;
    Mutasi m;

    bersihkanLayar();
    printf("=== INPUT WARGA PINDAH DATANG ===\n");

    // 1. DATA MUTASI
    printf("Tanggal Pindah (DD MM YYYY): ");
    scanf("%d %d %d", &m.tglKejadian.hari, &m.tglKejadian.bulan, &m.tglKejadian.tahun);
    
    // 2. DATA WARGA
    printf("Masukan NIK : ");
    scanf("%s", p.nik);

    // Validasi 16 Digit
    if (strlen(p.nik) != 16) {
        printf("[KESALAHAN] NIK harus 16 digit!\n");
        jedaLayar();
        return;
    }

    // Validasi Duplikat 
    if (cekNIKDuplikat(p.nik)) {
        printf("[KESALAHAN] NIK sudah terdaftar!\n");
        jedaLayar();
        return;
    }

    printf("Masukan Nama : ");
    scanf(" %[^\n]", p.namaLengkap);

    printf("Tempat Lahir : ");
    scanf(" %[^\n]", p.tempatLahir);

    printf("Tanggal Lahir (DD MM YYYY) : ");
    scanf("%d %d %d", &p.tglLahir.hari, &p.tglLahir.bulan, &p.tglLahir.tahun);

    printf("Jenis Kelamin (L/P) : ");
    scanf("%s", p.jenisKelamin);

    printf("Alamat : ");
    scanf(" %[^\n]", p.alamat);

    printf("RT / RW : ");
    scanf("%d / %d", &p.rt, &p.rw);

    printf("Agama : ");
    scanf(" %[^\n]", p.agama);

    printf("Pekerjaan : ");
    scanf(" %[^\n]", p.pekerjaan);

    printf("Status Kawin : ");
    scanf(" %[^\n]", p.statusPerkawinan);

    // Set status default
    strcpy(p.statusWarga, "Aktif");

    // Simpan ke Array Warga
    dataWarga[jumlahWarga] = p;
    jumlahWarga++;

    // Simpan ke Log Mutasi
    strcpy(dataMutasi[jumlahMutasi].nikTerkait, p.nik);
    strcpy(dataMutasi[jumlahMutasi].jenisMutasi, "Pindah Datang");
    strcpy(dataMutasi[jumlahMutasi].alasan, "Warga Pindah Datang");
    dataMutasi[jumlahMutasi].tglKejadian = m.tglKejadian;
    
    jumlahMutasi++;

    printf("\n[SUKSES] Warga baru berhasil ditambahkan.\n");
    jedaLayar();
}

void pindahKeluar() {
    char nikTerkait[17];
    int index = -1;

    bersihkanLayar();
    printf("=== INPUT PINDAH KELUAR ===\n");
    printf("Masukan NIK : ");
    scanf("%s", nikTerkait);

    // Cari NIK
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nikTerkait) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("[KESALAHAN] NIK tidak ditemukan.\n");
    } else {
        // Tampilkan nama biar yakin
        printf("Ditemukan: %s\n", dataWarga[index].namaLengkap);
        
        // Update Status Warga
        strcpy(dataWarga[index].statusWarga, "Pindah");

        // Catat Log Mutasi
        strcpy(dataMutasi[jumlahMutasi].nikTerkait, nikTerkait);
        strcpy(dataMutasi[jumlahMutasi].jenisMutasi, "Pindah Keluar");

        printf("Tanggal Pindah (DD MM YYYY) : ");
        scanf("%d %d %d", &dataMutasi[jumlahMutasi].tglKejadian.hari, &dataMutasi[jumlahMutasi].tglKejadian.bulan, &dataMutasi[jumlahMutasi].tglKejadian.tahun);

        printf("Alasan pindah : ");
        scanf(" %[^\n]", dataMutasi[jumlahMutasi].alasan);

        jumlahMutasi++;
        printf("\n[SUKSES] Data pindah keluar berhasil dicatat.\n");
    }

    jedaLayar();
}

void laporKematian() {
    char nikTerkait[17];
    int index = -1;

    bersihkanLayar();
    printf("=== LAPOR KEMATIAN ===\n");
    printf("Masukan NIK : ");
    scanf("%s", nikTerkait);

    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nikTerkait) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("[KESALAHAN] NIK tidak ditemukan.\n");
    } else {
        printf("Ditemukan: %s\n", dataWarga[index].namaLengkap);

        // Update Status
        strcpy(dataWarga[index].statusWarga, "Meninggal");

        // Catat Log
        strcpy(dataMutasi[jumlahMutasi].nikTerkait, nikTerkait);
        strcpy(dataMutasi[jumlahMutasi].jenisMutasi, "Kematian");
        strcpy(dataMutasi[jumlahMutasi].alasan, "Meninggal Dunia");

        printf("Tanggal Kematian (DD MM YYYY): ");
        scanf("%d %d %d", &dataMutasi[jumlahMutasi].tglKejadian.hari,
                          &dataMutasi[jumlahMutasi].tglKejadian.bulan,
                          &dataMutasi[jumlahMutasi].tglKejadian.tahun);

        jumlahMutasi++;
        printf("\n[SUKSES] Data kematian berhasil dicatat.\n");
    }

    jedaLayar();
}

void lihatLogMutasi() {
    bersihkanLayar();
    printf("=== LOG MUTASI ===\n");

    if (jumlahMutasi == 0) {
        printf("Belum ada data mutasi.\n");
    } else {
        // Header simpel
        printf("%-3s | %-16s | %-15s | %-12s | %s\n", "NO", "NIK", "JENIS", "TANGGAL", "ALASAN");
        printf("----------------------------------------------------------------------\n");
        
        for (int i = 0; i < jumlahMutasi; i++) {
            printf("%-3d | %-16s | %-15s | %02d-%02d-%04d | %s\n",
                i + 1,
                dataMutasi[i].nikTerkait,
                dataMutasi[i].jenisMutasi,
                dataMutasi[i].tglKejadian.hari,
                dataMutasi[i].tglKejadian.bulan,
                dataMutasi[i].tglKejadian.tahun,
                dataMutasi[i].alasan
            );
        }
    }
    jedaLayar();
}

void menuMutasi() {
    int pilihan;
    do {
        bersihkanLayar();
        printf("=== MENU MUTASI PENDUDUK ===\n");
        printf("[1] Warga Pindah Datang\n");
        printf("[2] Warga Pindah Keluar\n");
        printf("[3] Lapor Kematian\n");
        printf("[4] Lihat Log Mutasi\n");
        printf("[0] Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1: pindahDatang(); break;
            case 2: pindahKeluar(); break;
            case 3: laporKematian(); break;
            case 4: lihatLogMutasi(); break;
            case 0: break;
            default: printf("Salah input!\n"); jedaLayar();
        }
    } while (pilihan != 0);
}
