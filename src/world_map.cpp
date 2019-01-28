#include "world_map.h"
#include "common.h"


void world_map::display_map( )
{
    cv::Mat topographic_map( height, width, CV_8UC3 );

    cv::Mat avg_temp_map( height, width, CV_8UC3 );

    cv::Mat min_temp_map( height, width, CV_8UC3 );

    cv::Mat max_temp_map( height, width, CV_8UC3 );

    cv::Mat rainfall_map( height, width, CV_8UC3 );

    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            topographic_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].topography_color;

            avg_temp_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].avg_temp_color;

            min_temp_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].min_temp_color;

            max_temp_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].max_temp_color;

            rainfall_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].rainfall_color;
        }
    }

    imshow("Topographic Map", topographic_map);

    imshow("Average temperature Map", avg_temp_map);

    imshow("Minimum temperature Map", min_temp_map);

    imshow("Maximum temperature Map", max_temp_map);

    imshow("Rainfall Map", rainfall_map);
}

void world_map::find_max()
{
    double max_altitude = 0;
    double min_temperature = 1000;
    double max_temperature = -1000;
    double max_rainfall = 0;

    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            if( world[i][j].altitude > max_altitude )
            {
                max_altitude = world[i][j].altitude;
            }
            if( world[i][j].avg_temp > max_temperature )
            {
                max_temperature = world[i][j].avg_temp;
            }
            if( world[i][j].avg_temp < min_temperature )
            {
                min_temperature = world[i][j].avg_temp;
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
