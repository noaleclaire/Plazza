/*
** EPITECH PROJECT, 2022
** Kitchen.cpp
** File description:
** Kitchen.cpp
*/

#include "../Include/Kitchen.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "../Include/Core.hpp"

Kitchen::Kitchen(std::size_t id, std::size_t nbCooks, std::size_t replaceTime) : _id(id), _nbCooks(nbCooks),
_replaceTime(replaceTime), _isCopy(false)
{
    _refillStart = std::chrono::system_clock::now();
    _afkStart = std::chrono::system_clock::now();
    _stock.push_back(std::make_pair(Ingredients(Ingredients::Ingredient::DOE), 5));
    _stock.push_back(std::make_pair(Ingredients(Ingredients::Ingredient::TOMATO), 5));
    _stock.push_back(std::make_pair(Ingredients(Ingredients::Ingredient::GRUYERE), 5));
    _stock.push_back(std::make_pair(Ingredients(Ingredients::Ingredient::HAM), 5));
    _stock.push_back(std::make_pair(Ingredients(Ingredients::Ingredient::MUSHROOM), 5));
    _stock.push_back(std::make_pair(Ingredients(Ingredients::Ingredient::STEAK), 5));
    _stock.push_back(std::make_pair(Ingredients(Ingredients::Ingredient::EGGPLANT), 5));
    _stock.push_back(std::make_pair(Ingredients(Ingredients::Ingredient::GOAT_CHEESE), 5));
    _stock.push_back(std::make_pair(Ingredients(Ingredients::Ingredient::CHIEF_LOVE), 5));
    Core::_file << "[Kitchen " << _id << "] Is now open !" << std::endl;
    for (std::size_t increm = 0; increm < nbCooks; increm++) {
        _cooks.push_back(std::make_shared<Cook>(Cook(increm + 1, _id)));
    }
}

Kitchen::~Kitchen()
{
}

void Kitchen::cookInfo() const
{
    int i = 0;

    for (const auto &c : _cooks) {
        std::cout << "The cook n°" << c->getId() << ":";
        if (c->getBaking() == true) {
            std::cout << " is baking a pizza." << std::endl;
        } else  {
            std::cout << " do nothing." << std::endl;
        }
    }
}

void Kitchen::kitchenInfo() const
{
    std::cout << "Ingredients available: " << std::endl;
    for (auto &s : _stock) {
        std::cout << "\t- " << s.first.getName() << " quantity: " << s.second << std::endl;
    }
}

void Kitchen::createAndJoinCook(Queue<std::shared_ptr<Pizza>> &pizza)
{
    _thread.create(&Kitchen::handleKitchen, this, std::ref(pizza));
    for (const auto &c : _cooks) {
        c->create(_pizzas);
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
    _pizzas.quit();
    Core::_file << "[Kitchen " << _id << "] Closes its doors..." << std::endl;
}

bool Kitchen::addPizza(std::shared_ptr<Pizza> &pizza)
{
    int nbCooksOccupied = 0;

    for (auto const &c : _cooks) {
        if (c->getBaking())
            nbCooksOccupied++;
    }
    if (_pizzas.size() + nbCooksOccupied == 2 * _nbCooks)
        return (false);
    _pizzas.push(pizza);
    return (true);
}

void Kitchen::update()
{
    isRefill();
    if (!areAllCooksAvailable())
        _afkStart = std::chrono::system_clock::now();
}

bool Kitchen::isClose() const
{
    if ((std::chrono::system_clock::now() - _afkStart) >= std::chrono::seconds(5)) {
        return (true);
    }
    return (false);
}

bool Kitchen::isFull() const
{
    int nbCooksOccupied = 0;

    for (auto const &c : _cooks) {
        if (c->getBaking())
            nbCooksOccupied++;
    }
    if (_pizzas.size() + nbCooksOccupied == 2 * _nbCooks)
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

bool Kitchen::areAllCooksAvailable() const
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
        if (!c->getBaking()) {
            return (true);
        }
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

std::size_t Kitchen::getId()
{
    return _id;
}