/*
** EPITECH PROJECT, 2022
** Factory.cpp
** File description:
** Factory.cpp
*/

#include "../Include/Factory.hpp"

std::shared_ptr<Pizza> Factory::createPizza(std::string &type, std::string &size)
{
    return (std::make_shared<Pizza>(Pizza(type, size)));
}