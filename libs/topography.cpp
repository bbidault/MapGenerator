#include "world_map.h"
#include "common.h"
#include "ctime"


void world_map::create_topography()
{
    this->randomize_altitude( 1800 );

    for( int i = 0 ; i < 40 ; i++ )
    {
        this->dilation();
    }

    for( int i = 0 ; i < 40 ; i++ )
    {
        this->erosion();
    }

    for( int i = 0 ; i < 30 ; i++ )
    {
        this->average_altitude();
    }

    this->create_irregularities( 10, 10 );

    this->average_altitude();
}

void world_map::randomize_altitude( int prob )
{
    srand(time(NULL));

    for( int i = width/10 ; i < width - width/10 ; i++ )
    {
        for( int j = height/10 ; j < height - height/10 ; j++ )
        {
            int k = rand()%prob;
            int l = rand()%13;

            if( k == 0 )
            {
                world[i][j].altitude = pow( 2, l );
            }
        }
    }
}

void world_map::dilation()
{
    pixel **world_copy = new pixel*[width];

    for( int i = 0 ; i < width ; i++ )
    {
        world_copy[i] = new pixel[height];
    }

    for( int i = 1 ; i < width - 1 ; i++ )
    {
        for( int j = 1 ; j < height - 1 ; j++ )
        {
            if( world[i][j].altitude >= 0 )
            {
                world_copy[i][j].altitude = world[i][j].altitude;
                
                if( !between( world[i + 1][j].altitude, 0, world[i][j].altitude ) )
                {
                    world_copy[i + 1][j].altitude = world[i][j].altitude;
                }
                if( !between( world[i - 1][j].altitude, 0, world[i][j].altitude ) )
                {
                    world_copy[i - 1][j].altitude = world[i][j].altitude;
                }
                if( !between( world[i][j + 1].altitude, 0, world[i][j].altitude ) )
                {
                    world_copy[i][j + 1].altitude = world[i][j].altitude;
                }
                if( !between( world[i][j - 1].altitude, 0, world[i][j].altitude ) )
                {
                    world_copy[i][j - 1].altitude = world[i][j].altitude;
                }
                if( !between( world[i + 1][j + 1].altitude, 0, world[i][j].altitude ) )
                {
                    world_copy[i + 1][j + 1].altitude = world[i][j].altitude;
                }
                if( !between( world[i - 1][j - 1].altitude, 0, world[i][j].altitude ) )
                {
                    world_copy[i - 1][j - 1].altitude = world[i][j].altitude;
                }
                if( !between( world[i - 1][j + 1].altitude, 0, world[i][j].altitude ) )
                {
                    world_copy[i - 1][j + 1].altitude = world[i][j].altitude;
                }
                if( !between( world[i + 1][j - 1].altitude, 0, world[i][j].altitude ) )
                {
                    world_copy[i + 1][j - 1].altitude = world[i][j].altitude;
                }
            }
        }
    }

    world = world_copy;
}

void world_map::erosion()
{
    pixel **world_copy = new pixel*[width];

    for( int i = 0 ; i < width ; i++ )
    {
        world_copy[i] = new pixel[height];
    }

    for( int i = 1 ; i < width - 1 ; i++ )
    {
        for( int j = 1 ; j < height - 1 ; j++ )
        {
            world_copy[i][j].altitude = world[i][j].altitude;
            
            if( world[i][j].altitude < 0 )
            {
                world_copy[i][j + 1].altitude = world[i][j].altitude;
                world_copy[i][j - 1].altitude = world[i][j].altitude;
                world_copy[i + 1][j].altitude = world[i][j].altitude;
                world_copy[i + 1][j + 1].altitude = world[i][j].altitude;
                world_copy[i + 1][j - 1].altitude = world[i][j].altitude;
                world_copy[i - 1][j].altitude = world[i][j].altitude;
                world_copy[i - 1][j + 1].altitude = world[i][j].altitude;
                world_copy[i - 1][j - 1].altitude = world[i][j].altitude;
            }
        }
    }

    world = world_copy;
}

void world_map::average_altitude()
{
    for( int i = 1 ; i < width - 1 ; i++ )
    {
        for( int j = 1 ; j < height - 1 ; j++ )
        {
            world[i][j].altitude = ( ( world[i - 1][j - 1].altitude + world[i - 1][j + 1].altitude )*0.71
                                    + world[i - 1][j].altitude + world[i][j - 1].altitude 
                                    + world[i][j].altitude*2 ) / 5.42;
        }
    }

    for( int i = width - 2 ; i > 0 ; i-- )
    {
        for( int j = height - 2 ; j > 0 ; j-- )
        {
            world[i][j].altitude = ( ( world[i + 1][j + 1].altitude + world[i + 1][j - 1].altitude )*0.71
                                    + world[i + 1][j].altitude + world[i][j + 1].altitude
                                    + world[i][j].altitude*2 ) / 5.42;
        }
    }
}

void world_map::create_irregularities( int prob, int size )
{
    srand(time(NULL));

    for( int i = 1 ; i < width - 1 ; i++ )
    {
        for( int j = 1 ; j < height - 1 ; j++ )
        {
            int k = rand()%prob;

            if( k == 0 )
            {
                int l = rand()%size - size/2;

                world[i][j].altitude += l; 
            }
        }
    }
}

void world_map::color_topography()
{
    for( int i = 1 ; i < width - 1 ; i++ )
    {
        for( int j = 1 ; j < height - 1 ; j++ )
        {
            if( world[i][j].state == RIVER
                || ( ( world[i][j].state == LAKE 
                       || world[i][j].altitude < 0 ) 
                     && ( world[i + 1][j].altitude > 0
                          || world[i - 1][j].altitude > 0
                          || world[i][j + 1].altitude > 0
                          || world[i][j - 1].altitude > 0 ) ) )
            {
                world[i][j].topography_color[0] = 171;
                world[i][j].topography_color[1] = 120;
                world[i][j].topography_color[2] = 9;
            }
            else if( world[i][j].altitude < -1800 )
            {
                world[i][j].topography_color[0] = 216;
                world[i][j].topography_color[1] = 171;
                world[i][j].topography_color[2] = 113;
            }
            else if( between( world[i][j].altitude, -1800, -1600 ) )
            {
                world[i][j].topography_color[0] = 222;
                world[i][j].topography_color[1] = 178;
                world[i][j].topography_color[2] = 121;
            }
            else if( between( world[i][j].altitude, -1600, -1400 ) )
            {
                world[i][j].topography_color[0] = 227;
                world[i][j].topography_color[1] = 185;
                world[i][j].topography_color[2] = 132;
            }
            else if( between( world[i][j].altitude, -1400, -1200 ) )
            {
                world[i][j].topography_color[0] = 234;
                world[i][j].topography_color[1] = 193;
                world[i][j].topography_color[2] = 141;
            }
            else if( between( world[i][j].altitude, -1200, -1000 ) )
            {
                world[i][j].topography_color[0] = 240;
                world[i][j].topography_color[1] = 201;
                world[i][j].topography_color[2] = 150;
            }
            else if( between( world[i][j].altitude, -1000, -800 ) )
            {
                world[i][j].topography_color[0] = 247;
                world[i][j].topography_color[1] = 210;
                world[i][j].topography_color[2] = 161;
            }
            else if( between( world[i][j].altitude, -800, -600 ) )
            {
                world[i][j].topography_color[0] = 251;
                world[i][j].topography_color[1] = 219;
                world[i][j].topography_color[2] = 172;
            }
            else if( between( world[i][j].altitude, -600, -400 ) )
            {
                world[i][j].topography_color[0] = 255;
                world[i][j].topography_color[1] = 227;
                world[i][j].topography_color[2] = 185;
            }
            else if( between( world[i][j].altitude, -400, -200 ) )
            {
                world[i][j].topography_color[0] = 255;
                world[i][j].topography_color[1] = 236;
                world[i][j].topography_color[2] = 198;
            }
            else if( between( world[i][j].altitude, -200, 0 )
                    || world[i][j].state == LAKE )
            {
                world[i][j].topography_color[0] = 254;
                world[i][j].topography_color[1] = 242;
                world[i][j].topography_color[2] = 216;
            }
            else if( between( world[i][j].altitude, 0, 200 ) )
            {
                world[i][j].topography_color[0] = 165;
                world[i][j].topography_color[1] = 208;
                world[i][j].topography_color[2] = 172;
            }
            else if( between( world[i][j].altitude, 200, 400 ) )
            {
                world[i][j].topography_color[0] = 139;
                world[i][j].topography_color[1] = 191;
                world[i][j].topography_color[2] = 148;
            }
            else if( between( world[i][j].altitude, 400, 600 ) )
            {
                world[i][j].topography_color[0] = 143;
                world[i][j].topography_color[1] = 198;
                world[i][j].topography_color[2] = 168;
            }
            else if( between( world[i][j].altitude, 600, 800 ) )
            {
                world[i][j].topography_color[0] = 150;
                world[i][j].topography_color[1] = 204;
                world[i][j].topography_color[2] = 189;
            }
            else if( between( world[i][j].altitude, 800, 1000 ) )
            {
                world[i][j].topography_color[0] = 171;
                world[i][j].topography_color[1] = 215;
                world[i][j].topography_color[2] = 209;
            }
            else if( between( world[i][j].altitude, 1000, 1200 ) )
            {
                world[i][j].topography_color[0] = 181;
                world[i][j].topography_color[1] = 228;
                world[i][j].topography_color[2] = 225;
            }
            else if( between( world[i][j].altitude, 1200, 1400 ) )
            {
                world[i][j].topography_color[0] = 192;
                world[i][j].topography_color[1] = 235;
                world[i][j].topography_color[2] = 239;
            }
            else if( between( world[i][j].altitude, 1400, 1600 ) )
            {
                world[i][j].topography_color[0] = 163;
                world[i][j].topography_color[1] = 214;
                world[i][j].topography_color[2] = 222;
            }
            else if( between( world[i][j].altitude, 1600, 1800 ) )
            {
                world[i][j].topography_color[0] = 157;
                world[i][j].topography_color[1] = 202;
                world[i][j].topography_color[2] = 211;
            }
            else if( between( world[i][j].altitude, 1800, 2000 ) )
            {
                world[i][j].topography_color[0] = 130;
                world[i][j].topography_color[1] = 185;
                world[i][j].topography_color[2] = 202;
            }
            else if( between( world[i][j].altitude, 2000, 2200 ) )
            {
                world[i][j].topography_color[0] = 107;
                world[i][j].topography_color[1] = 167;
                world[i][j].topography_color[2] = 195;
            }
            else if( between( world[i][j].altitude, 2200, 2400 ) )
            {
                world[i][j].topography_color[0] = 90;
                world[i][j].topography_color[1] = 152;
                world[i][j].topography_color[2] = 185;
            }
            else if( between( world[i][j].altitude, 2400, 2600 ) )
            {
                world[i][j].topography_color[0] = 83;
                world[i][j].topography_color[1] = 135;
                world[i][j].topography_color[2] = 170;
            }
            else if( between( world[i][j].altitude, 2600, 2800 ) )
            {
                world[i][j].topography_color[0] = 124;
                world[i][j].topography_color[1] = 154;
                world[i][j].topography_color[2] = 172;
            }
            else if( between( world[i][j].altitude, 2800, 3000 ) )
            {
                world[i][j].topography_color[0] = 154;
                world[i][j].topography_color[1] = 174;
                world[i][j].topography_color[2] = 186;
            }
            else if( between( world[i][j].altitude, 3000, 3200 ) )
            {
                world[i][j].topography_color[0] = 184;
                world[i][j].topography_color[1] = 195;
                world[i][j].topography_color[2] = 202;
            }
            else if( between( world[i][j].altitude, 3200, 3400 ) )
            {
                world[i][j].topography_color[0] = 216;
                world[i][j].topography_color[1] = 222;
                world[i][j].topography_color[2] = 224;
            }
            else if( world[i][j].altitude > 3400 )
            {
                world[i][j].topography_color[0] = 242;
                world[i][j].topography_color[1] = 244;
                world[i][j].topography_color[2] = 245;
            }
        }
    }
}
