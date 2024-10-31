#include "Amber.h"

namespace AMBER
{
    //cpp definitions
    void SLEEP(double seconds)
    {
        std::chrono::time_point<std::chrono::system_clock> START, END;
        START = std::chrono::high_resolution_clock::now();
        while(true)
        {
            END = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = END - START;
            if(duration.count() >= seconds)
            {
                break;
            }
        }
    }

    int random(int minimum, int maximum) //note that srand() has to be done by the user using this header file
    {
        return (rand() % (maximum - minimum + 1)) + minimum;
    }

    double randomdouble(double minimum, double maximum)
    {
        return minimum + ((double)rand() / RAND_MAX) * (maximum - minimum);
    }
}
