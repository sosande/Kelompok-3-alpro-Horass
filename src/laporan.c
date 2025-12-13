#include <stdio.h>
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/laporan.h"

extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;
extern Transaksi dataTransaksi[MAX_TRANSAKSI];
extern int jumlahTransaksi;

void statistikWarga() {
    // TODO: Tugas
    // 1. Loop dataWarga
    // 2. Hitung berapa Laki-laki, Perempuan, Kartu Keluarga (KK)
    // 3. Tampilkan angka-angkanya
    printf("\n[DEV] Statistik Warga belum diisi.\n");
    jedaLayar();
}

void rekapKeuangan() {
    // TODO: Tugas
    // 1. Loop dataTransaksi
    // 2. Jumlahkan field 'nominal'
    // 3. Tampilkan Total Pemasukan Desa
    printf("\n[DEV] Rekap Keuangan belum diisi.\n");
    jedaLayar();
}

void menuLaporan() {
    int pilihan;
    do {
        bersihkanLayar();
        printf("=== MENU LAPORAN & STATISTIK ===\n");
        printf("[1] Statistik Kependudukan\n");
        printf("[2] Rekap Keuangan Desa\n");
        printf("[0] Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1: statistikWarga(); break;
            case 2: rekapKeuangan(); break;
            case 0: break;
            default: printf("Salah input!\n"); jedaLayar();
        }
    } while (pilihan != 0);
}
