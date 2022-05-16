/*
** EPITECH PROJECT, 2022
** Pizza
** File description:
** Pizza
*/

#include <vector>
#include "Pizza.hpp"
#include "../Include/Exceptions/PizzaException.hpp"

static const std::vector<std::pair<std::string, PizzaType>> pizzaTypes = {
    std::make_pair("Regina", Regina), std::make_pair("Margarita", Margarita),
    std::make_pair("Americana", Americana), std::make_pair("Fantasia", Fantasia)
};

static const std::vector<std::pair<std::string, PizzaSize>> pizzaSizes = {
    std::make_pair("S", S), std::make_pair("M", M),
    std::make_pair("L", L), std::make_pair("XL", XL), std::make_pair("XXL", XXL)
};

Pizza::Pizza(std::string &pizzaType, std::string &pizzaSize)
{
    int exist = -1;

    for (int i = 0; i < pizzaTypes.size(); i++) {
        if (pizzaTypes.at(i).first.compare(pizzaType) == 0)
            exist = i;
    }
    if (exist == -1)
        throw PizzaException("This pizza type doesn't exist",
        " Error in : Pizza::Pizza(std::string &pizzaType, std::size_t &pizzaSize)");
    this->_pizzaType = pizzaTypes.at(exist).second;
    exist = -1;
    for (int i = 0; i < pizzaSizes.size(); i++) {
        if (pizzaSizes.at(i).first.compare(pizzaSize) == 0)
            exist = i;
    }
    if (exist == -1)
        throw PizzaException("This pizza size doesn't exist",
        " Error in : Pizza::Pizza(std::string &pizzaType, std::size_t &pizzaSize)");
    this->_pizzaSize = pizzaSizes.at(exist).second;
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
