#ifndef HUGEQVECTOR_H
#define HUGEQVECTOR_H

#include "msg.h"

#include <QVector>

/**
 * \def CONTAINER_SIZE
 * \brief Size of single msg container QVector
 */
#define CONTAINER_SIZE 1000u

/**
 * \class HugeQVector
 * @brief The HugeQVector class
 *
 * Since the data set which is stored in the message model is potentially huge,
 * a regular QVector struggles to expand to the needed size (due to frequent reallocations
 * and of course the needed contigous memory being big).
 * Therefore, HugeQVector is a wrapper container, which contains multiple QVectors
 * that each have a reserved size of \ref CONTAINER_SIZE. Allocation load is alleviated,
 * and in addition contiguous memory is only needed per QVector. The overall QVector stores
 * pointers to the QVectros, which contain the Msgs.
 *
 * The most important functions have been adapted to provide a smooth interface.
 */

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
