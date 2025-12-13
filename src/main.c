#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"
#include "../include/structs.h"
#include "../include/file_handler.h"
#include "../include/data_warga.h"
#include "../include/layanan_surat.h"
#include "../include/retribusi.h"
#include "../include/mutasi.h"
#include "../include/laporan.h"

// deklarasi penyimpanan data
Penduduk dataWarga[MAX_WARGA];           
RiwayatSurat dataSurat[MAX_SURAT];      
Transaksi dataTransaksi[MAX_TRANSAKSI];  
Mutasi dataMutasi[MAX_MUTASI];

// Penghitung jumlah data
int jumlahWarga = 0;
int jumlahSurat = 0;
int jumlahTransaksi = 0;
int jumlahMutasi = 0;

int main() {
  int pilihan;

  muatData();

  do {
    // bersihkan layar
    bersihkanLayar();

    printf("===================================================\n");
    printf("   SISTEM ADMINISTRASI KEPENDUDUKAN & RETRIBUSI    \n");
    printf("===================================================\n");
    printf("MENU UTAMA:\n");
    printf("[1] Kelola Data Warga\n");
    printf("[2] Layanan Surat\n");
    printf("[3] Loket Retribusi\n");
    printf("[4] Mutasi Penduduk\n");
    printf("[5] Laporan & Statistik\n");
    printf("---------------------------------------------------\n");
    printf("[0] Simpan & Keluar\n");
    printf("===================================================\n");
    printf("Pilihan Anda: ");

    // Input Pilihan
    scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
            menuDataWarga();
            break;
        case 2:
            menuLayananSurat();
            break;
        case 3:
            menuRetribusi();
            break;
        case 4:
            menuMutasi();
            break;
        case 5:
            menuLaporan();
            break;
        case 0:
            printf("\n[INFO] Sedang menyimpan data... Jangan matikan laptop!\n");
            simpanData(); // <--- simpan data sebelum program berakhir 
            printf("[INFO] Terima kasih! Sampai jumpa.\n");
            break;
        default:
            printf("\n[ERROR] Pilihan tidak valid! Masukkan angka 0-5.\n");
            jedaLayar();
   }
  } while (pilihan != 0);

  return 0;
}
