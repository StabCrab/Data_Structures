//
// Created by trykr on 01.05.2020.
//

#pragma once
#include <cstdio>

template<class ValueType>
class QueueImplementation {
public:
    // добавление в хвост
    virtual void enqueue(const ValueType& value) = 0;
    // удаление с головы
    virtual void dequeue() = 0;
    // посмотреть элемент в голове(элемент в голове - это очень важный элемент!)
    virtual ValueType& front() const = 0;
    // проверка на пустоту
    virtual bool isEmpty() const = 0;
    // размер
    virtual size_t size() const = 0;
    // виртуальный деструктор
    virtual ~QueueImplementation() = default;;
};

