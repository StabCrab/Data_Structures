//
// Created by trykr on 10.06.2020.
//

#ifndef QUEUE_DOUBLYLISTQUEUE_H
#define QUEUE_DOUBLYLISTQUEUE_H
#include <stdlib.h>
#include "DoublyLinkedList.h"
#include "QueueImplementation.h"
template<class ValueType>
class DoublyLinkedListQueue : public QueueImplementation<ValueType>, public DoublyLinkedList<ValueType>
{
public:
    void enqueue(const ValueType &value) override;
    void dequeue() override;
    ValueType& front() const override;
    size_t size() const override;
    bool isEmpty() const override;
};

template<class ValueType>
void DoublyLinkedListQueue<ValueType>::enqueue(const ValueType &value)
{
    this->pushBack(value);
}

template<class ValueType>
void DoublyLinkedListQueue<ValueType>::dequeue()
{
    this->removeFront();
}

template<class ValueType>
ValueType& DoublyLinkedListQueue<ValueType>::front() const
{
    return this->getFirstNode()->value;
}
template<class ValueType>
size_t DoublyLinkedListQueue<ValueType>::size() const
{
    return this->sizeList();
}
template<class ValueType>
bool DoublyLinkedListQueue<ValueType>::isEmpty() const
{
    return this->sizeList() == 0;
}
#endif //QUEUE_DOUBLYLISTQUEUE_H
