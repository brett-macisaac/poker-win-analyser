#pragma once

#include<chrono>

enum TimeUnit
{
    NanoSecs,
    MicroSecs,
    MilliSecs,
    Secs
};

class StopWatch
{

private:

    std::chrono::time_point<std::chrono::steady_clock> f_start, f_end;

    std::chrono::duration<float> f_duration;

    // A field for the unit.
    TimeUnit f_unit;


public:

    StopWatch(bool a_start = true, TimeUnit a_unit = TimeUnit::MilliSecs);

    void Start();

    void Stop();

    float GetDuration() const;

    void SetUnit(TimeUnit a_unit);


private:

    //CalculateDuration

};
