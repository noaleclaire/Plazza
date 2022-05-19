/*
** EPITECH PROJECT, 2022
** Parser.hpp
** File description:
** Parser.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <map>
#include <memory>
#include "Pizza.hpp"

class Parser {
    public:
        Parser();
        ~Parser();

        void manageCommandLine();

        std::vector<std::shared_ptr<Pizza>> getPizzas();

    protected:
    private:
        std::string _buffer;
        int _start;
        std::vector<std::vector<std::string>> _pizza;
        std::vector<std::string> _cmd;
        std::vector<std::shared_ptr<Pizza>> _pizzas;

        void createPizza(std::vector<std::string> pizza);
        void getCommandLine();
        void splitCommandLine();
};
