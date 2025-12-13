#ifndef STRUCTS_H
#define STRUCTS_H

// batas maksimal data
#define MAX_WARGA 1000 // bisa simpan maksimal 1000 penduduk
#define MAX_SURAT 500 // bisa simpan maksimal 500 surat
#define MAX_TRANSAKSI 2000 // bisa simpan maksimal 2000 pembayaran
#define MAX_MUTASI 100 // bisa simpan maksimal 100 data mutasi
                       
// membuat tipe data Tanggal menggunakan struct
typedef struct {
  int hari;
  int bulan;
  int tahun;
} Tanggal;

// struct Penduduk
typedef struct {
  char nik[16];            // Primary Key 
  char namaLengkap[100];
  char tempatLahir[50];
  Tanggal tglLahir;        // Menggunakan struct Tanggal di atas
  char jenisKelamin[20];   // "Laki-laki" atau "Perempuan"
  char alamat[255];
  int rt;
  int rw;
  char agama[20];
  char statusPerkawinan[20];    // "Kawin", "Belum Kawin", "Cerai"
  char pekerjaan[50];
  char statusWarga[20];
} Penduduk;

// struct layanan surat
typedef struct {
    char kodeSurat[20];      // primary key 
    char nikPemohon[17];     // foreign key 
    char jenisSurat[50];     // "Surat Pengantar", "SKCK", dll
    char keperluan[100];     
    Tanggal tglDibuat;       
    char namaPetugas[50];    // Admin yang melayani
} RiwayatSurat;

// struct transaksi retribusi
typedef struct {
    char kodeTransaksi[20];  // primary key 
    char nikPembayar[17];    // foreign key 
    char jenisRetribusi[50]; // "Uang Kebersihan", "Keamanan"
    long nominal;       
    int periodeBulan;        // bayar untuk bulan ke (1-12)
    int periodeTahun;        
    Tanggal tglBayar;        
    char status[20];         // "Lunas" / "Belum bayar"
} Transaksi;

// struct data mutasi
typedef struct {
    char kodeMutasi[20]; // primary key
    char nikTerkait[17]; // foreign key
    char jenisMutasi[30];    // "Pindah Datang", "Pindah Keluar", "Kematian"
    Tanggal tglKejadian;
    char alasan[100];        
    char alamatBaru[255];    // Diisi jika pindah keluar
} Mutasi;

#endif
