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
#include <cmath>

static std::size_t kitchenId = 1;
float Core::_multiplier;
std::map<std::size_t, Kitchen *> Core::_kitchens;

void Core::managePlazza(float multiplier, std::size_t nbCooks, std::size_t replaceTime)
{
    Parser parser;
    std::vector<std::shared_ptr<Pizza>> pizzas;
    Queue<std::shared_ptr<Pizza>> safePizzas;
    std::map<std::size_t, Thread *> threads;
    std::map<std::size_t, Arg<Kitchen, Queue<std::shared_ptr<Pizza>>>> threadArgs;

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
                threadArgs.insert(std::make_pair(kitchenId, Arg<Kitchen, Queue<std::shared_ptr<Pizza>>>(std::ref(*_kitchens.at(kitchenId)), std::ref(safePizzas))));
                threads.insert(std::make_pair(kitchenId, new Thread));
                threads.at(kitchenId)->create(&Core::producer, std::ref(threadArgs.at(kitchenId)));
                if (threads.at(kitchenId)->joinable())
                    threads.at(kitchenId)->join();
                // Core::_kitchens.at(kitchenId)->createAndJoinCook(std::ref(safePizzas));
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

void Core::producer(Arg<Kitchen, Queue<std::shared_ptr<Pizza>>> &args)
{
    Kitchen &kitchen = args.getArg1();
    Queue<std::shared_ptr<Pizza>> &pizzas = args.getArg2();

    while (!kitchen.isClose()) {
        if (!pizzas.isEmptyQueue()) {
            auto pizza = pizzas.pop();
            if (!kitchen.addPizza(pizza))
                pizzas.push(pizza);
        }
        kitchen.update();
    }
    kitchen.getPizzas().quit();
    std::cout << "close" << std::endl;
}

void Core::consumer(Arg<Kitchen, std::size_t> &args)
{
    Kitchen &kitchen = args.getArg1();
    std::size_t id = args.getArg2();

    while (!kitchen.isClose()) {
        std::cout << "size before " << kitchen.getPizzas().size() << std::endl;
        kitchen.getThreadAt(id).setStatus(Thread::ThreadStatus::WAIT);
        auto pizza = kitchen.getPizzas().pop();
        std::cout << "after size " << kitchen.getPizzas().size() << std::endl;
        if (pizza == nullptr)
            break;
        std::cout << "Cook " << id << " is preparing the pizza" << std::endl;
        while (!kitchen.isIngredientAvailable(pizza->getIngredients()));
        kitchen.getThreadAt(id).setStatus(Thread::ThreadStatus::OCCUPIED);
        std::cout << "[Kitchen " << kitchen.getId() << "] starts baking the pizza " << pizza->getPizzaType() << "." << std::endl;
        kitchen.consumeIngredients(pizza->getIngredients());
        pizza->setPizzaBaked(Pizza::IN_PROGRESS);
        std::this_thread::sleep_for(std::chrono::milliseconds(std::lround(pizza->getBakedTime() * 1000 * Core::_multiplier)));
        std::cout << "[Kitchen " << kitchen.getId() << "] finished baking the pizza " << pizza->getPizzaType() << "." << std::endl;
        pizza->setPizzaBaked(Pizza::YES);
    }
    std::cout << "close pizza cook " << kitchen.getId() << std::endl;
}
