/*
** EPITECH PROJECT, 2022
** checkArgs
** File description:
** checkArgs
*/

#include <string>
#include <stdexcept>

bool isInteger(char *str)
{
    std::string tmp = std::string(str);
    std::size_t pos;

    try {
        long res = std::stol(tmp, &pos);
        if (pos != tmp.size())
            return (false);
        if (res < 0)
            return (false);
    } catch (std::invalid_argument const &e) {
        return (false);
    }
    return (true);
}

bool checkMultiplier(char *multiplier)
{
    std::string tmp = std::string(multiplier);
    std::size_t pos;

    if (tmp.find('.') != std::string::npos) {
        try {
            double res = std::stod(tmp, &pos);
            if (pos != tmp.size())
                return (false);
            if (0 < res && res < 1)
                return (true);
            else
                return (false);
        } catch (std::invalid_argument const &e) {
            return (false);
        }
    }
    if (!isInteger(multiplier))
        return (false);
    return (true);
}

bool checkErrorArgs(char **av)
{
    if (!checkMultiplier(av[1]))
        return (false);
    if (!isInteger(av[2]))
        return (false);
    if (!isInteger(av[3]))
        return (false);
    return (true);
}
