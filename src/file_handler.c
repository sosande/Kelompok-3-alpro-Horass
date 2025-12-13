#include <stdio.h>
#include "../include/structs.h"
#include "../include/file_handler.h"

// deklarasi variable
// extern berfungsi agar variable tidak dibuat duplikat, dan dapat digunakan di beberapa file 
extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;

extern RiwayatSurat dataSurat[MAX_SURAT];
extern int jumlahSurat;

extern Transaksi dataTransaksi[MAX_TRANSAKSI];
extern int jumlahTransaksi;

extern Mutasi dataMutasi[MAX_MUTASI];
extern int jumlahMutasi;

void muatData() {
    FILE *file;

    // 1. LOAD DATA WARGA
    file = fopen("data/db_warga.dat", "rb"); // rb = Read Binary
    if (file != NULL) {
        fread(&jumlahWarga, sizeof(int), 1, file); // Baca jumlahnya dulu, lalu simpan di variable jumlah
        fread(dataWarga, sizeof(Penduduk), jumlahWarga, file); // Baca datanya, lalu simpan di variable data
        fclose(file);
    } else {
        printf("[INFO] File data warga baru dibuat.\n");
    }

    // 2. LOAD DATA SURAT
    file = fopen("data/db_surat.dat", "rb");
    if (file != NULL) {
        fread(&jumlahSurat, sizeof(int), 1, file);
        fread(dataSurat, sizeof(RiwayatSurat), jumlahSurat, file);
        fclose(file);
    } else {
        printf("[INFO] File data riwayat surat baru dibuat.\n");
    }

    // 3. LOAD DATA KEUANGAN
    file = fopen("data/db_keuangan.dat", "rb");
    if (file != NULL) {
        fread(&jumlahTransaksi, sizeof(int), 1, file);
        fread(dataTransaksi, sizeof(Transaksi), jumlahTransaksi, file);
        fclose(file);
    } else {
        printf("[INFO] File data transaksi retribusi baru dibuat.\n");
    }

   
    // 4. LOAD DATA MUTASI
    file = fopen("data/db_mutasi.dat", "rb");
    if (file != NULL) {
        fread(&jumlahMutasi, sizeof(int), 1, file);
        fread(dataMutasi, sizeof(Mutasi), jumlahMutasi, file);
        fclose(file);
    } else {
        printf("[INFO] File data mutasi baru dibuat.\n");
    }

}

// --- FUNGSI SAVE (TULIS FILE) ---
void simpanData() {
    FILE *file;

    // 1. SIMPAN DATA WARGA
    file = fopen("data/db_warga.dat", "wb"); // wb = Write Binary
    if (file != NULL) {
        fwrite(&jumlahWarga, sizeof(int), 1, file); // Simpan jumlahnya
        fwrite(dataWarga, sizeof(Penduduk), jumlahWarga, file); // Simpan datanya
        fclose(file);
    }

    // 2. SIMPAN DATA SURAT
    file = fopen("data/db_surat.dat", "wb");
    if (file != NULL) {
        fwrite(&jumlahSurat, sizeof(int), 1, file);
        fwrite(dataSurat, sizeof(RiwayatSurat), jumlahSurat, file);
        fclose(file);
    }

    // 3. SIMPAN DATA KEUANGAN
    file = fopen("data/db_keuangan.dat", "wb");
    if (file != NULL) {
        fwrite(&jumlahTransaksi, sizeof(int), 1, file);
        fwrite(dataTransaksi, sizeof(Transaksi), jumlahTransaksi, file);
        fclose(file);
    }

    // 4. SIMPAN DATA MUTASI
    file = fopen("data/db_mutasi.dat", "wb");
    if (file != NULL) {
        fwrite(&jumlahMutasi, sizeof(int), 1, file);
        fwrite(dataMutasi, sizeof(Mutasi), jumlahMutasi, file);
        fclose(file);
    }

    printf("\n[SUKSES] Semua data berhasil disimpan ke file!\n");
}
