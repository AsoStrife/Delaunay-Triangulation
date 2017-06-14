#ifndef COMMON_MODULE_TIMER_H
#define COMMON_MODULE_TIMER_H

#include <QString>

#include <time.h>
#include <iostream>
#include <sys/time.h>

class Timer {
    public:
        Timer (const std::string& caption, bool start_ = true);

        void start();

        void stopAndPrint();

        void stop();

        void print ();

        double delay();

    private:
        std::string caption;
        timeval begin, end;
        bool isStopped;
};

#include "timer.cpp"

#endif //COMMON_MODULE_TIMER_H
