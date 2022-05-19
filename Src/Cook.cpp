/*
** EPITECH PROJECT, 2022
** Cook.cpp
** File description:
** Cook.cpp
*/

#include "../Include/Cook.hpp"
#include <stdexcept>
#include <memory>
#include <iostream>

Cook::Cook(std::size_t id, std::size_t kitchenId) : _id(id), _kitchenId(kitchenId)
{
    _baking = false;
}

Cook::Cook(Cook const &other)
{
    _id = other.getId();
    _kitchenId = other.getKitchenId();
    _baking = other.getBaking();
}

Cook &Cook::operator=(Cook const &other)
{
    _id = other.getId();
    _kitchenId = other.getKitchenId();
    _baking = other.getBaking();
    return (*this);
}

void Cook::cookPizza(std::shared_ptr<Pizza> pizza)
{
    if (!_baking) {
        _thread.detach();
        _thread.create(&Cook::bakePizza, this, pizza);
        _thread.join();
    }
}

void Cook::bakePizza(std::shared_ptr<Pizza> pizza)
{
    std::cout << "[Kitchen " << getKitchenId() << "] Cook " << getId() << ": starts baking the pizza " << pizza->getPizzaType() << "." << std::endl;
    setBaking(true);
    pizza->setPizzaBaked(Pizza::IN_PROGRESS);
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    while ((std::chrono::system_clock::now() - start) < std::chrono::seconds(pizza->getBakedTime()));
    std::cout << "[Kitchen " << getKitchenId() << "] Cook " << getId() << ": finished baking the pizza " << pizza->getPizzaType() << "." << std::endl;
    setBaking(false);
    pizza->setPizzaBaked(Pizza::YES);
}

bool Cook::getBaking() const
{
    return (_baking);
}

std::size_t Cook::getKitchenId() const
{
    return (_kitchenId);
}

std::size_t Cook::getId() const
{
    return (_id);
}

void Cook::setBaking(bool baking)
{
    _baking = baking;
}