#pragma once

#include "StackImplementation.h"
#include "SinglyLinkedList.h"

#include "DoublyLinkedList.h"// меняете на include вашего листа

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
template<class ValueType>
class SinglyLinkedListStack : public StackImplementation<ValueType>, public SinglyLinkedList<ValueType>
{
public:
    void push(const ValueType &value) override;
    void pop() override;
    ValueType& top() const override;
    size_t size() const override;
    bool isEmpty() const override;
};

template<class ValueType>
void SinglyLinkedListStack<ValueType>::push(const ValueType &value)
{
    this->pushBack(value);
}

template<class ValueType>
void SinglyLinkedListStack<ValueType>::pop()
{
    this->removeBack();
}

template<class ValueType>
ValueType& SinglyLinkedListStack<ValueType>::top() const
{
    return this->getLastNode()->value;
}
template<class ValueType>
size_t SinglyLinkedListStack<ValueType>::size() const
{
    return this->sizeList();
}
template<class ValueType>
bool SinglyLinkedListStack<ValueType>::isEmpty() const
{
    return this->size() == 0;
}
