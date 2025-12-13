#ifndef DATA_WARGA_H
#define DATA_WARGA_H

// untuk menavigasi menu
void menuDataWarga();

// menambah data warga
void tambahWarga();

void lihatDaftarWarga();      // Tampilan tabel (singkat)
void detailWarga(char* nik);  // Tampilan lengkap (detail satu orang)
void cariWarga();             // Fitur pencarian

// fungsi untuk mengubah data warga
void editWarga();

// fungsi untuk menghapus data warga
void hapusWarga();

// 6. Helper / Validasi (Fungsi pembantu)
// Mengembalikan 1 jika NIK ada, 0 jika belum ada
int cekNIKTerdaftar(char* nikCek);

#endif 
