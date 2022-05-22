/*
** EPITECH PROJECT, 2022
** Thread.hpp
** File description:
** Thread.hpp
*/

#pragma once

#include <thread>

class Thread {
    public:
        enum ThreadStatus {OCCUPIED, WAIT};
        Thread() = default;
        ~Thread() = default;

        void join()
        {
            _thread.join();
        };
        void detach()
        {
            _thread.detach();
        };
        bool joinable()
        {
            if (_thread.joinable())
                return (true);
            return (false);
        };
        template<typename Function, typename... Args>
        void create(Function fct, Args&&... args)
        {
            _thread = std::thread(fct, args...);
        };
        ThreadStatus getStatus() const
        {
            return (_status);
        };
        void setStatus(ThreadStatus status)
        {
            _status = status;
        };

    protected:
    private:
        std::thread _thread;
        ThreadStatus _status = WAIT;
};