/*
** EPITECH PROJECT, 2022
** Cook.hpp
** File description:
** Cook.hpp
*/

#pragma once

#include <memory>
#include <thread>
#include <string>
#include "Thread.hpp"
#include "Pizza.hpp"

class Cook {
    public:
        Cook(std::size_t id, std::size_t kitchenId);
        Cook(Cook const &other);
        ~Cook() = default;
        Cook &operator=(Cook const &other);

        void cookPizza(std::shared_ptr<Pizza> pizza);

        bool getBaking() const;
        std::size_t getKitchenId() const;
        std::size_t getId() const;

        void setBaking(bool baking);

    protected:
    private:
        std::size_t _id;
        std::size_t _kitchenId;
        Thread _thread;
        bool _baking;

        void bakePizza(std::shared_ptr<Pizza> pizza);
};