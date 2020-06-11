//
// Created by trykr on 01.05.2020.
//

#pragma once
#include "MyVector.h"
#include "QueueImplementation.h"

template<class ValueType>
class VectorQueue: public QueueImplementation<ValueType>, public MyVector<ValueType>
{
public:
    void enqueue(const ValueType &value) override;
    void dequeue() override;
    ValueType& front() const override;
    size_t size() const override;
    bool isEmpty() const override;
};
template<class ValueType>
void VectorQueue<ValueType>::enqueue(const ValueType &value)
{
    this->pushBack(value);
}
template<class ValueType>
void VectorQueue<ValueType>:: dequeue()
{
    this->popFront();
}
template<class ValueType>
ValueType& VectorQueue<ValueType>::front() const
{
    return this->_data[0];
}
template<class ValueType>
size_t VectorQueue<ValueType>::size() const
{
    return this->_size;
}
template<class ValueType>
bool VectorQueue<ValueType>::isEmpty() const
{
    return this->_size == 0;
}
