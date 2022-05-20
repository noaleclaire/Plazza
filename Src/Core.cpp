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

static std::size_t kitchenId = 1;
float Core::_multiplier;

void Core::managePlazza(float multiplier, std::size_t nbCooks, std::size_t replaceTime)
{
    Parser parser;
    std::vector<std::shared_ptr<Pizza>> pizzas;

    Core::_multiplier = multiplier;
    while(1) {
        parser.manageCommandLine();
        pizzas = parser.getPizzas();
        while (1) {
            for (auto &p : pizzas) {
                for (auto &k : _kitchens) {
                    if (k->addPizza(p)) {
                        auto it = std::find(pizzas.begin(), pizzas.end(), p);
                        pizzas.erase(it);
                    }
                    k->update();
                }
            }
            if (pizzas.size() != 0) {
                _kitchens.push_back(std::make_shared<Kitchen>(Kitchen(kitchenId, nbCooks, replaceTime)));
                kitchenId++;
            } else {
                break;
            }
        }
        checkKitchens();
    }
}

void Core::checkKitchens()
{
    for (auto &k : _kitchens) {
        if (k->isClose()) {
            auto it = std::find(_kitchens.begin(), _kitchens.end(), k);
            _kitchens.erase(it);
        }
    }
}