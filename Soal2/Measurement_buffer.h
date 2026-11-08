#ifndef MEASUREMENT_BUFFER_H
#define MEASUREMENT_BUFFER_H

#include <iostream>
#include <iomanip>

struct Record {
    int seqNo;
    int value;
};

class MeasurementBuffer {
public:
    virtual ~MeasurementBuffer() {}
    virtual bool tulis(int k, const int values[], int& nextSeq, int& shiftCount) = 0;
    virtual bool ambil(int k, int& shiftCount) = 0;
    virtual void lihat() const = 0;
    virtual void ringkas() const = 0;
    virtual void kosongkan() = 0;
};

// Implementasi 1: Array Geser
class ShiftArrayBuffer : public MeasurementBuffer {
private:
    Record buffer[6];
    int head;
    int tail;
public:
    ShiftArrayBuffer();
    bool tulis(int k, const int values[], int& nextSeq, int& shiftCount) override;
    bool ambil(int k, int& shiftCount) override;
    void lihat() const override;
    void ringkas() const override;
    void kosongkan() override;
};

// Implementasi 2: Array dengan Pemadatan
class CompactionArrayBuffer : public MeasurementBuffer {
private:
    Record buffer[6];
    int head;
    int tail;
public:
    CompactionArrayBuffer();
    bool tulis(int k, const int values[], int& nextSeq, int& shiftCount) override;
    bool ambil(int k, int& shiftCount) override;
    void lihat() const override;
    void ringkas() const override;
    void kosongkan() override;
};

// Implementasi 3: Circular Queue (Head + Count)
class CircularBuffer : public MeasurementBuffer {
private:
    Record buffer[6];
    int head;
    int count;
public:
    CircularBuffer();
    bool tulis(int k, const int values[], int& nextSeq, int& shiftCount) override;
    bool ambil(int k, int& shiftCount) override;
    void lihat() const override;
    void ringkas() const override;
    void kosongkan() override;
};

#endif