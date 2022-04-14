
#include"StopWatch.h"

StopWatch::StopWatch(bool a_start /* = true */, TimeUnit a_unit /* = TimeUnit::MilliSecs */)
    : f_unit(a_unit)
{
    if (a_start)
    {
        Start();
    }

}

void StopWatch::Start()
{
    f_start = std::chrono::high_resolution_clock::now();
}

void StopWatch::Stop()
{
    f_end = std::chrono::high_resolution_clock::now();

    f_duration = f_end - f_start;
}

float StopWatch::GetDuration() const
{
    if (f_unit == TimeUnit::NanoSecs)
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(f_duration).count();
    }
    else if (f_unit == TimeUnit::MicroSecs)
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(f_duration).count();
    }
    else if (f_unit == TimeUnit::MilliSecs)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(f_duration).count();
    }
    else if (f_unit == TimeUnit::Secs)
    {
        return std::chrono::duration_cast<std::chrono::seconds>(f_duration).count();
    }

}

void StopWatch::SetUnit(TimeUnit a_unit)
{
    f_unit = a_unit;
}