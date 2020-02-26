#include "world_map.h"
#include "common.h"

/**
 * @brief evaluate pixel biome from temperature and precipitation
 */
void WorldMap::setBiome()
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            if ( ( world[i][j].state == SEA ) || ( world[i][j].state == LAKE ) )
            {
                if ( world[i][j].q2Q4Temp < -10 )
                {
                    world[i][j].biome = POLAR_DESERT;
                }
            }
            else
            {
                if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 4500 / 10 - 7875 )
                {
                    if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 500 / 35 - 500 / 7 )
                    {
                        world[i][j].biome = ARID_DESERT;
                    }
                    else if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 750 / 30 )
                    {
                        world[i][j].biome = XERIC_SHRUBLAND;
                    }
                    else if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 1000 / 15 - 1000 )
                    {
                        world[i][j].biome = SEMIARID_DESERT;
                    }
                    else if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 1250 / 30 )
                    {
                        world[i][j].biome = GRASS_SAVANNA;
                    }
                    else if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 2000 / 42.5 + 12.5 * 2000 / 42.5 )
                    {
                        world[i][j].biome = TREE_SAVANNA;
                    }
                    else if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 2750 / 42.5 + 12.5 * 2750 / 42.5 )
                    {
                        world[i][j].biome = SUBTROPICAL_DRY_FOREST;
                    }
                    else if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 3500 / 42.5 + 12.5 * 3500 / 42.5 )
                    {
                        world[i][j].biome = SUBTROPICAL_RAINFOREST;
                    }
                    else
                    {
                        world[i][j].biome = TROPICAL_RAINFOREST;
                    }
                }
                else if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 4500 / 10 - 2250 )
                {
                    if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 500 / 35 - 500 / 7 )
                    {
                        world[i][j].biome = DRY_STEPPE;
                    }
                    else if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 750 / 30 )
                    {
                        world[i][j].biome = TEMPERATE_STEPPE;
                    }
                    else if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 1250 / 30 )
                    {
                        world[i][j].biome = CHAPPARALS;
                    }
                    else
                    {
                        if ( world[i][j].altitude < 2000 )
                        {
                            world[i][j].biome = TEMPERATE_FOREST;
                        }
                        else
                        {
                            world[i][j].biome = MONTANE_FOREST;
                        }
                    }
                }
                else if ( world[i][j].q2Q4Temp > 0 )
                {
                    if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 500 / 35 - 500 / 7 )
                    {
                        world[i][j].biome = DRY_STEPPE;
                    }
                    else if ( world[i][j].precipitation < world[i][j].q2Q4Temp * 1250 / 30 )
                    {
                        world[i][j].biome = CHAPPARALS;
                    }
                    else
                    {
                        world[i][j].biome = TAIGA;
                    }
                }
                else
                {
                    if ( world[i][j].q2Q4Temp > -5 )
                    {
                        if ( world[i][j].altitude < 2000 )
                        {
                            world[i][j].biome = TUNDRA;
                        }
                        else
                        {
                            world[i][j].biome = ALPINE_TUNDRA;
                        }
                    }
                    else
                    {
                        world[i][j].biome = POLAR_DESERT;
                    }
                }
            }
        }
    }
}

/**
 * @brief color biome map
 *
 * @param aRealist whether the set of displayed color should be realistic or shematic
 */
void WorldMap::colorBiome( bool aRealist )
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            if ( world[i][j].biome == POLAR_DESERT )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 255 : 185;
                world[i][j].biomeColor[1] = ( aRealist ) ? 255 : 185;
                world[i][j].biomeColor[2] = ( aRealist ) ? 255 : 185;
            }
            else if ( world[i][j].state == SEA )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 50 : 216;
                world[i][j].biomeColor[1] = ( aRealist ) ? 10 : 171;
                world[i][j].biomeColor[2] = ( aRealist ) ? 11 : 113;
            }
            else if ( world[i][j].state == LAKE )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 50 : 171;
                world[i][j].biomeColor[1] = ( aRealist ) ? 10 : 120;
                world[i][j].biomeColor[2] = ( aRealist ) ? 11 : 9;
            }
            else if ( world[i][j].biome == ALPINE_TUNDRA )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 235 : 215;
                world[i][j].biomeColor[1] = ( aRealist ) ? 240 : 182;
                world[i][j].biomeColor[2] = ( aRealist ) ? 240 : 158;
            }
            else if ( world[i][j].biome == TUNDRA )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 140 : 195;
                world[i][j].biomeColor[1] = ( aRealist ) ? 173 : 209;
                world[i][j].biomeColor[2] = ( aRealist ) ? 189 : 150;
            }
            else if ( world[i][j].biome == DRY_STEPPE )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 65 : 61;
                world[i][j].biomeColor[1] = ( aRealist ) ? 99 : 122;
                world[i][j].biomeColor[2] = ( aRealist ) ? 112 : 146;
            }
            else if ( world[i][j].biome == TEMPERATE_STEPPE )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 29 : 100;
                world[i][j].biomeColor[1] = ( aRealist ) ? 86 : 234;
                world[i][j].biomeColor[2] = ( aRealist ) ? 71 : 246;
            }
            else if ( world[i][j].biome == TAIGA )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 11 : 89;
                world[i][j].biomeColor[1] = ( aRealist ) ? 49 : 98;
                world[i][j].biomeColor[2] = ( aRealist ) ? 37 : 0;
            }
            else if ( world[i][j].biome == CHAPPARALS )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 89 : 144;
                world[i][j].biomeColor[1] = ( aRealist ) ? 133 : 107;
                world[i][j].biomeColor[2] = ( aRealist ) ? 157 : 134;
            }
            else if ( world[i][j].biome == TEMPERATE_FOREST )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 11 : 82;
                world[i][j].biomeColor[1] = ( aRealist ) ? 74 : 220;
                world[i][j].biomeColor[2] = ( aRealist ) ? 48 : 155;
            }
            else if ( world[i][j].biome == MONTANE_FOREST )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 10 : 142;
                world[i][j].biomeColor[1] = ( aRealist ) ? 38 : 141;
                world[i][j].biomeColor[2] = ( aRealist ) ? 22 : 50;
            }
            else if ( world[i][j].biome == SUBTROPICAL_RAINFOREST )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 13 : 9;
                world[i][j].biomeColor[1] = ( aRealist ) ? 84 : 115;
                world[i][j].biomeColor[2] = ( aRealist ) ? 57 : 9;
            }
            else if ( world[i][j].biome == ARID_DESERT )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 175 : 50;
                world[i][j].biomeColor[1] = ( aRealist ) ? 229 : 77;
                world[i][j].biomeColor[2] = ( aRealist ) ? 254 : 139;
            }
            else if ( world[i][j].biome == XERIC_SHRUBLAND )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 121 : 72;
                world[i][j].biomeColor[1] = ( aRealist ) ? 168 : 106;
                world[i][j].biomeColor[2] = ( aRealist ) ? 212 : 178;
            }
            else if ( world[i][j].biome == SEMIARID_DESERT )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 141 : 125;
                world[i][j].biomeColor[1] = ( aRealist ) ? 190 : 177;
                world[i][j].biomeColor[2] = ( aRealist ) ? 246 : 218;
            }
            else if ( world[i][j].biome == GRASS_SAVANNA )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 46 : 73;
                world[i][j].biomeColor[1] = ( aRealist ) ? 117 : 195;
                world[i][j].biomeColor[2] = ( aRealist ) ? 101 : 199;
            }
            else if ( world[i][j].biome == TREE_SAVANNA )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 14 : 19;
                world[i][j].biomeColor[1] = ( aRealist ) ? 88 : 158;
                world[i][j].biomeColor[2] = ( aRealist ) ? 62 : 164;
            }
            else if ( world[i][j].biome == SUBTROPICAL_DRY_FOREST )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 29 : 43;
                world[i][j].biomeColor[1] = ( aRealist ) ? 76 : 132;
                world[i][j].biomeColor[2] = ( aRealist ) ? 73 : 107;
            }
            else if ( world[i][j].biome == MONSOON_FOREST )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 47 : 100;
                world[i][j].biomeColor[1] = ( aRealist ) ? 119 : 139;
                world[i][j].biomeColor[2] = ( aRealist ) ? 106 : 100;
            }
            else if ( world[i][j].biome == TROPICAL_RAINFOREST )
            {
                world[i][j].biomeColor[0] = ( aRealist ) ? 9 : 0;
                world[i][j].biomeColor[1] = ( aRealist ) ? 58 : 81;
                world[i][j].biomeColor[2] = ( aRealist ) ? 38 : 0;
            }
        }
    }
}

/**
 * @brief average biome color map
 */
void WorldMap::averageBiomeColor()
{
    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            if ( ( world[i][j].state != LAKE ) && ( world[i][j].state != SEA ) )
            {
                world[i][j].biomeColor[0] = world[i][j].biomeColor[0] * 2;
                world[i][j].biomeColor[1] = world[i][j].biomeColor[1] * 2;
                world[i][j].biomeColor[2] = world[i][j].biomeColor[2] * 2;
                double denominator = 2;

                if ( ( world[i - 1][j - 1].state != LAKE ) && ( world[i - 1][j - 1].state != SEA ) )
                {
                    world[i][j].biomeColor[0] += world[i - 1][j - 1].biomeColor[0] / SQRT_2;
                    world[i][j].biomeColor[1] += world[i - 1][j - 1].biomeColor[1] / SQRT_2;
                    world[i][j].biomeColor[2] += world[i - 1][j - 1].biomeColor[2] / SQRT_2;
                    denominator               += 1 / SQRT_2;
                }

                if ( ( world[i - 1][j + 1].state != LAKE ) && ( world[i - 1][j + 1].state != SEA ) )
                {
                    world[i][j].biomeColor[0] += world[i - 1][j + 1].biomeColor[0] / SQRT_2;
                    world[i][j].biomeColor[1] += world[i - 1][j + 1].biomeColor[1] / SQRT_2;
                    world[i][j].biomeColor[2] += world[i - 1][j + 1].biomeColor[2] / SQRT_2;
                    denominator               += 1 / SQRT_2;
                }

                if ( ( world[i - 1][j].state != LAKE ) && ( world[i - 1][j].state != SEA ) )
                {
                    world[i][j].biomeColor[0] += world[i - 1][j].biomeColor[0];
                    world[i][j].biomeColor[1] += world[i - 1][j].biomeColor[1];
                    world[i][j].biomeColor[2] += world[i - 1][j].biomeColor[2];
                    denominator               += 1;
                }

                if ( ( world[i][j - 1].state != LAKE ) && ( world[i][j - 1].state != SEA ) )
                {
                    world[i][j].biomeColor[0] += world[i][j - 1].biomeColor[0];
                    world[i][j].biomeColor[1] += world[i][j - 1].biomeColor[1];
                    world[i][j].biomeColor[2] += world[i][j - 1].biomeColor[2];
                    denominator               += 1;
                }

                world[i][j].biomeColor[0] = world[i][j].biomeColor[0] / denominator;
                world[i][j].biomeColor[1] = world[i][j].biomeColor[1] / denominator;
                world[i][j].biomeColor[2] = world[i][j].biomeColor[2] / denominator;
            }
        }
    }

    for ( int i = width - 2; i > 0; i-- )
    {
        for ( int j = height - 2; j > 0; j-- )
        {
            if ( ( world[i][j].state != LAKE ) && ( world[i][j].state != SEA ) )
            {
                world[i][j].biomeColor[0] = world[i][j].biomeColor[0] * 2;
                world[i][j].biomeColor[1] = world[i][j].biomeColor[1] * 2;
                world[i][j].biomeColor[2] = world[i][j].biomeColor[2] * 2;
                double denominator = 2;

                if ( ( world[i + 1][j + 1].state != LAKE ) && ( world[i + 1][j + 1].state != SEA ) )
                {
                    world[i][j].biomeColor[0] += world[i + 1][j + 1].biomeColor[0] / SQRT_2;
                    world[i][j].biomeColor[1] += world[i + 1][j + 1].biomeColor[1] / SQRT_2;
                    world[i][j].biomeColor[2] += world[i + 1][j + 1].biomeColor[2] / SQRT_2;
                    denominator               += 1 / SQRT_2;
                }

                if ( ( world[i + 1][j - 1].state != LAKE ) && ( world[i + 1][j - 1].state != SEA ) )
                {
                    world[i][j].biomeColor[0] += world[i + 1][j - 1].biomeColor[0] / SQRT_2;
                    world[i][j].biomeColor[1] += world[i + 1][j - 1].biomeColor[1] / SQRT_2;
                    world[i][j].biomeColor[2] += world[i + 1][j - 1].biomeColor[2] / SQRT_2;
                    denominator               += 1 / SQRT_2;
                }

                if ( ( world[i + 1][j].state != LAKE ) && ( world[i + 1][j].state != SEA ) )
                {
                    world[i][j].biomeColor[0] += world[i + 1][j].biomeColor[0];
                    world[i][j].biomeColor[1] += world[i + 1][j].biomeColor[1];
                    world[i][j].biomeColor[2] += world[i + 1][j].biomeColor[2];
                    denominator               += 1;
                }

                if ( ( world[i][j + 1].state != LAKE ) && ( world[i][j + 1].state != SEA ) )
                {
                    world[i][j].biomeColor[0] += world[i][j + 1].biomeColor[0];
                    world[i][j].biomeColor[1] += world[i][j + 1].biomeColor[1];
                    world[i][j].biomeColor[2] += world[i][j + 1].biomeColor[2];
                    denominator               += 1;
                }

                world[i][j].biomeColor[0] = world[i][j].biomeColor[0] / denominator;
                world[i][j].biomeColor[1] = world[i][j].biomeColor[1] / denominator;
                world[i][j].biomeColor[2] = world[i][j].biomeColor[2] / denominator;
            }
        }
    }
}
