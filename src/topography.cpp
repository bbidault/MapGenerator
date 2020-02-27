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

    this->setSeasLakesLands();
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
                 ( ( world[i][j].altitude < 0 ) &&
                   ( ( world[i + 1][j].altitude > 0 ) ||
                     ( world[i - 1][j].altitude > 0 ) ||
                     ( world[i][j + 1].altitude > 0 ) ||
                     ( world[i][j - 1].altitude > 0 ) ) ) )
            {
                world[i][j].topographyColor[0] = 171;
                world[i][j].topographyColor[1] = 120;
                world[i][j].topographyColor[2] = 9;
            }
            else if ( world[i][j].altitude < -1800 )
            {
                world[i][j].topographyColor[0] = 216;
                world[i][j].topographyColor[1] = 171;
                world[i][j].topographyColor[2] = 113;
            }
            else if ( between( world[i][j].altitude, -1800, -1600 ) )
            {
                world[i][j].topographyColor[0] = 222;
                world[i][j].topographyColor[1] = 178;
                world[i][j].topographyColor[2] = 121;
            }
            else if ( between( world[i][j].altitude, -1600, -1400 ) )
            {
                world[i][j].topographyColor[0] = 227;
                world[i][j].topographyColor[1] = 185;
                world[i][j].topographyColor[2] = 132;
            }
            else if ( between( world[i][j].altitude, -1400, -1200 ) )
            {
                world[i][j].topographyColor[0] = 234;
                world[i][j].topographyColor[1] = 193;
                world[i][j].topographyColor[2] = 141;
            }
            else if ( between( world[i][j].altitude, -1200, -1000 ) )
            {
                world[i][j].topographyColor[0] = 240;
                world[i][j].topographyColor[1] = 201;
                world[i][j].topographyColor[2] = 150;
            }
            else if ( between( world[i][j].altitude, -1000, -800 ) )
            {
                world[i][j].topographyColor[0] = 247;
                world[i][j].topographyColor[1] = 210;
                world[i][j].topographyColor[2] = 161;
            }
            else if ( between( world[i][j].altitude, -800, -600 ) )
            {
                world[i][j].topographyColor[0] = 251;
                world[i][j].topographyColor[1] = 219;
                world[i][j].topographyColor[2] = 172;
            }
            else if ( between( world[i][j].altitude, -600, -400 ) )
            {
                world[i][j].topographyColor[0] = 255;
                world[i][j].topographyColor[1] = 227;
                world[i][j].topographyColor[2] = 185;
            }
            else if ( between( world[i][j].altitude, -400, -200 ) )
            {
                world[i][j].topographyColor[0] = 255;
                world[i][j].topographyColor[1] = 236;
                world[i][j].topographyColor[2] = 198;
            }
            else if ( between( world[i][j].altitude, -200, 0 ) )
            {
                world[i][j].topographyColor[0] = 254;
                world[i][j].topographyColor[1] = 242;
                world[i][j].topographyColor[2] = 216;
            }
            else if ( between( world[i][j].altitude, 0, 200 ) )
            {
                world[i][j].topographyColor[0] = 165;
                world[i][j].topographyColor[1] = 208;
                world[i][j].topographyColor[2] = 172;
            }
            else if ( between( world[i][j].altitude, 200, 400 ) )
            {
                world[i][j].topographyColor[0] = 139;
                world[i][j].topographyColor[1] = 191;
                world[i][j].topographyColor[2] = 148;
            }
            else if ( between( world[i][j].altitude, 400, 600 ) )
            {
                world[i][j].topographyColor[0] = 143;
                world[i][j].topographyColor[1] = 198;
                world[i][j].topographyColor[2] = 168;
            }
            else if ( between( world[i][j].altitude, 600, 800 ) )
            {
                world[i][j].topographyColor[0] = 150;
                world[i][j].topographyColor[1] = 204;
                world[i][j].topographyColor[2] = 189;
            }
            else if ( between( world[i][j].altitude, 800, 1000 ) )
            {
                world[i][j].topographyColor[0] = 171;
                world[i][j].topographyColor[1] = 215;
                world[i][j].topographyColor[2] = 209;
            }
            else if ( between( world[i][j].altitude, 1000, 1200 ) )
            {
                world[i][j].topographyColor[0] = 181;
                world[i][j].topographyColor[1] = 228;
                world[i][j].topographyColor[2] = 225;
            }
            else if ( between( world[i][j].altitude, 1200, 1400 ) )
            {
                world[i][j].topographyColor[0] = 192;
                world[i][j].topographyColor[1] = 235;
                world[i][j].topographyColor[2] = 239;
            }
            else if ( between( world[i][j].altitude, 1400, 1600 ) )
            {
                world[i][j].topographyColor[0] = 163;
                world[i][j].topographyColor[1] = 214;
                world[i][j].topographyColor[2] = 222;
            }
            else if ( between( world[i][j].altitude, 1600, 1800 ) )
            {
                world[i][j].topographyColor[0] = 157;
                world[i][j].topographyColor[1] = 202;
                world[i][j].topographyColor[2] = 211;
            }
            else if ( between( world[i][j].altitude, 1800, 2000 ) )
            {
                world[i][j].topographyColor[0] = 130;
                world[i][j].topographyColor[1] = 185;
                world[i][j].topographyColor[2] = 202;
            }
            else if ( between( world[i][j].altitude, 2000, 2200 ) )
            {
                world[i][j].topographyColor[0] = 107;
                world[i][j].topographyColor[1] = 167;
                world[i][j].topographyColor[2] = 195;
            }
            else if ( between( world[i][j].altitude, 2200, 2400 ) )
            {
                world[i][j].topographyColor[0] = 90;
                world[i][j].topographyColor[1] = 152;
                world[i][j].topographyColor[2] = 185;
            }
            else if ( between( world[i][j].altitude, 2400, 2600 ) )
            {
                world[i][j].topographyColor[0] = 83;
                world[i][j].topographyColor[1] = 135;
                world[i][j].topographyColor[2] = 170;
            }
            else if ( between( world[i][j].altitude, 2600, 2800 ) )
            {
                world[i][j].topographyColor[0] = 124;
                world[i][j].topographyColor[1] = 154;
                world[i][j].topographyColor[2] = 172;
            }
            else if ( between( world[i][j].altitude, 2800, 3000 ) )
            {
                world[i][j].topographyColor[0] = 154;
                world[i][j].topographyColor[1] = 174;
                world[i][j].topographyColor[2] = 186;
            }
            else if ( between( world[i][j].altitude, 3000, 3200 ) )
            {
                world[i][j].topographyColor[0] = 184;
                world[i][j].topographyColor[1] = 195;
                world[i][j].topographyColor[2] = 202;
            }
            else if ( between( world[i][j].altitude, 3200, 3400 ) )
            {
                world[i][j].topographyColor[0] = 216;
                world[i][j].topographyColor[1] = 222;
                world[i][j].topographyColor[2] = 224;
            }
            else if ( world[i][j].altitude > 3400 )
            {
                world[i][j].topographyColor[0] = 242;
                world[i][j].topographyColor[1] = 244;
                world[i][j].topographyColor[2] = 245;
            }
        }
    }
}
