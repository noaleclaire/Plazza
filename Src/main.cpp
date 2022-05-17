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

bool checkErrorArgs(char **av);

int main(int ac, char **av)
{
    if (ac != 4)
        return (84);
    if (!checkErrorArgs(av))
        return (84);
    return (0);
}