
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
        if (strcmp(dataTransaksi[i].nikPembayar, nikCari) == 0) {
            printf("Warga ini sudah membayar retribusi.\n");
            jedaLayar();
            return;
        }
    }

    // Simpan transaksi
    strcpy(dataTransaksi[jumlahTransaksi].nikPembayar, nikCari);

    printf("Jenis Retribusi (Kebersihan/Keamanan): ");
    scanf("%19s", dataTransaksi[jumlahTransaksi].jenisRetribusi);

    printf("Nominal: ");
    scanf("%d", &dataTransaksi[jumlahTransaksi].nominal);

    if (dataTransaksi[jumlahTransaksi].nominal <= 0) {
        printf("Nominal tidak valid.\n");
        jedaLayar();
        return;
    }

    jumlahTransaksi++;

    printf("Pembayaran berhasil dicatat.\n");
    jedaLayar();
}

/* 
   LAPORAN TUNGGAKAN
   Asumsi: Berlaku untuk satu periode aktif
  */
void laporanTunggakan() {
    Penduduk penunggak[MAX_WARGA];
    int jumlahPenunggak = 0;
    int sudahBayar;

    // Bandingkan data warga vs transaksi
    for (int i = 0; i < jumlahWarga; i++) {
        sudahBayar = 0;
        for (int j = 0; j < jumlahTransaksi; j++) {
            if (strcmp(dataWarga[i].nik, dataTransaksi[j].nikPembayar) == 0) {
                sudahBayar = 1;
                break;
            }
        }
        if (!sudahBayar) {
            penunggak[jumlahPenunggak++] = dataWarga[i];
        }
    }

    // Bubble Sort O(n^2) berdasarkan nama (A-Z)
    Penduduk temp;
    for (int i = 0; i < jumlahPenunggak - 1; i++) {
        for (int j = 0; j < jumlahPenunggak - i - 1; j++) {
            if (strcmp(penunggak[j].namaLengkap, penunggak[j + 1].namaLengkap) > 0) {
                temp = penunggak[j];
                penunggak[j] = penunggak[j + 1];
                penunggak[j + 1] = temp;
            }
        }
    }

    printf("\n=== DAFTAR PENUNGGAK RETRIBUSI ===\n");
    printf("%-16s %-15s %s\n", "NIK", "Nama", "RT");

    for (int i = 0; i < jumlahPenunggak; i++) {
        printf("%-16s %-15s %d\n",
               penunggak[i].nik,
               penunggak[i].namaLengkap,
               penunggak[i].rt);
    }

    if (jumlahPenunggak == 0) {
        printf("Tidak ada penunggak.\n");
    }

    jedaLayar();
}

/* 
   RIWAYAT TRANSAKSI
  */
void riwayatTransaksi() {
    int total = 0;

    printf("\n=== RIWAYAT TRANSAKSI RETRIBUSI ===\n");
    printf("%-3s %-16s %-12s %s\n", "No", "NIK", "Jenis", "Nominal");

    for (int i = 0; i < jumlahTransaksi; i++) {
        printf("%-3d %-16s %-12s %d\n",
               i + 1,
               dataTransaksi[i].nikPembayar,
               dataTransaksi[i].jenisRetribusi,
               dataTransaksi[i].nominal);
        total += dataTransaksi[i].nominal;
    }

    printf("----------------------------------\n");
    printf("Total Uang Masuk: %d\n", total);

    jedaLayar();
}

/*  
   MENU RETRIBUSI
  */
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
            default:
                printf("Salah input!\n");
                jedaLayar();
        }
    } while (pilihan != 0);
}
