/*
** EPITECH PROJECT, 2022
** Kitchen.cpp
** File description:
** Kitchen.cpp
*/

#include "../Include/Kitchen.hpp"
#include <iostream>
#include <stdexcept>

Kitchen::Kitchen(std::size_t id, std::size_t nbCooks, std::size_t replaceTime) : _id(id), _nbCooks(nbCooks),
_replaceTime(replaceTime),  _isCopy(false)
{
    _refillStart = std::chrono::system_clock::now();
    _afkStart = std::chrono::system_clock::now();
    std::cout << "The kitchen " << _id << " is now open !" << std::endl;
    for (std::size_t increm = 0; increm < nbCooks; increm++) {
        _cooks.push_back(std::make_shared<Cook>(Cook(increm + 1, _id)));
        _cooks.at(increm)->create(_pizzas);
        _cooks.at(increm)->join();
    }
}

// Kitchen::Kitchen(Kitchen const &other)
// {
//     _isCopy = true;
//     _id = other._id;
//     _nbCooks = other._nbCooks;
//     _replaceTime = other._replaceTime;
//     _cooks = other._cooks;
//     _afkStart = other._afkStart;
//     _stock = other._stock;
//     _refillStart = other._refillStart;
// }

Kitchen::~Kitchen()
{
    if (!_isCopy)
        std::cout << "The kitchen " << _id << " closes its doors..." << std::endl;
}

bool Kitchen::addPizza(std::shared_ptr<Pizza> pizza)
{
    if (_pizzas.size() == 2 * _nbCooks)
        return (false);
    _pizzas.push(pizza);
    return (true);
}

void Kitchen::update()
{
    isRefill();
    if (!AreAllCooksAvailable())
        _afkStart = std::chrono::system_clock::now();
}

bool Kitchen::isClose() const
{
    if ((std::chrono::system_clock::now() - _afkStart) >= std::chrono::seconds(5))
        return (true);
    return (false);
}

bool Kitchen::isRefill()
{
    if ((std::chrono::system_clock::now() - _refillStart) >= std::chrono::milliseconds(_replaceTime)) {
        refill();
        _refillStart = std::chrono::system_clock::now();
        return (true);
    }
    return (false);
}

bool Kitchen::AreAllCooksAvailable() const
{
    for (auto const &c : _cooks) {
        if (c->getBaking()) {
            return (false);
        }
    }
    return (true);
}

bool Kitchen::isThereAvailableCooks() const
{
    for (auto const &c : _cooks) {
        if (!c->getBaking())
            return (true);
    }
    return (false);
}

bool Kitchen::isIngredientAvailable(std::vector<Ingredients> ingredients)
{
    for (auto &i : ingredients) {
        for (auto &s : _stock) {
            if (s.first.getName().compare(i.getName()) == 0 && s.second == 0) {
                return (false);
            }
        }
    }
    return (true);
}

void Kitchen::consumeIngredients(std::vector<Ingredients> ingredients)
{
    for (auto &i : ingredients) {
        for (auto &s : _stock) {
            if (s.first.getName().compare(i.getName()) == 0) {
                s.second--;
            }
        }
    }
}

void Kitchen::refill()
{
    for (auto &s : _stock)
        s.second = 5;
}