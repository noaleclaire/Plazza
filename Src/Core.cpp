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
std::ofstream Core::_file;

void Core::getInfoKitchen()
{
    for (auto &k : Core::_kitchens) {
        if (!k.second->isClose()) {
            std::cout << "Kitchen n°: " << k.second->getId()
            << " informations : " << std::endl;
            k.second->cookInfo();
            k.second->kitchenInfo();
        }
    }
}

void Core::managePlazza(float multiplier, std::size_t nbCooks, std::size_t replaceTime)
{
    Parser parser;
    std::vector<std::shared_ptr<Pizza>> pizzas;
    Queue<std::shared_ptr<Pizza>> safePizzas;
    Thread thread;

    Core::_multiplier = multiplier;
    Core::_file.open("logs.txt");
    Core::_file.clear();
    while(1) {
        if (parser.hasPizza()) {
            pizzas = parser.getPizzas();
            insertPizzaInQueue(pizzas, safePizzas);
        }
        while (safePizzas.size() != 0) {
            if (isAllKitchensFull()) {
                Core::_kitchens.insert(std::make_pair(kitchenId, new Kitchen(kitchenId, nbCooks, replaceTime)));
                Core::_kitchens.at(kitchenId)->createAndJoinCook(std::ref(safePizzas));
                kitchenId++;
            }
        }
    }
    for (auto &k : _kitchens) {
        delete k.second;
    }
    Core::_file.close();
}

bool Core::isAllKitchensFull()
{
    for (auto const &k : Core::_kitchens) {
        if (!k.second->isClose() && !k.second->isFull())
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