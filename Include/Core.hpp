/*
** EPITECH PROJECT, 2022
** Core.hpp
** File description:
** Core.hpp
*/

#pragma once

#include <string>
#include <map>
#include <memory>
#include "Kitchen.hpp"
#include "Pizza.hpp"
#include "Queue.hpp"
#include "Arg.hpp"

class Core {
    public:
        static std::map<std::size_t, Kitchen *> _kitchens;
        static float _multiplier;

        static void managePlazza(float multiplier, std::size_t nbCooks, std::size_t replaceTime);
        static void producer(Arg<Kitchen, Queue<std::shared_ptr<Pizza>>> &args);
        static void consumer(Arg<Kitchen, std::size_t> &args);

    protected:
    private:
        static void checkKitchens();
        static bool isAllKitchensFull();
        static void insertPizzaInQueue(std::vector<std::shared_ptr<Pizza>> &pizzas, Queue<std::shared_ptr<Pizza>> &safePizzas);
};