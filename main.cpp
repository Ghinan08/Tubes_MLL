#include <iostream>
#include <limits>
#include "MLL T.h"
using namespace std;

int main() {
    ListKategori LK;
    ListProduk LP;
    ListRelasi LR;
    createListKategori(LK);
    createListProduk(LP);
    createListRelasi(LR);

    int pilihan;
    string namaKategori, namaProduk;
    double hargaProduk;
    adrKategori k;
    adrProduk p;

    do {
        cout << "----------------------------------------" << endl;
        cout << "  Kategori produk n to m (many to many)       " << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. Tambah Kategori" << endl;
        cout << "2. Tambah Produk" << endl;
        cout << "3. Hubungkan Produk & Kategori (Relasi)" << endl;
        cout << "4. Tampilkan Data (Group by Kategori)" << endl;
        cout << "5. Cari Data Produk" << endl;
        cout << "6. Hapus Kategori" << endl;
        cout << "7. Hapus Produk" << endl;
        cout << "0. Keluar" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Pilih menu: ";

        if (!(cin >> pilihan)) {
            cout << "Input error! Masukkan angka saja." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = -1;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (pilihan) {
                case 1: {
                    cout << "[ Input Kategori ]" << endl;
                    cout << "Masukkan nama kategori: ";
                    getline(cin, namaKategori);
                    k = createElmKategori(namaKategori);
                    insertKategori(LK, k);
                    cout << "Sip! Kategori '" << namaKategori << "' berhasil dibuat" << endl;
                    cout << endl;
                    break;
                }

                case 2: {
                    cout << "[ Input Produk ]" << endl;
                    cout << "Masukkan nama produk: ";
                    getline(cin, namaProduk);
                    cout << "Masukkan harga produk: ";

                    while (!(cin >> hargaProduk)) {
                         cout << "Harga harus angka! Ulangi: ";
                         cin.clear();
                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore();

                    p = createElmProduk(namaProduk, hargaProduk);
                    insertProduk(LP, p);
                    cout << "Sip! Produk '" << namaProduk << "' berhasil dibuat" << endl;
                    cout << "   (Jangan lupa direlasikan di menu 3)" << endl;
                    cout << endl;
                    break;
                }

                case 3: {
                    cout << "[ Relasi (SAMBUNGKAN) ]" << endl;
                    cout << "Nama Produk yg mau disambung : ";
                    getline(cin, namaProduk);
                    cout << "Mau dimasukkan ke Kategori apa: ";
                    getline(cin, namaKategori);
                    addRelasi(LR, LK, LP, namaProduk, namaKategori);
                    cout << endl;
                    break;
                }
                case 4: {
                    showData(LK, LP, LR);
                    cout << endl;
                    break;
                }
                case 5: {
                    cout << "[ Cari Produk ]" << endl;
                    cout << "Masukkan nama produk: ";
                    getline(cin, namaProduk);
                    p = searchProduk(LP, namaProduk);
                    if (p != nullptr) {
                        cout << "Ditemukan: " << p->info.nama << " | Rp " << p->info.harga << endl;
                        cout << endl;
                    } else {
                        cout << "Produk tidak ditemukan" << endl;
                        cout << endl;
                    }
                    break;
                }

                case 6: {
                    cout << "[ Hapus Kategori ]" << endl;
                    cout << "Nama Kategori yg dihapus: ";
                    getline(cin, namaKategori);
                    deleteKategori(LK, LR, namaKategori);
                    cout << endl;
                    break;
                }
                case 7: {
                    cout << "[ Hapus Produk ]" << endl;
                    cout << "Nama Produk yg dihapus: ";
                    getline(cin, namaProduk);
                    deleteProduk(LP, LR, namaProduk);
                    cout << endl;
                    break;
                }

                case 0:
                    cout << "Program selesai" << endl;
                    break;
                default:
                    cout << "Pilihan tidak ada, coba lagi." << endl;
                    break;
            }
        }

    } while (pilihan != 0);

    return 0;
}
