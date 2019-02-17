#include "world_map.h"

void world_map::set_biome()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {

        }
    }
}

void world_map::color_biome()
{
    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            if( world[i][j].biome == POLAR_DESERT )
            {
                world[i][j].biome_color[0] = 185;
                world[i][j].biome_color[1] = 185;
                world[i][j].biome_color[2] = 185;
            }
            else if( world[i][j].state == SEA )
            {
                world[i][j].biome_color[0] = 216;
                world[i][j].biome_color[1] = 171;
                world[i][j].biome_color[2] = 113;
            }
            else if( world[i][j].state == LAKE )
            {
                world[i][j].biome_color[0] = 171;
                world[i][j].biome_color[1] = 120;
                world[i][j].biome_color[2] = 9;
            }
            else if( world[i][j].biome == ALPINE_TUNDRA )
            {
                world[i][j].biome_color[0] = 215;
                world[i][j].biome_color[1] = 182;
                world[i][j].biome_color[2] = 158;
            }
            else if( world[i][j].biome == TUNDRA )
            {
                world[i][j].biome_color[0] = 195;
                world[i][j].biome_color[1] = 209;
                world[i][j].biome_color[2] = 150;
            }
            else if( world[i][j].biome == DRY_STEPPE )
            {
                world[i][j].biome_color[0] = 61;
                world[i][j].biome_color[1] = 122;
                world[i][j].biome_color[2] = 146;
            }
            else if( world[i][j].biome == TEMPERATE_STEPPE )
            {
                world[i][j].biome_color[0] = 100;
                world[i][j].biome_color[1] = 234;
                world[i][j].biome_color[2] = 246;
            }
            else if( world[i][j].biome == TAIGA )
            {
                world[i][j].biome_color[0] = 89;
                world[i][j].biome_color[1] = 98;
                world[i][j].biome_color[2] = 0;
            }
            else if( world[i][j].biome == CHAPPARALS )
            {
                world[i][j].biome_color[0] = 144;
                world[i][j].biome_color[1] = 107;
                world[i][j].biome_color[2] = 134;
            }
            else if( world[i][j].biome == TEMPERATE_FOREST )
            {
                world[i][j].biome_color[0] = 82;
                world[i][j].biome_color[1] = 220;
                world[i][j].biome_color[2] = 155;
            }
            else if( world[i][j].biome == MONTANE_FOREST )
            {
                world[i][j].biome_color[0] = 142;
                world[i][j].biome_color[1] = 141;
                world[i][j].biome_color[2] = 50;
            }
            else if( world[i][j].biome == SUBTROPICAL_RAINFOREST )
            {
                world[i][j].biome_color[0] = 9;
                world[i][j].biome_color[1] = 115;
                world[i][j].biome_color[2] = 9;
            }
            else if( world[i][j].biome == ARID_DESERT )
            {
                world[i][j].biome_color[0] = 50;
                world[i][j].biome_color[1] = 77;
                world[i][j].biome_color[2] = 139;
            }
            else if( world[i][j].biome == XERIC_SHRUBLAND )
            {
                world[i][j].biome_color[0] = 72;
                world[i][j].biome_color[1] = 106;
                world[i][j].biome_color[2] = 178;
            }
            else if( world[i][j].biome == SEMIARID_DESERT )
            {
                world[i][j].biome_color[0] = 125;
                world[i][j].biome_color[1] = 177;
                world[i][j].biome_color[2] = 218;
            }
            else if( world[i][j].biome == GRASS_SAVANNA )
            {
                world[i][j].biome_color[0] = 73;
                world[i][j].biome_color[1] = 195;
                world[i][j].biome_color[2] = 199;
            }
            else if( world[i][j].biome == TREE_SAVANNA )
            {
                world[i][j].biome_color[0] = 19;
                world[i][j].biome_color[1] = 158;
                world[i][j].biome_color[2] = 164;
            }
            else if( world[i][j].biome == SUBTROPICAL_DRY_FOREST )
            {
                world[i][j].biome_color[0] = 43;
                world[i][j].biome_color[1] = 132;
                world[i][j].biome_color[2] = 107;
            }
            else if( world[i][j].biome == MONSOON_FOREST )
            {
                world[i][j].biome_color[0] = 100;
                world[i][j].biome_color[1] = 139;
                world[i][j].biome_color[2] = 100;
            }
            else if( world[i][j].biome == TROPICAL_RAINFOREST )
            {
                world[i][j].biome_color[0] = 0;
                world[i][j].biome_color[1] = 81;
                world[i][j].biome_color[2] = 0;
            }
        }
    }
}
