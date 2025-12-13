#ifndef LAYANAN_SURAT_H
#define LAYANAN_SURAT_H

#include "structs.h"

// Menu navigasi 
void menuLayananSurat();

// Buat Surat
void buatSuratBaru();

// mencari data pemohon berdasarkan nik 
int cariDataPemohon(char* nik);

// generate surat menjadi file txt 
void cetakSurat(int indexWarga, char* jenisSurat, char* keperluan);

// Fitur Lihat History
void lihatRiwayatSurat();

#endif
