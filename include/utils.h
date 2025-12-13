#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

// Fungsi untuk membersihkan layar
static void bersihkanLayar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi untuk menjeda layar
static void jedaLayar() {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar(); getchar(); 
}

#endif 
