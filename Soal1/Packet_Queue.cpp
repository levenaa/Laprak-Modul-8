#include "packet_queue.h"

void createQueue(Queue& Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

bool isEmptyQueue(const Queue& Q) {
    return (Q.head == nullptr && Q.tail == nullptr);
}

Node* alokasi(std::string code, int weight) {
    Node* P = new Node;
    P->data.code = code;
    P->data.weight = weight;
    P->next = nullptr;
    return P;
}

void dealokasi(Node*& P) {
    delete P;
    P = nullptr;
}

void enqueue(Queue& Q, Node* P) {
    if (P == nullptr) return;
    P->next = nullptr;
    if (isEmptyQueue(Q)) {
        Q.head = P;
        Q.tail = P;
    } else {
        Q.tail->next = P;
        Q.tail = P;
    }
}

void dequeue(Queue& Q, Node*& P) {
    if (isEmptyQueue(Q)) {
        P = nullptr;
        return;
    }
    P = Q.head;
    if (Q.head == Q.tail) {
        Q.head = nullptr;
        Q.tail = nullptr;
    } else {
        Q.head = Q.head->next;
    }
    P->next = nullptr; // Sesuai aturan: next node lepas harus nullptr
}

Node* findElm(const Queue& Q, std::string code) {
    Node* P = Q.head;
    while (P != nullptr) {
        if (P->data.code == code) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

Node* fFindElm(const Queue& Q, std::string code) {
    return findElm(Q, code);
}

int nbList(const Queue& Q) {
    int count = 0;
    Node* P = Q.head;
    while (P != nullptr) {
        count++;
        P = P->next;
    }
    return count;
}

void printInfo(const Queue& Q) {
    Node* P = Q.head;
    while (P != nullptr) {
        std::cout << P->data.code << " (" << P->data.weight << " gram)";
        if (P->next != nullptr) std::cout << ", ";
        P = P->next;
    }
}

void delAll(Queue& Q) {
    Node* P;
    while (!isEmptyQueue(Q)) {
        dequeue(Q, P);
        dealokasi(P);
    }
}