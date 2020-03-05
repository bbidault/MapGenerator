#include "world_map.h"
#include "common.h"

/**
 * @brief initializes seas and lands status
 */
void WorldMap::setSeasAndLands()
{
    visitSea( 0, 0, 0 );

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
                visitSea( i, j, 0 );
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

    setLands();
}

/**
 * @brief set sea status
 *
 * @param aRow latitute of next pixel
 * @param aCol longitude of next pixel
 * @param aVisitedPixels the number of visited pixels so far
 */
void WorldMap::visitSea( int aRow, int aCol, int aVisitedPixels )
{
    world[aRow][aCol].pixelVisited = true;
    world[aRow][aCol].state        = SEA;
    aVisitedPixels++;

    if ( aVisitedPixels < Constants::MaximumNumberOfRecursiveCalls )
    {
        if ( aRow > 0 )
        {
            if ( ( world[aRow - 1][aCol].altitude < 0 ) && ( false == world[aRow - 1][aCol].pixelVisited ) )
            {
                visitSea( aRow - 1, aCol, aVisitedPixels );
            }
        }
        if ( aCol > 0 )
        {
            if ( ( world[aRow][aCol - 1].altitude < 0 ) && ( false == world[aRow][aCol - 1].pixelVisited ) )
            {
                visitSea( aRow, aCol - 1, aVisitedPixels );
            }
        }
        if ( aRow < width - 1 )
        {
            if ( ( world[aRow + 1][aCol].altitude < 0 ) && ( false == world[aRow + 1][aCol].pixelVisited ) )
            {
                visitSea( aRow + 1, aCol, aVisitedPixels );
            }
        }
        if ( aCol < height - 1 )
        {
            if ( ( world[aRow][aCol + 1].altitude < 0 ) && ( false == world[aRow][aCol + 1].pixelVisited ) )
            {
                visitSea( aRow, aCol + 1, aVisitedPixels );
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
                    generateRiver( i, j, Constants::sourceFlow );
                }
            }
        }
    }
}

/**
 * @brief generate a river from source
 *
 * @param aRow latitude of the source
 * @param aCol longitude of the source
 * @param aWaterLeft the water left in the river
 */
void WorldMap::generateRiver( int aRow, int aCol, float aWaterLeft )
{
    aWaterLeft--;
    if ( aWaterLeft <= 0 )
    {
        return;
    }

    float lowestAltitude = world[aRow][aCol].altitude;
    // the position of the river flow destination
    int row = aRow;
    int col = aCol;

    for ( int k = -1; k <= 1; k++ )
    {
        for ( int l = -1; l <= 1; l++ )
        {
            if ( ( std::abs( k ) == 1 ) && ( std::abs( l ) == 1 ) )
            {
                if ( world[aRow + k][aCol + l].altitude < 0 )
                {
                    if ( ( world[aRow + k][aCol + l].altitude / SQRT_2 ) < lowestAltitude )
                    {
                        lowestAltitude = world[aRow + k][aCol + l].altitude;
                        row            = aRow + k;
                        col            = aCol + l;
                    }
                }
                else
                {
                    if ( SQRT_2 * world[aRow + k][aCol + l].altitude < lowestAltitude )
                    {
                        lowestAltitude = world[aRow + k][aCol + l].altitude;
                        row            = aRow + k;
                        col            = aCol + l;
                    }
                }
            }
            else
            {
                if ( world[aRow + k][aCol + l].altitude < lowestAltitude )
                {
                    lowestAltitude = world[aRow + k][aCol + l].altitude;
                    row            = aRow + k;
                    col            = aCol + l;
                }
            }
        }
    }

    if ( ( world[row][col].state == SEA ) ||
         ( world[row][col].seaConnected == true ) )
    {
        setConnection( row, col );
    }
    else if ( ( ( row == aRow ) && ( col == aCol ) ) ||
              ( world[row][col].state == LAKE ) )
    {
        world[row][col].state = LAKE;
        generateLake( row, col, aWaterLeft );
    }
    else if ( world[row][col].state == RIVER )
    {
        findRiverLowestEnd( row, col, aWaterLeft );
    }
    else
    {
        world[row][col].state = RIVER;
        generateRiver( row, col, aWaterLeft );
    }
}

/**
 * @brief update rivers and lakes connection status
 *
 * @param aRow latitude of the source
 * @param aCol longitude of the source
 */
void WorldMap::setConnection( int aRow, int aCol )
{
    for ( int k = -1; k <= 1; k++ )
    {
        for ( int l = -1; l <= 1; l++ )
        {
            if ( ( ( world[aRow + k][aCol + l].state == RIVER ) ||
                   ( world[aRow + k][aCol + l].state == LAKE ) ) &&
                 ( false == world[aRow + k][aCol + l].seaConnected ) )
            {
                world[aRow + k][aCol + l].seaConnected = true;
                setConnection( aRow + k, aCol + l );
            }
        }
    }
}

/**
 * @brief generate a lake from a river
 *
 * @param aRow latitude of the source
 * @param aCol longitude of the source
 * @param aWaterLeft the water left in the river
 */
void WorldMap::generateLake( int aRow, int aCol, float aWaterLeft )
{
    bool  buildingLake   = true;
    float lowestAltitude = 10000.0F;

    // sub-lake studied
    int row = aRow;
    int col = aCol;

    // next addition to the total lake
    int nextRow = aRow;
    int nextCol = aCol;

    // total lake
    std::vector<PixelCoordinates_T> currentLake;

    PixelCoordinates_T newLake;
    newLake.row = aRow;
    newLake.col = aCol;
    currentLake.push_back( newLake );

    if ( world[aRow][aCol].state == LAKE )
    {
        createVectorOfLakes( aRow, aCol, currentLake );
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
                generateRiver( row + 1, col, aWaterLeft );
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
                generateRiver( row - 1, col, aWaterLeft );
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
                generateRiver( row, col + 1, aWaterLeft );
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
                generateRiver( row, col - 1, aWaterLeft );
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
 * @param aRow latitude of the lake
 * @param aCol longitude of the lake
 * @param aLake total lake
 */
void WorldMap::createVectorOfLakes( int aRow, int aCol, std::vector<PixelCoordinates_T> &aLake )
{
    world[aRow][aCol].pixelVisited = true;
    PixelCoordinates_T newLake;

    if ( ( world[aRow + 1][aCol].state == LAKE ) && ( false == world[aRow + 1][aCol].pixelVisited ) )
    {
        newLake.row = aRow + 1;
        newLake.col = aCol;
        aLake.push_back( newLake );
        createVectorOfLakes( aRow + 1, aCol, aLake );
    }
    if ( ( world[aRow - 1][aCol].state == LAKE ) && ( false == world[aRow - 1][aCol].pixelVisited ) )
    {
        newLake.row = aRow - 1;
        newLake.col = aCol;
        aLake.push_back( newLake );
        createVectorOfLakes( aRow - 1, aCol, aLake );
    }
    if ( ( world[aRow][aCol + 1].state == LAKE ) && ( false == world[aRow][aCol + 1].pixelVisited ) )
    {
        newLake.row = aRow;
        newLake.col = aCol + 1;
        aLake.push_back( newLake );
        createVectorOfLakes( aRow, aCol + 1, aLake );
    }
    if ( ( world[aRow][aCol - 1].state == LAKE ) && ( false == world[aRow][aCol - 1].pixelVisited ) )
    {
        newLake.row = aRow;
        newLake.col = aCol - 1;
        aLake.push_back( newLake );
        createVectorOfLakes( aRow, aCol - 1, aLake );
    }
}

/**
 * @brief find lowest end of a drainage system and generate the leftover river from there
 *
 * @param aRow latitude of the river
 * @param aCol longitude of the river
 * @param aWaterLeft the water left in the river
 */
void WorldMap::findRiverLowestEnd( int aRow, int aCol, float aWaterLeft )
{
    // total rivers and lakes
    std::vector<PixelCoordinates_T> drainageSystem;

    PixelCoordinates_T river;
    river.row = aRow;
    river.col = aCol;
    drainageSystem.push_back( river );

    createVectorOfRivers( aRow, aCol, drainageSystem );

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

    generateRiver( futureRiverRow, futureRiverCol, aWaterLeft );
}

/**
 * @brief create a vector listing all the pixels of a lake
 *
 * @param aRow latitude of the river or lake
 * @param aCol longitude of the river or lake
 * @param aDrainageSystem total drainage system
 */
void WorldMap::createVectorOfRivers( int aRow, int aCol, std::vector<PixelCoordinates_T> &aDrainageSystem )
{
    world[aRow][aCol].pixelVisited = true;
    PixelCoordinates_T newRiver;

    for ( int k = -1; k <= 1; k++ )
    {
        for ( int l = -1; l <= 1; l++ )
        {
            if ( ( ( world[aRow + k][aCol + l].state == LAKE ) ||
                   ( world[aRow + k][aCol + l].state == RIVER ) ) &&
                 ( false == world[aRow + k][aCol + l].pixelVisited ) )
            {
                newRiver.row = aRow + k;
                newRiver.col = aCol + l;
                aDrainageSystem.push_back( newRiver );
                createVectorOfRivers( aRow + k, aCol + l, aDrainageSystem );
            }
        }
    }
}
