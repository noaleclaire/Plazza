/*
** EPITECH PROJECT, 2022
** Ingredients.hpp
** File description:
** Ingredient
*/

#pragma once

#include <string>

class Ingredients {
    public:
        enum Ingredient {
            DOE,
            TOMATO,
            GRUYERE,
            HAM,
            MUSHROOM,
            STEAK,
            EGGPLANT,
            GOAT_CHEESE,
            CHIEF_LOVE,
        };
        Ingredients(Ingredient ing);
        ~Ingredients();
        std::string getName();

    protected:
    private:
        std::string _name;
};