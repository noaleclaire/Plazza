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
std::map<std::size_t, Kitchen *> Core::_kitchens;

void Core::managePlazza(float multiplier, std::size_t nbCooks, std::size_t replaceTime)
{
    Parser parser;
    std::vector<std::shared_ptr<Pizza>> pizzas;

    Core::_multiplier = multiplier;
    while(1) {
        std::cout << "test" << std::endl;
        parser.manageCommandLine();
        pizzas = parser.getPizzas();
        while (1) {
            std::cout << "test2" << std::endl;
            for (auto &p : pizzas) {
                for (auto &k : Core::_kitchens) {
                    if (k.second->addPizza(p)) {
                        auto it = std::find(pizzas.begin(), pizzas.end(), p);
                        pizzas.erase(it);
                    }
                    k.second->update();
                }
            }
            if (pizzas.size() != 0) {
                Core::_kitchens.insert(std::make_pair(kitchenId, new Kitchen(kitchenId, nbCooks, replaceTime)));
                Core::_kitchens.at(kitchenId)->createAndJoinCook();
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
    for (auto &k : Core::_kitchens) {
        if (k.second->isClose()) {
            auto it = std::find(Core::_kitchens.begin(), Core::_kitchens.end(), k);
            Core::_kitchens.erase(it);
        }
    }
}