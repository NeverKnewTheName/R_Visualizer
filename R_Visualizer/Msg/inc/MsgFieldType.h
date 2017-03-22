/**
 * \file MsgFieldType.h
 * \author Chrisitan Neuberger
 * \date 2017-03-22
 * 
 * \brief Message Field typesafe primitive types
 */
#ifndef MSGFIELDTYPE_H
#define MSGFIELDTYPE_H

#include <QString>
#include <QVector>

/**
 * \brief Wrapper for Message Field primitive types with derivate support
 * 
 */
template<typename T, typename Derivate>
class MsgFieldTypeTemplate
{
public:
    explicit MsgFieldTypeTemplate() : field(T())
    {}
    explicit MsgFieldTypeTemplate(const T &field) : field(field)
    {}
    MsgFieldTypeTemplate(const MsgFieldTypeTemplate<T,Derivate> &other) :
        field(other.field)
    {}

    const MsgFieldTypeTemplate<T,Derivate> &operator =(const Derivate &other)
    {
        this->field = other.field;
        return *this;
    }

    const MsgFieldTypeTemplate<T,Derivate> &operator |=(const Derivate &rhs)
    {
        this->field |= rhs.field;
        return *this;
    }
    friend inline Derivate operator |(Derivate lhs, const Derivate &rhs)
    {
        lhs |= rhs;
        return lhs;
    }
    friend inline Derivate operator |(Derivate lhs, const T &rhs)
    {
        return Derivate(lhs.field | rhs);
    }

    const MsgFieldTypeTemplate<T,Derivate> &operator &=(const Derivate &rhs)
    {
        this->field &= rhs.field;
        return *this;
    }
    friend inline Derivate operator &(Derivate lhs, const Derivate &rhs)
    {
        lhs &= rhs;
        return lhs;
    }
    friend inline Derivate operator &(Derivate lhs, const T &rhs)
    {
        return Derivate(lhs.field & rhs);
    }

    const MsgFieldTypeTemplate<T,Derivate> &operator ^=(const Derivate &rhs)
    {
        this->field ^= rhs.field;
        return *this;
    }
    friend inline Derivate operator ^(Derivate lhs, const Derivate &rhs)
    {
        lhs ^= rhs;
        return lhs;
    }
    friend inline Derivate operator ^(Derivate lhs, const T &rhs)
    {
        return Derivate(lhs.field ^ rhs);
    }

    Derivate operator ~() const
    {
        return Derivate(~field);
    }
    Derivate operator -() const
    {
        return Derivate(-field);
    }

    const MsgFieldTypeTemplate<T,Derivate> &operator>>=(const int &rhs)
    {
        this->field >>= rhs;
        return *this;
    }
    friend inline Derivate operator>>(Derivate lhs,const int &rhs)
    {
        lhs >>= rhs;
        return lhs;
    }
    const MsgFieldTypeTemplate<T,Derivate> &operator<<=(const int &rhs)
    {
        this->field <<= rhs;
        return *this;
    }
    friend inline Derivate operator<<(Derivate lhs,const int &rhs)
    {
        lhs <<= rhs;
        return lhs;
    }

    friend inline bool operator==(const Derivate &lhs,const Derivate &rhs)
    {
        return lhs.field == rhs.field;
    }
    friend inline bool operator!=(const Derivate &lhs,const Derivate &rhs)
    {
        return !operator==(lhs,rhs);
    }

    friend inline bool operator<(const Derivate &lhs,const Derivate &rhs)
    {
        return lhs.field < rhs.field;
    }
    friend inline bool operator>(const Derivate &lhs,const Derivate &rhs)
    {
        return operator<(rhs,lhs);
    }
    friend inline bool operator<=(const Derivate &lhs,const Derivate &rhs)
    {
        return !operator>(lhs,rhs);
    }
    friend inline bool operator>=(const Derivate &lhs,const Derivate &rhs)
    {
        return !operator<(lhs,rhs);
    }

    bool operator !() const
    {
        return !field;
    }
    friend inline bool operator||(const Derivate &lhs,const Derivate &rhs)
    {
        return lhs.field || rhs.field;
    }
    friend inline bool operator&&(const Derivate &lhs,const Derivate &rhs)
    {
        return lhs.field && rhs.field;
    }

    virtual explicit operator T()
    {
        return field;
    }
    virtual explicit operator bool()
    {
        return field;
    }
    virtual explicit operator QString()
    {
        return QString("0x%1").arg(QString::number(field,16));
    }
    /* virtual explicit operator QColor() */
    /* { return QColor(Qt::green); } */

    T getField() const
    {
        return field;
    }

private:
    const Derivate &operator=(const T &forbidden);
    T field;
};

/**
 * \brief Wrapper class for typesafe primitive types that act as Message Fields
 * 
 * \note Types that need special functions for implicit casts to T, QString,
 * bool, or QColor need to derive from #MsgFieldTypeTemplate in the manner this
 * class does!
 */
template<typename T>
class MsgFieldType : public MsgFieldTypeTemplate<T, MsgFieldType<T>>
{
public:
    explicit MsgFieldType() :
        MsgID<T,MsgFieldType<T>>()
    {}
    explicit MsgFieldType(const T &id) :
        MsgID<T,MsgFieldType<T>>(id)
    {}
};

typedef quint16 MsgIDPrimitiveType;
typedef MsgFieldType<MsgIDPrimitiveType> MsgID;

typedef quint16 MsgCodePrimitiveType;
typedef MsgFieldType<MsgCodePrimitiveType> MsgCode;

typedef quint8 MsgDataBytePrimitiveType;
typedef MsgFieldType<MsgDataBytePrimitiveType> MsgDataByte;

typedef QVector<MsgDataByte> MsgDataByteVect;

#endif /* MSGFIELDTYPE_H */
