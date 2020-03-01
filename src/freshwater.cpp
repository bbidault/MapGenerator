#include "world_map.h"
#include "common.h"

/**
 * @brief initializes seas, lakes and lands status
 */
void WorldMap::setSeasLakesLands()
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

    this->setLakesLands();
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
 * @brief set lake and land status
 */
void WorldMap::setLakesLands()
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            if ( ( world[i][j].altitude < 0 ) && ( world[i][j].state == NO_STATE ) )
            {
                world[i][j].state = LAKE;
            }
            else if ( world[i][j].state == NO_STATE )
            {
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
                    this->generateRiver( i, j );
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
 */
void WorldMap::generateRiver( int i, int j )
{
    double lowest = world[i][j].altitude;
    // the position of the river flow destination
    int row = i;
    int col = j;

    for ( int k = 0; k < 3; k++ )
    {
        for ( int l = 0; l < 3; l++ )
        {
            if ( ( std::abs( k - 1 ) == 1 ) && ( std::abs( l - 1 ) == 1 ) )
            {
                if ( SQRT_2 * world[i + k - 1][j + l - 1].altitude < lowest )
                {
                    lowest = world[i + k - 1][j + l - 1].altitude;
                    row    = i + k - 1;
                    col    = j + l - 1;
                }
            }
            else
            {
                if ( world[i + k - 1][j + l - 1].altitude < lowest )
                {
                    lowest = world[i + k - 1][j + l - 1].altitude;
                    row    = i + k - 1;
                    col    = j + l - 1;
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
        this->generateLake( row, col );
    }
    else
    {
        world[row][col].state = RIVER;
        this->generateRiver( row, col );
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
 */
void WorldMap::generateLake( int i, int j )
{
    bool   buildingLake = true;
    double lowest       = 10000;

    // sub-lake studied
    int col = i;
    int row = j;

    // next addition to the total lake
    int nextRow = i;
    int nextCol = j;

    // total lake
    std::vector<PixelCoordinates_T> currentLake;

    PixelCoordinates_T newLake;
    newLake.row = i;
    newLake.col = j;
    currentLake.push_back( newLake );

    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            world[i][j].pixelVisited = false;
        }
    }

    if ( world[i][j].state == LAKE )
    {
        this->createVectorOfLakes( i, j, currentLake );
    }

    while ( buildingLake )
    {
        lowest = 10000;

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
                this->generateRiver( row + 1, col );
                buildingLake = false;
                break;
            }
            else if ( ( world[row + 1][col].altitude < lowest ) &&
                      ( world[row + 1][col].state != LAKE ) )
            {
                lowest  = world[row + 1][col].altitude;
                nextRow = row + 1;
                nextCol = col;
            }

            if ( ( world[row - 1][col].altitude < world[row][col].altitude ) &&
                 ( world[row - 1][col].state != LAKE ) &&
                 ( world[row - 1][col].state != RIVER ) )
            {
                world[row - 1][col].state = RIVER;
                this->generateRiver( row - 1, col );
                buildingLake = false;
                break;
            }
            else if ( ( world[row - 1][col].altitude < lowest ) &&
                      ( world[row - 1][col].state != LAKE ) )
            {
                lowest  = world[row - 1][col].altitude;
                nextRow = row - 1;
                nextCol = col;
            }

            if ( ( world[row][col + 1].altitude < world[row][col].altitude ) &&
                 ( world[row][col + 1].state != LAKE ) &&
                 ( world[row][col + 1].state != RIVER ) )
            {
                world[row][col + 1].state = RIVER;
                this->generateRiver( row, col + 1 );
                buildingLake = false;
                break;
            }
            else if ( ( world[row][col + 1].altitude < lowest ) &&
                      ( world[row][col + 1].state != LAKE ) )
            {
                lowest  = world[row][col + 1].altitude;
                nextRow = row;
                nextCol = col + 1;
            }

            if ( ( world[row][col - 1].altitude < world[row][col].altitude ) &&
                 ( world[row][col - 1].state != LAKE ) &&
                 ( world[row][col - 1].state != RIVER ) )
            {
                world[row][col - 1].state = RIVER;
                this->generateRiver( row, col - 1 );
                buildingLake = false;
                break;
            }
            else if ( ( world[row][col - 1].altitude < lowest ) &&
                      ( world[row][col - 1].state != LAKE ) )
            {
                lowest  = world[row][col - 1].altitude;
                nextRow = row;
                nextCol = col - 1;
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
