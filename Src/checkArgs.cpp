/*
** EPITECH PROJECT, 2022
** checkArgs
** File description:
** checkArgs
*/

#include <string>
#include <stdexcept>

bool isInteger(std::string str, int &nb)
{
    std::string tmp = str;
    std::size_t pos;

    try {
        int res = std::stoi(tmp, &pos);
        if (pos != tmp.size())
            return (false);
        if (res < 0)
            return (false);
        nb = res;
    } catch (std::invalid_argument const &e) {
        return (false);
    }
    return (true);
}

bool checkMultiplier(char *multiplier)
{
    std::string tmp = std::string(multiplier);
    std::size_t pos;
    int nb = 0;

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
    if (!isInteger(tmp, nb))
        return (false);
    return (true);
}

bool checkErrorArgs(char **av)
{
    int nb = 0;

    if (!checkMultiplier(av[1]))
        return (false);
    if (!isInteger(std::string(av[2]), nb))
        return (false);
    if (!isInteger(std::string(av[3]), nb))
        return (false);
    return (true);
}
