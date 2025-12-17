#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h" 
#include "../include/data_warga.h"

// ambil data variable dari file main.c 
extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;

void tambahWarga() {
    // TODO: Tugas 
    // 1. Cek apakah database penuh?
    // 2. Input NIK, Nama, dll.
    // 3. Validasi NIK (panggil fungsi cekNIKTerdaftar)
    // 4. Simpan ke array dataWarga

    printf("\n[DEV] Fitur Tambah Warga belum diisi logikanya.\n");
    jedaLayar();
}

void lihatDaftarWarga() {
    bersihkanLayar();
    printf("=== DAFTAR DATA WARGA ===\n");

    if (jumlahWarga == 0) {
        printf("[INFO] Belum ada data warga.\n");
        jedaLayar();
        return;
    }

    printf("----------------------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-16s | %-20s | %-12s | %-15s | %-10s |\n",
           "No", "NIK", "Nama", "Kelamin", "Pekerjaan", "Status");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahWarga; i++) {
        printf("| %-3d | %-16s | %-20s | %-12s | %-15s | %-10s |\n",
               i + 1,
               dataWarga[i].nik,
               dataWarga[i].namaLengkap,
               dataWarga[i].jenisKelamin,
               dataWarga[i].pekerjaan,
               dataWarga[i].statusWarga);
    }

    printf("----------------------------------------------------------------------------------------------------\n");
    printf("Total Warga: %d orang\n", jumlahWarga);

    jedaLayar();
}

void detailWarga(char* nik) {
    // TODO: Tugas
    // Cari index warga berdasarkan NIK
    int index = -1;
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nik) == 0) {
            index = i;
            break;
        }
    }
    // Kalau ketemu, print semua data (TTL, Agama, Status, dll)
    if (index != -1) {
        Penduduk p = dataWarga[index];
        printf("\n=== DETAIL WARGA ===\n");
        printf("NIK              : %s\n", p.nik);
        printf("Nama Lengkap     : %s\n", p.namaLengkap);
        printf("Tempat, Tgl Lahir: %s, %02d-%02d-%04d\n", p.tempatLahir, p.tglLahir.hari, p.tglLahir.bulan, p.tglLahir.tahun);
        printf("Jenis Kelamin    : %s\n", p.jenisKelamin);
        printf("Alamat           : %s\n", p.alamat);
        printf("RT/RW            : %d/%d\n", p.rt, p.rw);
        printf("Agama            : %s\n", p.agama);
        printf("Status Perkawinan: %s\n", p.statusPerkawinan);
        printf("Pekerjaan        : %s\n", p.pekerjaan);
        printf("Status Warga     : %s\n", p.statusWarga);
    } else {
        // Kalau tidak ketemu, print Error
        printf("[KESALAHAN] Data warga dengan NIK '%s' tidak ditemukan.\n", nik);
    }

    jedaLayar();
}

void cariWarga() {
    // TODO: Tugas

    char input[100];
    int index = -1;
    // minta input NIK atau Nama
    printf("Masukkan NIK atau Nama Warga: ");
    scanf("%s", input);
    // cari data warga dengan nik atau nama
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, input) == 0 || strcmp(dataWarga[i].namaLengkap, input) == 0) {
            index = i;
            break;
        }
    }
    // tampilkan detail warga jika ditemukan
    if (index != -1) {
        detailWarga(dataWarga[index].nik);
    } else {
        printf("[KESALAHAN] Data warga tidak ditemukan.\n");
        jedaLayar();
    }
}

void editWarga() {
    // TODO: Tugas
    // 1. Minta input NIK yang mau diedit
    char nik[17] = "";
    printf("Masukkan NIK yang ingin diedit: ");
    scanf("%s", nik);
    
    // 2. Cari index-nya
    int index = -1;
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nik) == 0) {
            index = i;
            break;
        }
    }
    // 3. Tawarkan mau edit kolom apa (Nama/Alamat/Status)
    if (index == -1) {
        printf("[KESALAHAN] NIK '%s' tidak ditemukan dalam database.\n", nik);
        jedaLayar();
        return;
    }
    printf("\nData Ditemukan:\n");
    printf("----------------------------------------\n");
    printf("Nama Lengkap : %s\n", dataWarga[index].namaLengkap);
    printf("Alamat       : %s\n", dataWarga[index].alamat);
    printf("Status Saat Ini: %s\n", dataWarga[index].statusWarga);
    printf("----------------------------------------\n");
    printf("\nPilih kolom yang ingin diedit:\n");
    printf("[1] Nama Lengkap\n");
    printf("[2] Alamat\n");
    printf("[3] Status Warga\n");
    printf("Pilihan: ");
    int pilihan;
    scanf("%d", &pilihan);
    char buffer[100];
    switch (pilihan) {
        case 1:
            printf("Masukkan Nama Lengkap baru: ");
            scanf(" %[^\n]", buffer);
            // strcpy(dataWarga[index].namaLengkap, buffer);
            break;
        case 2:
            printf("Masukkan Alamat baru: ");
            scanf(" %[^\n]", buffer);
            // strcpy(dataWarga[index].alamat, buffer);
            break;
        case 3:
            printf("Masukkan Status Warga baru: ");
            scanf(" %[^\n]", buffer);
            // strcpy(dataWarga[index].statusWarga, buffer);
            break;
        default:
            printf("[KESALAHAN] Pilihan tidak valid.\n");
            jedaLayar();
            return;
    }

    // 4. Update data di array

    switch (pilihan) {
        case 1:
            strcpy(dataWarga[index].namaLengkap, buffer);
            break;
        case 2:
            strcpy(dataWarga[index].alamat, buffer);
            break;
        case 3:
            strcpy(dataWarga[index].statusWarga, buffer);
            break;
    }
    printf("\n[SUKSES] Data warga telah diperbarui.\n");
    jedaLayar();
}

void hapusWarga() {
    char nik[17] = "";
    char konfirmasi = 'N'; 
    int index = -1; 

    bersihkanLayar();
    printf("=== HAPUS DATA WARGA ===\n");
    printf("Masukkan NIK Target: ");
    scanf("%s", nik);

    // cari data warga dengan nik 
    for (int i = 0; i < jumlahWarga; i++) {
        // cek apakah niknya terdaftar atau tidak
        if (strcmp(nik, dataWarga[i].nik) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("[KESALAHAN] NIK '%s' tidak ditemukan dalam database.\n", nik);
    } else {
        printf("\n[INFO] Data Ditemukan:\n");
        
        // menampilkan detail warga
        printf("----------------------------------------\n");
        printf("Nama Lengkap : %s\n", dataWarga[index].namaLengkap);
        printf("Alamat       : %s\n", dataWarga[index].alamat);
        printf("Status Saat Ini: %s\n", dataWarga[index].statusWarga);
        printf("----------------------------------------\n");
        
        printf("\n[PERINGATAN] Data yang dihapus tidak dapat dikembalikan.\n");
        printf("Apakah Anda YAKIN ingin menghapus warga ini? (Y/N): ");
        
        scanf(" %c", &konfirmasi); 

        // cek apakah user yakin ingin menghapus data warga tersebut
        if (konfirmasi == 'Y' || konfirmasi == 'y') {
            // Data index ke-i ditimpa oleh data index ke-i+1
            for (int i = index; i < jumlahWarga - 1; i++) {
                dataWarga[i] = dataWarga[i + 1];
            }

            jumlahWarga--; // Kurangi total warga
            printf("\n[SUKSES] Data atas nama %s telah dihapus permanen.\n", dataWarga[index].namaLengkap);
        } else {
            printf("\n[INFO] Penghapusan dibatalkan.\n");
        }
    }

    jedaLayar();
}

int cekNIKTerdaftar(char* nikCek) {
    // untuk mengecek apakah nik sudah terdaftar atau belum
    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, nikCek) == 0) {
            return 1; // Ada
        }
    }
    return 0; // Tidak ada
}

void menuDataWarga() {
  int pilihan;

  do {
    bersihkanLayar();

    printf("=== MENU KELOLA DATA WARGA ===\n");
    printf("[1] Tambah Warga Baru\n");
    printf("[2] Lihat Daftar Warga\n");
    printf("[3] Cari & Detail Warga\n");
    printf("[4] Edit Data Warga\n");
    printf("[5] Hapus Warga\n");
    printf("[0] Kembali ke Menu Utama\n");   
    printf("------------------------------\n");
    printf("Pilihan: ");

    scanf("%d", &pilihan);

    switch (pilihan) {
        case 1: tambahWarga(); break;
        case 2: lihatDaftarWarga(); break;
        case 3: cariWarga(); break;
        case 4: editWarga(); break;
        case 5: hapusWarga(); break;
        case 0: printf("Kembali ke menu utama...\n"); break;
        default: printf("Input salah!\n"); jedaLayar();       
    }
    } while (pilihan != 0);
}
