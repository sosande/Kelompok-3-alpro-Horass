#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h" 
#include "../include/data_warga.h"

// ambil data variable dari file main.c 
extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;

void menuDataWarga() {
  int pilihan;

  do {
    bersihkanLayar();

    printf("=== MENU KELOLA DATA WARGA ===\n");
    printf("[1] Tambah Warga Baru\n");
    printf("[2] Lihat Daftar Warga\n");
    printf("[3] Edit Data Warga\n");   
    printf("[4] Hapus Warga\n");      
    printf("[0] Kembali ke Menu Utama\n");
    printf("------------------------------\n");
    printf("Pilihan: ");

    scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
            // tambahWarga();
            jedaLayar();
             break;
        case 2:
            // lihatDaftarWarga();
            jedaLayar();
            break;
        case 3:          
            // ubahWarga();
            jedaLayar();
            break;
        case 4:            
            // hapusWarga();
            jedaLayar();
            break;
        case 0:
            printf("Kembali ke menu utama...\n");
            break;
        default:
            printf("Pilihan salah!\n");
            jedaLayar();
        }
    } while (pilihan != 0);
}
