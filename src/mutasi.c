#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h"
#include "../include/mutasi.h"

extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;
<<<<<<< HEAD

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


=======
extern Mutasi dataMutasi[MAX_MUTASI];
extern int jumlahMutasi;

// Helper: Cek apakah NIK sudah dipakai
int cekNIKDuplikat(char* nik) {
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nik) == 0) return 1;
    }
    return 0;
}

void pindahDatang() { 
>>>>>>> 4a70f8bd87389a3631b2bf10e0e06bf0de0808e5
    Penduduk p;
    Mutasi m;

    bersihkanLayar();
    printf("=== INPUT WARGA PINDAH DATANG ===\n");

    // 1. DATA MUTASI
    printf("Tanggal Pindah (DD MM YYYY): ");
    scanf("%d %d %d", &m.tglKejadian.hari, &m.tglKejadian.bulan, &m.tglKejadian.tahun);
    
<<<<<<< HEAD
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
=======
    // 2. DATA WARGA
    printf("Masukan NIK : ");
    scanf("%s", p.nik);

    // Validasi 16 Digit
    if (strlen(p.nik) != 16) {
        printf("[KESALAHAN] NIK harus 16 digit!\n");
        jedaLayar();
        return;
    }

    // Validasi Duplikat 
    if (cekNIKDuplikat(p.nik)) {
        printf("[KESALAHAN] NIK sudah terdaftar!\n");
        jedaLayar();
        return;
    }

    printf("Masukan Nama : ");
    scanf(" %[^\n]", p.namaLengkap);

    printf("Tempat Lahir : ");
    scanf(" %[^\n]", p.tempatLahir);

    printf("Tanggal Lahir (DD MM YYYY) : ");
    scanf("%d %d %d", &p.tglLahir.hari, &p.tglLahir.bulan, &p.tglLahir.tahun);

    printf("Jenis Kelamin (L/P) : ");
    scanf("%s", p.jenisKelamin);

    printf("Alamat : ");
    scanf(" %[^\n]", p.alamat);

    printf("RT / RW : ");
    scanf("%d / %d", &p.rt, &p.rw);

    printf("Agama : ");
    scanf(" %[^\n]", p.agama);

    printf("Pekerjaan : ");
    scanf(" %[^\n]", p.pekerjaan);

    printf("Status Kawin : ");
    scanf(" %[^\n]", p.statusPerkawinan);

    // Set status default
    strcpy(p.statusWarga, "Aktif");

    // Simpan ke Array Warga
    dataWarga[jumlahWarga] = p;
    jumlahWarga++;

    // Simpan ke Log Mutasi
    strcpy(dataMutasi[jumlahMutasi].nikTerkait, p.nik);
    strcpy(dataMutasi[jumlahMutasi].jenisMutasi, "Pindah Datang");
    strcpy(dataMutasi[jumlahMutasi].alasan, "Warga Pindah Datang");
    dataMutasi[jumlahMutasi].tglKejadian = m.tglKejadian;
    
    jumlahMutasi++;
>>>>>>> 4a70f8bd87389a3631b2bf10e0e06bf0de0808e5

    printf("\n[SUKSES] Warga baru berhasil ditambahkan.\n");
    jedaLayar();
}

void pindahKeluar() {
<<<<<<< HEAD
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

=======
>>>>>>> 4a70f8bd87389a3631b2bf10e0e06bf0de0808e5
    char nikTerkait[17];
    int index = -1;

    bersihkanLayar();
    printf("=== INPUT PINDAH KELUAR ===\n");
    printf("Masukan NIK : ");
    scanf("%s", nikTerkait);

    // Cari NIK
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nikTerkait) == 0) {
<<<<<<< HEAD
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
=======
            index = i;
            break;
>>>>>>> 4a70f8bd87389a3631b2bf10e0e06bf0de0808e5
        }
    }

    if (index == -1) {
        printf("[KESALAHAN] NIK tidak ditemukan.\n");
    } else {
        // Tampilkan nama biar yakin
        printf("Ditemukan: %s\n", dataWarga[index].namaLengkap);
        
        // Update Status Warga
        strcpy(dataWarga[index].statusWarga, "Pindah");

        // Catat Log Mutasi
        strcpy(dataMutasi[jumlahMutasi].nikTerkait, nikTerkait);
        strcpy(dataMutasi[jumlahMutasi].jenisMutasi, "Pindah Keluar");

        printf("Tanggal Pindah (DD MM YYYY) : ");
        scanf("%d %d %d", &dataMutasi[jumlahMutasi].tglKejadian.hari, &dataMutasi[jumlahMutasi].tglKejadian.bulan, &dataMutasi[jumlahMutasi].tglKejadian.tahun);

        printf("Alasan pindah : ");
        scanf(" %[^\n]", dataMutasi[jumlahMutasi].alasan);

        jumlahMutasi++;
        printf("\n[SUKSES] Data pindah keluar berhasil dicatat.\n");
    }

    jedaLayar();
}

void laporKematian() {
<<<<<<< HEAD
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

=======
>>>>>>> 4a70f8bd87389a3631b2bf10e0e06bf0de0808e5
    char nikTerkait[17];
    int index = -1;

    bersihkanLayar();
    printf("=== LAPOR KEMATIAN ===\n");
    printf("Masukan NIK : ");
    scanf("%s", nikTerkait);

    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nikTerkait) == 0) {
<<<<<<< HEAD
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
=======
            index = i;
            break;
>>>>>>> 4a70f8bd87389a3631b2bf10e0e06bf0de0808e5
        }
    }

    if (index == -1) {
        printf("[KESALAHAN] NIK tidak ditemukan.\n");
    } else {
        printf("Ditemukan: %s\n", dataWarga[index].namaLengkap);

        // Update Status
        strcpy(dataWarga[index].statusWarga, "Meninggal");

        // Catat Log
        strcpy(dataMutasi[jumlahMutasi].nikTerkait, nikTerkait);
        strcpy(dataMutasi[jumlahMutasi].jenisMutasi, "Kematian");
        strcpy(dataMutasi[jumlahMutasi].alasan, "Meninggal Dunia");

        printf("Tanggal Kematian (DD MM YYYY): ");
        scanf("%d %d %d", &dataMutasi[jumlahMutasi].tglKejadian.hari,
                          &dataMutasi[jumlahMutasi].tglKejadian.bulan,
                          &dataMutasi[jumlahMutasi].tglKejadian.tahun);

        jumlahMutasi++;
        printf("\n[SUKSES] Data kematian berhasil dicatat.\n");
    }

    jedaLayar();
}

void lihatLogMutasi() {
<<<<<<< HEAD
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
=======
    bersihkanLayar();
    printf("=== LOG MUTASI ===\n");

    if (jumlahMutasi == 0) {
        printf("Belum ada data mutasi.\n");
    } else {
        // Header simpel
        printf("%-3s | %-16s | %-15s | %-12s | %s\n", "NO", "NIK", "JENIS", "TANGGAL", "ALASAN");
        printf("----------------------------------------------------------------------\n");
>>>>>>> 4a70f8bd87389a3631b2bf10e0e06bf0de0808e5
        
        for (int i = 0; i < jumlahMutasi; i++) {
            printf("%-3d | %-16s | %-15s | %02d-%02d-%04d | %s\n",
                i + 1,
                dataMutasi[i].nikTerkait,
                dataMutasi[i].jenisMutasi,
                dataMutasi[i].tglKejadian.hari,
                dataMutasi[i].tglKejadian.bulan,
                dataMutasi[i].tglKejadian.tahun,
                dataMutasi[i].alasan
            );
        }
    }
    jedaLayar();
}

void menuMutasi() {
    int pilihan;
    do {
        bersihkanLayar();
        printf("=== MENU MUTASI PENDUDUK ===\n");
        printf("[1] Warga Pindah Datang\n");
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
