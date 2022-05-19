/*
** EPITECH PROJECT, 2022
** Pizza
** File description:
** Pizza
*/

#include <map>
#include <stdexcept>
#include "../Include/Pizza.hpp"
#include "../Include/Exceptions/PizzaException.hpp"

static const std::map<std::string, std::pair<PizzaType, std::size_t>> pizzaTypes = {
    std::make_pair("regina", std::make_pair(Regina, 2)),
    std::make_pair("margarita", std::make_pair(Margarita, 1)),
    std::make_pair("americana", std::make_pair(Americana, 2)),
    std::make_pair("fantasia", std::make_pair(Fantasia, 4))
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

void Pizza::setPizzaBaked(PizzaBaked pizzaBaked)
{
    _pizzaBaked = pizzaBaked;
}

void Pizza::setIngredients()
{
    switch (_pizzaType)
    {
    case Regina:
        _ingredients.push_back(Ingredients(Ingredients::DOE));
        _ingredients.push_back(Ingredients(Ingredients::TOMATO));
        _ingredients.push_back(Ingredients(Ingredients::GRUYERE));
        _ingredients.push_back(Ingredients(Ingredients::HAM));
        _ingredients.push_back(Ingredients(Ingredients::MUSHROOM));
        break;
    case Margarita:
        _ingredients.push_back(Ingredients(Ingredients::DOE));
        _ingredients.push_back(Ingredients(Ingredients::TOMATO));
        _ingredients.push_back(Ingredients(Ingredients::GRUYERE));
        break;
    case Americana:
        _ingredients.push_back(Ingredients(Ingredients::DOE));
        _ingredients.push_back(Ingredients(Ingredients::TOMATO));
        _ingredients.push_back(Ingredients(Ingredients::GRUYERE));
        _ingredients.push_back(Ingredients(Ingredients::STEAK));
        break;
    case Fantasia:
        _ingredients.push_back(Ingredients(Ingredients::DOE));
        _ingredients.push_back(Ingredients(Ingredients::TOMATO));
        _ingredients.push_back(Ingredients(Ingredients::EGGPLANT));
        _ingredients.push_back(Ingredients(Ingredients::GOAT_CHEESE));
        _ingredients.push_back(Ingredients(Ingredients::CHIEF_LOVE));
        break;
    default:
        break;
    }
}

std::vector<Ingredients> Pizza::getIngredients() const
{
    return (_ingredients);
}
