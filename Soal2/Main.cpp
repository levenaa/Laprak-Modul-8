#include <iostream>
#include "measurement_buffer.h"

using namespace std;

void runSimulation(MeasurementBuffer* buffer, string versionName) {
    cout << "=== UJI COBA: " << versionName << " ===\n";
    int nextSeq = 1;
    int shiftCount = 0;

    // 1. TULIS 6 12 -4 7 0 15 6
    int vals1[] = {12, -4, 7, 0, 15, 6};
    buffer->tulis(6, vals1, nextSeq, shiftCount);
    buffer->lihat();

    // 2. AMBIL 2
    buffer->ambil(2, shiftCount);
    buffer->lihat();

    // 3. TULIS 3 9 11 -2 (Harus ditolak karena sisa ruang 2)
    int vals2[] = {9, 11, -2};
    if (!buffer->tulis(3, vals2, nextSeq, shiftCount)) {
        cout << "TULIS 3 ditolak sesuai aturan.\n";
    }

    // 4. TULIS 2 9 -2
    int vals3[] = {9, -2};
    buffer->tulis(2, vals3, nextSeq, shiftCount);
    buffer->lihat();

    // 5. RINGKAS
    buffer->ringkas();
    cout << "Total pergeseran data: " << shiftCount << "\n\n";
}

int main() {
    ShiftArrayBuffer v1;
    CompactionArrayBuffer v2;
    CircularBuffer v3;

    runSimulation(&v1, "Versi 1 (Array Geser)");
    runSimulation(&v2, "Versi 2 (Array dengan Pemadatan)");
    runSimulation(&v3, "Versi 3 (Circular Queue)");

    return 0;
}