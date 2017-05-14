/**
 * \file MsgDataType.h
 * \author Christian Neuberger
 * \date 2017-03-23
 * 
 * \brief Typedefs for the Message Data Field
 */
#ifndef MSGDATATYPE_H
#define MSGDATATYPE_H

#include <QMetaType>
#include <QVector>
#include <QDataStream>

#include "MsgFieldType.h"

/**
 * @addtogroup MessageFieldGroup
 * 
 * @{
 */

/**
 * \brief Typedef for the primitive type of a single data byte of a message's
 * data field
 */
typedef quint8 MsgDataBytePrimitiveType;

CREATE_OPAQUE_MSG_FIELD_TYPE(MsgDataBytePrimitiveType, MsgDataByteType)

Q_DECLARE_METATYPE(MsgDataByteType)

/*
 * \brief Typedef for a message's data
 * 
 * \note This groups the indiviual data bytes of the data field
 */
//typedef QVector<MsgDataByteType> MsgDataType;

/**
 * @brief The MsgDataType class is a wrapper for a QVector to facilitate additional
 * functionality to a regular QVector and type safety
 *
 * \note Groups the individual #MsgDataByteType from the data portion of a #IMsg
 */
class MsgDataType
{
public:
    /**
     * @brief QT constant iterator
     */
    typedef QVector<MsgDataByteType>::ConstIterator ConstIterator;
    /**
     * @brief QT non-constant iterator
     */
    typedef QVector<MsgDataByteType>::Iterator Iterator;
    /**
     * @brief STL-style constant iterator
     */
    typedef QVector<MsgDataByteType>::const_iterator const_iterator;
    /**
     * @brief STL-Style constant pointer forthe contained data
     */
    typedef QVector<MsgDataByteType>::const_pointer const_pointer;
    /**
     * @brief STL-style constant reference forthe contained data
     */
    typedef QVector<MsgDataByteType>::const_reference const_reference;
    /**
     * @brief STL-style constant reverse iterator
     */
    typedef QVector<MsgDataByteType>::const_reverse_iterator const_reverse_iterator;
    /**
     * @brief STL-style difference_type
     */
    typedef QVector<MsgDataByteType>::difference_type difference_type;
    /**
     * @brief STL-style non-constant iterator
     */
    typedef QVector<MsgDataByteType>::iterator iterator;
    /**
     * @brief STL-style non-constant pointer forthe contained data
     */
    typedef QVector<MsgDataByteType>::pointer pointer;
    /**
     * @brief STL-style non-constant reference for the contained data
     */
    typedef QVector<MsgDataByteType>::reference reference;
    /**
     * @brief STL-style non-constant reverse iterator
     */
    typedef QVector<MsgDataByteType>::reverse_iterator reverse_iterator;
    /**
     * @brief STL-style size_type
     */
    typedef QVector<MsgDataByteType>::size_type size_type;
    /**
     * @brief STL-Style value_type for the contained data
     */
    typedef QVector<MsgDataByteType>::value_type value_type;

    /**
     * @brief Creates a #MsgDataType from a standard QList<MsgDataByteType>
     *
     * @param list
     *
     * @return A #MsgDataType with the data from the provided QList
     */
    static MsgDataType fromList(const QList<MsgDataByteType> &list)
    {
        return MsgDataType(QVector<MsgDataByteType>::fromList(list));
    }

    /**
     * @brief Creates a #MsgDataType from a standard std::vector<MsgDataByteType>
     *
     * @param stdVector
     *
     * @return A #MsgDataType with the data from the provied std::vector
     */
    static MsgDataType fromStdVector(const std::vector<MsgDataByteType> &stdVector)
    {
        return MsgDataType(QVector<MsgDataByteType>::fromStdVector(stdVector));
    }

    MsgDataType() :
        dataByteVector()
    {

    }

    MsgDataType(int size) :
        dataByteVector(size)
    {

    }

    MsgDataType(int size, const MsgDataByteType &value) :
        dataByteVector(size, value)
    {

    }

    MsgDataType(const MsgDataType &other) :
        dataByteVector(other.dataByteVector)
    {

    }

    MsgDataType(MsgDataType &&other) :
        dataByteVector(std::move(other.dataByteVector))
    {

    }

    MsgDataType(std::initializer_list<MsgDataByteType> args) :
        dataByteVector(args)
    {

    }

    ~MsgDataType()
    {

    }

    void append(const MsgDataByteType &value)
    {
        dataByteVector.append(value);
    }

    void append(MsgDataByteType &&value)
    {
        dataByteVector.append(std::move(value));
    }

    void append(const MsgDataType &other)
    {
        dataByteVector.append(other.dataByteVector);
    }

    const MsgDataByteType &at(int i) const
    {
        return dataByteVector.at(i);
    }

    reference back()
    {
        return dataByteVector.back();
    }

    const_reference back() const
    {
        return dataByteVector.back();
    }

    iterator begin()
    {
        return dataByteVector.begin();
    }

    const_iterator begin() const
    {
        return dataByteVector.begin();
    }

    int capacity()
    {
        return dataByteVector.capacity();
    }

    const_iterator cbegin() const
    {
        return dataByteVector.cbegin();
    }

    const_iterator cend() const
    {
        return dataByteVector.cend();
    }

    void clear()
    {
        dataByteVector.clear();
    }

    const_iterator constBegin() const
    {
        return dataByteVector.constBegin();
    }

    const MsgDataByteType *constData() const
    {
        return dataByteVector.constData();
    }

    const_iterator constEnd() const
    {
        return dataByteVector.constEnd();
    }

    const MsgDataByteType &constFirst() const
    {
        return dataByteVector.constFirst();
    }

    const MsgDataByteType &constLast() const
    {
        return dataByteVector.constLast();
    }

    bool contains(const MsgDataByteType &value) const
    {
        return dataByteVector.contains(value);
    }

    int count(const MsgDataByteType &value) const
    {
        return dataByteVector.count(value);
    }

    int count() const
    {
        return dataByteVector.count();
    }

    const_reverse_iterator crbeging() const
    {
        return dataByteVector.crbegin();
    }

    const_reverse_iterator crend() const
    {
        return dataByteVector.crend();
    }

    MsgDataByteType *data()
    {
        return dataByteVector.data();
    }

    const MsgDataByteType *data() const
    {
        return dataByteVector.data();
    }

    bool empty() const
    {
        return dataByteVector.empty();
    }

    iterator end()
    {
        return dataByteVector.end();
    }

    const_iterator end() const
    {
        return dataByteVector.end();
    }

    bool endsWith(const MsgDataByteType &value) const
    {
        return dataByteVector.endsWith(value);
    }

    iterator erase(iterator pos)
    {
        return dataByteVector.erase(pos);
    }

    iterator erase(iterator begin, iterator end)
    {
        return dataByteVector.erase(begin,end);
    }

    MsgDataType &fill(const MsgDataByteType &value, int size = 1)
    {
        dataByteVector.fill(value,size);
        return *this;
    }

    MsgDataByteType &first()
    {
        return dataByteVector.first();
    }

    const MsgDataByteType &first() const
    {
        return dataByteVector.first();
    }

    MsgDataByteType &front()
    {
        return dataByteVector.front();
    }

    const_reference front() const
    {
        return dataByteVector.front();
    }

    int indexOf(const MsgDataByteType &value, int from = 0)
    {
        return dataByteVector.indexOf(value,from);
    }

    void insert(int i, const MsgDataByteType &value)
    {
        dataByteVector.insert(i,value);
    }

    void insert(int i, int count, const MsgDataByteType &value)
    {
        dataByteVector.insert(i,count,value);
    }

    iterator insert(iterator before, int count, const MsgDataByteType &value)
    {
        return dataByteVector.insert(before,count,value);
    }

    iterator insert(iterator before, const MsgDataByteType &value)
    {
        return dataByteVector.insert(before,value);
    }

    bool isEmpty()
    {
        return dataByteVector.isEmpty();
    }

    MsgDataByteType &last()
    {
        return dataByteVector.last();
    }

    const MsgDataByteType &last() const
    {
        return dataByteVector.last();
    }

    int lastIndexOf(const MsgDataByteType &value, int from = -1) const
    {
        return dataByteVector.lastIndexOf(value,from);
    }

    int length() const
    {
        return dataByteVector.length();
    }

    MsgDataType mid(int pos, int length = -1) const
    {
        return MsgDataType(dataByteVector.mid(pos,length));
    }

    void move(int from, int to)
    {
        dataByteVector.move(from,to);
    }

    void pop_back()
    {
        dataByteVector.pop_back();
    }

    void pop_front()
    {
        dataByteVector.pop_front();
    }

    void prepend(const MsgDataByteType &value)
    {
        dataByteVector.prepend(value);
    }

    void push_back(const MsgDataByteType &value)
    {
        dataByteVector.push_back(value);
    }

    void push_back(MsgDataByteType &&value)
    {
        dataByteVector.push_back(std::move(value));
    }

    void push_front(const MsgDataByteType &value)
    {
        dataByteVector.push_front(value);
    }

    reverse_iterator rbegin()
    {
        return dataByteVector.rbegin();
    }


    const_reverse_iterator rbegin() const
    {
        return dataByteVector.rbegin();
    }

    void remove(int i)
    {
        dataByteVector.remove(i);
    }

    void remove(int i, int count)
    {
        dataByteVector.remove(i,count);
    }

    int removeAll(const MsgDataByteType &value)
    {
        return dataByteVector.removeAll(value);
    }

    void removeAt(int i)
    {
        dataByteVector.removeAt(i);
    }

    void removeFirst()
    {
        dataByteVector.removeFirst();
    }

    void removeLast()
    {
        dataByteVector.removeLast();
    }

    bool removeOne(const MsgDataByteType &value)
    {
        return dataByteVector.removeOne(value);
    }

    reverse_iterator rend()
    {
        return dataByteVector.rend();
    }

    const_reverse_iterator rend() const
    {
        return dataByteVector.rend();
    }

    void replace(int i, const MsgDataByteType &value)
    {
        dataByteVector.replace(i,value);
    }

    void reserve(int size)
    {
        dataByteVector.reserve(size);
    }

    void resize(int size)
    {
        dataByteVector.resize(size);
    }

    int size() const
    {
        return dataByteVector.size();
    }

    void squeeze()
    {
        dataByteVector.squeeze();
    }

    bool startsWith(const MsgDataByteType &value) const
    {
        return dataByteVector.startsWith(value);
    }

    void swap(MsgDataType &other)
    {
        dataByteVector.swap(other.dataByteVector);
    }

    MsgDataByteType takeAt(int i)
    {
        return dataByteVector.takeAt(i);
    }

    MsgDataByteType takeFirst()
    {
        return dataByteVector.takeFirst();
    }

    MsgDataByteType takeLast()
    {
        return dataByteVector.takeLast();
    }

    QList<MsgDataByteType> toList() const
    {
        return dataByteVector.toList();
    }

    std::vector<MsgDataByteType> toVector() const
    {
        return dataByteVector.toStdVector();
    }

    MsgDataByteType value(int i) const
    {
        return dataByteVector.value(i);
    }

    MsgDataByteType value(int i, const MsgDataByteType &defaultValue) const
    {
        return dataByteVector.value(i,defaultValue);
    }

    bool operator !=(const MsgDataType &other) const
    {
        return dataByteVector.operator !=(other.dataByteVector);
    }

    MsgDataType operator +(const MsgDataType &other) const
    {
        return MsgDataType(dataByteVector.operator +(other.dataByteVector));
    }

    MsgDataType &operator +=(const MsgDataType &other)
    {
        dataByteVector.operator +=(other.dataByteVector);

        return *this;
    }

    MsgDataType &operator +=(const MsgDataByteType &value)
    {
        dataByteVector.operator +=(value);

        return *this;
    }

    MsgDataType &operator <<(const MsgDataByteType &value)
    {
        dataByteVector.operator <<(value);

        return *this;
    }

    MsgDataType &operator <<(const MsgDataType &other)
    {
        dataByteVector.operator <<(other.dataByteVector);

        return *this;
    }

    MsgDataType &operator =(const MsgDataType &other)
    {
        dataByteVector.operator =(other.dataByteVector);

        return *this;
    }

    MsgDataType &operator =(MsgDataType &&other)
    {
        dataByteVector.operator =(std::move(other.dataByteVector));

        return *this;
    }

    bool operator ==(const MsgDataType &other) const
    {
        return dataByteVector.operator ==(other.dataByteVector);
    }

    MsgDataByteType &operator [](int i)
    {
        return dataByteVector.operator [](i);
    }

    const MsgDataByteType &operator [](int i) const
    {
        return dataByteVector.operator [](i);
    }

    friend uint qHash(const MsgDataType &key, uint seed = 0)
    {
        return qHash(key.dataByteVector,seed);
    }

    friend bool operator <(const MsgDataType &lhs, const MsgDataType &rhs)
    {
        return operator <(lhs.dataByteVector,rhs.dataByteVector);
    }

    friend bool operator >(const MsgDataType &lhs, const MsgDataType &rhs)
    {
        return operator >(lhs.dataByteVector, rhs.dataByteVector);
    }

    friend bool operator >=(const MsgDataType &lhs, const MsgDataType &rhs)
    {
        return operator >=(lhs.dataByteVector, rhs.dataByteVector);
    }

    explicit operator QString() const
    {
        QString stringRep("");

        for(const MsgDataByteType &byte : dataByteVector)
        {
            stringRep.append(static_cast<QString>(byte) + " ");
        }

        return stringRep.trimmed();
    }


private:
    MsgDataType(const QVector<MsgDataByteType> &byteVector) :
        dataByteVector(byteVector)
    {

    }

    MsgDataType(QVector<MsgDataByteType> &&byteVector) :
        dataByteVector(std::move(byteVector))
    {

    }

    QVector<MsgDataByteType> dataByteVector;
};

Q_DECLARE_METATYPE(MsgDataType)

/**
 * @}
 */

#endif /* MSGDATATYPE_H */
