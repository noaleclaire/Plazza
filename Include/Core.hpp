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

class Core {
    public:
        static std::map<std::size_t, Kitchen *> _kitchens;
        static float _multiplier;

        static void managePlazza(float multiplier, std::size_t nbCooks, std::size_t replaceTime);

        static int getSize()
        {
            return (_kitchens.size());
        }

    protected:
    private:
        static void checkKitchens();
};