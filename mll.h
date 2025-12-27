#ifndef MLL_T_H_INCLUDED
#define MLL_T_H_INCLUDED

#include <iostream>
using namespace std;

typedef struct elmKategori *adrKategori;
typedef struct elmProduk *adrProduk;
typedef struct elmRelasi *adrRelasi;

struct Kategori {
    string nama;
};

struct Produk {
    string nama;
    int harga;
};

struct elmKategori {
    Kategori info;
    adrKategori next;
    adrKategori prev;
};

struct elmProduk {
    Produk info;
    adrProduk next;
    adrProduk prev;
};

struct elmRelasi {
    adrRelasi next;
    adrKategori nextKategori;
    adrProduk nextProduk;
};

struct ListKategori {
    adrKategori first;
    adrKategori last;
};

struct ListProduk {
    adrProduk first;
    adrProduk last;
};

struct ListRelasi {
    adrRelasi first;
};

void createListKategori(ListKategori &L);
void createListProduk(ListProduk &L);
void createListRelasi(ListRelasi &L);
bool isEmptyKategori(ListKategori L);
adrKategori createElmKategori(string nama);
adrProduk createElmProduk(string nama, int harga);
adrRelasi createElmRelasi(adrKategori K, adrProduk P);
void insertKategori(ListKategori &L, adrKategori p);
void insertProduk(ListProduk &L, adrProduk p);
void insertRelasi(ListRelasi &L, adrRelasi p);
adrKategori searchKategori(ListKategori L, string nama);
adrProduk searchProduk(ListProduk L, string nama);
adrRelasi searchRelasi(ListRelasi L, adrKategori K, adrProduk P);
void addRelasi(ListRelasi &LR, ListKategori LK, ListProduk LP, string namaProduk, string namaKategori);
void showData(ListKategori LK, ListProduk LP, ListRelasi LR);
void deleteKategori(ListKategori &LK, ListRelasi &LR, string namaKategori);
void deleteProduk(ListProduk &LP, ListRelasi &LR, string namaProduk);

#endif // MLL_T_H_INCLUDED
