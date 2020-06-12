//
// Created by trykr on 09.06.2020.
//

#pragma once
#include <cstdlib>
#include <iostream>
#include <cassert>
template <class ValueType>
class DoublyLinkedList
{
public:
    struct Node{
    public:
        Node();
        explicit Node(const ValueType& value, Node* next = nullptr, Node* previous = nullptr);
        ~Node();

        void insertNext(const ValueType& value);
        void removeNext();

        void insertPrevious(const ValueType& value);
        void removePrevious();

        ValueType value;
        Node* next;
        Node *previous;
        void forceNodeDelete(Node* node);
    };

private:
    Node* _firstNode;
    size_t	_size;
    Node* _lastNode;

// класс узла списка
// по своей сути, может содержать любые данные,
// можно реализовать и ассоциативный массив, просто добавив
// поле с ключем в узел и, с учетом этого, поменять методы DoublyLinkedList
// (доступ по ключу, поиск по ключу и т.д.)
public:
    ////
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& copyList);
    DoublyLinkedList& operator=(const DoublyLinkedList& copyList);

    DoublyLinkedList(DoublyLinkedList&& moveList) noexcept;
    DoublyLinkedList& operator=(DoublyLinkedList&& moveList) noexcept;

    ~DoublyLinkedList();
    ////
    // доступ к значению элемента по индексу
    ValueType& operator[](const size_t pos) const;
    // доступ к узлу по индексу
    Node* getFirstNode() const;
    Node* getLastNode() const;

    Node* getNode(const size_t pos) const;
    // вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
    void insert(const size_t pos, const ValueType& value);
    // вставка элемента после узла, (O(1))
    void insertAfterNode(Node* node, const ValueType& value);
    void insertBeforeNode(Node* node, const ValueType& value);
    // вставка в конец (О(n))
    void pushBack(const ValueType& value);
    // вставка в начало (О(1))
    void pushFront(const ValueType& value);

    // удаление
    void remove(const size_t pos);
    void removeNextNode(Node* node);
    void removeFront();
    void removeBack();

    // поиск, О(n)
    long long int findIndex(const ValueType& value) const;
    Node* findNode(const ValueType& value) const;

    // разворот списка
    void reverse();
    DoublyLinkedList reverse() const;// полчение нового списка (для константных объектов)
    DoublyLinkedList getReverseList() const; // чтобы неконстантный объект тоже мог возвращать новый развернутый список

    size_t sizeList() const;
    void setSize(size_t size);

    void print(); // этот метод нужен исключительно для отладки

};

template<class ValueType>
DoublyLinkedList<ValueType>::Node::Node()
{
    this->value = ValueType();
    this->next = nullptr;
    this->previous = nullptr;
}

template<class ValueType>
DoublyLinkedList<ValueType>::Node::Node(const ValueType& value, Node* next, Node* previous)
{
    this->value = value;
    this->next = next;
    this->previous = previous;
}

template<class ValueType>
DoublyLinkedList<ValueType>::Node::~Node() {}

template<class ValueType>
void DoublyLinkedList<ValueType>::Node::insertNext(const ValueType& value)
{
    Node* newNode = new Node(value, this->next, this);
    this->next = newNode;
}
template<class ValueType>
void DoublyLinkedList<ValueType>:: Node::insertPrevious(const ValueType &value)
{
    Node* newNode = new Node(value, this, this->previous);
    this->previous = newNode;
}

template<class ValueType>
void DoublyLinkedList<ValueType>::Node::removeNext()
{
    Node* removeNode = this->next;
    Node* newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
    newNext->previous = this;
}
template<class ValueType>
void DoublyLinkedList<ValueType>::Node::removePrevious()
{
    Node* removeNode = this->previous;
    Node* newPrevious = removeNode->previous;
    delete removeNode;
    this->previous = newPrevious;
    newPrevious->next = this;
}

template<class ValueType>
void DoublyLinkedList<ValueType>::Node::forceNodeDelete(Node *node)
{
    if (node == nullptr) {
        return;
    }
    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}

template<class ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList()
{
    _lastNode = nullptr;
    _firstNode = nullptr;
    this->_size = 0;
}

template<class ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(const DoublyLinkedList& copyList)
{
    this->_size = copyList._size;
    if (this->_size == 0)
    {
        this->_lastNode = nullptr;
        this->_firstNode = nullptr;
        return;
    }
    this->_firstNode= new Node (copyList._firstNode->value);
    Node* currentNode = this->_firstNode;
    Node* currentCopyNode = copyList._firstNode;


    while (currentCopyNode->next) {
        currentCopyNode = currentCopyNode->next;
        currentNode->next = new Node(currentCopyNode->value);
        currentNode = currentNode->next;
    }
    _lastNode = currentNode;
}

template<class ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>:: operator=(const DoublyLinkedList& copyList)
{
    if (this == &copyList) {
        return *this;
    }
    DoublyLinkedList<ValueType> bufList(copyList);
    this->_size = bufList._size;
    this->_lastNode = bufList._lastNode;
    this->_firstNode = bufList._firstNode;
    return *this;
}

template<class ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(DoublyLinkedList&& moveList) noexcept
{
    this->_size = moveList._size;
    this->_firstNode = moveList._firstNode;
    this->_lastNode = moveList._lastNode;

    moveList._size = 0;
    moveList._firstNode = nullptr;
    moveList._lastNode = nullptr;
}

template<class ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(DoublyLinkedList&& moveList) noexcept
{
    if (this == &moveList) {
        return *this;
    }
    forceNodeDelete(_firstNode);
    this->_size = moveList._size;
    this->_lastNode = moveList._lastNode;
    this->_firstNode = moveList._firstNode;

    moveList._size = 0;
    moveList._lastNode= nullptr;
    moveList._firstNode = nullptr;

    return *this;
}

template<class ValueType>
DoublyLinkedList<ValueType>:: ~DoublyLinkedList()
{
    _firstNode->forceNodeDelete(this->_firstNode);
}

template<class ValueType>
ValueType& DoublyLinkedList<ValueType>:: operator[](const size_t pos) const
{
    return getNode(pos)->value;
}

template<class ValueType>
class DoublyLinkedList<ValueType>::Node* DoublyLinkedList<ValueType>::getNode(const size_t pos) const
{
    if (pos < 0) {
        throw std::out_of_range ("pos < 0");

    }
    else if (pos >= this->_size) {
        throw std::out_of_range ("pos >= this->_size");
    }

    Node* bufNode = this->_firstNode;
    for (int i = 0; i < pos; ++i) {
        bufNode = bufNode->next;
    }

    return bufNode;
}

template<class ValueType>
void DoublyLinkedList<ValueType>::insert(const size_t pos, const ValueType& value)
{
    if (pos < 0) {
        throw std::out_of_range ("pos < 0");
    }
    else if (pos > this->_size) {
        throw std::out_of_range ("pos > this->_size");
    }

    if (pos == 0) {
        pushFront(value);
    }
    else if(pos == _size )
    {
        pushBack(value);
    }
    else{
        Node* bufNode = this->_firstNode;
        for (size_t i = 0; i < pos - 1; i++)
        {
            bufNode = bufNode->next;
        }
        bufNode->insertNext(value);
        _size++;
    }
}
template<class ValueType>
void DoublyLinkedList<ValueType>::insertBeforeNode(Node *node, const ValueType &value)
{
    node->insertPrevious(value);
    this->_size++;
}
template<class ValueType>
void DoublyLinkedList<ValueType>::insertAfterNode(Node* node, const ValueType& value)
{
    node->insertNext(value);
    this->_size++;
}

template<class ValueType>
void DoublyLinkedList<ValueType>::pushBack(const ValueType& value)
{
    if (_size == 0) {
        this->_firstNode = new Node(value, nullptr, _lastNode);
        this->_lastNode = _firstNode;
    }
    else
    {
        Node* newNode = new Node(value, nullptr, _lastNode);
        _lastNode->next = newNode;
        _lastNode = newNode;
    }
    _size++;
}

template<class ValueType>
void DoublyLinkedList<ValueType>::pushFront(const ValueType& value)
{
    if (_size == 0)
    {
        this->_firstNode = new Node(value, nullptr, nullptr);
        this->_lastNode = _firstNode;
    }
    else
    {
        _firstNode->previous = new Node(value, _firstNode, nullptr);
        _firstNode = _firstNode->previous;
    }
    _size++;
}

template<class ValueType>
void DoublyLinkedList<ValueType>:: remove(const size_t pos)
{
    if (pos < 0)
        throw std::out_of_range("pos< 0");

    if (pos > this->_size)
        throw std::out_of_range ("pos > this->_size");
    if (pos == 0) {
        removeFront();
    }
    else {
        Node* node = getNode(pos - 1);
        removeNextNode(node);
    }
}
template <class ValueType>
void DoublyLinkedList<ValueType>:: removeNextNode(Node* node)
{
    Node *deletedNode = node->next;
    node->next = node->next->next;
    delete deletedNode;
    _size--;
}

template<class ValueType>
void DoublyLinkedList<ValueType>::removeFront()
{
    if (_size == 0)
    {
        throw std::runtime_error("list is empty");
    }
    Node *node = _firstNode;
    this->_firstNode = this->_firstNode->next;
    delete node;
    this->_size--;
}

template<class ValueType>
void DoublyLinkedList<ValueType>:: removeBack()
{
    Node *node = _lastNode;
    this->_lastNode = this->_lastNode;
    delete node;
    this->_size--;
}

template<class ValueType>
long long int DoublyLinkedList<ValueType>::findIndex(const ValueType& value) const
{
    long long int i = 0;
    Node *currentNode = _firstNode;
    while (i < _size)
    {
        if (currentNode->value == value)
            return i;
        i++;
        currentNode = currentNode->next;
    }
    return -1;
}

template<class ValueType>
class DoublyLinkedList<ValueType>::Node* DoublyLinkedList<ValueType>::findNode(const ValueType& value) const
{
    size_t i = 0;
    Node *currentNode = _firstNode;
    while (i < _size)
    {
        if (currentNode->value == value)
            return currentNode;
        i++;
        currentNode = currentNode->next;
    }
    return nullptr;
}
template<class ValueType>
void DoublyLinkedList<ValueType>:: reverse()
{
    Node *nextNode;
    Node *currentNode;
    Node *previousNode;
    previousNode = _firstNode;
    currentNode = _firstNode->next;
    nextNode = currentNode->next;
    _firstNode->next = nullptr;
    currentNode->next = previousNode;
    _lastNode = _firstNode;
    while (nextNode->next != nullptr)
    {
        previousNode = currentNode;
        currentNode = nextNode;
        nextNode = nextNode->next;
        currentNode->next = previousNode;
    }
    previousNode = currentNode;
    currentNode = nextNode;
    nextNode = nextNode->next;
    currentNode->next = previousNode;
    _firstNode = currentNode;
}
template<class ValueType>
DoublyLinkedList<ValueType> DoublyLinkedList<ValueType>:: reverse() const
{
    DoublyLinkedList reversedList = *this;
    reversedList.reverse();
    return reversedList;
}


template<class ValueType>
DoublyLinkedList<ValueType> DoublyLinkedList<ValueType>:: getReverseList() const
{
    return this->reverse();
}

template<class ValueType>
size_t DoublyLinkedList<ValueType> :: sizeList() const
{
    return _size;
}

template<class ValueType>
void DoublyLinkedList<ValueType>::print()
{
    Node* node = this->_firstNode;
    while(node->next != nullptr)
    {
        std::cout << node->value<< std::endl;
        node = node->next;
    }
    std::cout << node->value<< std::endl;
}

template<class ValueType>
class DoublyLinkedList<ValueType>::Node *DoublyLinkedList<ValueType>::getFirstNode() const{
    return this->_firstNode;
}

template<class ValueType>
void DoublyLinkedList<ValueType>::setSize(size_t size)
{
    this->_size = size;
}

template<class ValueType>
class DoublyLinkedList<ValueType>::Node *DoublyLinkedList<ValueType>::getLastNode() const {
    return this->_lastNode;
}
