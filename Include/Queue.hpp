/*
** EPITECH PROJECT, 2022
** Queue
** File description:
** Queue
*/

#pragma once

#include <vector>
#include <thread>
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "ConditionVariable.hpp"

template <typename T>
class Queue {
    public:
        Queue() = default;
        ~Queue() = default;

        void push(T value)
        {
            ScopedLock lock(&_mutex, ScopedLock::BASIC);
            _values.push_back(value);
            _size++;
            _cv.notifyOne();
        }
        bool tryPop(T &value)
        {
            ScopedLock lock(&_mutex, ScopedLock::DEFER);
            while (_values.empty())
                std::this_thread::sleep_for(std::chrono::seconds(1));
            lock.lock();
            value = _values.at(0);
            _values.erase(_values.begin());
            _size--;
            return (true);
        }
        T pop()
        {
            ScopedLock lock(&_mutex, ScopedLock::BASIC);
            T value = 0;

            _cv.wait(lock.getLock(), [this]{
                if (_values.empty())
                    return (false);
                return (true);
            });
            value = _values.at(0);
            _values.erase(_values.begin());
            _size--;
            return (value);
        }
        bool isEmptyQueue() const
        {
            return (_values.empty());
        }
        std::size_t size() const
        {
            return (_size);
        }

    protected:
    private:
        Mutex _mutex;
        ConditionVariable _cv;
        std::vector<T> _values;
        std::size_t _size = 0;
};
