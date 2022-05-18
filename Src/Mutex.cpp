/*
** EPITECH PROJECT, 2022
** Mutex
** File description:
** Mutex
*/

#include "../Include/Mutex.hpp"

Mutex::Mutex()
{
}

Mutex::~Mutex()
{
}

std::mutex &Mutex::getMutex()
{
    return (_mutex);
}

void Mutex::lock(void)
{
    _mutex.lock();
}

void Mutex::tryLock(void)
{
    _mutex.try_lock();
}

void Mutex::unlock(void)
{
    _mutex.unlock();
}
