#ifndef HUGEQVECTOR_H
#define HUGEQVECTOR_H

#include "msg.h"

#include <QVector>
#include <QDebug>

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

template<class T> class HugeQVector
{
public:
    HugeQVector() : currentSize(0) {}

    T *at(int index) const
    {
        return msgVectorStore.at(index/CONTAINER_SIZE)->at(index%CONTAINER_SIZE);
    }

    T *operator[](int index) const
    {
        return msgVectorStore.at(index/CONTAINER_SIZE)->operator [](index%CONTAINER_SIZE);
    }

    T *append(T* msg)
    {

        if(!(currentSize % CONTAINER_SIZE))
        {
            QVector<T*> *newQVector = new QVector<T*>();
            newQVector->reserve(CONTAINER_SIZE);
            msgVectorStore.append(newQVector);
        }
        msgVectorStore.at(currentSize/CONTAINER_SIZE)->append(msg);
        currentSize++;
        return msg;
    }

    void remove(int index)
    {
        if(!currentSize)
            return;

        int containerNr = index/CONTAINER_SIZE;
        int currentNrOfContainers = (currentSize-1)/CONTAINER_SIZE;

        qDebug() << "Remove index:" << index << "from container nr.:" << containerNr << "with a total nr of containers of: " << currentNrOfContainers;

        //remove from containing container
        msgVectorStore.at(containerNr)->remove(index%CONTAINER_SIZE);

        // iterate over all preceeding containers and rearrange them
        while(containerNr < currentNrOfContainers )
        {
            //take first element of preceeding container and append to current container
            qDebug() << "First element of container nr. " << containerNr +1 << "shifts to container nr. " << containerNr;
            msgVectorStore.at(containerNr)->append(msgVectorStore.at(containerNr+1)->first());
            //remove the first element (QVector should rearrange itself accordingly)
            msgVectorStore.at(containerNr+1)->remove(0);
            //Next container
            containerNr++;
        }

        //new size
        currentSize--;
    }

    void clear()
    {
        for(QVector<T*>* vector : msgVectorStore)
        {
            for(T* item : *vector)
            {
                delete item;
            }
            vector->clear();
        }
        qDeleteAll(msgVectorStore);
        msgVectorStore.clear();
        currentSize = 0;
    }

    int size() const
    {
        return currentSize;
    }

private:
    QVector<QVector<T*>*> msgVectorStore;
    int currentSize;
};

#endif // HUGEQVECTOR_H
