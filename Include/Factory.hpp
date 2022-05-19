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
        static std::shared_ptr<Pizza> createMargarita(const std::string size);
        static std::shared_ptr<Pizza> createRegina(const std::string size);
        static std::shared_ptr<Pizza> createAmericana(const std::string size);
        static std::shared_ptr<Pizza> createFantasia(const std::string size);
};