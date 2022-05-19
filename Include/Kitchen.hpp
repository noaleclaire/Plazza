/*
** EPITECH PROJECT, 2022
** Kitchen.hpp
** File description:
** Kitchen.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include "Cook.hpp"
#include "Pizza.hpp"

class Kitchen {
    public:
        Kitchen(std::size_t id, std::size_t nbCooks, std::size_t replaceTime, std::size_t multiplier);
        Kitchen(Kitchen const &other);
        ~Kitchen();

        bool addPizza(std::shared_ptr<Pizza> pizza);
        void checkPizzas();
        bool isClose() const;

    protected:
    private:
        std::size_t _id;
        std::size_t _nbCooks;
        std::size_t _replaceTime;
        std::size_t _multiplier;
        std::vector<std::shared_ptr<Cook>> _cooks;
        std::vector<std::shared_ptr<Pizza>> _pizzas;
        std::chrono::time_point<std::chrono::system_clock> _afkStart;
        bool _isCopy;
};