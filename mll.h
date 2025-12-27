#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED

#include <iostream>
using namespace std;

typedef struct elmKategori *adrKategori;
typedef struct elmProduk *adrProduk;

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
    adrKategori parent;
};

struct ListKategori {
    adrKategori first;
    adrKategori last;
};

struct ListProduk {
    adrProduk first;
    adrProduk last;
};

void createListKategori(ListKategori &L);
void createListProduk(ListProduk &L);
bool isEmptyKategori(ListKategori L);
bool isEmptyProduk(adrKategori p);
adrKategori createElmKategori(string nama);
adrProduk createElmProduk(string nama, int harga);
void insertKategori(ListKategori &L, adrKategori p);
void insertProduk(ListProduk &L, adrProduk p);
adrKategori searchKategori(ListKategori L, string nama);
adrProduk searchProduk(ListProduk L, string nama);
void addRelasi(ListProduk &LP, ListKategori &LK, string namaProduk, string namaKategori);
void showData(ListKategori LK, ListProduk LP);
void deleteKategori(ListKategori &LK, ListProduk &LP, string namaKategori);
void deleteProduk(ListProduk &L, string namaProduk);
#endif // MLL_H_INCLUDED
