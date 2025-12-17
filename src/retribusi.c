#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/retribusi.h"

extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;
extern Transaksi dataTransaksi[MAX_TRANSAKSI];
extern int jumlahTransaksi;

/* ==============================
  ini BAYAR RETRIBUSI
============================== */
void bayarRetribusi() {
    char nikCari[20];
    int ditemukan = -1;

    printf("\n=== BAYAR RETRIBUSI ===\n");
    printf("Masukkan NIK: ");
    scanf("%s", nikCari);

    // Cari warga berdasarkan NIK
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

    // Input data transaksi
    strcpy(dataTransaksi[jumlahTransaksi].nik, nikCari);

    printf("Jenis Retribusi (Kebersihan/Keamanan): ");
    scanf("%s", dataTransaksi[jumlahTransaksi].jenis);

    printf("Nominal: ");
    scanf("%d", &dataTransaksi[jumlahTransaksi].nominal);

    jumlahTransaksi++;

    printf("Pembayaran berhasil dicatat.\n");
    jedaLayar();
}

/* ==============================
  ini  LAPORAN TUNGGAKAN
============================== */
void laporanTunggakan() {
    Penduduk penunggak[MAX_WARGA];
    int jumlahPenunggak = 0;
    int sudahBayar;

    // Cek siapa yang belum membayar
    for (int i = 0; i < jumlahWarga; i++) {
        sudahBayar = 0;
        for (int j = 0; j < jumlahTransaksi; j++) {
            if (strcmp(dataWarga[i].nik, dataTransaksi[j].nik) == 0) {
                sudahBayar = 1;
                break;
            }
        }
        if (!sudahBayar) {
            penunggak[jumlahPenunggak++] = dataWarga[i];
        }
    }

    // Bubble Sort berdasarkan nama (A-Z)
    Penduduk temp;
    for (int i = 0; i < jumlahPenunggak - 1; i++) {
        for (int j = 0; j < jumlahPenunggak - i - 1; j++) {
            if (strcmp(penunggak[j].nama, penunggak[j + 1].nama) > 0) {
                temp = penunggak[j];
                penunggak[j] = penunggak[j + 1];
                penunggak[j + 1] = temp;
            }
        }
    }

    printf("\n=== DAFTAR PENUNGGAK RETRIBUSI ===\n");
    printf("NIK\t\tNama\t\tRT\n");

    for (int i = 0; i < jumlahPenunggak; i++) {
        printf("%s\t%-15s\t%d\n",
               penunggak[i].nik,
               penunggak[i].nama,
               penunggak[i].rt);
    }

    if (jumlahPenunggak == 0) {
        printf("Tidak ada penunggak.\n");
    }

    jedaLayar();
}

/* ==============================
  ini  RIWAYAT TRANSAKSI
============================== */
void riwayatTransaksi() {
    int total = 0;

    printf("\n=== RIWAYAT TRANSAKSI RETRIBUSI ===\n");
    printf("No\tNIK\t\tJenis\t\tNominal\n");

    for (int i = 0; i < jumlahTransaksi; i++) {
        printf("%d\t%s\t%-10s\t%d\n",
               i + 1,
               dataTransaksi[i].nik,
               dataTransaksi[i].jenis,
               dataTransaksi[i].nominal);
        total += dataTransaksi[i].nominal;
    }

    printf("----------------------------------\n");
    printf("Total Uang Masuk: %d\n", total);

    jedaLayar();
}

/* ==============================
  ini MENU
============================== */
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
