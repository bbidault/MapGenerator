#include "world_map.h"
#include "common.h"

/**
 * @brief generate the map topography
 */
void WorldMap::createTopography()
{
    this->randomizeAltitude( 1800 );

    for ( int i = 0; i < 40; i++ )
    {
        this->dilation();
    }

    for ( int i = 0; i < 40; i++ )
    {
        this->erosion();
    }

    for ( int i = 0; i < 30; i++ )
    {
        this->averageAltitude();
    }

    this->createIrregularities( 10, 10 );

    this->averageAltitude();

    this->setSeasAndLands();
}

/**
 * @brief generates random high points on the map
 *
 * @param aProb probability of altitude > 0
 */
void WorldMap::randomizeAltitude( int aProb )
{
    srand( time( NULL ) );

    for ( int i = width / 10; i < width - width / 10; i++ )
    {
        for ( int j = height / 10; j < height - height / 10; j++ )
        {
            int k = rand() % aProb;
            int l = rand() % 13;

            if ( k == 0 )
            {
                world[i][j].altitude = std::pow( 2, l );
            }
        }
    }
}

/**
 * @brief dilate points of altitude > 0
 */
void WorldMap::dilation()
{
    Pixel * *worldCopy = new Pixel *[width];
    for ( int i = 0; i < width; i++ )
    {
        worldCopy[i] = new Pixel[height];
    }

    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            if ( world[i][j].altitude >= 0 )
            {
                worldCopy[i][j].altitude = world[i][j].altitude;

                if ( !between( world[i + 1][j].altitude, 0, world[i][j].altitude ) )
                {
                    worldCopy[i + 1][j].altitude = world[i][j].altitude;
                }
                if ( !between( world[i - 1][j].altitude, 0, world[i][j].altitude ) )
                {
                    worldCopy[i - 1][j].altitude = world[i][j].altitude;
                }
                if ( !between( world[i][j + 1].altitude, 0, world[i][j].altitude ) )
                {
                    worldCopy[i][j + 1].altitude = world[i][j].altitude;
                }
                if ( !between( world[i][j - 1].altitude, 0, world[i][j].altitude ) )
                {
                    worldCopy[i][j - 1].altitude = world[i][j].altitude;
                }
                if ( !between( world[i + 1][j + 1].altitude, 0, world[i][j].altitude ) )
                {
                    worldCopy[i + 1][j + 1].altitude = world[i][j].altitude;
                }
                if ( !between( world[i - 1][j - 1].altitude, 0, world[i][j].altitude ) )
                {
                    worldCopy[i - 1][j - 1].altitude = world[i][j].altitude;
                }
                if ( !between( world[i - 1][j + 1].altitude, 0, world[i][j].altitude ) )
                {
                    worldCopy[i - 1][j + 1].altitude = world[i][j].altitude;
                }
                if ( !between( world[i + 1][j - 1].altitude, 0, world[i][j].altitude ) )
                {
                    worldCopy[i + 1][j - 1].altitude = world[i][j].altitude;
                }
            }
        }
    }

    for ( int i = 0; i < width; i++ )
    {
        delete[] world[i];
    }
    delete[] world;

    world = worldCopy;
}

/**
 * @brief erode points of altitude > 0
 */
void WorldMap::erosion()
{
    Pixel * *worldCopy = new Pixel *[width];
    for ( int i = 0; i < width; i++ )
    {
        worldCopy[i] = new Pixel[height];
    }

    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            worldCopy[i][j].altitude = world[i][j].altitude;

            if ( world[i][j].altitude < 0 )
            {
                worldCopy[i][j + 1].altitude     = world[i][j].altitude;
                worldCopy[i][j - 1].altitude     = world[i][j].altitude;
                worldCopy[i + 1][j].altitude     = world[i][j].altitude;
                worldCopy[i + 1][j + 1].altitude = world[i][j].altitude;
                worldCopy[i + 1][j - 1].altitude = world[i][j].altitude;
                worldCopy[i - 1][j].altitude     = world[i][j].altitude;
                worldCopy[i - 1][j + 1].altitude = world[i][j].altitude;
                worldCopy[i - 1][j - 1].altitude = world[i][j].altitude;
            }
        }
    }

    for ( int i = 0; i < width; i++ )
    {
        delete[] world[i];
    }
    delete[] world;

    world = worldCopy;
}

/**
 * @brief average altitude across the map
 */
void WorldMap::averageAltitude()
{
    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            world[i][j].altitude = ( ( world[i - 1][j - 1].altitude + world[i - 1][j + 1].altitude ) / SQRT_2
                                     + world[i - 1][j].altitude + world[i][j - 1].altitude
                                     + world[i][j].altitude * 2 ) / ( 4 + SQRT_2 );
        }
    }

    for ( int i = width - 2; i > 0; i-- )
    {
        for ( int j = height - 2; j > 0; j-- )
        {
            world[i][j].altitude = ( ( world[i + 1][j + 1].altitude + world[i + 1][j - 1].altitude ) / SQRT_2
                                     + world[i + 1][j].altitude + world[i][j + 1].altitude
                                     + world[i][j].altitude * 2 ) / ( 4 + SQRT_2 );
        }
    }
}

/**
 * @brief create random altutude irregularities
 *
 * @param aProb probability of irregularity
 * @param aSize of irregularity
 */
void WorldMap::createIrregularities( int aProb, int aSize )
{
    srand( time( NULL ) );

    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            int k = rand() % aProb;

            if ( k == 0 )
            {
                int l = rand() % aSize - aSize / 2;

                world[i][j].altitude += l;
            }
        }
    }
}

/**
 * @brief color topographic map
 */
void WorldMap::colorTopography()
{
    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            if ( ( world[i][j].state == RIVER ) ||
                 ( world[i][j].state == LAKE ) ||
                 ( ( world[i][j].state == SEA ) &&
                   ( ( world[i + 1][j].altitude > 0 ) ||
                     ( world[i - 1][j].altitude > 0 ) ||
                     ( world[i][j + 1].altitude > 0 ) ||
                     ( world[i][j - 1].altitude > 0 ) ) ) )
            {
                world[i][j].topographyColor = TopographyColors::CoastLakeRiver;
            }
            else if ( ( world[i][j].state == LAND ) &&
                      ( world[i][j].altitude < 0 ) )
            {
                world[i][j].topographyColor = TopographyColors::Depression;
            }
            else if ( world[i][j].altitude < -1800 )
            {
                world[i][j].topographyColor = TopographyColors::NegativeAltitude0;
            }
            else if ( between( world[i][j].altitude, -1800, -1600 ) )
            {
                world[i][j].topographyColor = TopographyColors::NegativeAltitude1;
            }
            else if ( between( world[i][j].altitude, -1600, -1400 ) )
            {
                world[i][j].topographyColor = TopographyColors::NegativeAltitude2;
            }
            else if ( between( world[i][j].altitude, -1400, -1200 ) )
            {
                world[i][j].topographyColor = TopographyColors::NegativeAltitude3;
            }
            else if ( between( world[i][j].altitude, -1200, -1000 ) )
            {
                world[i][j].topographyColor = TopographyColors::NegativeAltitude4;
            }
            else if ( between( world[i][j].altitude, -1000, -800 ) )
            {
                world[i][j].topographyColor = TopographyColors::NegativeAltitude5;
            }
            else if ( between( world[i][j].altitude, -800, -600 ) )
            {
                world[i][j].topographyColor = TopographyColors::NegativeAltitude6;
            }
            else if ( between( world[i][j].altitude, -600, -400 ) )
            {
                world[i][j].topographyColor = TopographyColors::NegativeAltitude7;
            }
            else if ( between( world[i][j].altitude, -400, -200 ) )
            {
                world[i][j].topographyColor = TopographyColors::NegativeAltitude8;
            }
            else if ( between( world[i][j].altitude, -200, 0 ) )
            {
                world[i][j].topographyColor = TopographyColors::NegativeAltitude9;
            }
            else if ( between( world[i][j].altitude, 0, 200 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude0;
            }
            else if ( between( world[i][j].altitude, 200, 400 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude1;
            }
            else if ( between( world[i][j].altitude, 400, 600 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude2;
            }
            else if ( between( world[i][j].altitude, 600, 800 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude3;
            }
            else if ( between( world[i][j].altitude, 800, 1000 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude4;
            }
            else if ( between( world[i][j].altitude, 1000, 1200 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude5;
            }
            else if ( between( world[i][j].altitude, 1200, 1400 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude6;
            }
            else if ( between( world[i][j].altitude, 1400, 1600 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude7;
            }
            else if ( between( world[i][j].altitude, 1600, 1800 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude8;
            }
            else if ( between( world[i][j].altitude, 1800, 2000 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude9;
            }
            else if ( between( world[i][j].altitude, 2000, 2200 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude10;
            }
            else if ( between( world[i][j].altitude, 2200, 2400 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude11;
            }
            else if ( between( world[i][j].altitude, 2400, 2600 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude12;
            }
            else if ( between( world[i][j].altitude, 2600, 2800 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude13;
            }
            else if ( between( world[i][j].altitude, 2800, 3000 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude14;
            }
            else if ( between( world[i][j].altitude, 3000, 3200 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude15;
            }
            else if ( between( world[i][j].altitude, 3200, 3400 ) )
            {
                world[i][j].topographyColor = TopographyColors::Altitude16;
            }
            else if ( world[i][j].altitude > 3400 )
            {
                world[i][j].topographyColor = TopographyColors::Altitude17;
            }
        }
    }
}
