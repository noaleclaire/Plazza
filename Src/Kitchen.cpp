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
#include "../Include/Arg.hpp"

Kitchen::Kitchen(std::size_t id, std::size_t nbCooks, std::size_t replaceTime) : _id(id), _nbCooks(nbCooks),
_replaceTime(replaceTime), _isCopy(false)
{
    std::vector<Arg<Kitchen, std::size_t> *> threadArgs;
    _refillStart = std::chrono::system_clock::now();
    _afkStart = std::chrono::system_clock::now();
    std::cout << "The kitchen " << _id << " is now open !" << std::endl;
    for (std::size_t increm = 0; increm < nbCooks; increm++) {
        _threads.push_back(new Thread);
        threadArgs.push_back(new Arg<Kitchen, std::size_t>(*this, increm));
        _threads.at(increm)->create(&Core::consumer, std::ref(*threadArgs.at(increm)));
        if (_threads.at(increm)->joinable())
            _threads.at(increm)->join();
    }
    // _cooks.push_back(std::make_shared<Cook>(Cook(increm + 1, _id)));
}

void Kitchen::handleCooks(std::size_t id)
{
    while (!isClose()) {
        std::cout << "size before " << _pizzas.size() << std::endl;
        _threads.at(id)->setStatus(Thread::ThreadStatus::WAIT);
        auto pizza = _pizzas.pop();
        std::cout << "after size " << _pizzas.size() << std::endl;
        if (pizza == nullptr)
            break;
        std::cout << "Cook " << _id << " is preparing the pizza" << std::endl;
        while (!isIngredientAvailable(pizza->getIngredients()));
        _threads.at(id)->setStatus(Thread::ThreadStatus::OCCUPIED);
        std::cout << "[Kitchen " << _id << "] starts baking the pizza " << pizza->getPizzaType() << "." << std::endl;
        consumeIngredients(pizza->getIngredients());
        pizza->setPizzaBaked(Pizza::IN_PROGRESS);
        std::this_thread::sleep_for(std::chrono::milliseconds(std::lround(pizza->getBakedTime() * 1000 * Core::_multiplier)));
        std::cout << "[Kitchen " << _id << "] finished baking the pizza " << pizza->getPizzaType() << "." << std::endl;
        pizza->setPizzaBaked(Pizza::YES);
    }
    std::cout << "close pizza cook " << _id << std::endl;
}

Kitchen::~Kitchen()
{
    if (!_isCopy)
        std::cout << "The kitchen " << _id << " closes its doors..." << std::endl;
}

void Kitchen::createAndJoinCook(Queue<std::shared_ptr<Pizza>> &pizza)
{
    // _thread.create(&Kitchen::handleKitchen, this, std::ref(pizza));
    // for (const auto &c : _cooks) {
    //     c->create(_pizzas);
    // }
    // if (_thread.joinable())
        // _thread.join();
    // for (const auto &c : _cooks) {
    //     c->join();
    // }
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
    std::cout << "close" << std::endl;
}

bool Kitchen::addPizza(std::shared_ptr<Pizza> &pizza)
{
    int nbCooksOccupied = 0;

    for (auto const &t : _threads) {
        if (t->getStatus() == Thread::ThreadStatus::OCCUPIED)
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
        std::cout << "oui" << std::endl;
        return (true);
    }
    return (false);
}

bool Kitchen::isFull() const
{
    int nbCooksOccupied = 0;

    for (auto const &t : _threads) {
        if (t->getStatus() == Thread::ThreadStatus::OCCUPIED)
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
    for (auto const &t : _threads) {
        if (t->getStatus() == Thread::ThreadStatus::OCCUPIED) {
            return (false);
        }
    }
    return (true);
}

bool Kitchen::isThereAvailableCooks() const
{
    for (auto const &t : _threads) {
        if (t->getStatus() == Thread::ThreadStatus::WAIT) {
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

Queue<std::shared_ptr<Pizza>> &Kitchen::getPizzas()
{
    return (std::ref(_pizzas));
}

std::size_t Kitchen::getId()
{
    return _id;
}