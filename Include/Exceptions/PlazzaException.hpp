/*
** EPITECH PROJECT, 2022
** PlazzaException
** File description:
** PlazaException
*/

#pragma once

#include <string>

class PlazzaException : public std::exception {
    public:
        PlazzaException(const std::string &message, const std::string &location) : _message(message), _location(location) {};
        ~PlazzaException() = default;

        const char *what() const noexcept override
        {
            return (_message.c_str());
        };
        const char *where() const noexcept
        {
            return (_location.c_str());
        };

    protected:
    private:
        std::string _message;
        std::string _location;
};
