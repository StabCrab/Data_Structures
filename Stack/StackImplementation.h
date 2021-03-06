//
// Created by trykr on 01.05.2020.
//

#pragma once
#include <cstdio>

template<class ValueType>
class StackImplementation {
public:
    // добавление в хвост
    virtual void push(const ValueType& value) = 0;
    // удаление с головы
    virtual void pop() = 0;
    // посмотреть элемент в голове(элемент в голове - это очень важный элемент!)
    virtual ValueType& top() const = 0;
    // проверка на пустоту
    virtual bool isEmpty() const = 0;
    // размер
    virtual size_t size() const = 0;
    // виртуальный деструктор
    virtual ~StackImplementation() = default;;
};

