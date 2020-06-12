//
// Created by trykr on 01.05.2020.
//

#pragma once
#include "MyVector.h"
#include "StackImplementation.h"

template<class ValueType>
class VectorStack: public StackImplementation<ValueType>, public MyVector<ValueType>
{
public:
    void push(const ValueType &value) override;
    void pop() override;
    ValueType& top() const override;
    size_t size() const override;
    bool isEmpty() const override;
};
template<class ValueType>
void VectorStack<ValueType>::push(const ValueType &value)
{
    this->pushBack(value);
}
template<class ValueType>
void VectorStack<ValueType>:: pop()
{
    this->popBack();
}
template<class ValueType>
ValueType& VectorStack<ValueType>::top() const
{
    return this->_data[this->size() - 1];
}
template<class ValueType>
size_t VectorStack<ValueType>::size() const
{
    return this->_size;
}
template<class ValueType>
bool VectorStack<ValueType>::isEmpty() const
{
    return this->_size == 0;
}
