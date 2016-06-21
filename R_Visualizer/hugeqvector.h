#ifndef HUGEQVECTOR_H
#define HUGEQVECTOR_H

#include "msg.h"

#include <QVector>

#define CONTAINER_SIZE 1000u

class HugeQVector
{
public:
    HugeQVector();

    Msg *at(int index) const;
    Msg *operator[](int index) const;
    Msg *append(Msg* msg);
    void remove(int index);
    void clear();
    int size() const;

private:
    QVector<QVector<Msg*>*> msgVectorStore;
    int currentSize;
};

#endif // HUGEQVECTOR_H
