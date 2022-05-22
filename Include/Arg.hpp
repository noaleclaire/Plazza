/*
** EPITECH PROJECT, 2022
** Arg.hpp
** File description:
** Arg.hpp
*/

#pragma once

template<typename T, typename S>
class Arg {
    public:
        Arg(T &arg1, S &arg2) : _arg1(arg1), _arg2(arg2) {};
        ~Arg() = default;

        T &getArg1()
        {
            return (_arg1);
        };
        S &getArg2()
        {
            return (_arg2);
        };

    protected:
    private:
        T &_arg1;
        S &_arg2;
};