/*
** EPITECH PROJECT, 2022
** ConditionVariable
** File description:
** ConditionVariable
*/

#pragma once

#include <condition_variable>

class ConditionVariable {
    public:
        ConditionVariable();
        ~ConditionVariable();

        void notifyOne();
        void notifyAll();
        void wait(std::unique_lock<std::mutex> &lock, bool (*predicate)(void));

    protected:
    private:
        std::condition_variable cv;
};
