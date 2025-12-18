#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/retribusi.h"

extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;
extern Transaksi dataTransaksi[MAX_TRANSAKSI];
extern int jumlahTransaksi;

void bayarRetribusi() {
    // TODO: Tugas
    // 1. Cari NIK pembayar
    // 2. Input Jenis (Kebersihan/Keamanan) & Nominal
    // 3. Simpan ke array dataTransaksi
    
    printf("\n[DEV] Fitur Bayar Retribusi belum diisi.\n");
    jedaLayar();
}

void laporanTunggakan() {
    // TODO: Tugas 
    // 1. Identifikasi siapa yang belum ada di dataTransaksi bulan ini
    // 2. Masukkan mereka ke array sementara
    // 3. Lakukan Bubble Sort / Selection Sort berdasarkan Nama/RT
    // 4. Tampilkan daftarnya
    
    printf("\n[DEV] Fitur Laporan Tunggakan (Sorting) belum diisi.\n");
    jedaLayar();
}

void riwayatTransaksi() {
    // TODO: Tugas 
    // Tampilkan tabel semua uang yang masuk
    
    printf("\n[DEV] Fitur Riwayat Transaksi belum diisi.\n");
    jedaLayar();
}

void menuRetribusi() {
    int pilihan;
    do {
        bersihkanLayar();
        printf("=== LOKET RETRIBUSI ===\n");
        printf("[1] Bayar Retribusi\n");
        printf("[2] Cek Penunggak\n");
        printf("[3] Riwayat Transaksi Masuk\n");
        printf("[0] Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1: bayarRetribusi(); break;
            case 2: laporanTunggakan(); break;
            case 3: riwayatTransaksi(); break;
            case 0: break;
            default: printf("Salah input!\n"); jedaLayar();
        }
    } while (pilihan != 0);
}
