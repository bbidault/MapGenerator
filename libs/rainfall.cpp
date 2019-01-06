#include "world_map.h"
#include "common.h"
#include "ctime"


void world_map::create_rainfall()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            if( world[i][j].altitude < 0 )
            {
                if( j < height/3 )
                { 
                    for( int k = 0 ; k < 18 ; k++ )
                    {
                        int l = 1;
                        int max = width/5 - abs( ( j*width*6 )/( 5*height ) - width/5 );

                        if( ( i + l ) < ( width - 1 ) )
                        {
                            while( 400 + k*200 > world[i + l][j].altitude 
                                   && l <= max
                                   && ( i + l ) < ( width - 1 ) )
                            {
                                world[i + l][j].rainfall += 1;
                                l++;
                            }

                            if( ( i + l ) < ( width - 1 ) )
                            {
                                world[i + l][j].rainfall += ( max - l );
                            }
                        }
                    }
                }
                else if( between( j, height/3, height*2/3 ) )
                {
                    for( int k = 0 ; k < 18 ; k++ )
                    {
                        int l = 1;
                        int max = width/5 - abs( ( ( j - height/3 )*width*6 )/( 5*height ) - width/5 );

                        if( ( i - l ) > 0 )
                        {
                            while( 400 + k*200 > world[i - l][j].altitude 
                                   && l <= max 
                                   && ( i - l ) > 0 )
                            {
                                world[i - l][j].rainfall += 1;
                                l++;
                            }

                            if( ( i - l ) > 0 )
                            {
                                world[i - l][j].rainfall += ( max - l );
                            }
                        }
                    }
                }
                else
                {
                    for( int k = 0 ; k < 18 ; k++ )
                    {
                        int l = 1;
                        int max = width/5 - abs( ( ( j - height*2/3 )*width*6 )/( 5*height ) - width/5 );

                        if( ( i + l ) < ( width - 1 ) )
                        {
                            while( 400 + k*200 > world[i + l][j].altitude 
                                   && l <= max
                                   && ( i + l ) < ( width - 1 ) )
                            {
                                world[i + l][j].rainfall += 1;
                                l++;
                            }

                            if( ( i + l ) < ( width - 1 ) )
                            {
                                world[i + l][j].rainfall += ( max - l );
                            }
                        }
                    }
                }
            }
        }
    }

    for( int i = 0 ; i < 30 ; i++ )
    {
        this->average_rainfall();
    }
}

void world_map::average_rainfall()
{
    for( int i = 1 ; i < width - 1 ; i++ )
    {
        for( int j = 1 ; j < height - 1 ; j++ )
        {
            world[i][j].rainfall = ( ( world[i - 1][j - 1].rainfall + world[i - 1][j + 1].rainfall )*0.71
                                    + world[i - 1][j].rainfall + world[i][j - 1].rainfall 
                                    + world[i][j].rainfall*2 ) / 5.42;
        }
    }

    for( int i = width - 2 ; i > 0 ; i-- )
    {
        for( int j = height - 2 ; j > 0 ; j-- )
        {
            world[i][j].rainfall = ( ( world[i + 1][j + 1].rainfall + world[i + 1][j - 1].rainfall )*0.71
                                    + world[i + 1][j].rainfall + world[i][j + 1].rainfall
                                    + world[i][j].rainfall*2 ) / 5.42;
        }
    }
}

void world_map::color_rainfall()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            world[i][j].rainfall_color[0] = 255 - world[i][j].rainfall*255/10000;
            world[i][j].rainfall_color[1] = 255 - world[i][j].rainfall*255/10000;
            world[i][j].rainfall_color[2] = 255;
        }
    }
}
