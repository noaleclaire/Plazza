/*
** EPITECH PROJECT, 2022
** Pizza
** File description:
** Pizza
*/

#pragma once

#include <string>

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};
enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

class Pizza {
    public:
        enum PizzaBaked {
            YES,
            NO,
            IN_PROGRESS
        };
        Pizza(std::string &pizzaType, std::string &pizzaSize);
        ~Pizza();

        PizzaType getPizzaType() const;
        PizzaSize getPizzaSize() const;
        PizzaBaked getPizzaBaked() const;
        size_t getBakedTime() const;

        void setPizzaBaked(PizzaBaked pizzaBaked);

    protected:
    private:
        PizzaType _pizzaType;
        PizzaSize _pizzaSize;
        PizzaBaked _pizzaBaked = NO;
        size_t _bakedTime;
};
