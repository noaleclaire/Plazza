/*
** EPITECH PROJECT, 2022
** Kitchen.cpp
** File description:
** Kitchen.cpp
*/

#include "../Include/Kitchen.hpp"
#include <iostream>

Kitchen::Kitchen(std::size_t id, std::size_t nbCooks, std::size_t replaceTime, std::size_t multiplier) : _id(id), _nbCooks(nbCooks),
_replaceTime(replaceTime), _multiplier(multiplier), _isCopy(false)
{
    std::cout << "The kitchen " << _id << " is now open !" << std::endl;
    for (std::size_t increm = 0; increm < nbCooks; increm++)
        _cooks.push_back(std::make_shared<Cook>(Cook(increm + 1, _id)));
}

Kitchen::Kitchen(Kitchen const &other)
{
    _isCopy = true;
    _id = other._id;
    _nbCooks = other._nbCooks;
    _replaceTime = other._replaceTime;
    _multiplier = other._multiplier;
    _cooks = other._cooks;
    _pizzas = other._pizzas;
    _afkStart = other._afkStart;
}

Kitchen::~Kitchen()
{
    if (!_isCopy)
        std::cout << "The kitchen " << _id << " closes its doors..." << std::endl;
}

bool Kitchen::addPizza(std::shared_ptr<Pizza> pizza)
{
    if (_pizzas.size() == 2 * _nbCooks)
        return (false);
    _pizzas.push_back(pizza);
    return (true);
}

void Kitchen::checkPizzas()
{
    std::vector<std::shared_ptr<Pizza>>::iterator index = _pizzas.begin();

    if (_pizzas.size() == 0)
        return;
    for (auto const &e : _pizzas) {
        if (e->getPizzaBaked() == Pizza::YES) {
            _pizzas.erase(index);
        } else {
            index++;
        }
    }
}

bool Kitchen::isClose() const
{
    if ((std::chrono::system_clock::now() - _afkStart) >= std::chrono::seconds(5))
        return (true);
    return (false);
}