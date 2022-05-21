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
        enum ParserStatus {HAS_PIZZA, HASNT_PIZZA};
        Parser();
        ~Parser();

        void manageCommandLine();
        ParserStatus getStatus() const;

        std::vector<std::shared_ptr<Pizza>> getPizzas();

    protected:
    private:
        std::string _buffer;
        int _start;
        std::vector<std::vector<std::string>> _pizza;
        std::vector<std::string> _cmd;
        std::vector<std::shared_ptr<Pizza>> _pizzas;
        ParserStatus _status;

        void createPizza(std::vector<std::string> pizza);
        void getCommandLine();
        void splitCommandLine();
};
