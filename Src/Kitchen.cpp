/*
** EPITECH PROJECT, 2022
** Kitchen.cpp
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"
#include <algorithm>

Kitchen::Kitchen(std::size_t nbCooks) : _nbCooks(nbCooks)
{
    for (std::size_t increm = 0; increm < nbCooks; increm++)
        _cooks.push_back(std::make_unique<Cook>(Cook()));
}

bool Kitchen::addPizza(Pizza &pizza)
{
    _pizzas.push_back(std::make_unique<Pizza>(pizza));
}

void Kitchen::checkPizzas()
{
    std::vector<std::unique_ptr<Pizza>>::iterator index = _pizzas.begin();

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