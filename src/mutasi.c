#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/mutasi.h"

// akses data warga untuk mengubah status
extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;
extern Mutasi dataMutasi[MAX_MUTASI];
extern int jumlahMutasi;

void pindahDatang() {
    // TODO: Tugas
    // Ini mirip tambahWarga(), tapi catat juga ke dataMutasi sebagai "Masuk"
    printf("\n[DEV] Fitur Pindah Datang belum diisi.\n");
    jedaLayar();
}

void pindahKeluar() {
    // TODO: Tugas
    // 1. Cari NIK
    // 2. Ubah dataWarga[i].statusWarga jadi "Pindah"
    // 3. Catat alasan dan tujuan ke dataMutasi
    printf("\n[DEV] Fitur Pindah Keluar belum diisi.\n");
    jedaLayar();
}

void laporKematian() {
    // TODO: Tugas
    // 1. Cari NIK
    // 2. Ubah dataWarga[i].statusWarga jadi "Meninggal"
    // 3. Catat tanggal kematian ke dataMutasi
    printf("\n[DEV] Fitur Lapor Kematian belum diisi.\n");
    jedaLayar();
}

void lihatLogMutasi() {
    // Tampilkan tabel mutasi
    printf("\n[DEV] Fitur Log Mutasi belum diisi.\n");
    jedaLayar();
}

void menuMutasi() {
    int pilihan;
    do {
        bersihkanLayar();
        printf("=== MENU MUTASI PENDUDUK ===\n");
        printf("[1] Warga Pindah Datang (Masuk)\n");
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
