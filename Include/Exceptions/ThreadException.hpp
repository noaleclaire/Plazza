/*
** EPITECH PROJECT, 2022
** ThreadException
** File description:
** ThreadException
*/

#pragma once

#include "PlazzaException.hpp"

class ThreadException : public PlazzaException {
    public:
        ThreadException(const std::string &message, const std::string &location) : PlazzaException(message, location) {};
        ~ThreadException();

    protected:
    private:
};
