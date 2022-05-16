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
#include "Cook.hpp"
#include "Pizza.hpp"

class Kitchen {
    public:
        Kitchen(std::size_t nbCooks);
        ~Kitchen() = default;

        bool addPizza(Pizza &pizza);
        void checkPizzas();
        bool isClose() const;

    protected:
    private:
        std::size_t _nbCooks;
        std::vector<std::unique_ptr<Cook>> _cooks;
        std::vector<std::unique_ptr<Pizza>> _pizzas;
        std::chrono::time_point<std::chrono::system_clock> _afkStart;
        std::mutex _mutex;
};