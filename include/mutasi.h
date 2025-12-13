#ifndef MUTASI_H
#define MUTASI_H

#include "structs.h"

void menuMutasi();
void pindahDatang();  // Warga masuk (tambah warga + log mutasi)
void pindahKeluar();  // Warga keluar (ubah status jadi "Pindah" + log)
void laporKematian(); // Warga meninggal (ubah status jadi "Meninggal" + log)
void lihatLogMutasi();

#endif
