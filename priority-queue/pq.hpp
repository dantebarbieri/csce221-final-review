#pragma once

template <class T>
class PQ {
public:
    virtual const T& top() const = 0;
    virtual void push(const T& data) = 0;
    virtual void pop() = 0;
};
