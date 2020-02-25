#include "stdio.h"
#include "opencv2/opencv.hpp"

/// sea floor altitude
#define SEA_FLOOR -2000

/// coordinates of a certain pixel
//typedef std::pair<int, int> PixelCoordinates_T; // TODO
typedef struct
{
    int row;
    int col;
}PixelCoordinates_T;

/// list of pixel states
typedef enum
{
    NO_STATE = 0,
    SEA,
    LAKE,
    LAND,
    SOURCE,
    RIVER,
    CITY,
    ROAD,
    RAILWAY,
}PixelState_T;

/// list of biomes
typedef enum
{
    NO_BIOME = 0,
    POLAR_DESERT,
    ALPINE_TUNDRA,
    TUNDRA,
    DRY_STEPPE,
    TEMPERATE_STEPPE,
    TAIGA,
    CHAPPARALS,
    TEMPERATE_FOREST,
    MONTANE_FOREST,
    SUBTROPICAL_RAINFOREST,
    ARID_DESERT,
    XERIC_SHRUBLAND,
    SEMIARID_DESERT,
    GRASS_SAVANNA,
    TREE_SAVANNA,
    SUBTROPICAL_DRY_FOREST,
    MONSOON_FOREST,
    TROPICAL_RAINFOREST,
}PixelBiome_T;

/// Pixel class definition : one element of the global map
class Pixel
{
    public:
        cv::Vec3b topographyColor;
        cv::Vec3b q2Q4TempColor;
        cv::Vec3b q1TempColor;
        cv::Vec3b q3TempColor;
        cv::Vec3b precipitationColor;
        cv::Vec3i biomeColor;
        double altitude;
        double q2Q4Temp;
        double q1Temp;
        double q3Temp;
        double precipitation;
        PixelState_T state;
        bool pixelVisited;
        bool seaConnected;
        PixelBiome_T biome;

        /// constructor
        Pixel()
        {
            topographyColor[0]    = 0;
            topographyColor[1]    = 0;
            topographyColor[2]    = 0;
            q2Q4TempColor[0]      = 0;
            q2Q4TempColor[1]      = 0;
            q2Q4TempColor[2]      = 0;
            q1TempColor[0]        = 0;
            q1TempColor[1]        = 0;
            q1TempColor[2]        = 0;
            q3TempColor[0]        = 0;
            q3TempColor[1]        = 0;
            q3TempColor[2]        = 0;
            precipitationColor[0] = 0;
            precipitationColor[1] = 0;
            precipitationColor[2] = 0;
            biomeColor[0]         = 0;
            biomeColor[1]         = 0;
            biomeColor[2]         = 0;
            altitude              = SEA_FLOOR;
            q2Q4Temp              = 0;
            q1Temp                = 0;
            q3Temp                = 0;
            precipitation         = 0;
            state                 = NO_STATE;
            pixelVisited          = false;
            seaConnected          = false;
            biome                 = NO_BIOME;
        }
};
