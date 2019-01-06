#include "stdio.h"
#include "opencv2/opencv.hpp"

enum pixel_state
{

    NOTHING = 0,
    SOURCE,
    RIVER,
    LAKE,
    CITY,
    ROAD,
    RAILWAY,
};

class pixel
{
    public:
        cv::Vec3b topography_color;
        cv::Vec3b heat_color;
        cv::Vec3b rainfall_color;
        double altitude;
        double temperature;
        double rainfall;
        bool visited;
        pixel_state state;

        pixel()
        {
            topography_color[0] = 0;
            topography_color[1] = 0;
            topography_color[2] = 0;
            heat_color[0] = 0;
            heat_color[1] = 0;
            heat_color[2] = 0;
            rainfall_color[0] = 0;
            rainfall_color[1] = 0;
            rainfall_color[2] = 0;
            altitude = -2000;
            temperature = 0;
            rainfall = 0;
            visited = false;
            state = NOTHING;
        }
};
