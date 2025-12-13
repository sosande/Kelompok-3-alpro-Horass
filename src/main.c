#include <stdio.h>
#include "../include/structs.h"
#include "../include/file_handler.h"

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
  muatData();

  return 0;
}
