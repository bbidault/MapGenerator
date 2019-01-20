#include "world_map.h"
#include "ctime"


void world_map::create_sources()
{
    srand(time(NULL));

    for( int i = 1 ; i < width - 1 ; i++ )
    {
        for( int j = 1 ; j < height - 1 ; j++ )
        {
            if( world[i][j].altitude > 300
                && world[i][j].rainfall > 1000 
                && world[i][j].altitude < 2000  )
            {
                int k = rand()%500;

                if( k == 0 )
                {
                    world[i][j].state = RIVER;
                    this->generate_river( i, j );
                }
            }
        }
    }
}

void world_map::generate_river( int i, int j )
{
    double lowest = world[i][j].altitude;
    int row = i;
    int col = j;

    for( int k = 0 ; k < 3 ; k++ )
    {
        for( int l = 0 ; l < 3 ; l++ )
        {
            if( abs( k - 1 ) == 1 && abs( l - 1 ) == 1 )
            {
                if( 1.2*world[i + k - 1][j + l - 1].altitude < lowest )
                {
                    lowest = world[i + k - 1][j + l - 1].altitude;
                    row = i + k - 1;
                    col = j + l - 1;
                }
            }
            else
            {
                if( world[i + k - 1][j + l - 1].altitude < lowest )
                {
                    lowest = world[i + k - 1][j + l - 1].altitude;
                    row = i + k - 1;
                    col = j + l - 1;
                }
            }
        }
    }

    if( lowest > 0 && !world[row][col].sea_connected )
    {
        if( row == i && col == j )
        {
            world[row][col].state = LAKE;
            this->generate_lake( row, col );
        }
        else
        {
            world[row][col].state = RIVER;
            this->generate_river( row, col );
        }
    }
    else
    {
        this->set_connection( row, col );
    }
}

void world_map::set_connection( int i, int j )
{
    for( int k = 0 ; k < 3 ; k++ )
    {
        for( int l = 0 ; l < 3 ; l++ )
        {
            if( ( world[i + k - 1][j + l -1].state == RIVER
                  || world[i + k - 1][j + l -1].state == LAKE )
                && !world[i + k - 1][j + l -1].sea_connected )
            {
                world[i + k - 1][j + l -1].sea_connected = true;
                this->set_connection( i + k - 1, j + l - 1 );
            }
        }
    }
}

void world_map::generate_lake( int i, int j )
{
    bool building_lake = true;
    double lowest = 10000;

    /// sub-lake studied
    int col = i;
    int row = j;

    /// next addition to the total lake
    int next_row = i;
    int next_col = j;

    /// total lake
    std::vector <pixel_coordinates> current_lake;
    
    pixel_coordinates new_lake;
    new_lake.row = i;
    new_lake.col = j;
    current_lake.push_back( new_lake );

    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            world[i][j].pixel_visited = false;
        }
    }

    if( world[i][j].state == LAKE )
    {
        this->visit_lake( i, j, current_lake );
    }

    while( building_lake )
    {
        lowest = 10000;

        /// for each sub-lake
        for( int k = 0 ; k < current_lake.size() ; k++ )
        {
            row = current_lake[k].row;
            col = current_lake[k].col;

            /// if the lake overflows
            if( world[row + 1][col].altitude < world[row][col].altitude 
                && world[row + 1][col].state != LAKE
                && world[row + 1][col].state != RIVER )
            {
                world[row + 1][col].state = RIVER;
                this->generate_river( row + 1, col );
                building_lake = false;
                break;
            }
            else if( world[row + 1][col].altitude < lowest 
                     && world[row + 1][col].state != LAKE )
            {
                lowest = world[row + 1][col].altitude;
                next_row = row + 1;
                next_col = col;
            }

            if( world[row - 1][col].altitude < world[row][col].altitude 
                && world[row - 1][col].state != LAKE
                && world[row - 1][col].state != RIVER )
            {
                world[row - 1][col].state = RIVER;
                this->generate_river( row - 1, col );
                building_lake = false;
                break;
            }
            else if( world[row - 1][col].altitude < lowest 
                     && world[row - 1][col].state != LAKE )
            {
                lowest = world[row - 1][col].altitude;
                next_row = row - 1;
                next_col = col;
            }

            if( world[row][col + 1].altitude < world[row][col].altitude 
                && world[row][col + 1].state != LAKE
                && world[row][col + 1].state != RIVER )
            {
                world[row][col + 1].state = RIVER;
                this->generate_river( row, col + 1 );
                building_lake = false;
                break;
            }
            else if( world[row][col + 1].altitude < lowest 
                     && world[row][col + 1].state != LAKE )
            {
                lowest = world[row][col + 1].altitude;
                next_row = row;
                next_col = col + 1;
            }

            if( world[row][col - 1].altitude < world[row][col].altitude 
                && world[row][col - 1].state != LAKE
                && world[row][col - 1].state != RIVER )
            {
                world[row][col - 1].state = RIVER;
                this->generate_river( row, col - 1 );
                building_lake = false;
                break;
            }
            else if( world[row][col - 1].altitude < lowest 
                     && world[row][col - 1].state != LAKE )
            {
                lowest = world[row][col - 1].altitude;
                next_row = row;
                next_col = col - 1;
            }
        }

        if( building_lake )
        {
            world[next_row][next_col].state = LAKE;
            new_lake.row = next_row;
            new_lake.col = next_col;
            current_lake.push_back(new_lake);
        }
    }
}

void world_map::visit_lake( int i, int j, std::vector <pixel_coordinates> &lake )
{
    world[i][j].pixel_visited = true;
    pixel_coordinates new_lake;

    if( world[i + 1][j].state == LAKE && !world[i + 1][j].pixel_visited )
    {
        new_lake.row = i + 1;
        new_lake.col = j;
        lake.push_back( new_lake );
        lake.shrink_to_fit();
        this->visit_lake( i + 1, j, lake );
    }
    if( world[i - 1][j].state == LAKE && !world[i - 1][j].pixel_visited )
    {
        new_lake.row = i - 1;
        new_lake.col = j;
        lake.push_back( new_lake );
        lake.shrink_to_fit();
        this->visit_lake( i - 1, j, lake );
    }
    if( world[i][j + 1].state == LAKE && !world[i][j + 1].pixel_visited )
    {
        new_lake.row = i;
        new_lake.col = j + 1;
        lake.push_back( new_lake );
        lake.shrink_to_fit();
        this->visit_lake( i, j + 1, lake );
    }
    if( world[i][j - 1].state == LAKE && !world[i][j - 1].pixel_visited )
    {
        new_lake.row = i;
        new_lake.col = j - 1;
        lake.push_back( new_lake );
        lake.shrink_to_fit();
        this->visit_lake( i, j - 1, lake );
    }
}
