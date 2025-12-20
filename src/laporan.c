#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/laporan.h"

extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;
extern Transaksi dataTransaksi[MAX_TRANSAKSI];
extern int jumlahTransaksi;

void statistikWarga() {
    int laki = 0, perempuan = 0;
    for(int i = 0; i < jumlahWarga; i++){
        if(strcmp(dataWarga[i].jenisKelamin, "Laki-laki") == 0){
            laki++;
        } else if(strcmp(dataWarga[i].jenisKelamin, "Perempuan") == 0){
            perempuan++;
        }
    }
    printf("\n=== STATISTIK KEPENDUDUKAN ===\n");
    printf("Jumlah Laki-laki: %d\n", laki);
    printf("Jumlah Perempuan: %d\n", perempuan);
    printf("Jumlah Penduduk: %d\n", jumlahWarga);
    jedaLayar();
}

void rekapKeuangan() {
    long total = 0;
    for(int i = 0; i < jumlahTransaksi; i++){
        total += dataTransaksi[i].nominal;
    }
    printf("\n=== REKAP KEUANGAN DESA ===\n");
    printf("Total Pemasukan Desa: %ld\n", total);
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
