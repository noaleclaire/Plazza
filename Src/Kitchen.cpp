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
_replaceTime(replaceTime), _isCopy(false)
{
    _refillStart = std::chrono::system_clock::now();
    _afkStart = std::chrono::system_clock::now();
    std::cout << "The kitchen " << _id << " is now open !" << std::endl;
    for (std::size_t increm = 0; increm < nbCooks; increm++)
        _cooks.push_back(std::make_shared<Cook>(Cook(increm + 1, _id)));
}

Kitchen::~Kitchen()
{
    if (!_isCopy)
        std::cout << "The kitchen " << _id << " closes its doors..." << std::endl;
}

void Kitchen::createAndJoinCook(Queue<std::shared_ptr<Pizza>> &pizza)
{
    _thread.create(&Kitchen::handleKitchen, this, std::ref(pizza));
    for (const auto &c : _cooks) {
        c->create(_pizzas);
    }
    _thread.join();
    for (const auto &c : _cooks) {
        c->join();
    }
}

void Kitchen::handleKitchen(Queue<std::shared_ptr<Pizza>> &pizzas)
{
    while (!isClose()) {
        if (!pizzas.isEmptyQueue()) {
            auto pizza = pizzas.pop();
            if (!addPizza(pizza))
                pizzas.push(pizza);
        }
        update();
    }
    std::cout << "close" << std::endl;
}

bool Kitchen::addPizza(std::shared_ptr<Pizza> &pizza)
{
    if (_pizzas.size() == 2 * _nbCooks)
        return (false);
    _pizzas.push(pizza);
    return (true);
}

void Kitchen::update()
{
    // isRefill();
    if (!AreAllCooksAvailable())
        _afkStart = std::chrono::system_clock::now();
}

bool Kitchen::isClose() const
{
    // if ((std::chrono::system_clock::now() - _afkStart) >= std::chrono::seconds(5)) {
    //     std::cout << "oui" << std::endl;
    //     return (true);
    // }
    return (false);
}

bool Kitchen::isFull() const
{
    if (_pizzas.size() == 2 * _nbCooks)
        return (false);
    return (true);
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