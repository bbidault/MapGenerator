#include "stdio.h"
#include "opencv2/opencv.hpp"

/// sea floor altitude
#define SEA_FLOOR -2000


/// coordinates of a certain pixel
struct pixel_coordinates
{
    int row;
    int col;
};

/// list of pixel states
enum pixel_state
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
};

/// list of biomes
enum pixel_biome
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
};

/// pixel class definition : one element of the global map
class pixel
{
    public:
        cv::Vec3b topography_color;
        cv::Vec3b Q2_Q4_temp_color;
        cv::Vec3b Q1_temp_color;
        cv::Vec3b Q3_temp_color;
        cv::Vec3b precipitation_color;
        cv::Vec3i biome_color;
        double altitude;
        double Q2_Q4_temp;
        double Q1_temp;
        double Q3_temp;
        double precipitation;
        pixel_state state;
        bool pixel_visited;
        bool sea_connected;
        pixel_biome biome;

        /// constructor
        pixel()
        {
            topography_color[0] = 0;
            topography_color[1] = 0;
            topography_color[2] = 0;
            Q2_Q4_temp_color[0] = 0;
            Q2_Q4_temp_color[1] = 0;
            Q2_Q4_temp_color[2] = 0;
            Q1_temp_color[0] = 0;
            Q1_temp_color[1] = 0;
            Q1_temp_color[2] = 0;
            Q3_temp_color[0] = 0;
            Q3_temp_color[1] = 0;
            Q3_temp_color[2] = 0;
            precipitation_color[0] = 0;
            precipitation_color[1] = 0;
            precipitation_color[2] = 0;
            biome_color[0] = 0;
            biome_color[1] = 0;
            biome_color[2] = 0;
            altitude = SEA_FLOOR;
            Q2_Q4_temp = 0;
            Q1_temp = 0;
            Q3_temp = 0;
            precipitation = 0;
            state = NO_STATE;
            pixel_visited = false;
            sea_connected = false;
            biome = NO_BIOME;
        }
};
