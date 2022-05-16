/*
** EPITECH PROJECT, 2022
** Cook.hpp
** File description:
** Cook.hpp
*/

#pragma once

#include <threads.h>
#include "Pizza.hpp"

class Cook {
    public:
        Cook();
        ~Cook() = default;

        void create(void *(*fptr)(void *), Pizza &arg);
        void join();

    protected:
    private:
        pthread_t _thread;
};