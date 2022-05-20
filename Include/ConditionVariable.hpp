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
        ConditionVariable() = default;
        ~ConditionVariable() = default;

        void notifyOne()
        {
            cv.notify_one();
        };
        void notifyAll()
        {
            cv.notify_all();
        };
        template<typename Predicate>
        void wait(std::unique_lock<std::mutex> &lock, Predicate &&predicate)
        {
            cv.wait(lock, predicate);
        };

    protected:
    private:
        std::condition_variable cv;
};
