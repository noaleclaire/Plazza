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
#include "Ingredients.hpp"
#include "Pizza.hpp"
#include "Queue.hpp"

class Kitchen {
    public:
        Kitchen(std::size_t id, std::size_t nbCooks, std::size_t replaceTime);
        ~Kitchen();

        bool addPizza(std::shared_ptr<Pizza> &pizza);
        bool isIngredientAvailable(std::vector<Ingredients> ingredients);
        void consumeIngredients(std::vector<Ingredients> ingredients);

        void createAndJoinCook(Queue<std::shared_ptr<Pizza>> &pizzas);
        void update();
        bool isClose() const;
        bool isFull() const;

        std::size_t getId()
        {
            return _id;
        }

    protected:
    private:
        std::size_t _id;
        std::size_t _nbCooks;
        std::size_t _replaceTime;
        Queue<std::shared_ptr<Pizza>> _pizzas;
        std::vector<std::pair<Ingredients, std::size_t>> _stock;
        std::vector<std::shared_ptr<Cook>> _cooks;
        std::chrono::time_point<std::chrono::system_clock> _afkStart;
        std::chrono::time_point<std::chrono::system_clock> _refillStart;
        bool _isCopy;

        Thread _thread;
        void handleKitchen(Queue<std::shared_ptr<Pizza>> &pizza);

        bool isRefill();
        bool isThereAvailableCooks() const;
        bool AreAllCooksAvailable() const;
        void refill();
};