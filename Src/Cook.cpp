/*
** EPITECH PROJECT, 2022
** Cook.cpp
** File description:
** Cook.cpp
*/

#include "../Include/Cook.hpp"
#include "../Include/Core.hpp"
#include "../Include/Kitchen.hpp"
#include <stdexcept>
#include <memory>
#include <cmath>
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

void Cook::create(Queue<std::shared_ptr<Pizza>> &pizzas)
{
    _thread.create(&Cook::handlePizzas, this, std::ref(pizzas));
}

void Cook::join()
{
    _thread.join();
}

void Cook::handlePizzas(Queue<std::shared_ptr<Pizza>> &pizzas)
{
    // while (!Core::_kitchens.at(_kitchenId)->isClose()) {
    //     auto pizza = pizzas.pop();
    //     while (!Core::_kitchens.at(_kitchenId)->isIngredientAvailable(pizza->getIngredients()));
    //     std::cout << "[Kitchen " << _kitchenId << "] Cook " << _id << ": starts baking the pizza " << pizza->getPizzaType() << "." << std::endl;
    //     Core::_kitchens.at(_kitchenId)->consumeIngredients(pizza->getIngredients());
    //     _baking = true;
    //     pizza->setPizzaBaked(Pizza::IN_PROGRESS);
    //     std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    //     while ((std::chrono::system_clock::now() - start) < std::chrono::milliseconds(std::lround(pizza->getBakedTime() * 1000 * Core::_multiplier)));
    //     std::cout << "[Kitchen " << _kitchenId << "] Cook " << _id << ": finished baking the pizza " << pizza->getPizzaType() << "." << std::endl;
    //     _baking = false;
    //     pizza->setPizzaBaked(Pizza::YES);
    // }
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