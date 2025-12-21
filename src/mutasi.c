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


void pindahDatang() { 
    // TODO:
    // Ini mirip tambahWarga(), tapi catat juga ke dataMutasi sebagai "Masuk"
   
    // cek apakah masih ada slot untuk warga baru
    if (jumlahWarga >= MAX_WARGA) {
        printf ("Data warga sudah penuh, tidak bisa tambah warga baru.\n");
        jedaLayar();
        return;
    }
    
    // cek apakah masih ada slot untuk mutasi baru
    if (jumlahMutasi >= MAX_MUTASI) {
        printf ("Data mutasi sudah penuh, tidak bisa catat mutasi baru.\n");
        jedaLayar();
        return;
    }


    Penduduk p;
    Mutasi m;

    //input data warga
    printf ("tanggal pindah datang (dd-mm-yy): ");
    scanf ("%d-%d-%d", &m.tglKejadian.hari, &m.tglKejadian.bulan, &m.tglKejadian.tahun);
    
    printf("masukan NIK : ");
    scanf ("%s", p.nik);

    printf("masukan nama lengkap: ");
    scanf (" %[^\n]", p.namaLengkap);

    printf("masukan tempat lahir: ");
    scanf (" %[^\n]", p.tempatLahir);

    printf("masukan tanggal lahir (dd-mm-yy): ");
    scanf ("%d-%d-%d", &p.tglLahir.hari, &p.tglLahir.bulan, &p.tglLahir.tahun);

    printf("masukan jenis kelamin: ");
    scanf (" %[^\n]", p.jenisKelamin);

    printf("masukan alamat: ");
    scanf (" %[^\n]", p.alamat);

    printf("masukan RT: ");
    scanf ("%d", &p.rt);

    printf("masukan RW: ");
    scanf ("%d", &p.rw);

    printf("masukan agama: ");
    scanf (" %[^\n]", p.agama);

    printf("masukan status perkawinan: ");
    scanf (" %[^\n]", p.statusPerkawinan);

    printf("masukan pekerjaan: ");
    scanf (" %[^\n]", p.pekerjaan);
    
    // set status awal
    strcpy (p.statusWarga, "Aktif");

    //simpan ke array dataWarga
    dataWarga[jumlahWarga] = p;

    jumlahWarga++;  // jumlah warga nya bertambah

    //catat ke log mutasi
    sprintf (m.kodeMutasi, "M%03d", jumlahMutasi + 1); // buat kode mutasinya
    strcpy (m.nikTerkait, p.nik);
    strcpy(m.jenisMutasi, "Pindah Datang");
    strcpy(m.alasan, "Warga pindah datang");

    dataMutasi[jumlahMutasi] = m;
    jumlahMutasi++; // jumlah mutasi nya bertambah

    printf("\n warga baru berhasil ditmbahkan\n");
    jedaLayar();
}

void pindahKeluar() {
    // TODO: 
    // 1. Cari NIK
    // 2. Ubah dataWarga[i].statusWarga jadi "Pindah"
    // 3. Catat alasan dan tujuan ke dataMutasi

    // cek apakah masih ada slot untuk mutasi baru
    if (jumlahMutasi >= MAX_MUTASI) {
        printf ("Data mutasi sudah penuh, tidak bisa catat mutasi baru.\n");
        jedaLayar();
        return;
    }

    char nikTerkait[17];
    int ditemukan = 0;

    printf ("Masukan NIK : ");
    scanf ("%s", nikTerkait);

    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nikTerkait) == 0) {
            //ubah status warga
            strcpy (dataWarga[i].statusWarga, "Pindah");

            //catat ke log mutasi
            sprintf (dataMutasi[jumlahMutasi].kodeMutasi, "M%03d", jumlahMutasi + 1); // buat kode mutasinya
            strcpy (dataMutasi[jumlahMutasi].nikTerkait, nikTerkait);
            strcpy (dataMutasi[jumlahMutasi].jenisMutasi, "Pindah Keluar");

            printf ("Tanggal pindah keluar (dd-mm-yy): ");
            scanf ("%d-%d-%d", &dataMutasi[jumlahMutasi].tglKejadian.hari, &dataMutasi[jumlahMutasi].tglKejadian.bulan, &dataMutasi[jumlahMutasi].tglKejadian.tahun);

            printf ("Alasan pindah : ");
            scanf (" %[^\n]", dataMutasi[jumlahMutasi].alasan);

            printf ("Alamat baru : ");
            scanf (" %[^\n]", dataMutasi[jumlahMutasi].alamatBaru);

            jumlahMutasi++; // bertambah jumlah mutasinya
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
    // TODO:
    // 1. Cari NIK
    // 2. Ubah dataWarga[i].statusWarga jadi "Meninggal"
    // 3. Catat tanggal kematian ke dataMutasi

    // cek apakah masih ada slot untuk mutasi baru
    if (jumlahMutasi >= MAX_MUTASI) {
        printf ("Data mutasi sudah penuh, tidak bisa catat mutasi baru.\n");
        jedaLayar();
        return;
    }

    char nikTerkait[17];
    int ditemukan = 0;

    printf ("Masukan NIK : ");
    scanf ("%s", nikTerkait);

    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nikTerkait) == 0) {
            //ubah status warga
            strcpy (dataWarga[i].statusWarga, "Meninggal");

            //catat ke log mutasi
            sprintf (dataMutasi[jumlahMutasi].kodeMutasi, "M%03d", jumlahMutasi + 1); // buat kode mutasinya
            strcpy (dataMutasi[jumlahMutasi].nikTerkait, nikTerkait);
            strcpy (dataMutasi[jumlahMutasi].jenisMutasi, "Kematian");

            printf ("Tanggal kematian (dd-mm-yy): ");
            scanf ("%d-%d-%d", &dataMutasi[jumlahMutasi].tglKejadian.hari, &dataMutasi[jumlahMutasi].tglKejadian.bulan, &dataMutasi[jumlahMutasi].tglKejadian.tahun);

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
    // Tampilkan riwayat mutasi
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
                if (strcmp(dataMutasi[i].jenisMutasi, "Pindah Keluar") == 0) {
                    printf ("    Alamat Baru: %s\n", dataMutasi[i].alamatBaru);

                }
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
