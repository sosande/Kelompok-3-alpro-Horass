#include <stdio.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/utils.h" 
#include "../include/data_warga.h"

// ambil data variable dari file main.c 
extern Penduduk dataWarga[MAX_WARGA];
extern int jumlahWarga;

// void tambahWarga() {
//     // TODO: Tugas 
//     // 1. Cek apakah database penuh?
//     // 2. Input NIK, Nama, dll.
//     // 3. Validasi NIK (panggil fungsi cekNIKTerdaftar)
//     // 4. Simpan ke array dataWarga
//
//     printf("\n[DEV] Fitur Tambah Warga belum diisi logikanya.\n");
//     jedaLayar();
// }

void lihatDaftarWarga() {
    // TODO: Tugas
    // 1. Loop dari 0 sampai jumlahWarga
    // 2. Printf data dalam bentuk tabel rapi
    
    printf("\n[DEV] Fitur Lihat Daftar belum diisi logikanya.\n");
    jedaLayar();
}

void detailWarga(char* nik) {
    // TODO: Tugas
    // 1. Cari index warga berdasarkan NIK
    // 2. Kalau ketemu, print semua data (TTL, Agama, Status, dll)
    // 3. Kalau tidak ketemu, print Error
}

void cariWarga() {
    // TODO: Tugas
    // 1. Minta input NIK atau Nama
    // 2. Panggil fungsi detailWarga() jika ketemu
    char input[100];
    int index = -1;

    printf("Masukkan NIK atau Nama Warga: ");
    scanf("%s", input);

    for (int i = 0; i < jumlahWarga; i++) {
        if (strcmp(dataWarga[i].nik, input) == 0 || strcmp(dataWarga[i].namaLengkap, input) == 0) {
            index = i;
            break;
        }
    }

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
    // 2. Cari index-nya
    // 3. Tawarkan mau edit kolom apa (Nama/Alamat/Status)
    // 4. Update data di array
    
    printf("\n[DEV] Fitur Edit Warga belum diisi logikanya.\n");
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
            printf("\n[SUKSES] Data atas nama %s telah dihapus permanen.\n", dataWarga[i].nama);
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
