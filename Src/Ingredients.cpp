/*
** EPITECH PROJECT, 2022
** Ingredients.cpp
** File description:
** Ingredients
*/

#include "../Include/Ingredients.hpp"

Ingredients::Ingredients(Ingredient ing)
{
    switch (ing) {
        case Ingredients::DOE :
            _name = "doe";
            break;
        case Ingredients::TOMATO :
            _name = "tomato";
            break;
        case Ingredients::GRUYERE :
            _name = "gruyere";
            break;
        case Ingredients::HAM :
            _name = "ham";
            break;
        case Ingredients::MUSHROOM :
            _name = "mushroom";
            break;
        case Ingredients::STEAK :
            _name = "steak";
            break;
        case Ingredients::EGGPLANT :
            _name = "eggplant";
            break;
        case Ingredients::GOAT_CHEESE :
            _name = "goat cheese";
            break;
        case Ingredients::CHIEF_LOVE :
            _name = "chief love";
            break;
        default:
            break;
    }
}

Ingredients::~Ingredients()
{
}

std::string Ingredients::getName() const
{
    return (_name);
}