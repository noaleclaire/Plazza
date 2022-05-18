/*
** EPITECH PROJECT, 2022
** Mutex
** File description:
** Mutex
*/

#pragma once

#include <mutex>

class Mutex {
    public:
        Mutex();
        ~Mutex();

        void lock(void);
        void tryLock(void);
        void unlock(void);
        std::mutex &getMutex();

    protected:
    private:
        std::mutex _mutex;
};
