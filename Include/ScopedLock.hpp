/*
** EPITECH PROJECT, 2022
** ScopedLock
** File description:
** ScopedLock
*/

#pragma once

#include "Mutex.hpp"

class ScopedLock {
    public:
        enum TypeLock {
            BASIC,
            DEFER
        };
        ScopedLock(Mutex *mutex, TypeLock type);
        ~ScopedLock();

        void lock(void);
        void tryLock(void);
        void unlock(void);
        std::unique_lock<std::mutex> &getLock();

    protected:
    private:
        Mutex *_mutex;
        std::unique_lock<std::mutex> _lock;
};
