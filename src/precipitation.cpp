#include "world_map.h"
#include "common.h"

/**
 * @brief clear precipitation values
 */
void WorldMap::clearPrecipitation()
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            world[i][j].precipitation = 0;
        }
    }
}

/**
 * @brief generate precipitation map from water mass locations and air currents
 */
void WorldMap::createPrecipitation()
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            // clouds form over lakes and seas
            if ( ( world[i][j].state == SEA ) || ( world[i][j].state == LAKE ) )
            {
                world[i][j].precipitation += 1000;

                // if north of the northern Horse latitude
                if ( j < height / 3 )
                {
                    for ( int k = 0; k < 18; k++ )
                    {
                        int cloudDistTVL  = 1;  // distance travelled by the cloud
                        int rainDropCount = width / 6 - std::abs( ( j * width * 6 ) / ( 6 * height ) - width / 6 )
                            + width / 5 - std::abs( ( j * width * 2 ) / ( 5 * height ) - width / 5 );

                        if ( ( i + cloudDistTVL ) < ( width - 1 ) )
                        {
                            while ( 400 + k * 200 > world[i + cloudDistTVL][j].altitude &&
                                    cloudDistTVL <= rainDropCount &&
                                    ( i + cloudDistTVL ) < ( width - 1 ) )
                            {
                                world[i + cloudDistTVL][j].precipitation += Constants::RainDrop;
                                cloudDistTVL++;
                            }

                            if ( ( i + cloudDistTVL ) < ( width - 1 ) )
                            {
                                world[i + cloudDistTVL][j].precipitation += ( rainDropCount - cloudDistTVL ) * Constants::RainDrop;
                            }
                        }
                    }
                }
                // if between the Horse latitudes
                else if ( between( j, height / 3, height * 2 / 3 ) )
                {
                    for ( int k = 0; k < 18; k++ )
                    {
                        int cloudDistTVL  = 1;
                        int rainDropCount = width / 6 - std::abs( ( ( j - height / 3 ) * width * 6 ) / ( 6 * height ) - width / 6 )
                            + width / 5 - std::abs( ( j * width * 2 ) / ( 5 * height ) - width / 5 );

                        if ( ( i - cloudDistTVL ) > 0 )
                        {
                            while ( 400 + k * 200 > world[i - cloudDistTVL][j].altitude &&
                                    cloudDistTVL <= rainDropCount &&
                                    ( i - cloudDistTVL ) > 0 )
                            {
                                world[i - cloudDistTVL][j].precipitation += Constants::RainDrop;
                                cloudDistTVL++;
                            }

                            if ( ( i - cloudDistTVL ) > 0 )
                            {
                                world[i - cloudDistTVL][j].precipitation += ( rainDropCount - cloudDistTVL ) * Constants::RainDrop;
                            }
                        }
                    }
                }
                // if south of southern Horse latitude
                else
                {
                    for ( int k = 0; k < 18; k++ )
                    {
                        int cloudDistTVL  = 1;
                        int rainDropCount = width / 6 - std::abs( ( ( j - height * 2 / 3 ) * width * 6 ) / ( 6 * height ) - width / 6 )
                            + width / 5 - std::abs( ( j * width * 2 ) / ( 5 * height ) - width / 5 );

                        if ( ( i + cloudDistTVL ) < ( width - 1 ) )
                        {
                            while ( 400 + k * 200 > world[i + cloudDistTVL][j].altitude &&
                                    cloudDistTVL <= rainDropCount &&
                                    ( i + cloudDistTVL ) < ( width - 1 ) )
                            {
                                world[i + cloudDistTVL][j].precipitation += Constants::RainDrop;
                                cloudDistTVL++;
                            }

                            if ( ( i + cloudDistTVL ) < ( width - 1 ) )
                            {
                                world[i + cloudDistTVL][j].precipitation += ( rainDropCount - cloudDistTVL ) * Constants::RainDrop;
                            }
                        }
                    }
                }
            }
            else if ( world[i][j].state == RIVER )
            {
                world[i][j].precipitation += 1000;
            }
        }
    }

    for ( int i = 0; i < 30; i++ )
    {
        this->averagePrecipitation();
    }
}

/**
 * @brief average precipitation across the map
 */
void WorldMap::averagePrecipitation()
{
    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            world[i][j].precipitation = ( ( world[i - 1][j - 1].precipitation + world[i - 1][j + 1].precipitation ) / SQRT_2
                                          + world[i - 1][j].precipitation + world[i][j - 1].precipitation
                                          + world[i][j].precipitation * 2 ) / ( 4 + SQRT_2 );
        }
    }

    for ( int i = width - 2; i > 0; i-- )
    {
        for ( int j = height - 2; j > 0; j-- )
        {
            world[i][j].precipitation = ( ( world[i + 1][j + 1].precipitation + world[i + 1][j - 1].precipitation ) / SQRT_2
                                          + world[i + 1][j].precipitation + world[i][j + 1].precipitation
                                          + world[i][j].precipitation * 2 ) / ( 4 + SQRT_2 );
        }
    }
}

/**
 * @brief color precipitation map
 */
void WorldMap::colorPrecipitation()
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            world[i][j].precipitationColor[0] = 255 - world[i][j].precipitation * 255 / 10000;
            world[i][j].precipitationColor[1] = 255 - world[i][j].precipitation * 255 / 10000;
            world[i][j].precipitationColor[2] = 255;
        }
    }
}
