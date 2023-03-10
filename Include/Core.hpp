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
#include <fstream>
#include "Kitchen.hpp"
#include "Pizza.hpp"
#include "Queue.hpp"

class Core {
    public:
        static std::ofstream _file;
        static std::map<std::size_t, Kitchen *> _kitchens;
        static float _multiplier;

        static void managePlazza(float multiplier, std::size_t nbCooks, std::size_t replaceTime);

        static void getInfoKitchen();

    protected:
    private:
        static bool isAllKitchensFull();
        static void insertPizzaInQueue(std::vector<std::shared_ptr<Pizza>> &pizzas, Queue<std::shared_ptr<Pizza>> &safePizzas);
};