/*
** EPITECH PROJECT, 2022
** Parser.cpp
** File description:
** parser
*/

#include "../Include/Parser.hpp"
#include "../Include/Core.hpp"
#include "../Include/Pizza.hpp"
#include "../Include/Factory.hpp"
#include "../Include/Kitchen.hpp"
#include "../Include/Exceptions/PizzaException.hpp"
#include <iostream>

bool isInteger(std::string str, int &nb);

Parser::Parser() : _start(0)
{
    _thread.create(&Parser::manageCommandLine, this);
}

Parser::~Parser()
{
}

void Parser::manageCommandLine()
{
    while (1) {
        std::getline(std::cin, _buffer);
        getCommandLine();
        _buffer.clear();
        splitCommandLine();
        _cmd.clear();
        _start = 0;
    }
}

void Parser::getCommandLine()
{
    int i = 0;

    for (i = 0 ; i < _buffer.length(); i++) {
        if (_buffer.at(i) == ';') {
            std::cout << _buffer.substr(_start, i - _start) << std::endl;
            _cmd.push_back(_buffer.substr(_start, i - _start));
            _start = i + 2;
        }
    }
    _cmd.push_back(_buffer.substr(_start, i - _start));
}

void Parser::splitCommandLine()
{
    char *line;
    std::vector<std::string> split;

    for (int i = 0; i < _cmd.size(); i++) {
        line = std::strtok(const_cast<char *>(_cmd.at(i).c_str()), " ");
        while (line != nullptr) {
            split.push_back(std::string(line));
            line = std::strtok(nullptr, " ");
        }
        _pizza.push_back(split);
        split.clear();
    }
}

void Parser::createPizza(std::vector<std::string> pizza)
{
    std::string pizzaType = pizza.at(0);
    std::string pizzaSize = pizza.at(1);
    int pizza_nb = 0;

    isInteger((pizza.at(2).substr(1, pizza.at(2).length() - 1)), pizza_nb);
    for (int i = 0; i < pizza_nb; i++) {
        try {
            _pizzas.push_back(Factory::createPizza(pizzaType, pizzaSize));
        } catch (const PizzaException &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

std::vector<std::shared_ptr<Pizza>> Parser::getPizzas()
{
    int nb = -1;

    _pizzas.clear();
    for (int i = 0; i < _pizza.size(); i++) {
        for (int j = 0; j < _pizza.at(i).size(); j++) {
            if (_pizza.at(i).size() == 1 && _pizza.at(i).at(0).compare("status") == 0) {
                Core::getInfoKitchen();
                break;
            }
            if (_pizza.at(i).size() != 3) {
                std::cerr << "Command n°" << i << ": Invalid number of arguments.." << std::endl;
                break;
            }
            if (_pizza.at(i).at(2).at(_pizza.at(i).at(2).length() - 1) == ';')
                _pizza.at(i).at(2).at(_pizza.at(i).at(2).length() - 1) = '\0';
            if (_pizza.at(i).at(2).at(0) != 'x') {
                std::cerr << "Command n°" << i << ": Invalid numbers of pizza (x(N)).." << std::endl;
                break;
            }
            if (!isInteger((_pizza.at(i).at(2).substr(1, _pizza.at(i).at(2).length() - 1)), nb)) {
                std::cerr << "Command n°" << i << ": Invalid number of pizzas xN pizza must be Integer.." << std::endl;
                break;
            }
            if (nb == -1) {
                std::cerr << "Command n°" << i << ": Invalid numbers of Pizza, number must be positive.." << std::endl;
                break;
            }
            createPizza(_pizza.at(i));
            break;
        }
    }
    _pizza.clear();
    return (_pizzas);
}

bool Parser::hasPizza()
{
    if (_pizza.empty())
        return (false);
    return (true);
}