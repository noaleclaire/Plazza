/*
** EPITECH PROJECT, 2022
** ConditionVariable
** File description:
** ConditionVariable
*/

#include "../Include/ConditionVariable.hpp"

ConditionVariable::ConditionVariable()
{
}

ConditionVariable::~ConditionVariable()
{
}

void ConditionVariable::notifyOne()
{
    cv.notify_one();
}

void ConditionVariable::notifyAll()
{
    cv.notify_all();
}

void ConditionVariable::wait(std::unique_lock<std::mutex> &lock, bool (*predicate)(void))
{
    cv.wait(lock, predicate);
}

