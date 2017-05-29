/**
 * @file IMsgFieldFilterStore.h
 * @author Christian Neuberger
 * @date 2017-04-06
 * 
 * @brief Templated interface for MsgField filter stores
 */
#ifndef IMSGFIELDFILTERSTORE_H
#define IMSGFIELDFILTERSTORE_H

/**
 * @brief The IMsgFieldFilterStore template interface
 */
template<class MsgFieldType>
class IMsgFieldFilterStore
{
public:
    virtual ~IMsgFieldFilterStore(){}

    virtual void add(const MsgFieldType &toAdd) = 0;
    virtual void remove(const MsgFieldType &toRemove) = 0;

    virtual bool contains(const MsgFieldType &toLookFor) const = 0;

    virtual MsgFieldType at(int index) const = 0;

    virtual void clear() = 0;
};

#endif /* IMSGFIELDFILTERSTORE_H */
