#ifdef HUGEQVECTOR_NO_TEMPLATE

#include "hugeqvector.h"


#include <QDebug>

template<class T> HugeQVector<T>::HugeQVector() :
    currentSize(0)
{
    //    msgVectorStore.append(new QVector<Msg*>());
    //    msgVectorStore.at(0)->reserve(CONTAINER_SIZE);
}

template<class T> T *HugeQVector<T>::at(int index) const
{
    return msgVectorStore.at(index/CONTAINER_SIZE)->at(index%CONTAINER_SIZE);
}

template<class T> T *HugeQVector<T>::operator[](int index) const
{
    return msgVectorStore.at(index/CONTAINER_SIZE)->operator [](index%CONTAINER_SIZE);
}

template<class T> T *HugeQVector<T>::append(T *msg)
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

template<class T> void HugeQVector<T>::remove(int index)
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

template<class T> void HugeQVector<T>::clear()
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

template<class T> int HugeQVector<T>::size() const
{
    return currentSize;
}

#endif // HUGEQVECTOR_NO_TEMPLATE
