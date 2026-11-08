#ifndef PACKET_QUEUE_H
#define PACKET_QUEUE_H

#include <string>
#include <iostream>

struct Packet {
    std::string code;
    int weight;
};

struct Node {
    Packet data;
    Node* next;
};

struct Queue {
    Node* head;
    Node* tail;
};

// Prototipe Fungsi & Prosedur ADT
void createQueue(Queue& Q);
bool isEmptyQueue(const Queue& Q);
Node* alokasi(std::string code, int weight);
void dealokasi(Node*& P);
void enqueue(Queue& Q, Node* P);
void dequeue(Queue& Q, Node*& P);
Node* findElm(const Queue& Q, std::string code);
Node* fFindElm(const Queue& Q, std::string code);
int nbList(const Queue& Q);
void printInfo(const Queue& Q);
void delAll(Queue& Q);

// Statistik Terkirim
struct Statistics {
    int totalCount = 0;
    int totalWeight = 0;
};

#endif