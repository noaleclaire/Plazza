/*
** EPITECH PROJECT, 2022
** Core.hpp
** File description:
** Core.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Kitchen.hpp"

class Core {
    public:
        Core() = default;
        ~Core() = default;

        void managePlazza(std::size_t multiplier, std::size_t nbCooks, std::size_t replaceTime);

    protected:
    private:
        std::vector<std::shared_ptr<Kitchen>> _kitchens;

        void checkKitchens();
};