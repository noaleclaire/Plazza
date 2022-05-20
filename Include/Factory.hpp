/*
** EPITECH PROJECT, 2022
** Factory.hpp
** File description:
** Factory.hpp
*/

#pragma once

#include <memory>
#include "Pizza.hpp"

class Factory {
    public:
        static std::shared_ptr<Pizza> createPizza(std::string &type, std::string &size);

    protected:
    private:
};