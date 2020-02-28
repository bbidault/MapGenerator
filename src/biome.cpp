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
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::PolarDesert : biomeColors::PolarDesertRealist;
            }
            else if ( world[i][j].state == SEA )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::Sea : biomeColors::SeaRealist;
            }
            else if ( world[i][j].state == LAKE )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::Lake : biomeColors::LakeRealist;
            }
            else if ( world[i][j].biome == ALPINE_TUNDRA )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::AlpineTundra : biomeColors::AlpineTundraRealist;
            }
            else if ( world[i][j].biome == TUNDRA )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::Tundra : biomeColors::TundraRealist;
            }
            else if ( world[i][j].biome == DRY_STEPPE )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::DrySteppe : biomeColors::DrySteppeRealist;
            }
            else if ( world[i][j].biome == TEMPERATE_STEPPE )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::TemperateSteppe : biomeColors::TemperateSteppeRealist;
            }
            else if ( world[i][j].biome == TAIGA )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::Taiga : biomeColors::TaigaRealist;
            }
            else if ( world[i][j].biome == CHAPPARALS )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::Chapparals : biomeColors::ChapparalsRealist;
            }
            else if ( world[i][j].biome == TEMPERATE_FOREST )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::TemperateForest : biomeColors::TemperateForestRealist;
            }
            else if ( world[i][j].biome == MONTANE_FOREST )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::MontaneForest : biomeColors::MontaneForestRealist;
            }
            else if ( world[i][j].biome == SUBTROPICAL_RAINFOREST )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::SubtropicalRainForest : biomeColors::SubtropicalRainForestRealist;
            }
            else if ( world[i][j].biome == ARID_DESERT )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::AridDesert : biomeColors::AridDesertRealist;
            }
            else if ( world[i][j].biome == XERIC_SHRUBLAND )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::XericShrubland : biomeColors::XericShrublandRealist;
            }
            else if ( world[i][j].biome == SEMIARID_DESERT )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::SemiAridDesert : biomeColors::SemiAridDesertRealist;
            }
            else if ( world[i][j].biome == GRASS_SAVANNA )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::GrassSavanna : biomeColors::GrassSavannaRealist;
            }
            else if ( world[i][j].biome == TREE_SAVANNA )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::TreeSavanna : biomeColors::TreeSavannaRealist;
            }
            else if ( world[i][j].biome == SUBTROPICAL_DRY_FOREST )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::SubtropicalDryForest : biomeColors::SubtropicalDryForestRealist;
            }
            else if ( world[i][j].biome == MONSOON_FOREST )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::MontaneForest : biomeColors::MontaneForestRealist;
            }
            else if ( world[i][j].biome == TROPICAL_RAINFOREST )
            {
                world[i][j].biomeColor = ( aRealist ) ? biomeColors::TropicalRainForest : biomeColors::TropicalRainForestRealist;
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
