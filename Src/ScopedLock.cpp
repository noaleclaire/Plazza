/*
** EPITECH PROJECT, 2022
** ScopedLock
** File description:
** ScopedLock
*/

#include <utility>
#include "../Include/ScopedLock.hpp"

ScopedLock::ScopedLock(Mutex *mutex, TypeLock type) : _mutex(mutex)
{
    if (type == BASIC) {
        std::unique_lock<std::mutex> lock(_mutex->getMutex());
        _lock = std::move(lock);
    }
    if (type == DEFER) {
        std::unique_lock<std::mutex> lock(_mutex->getMutex(), std::defer_lock);
        _lock = std::move(lock);
    }
}

ScopedLock::~ScopedLock()
{
}

std::unique_lock<std::mutex> &ScopedLock::getLock()
{
    return (_lock);
}

void ScopedLock::lock(void)
{
    _lock.lock();
}

void ScopedLock::tryLock(void)
{
    _lock.try_lock();
}

void ScopedLock::unlock(void)
{
    _lock.unlock();
}
