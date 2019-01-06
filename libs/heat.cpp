#include "world_map.h"
#include "common.h"
#include "ctime"


///
void world_map::create_heat()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            world[i][j].temperature += 30 - ( sign( 60 - j*120/height ) );

            if( world[i][j].altitude >= 0 )
            {
                world[i][j].temperature += 30 - world[i][j].altitude*6/400;
            }
            else if( between( world[i][j].altitude, -200, 0 ) )
            {
                world[i][j].temperature += 30 + world[i][j].altitude*3/20;
            }
        }
    }

    for( int i = 0 ; i < 30 ; i++ )
    {
        this->average_temperature();
    }
}

///
void world_map::average_temperature()
{
    for( int i = 1 ; i < width - 1 ; i++ )
    {
        for( int j = 1 ; j < height - 1 ; j++ )
        {
            world[i][j].temperature = ( ( world[i - 1][j - 1].temperature + world[i - 1][j + 1].temperature )*0.71
                                    + world[i - 1][j].temperature + world[i][j - 1].temperature 
                                    + world[i][j].temperature*2 ) / 5.42;
        }
    }

    for( int i = width - 2 ; i > 0 ; i-- )
    {
        for( int j = height - 2 ; j > 0 ; j-- )
        {
            world[i][j].temperature = ( ( world[i + 1][j + 1].temperature + world[i + 1][j - 1].temperature )*0.71
                                    + world[i + 1][j].temperature + world[i][j + 1].temperature
                                    + world[i][j].temperature*2 ) / 5.42;
        }
    }
}

///
void world_map::color_heat()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            world[i][j].heat_color[0] = 127.5 - world[i][j].temperature*127.5/60;
            world[i][j].heat_color[1] = 0;
            world[i][j].heat_color[2] = 127.5 + world[i][j].temperature*127.5/60;
        }
    }
}
