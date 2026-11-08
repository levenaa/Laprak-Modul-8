#include <iostream>
#include <string>
#include "packet_queue.h"

using namespace std;

bool isCodeActive(const Queue& A, const Queue& B, string code) {
    return (findElm(A, code) != nullptr || findElm(B, code) != nullptr);
}

int main() {
    Queue A, B;
    createQueue(A);
    createQueue(B);
    Statistics stats;

    string command;
    while (cin >> command) {
        if (command == "MASUK") {
            string code;
            int weight;
            cin >> code >> weight;
            if (weight <= 0 || weight > 5000) {
                cout << "Ditolak: Berat tidak valid (1-5000 gram).\n";
            } else if (isCodeActive(A, B, code)) {
                cout << "Ditolak: Kode aktif sudah ada di dalam sistem.\n";
            } else {
                Node* P = alokasi(code, weight);
                if (P == nullptr) {
                    cout << "Ditolak: Alokasi memori gagal.\n";
                } else {
                    enqueue(A, P);
                    cout << "Berhasil memasukkan " << code << " ke A.\n";
                }
            }
        } else if (command == "PINDAH") {
            int n;
            cin >> n;
            if (n <= 0 || n > nbList(A)) {
                cout << "Ditolak: Jumlah n tidak valid atau melebihi paket di A.\n";
            } else {
                for (int i = 0; i < n; i++) {
                    Node* P = nullptr;
                    dequeue(A, P);
                    enqueue(B, P);
                }
                cout << "Berhasil memindahkan " << n << " paket dari A ke B.\n";
            }
        } else if (command == "KIRIM") {
            int n;
            cin >> n;
            if (n <= 0 || n > nbList(B)) {
                cout << "Ditolak: Jumlah n tidak valid atau melebihi paket di B.\n";
            } else {
                for (int i = 0; i < n; i++) {
                    Node* P = nullptr;
                    dequeue(B, P);
                    cout << "Kirim -> Kode: " << P->data.code << ", Berat: " << P->data.weight << " gram\n";
                    stats.totalCount++;
                    stats.totalWeight += P->data.weight;
                    dealokasi(P);
                }
            }
        } else if (command == "CARI") {
            string code;
            cin >> code;
            Node* foundA = findElm(A, code);
            Node* foundB = findElm(B, code);
            if (foundA != nullptr) {
                int pos = 1;
                Node* curr = A.head;
                while (curr != foundA) { pos++; curr = curr->next; }
                cout << "A, posisi " << pos << ", berat " << foundA->data.weight << " gram\n";
            } else if (foundB != nullptr) {
                int pos = 1;
                Node* curr = B.head;
                while (curr != foundB) { pos++; curr = curr->next; }
                cout << "B, posisi " << pos << ", berat " << foundB->data.weight << " gram\n";
            } else {
                cout << "TIDAK DITEMUKAN\n";
            }
        } else if (command == "LIHAT") {
            cout << "Antrean A: "; printInfo(A); cout << "\n";
            cout << "Antrean B: "; printInfo(B); cout << "\n";
        } else if (command == "REKAP") {
            cout << "Antrean A -> Jumlah: " << nbList(A) << "\n";
            cout << "Antrean B -> Jumlah: " << nbList(B) << "\n";
            cout << "Terkirim -> Jumlah: " << stats.totalCount << ", Total Berat: " << stats.totalWeight << " gram\n";
        } else if (command == "BERSIHKAN") {
            delAll(A);
            delAll(B);
            cout << "Buffer A dan B dibersihkan.\n";
        } else if (command == "SELESAI") {
            delAll(A);
            delAll(B);
            cout << "Program selesai.\n";
            break;
        }
    }
    return 0;
}