/*
** EPITECH PROJECT, 2022
** Cook.cpp
** File description:
** Cook.cpp
*/

#include "Cook.hpp"
#include <stdexcept>

Cook::Cook()
{
}

extern "C"
{
    void Cook::create(void *(*fptr)(void *), Pizza &arg)
    {
        if (pthread_create(&_thread, NULL, fptr, &arg) == -1)
            throw std::runtime_error("Error when creating the thread.");
    }

    void Cook::join()
    {
        if (pthread_join(_thread, NULL) == -1)
            throw std::runtime_error("Error when running the thread.");
    }
}