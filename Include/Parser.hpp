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

class Parser {
    public:
        Parser();
        ~Parser();
        void getCommandLine();
        void splitCommandLine();
        void errorHandling();
        void createPizza(std::vector<std::string> pizza);

    protected:
    private:
        std::string _buffer;
        int _start;
        std::vector<std::vector<std::string>> _pizza;
        std::vector<std::string> _cmd;
};
