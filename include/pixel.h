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
    NOTHING = 0,
    SEA,
    LAKE,
    LAND,
    SOURCE,
    RIVER,
    CITY,
    ROAD,
    RAILWAY,
};

/// pixel class definition : one element of the global map
class pixel
{
    public:
        cv::Vec3b topography_color;
        cv::Vec3b avg_temp_color;
        cv::Vec3b min_temp_color;
        cv::Vec3b max_temp_color;
        cv::Vec3b rainfall_color;
        double altitude;
        double avg_temp;
        double min_temp;
        double max_temp;
        double rainfall;
        pixel_state state;
        bool pixel_visited;
        bool sea_connected;

        /// constructor
        pixel()
        {
            topography_color[0] = 0;
            topography_color[1] = 0;
            topography_color[2] = 0;
            avg_temp_color[0] = 0;
            avg_temp_color[1] = 0;
            avg_temp_color[2] = 0;
            min_temp_color[0] = 0;
            min_temp_color[1] = 0;
            min_temp_color[2] = 0;
            max_temp_color[0] = 0;
            max_temp_color[1] = 0;
            max_temp_color[2] = 0;
            rainfall_color[0] = 0;
            rainfall_color[1] = 0;
            rainfall_color[2] = 0;
            altitude = SEA_FLOOR;
            avg_temp = 0;
            min_temp = 0;
            max_temp = 0;
            rainfall = 0;
            state = NOTHING;
            pixel_visited = false;
            sea_connected = false;
        }
};
