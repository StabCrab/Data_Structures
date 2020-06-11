#pragma once

#include "QueueImplementation.h"
#include "SinglyLinkedList.h"

#include "DoublyLinkedList.h"// меняете на include вашего листа

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
template<class ValueType>
class SinglyLinkedListQueue : public QueueImplementation<ValueType>, public SinglyLinkedList<ValueType>
{
public:
    void enqueue(const ValueType &value) override;
    void dequeue() override;
    ValueType& front() const override;
    size_t size() const override;
    bool isEmpty() const override;
};

template<class ValueType>
void SinglyLinkedListQueue<ValueType>::enqueue(const ValueType &value)
{
    this->pushBack(value);
}

template<class ValueType>
void SinglyLinkedListQueue<ValueType>::dequeue()
{
    this->removeFront();
}

template<class ValueType>
ValueType& SinglyLinkedListQueue<ValueType>::front() const
{
    return this->getFirstNode()->value;
}
template<class ValueType>
size_t SinglyLinkedListQueue<ValueType>::size() const
{
    return this->sizeList();
}
template<class ValueType>
bool SinglyLinkedListQueue<ValueType>::isEmpty() const
{
    return this->size() == 0;
}