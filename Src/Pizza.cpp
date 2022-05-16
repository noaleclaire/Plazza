/*
** EPITECH PROJECT, 2022
** Pizza
** File description:
** Pizza
*/

#include <map>
#include <stdexcept>
#include "Pizza.hpp"
#include "../Include/Exceptions/PizzaException.hpp"

static const std::map<std::string, std::pair<PizzaType, std::size_t>> pizzaTypes = {
    std::make_pair("Regina", std::make_pair(Regina, 2)),
    std::make_pair("Margarita", std::make_pair(Margarita, 1)),
    std::make_pair("Americana", std::make_pair(Americana, 2)),
    std::make_pair("Fantasia", std::make_pair(Fantasia, 4))
};

static const std::map<std::string, PizzaSize> pizzaSizes = {
    std::make_pair("S", S), std::make_pair("M", M),
    std::make_pair("L", L), std::make_pair("XL", XL),
    std::make_pair("XXL", XXL)
};

Pizza::Pizza(std::string &pizzaType, std::string &pizzaSize)
{
    int exist = -1;
    try {
        pizzaTypes.at(pizzaType);
    } catch (const std::out_of_range &e) {
        throw PizzaException("This pizza type doesn't exist",
        " Error in : Pizza::Pizza(std::string &pizzaType, std::size_t &pizzaSize)");
    }
    this->_pizzaType = pizzaTypes.at(pizzaType).first;
    this->_bakedTime = pizzaTypes.at(pizzaType).second;
    try {
        pizzaSizes.at(pizzaSize);
    } catch (const std::out_of_range &e) {
        throw PizzaException("This pizza size doesn't exist",
        " Error in : Pizza::Pizza(std::string &pizzaType, std::size_t &pizzaSize)");
    }
    this->_pizzaSize = pizzaSizes.at(pizzaSize);
}

Pizza::~Pizza()
{
}

PizzaType Pizza::getPizzaType() const
{
    return (this->_pizzaType);
}

PizzaSize Pizza::getPizzaSize() const
{
    return (this->_pizzaSize);
}

Pizza::PizzaBaked Pizza::getPizzaBaked() const
{
    return (this->_pizzaBaked);
}

size_t Pizza::getBakedTime() const
{
    return (this->_bakedTime);
}
