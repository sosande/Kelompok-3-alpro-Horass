#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/retribusi.h"

extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;
extern Transaksi dataTransaksi[MAX_TRANSAKSI];
extern int jumlahTransaksi;

/*  
   BAYAR RETRIBUSI
 */
void bayarRetribusi() {
    char nikCari[20];
    int ditemukan = -1;

    // Cegah overflow array
    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        printf("Data transaksi sudah penuh!\n");
        jedaLayar();
        return;
    }

    printf("\n=== BAYAR RETRIBUSI ===\n");
    printf("Masukkan NIK: ");
    scanf("%19s", nikCari);

    // Cari warga
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nikCari) == 0) {
            ditemukan = i;
            break;
        }
    }

    if (ditemukan == -1) {
        printf("Warga tidak ditemukan.\n");
        jedaLayar();
        return;
    }

    // Cegah pembayaran ganda
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (strcmp(dataTransaksi[i].nik, nikCari) == 0) {
            printf("Warga ini sudah membayar retribusi.\n");
            jedaLayar();
            return;
        }
    }
