#include "world_map.h"
#include "common.h"

void world_map::set_biome()
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            if ( ( world[i][j].state == SEA ) || ( world[i][j].state == LAKE ) )
            {
                if ( world[i][j].Q2_Q4_temp < -10 )
                {
                    world[i][j].biome = POLAR_DESERT;
                }
            }
            else
            {
                if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 4500 / 10 - 7875 )
                {
                    if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 500 / 35 - 500 / 7 )
                    {
                        world[i][j].biome = ARID_DESERT;
                    }
                    else if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 750 / 30 )
                    {
                        world[i][j].biome = XERIC_SHRUBLAND;
                    }
                    else if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 1000 / 15 - 1000 )
                    {
                        world[i][j].biome = SEMIARID_DESERT;
                    }
                    else if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 1250 / 30 )
                    {
                        world[i][j].biome = GRASS_SAVANNA;
                    }
                    else if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 2000 / 42.5 + 12.5 * 2000 / 42.5 )
                    {
                        world[i][j].biome = TREE_SAVANNA;
                    }
                    else if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 2750 / 42.5 + 12.5 * 2750 / 42.5 )
                    {
                        world[i][j].biome = SUBTROPICAL_DRY_FOREST;
                    }
                    else if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 3500 / 42.5 + 12.5 * 3500 / 42.5 )
                    {
                        world[i][j].biome = SUBTROPICAL_RAINFOREST;
                    }
                    else
                    {
                        world[i][j].biome = TROPICAL_RAINFOREST;
                    }
                }
                else if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 4500 / 10 - 2250 )
                {
                    if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 500 / 35 - 500 / 7 )
                    {
                        world[i][j].biome = DRY_STEPPE;
                    }
                    else if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 750 / 30 )
                    {
                        world[i][j].biome = TEMPERATE_STEPPE;
                    }
                    else if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 1250 / 30 )
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
                else if ( world[i][j].Q2_Q4_temp > 0 )
                {
                    if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 500 / 35 - 500 / 7 )
                    {
                        world[i][j].biome = DRY_STEPPE;
                    }
                    else if ( world[i][j].precipitation < world[i][j].Q2_Q4_temp * 1250 / 30 )
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
                    if ( world[i][j].Q2_Q4_temp > -5 )
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

void world_map::color_biome( bool realist )
{
    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            if ( world[i][j].biome == POLAR_DESERT )
            {
                world[i][j].biome_color[0] = ( realist ) ? 255 : 185;
                world[i][j].biome_color[1] = ( realist ) ? 255 : 185;
                world[i][j].biome_color[2] = ( realist ) ? 255 : 185;
            }
            else if ( world[i][j].state == SEA )
            {
                world[i][j].biome_color[0] = ( realist ) ? 50 : 216;
                world[i][j].biome_color[1] = ( realist ) ? 10 : 171;
                world[i][j].biome_color[2] = ( realist ) ? 11 : 113;
            }
            else if ( world[i][j].state == LAKE )
            {
                world[i][j].biome_color[0] = ( realist ) ? 50 : 171;
                world[i][j].biome_color[1] = ( realist ) ? 10 : 120;
                world[i][j].biome_color[2] = ( realist ) ? 11 : 9;
            }
            else if ( world[i][j].biome == ALPINE_TUNDRA )
            {
                world[i][j].biome_color[0] = ( realist ) ? 235 : 215;
                world[i][j].biome_color[1] = ( realist ) ? 240 : 182;
                world[i][j].biome_color[2] = ( realist ) ? 240 : 158;
            }
            else if ( world[i][j].biome == TUNDRA )
            {
                world[i][j].biome_color[0] = ( realist ) ? 140 : 195;
                world[i][j].biome_color[1] = ( realist ) ? 173 : 209;
                world[i][j].biome_color[2] = ( realist ) ? 189 : 150;
            }
            else if ( world[i][j].biome == DRY_STEPPE )
            {
                world[i][j].biome_color[0] = ( realist ) ? 65 : 61;
                world[i][j].biome_color[1] = ( realist ) ? 99 : 122;
                world[i][j].biome_color[2] = ( realist ) ? 112 : 146;
            }
            else if ( world[i][j].biome == TEMPERATE_STEPPE )
            {
                world[i][j].biome_color[0] = ( realist ) ? 29 : 100;
                world[i][j].biome_color[1] = ( realist ) ? 86 : 234;
                world[i][j].biome_color[2] = ( realist ) ? 71 : 246;
            }
            else if ( world[i][j].biome == TAIGA )
            {
                world[i][j].biome_color[0] = ( realist ) ? 11 : 89;
                world[i][j].biome_color[1] = ( realist ) ? 49 : 98;
                world[i][j].biome_color[2] = ( realist ) ? 37 : 0;
            }
            else if ( world[i][j].biome == CHAPPARALS )
            {
                world[i][j].biome_color[0] = ( realist ) ? 89 : 144;
                world[i][j].biome_color[1] = ( realist ) ? 133 : 107;
                world[i][j].biome_color[2] = ( realist ) ? 157 : 134;
            }
            else if ( world[i][j].biome == TEMPERATE_FOREST )
            {
                world[i][j].biome_color[0] = ( realist ) ? 11 : 82;
                world[i][j].biome_color[1] = ( realist ) ? 74 : 220;
                world[i][j].biome_color[2] = ( realist ) ? 48 : 155;
            }
            else if ( world[i][j].biome == MONTANE_FOREST )
            {
                world[i][j].biome_color[0] = ( realist ) ? 10 : 142;
                world[i][j].biome_color[1] = ( realist ) ? 38 : 141;
                world[i][j].biome_color[2] = ( realist ) ? 22 : 50;
            }
            else if ( world[i][j].biome == SUBTROPICAL_RAINFOREST )
            {
                world[i][j].biome_color[0] = ( realist ) ? 13 : 9;
                world[i][j].biome_color[1] = ( realist ) ? 84 : 115;
                world[i][j].biome_color[2] = ( realist ) ? 57 : 9;
            }
            else if ( world[i][j].biome == ARID_DESERT )
            {
                world[i][j].biome_color[0] = ( realist ) ? 175 : 50;
                world[i][j].biome_color[1] = ( realist ) ? 229 : 77;
                world[i][j].biome_color[2] = ( realist ) ? 254 : 139;
            }
            else if ( world[i][j].biome == XERIC_SHRUBLAND )
            {
                world[i][j].biome_color[0] = ( realist ) ? 121 : 72;
                world[i][j].biome_color[1] = ( realist ) ? 168 : 106;
                world[i][j].biome_color[2] = ( realist ) ? 212 : 178;
            }
            else if ( world[i][j].biome == SEMIARID_DESERT )
            {
                world[i][j].biome_color[0] = ( realist ) ? 141 : 125;
                world[i][j].biome_color[1] = ( realist ) ? 190 : 177;
                world[i][j].biome_color[2] = ( realist ) ? 246 : 218;
            }
            else if ( world[i][j].biome == GRASS_SAVANNA )
            {
                world[i][j].biome_color[0] = ( realist ) ? 46 : 73;
                world[i][j].biome_color[1] = ( realist ) ? 117 : 195;
                world[i][j].biome_color[2] = ( realist ) ? 101 : 199;
            }
            else if ( world[i][j].biome == TREE_SAVANNA )
            {
                world[i][j].biome_color[0] = ( realist ) ? 14 : 19;
                world[i][j].biome_color[1] = ( realist ) ? 88 : 158;
                world[i][j].biome_color[2] = ( realist ) ? 62 : 164;
            }
            else if ( world[i][j].biome == SUBTROPICAL_DRY_FOREST )
            {
                world[i][j].biome_color[0] = ( realist ) ? 29 : 43;
                world[i][j].biome_color[1] = ( realist ) ? 76 : 132;
                world[i][j].biome_color[2] = ( realist ) ? 73 : 107;
            }
            else if ( world[i][j].biome == MONSOON_FOREST )
            {
                world[i][j].biome_color[0] = ( realist ) ? 47 : 100;
                world[i][j].biome_color[1] = ( realist ) ? 119 : 139;
                world[i][j].biome_color[2] = ( realist ) ? 106 : 100;
            }
            else if ( world[i][j].biome == TROPICAL_RAINFOREST )
            {
                world[i][j].biome_color[0] = ( realist ) ? 9 : 0;
                world[i][j].biome_color[1] = ( realist ) ? 58 : 81;
                world[i][j].biome_color[2] = ( realist ) ? 38 : 0;
            }
        }
    }
}

void world_map::average_biome_color()
{
    for ( int i = 1; i < width - 1; i++ )
    {
        for ( int j = 1; j < height - 1; j++ )
        {
            if ( ( world[i][j].state != LAKE ) && ( world[i][j].state != SEA ) )
            {
                world[i][j].biome_color[0] = world[i][j].biome_color[0] * 2;
                world[i][j].biome_color[1] = world[i][j].biome_color[1] * 2;
                world[i][j].biome_color[2] = world[i][j].biome_color[2] * 2;
                double denominator = 2;

                if ( ( world[i - 1][j - 1].state != LAKE ) && ( world[i - 1][j - 1].state != SEA ) )
                {
                    world[i][j].biome_color[0] += world[i - 1][j - 1].biome_color[0] / SQRT_2;
                    world[i][j].biome_color[1] += world[i - 1][j - 1].biome_color[1] / SQRT_2;
                    world[i][j].biome_color[2] += world[i - 1][j - 1].biome_color[2] / SQRT_2;
                    denominator                += 1 / SQRT_2;
                }

                if ( ( world[i - 1][j + 1].state != LAKE ) && ( world[i - 1][j + 1].state != SEA ) )
                {
                    world[i][j].biome_color[0] += world[i - 1][j + 1].biome_color[0] / SQRT_2;
                    world[i][j].biome_color[1] += world[i - 1][j + 1].biome_color[1] / SQRT_2;
                    world[i][j].biome_color[2] += world[i - 1][j + 1].biome_color[2] / SQRT_2;
                    denominator                += 1 / SQRT_2;
                }

                if ( ( world[i - 1][j].state != LAKE ) && ( world[i - 1][j].state != SEA ) )
                {
                    world[i][j].biome_color[0] += world[i - 1][j].biome_color[0];
                    world[i][j].biome_color[1] += world[i - 1][j].biome_color[1];
                    world[i][j].biome_color[2] += world[i - 1][j].biome_color[2];
                    denominator                += 1;
                }

                if ( ( world[i][j - 1].state != LAKE ) && ( world[i][j - 1].state != SEA ) )
                {
                    world[i][j].biome_color[0] += world[i][j - 1].biome_color[0];
                    world[i][j].biome_color[1] += world[i][j - 1].biome_color[1];
                    world[i][j].biome_color[2] += world[i][j - 1].biome_color[2];
                    denominator                += 1;
                }

                world[i][j].biome_color[0] = world[i][j].biome_color[0] / denominator;
                world[i][j].biome_color[1] = world[i][j].biome_color[1] / denominator;
                world[i][j].biome_color[2] = world[i][j].biome_color[2] / denominator;
            }
        }
    }

    for ( int i = width - 2; i > 0; i-- )
    {
        for ( int j = height - 2; j > 0; j-- )
        {
            if ( ( world[i][j].state != LAKE ) && ( world[i][j].state != SEA ) )
            {
                world[i][j].biome_color[0] = world[i][j].biome_color[0] * 2;
                world[i][j].biome_color[1] = world[i][j].biome_color[1] * 2;
                world[i][j].biome_color[2] = world[i][j].biome_color[2] * 2;
                double denominator = 2;

                if ( ( world[i + 1][j + 1].state != LAKE ) && ( world[i + 1][j + 1].state != SEA ) )
                {
                    world[i][j].biome_color[0] += world[i + 1][j + 1].biome_color[0] / SQRT_2;
                    world[i][j].biome_color[1] += world[i + 1][j + 1].biome_color[1] / SQRT_2;
                    world[i][j].biome_color[2] += world[i + 1][j + 1].biome_color[2] / SQRT_2;
                    denominator                += 1 / SQRT_2;
                }

                if ( ( world[i + 1][j - 1].state != LAKE ) && ( world[i + 1][j - 1].state != SEA ) )
                {
                    world[i][j].biome_color[0] += world[i + 1][j - 1].biome_color[0] / SQRT_2;
                    world[i][j].biome_color[1] += world[i + 1][j - 1].biome_color[1] / SQRT_2;
                    world[i][j].biome_color[2] += world[i + 1][j - 1].biome_color[2] / SQRT_2;
                    denominator                += 1 / SQRT_2;
                }

                if ( ( world[i + 1][j].state != LAKE ) && ( world[i + 1][j].state != SEA ) )
                {
                    world[i][j].biome_color[0] += world[i + 1][j].biome_color[0];
                    world[i][j].biome_color[1] += world[i + 1][j].biome_color[1];
                    world[i][j].biome_color[2] += world[i + 1][j].biome_color[2];
                    denominator                += 1;
                }

                if ( ( world[i][j + 1].state != LAKE ) && ( world[i][j + 1].state != SEA ) )
                {
                    world[i][j].biome_color[0] += world[i][j + 1].biome_color[0];
                    world[i][j].biome_color[1] += world[i][j + 1].biome_color[1];
                    world[i][j].biome_color[2] += world[i][j + 1].biome_color[2];
                    denominator                += 1;
                }

                world[i][j].biome_color[0] = world[i][j].biome_color[0] / denominator;
                world[i][j].biome_color[1] = world[i][j].biome_color[1] / denominator;
                world[i][j].biome_color[2] = world[i][j].biome_color[2] / denominator;
            }
        }
    }
}
