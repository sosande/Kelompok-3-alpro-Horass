#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/layanan_surat.h"

extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;
extern RiwayatSurat dataSurat[MAX_SURAT];
extern int jumlahSurat;

int cariDataPemohon(char* nik) {
    // TODO: Tugas
    // 1. Loop array dataWarga
    // 2. Cek apakah nik == dataWarga[i].nik
    // 3. Return index 'i' kalau ketemu
  
    for (int i = 0; i < jumlahWarga; i++) {
      if (strcmp(nik, dataWarga[i].nik) == 0) {
        return i;
      }
    }
    
    return -1; // Default gak ketemu
}

void cetakSurat(int indexWarga, char* jenisSurat, char* keperluan) {
    // TODO: Tugas
    // 1. Buat nama file unik (misal: "Surat_[NIK].txt")
    // 2. fopen file mode "w"
    // 3. fprintf data warga (Nama, TTL, dll) ke dalam file
    // 4. fprintf keperluan surat
    // 5. fclose
    // 6. Simpan data log ke array dataSurat (untuk history)
    
    printf("\n[DEV] Simulasi cetak surat %s untuk %s...\n", jenisSurat, dataWarga[indexWarga].namaLengkap);
}

void buatSuratBaru() {
    char nik[17] = "";
    char jenisSurat[50] = "";
    char keperluan[100] = "";
    int indexWarga = 0;

    bersihkanLayar();

    printf("=== LAYANAN BUAT SURAT BARU ===\n");
    
    printf("Masukkan NIK Pemohon: ");
    scanf("%s", nik);

    indexWarga = cariDataPemohon(nik);

    if (indexWarga == -1) {
        printf("\n[KESALAHAN] Data warga dengan NIK %s tidak ditemukan!\n", nik);
    } else {
        printf("\n[INFO] Data Warga Ditemukan:\n");
        printf("Nama Lengkap : %s\n", dataWarga[indexWarga].namaLengkap);
        printf("Pekerjaan    : %s\n", dataWarga[indexWarga].pekerjaan);
        printf("----------------------------------------\n"); 

        // Input 2
        printf("Jenis Surat  : ");
        scanf(" %[^\n]", jenisSurat);

        // Input 3
        printf("Keperluan    : ");
        scanf(" %[^\n]", keperluan);

        // Eksekusi
        cetakSurat(indexWarga, jenisSurat, keperluan);
    }
    
    jedaLayar();
}

void lihatRiwayatSurat() {
    // TODO: Tugas
    // 1. Loop array dataSurat
    // 2. Tampilkan siapa saja yang pernah bikin surat
    
    printf("\n[DEV] Fitur History Surat belum diisi.\n");
    jedaLayar();
}

void menuLayananSurat() {
    int pilihan;
    do {
        bersihkanLayar();
        printf("=== LAYANAN PERSURATAN ===\n");
        printf("[1] Buat Surat Baru\n");
        printf("[2] Lihat Riwayat Surat\n");
        printf("[0] Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1: buatSuratBaru(); break;
            case 2: lihatRiwayatSurat(); break;
            case 0: break;
            default: printf("Salah input!\n"); jedaLayar();
        }
    } while (pilihan != 0);
}
