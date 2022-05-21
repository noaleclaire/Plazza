/*
** EPITECH PROJECT, 2022
** Queue
** File description:
** Queue
*/

#pragma once

#include <vector>
#include <thread>
#include <stdexcept>
#include <iostream>
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
            std::unique_lock<std::mutex> lock(mutex);
            // ScopedLock lock(&_mutex, ScopedLock::BASIC);
            std::cout << "là1" << std::endl;
            _values.push_back(value);
            _size++;
            cv.notify_one();
            // _cv.notifyOne();
        }
        bool tryPop(T &value)
        {
            std::unique_lock<std::mutex> lock(mutex, std::defer_lock);
            // ScopedLock lock(&_mutex, ScopedLock::DEFER);
            while (_values.empty())
                std::this_thread::sleep_for(std::chrono::seconds(1));
            lock.lock();
            // lock.lock();
            value = _values.at(0);
            _values.erase(_values.begin());
            _size--;
            return (true);
        }
        T pop()
        {
            std::unique_lock<std::mutex> lock(mutex);
            // ScopedLock lock(&_mutex, ScopedLock::BASIC);
            T value = 0;

            std::cout << "wsh1" << std::endl;
            cv.wait(lock, [this]{
                if (_mustQuit)
                    return (true);
                if (_values.empty())
                    return (false);
                return (true);
            });
            // _cv.wait(lock.getLock(), [this]{
            //     if (_values.empty())
            //         return (false);
            //     return (true);
            // });
            std::cout << "wsh2" << std::endl;
            if (!_mustQuit) {
                value = _values.at(0);
                _values.erase(_values.begin());
                _size--;
                return (value);
            }
            return (nullptr);
        }
        bool isEmptyQueue() const
        {
            return (_values.empty());
        }
        std::size_t size() const
        {
            return (_size);
        }
        void quit()
        {
            _mustQuit = true;
            cv.notify_all();
        };

    protected:
    private:
        Mutex _mutex;
        ConditionVariable _cv;
        std::vector<T> _values;
        std::size_t _size = 0;
        std::mutex mutex;
        std::condition_variable cv;
        bool _mustQuit = false;
};
