#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/mutasi.h"

// akses data warga untuk mengubah status
extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;
// akses data mutasi untuk mencatat log mutasi
extern Mutasi dataMutasi[MAX_MUTASI];
extern int jumlahMutasi;

/* =====================================================
   PINDAH DATANG (WARGA MASUK)
   - Tambah data warga baru
   - Status otomatis "Aktif"
   - Catat ke log mutasi sebagai "Masuk"
   ===================================================== */

void pindahDatang() { // Warga masuk (tambah warga + log mutasi)
    // TODO: Tugas
    // Ini mirip tambahWarga(), tapi catat juga ke dataMutasi sebagai "Masuk"
    Penduduk p;
    Mutasi m;

    //input data warga
    printf ("tanggal pindah datang (dd-mm-yy): ");
    scanf ("%d-%d-%d", &m.tglKejadian.hari, &m.tglKejadian.bulan, &m.tglKejadian.tahun);
    
    printf("masukan NIK : ");
    scanf ("%s", m.nikTerkait);

    printf("masukan nama : ");
    scanf (" %[^\n]", p.namaLengkap);

    // set status awal
    strcpy (p.statusWarga, "Aktif");
    //simpan ke array dataWarga
    dataWarga[jumlahWarga] = p;
    jumlahWarga++;  // jumlah warga bertambah

    //catat ke log mutasi
    strcpy (dataMutasi[jumlahMutasi].nikTerkait, m.nikTerkait);
    strcpy (dataMutasi[jumlahMutasi].jenisMutasi, "Pindah Datang");
    strcpy (dataMutasi[jumlahMutasi].alasan, "Warga pindah datang");
    
    jumlahMutasi++; // jumlah mutasi bertambah

    printf("\n warga baru berhasil ditmbahkan\n");
    jedaLayar();
}

void pindahKeluar() {
    // TODO: Tugas
    // 1. Cari NIK
    // 2. Ubah dataWarga[i].statusWarga jadi "Pindah"
    // 3. Catat alasan dan tujuan ke dataMutasi

    char nikTerkait[17];
    int ditemukan = 0;

    printf ("Masukan NIK : ");
    scanf ("%s", nikTerkait);

    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nikTerkait) == 0) {
            //ubah status warga
            strcpy (dataWarga[i].statusWarga, "Pindah");

            //catat ke log mutasi
            strcpy (dataMutasi[jumlahMutasi].nikTerkait, nikTerkait);
            strcpy (dataMutasi[jumlahMutasi].jenisMutasi, "Pindah Keluar");

            printf ("Alasan pindah : ");
            scanf (" %[^\n]", dataMutasi[jumlahMutasi].alasan);

            jumlahMutasi++; // tambah jumlah mutasi
            ditemukan = 1;  // tandai bahwa data ditemukan

            printf ("\n data pindah keluar berhasil dicatat\n");
            break; // keluar dari loop
        }
    }
// jika NIK tidak ditemukan
    if (ditemukan == 0) {
        printf ("NIK tidak ditemukan\n");
    }

    jedaLayar();
}

void laporKematian() {
    // TODO: Tugas
    // 1. Cari NIK
    // 2. Ubah dataWarga[i].statusWarga jadi "Meninggal"
    // 3. Catat tanggal kematian ke dataMutasi

    char nikTerkait[17];
    int ditemukan = 0;

    printf ("Masukan NIK : ");
    scanf ("%s", nikTerkait);

    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nikTerkait) == 0) {
            //ubah status warga
            strcpy (dataWarga[i].statusWarga, "Meninggal");

            //catat ke log mutasi
            strcpy (dataMutasi[jumlahMutasi].nikTerkait, nikTerkait);
            strcpy (dataMutasi[jumlahMutasi].jenisMutasi, "Kematian");

            printf ("Tanggal kematian (dd-mm-yy): ");
            scanf ("%d-%d-%d", &dataMutasi[jumlahMutasi].tglKejadian.hari,
                               &dataMutasi[jumlahMutasi].tglKejadian.bulan,
                               &dataMutasi[jumlahMutasi].tglKejadian.tahun);

            strcpy (dataMutasi[jumlahMutasi].alasan, "Warga meninggal dunia");

            jumlahMutasi++; // tambah jumlah mutasi
            ditemukan = 1;  // tandai bahwa data ditemukan

            printf ("\n data kematian berhasil dicatat\n");
            break; // keluar dari loop
        }
    }
    // jika NIK tidak ditemukan
    if (ditemukan == 0) {
        printf ("NIK tidak ditemukan\n");
    }

    jedaLayar();
}

void lihatLogMutasi() {
    // Tampilkan tabel mutasi

    printf ("\n=== LOG MUTASI ===\n");

        if (jumlahMutasi == 0) {
            printf ("Belum ada data mutasi.\n");
        } else {
            for (int i = 0; i < jumlahMutasi; i++) {
                printf ("%d. %s | %s | %02d-%02d-%d\n",
                    i + 1,
                    dataMutasi[i].nikTerkait,
                    dataMutasi[i].jenisMutasi,
                    dataMutasi[i].tglKejadian.hari,
                    dataMutasi[i].tglKejadian.bulan,
                    dataMutasi[i].tglKejadian.tahun
                );
                printf ("    Alasan: %s\n", dataMutasi[i].alasan);

            }
        }
        
    jedaLayar();
}

void menuMutasi() {
    int pilihan;
    do {
        bersihkanLayar();
        printf("=== MENU MUTASI PENDUDUK ===\n");
        printf("[1] Warga Pindah Datang (Masuk)\n");
        printf("[2] Warga Pindah Keluar\n");
        printf("[3] Lapor Kematian\n");
        printf("[4] Lihat Log Mutasi\n");
        printf("[0] Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1: pindahDatang(); break;
            case 2: pindahKeluar(); break;
            case 3: laporKematian(); break;
            case 4: lihatLogMutasi(); break;
            case 0: break;
            default: printf("Salah input!\n"); jedaLayar();
        }
    } while (pilihan != 0);
}
