#include <stdio.h>

struct mahasiswa {
  char nim[8];
  char nama[30];
};

int main() {
  FILE* data;

  data = fopen("data.csv", "w");

  struct mahasiswa bayu = {"2508391", "Bayu Gatra Hermawan"};

  fprintf(data, "%s,%s\n", bayu.nim, bayu.nama);

  printf("Success\n");

  fclose(data);

  return 0;
}
