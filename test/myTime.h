#ifndef MYTIMER_H
#define MYTIMER_H
#include <chrono>

enum class Type {
    MS, //millisecond
    US, //microsecond
    NS, //nanosecond
    S   //second
};

class myTimer
{
    typedef std::chrono::steady_clock::time_point timePoint;
public:
    myTimer(const char *msg, Type type = Type::S, bool dumpOnDestruct = true, bool startOnConstruct = true);
    ~myTimer();

    void            getTime(bool cont = false);

protected:
    void            start();
    void            pause();

protected:
    const char*     _msg;
    bool            _dumpOnDestruct;
    bool            _active;
    Type            _type;
    timePoint       _startTime;
    timePoint       _endTime;
};

#endif // MYTIMER_H
