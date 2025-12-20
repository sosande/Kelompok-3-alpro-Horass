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
    int laki = 0, perempuan = 0, kk = 0;
    for(int i = 0; i < jumlahWarga; i++){
        if(strcmp(dataWarga[i].jenisKelamin, "Laki-laki") == 0){
            laki++;
        } else if(strcmp(dataWarga[i].jenisKelamin, "Perempuan") == 0){
            perempuan++;
        }
        kk++;
    }
    printf("\n=== STATISTIK KEPENDUDUKAN ===\n");
    printf("Jumlah Laki-laki: %d\n", laki);
    printf("Jumlah Perempuan: %d\n", perempuan);
    printf("Jumlah Kartu Keluarga: %d\n", kk);
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

void tampilkanTabelWarga() {
    printf("\n=== DAFTAR WARGA ===\n");
    if (jumlahWarga == 0) {
        printf("Tidak ada data warga.\n");
        return;
    }
    printf("%-16s %-20s %-10s %-15s %-5s %-5s %-10s\n", "NIK", "Nama", "Jenis Kelamin", "Alamat", "RT", "RW", "Status");
    printf("--------------------------------------------------------------------------------\n");
    for(int i = 0; i < jumlahWarga; i++){
        printf("%-16s %-20s %-10s %-15s %-5d %-5d %-10s\n", 
               dataWarga[i].nik, 
               dataWarga[i].namaLengkap, 
               dataWarga[i].jenisKelamin, 
               dataWarga[i].alamat, 
               dataWarga[i].rt, 
               dataWarga[i].rw, 
               dataWarga[i].statusWarga);
    }
}

void eksporKeFile() {
    char namaFile[100];
    printf("Masukkan nama file untuk ekspor (tanpa ekstensi): ");
    scanf("%s", namaFile);
    strcat(namaFile, ".txt");
    
    FILE *file = fopen(namaFile, "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk ekspor.\n");
        jedaLayar();
        return;
    }
    
    fprintf(file, "Daftar Warga\n");
    fprintf(file, "NIK,Nama,Jenis Kelamin,Alamat,RT,RW,Status\n");
    for(int i = 0; i < jumlahWarga; i++){
        fprintf(file, "%s,%s,%s,%s,%d,%d,%s\n", 
                dataWarga[i].nik, 
                dataWarga[i].namaLengkap, 
                dataWarga[i].jenisKelamin, 
                dataWarga[i].alamat, 
                dataWarga[i].rt, 
                dataWarga[i].rw, 
                dataWarga[i].statusWarga);
    }
    fclose(file);
    printf("Data berhasil diekspor ke file %s\n", namaFile);
    jedaLayar();
}

void laporanDataWarga() {
    int pilihan;
    do {
        bersihkanLayar();
        printf("=== LAPORAN DATA WARGA ===\n");
        printf("[1] Tampilkan Semua Warga\n");
        printf("[2] Ekspor ke File\n");
        printf("[0] Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1: tampilkanTabelWarga(); jedaLayar(); break;
            case 2: eksporKeFile(); break;
            case 0: break;
            default: printf("Salah input!\n"); jedaLayar();
        }
    } while (pilihan != 0);
}

void menuLaporan() {
    int pilihan;
    do {
        bersihkanLayar();
        printf("=== MENU LAPORAN & STATISTIK ===\n");
        printf("[1] Statistik Kependudukan\n");
        printf("[2] Rekap Keuangan Desa\n");
        printf("[3] Laporan Data Warga\n");
        printf("[0] Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1: statistikWarga(); break;
            case 2: rekapKeuangan(); break;
            case 3: laporanDataWarga(); break;
            case 0: break;
            default: printf("Salah input!\n"); jedaLayar();
        }
    } while (pilihan != 0);
}
