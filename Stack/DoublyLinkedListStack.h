//
// Created by trykr on 10.06.2020.
//

#ifndef QUEUE_DOUBLYLISTQUEUE_H
#define QUEUE_DOUBLYLISTQUEUE_H
#include <stdlib.h>
#include "DoublyLinkedList.h"
#include "StackImplementation.h"
template<class ValueType>
class DoublyLinkedListStack : public StackImplementation<ValueType>, public DoublyLinkedList<ValueType>
{
public:
    void push(const ValueType &value) override;
    void pop() override;
    ValueType& top() const override;
    size_t size() const override;
    bool isEmpty() const override;
};

template<class ValueType>
void DoublyLinkedListStack<ValueType>::push(const ValueType &value)
{
    this->pushBack(value);
}

template<class ValueType>
void DoublyLinkedListStack<ValueType>::pop()
{
    this->removeBack();
}

template<class ValueType>
ValueType& DoublyLinkedListStack<ValueType>::top() const
{
    return this->getLastNode()->value;
}
template<class ValueType>
size_t DoublyLinkedListStack<ValueType>::size() const
{
    return this->sizeList();
}
template<class ValueType>
bool DoublyLinkedListStack<ValueType>::isEmpty() const
{
    return this->sizeList() == 0;
}
#endif //QUEUE_DOUBLYLISTQUEUE_H
