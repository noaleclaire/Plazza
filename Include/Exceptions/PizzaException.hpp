/*
** EPITECH PROJECT, 2022
** PizzaException
** File description:
** PizzaException
*/

#pragma once

#include "PlazzaException.hpp"

class PizzaException : public PlazzaException {
    public:
        PizzaException(const std::string &message, const std::string &location) : PlazzaException(message, location) {};
        ~PizzaException() = default;

    protected:
    private:
};
