#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/retribusi.h"
#define MAX_WARGA 100
#define MAX_TRANSAKSI 100

/* =====================
   STRUCT DATA
===================== */
typedef struct {
    int id;
    char nama[50];
    int rt;
} Warga;

typedef struct {
    int idWarga;
    int nominal;
    char tanggal[20];
} Retribusi;

/* =====================
   GLOBAL DATA (SIMULASI)
===================== */
Warga dataWarga[MAX_WARGA];
Retribusi dataRetribusi[MAX_TRANSAKSI];

int jumlahWarga = 0;
int jumlahRetribusi = 0;

/* =====================
   FUNGSI BANTUAN
===================== */
int sudahBayar(int idWarga) {
    for (int i = 0; i < jumlahRetribusi; i++) {
        if (dataRetribusi[i].idWarga == idWarga) {
            return 1;
        }
    }
    return 0;
}

/* =====================
   BAYAR RETRIBUSI
===================== */
void bayarRetribusi() {
    int id, nominal;
    char tanggal[20];

    printf("\n=== BAYAR RETRIBUSI ===\n");
    printf("Masukkan ID Warga   : ");
    scanf("%d", &id);

    printf("Masukkan Nominal    : ");
    scanf("%d", &nominal);

    printf("Masukkan Tanggal    : ");
    scanf("%s", tanggal);

    dataRetribusi[jumlahRetribusi].idWarga = id;
    dataRetribusi[jumlahRetribusi].nominal = nominal;
    strcpy(dataRetribusi[jumlahRetribusi].tanggal, tanggal);

    jumlahRetribusi++;

    printf(">> Pembayaran berhasil dicatat.\n");
}

/* =====================
   SORT BUBBLE (A-Z)
===================== */
void sortPenunggak(Warga penunggak[], int n) {
    Warga temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(penunggak[j].nama, penunggak[j + 1].nama) > 0) {
                temp = penunggak[j];
                penunggak[j] = penunggak[j + 1];
                penunggak[j + 1] = temp;
            }
        }
    }
}

/* =====================
   LAPORAN PENUNGGAK
===================== */
void laporanPenunggak() {
    Warga penunggak[MAX_WARGA];
    int jumlahPenunggak = 0;

    for (int i = 0; i < jumlahWarga; i++) {
        if (!sudahBayar(dataWarga[i].id)) {
            penunggak[jumlahPenunggak++] = dataWarga[i];
        }
    }

    sortPenunggak(penunggak, jumlahPenunggak);

    printf("\n=== LAPORAN PENUNGGAK RETRIBUSI ===\n");
    printf("ID\tNama\t\tRT\n");

    for (int i = 0; i < jumlahPenunggak; i++) {
        printf("%d\t%-15s\t%d\n",
               penunggak[i].id,
               penunggak[i].nama,
               penunggak[i].rt);
    }

    if (jumlahPenunggak == 0) {
        printf("Tidak ada penunggak.\n");
    }
}

/* =====================
   MENU RETRIBUSI
===================== */
void menuRetribusi() {
    int pilih;
    do {
        printf("\n=== MENU RETRIBUSI ===\n");
        printf("1. Bayar Retribusi\n");
        printf("2. Laporan Penunggak\n");
        printf("0. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                bayarRetribusi();
                break;
            case 2:
                laporanPenunggak();
                break;
        }
    } while (pilih != 0);
}
