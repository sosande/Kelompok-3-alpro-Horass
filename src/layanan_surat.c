#include <stdio.h>
#include <string.h>
#include <time.h> // untuk generate tanggal saat ini
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/layanan_surat.h"

extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;
extern RiwayatSurat dataSurat[MAX_SURAT];
extern int jumlahSurat;

int cariDataPemohon(char* nik) {
    for (int i = 0; i < jumlahWarga; i++) {
      if (strcmp(nik, dataWarga[i].nik) == 0) {
        return i;
      }
    }
    
    return -1; // Default gak ketemu
}

void cetakSurat(int indexWarga, char* jenisSurat, char* keperluan) {
    FILE *fp;
    char namaFile[120];

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Nama file
    sprintf(namaFile, "output_surat/Surat_%s_%s.txt",
            dataWarga[indexWarga].nik, jenisSurat);

    fp = fopen(namaFile, "w");
    if (fp == NULL) {
        printf("\n[KESALAHAN] Gagal membuat file surat.\n");
        printf("Pastikan folder 'output_surat' sudah tersedia.\n");
        return;
    }

    /* ===================== ISI SURAT ===================== */
    fprintf(fp, "=====================================================================\n");
    fprintf(fp, "                     PEMERINTAH DESA NAGRI KALER                     \n");
    fprintf(fp, "=====================================================================\n\n");

    fprintf(fp, "                              SURAT KETERANGAN                      \n");
    fprintf(fp, "                           Jenis Surat : %s                          \n\n", jenisSurat);

    fprintf(fp, "Yang bertanda tangan di bawah ini menerangkan bahwa:\n\n");

    fprintf(fp, "Nama Lengkap     : %s\n", dataWarga[indexWarga].namaLengkap);
    fprintf(fp, "NIK              : %s\n", dataWarga[indexWarga].nik);
    fprintf(fp, "Tempat/Tgl Lahir : %s, %02d-%02d-%04d\n",
            dataWarga[indexWarga].tempatLahir,
            dataWarga[indexWarga].tglLahir.hari,
            dataWarga[indexWarga].tglLahir.bulan,
            dataWarga[indexWarga].tglLahir.tahun);
    fprintf(fp, "Alamat           : %s\n\n", dataWarga[indexWarga].alamat);

    fprintf(fp, "Adalah benar warga Desa Nagri Kaler.\n");
    fprintf(fp, "Surat keterangan ini dibuat untuk keperluan:\n\n");
    fprintf(fp, "    \"%s\"\n\n", keperluan);

    fprintf(fp, "Demikian surat keterangan ini dibuat agar dapat digunakan sebagaimana mestinya.\n\n");

    fprintf(fp, "Nagri Kaler, %02d-%02d-%04d\n\n",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);

    fprintf(fp, "Kepala Desa Nagri Kaler,\n\n\n");
    fprintf(fp, "( Agus Purwanto )\n");

    fclose(fp);

    /* ===================== SIMPAN RIWAYAT ===================== */
    sprintf(dataSurat[jumlahSurat].kodeSurat, "SRT-%03d", jumlahSurat + 1);
    sprintf(dataSurat[jumlahSurat].namaFile, "Surat_%s_%s.txt",
            dataWarga[indexWarga].nik, jenisSurat);

    strcpy(dataSurat[jumlahSurat].jenisSurat, jenisSurat);
    strcpy(dataSurat[jumlahSurat].nikPemohon, dataWarga[indexWarga].nik);
    strcpy(dataSurat[jumlahSurat].keperluan, keperluan);

    dataSurat[jumlahSurat].tglDibuat.hari  = t->tm_mday;
    dataSurat[jumlahSurat].tglDibuat.bulan = t->tm_mon + 1;
    dataSurat[jumlahSurat].tglDibuat.tahun = t->tm_year + 1900;

    jumlahSurat++;

    printf("\n[SUKSES] Surat \"%s\" berhasil dibuat.\n", jenisSurat);
    printf("[INFO] File disimpan sebagai: %s\n", namaFile);
}

void buatSuratBaru() {
    char nik[17] = "";
    char jenisSurat[50] = "";
    char keperluan[100] = "";
    int indexWarga;

    bersihkanLayar();
    printf("================================ LAYANAN BUAT SURAT BARU ================================\n");
    printf("Masukkan NIK Pemohon: ");
    scanf("%s", nik);
    printf("-----------------------------------------------------------------------------------------\n");

    indexWarga = cariDataPemohon(nik);

    if (indexWarga == -1) {
        printf("[KESALAHAN] Data warga dengan NIK '%s' tidak ditemukan.\n", nik);
        printf("=========================================================================================\n");
        jedaLayar();
        return;
    }

    // Preview data pemohon
    printf("DATA PEMOHON DITEMUKAN\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("NIK          : %-16s\n", dataWarga[indexWarga].nik);
    printf("Nama Lengkap : %-40s\n", dataWarga[indexWarga].namaLengkap);
    printf("Pekerjaan    : %-30s\n", dataWarga[indexWarga].pekerjaan);
    printf("-----------------------------------------------------------------------------------------\n");

    printf("Jenis Surat  : ");
    scanf(" %[^\n]", jenisSurat);

    printf("Keperluan    : ");
    scanf(" %[^\n]", keperluan);

    cetakSurat(indexWarga, jenisSurat, keperluan);

    printf("=========================================================================================\n");
    jedaLayar();
}
    
void lihatRiwayatSurat() {
    bersihkanLayar(); 

    // Header diperpanjang agar muat
    printf("=========================================================================================================\n");
    printf("                                          RIWAYAT SURAT KELUAR                                           \n");
    printf("=========================================================================================================\n");
    printf("Total Surat Dicetak: %d\n", jumlahSurat);
    
    // HEADER TABEL (Total Lebar sktr 105 karakter)
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-10s | %-16s | %-30s | %-30s |\n", "NO", "TANGGAL", "NIK PEMOHON", "JENIS SURAT", "NAMA FILE");
    printf("---------------------------------------------------------------------------------------------------------\n");

    if (jumlahSurat == 0) {
        // Lebar pesan kosong disesuaikan
        printf("| %-101s |\n", "       BELUM ADA DATA SURAT YANG DIBUAT");
    } else {
        // LOOPING DATA
        for (int i = 0; i < jumlahSurat; i++) {
            // Karena nama file ada path "output_surat/", kita bisa potong sedikit saat display kalau kepanjangan
            // Tapi untuk sekarang kita tampilkan full dulu
            printf("| %-3d | %02d-%02d-%04d | %-16s | %-30s | %-30s |\n",
                i + 1, 
                dataSurat[i].tglDibuat.hari, 
                dataSurat[i].tglDibuat.bulan,
                dataSurat[i].tglDibuat.tahun,
                dataSurat[i].nikPemohon,      
                dataSurat[i].jenisSurat,       
                dataSurat[i].namaFile // <--- Data Baru
            );
        }
    }

    printf("---------------------------------------------------------------------------------------------------------\n");
    jedaLayar();
}

void menuLayananSurat() {
    int pilihan;

    do {
        bersihkanLayar();
        printf("=================================== MENU LAYANAN PERSURATAN ================================\n");
        printf("[1] Buat Surat Baru\n");
        printf("[2] Lihat Riwayat Surat\n");
        printf("[0] Kembali ke Menu Utama\n");
        printf("------------------------------------------------------------------------------------------------\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: buatSuratBaru(); break;
            case 2: lihatRiwayatSurat(); break;
            case 0:
                printf("\n[INFO] Kembali ke menu utama...\n");
                jedaLayar();
                break;
            default:
                printf("\n[KESALAHAN] Pilihan menu tidak valid.\n");
                jedaLayar();
        }
    } while (pilihan != 0);
}

