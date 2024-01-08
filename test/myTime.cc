#include "myTime.h"
#include <string>

myTimer::myTimer(const char *msg, Type type, bool dumpOnDestruct, bool startOnConstruct)
    : _msg(msg), _dumpOnDestruct(dumpOnDestruct), _active(startOnConstruct), _type(type)
{
    if (_active)
        start();

}

myTimer::~myTimer()
{
    if (_dumpOnDestruct)
        pause();
}

void myTimer::start()
{
    _startTime = std::chrono::steady_clock::now();
}

void myTimer::pause()
{
    _endTime = std::chrono::steady_clock::now();
    double time;
    switch (_type) {
    case Type::MS:
        time = std::chrono::duration<double,std::milli>(_endTime - _startTime).count();
        printf("%s %6f ms\n", _msg, time);
        break;
    case Type::US:
        time = std::chrono::duration<double,std::micro>(_endTime - _startTime).count();
        printf("%s %6f us\n", _msg, time);
        break;
    case Type::NS:
        time = std::chrono::duration<double,std::nano>(_endTime - _startTime).count();
        printf("%s %6f ns\n", _msg, time);
        break;
    default:
        time = std::chrono::duration<double>(_endTime - _startTime).count();
        printf("%s %6f s\n", _msg, time);
        break;
    }
}

void myTimer::getTime(bool cont)
{
    pause();
    if (!cont) {
        start();
    }
}
