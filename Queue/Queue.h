//
// Created by trykr on 01.05.2020.
//

#pragma once
#include <cstdio>
#include "QueueImplementation.h"
#include "SinglyLinkedListQueue.h"
#include "DoublyLinkedListQueue.h"
#include "VectorQueue.h"
#include <stdexcept>
// Уровень абстракции
// клиентский код подключает именно этот хедер
enum class QueueContainer {
    Vector = 0,
    SinglyLinkedList = 1,
    DoublyLinkedList = 2
    // можно дополнять другими контейнерами
};
// тип значений в стеке


// на основе какого контейнера работает стек

// декларация класса с реализацией
template<typename ValueType>
class QueueImplementation;

template<class ValueType>
class Queue
{
public:
    // Большая пятерка
    Queue(QueueContainer container = QueueContainer::Vector);
    // элементы массива последовательно подкладываются в стек
    Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container = QueueContainer::Vector);
    Queue(const Queue& copyQueue);
    Queue& operator = (const Queue& copyQueue);
    // Здесь как обычно
    Queue& operator=(Queue&& moveQueue) noexcept;
    Queue(const Queue&& moveQueue) noexcept;
    ~Queue();

    // добавление в хвост
    void enqueue(const ValueType& value);
    // удаление с головы
    void dequeue();
    // посмотреть элемент в голове
    const ValueType& front() const;
    // проверка на пустоту
    bool isEmpty() const;
    // размер
    size_t size() const;
private:
    // указатель на имплементацию (уровень реализации)
    QueueImplementation<ValueType>* _pimpl = nullptr;
    // тип контейнера, наверняка понадобится
    QueueContainer _containerType;
};

template<class ValueType>
Queue<ValueType>::Queue(QueueContainer container)
{
    this->_containerType = container;
    switch (container)
    {
        case QueueContainer::SinglyLinkedList: {
            this->_pimpl = new SinglyLinkedListQueue<ValueType>(); // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case QueueContainer::Vector: {
            this->_pimpl = new VectorQueue<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case QueueContainer::DoublyLinkedList:
        {
            this->_pimpl = new DoublyLinkedListQueue<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}
template<class ValueType>
Queue<ValueType>::Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container)
{
    this->_containerType = container;
    switch (container)
    {
        case QueueContainer::SinglyLinkedList: {
            this->_pimpl = new SinglyLinkedListQueue<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case QueueContainer::Vector: {
            this->_pimpl = new VectorQueue<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case QueueContainer::DoublyLinkedList:
        {
            this->_pimpl = new DoublyLinkedListQueue<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
    for (int i = 0; i < arraySize; i++)
    {
        _pimpl->enqueue(valueArray[i]);
    }
}
template<class ValueType>
 Queue<ValueType>::Queue(const Queue& copyQueue)
{
    _containerType = copyQueue._containerType;
    switch (_containerType) {
        case QueueContainer::SinglyLinkedList: {
            _pimpl = new SinglyLinkedListQueue<ValueType>(*(static_cast<SinglyLinkedListQueue<ValueType>*>(copyQueue._pimpl)));
            break;
        }
        case QueueContainer::DoublyLinkedList: {
            _pimpl = new DoublyLinkedListQueue<ValueType>(*(static_cast<DoublyLinkedListQueue<ValueType>*>(copyQueue._pimpl)));
            break;
        }
        case QueueContainer::Vector: {
            _pimpl = new VectorQueue<ValueType>(*(static_cast<VectorQueue<ValueType>*>(copyQueue._pimpl)));
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}
template<class ValueType>
class Queue<ValueType>& Queue<ValueType>:: operator = (const Queue& copyQueue){
    if (this == &copyQueue)
        return *this;
    delete this->_pimpl;
    switch (copyQueue._containerType) {
        case QueueContainer::SinglyLinkedList:{

            this->_pimpl = new SinglyLinkedListQueue<ValueType>(*(static_cast<SinglyLinkedListQueue<ValueType> *>(copyQueue._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case QueueContainer::Vector: {
            this->_pimpl = new VectorQueue<ValueType>(*(static_cast<VectorQueue<ValueType> *>(copyQueue._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case QueueContainer::DoublyLinkedList: {
            this->_pimpl = new DoublyLinkedListQueue<ValueType>(*(static_cast<DoublyLinkedListQueue<ValueType> *>(copyQueue._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
    return *this;
}
template<class ValueType>
class Queue<ValueType>& Queue<ValueType>:: operator=(Queue&& moveQueue) noexcept
{
    if (this == &moveQueue)
        return *this;
    this->_containerType = moveQueue._containerType;
    delete this->_pimpl;
    this->_pimpl = moveQueue._pimpl;
    return *this;
}
template<class ValueType>
Queue<ValueType>::Queue(const Queue&& moveQueue) noexcept
{
    _pimpl = moveQueue._pimpl;
}
template<class ValueType>
Queue<ValueType>::~Queue()
{
    delete _pimpl;
}
template<class ValueType>
void Queue<ValueType>::enqueue(const ValueType& value)
{
    _pimpl->enqueue(value);
}
template<class ValueType>
void Queue<ValueType>::dequeue()
{
    _pimpl->dequeue();
}
template<class ValueType>
const ValueType& Queue<ValueType>:: front() const
{
    return _pimpl->front();
}

template<class ValueType>
bool Queue<ValueType>::isEmpty() const
{
    return _pimpl->isEmpty();
}
template<class ValueType>
size_t Queue<ValueType>::size() const
{
    return _pimpl->size();
}