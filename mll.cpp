#include "mll.h"

void createListKategori(ListKategori &L) {
    L.first = nullptr;
    L.last = nullptr;
}

void createListProduk(ListProduk &L) {
    L.first = nullptr;
    L.last = nullptr;
}

void createListRelasi(ListRelasi &L) {
    L.first = nullptr;
}

bool isEmptyKategori(ListKategori L) {
    return L.first == nullptr;
}

adrKategori createElmKategori(string nama) {
    adrKategori p = new elmKategori;
    p->info.nama = nama;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

adrProduk createElmProduk(string nama, int harga) {
    adrProduk p = new elmProduk;
    p->info.nama = nama;
    p->info.harga = harga;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

adrRelasi createElmRelasi(adrKategori K, adrProduk P) {
    adrRelasi r = new elmRelasi;
    r->nextKategori = K;
    r->nextProduk = P;
    r->next = nullptr;
    return r;
}

void insertKategori(ListKategori &L, adrKategori p) {
    if (L.first == nullptr) {
        L.first = p;
        L.last = p;
    } else {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
    }
}

void insertProduk(ListProduk &L, adrProduk p) {
    if (L.first == nullptr) {
        L.first = p;
        L.last = p;
    } else {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
    }
}

void insertRelasi(ListRelasi &L, adrRelasi p) {
    p->next = L.first;
    L.first = p;
}

adrKategori searchKategori(ListKategori L, string nama) {
    adrKategori p = L.first;
    while (p != nullptr) {
        if (p->info.nama == nama) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

adrProduk searchProduk(ListProduk L, string nama) {
    adrProduk p = L.first;
    while (p != nullptr) {
        if (p->info.nama == nama) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

adrRelasi searchRelasi(ListRelasi L, adrKategori K, adrProduk P) {
    adrRelasi r = L.first;
    while (r != nullptr) {
        if (r->nextKategori == K && r->nextProduk == P) {
            return r;
        }
        r = r->next;
    }
    return nullptr;
}


void addRelasi(ListRelasi &LR, ListKategori LK, ListProduk LP, string namaProduk, string namaKategori) {
    adrProduk P = searchProduk(LP, namaProduk);
    adrKategori K = searchKategori(LK, namaKategori);

    if (P != nullptr && K != nullptr) {
        adrRelasi cek = searchRelasi(LR, K, P);
        if (cek == nullptr) {
            adrRelasi R = createElmRelasi(K, P);
            insertRelasi(LR, R);
            cout << "Sukses! Produk '" << namaProduk << "' berhasil direlasikan ke '" << namaKategori << "'" << endl;
        } else {
            cout << "Notes: Relasi ini udah ada sebelumnya" << endl;
        }
    } else {
        cout << "Gagal, Produk atau Kategori tidak ditemukan" << endl;
    }
}

void showData(ListKategori LK, ListProduk LP, ListRelasi LR) {
    cout << "Laporan produk n to m (many to many)" << endl;

    adrKategori k = LK.first;
    while (k != nullptr) {
        cout << "[Kategori: " << k->info.nama << "]" << endl;

        bool found = false;
        adrRelasi r = LR.first;

        while (r != nullptr) {
            if (r->nextKategori == k) {
                cout << "  - " << r->nextProduk->info.nama
                     << " (Rp " << r->nextProduk->info.harga << ")" << endl;
                found = true;
            }
            r = r->next;
        }

        if (!found) {
            cout << "  - (Kategori ini belum memiliki produk)" << endl;
        }
        cout << endl;
        k = k->next;
    }

    cout << "----------------------------------------" << endl;
    cout << "[ Produk Tanpa Kategori (Belum Direlasikan) ]" << endl;

    adrProduk p = LP.first;
    bool adaProdukLepas = false;

    while (p != nullptr) {
        bool punyaRelasi = false;
        adrRelasi r = LR.first;

        while (r != nullptr) {
            if (r->nextProduk == p) {
                punyaRelasi = true;
                break;
            }
            r = r->next;
        }

        if (!punyaRelasi) {
            cout << "  - " << p->info.nama
                 << " (Rp " << p->info.harga << ")" << endl;
            adaProdukLepas = true;
        }
        p = p->next;
    }

    if (!adaProdukLepas) {
        cout << "  - (Semua produk sudah punya kategori)" << endl;
    }
    cout << "----------------------------------------" << endl;
}

void deleteKategori(ListKategori &LK, ListRelasi &LR, string namaKategori) {
    adrKategori K = searchKategori(LK, namaKategori);

    if (K != nullptr) {
        adrRelasi r = LR.first;
        adrRelasi prevR = nullptr;

        while (r != nullptr) {
            if (r->nextKategori == K) {
                adrRelasi hapus = r;
                if (hapus == LR.first) {
                    LR.first = r->next;
                    r = LR.first;
                    prevR = nullptr;
                } else {
                    prevR->next = r->next;
                    r = r->next;
                }
                delete hapus;
            } else {
                prevR = r;
                r = r->next;
            }
        }

        if (K == LK.first) {
            LK.first = K->next;
            if (LK.first != nullptr) LK.first->prev = nullptr;
            else LK.last = nullptr;
        } else if (K == LK.last) {
            LK.last = K->prev;
            LK.last->next = nullptr;
        } else {
            K->prev->next = K->next;
            K->next->prev = K->prev;
        }
        delete K;
        cout << "Sukses! Kategori '" << namaKategori << "' dan relasinya berhasil dihapus" << endl;
    } else {
        cout << "Gagal: Kategori tidak ditemukan" << endl;
    }
}

void deleteProduk(ListProduk &LP, ListRelasi &LR, string namaProduk) {
    adrProduk P = searchProduk(LP, namaProduk);
    if (P != nullptr) {
        adrRelasi r = LR.first;
        adrRelasi prevR = nullptr;

        while (r != nullptr) {
            if (r->nextProduk == P) {
                adrRelasi hapus = r;
                if (hapus == LR.first) {
                    LR.first = r->next;
                    r = LR.first;
                    prevR = nullptr;
                } else {
                    prevR->next = r->next;
                    r = r->next;
                }
                delete hapus;
            } else {
                prevR = r;
                r = r->next;
            }
        }
        if (P == LP.first) {
            LP.first = P->next;
            if (LP.first != nullptr) LP.first->prev = nullptr;
            else LP.last = nullptr;
        } else if (P == LP.last) {
            LP.last = P->prev;
            LP.last->next = nullptr;
        } else {
            P->prev->next = P->next;
            P->next->prev = P->prev;
        }
        delete P;
        cout << "Sukses! Produk '" << namaProduk << "' dan relasinya berhasil dihapus" << endl;
    } else {
        cout << "Gagal: Produk tidak ditemukan" << endl;
    }
}
