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
#include <QVariant>

/**
 * @defgroup MessageFieldGroup Message Fields
 * @ingroup MessageGroup
 * 
 * @{
 */

/**
 * \brief Wrapper for strongly typedef Message Field types
 * 
 * OpaqueT should be an opaque type of T. To create an opaque type create a
 * struct with a distinct name for the type. E.g. Opaque'T'Struc (replace T
 * with your type).
 * 
 * \note For simple usage of this class use the provided makro
 * #CREATE_OPAQUE_MSG_FIELD_TYPE
 * 
 * \note This wrapper does not include a cast to bool, because this would break
 * the strong typedef. Two different types could be compared for equalness by
 * casting them to bool and then comparing them. Having an explicit bool cast
 * operator solves this problem only partially. Therefore, use !! to emulate a
 * cast to bool!
 */
template<typename T, typename OpaqueT>
class MsgFieldTypeTemplate
{
public:
    /**
     * @brief Typedef for the undelying primitive type
     */
    typedef T type;

    /**
     * \brief Default constructor constructs a default value for T
     */
    explicit MsgFieldTypeTemplate() : field(T())
    {}

    /**
     * \brief Regular constructor constructs a MsgField from a T value
     */
    explicit MsgFieldTypeTemplate(const T &field) : field(field)
    {}

    /**
     * @brief Copy constructor constructs a copy of other
     */
    MsgFieldTypeTemplate(const MsgFieldTypeTemplate<T,OpaqueT> &other) :
        field(other.field)
    {}

    virtual ~MsgFieldTypeTemplate()
    {
    }


    /**
     * @brief Returns the stored field with its primitive data type T
     */
    const T getPrimitiveData() const { return field; }


    /**
     * @brief Assignment operator that assign the value of other's field to
     * this object
     */
    const MsgFieldTypeTemplate<T,OpaqueT> &operator =(
            const MsgFieldTypeTemplate<T,OpaqueT> &other
            )
    {
        this->field = other.field;
        return *this;
    }

    /**
     * @brief Addition Operator that adds this MsgField with rhs and stores
     * the result in this object
     */
    const MsgFieldTypeTemplate<T,OpaqueT> &operator +=(
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        this->field += rhs.field;
        return *this;
    }

    /**
     * @brief Addition Operator that adds lhs with rhs and returns the result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator +(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        lhs += rhs;
        return lhs;
    }

    /**
     * @brief Subtraction Operator that subtracts rhs from this MsgField and
     * stores the result in this object
     */
    const MsgFieldTypeTemplate<T,OpaqueT> &operator -=(
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        this->field -= rhs.field;
        return *this;
    }

    /**
     * @brief Subtraction Operator that subtracts rhs from lhs and returns the
     * result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator -(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        lhs -= rhs;
        return lhs;
    }

    /**
     * @brief Multiplication Operator that mulitplies this MsgField with rhs and
     * stores the result in this object
     */
    const MsgFieldTypeTemplate<T,OpaqueT> &operator *=(
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        this->field *= rhs.field;
        return *this;
    }

    /**
     * @brief Multiplication Operator that mulitplies lhs with rhs and returns
     * the result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator *(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        lhs *= rhs;
        return lhs;
    }

    /**
     * @brief Division Operator that divides this MsgField by rhs and
     * stores the result in this object
     */
    const MsgFieldTypeTemplate<T,OpaqueT> &operator /=(
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        this->field /= rhs.field;
        return *this;
    }

    /**
     * @brief Division Operator that divides lhs by rhs and returns
     * the result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator /(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        lhs /= rhs;
        return lhs;
    }

    /**
     * @brief OR-Assignment operator that ORs this MsgField with rhs and stores
     * the result in this object
     */
    const MsgFieldTypeTemplate<T,OpaqueT> &operator |=(
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        this->field |= rhs.field;
        return *this;
    }

    /**
     * @brief OR-Operator that ORs lhs with rhs and returns the result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator |(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        lhs |= rhs;
        return lhs;
    }

    /**
     * @brief OR-Operator that ORs lhs with an rhs of type T and returns the
     * result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator |(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const T &rhs
            )
    {
        return MsgFieldTypeTemplate<T,OpaqueT>(lhs.field | rhs);
    }


    /**
     * @brief AND-Assignment operator that ANDs this MsgField with rhs and
     * stores the result in this object
     */
    const MsgFieldTypeTemplate<T,OpaqueT> &operator &=
        (const MsgFieldTypeTemplate<T,OpaqueT> &rhs
         )
    {
        this->field &= rhs.field;
        return *this;
    }

    /**
     * @brief AND-Operator that ANDs lhs with rhs and returns the result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator &(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        lhs &= rhs;
        return lhs;
    }

    /**
     * @brief AND-Operator that ANDs lhs with an rhs of type T and returns the
     * result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator &(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const T &rhs
            )
    {
        return MsgFieldTypeTemplate<T,OpaqueT>(lhs.field & rhs);
    }


    /**
     * @brief XOR-Assignment operator that XORs this MsgField with rhs and
     * stores the result in this object
     */
    const MsgFieldTypeTemplate<T,OpaqueT> &operator ^=(
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        this->field ^= rhs.field;
        return *this;
    }

    /**
     * @brief XOR-Operator that XORs lhs with rhs and returns the result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator ^(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        lhs ^= rhs;
        return lhs;
    }

    /**
     * @brief XOR-Operator that XORs lhs with an rhs of type T and returns the
     * result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator ^(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const T &rhs
            )
    {
        return MsgFieldTypeTemplate<T,OpaqueT>(lhs.field ^ rhs);
    }


    /**
     * @brief Bitwise-Invert operator that inverts the bits of this field and
     * returns a new MsgField object as result
     */
    MsgFieldTypeTemplate<T,OpaqueT> operator ~() const
    {
        return MsgFieldTypeTemplate<T,OpaqueT>(~field);
    }

    /**
     * @brief Negate operator that negates this MsgField's field value and
     * returns a new MsgField object as result
     */

    MsgFieldTypeTemplate<T,OpaqueT> operator -() const
    {
        return MsgFieldTypeTemplate<T,OpaqueT>(-field);
    }


    /**
     * @brief Right-Shift-Assignment operator that shifts this object's field
     * rhs times to the right and stores the result in this object
     */
    const MsgFieldTypeTemplate<T,OpaqueT> &operator>>=(const int &rhs)
    {
        this->field >>= rhs;
        return *this;
    }

    /**
     * @brief Right-Shift operator that shifts lhs's field rhs times to the
     * right and returns a new MsgField as the result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator>>(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const int &rhs
            )
    {
        lhs >>= rhs;
        return lhs;
    }

    /**
     * @brief Left-Shift-Assignment operator that shifts this object's field
     * rhs times to the left and stores the result in this object
     */
    const MsgFieldTypeTemplate<T,OpaqueT> &operator<<=(const int &rhs)
    {
        this->field <<= rhs;
        return *this;
    }

    /**
     * @brief Left-Shift operator that shifts lhs's field rhs times to the
     * left and returns a new MsgField as the result
     */
    friend inline MsgFieldTypeTemplate<T,OpaqueT> operator<<(
            MsgFieldTypeTemplate<T,OpaqueT> lhs,
            const int &rhs
            )
    {
        lhs <<= rhs;
        return lhs;
    }


    /**
     * @brief Equal Operator to compare two MsgField objects of the same type
     * for equalness
     * 
     * \note Also needed for QHash!
     */
    friend inline bool operator==(
            const MsgFieldTypeTemplate<T,OpaqueT> &lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        return lhs.field == rhs.field;
    }

    /**
     * @brief Unequal Operator to compare two MsgField objects of the same type
     * for unequalness
     */
    friend inline bool operator!=(
            const MsgFieldTypeTemplate<T,OpaqueT> &lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        return !operator==(lhs,rhs);
    }


    /**
     * @brief Lesser operator to compare two MsgField objects for which is
     * lesser
     */
    friend inline bool operator<(
            const MsgFieldTypeTemplate<T,OpaqueT> &lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        return lhs.field < rhs.field;
    }

    /**
     * @brief Greater operator to compare two MsgField objects for which is
     * greater
     */
    friend inline bool operator>(
            const MsgFieldTypeTemplate<T,OpaqueT> &lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        return operator<(rhs,lhs);
    }

    /**
     * @brief Lesser-Or-Equal operator to compare two MsgField objects for which 
     * is lesser or if they are equal
     */
    friend inline bool operator<=(
            const MsgFieldTypeTemplate<T,OpaqueT> &lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        return !operator>(lhs,rhs);
    }

    /**
     * @brief Greater-Or-Equal operator to compare two MsgField objects for which 
     * is greater or if they are equal
     */
    friend inline bool operator>=(
            const MsgFieldTypeTemplate<T,OpaqueT> &lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        return !operator<(lhs,rhs);
    }


    /**
     * @brief Logical-Negate operator that logically negates this MsgField's
     *  field value
     */
    bool operator !() const
    {
        return !field;
    }

    /**
     * @brief Logical-OR operator that logically ORs lhs's and rhs's field
     * values
     */
    friend inline bool operator||(
            const MsgFieldTypeTemplate<T,OpaqueT> &lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        return lhs.field || rhs.field;
    }

    /**
     * @brief Logical-AND operator that logically ANDs lhs's and rhs's field
     * values
     */
    friend inline bool operator&&(
            const MsgFieldTypeTemplate<T,OpaqueT> &lhs,
            const MsgFieldTypeTemplate<T,OpaqueT> &rhs
            )
    {
        return lhs.field && rhs.field;
    }


    /**
     * @brief Cast operator for type T
     *
     * \note ONLY explicit casting is allowed with static_cast<T>(obj)
     */
    virtual explicit operator T() const
    {
        return field;
    }

    /**
     * @brief Cast operator for type QString
     * 
     * Returns the field value as a hexadecimal string. The primitive types
     * width is conserved and if the value does not fit in all digits, it is
     * filled with '0'.
     *
     * \note ONLY explicit casting is allowed with static_cast<QString>(obj)
     */
    virtual explicit operator QString() const
    {
        return QString("0x%1").arg(field,msgFieldWidth,16,QLatin1Char('0'));
        /* return QString("0x%1").arg(QString::number(field,16)); */
    }
    /* virtual explicit operator QColor() */
    /* { return QColor(Qt::green); } */

    virtual operator QVariant() const
    {
        return QVariant(field);
    }

    /**
     * @brief Support for QHash
     * 
     * In order to use the type with QHash a qHash function needs to be in the
     * namespace of this type
     */
    friend inline uint qHash(
            const MsgFieldTypeTemplate<T,OpaqueT> &key,
            uint seed
            )
    {
        return qHash(key.field, seed);
    }

private:
    /**
     * @brief Private value assignment operator to forbid the assignment of raw
     * values.
     */
    const MsgFieldTypeTemplate<T,OpaqueT> &operator=(const T &forbidden);

    /**
     * @brief msgFieldWidth is used to conserve the width of the underlying
     * primitive type.
     */
    static const int msgFieldWidth;

    /**
     * @brief Stores the actual value of the MsgField
     */
    T field;
};

/**
 * @brief Initialize the msgFieldWidth
 */
template<typename T, typename OpaqueT>
const int MsgFieldTypeTemplate<T,OpaqueT>::msgFieldWidth = sizeof(T) * 2;

// /**
// * \brief Wrapper class for typesafe primitive types that act as Message Fields
// * 
// * \note Types that need special functions for implicit casts to T, QString,
// * bool, or QColor need to derive from #MsgFieldTypeTemplate in the manner this
// * class does!
// * 
// * \note Fields need to typedef to this class with their respective type
// */
/* template<typename T> */
/* class MsgFieldType : public MsgFieldTypeTemplate<T, MsgFieldType<T>> */
/* { */
/* public: */
/*     explicit MsgFieldType() : */
/*         MsgID<T,MsgFieldType<T>>() */
/*     {} */
/*     explicit MsgFieldType(const T &field) : */
/*         MsgID<T,MsgFieldType<T>>(field) */
/*     {} */
/* }; */

/**
 * @brief MAKRO to create truly opaque MsgField types
 * 
 * In general C++ has weak typedefs:
 * 
 * typedef uint8_t someType;
 * 
 * typedef uint8_t anotherType;
 * 
 * These two types can be used interchargably. In order to forbid this behavior
 * and to restrict the operations and casts that can be done to and with a
 * MsgField, the data types are wrapped in the #MsgFieldTypeTemplate wrapper
 * class. Use This macro to create a strong typedef with name and the
 * underlying type primitiveType.
 */
#define CREATE_OPAQUE_MSG_FIELD_TYPE(primitiveType, name) \
    using name##Primitive = primitiveType; \
    /**
      @brief The name is a strong typedef for the corresponding message field
      @sa #MsgFieldTypeTemplate
    */ \
    using name \
     = MsgFieldTypeTemplate<name##Primitive, const struct Opaque##name>; \


 /**
  * @}
  */

#endif /* MSGFIELDTYPE_H */
