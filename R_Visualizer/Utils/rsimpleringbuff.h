/**
 * \file rsimpleringbuff.h
 * \author Christian Neuberger
 * \date 2017-02-04
 * 
 * \brief Simple destructive ring buffer for multipurpose use
 * 
 */
#ifndef RSIMPLERINGBUFF_H
#define RSIMPLERINGBUFF_H

#include <QVector>

/**
 * \brief Simple RingBuffer that destroys elements on overflow
 * 
 * \note The template parameter must have an implemented == operator!
 */
template<typename T> class RSimpleDestructiveRingBuff
{
public:
    /**
     * \brief constructs the ring buffer with the given size
     * 
     * \param[in] size    Size to set for the ring buffer
     */
    RSimpleDestructiveRingBuff(const int size) :
        RBufBuffer(size),
        RBufSize(size),
        RBufCurSize(0),
        RBufStartIndex(0),
        RBufEndIndex(size-1)
    {
    }

    /**
     * \brief append an element to the current end of the ring buffer
     * 
     * if the size of the ring buffer is exceeded the first element is overriden
     * the ring buffers location pointers are adapted accordingly
     */
    void append(const T &value)
    {
        if(RBufCurSize == RBufSize)
        {
            IncrementIndex(RBufStartIndex);// = (RBufStartIndex + 1) % RBufSize;
        }
        else
        {
            RBufCurSize++;
        }
        IncrementIndex(RBufEndIndex);// = ( RBufEndIndex +1 ) % RBufSize;

        RBufBuffer.replace(RBufEndIndex, value);
    }

    /** 
     * \brief prepend an element to the current start of the ring buffer
     * if the size of the ring buffer is exceeded the last element is overriden
     * the ring buffers location pointers are adapted accordingly
     */
    void prepend(const T &value)
    {
        if(RBufCurSize == RBufSize)
        {
            DecrementIndex(RBufEndIndex);// = (RBufEndIndex - 1+RBufSize) % RBufSize;
        }
        else
        {
            RBufCurSize++;
        }
        DecrementIndex(RBufStartIndex);// = (RBufStartIndex - 1+RBufSize) % RBufSize; //Negative modulo...

        RBufBuffer.replace(RBufStartIndex, value);
    }

    /**
     * \brief replaces the element at the given index with the given value
     */
    void replace(const int index, const T &value)
    {
        RBufBuffer.replace((index + RBufStartIndex ) % RBufSize, value);
    }

    /**
     * \brief removes the element at the given index from the ring buffer
     * 
     * The ring buffer's location pointers are adapted accordindly
     */
    void remove(const int index)
    {
        int calcdIndex = ( index + RBufStartIndex ) % RBufSize;
        if(calcdIndex < RBufCurSize)
        {
            if( calcdIndex == RBufStartIndex )
            {
                //Remove first
                IncrementIndex(RBufStartIndex);
            }
            else if( calcdIndex == RBufEndIndex )
            {
                //Remove last
                DecrementIndex(RBufEndIndex);
            }
            else
            {
                //Remove somewhere between...
                while(calcdIndex != RBufEndIndex)
                {
                    T &ToReplace = RBufBuffer[calcdIndex];
                    IncrementIndex(calcdIndex);
                    ToReplace = RBufBuffer[calcdIndex];
                }

                DecrementIndex(RBufEndIndex);// = (RBufEndIndex - 1+RBufSize) % RBufSize;
            }

            RBufCurSize--;
        }
    }

    /** 
     * \brief retrieves the current first element of the ring buffer
     * 
     * The first element is the element pointed to by the ring buffer's
     * start pointer.
     */
    const T &first() const
    {
        return RBufBuffer.at(RBufStartIndex);
    }

    /**
     * \brief retrieves the current last element of the ring buffer
     * 
     * The last element is the element pointed to by the ring buffer's
     * end pointer
     */
    const T &last() const
    {
        return RBufBuffer.at(RBufEndIndex);
    }

    /**
     * \brief retrieves the current element at the given index
     */
    const T &at(const int index) const
    {
        const int calcdIndex = ( index + RBufStartIndex ) % RBufSize;
        //        qDebug() << __PRETTY_FUNCTION__ << "CalcdIndex: " << calcdIndex;
        return RBufBuffer.at(calcdIndex);
    }

    /**
     * \brief verfifies that a given value is contained in the ring buffer
     */
    bool contains(const T &value) const
    {
        return RBufBuffer.contains(value);
    }

    /**
     * \brief returns the location of a given value in the ring buffer
     * 
     * if the value is not contained in the ring buffer -1 is returned.
     */
    int find(const T&value) const
    {
        int curIndex = RBufCurSize;
        while(curIndex--)
        {
            const T&found = at(curIndex);
            if(value == found)
                return curIndex;
        }
        return -1;
    }

    /**
     * \brief returns the current size of the ring buffer
     * 
     * \note the size of the ring buffer never exceeds its set size, 
     * however the current size of the ring buffer can be smaller.
     */
    int size() const
    {
        return RBufCurSize;
    }

    /**
     * \brief returns the capacity of the internal buffer
     */
    int capacity() const
    {
        return RBufBuffer.capacity();
    }

    /**
     * \brief clears the ring buffer and resets its location pointers
     * 
     * \warning This does not free the contained elements!
     */
    void clear()
    {
        RBufBuffer = QVector<T>(RBufSize);
        RBufCurSize = 0;
        RBufStartIndex = 0;
        RBufEndIndex = RBufSize-1;
    }

private:
    /**
     * \brief Decrement the given index with respect to the buffer size
     * 
     * This method ensures that the index is set to the maximum value if the minimum value
     * is fallen short of.
     */
    int DecrementIndex(int &index)
    {
        index = (index - 1+RBufSize) % RBufSize; //Negative modulo...
        return index;
    }
    /**
     * \brief Increment the given index with respect to the buffer size
     * 
     * This method ensures that the index does not exceed the buffer's size
     */
    int IncrementIndex(int &index)
    {
        index = (index + 1) % RBufSize;
        return index;
    }

    QVector<T> RBufBuffer; //!< Buffer vector
    const int RBufSize;    //!< Maximum size of the buffer
    int RBufCurSize;       //!< Current size of the buffer/Current number of elements in the buffer
    int RBufStartIndex;    //!< Current start index of the buffer
    int RBufEndIndex;      //!< Current end index of the buffer
};
#endif /* ifndef RSIMPLERINGBUFF_H */
