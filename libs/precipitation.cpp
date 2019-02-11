#include "world_map.h"
#include "common.h"


void world_map::clear_precipitation()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            world[i][j].precipitation = 0;
        }
    }
}

void world_map::create_precipitation()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            /// clouds form over lakes and seas
            if( world[i][j].state == SEA || world[i][j].state == LAKE )
            {
                /// if north of the northern Horse latitude
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
                                world[i + l][j].precipitation += 1;
                                l++;
                            }

                            if( ( i + l ) < ( width - 1 ) )
                            {
                                world[i + l][j].precipitation += ( max - l );
                            }
                        }
                    }
                }
                /// if between the Horse latitudes 
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
                                world[i - l][j].precipitation += 1;
                                l++;
                            }

                            if( ( i - l ) > 0 )
                            {
                                world[i - l][j].precipitation += ( max - l );
                            }
                        }
                    }
                }
                /// if south of southern Horse latitude
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
                                world[i + l][j].precipitation += 1;
                                l++;
                            }

                            if( ( i + l ) < ( width - 1 ) )
                            {
                                world[i + l][j].precipitation += ( max - l );
                            }
                        }
                    }
                }
            }
        }
    }

    for( int i = 0 ; i < 30 ; i++ )
    {
        this->average_precipitation();
    }
}

void world_map::average_precipitation()
{
    for( int i = 1 ; i < width - 1 ; i++ )
    {
        for( int j = 1 ; j < height - 1 ; j++ )
        {
            world[i][j].precipitation = ( ( world[i - 1][j - 1].precipitation + world[i - 1][j + 1].precipitation )/SQRT_2
                                    + world[i - 1][j].precipitation + world[i][j - 1].precipitation
                                    + world[i][j].precipitation*2 ) / ( 4 + SQRT_2 );
        }
    }

    for( int i = width - 2 ; i > 0 ; i-- )
    {
        for( int j = height - 2 ; j > 0 ; j-- )
        {
            world[i][j].precipitation = ( ( world[i + 1][j + 1].precipitation + world[i + 1][j - 1].precipitation )/SQRT_2
                                    + world[i + 1][j].precipitation + world[i][j + 1].precipitation
                                    + world[i][j].precipitation*2 ) / ( 4 + SQRT_2 );
        }
    }
}

void world_map::color_precipitation()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            world[i][j].precipitation_color[0] = 255 - world[i][j].precipitation*255/10000;
            world[i][j].precipitation_color[1] = 255 - world[i][j].precipitation*255/10000;
            world[i][j].precipitation_color[2] = 255;
        }
    }
}
