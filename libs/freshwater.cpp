#include "world_map.h"
#include "common.h"

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

void WorldMap::visitSea( int i, int j, int k )
{
    world[i][j].pixelVisited = true;
    world[i][j].state        = SEA;
    k++;

    if ( k < 100000 )
    {
        if ( i > 0 )
        {
            if ( ( world[i - 1][j].altitude < 0 ) && !world[i - 1][j].pixelVisited )
            {
                this->visitSea( i - 1, j, k );
            }
        }
        if ( j > 0 )
        {
            if ( ( world[i][j - 1].altitude < 0 ) && !world[i][j - 1].pixelVisited )
            {
                this->visitSea( i, j - 1, k );
            }
        }
        if ( i < width - 1 )
        {
            if ( ( world[i + 1][j].altitude < 0 ) && !world[i + 1][j].pixelVisited )
            {
                this->visitSea( i + 1, j, k );
            }
        }
        if ( j < height - 1 )
        {
            if ( ( world[i][j + 1].altitude < 0 ) && !world[i][j + 1].pixelVisited )
            {
                this->visitSea( i, j + 1, k );
            }
        }
    }

    k--;
}

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
                int k = rand() % 500;

                if ( k == 0 )
                {
                    world[i][j].state = RIVER;
                    this->generateRiver( i, j );
                }
            }
        }
    }
}

void WorldMap::generateRiver( int i, int j )
{
    double lowest = world[i][j].altitude;
    int    row    = i;
    int    col    = j;

    for ( int k = 0; k < 3; k++ )
    {
        for ( int l = 0; l < 3; l++ )
        {
            if ( ( abs( k - 1 ) == 1 ) && ( abs( l - 1 ) == 1 ) )
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

void WorldMap::generateLake( int i, int j )
{
    bool   buildingLake = true;
    double lowest       = 10000;

    /// sub-lake studied
    int col = i;
    int row = j;

    /// next addition to the total lake
    int nextRow = i;
    int nextCol = j;

    /// total lake
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
        this->visitLake( i, j, currentLake );
    }

    while ( buildingLake )
    {
        lowest = 10000;

        /// for each sub-lake
        for ( int k = 0; k < currentLake.size(); k++ )
        {
            row = currentLake[k].row;
            col = currentLake[k].col;

            /// if the lake overflows
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

void WorldMap::visitLake( int i, int j, std::vector<PixelCoordinates_T> &lake )
{
    world[i][j].pixelVisited = true;
    PixelCoordinates_T newLake;

    if ( ( world[i + 1][j].state == LAKE ) && !world[i + 1][j].pixelVisited )
    {
        newLake.row = i + 1;
        newLake.col = j;
        lake.push_back( newLake );
        this->visitLake( i + 1, j, lake );
    }
    if ( ( world[i - 1][j].state == LAKE ) && !world[i - 1][j].pixelVisited )
    {
        newLake.row = i - 1;
        newLake.col = j;
        lake.push_back( newLake );
        this->visitLake( i - 1, j, lake );
    }
    if ( ( world[i][j + 1].state == LAKE ) && !world[i][j + 1].pixelVisited )
    {
        newLake.row = i;
        newLake.col = j + 1;
        lake.push_back( newLake );
        this->visitLake( i, j + 1, lake );
    }
    if ( ( world[i][j - 1].state == LAKE ) && !world[i][j - 1].pixelVisited )
    {
        newLake.row = i;
        newLake.col = j - 1;
        lake.push_back( newLake );
        this->visitLake( i, j - 1, lake );
    }
}
