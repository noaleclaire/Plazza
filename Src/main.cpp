/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <string>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <map>
#include "../Include/Core.hpp"

bool checkErrorArgs(char **av);

int main(int ac, char **av)
{
    if (ac != 4)
        return (84);
    if (!checkErrorArgs(av))
        return (84);
    Core::managePlazza(atof(av[1]), atoi(av[2]), atoi(av[3]));
    return (0);
}