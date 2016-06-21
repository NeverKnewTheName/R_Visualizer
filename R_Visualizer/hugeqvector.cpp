#include "hugeqvector.h"

HugeQVector::HugeQVector() :
    currentSize(0)
{
    //    msgVectorStore.append(new QVector<Msg*>());
    //    msgVectorStore.at(0)->reserve(CONTAINER_SIZE);
}

Msg *HugeQVector::at(int index) const
{
    return msgVectorStore.at(CONTAINER_SIZE/index)->at(CONTAINER_SIZE-index);
}

Msg *HugeQVector::operator[](int index) const
{
    return msgVectorStore.at(CONTAINER_SIZE/index)->operator [](CONTAINER_SIZE-index);
}

Msg *HugeQVector::append(Msg *msg)
{
    if(!(currentSize % CONTAINER_SIZE))
    {
        msgVectorStore.append(new QVector<Msg*>());
        msgVectorStore.reserve(CONTAINER_SIZE);
    }
    msgVectorStore.at(CONTAINER_SIZE/currentSize)->append(msg);
    currentSize++;
    return msg;
}

void HugeQVector::remove(int index)
{
    msgVectorStore.at(CONTAINER_SIZE/index)->remove(CONTAINER_SIZE-index);
    currentSize++;
}

void HugeQVector::clear()
{
    for(QVector<Msg*>* vector : msgVectorStore)
    {
        for(Msg* item : *vector)
        {
            delete item;
        }
        vector->clear();
    }
    qDeleteAll(msgVectorStore);
    msgVectorStore.clear();
}

int HugeQVector::size() const
{
    return currentSize;
}

