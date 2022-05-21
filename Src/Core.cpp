/*
** EPITECH PROJECT, 2022
** Core.cpp
** File description:
** Core.cpp
*/

#include "../Include/Core.hpp"
#include "../Include/Parser.hpp"
#include <algorithm>
#include <iostream>
#include <unistd.h>

static std::size_t kitchenId = 1;
float Core::_multiplier;
std::map<std::size_t, Kitchen *> Core::_kitchens;

void Core::managePlazza(float multiplier, std::size_t nbCooks, std::size_t replaceTime)
{
    Parser parser;
    std::vector<std::shared_ptr<Pizza>> pizzas;
    Queue<std::shared_ptr<Pizza>> safePizzas;

    Core::_multiplier = multiplier;
    while(1) {
        std::cout << "test" << std::endl;
        parser.manageCommandLine();
        pizzas = parser.getPizzas();
        insertPizzaInQueue(pizzas, safePizzas);
        std::cout << "safe " << safePizzas.size() << std::endl;
        while (safePizzas.size() != 0) {
            std::cout << "test " << pizzas.size() << std::endl;
            if (isAllKitchensFull()) {
                std::cout << "b" << std::endl;
                Core::_kitchens.insert(std::make_pair(kitchenId, new Kitchen(kitchenId, nbCooks, replaceTime)));
                Core::_kitchens.at(kitchenId)->createAndJoinCook(std::ref(safePizzas));
                kitchenId++;
            }
        }
        std::cout << "test2" << std::endl;
        checkKitchens();
        std::cout << "test3" << std::endl;
    }
    for (auto &k : _kitchens)
        delete k.second;
}

void Core::checkKitchens()
{
    for (auto &k : Core::_kitchens) {
        if (k.second->isClose()) {
            auto it = std::find(Core::_kitchens.begin(), Core::_kitchens.end(), k);
            Core::_kitchens.erase(it);
        }
        if (_kitchens.size() == 0)
            break;
    }
}

bool Core::isAllKitchensFull()
{
    for (auto const &k : Core::_kitchens) {
        if (!k.second->isFull())
            return (false);
    }
    return (true);
}

void Core::insertPizzaInQueue(std::vector<std::shared_ptr<Pizza>> &pizzas, Queue<std::shared_ptr<Pizza>> &safePizzas)
{
    for (auto &p : pizzas) {
        safePizzas.push(p);
    }
}