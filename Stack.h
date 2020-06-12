//
// Created by trykr on 01.05.2020.
//

#pragma once
#include <cstdio>
#include "StackImplementation.h"
#include "SinglyLinkedListStack.h"
#include "DoublyLinkedListStack.h"
#include "VectorStack.h"
#include <stdexcept>
// Уровень абстракции
// клиентский код подключает именно этот хедер
enum class StackContainer {
    Vector = 0,
    SinglyLinkedList = 1,
    DoublyLinkedList = 2,
    List = 3
    // можно дополнять другими контейнерами
};
// тип значений в стеке


// на основе какого контейнера работает стек

// декларация класса с реализацией
template<typename ValueType>
class StackImplementation;

template<class ValueType>
class Stack
{
public:
    // Большая пятерка
    Stack(StackContainer container = StackContainer::Vector);
    // элементы массива последовательно подкладываются в стек
    Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container = StackContainer::Vector);
    Stack(const Stack& copyStack);
    Stack& operator = (const Stack& copyStack);
    // Здесь как обычно
    Stack& operator=(Stack&& moveStack) noexcept;
    Stack(const Stack&& moveStack) noexcept;
    ~Stack();

    // добавление в хвост
    void push(const ValueType& value);
    // удаление с головы
    void pop();
    // посмотреть элемент в голове
    const ValueType& top() const;
    // проверка на пустоту
    bool isEmpty() const;
    // размер
    size_t size() const;
private:
    // указатель на имплементацию (уровень реализации)
    StackImplementation<ValueType>* _pimpl = nullptr;
    // тип контейнера, наверняка понадобится
    StackContainer _containerType;
};

template<class ValueType>
Stack<ValueType>::Stack(StackContainer container)
{
    this->_containerType = container;
    switch (container)
    {
        case StackContainer::SinglyLinkedList: {
            this->_pimpl = new SinglyLinkedListStack<ValueType>(); // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::Vector: {
            this->_pimpl = new VectorStack<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::DoublyLinkedList:
        {
            this->_pimpl = new DoublyLinkedListStack<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::List:
        {
            this->_pimpl = new SinglyLinkedListStack<ValueType>(); // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}
template<class ValueType>
Stack<ValueType>::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container)
{
    this->_containerType = container;
    switch (container)
    {
        case StackContainer::SinglyLinkedList: {
            this->_pimpl = new SinglyLinkedListStack<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::Vector: {
            this->_pimpl = new VectorStack<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::DoublyLinkedList:
        {
            this->_pimpl = new DoublyLinkedListStack<ValueType>();	// конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::List:
        {
            this->_pimpl = new SinglyLinkedListStack<ValueType>(); // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
    for (int i = 0; i < arraySize; i++)
    {
        _pimpl->push(valueArray[i]);
    }
}
template<class ValueType>
 Stack<ValueType>::Stack(const Stack& copyStack)
{
    _containerType = copyStack._containerType;
    switch (_containerType) {
        case StackContainer::SinglyLinkedList: {
            _pimpl = new SinglyLinkedListStack<ValueType>(*(static_cast<SinglyLinkedListStack<ValueType>*>(copyStack._pimpl)));
            break;
        }
        case StackContainer::DoublyLinkedList: {
            _pimpl = new DoublyLinkedListStack<ValueType>(*(static_cast<DoublyLinkedListStack<ValueType>*>(copyStack._pimpl)));
            break;
        }
        case StackContainer::Vector: {
            _pimpl = new VectorStack<ValueType>(*(static_cast<VectorStack<ValueType>*>(copyStack._pimpl)));
            break;
        }
        case StackContainer::List: {
            _pimpl = new SinglyLinkedListStack<ValueType>(*(static_cast<SinglyLinkedListStack<ValueType>*>(copyStack._pimpl)));
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
}
template<class ValueType>
class Stack<ValueType>& Stack<ValueType>:: operator = (const Stack& copyStack){
    if (this == &copyStack)
        return *this;
    delete this->_pimpl;
    switch (copyStack._containerType) {
        case StackContainer::SinglyLinkedList:{

            this->_pimpl = new SinglyLinkedListStack<ValueType>(*(static_cast<SinglyLinkedListStack<ValueType> *>(copyStack._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::Vector: {
            this->_pimpl = new VectorStack<ValueType>(*(static_cast<VectorStack<ValueType> *>(copyStack._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::DoublyLinkedList: {
            this->_pimpl = new DoublyLinkedListStack<ValueType>(*(static_cast<DoublyLinkedListStack<ValueType> *>(copyStack._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        case StackContainer::List:{

            this->_pimpl = new SinglyLinkedListStack<ValueType>(*(static_cast<SinglyLinkedListStack<ValueType> *>(copyStack._pimpl)));    // конкретизируйте под ваши конструкторы, если надо
            break;
        }
        default:
            throw std::runtime_error("Неизвестный тип контейнера");
    }
    return *this;
}
template<class ValueType>
class Stack<ValueType>& Stack<ValueType>:: operator=(Stack&& moveStack) noexcept
{
    if (this == &moveStack)
        return *this;
    this->_containerType = moveStack._containerType;
    delete this->_pimpl;
    this->_pimpl = moveStack._pimpl;
    return *this;
}
template<class ValueType>
Stack<ValueType>::Stack(const Stack&& moveStack) noexcept
{
    _pimpl = moveStack._pimpl;
}
template<class ValueType>
Stack<ValueType>::~Stack()
{
    delete _pimpl;
}
template<class ValueType>
void Stack<ValueType>::push(const ValueType& value)
{
    _pimpl->push(value);
}
template<class ValueType>
void Stack<ValueType>::pop()
{
    _pimpl->pop();
}
template<class ValueType>
const ValueType& Stack<ValueType>:: top() const
{
    return _pimpl->top();
}

template<class ValueType>
bool Stack<ValueType>::isEmpty() const
{
    return _pimpl->isEmpty();
}
template<class ValueType>
size_t Stack<ValueType>::size() const
{
    return _pimpl->size();
}