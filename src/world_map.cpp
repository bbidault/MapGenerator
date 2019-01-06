#include "world_map.h"
#include "common.h"


void world_map::display_map( )
{
    cv::Mat topographic_map( height, width, CV_8UC3 );

    cv::Mat heat_map( height, width, CV_8UC3 );

    cv::Mat rainfall_map( height, width, CV_8UC3 );

    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            topographic_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].topography_color;

            heat_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].heat_color;

            rainfall_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].rainfall_color;
        }
    }

    imshow("Topographic Map", topographic_map);

    imshow("Heat Map", heat_map);

    imshow("Rainfall Map", rainfall_map);
}

void world_map::find_max()
{
    double max_altitude = 0;
    double min_temperature = 1000;
    double max_temperature = 0;
    double max_rainfall = 0;

    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            if( world[i][j].altitude > max_altitude )
            {
                max_altitude = world[i][j].altitude;
            }
            if( world[i][j].temperature > max_temperature )
            {
                max_temperature = world[i][j].temperature;
            }
            if( world[i][j].temperature < min_temperature )
            {
                min_temperature = world[i][j].temperature;
            }
            if( world[i][j].rainfall > max_rainfall )
            {
                max_rainfall = world[i][j].rainfall;
            }
        }
    }

    std::cout << "max altitude : " << max_altitude << std::endl;
    std::cout << "max temperature : " << max_temperature << std::endl;
    std::cout << "min temperature : " << min_temperature << std::endl;
    std::cout << "max rainfall : " << max_rainfall << std::endl;
}
