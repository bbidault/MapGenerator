#include "world_map.h"
#include "common.h"

/**
 * @brief initializes seas and lands status
 */
void WorldMap::setSeasAndLands()
{
    this->visitSea( 0, 0, 0 );

    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            if ( ( world[i][j].state == SEA ) &&
                 ( ( ( world[i + 1][j].altitude < 0 ) && ( world[i + 1][j].state == NO_STATE ) ) ||
                   ( ( world[i - 1][j].altitude < 0 ) && ( world[i - 1][j].state == NO_STATE ) ) ||
                   ( ( world[i][j + 1].altitude < 0 ) && ( world[i][j + 1].state == NO_STATE ) ) ||
                   ( ( world[i][j - 1].altitude < 0 ) && ( world[i][j - 1].state == NO_STATE ) ) ) )
            {
                this->visitSea( i, j, 0 );
            }
        }
    }

    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            world[i][j].pixelVisited = false;
        }
    }

    this->setLands();
}

/**
 * @brief set sea status
 *
 * @param i latitute of next pixel
 * @param j longitude of next pixel
 * @param aVisitedPixels the number of visited pixels so far
 */
void WorldMap::visitSea( int i, int j, int aVisitedPixels )
{
    world[i][j].pixelVisited = true;
    world[i][j].state        = SEA;
    aVisitedPixels++;

    if ( aVisitedPixels < Constants::MaximumNumberOfRecursiveCalls )
    {
        if ( i > 0 )
        {
            if ( ( world[i - 1][j].altitude < 0 ) && !world[i - 1][j].pixelVisited )
            {
                this->visitSea( i - 1, j, aVisitedPixels );
            }
        }
        if ( j > 0 )
        {
            if ( ( world[i][j - 1].altitude < 0 ) && !world[i][j - 1].pixelVisited )
            {
                this->visitSea( i, j - 1, aVisitedPixels );
            }
        }
        if ( i < width - 1 )
        {
            if ( ( world[i + 1][j].altitude < 0 ) && !world[i + 1][j].pixelVisited )
            {
                this->visitSea( i + 1, j, aVisitedPixels );
            }
        }
        if ( j < height - 1 )
        {
            if ( ( world[i][j + 1].altitude < 0 ) && !world[i][j + 1].pixelVisited )
            {
                this->visitSea( i, j + 1, aVisitedPixels );
            }
        }
    }

    aVisitedPixels--;
}

/**
 * @brief set land status
 */
void WorldMap::setLands()
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            if ( world[i][j].state == NO_STATE )
            {
                if ( world[i][j].altitude < 0 )
                {
                    world[i][j].altitude = world[i][j].altitude / 2.0F;
                }
                world[i][j].state = LAND;
            }
        }
    }
}

/**
 * @brief generate sources in locations of high precipitation
 */
void WorldMap::createSources()
{
    srand( time( NULL ) );

    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            if ( ( world[i][j].altitude > 0 ) &&
                 ( world[i][j].precipitation > 1000 ) )
            {
                int sourceProbability = rand() % 500;

                if ( sourceProbability == 0 )
                {
                    world[i][j].state = RIVER;
                    this->generateRiver( i, j, Constants::sourceFlow );
                }
            }
        }
    }
}

/**
 * @brief generate a river from source
 *
 * @param i latitude of the source
 * @param j longitude of the source
 * @param aWaterLeft the water left in the river
 */
void WorldMap::generateRiver( int i, int j, float aWaterLeft )
{
    aWaterLeft--;
    if ( aWaterLeft <= 0 )
    {
        return;
    }

    float lowestAltitude = world[i][j].altitude;
    // the position of the river flow destination
    int row = i;
    int col = j;

    for ( int k = -1; k <= 1; k++ )
    {
        for ( int l = -1; l <= 1; l++ )
        {
            if ( ( std::abs( k ) == 1 ) && ( std::abs( l ) == 1 ) )
            {
                if ( world[i + k][j + l].altitude < 0 )
                {
                    if ( ( world[i + k][j + l].altitude / SQRT_2 ) < lowestAltitude )
                    {
                        lowestAltitude = world[i + k][j + l].altitude;
                        row            = i + k;
                        col            = j + l;
                    }
                }
                else
                {
                    if ( SQRT_2 * world[i + k][j + l].altitude < lowestAltitude )
                    {
                        lowestAltitude = world[i + k][j + l].altitude;
                        row            = i + k;
                        col            = j + l;
                    }
                }
            }
            else
            {
                if ( world[i + k][j + l].altitude < lowestAltitude )
                {
                    lowestAltitude = world[i + k][j + l].altitude;
                    row            = i + k;
                    col            = j + l;
                }
            }
        }
    }

    if ( ( world[row][col].state == SEA ) ||
         ( world[row][col].seaConnected == true ) )
    {
        this->setConnection( row, col );
    }
    else if ( ( ( row == i ) && ( col == j ) ) ||
              ( world[row][col].state == LAKE ) )
    {
        world[row][col].state = LAKE;
        this->generateLake( row, col, aWaterLeft );
    }
    else if ( world[row][col].state == RIVER )
    {
        this->findRiverLowestEnd( row, col, aWaterLeft );
    }
    else
    {
        world[row][col].state = RIVER;
        this->generateRiver( row, col, aWaterLeft );
    }
}

/**
 * @brief update rivers and lakes connection status
 *
 * @param i latitude of the source
 * @param j longitude of the source
 */
void WorldMap::setConnection( int i, int j )
{
    for ( int k = 0; k < 3; k++ )
    {
        for ( int l = 0; l < 3; l++ )
        {
            if ( ( ( world[i + k - 1][j + l - 1].state == RIVER ) ||
                   ( world[i + k - 1][j + l - 1].state == LAKE ) ) &&
                 !world[i + k - 1][j + l - 1].seaConnected )
            {
                world[i + k - 1][j + l - 1].seaConnected = true;
                this->setConnection( i + k - 1, j + l - 1 );
            }
        }
    }
}

/**
 * @brief generate a lake from a river
 *
 * @param i latitude of the source
 * @param j longitude of the source
 * @param aWaterLeft the water left in the river
 */
void WorldMap::generateLake( int i, int j, float aWaterLeft )
{
    bool  buildingLake   = true;
    float lowestAltitude = 10000.0F;

    // sub-lake studied
    int row = i;
    int col = j;

    // next addition to the total lake
    int nextRow = i;
    int nextCol = j;

    // total lake
    std::vector<PixelCoordinates_T> currentLake;

    PixelCoordinates_T newLake;
    newLake.row = i;
    newLake.col = j;
    currentLake.push_back( newLake );

    if ( world[i][j].state == LAKE )
    {
        this->createVectorOfLakes( i, j, currentLake );
    }

    while ( buildingLake )
    {
        aWaterLeft--;
        if ( aWaterLeft <= 0 )
        {
            return;
        }

        lowestAltitude = 10000.0F;

        // for each sub-lake
        for ( int k = 0; k < currentLake.size(); k++ )
        {
            row = currentLake[k].row;
            col = currentLake[k].col;

            // if the lake overflows
            if ( ( world[row + 1][col].altitude < world[row][col].altitude ) &&
                 ( world[row + 1][col].state != LAKE ) &&
                 ( world[row + 1][col].state != RIVER ) )
            {
                world[row + 1][col].state = RIVER;
                this->generateRiver( row + 1, col, aWaterLeft );
                buildingLake = false;
                break;
            }
            else if ( ( world[row + 1][col].altitude < lowestAltitude ) &&
                      ( world[row + 1][col].state != LAKE ) )
            {
                lowestAltitude = world[row + 1][col].altitude;
                nextRow        = row + 1;
                nextCol        = col;
            }

            if ( ( world[row - 1][col].altitude < world[row][col].altitude ) &&
                 ( world[row - 1][col].state != LAKE ) &&
                 ( world[row - 1][col].state != RIVER ) )
            {
                world[row - 1][col].state = RIVER;
                this->generateRiver( row - 1, col, aWaterLeft );
                buildingLake = false;
                break;
            }
            else if ( ( world[row - 1][col].altitude < lowestAltitude ) &&
                      ( world[row - 1][col].state != LAKE ) )
            {
                lowestAltitude = world[row - 1][col].altitude;
                nextRow        = row - 1;
                nextCol        = col;
            }

            if ( ( world[row][col + 1].altitude < world[row][col].altitude ) &&
                 ( world[row][col + 1].state != LAKE ) &&
                 ( world[row][col + 1].state != RIVER ) )
            {
                world[row][col + 1].state = RIVER;
                this->generateRiver( row, col + 1, aWaterLeft );
                buildingLake = false;
                break;
            }
            else if ( ( world[row][col + 1].altitude < lowestAltitude ) &&
                      ( world[row][col + 1].state != LAKE ) )
            {
                lowestAltitude = world[row][col + 1].altitude;
                nextRow        = row;
                nextCol        = col + 1;
            }

            if ( ( world[row][col - 1].altitude < world[row][col].altitude ) &&
                 ( world[row][col - 1].state != LAKE ) &&
                 ( world[row][col - 1].state != RIVER ) )
            {
                world[row][col - 1].state = RIVER;
                this->generateRiver( row, col - 1, aWaterLeft );
                buildingLake = false;
                break;
            }
            else if ( ( world[row][col - 1].altitude < lowestAltitude ) &&
                      ( world[row][col - 1].state != LAKE ) )
            {
                lowestAltitude = world[row][col - 1].altitude;
                nextRow        = row;
                nextCol        = col - 1;
            }
        }

        if ( buildingLake )
        {
            world[nextRow][nextCol].state = LAKE;
            newLake.row                   = nextRow;
            newLake.col                   = nextCol;
            currentLake.push_back( newLake );
        }
    }

    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            world[i][j].pixelVisited = false;
        }
    }
}

/**
 * @brief create a vector listing all the pixels of a lake
 *
 * @param i latitude of the lake
 * @param j longitude of the lake
 * @param aLake total lake
 */
void WorldMap::createVectorOfLakes( int i, int j, std::vector<PixelCoordinates_T> &aLake )
{
    world[i][j].pixelVisited = true;
    PixelCoordinates_T newLake;

    if ( ( world[i + 1][j].state == LAKE ) && !world[i + 1][j].pixelVisited )
    {
        newLake.row = i + 1;
        newLake.col = j;
        aLake.push_back( newLake );
        this->createVectorOfLakes( i + 1, j, aLake );
    }
    if ( ( world[i - 1][j].state == LAKE ) && !world[i - 1][j].pixelVisited )
    {
        newLake.row = i - 1;
        newLake.col = j;
        aLake.push_back( newLake );
        this->createVectorOfLakes( i - 1, j, aLake );
    }
    if ( ( world[i][j + 1].state == LAKE ) && !world[i][j + 1].pixelVisited )
    {
        newLake.row = i;
        newLake.col = j + 1;
        aLake.push_back( newLake );
        this->createVectorOfLakes( i, j + 1, aLake );
    }
    if ( ( world[i][j - 1].state == LAKE ) && !world[i][j - 1].pixelVisited )
    {
        newLake.row = i;
        newLake.col = j - 1;
        aLake.push_back( newLake );
        this->createVectorOfLakes( i, j - 1, aLake );
    }
}

/**
 * @brief find lowest end of a drainage system and generate the leftover river from there
 *
 * @param i latitude of the river
 * @param j longitude of the river
 * @param aWaterLeft the water left in the river
 */
void WorldMap::findRiverLowestEnd( int i, int j, float aWaterLeft )
{
    // total rivers and lakes
    std::vector<PixelCoordinates_T> drainageSystem;

    PixelCoordinates_T river;
    river.row = i;
    river.col = j;
    drainageSystem.push_back( river );

    this->createVectorOfRivers( i, j, drainageSystem );

    float lowestAltitude = 10000.0F;
    int   row;
    int   col;
    int   futureRiverRow;
    int   futureRiverCol;

    for ( int i = 0; i < drainageSystem.size(); i++ )
    {
        row = drainageSystem[i].row;
        col = drainageSystem[i].col;
        if ( ( world[row][col].state == RIVER ) && ( world[row][col].altitude < lowestAltitude ) )
        {
            lowestAltitude = world[row][col].altitude;
            futureRiverRow = row;
            futureRiverCol = col;
        }
    }

    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            world[i][j].pixelVisited = false;
        }
    }

    this->generateRiver( futureRiverRow, futureRiverCol, aWaterLeft );
}

/**
 * @brief create a vector listing all the pixels of a lake
 *
 * @param i latitude of the river or lake
 * @param j longitude of the river or lake
 * @param aDrainageSystem total drainage system
 */
void WorldMap::createVectorOfRivers( int i, int j, std::vector<PixelCoordinates_T> &aDrainageSystem )
{
    world[i][j].pixelVisited = true;
    PixelCoordinates_T newRiver;

    for ( int k = -1; k <= 1; k++ )
    {
        for ( int l = -1; l <= 1; l++ )
        {
            if ( ( ( world[i + k][j + l].state == LAKE ) ||
                   ( world[i + k][j + l].state == RIVER ) ) &&
                 !world[i + k][j + l].pixelVisited )
            {
                newRiver.row = i + k;
                newRiver.col = j + l;
                aDrainageSystem.push_back( newRiver );
                this->createVectorOfRivers( i + k, j + l, aDrainageSystem );
            }
        }
    }
}
