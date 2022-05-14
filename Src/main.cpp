/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <string>
#include <iostream>

bool checkErrorArgs(char **av);

int main(int ac, char **av)
{
    if (ac != 4)
        return (84);
    if (!checkErrorArgs(av))
        return (84);
    return (0);
}
