#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <stdint.h>

#include <SFML/System/Clock.hpp>

namespace frmr
{
    class TimeManager
    {
    private:
        const int32_t	timeBase;
        float 			deltaTime;
        int32_t         elapsedTime;
        sf::Clock       timer;

    private:
        void 	UpdateDeltaTime();

    public:
        void	Start();
        void    Stop();
        float	GetDeltaTime() const;
        int32_t GetElapsedTime() const;

    public:
        TimeManager();
        ~TimeManager();
    };
}


#endif
