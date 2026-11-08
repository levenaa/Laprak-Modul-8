#include "measurement_buffer.h"
#include <cmath>

// --- Versi 1: Array Geser ---
ShiftArrayBuffer::ShiftArrayBuffer() { kosongkan(); }

void ShiftArrayBuffer::kosongkan() {
    head = -1;
    tail = -1;
}

bool ShiftArrayBuffer::tulis(int k, const int values[], int& nextSeq, int& shiftCount) {
    if (k < 1 || k > 6) return false;
    for (int i = 0; i < k; i++) {
        if (values[i] < -1000 || values[i] > 1000) return false;
    }
    int currentCount = (head == -1) ? 0 : (tail - head + 1);
    if (currentCount + k > 6) return false;

    for (int i = 0; i < k; i++) {
        if (head == -1) {
            head = 0;
            tail = 0;
        } else {
            tail++;
        }
        buffer[tail] = {nextSeq++, values[i]};
    }
    return true;
}

bool ShiftArrayBuffer::ambil(int k, int& shiftCount) {
    int currentCount = (head == -1) ? 0 : (tail - head + 1);
    if (k < 1 || k > currentCount) return false;

    for (int i = 0; i < k; i++) {
        std::cout << "Ambil -> No: " << buffer[head].seqNo << ", Nilai: " << buffer[head].value << "\n";
        // Geser ke kiri
        for (int j = head; j < tail; j++) {
            buffer[j] = buffer[j + 1];
            shiftCount++;
        }
        tail--;
        if (tail < head) {
            head = -1;
            tail = -1;
        }
    }
    return true;
}

void ShiftArrayBuffer::lihat() const {
    std::cout << "[Array Geser] FIFO: ";
    int currentCount = (head == -1) ? 0 : (tail - head + 1);
    for (int i = 0; i < currentCount; i++) {
        std::cout << buffer[head + i].seqNo << ":" << buffer[head + i].value << " ";
    }
    std::cout << "| head=" << head << ", tail=" << tail << "\n";
}

void ShiftArrayBuffer::ringkas() const {
    int currentCount = (head == -1) ? 0 : (tail - head + 1);
    if (currentCount == 0) {
        std::cout << "Jumlah 0; total 0; minimum TIDAK ADA; maksimum TIDAK ADA; rata-rata TIDAK ADA\n";
        return;
    }
    int total = 0, minVal = buffer[head].value, maxVal = buffer[head].value;
    for (int i = 0; i < currentCount; i++) {
        int v = buffer[head + i].value;
        total += v;
        if (v < minVal) minVal = v;
        if (v > maxVal) maxVal = v;
    }
    double avg = (double)total / currentCount;
    std::cout << "Jumlah " << currentCount << "; total " << total << "; minimum " << minVal 
              << "; maksimum " << maxVal << "; rata-rata " << std::fixed << std::setprecision(2) << avg << "\n";
}


// --- Versi 2: Array dengan Pemadatan ---
CompactionArrayBuffer::CompactionArrayBuffer() { kosongkan(); }

void CompactionArrayBuffer::kosongkan() {
    head = -1;
    tail = -1;
}

bool CompactionArrayBuffer::tulis(int k, const int values[], int& nextSeq, int& shiftCount) {
    if (k < 1 || k > 6) return false;
    for (int i = 0; i < k; i++) {
        if (values[i] < -1000 || values[i] > 1000) return false;
    }
    int currentCount = (head == -1) ? 0 : (tail - head + 1);
    
    // Cek apakah perlu pemadatan
    if (tail == 5 && (6 - currentCount) < k) {
        return false; // Ruang tidak cukup meskipun dipadatkan (atau melebihi batas)
    }
    
    if (head > 0 && (6 - tail - 1 + head) < k) {
        // Pemadatan manual jika ruang tidak cukup di ujung kanan
        int shiftDist = head;
        for (int i = head; i <= tail; i++) {
            buffer[i - shiftDist] = buffer[i];
            shiftCount += (shiftDist); // Hitung total pergeseran elemen
        }
        tail = tail - head;
        head = 0;
    }

    currentCount = (head == -1) ? 0 : (tail - head + 1);
    if (currentCount + k > 6) return false;

    for (int i = 0; i < k; i++) {
        if (head == -1) {
            head = 0;
            tail = 0;
        } else {
            tail++;
        }
        buffer[tail] = {nextSeq++, values[i]};
    }
    return true;
}

bool CompactionArrayBuffer::ambil(int k, int& shiftCount) {
    int currentCount = (head == -1) ? 0 : (tail - head + 1);
    if (k < 1 || k > currentCount) return false;

    for (int i = 0; i < k; i++) {
        std::cout << "Ambil -> No: " << buffer[head].seqNo << ", Nilai: " << buffer[head].value << "\n";
        head++;
        if (head > tail) {
            head = -1;
            tail = -1;
        }
    }
    return true;
}

void CompactionArrayBuffer::lihat() const {
    std::cout << "[Pemadatan] FIFO: ";
    int currentCount = (head == -1) ? 0 : (tail - head + 1);
    for (int i = 0; i < currentCount; i++) {
        std::cout << buffer[head + i].seqNo << ":" << buffer[head + i].value << " ";
    }
    std::cout << "| head=" << head << ", tail=" << tail << "\n";
}

void CompactionArrayBuffer::ringkas() const {
    int currentCount = (head == -1) ? 0 : (tail - head + 1);
    if (currentCount == 0) {
        std::cout << "Jumlah 0; total 0; minimum TIDAK ADA; maksimum TIDAK ADA; rata-rata TIDAK ADA\n";
        return;
    }
    int total = 0, minVal = buffer[head].value, maxVal = buffer[head].value;
    for (int i = 0; i < currentCount; i++) {
        int v = buffer[head + i].value;
        total += v;
        if (v < minVal) minVal = v;
        if (v > maxVal) maxVal = v;
    }
    double avg = (double)total / currentCount;
    std::cout << "Jumlah " << currentCount << "; total " << total << "; minimum " << minVal 
              << "; maksimum " << maxVal << "; rata-rata " << std::fixed << std::setprecision(2) << avg << "\n";
}


// --- Versi 3: Circular Queue ---
CircularBuffer::CircularBuffer() { kosongkan(); }

void CircularBuffer::kosongkan() {
    head = 0;
    count = 0;
}

bool CircularBuffer::tulis(int k, const int values[], int& nextSeq, int& shiftCount) {
    if (k < 1 || k > 6) return false;
    for (int i = 0; i < k; i++) {
        if (values[i] < -1000 || values[i] > 1000) return false;
    }
    if (count + k > 6) return false;

    for (int i = 0; i < k; i++) {
        int writeIdx = (head + count) % 6;
        buffer[writeIdx] = {nextSeq++, values[i]};
        count++;
    }
    return true;
}

bool CircularBuffer::ambil(int k, int& shiftCount) {
    if (k < 1 || k > count) return false;

    for (int i = 0; i < k; i++) {
        std::cout << "Ambil -> No: " << buffer[head].seqNo << ", Nilai: " << buffer[head].value << "\n";
        head = (head + 1) % 6;
        count--;
    }
    return true;
}

void CircularBuffer::lihat() const {
    std::cout << "[Circular] FIFO: ";
    for (int i = 0; i < count; i++) {
        int idx = (head + i) % 6;
        std::cout << buffer[idx].seqNo << ":" << buffer[idx].value << " ";
    }
    std::cout << "| head=" << head << ", count=" << count << "\n";
}

void CircularBuffer::ringkas() const {
    if (count == 0) {
        std::cout << "Jumlah 0; total 0; minimum TIDAK ADA; maksimum TIDAK ADA; rata-rata TIDAK ADA\n";
        return;
    }
    int total = 0, minVal = buffer[head].value, maxVal = buffer[head].value;
    for (int i = 0; i < count; i++) {
        int idx = (head + i) % 6;
        int v = buffer[idx].value;
        total += v;
        if (v < minVal) minVal = v;
        if (v > maxVal) maxVal = v;
    }
    double avg = (double)total / count;
    std::cout << "Jumlah " << count << "; total " << total << "; minimum " << minVal 
              << "; maksimum " << maxVal << "; rata-rata " << std::fixed << std::setprecision(2) << avg << "\n";
}