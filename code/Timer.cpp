class Timer 
{
public:
    static int64_t getTick()
    {
        LARGE_INTEGER ticks;
        if (!QueryPerformanceCounter(&ticks))
        {   
            // log error
        }
        return ticks.QuadPart;
    }    
}



