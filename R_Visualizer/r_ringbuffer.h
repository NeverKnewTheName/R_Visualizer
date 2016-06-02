#ifndef R_RINGBUFFER_H
#define R_RINGBUFFER_H

#define STD_SIZE 100

template <typename T> class R_RingBuffer
{
public:
    R_RingBuffer() : m_size(STD_SIZE), m_head(0), m_tail(0)
    {
        m_Buffer = new T[STD_SIZE];
    }
    R_RingBuffer(unsigned int size) : m_size(size), m_head(0), m_tail(0)
    {
        m_Buffer = new T[size];
    }
    ~R_RingBuffer()
    {
        delete [] m_Buffer;
    }

    void push(T newEntry)
    {
        m_Buffer[m_head] = newEntry;
        if( m_head == m_tail )// head is overtaking tail
            m_tail = nextIndex(m_tail);
        m_head = nextIndex(m_head);
    }
    T pop()
    {
        // NOTE: do not call pop on empty buffer...
        // ToDO: check wether head is the same as tail and return if this is the case -> empty;
        m_head = prevIndex(m_head);
        T obj = m_Buffer[m_head];
        return obj;
    }

    T at(const unsigned int index) const
    {
        int newIndex = ( index + m_tail ) % m_size;
        return m_Buffer[newIndex];
    }

private:
    unsigned int nextIndex(unsigned int currentIndex)
    {
        ++currentIndex;
        return currentIndex % m_size;
    }
    unsigned int prevIndex(unsigned int currentIndex)
    {
        --currentIndex;
        return ( currentIndex > 0 ) ? currentIndex : m_size-1;
    }

    T *m_Buffer;
    unsigned int m_size;
    unsigned int m_head;
    unsigned int m_tail;
};

#endif // R_RINGBUFFER_H
