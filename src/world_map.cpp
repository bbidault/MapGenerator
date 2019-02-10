#include "world_map.h"
#include "common.h"


void world_map::display_map( )
{
    cv::Mat topographic_map( height, width, CV_8UC3 );

    cv::Mat Q2_Q4_temp_map( height, width, CV_8UC3 );

    cv::Mat Q1_temp_map( height, width, CV_8UC3 );

    cv::Mat Q3_temp_map( height, width, CV_8UC3 );

    cv::Mat rainfall_map( height, width, CV_8UC3 );

    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            topographic_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].topography_color;

            Q2_Q4_temp_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].Q2_Q4_temp_color;

            Q1_temp_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].Q1_temp_color;

            Q3_temp_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].Q3_temp_color;

            rainfall_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].rainfall_color;
        }
    }

    imshow("Topographic map", topographic_map);

    imshow("Q2 and Q4 temperature map", Q2_Q4_temp_map);

    imshow("Q1 temperature map", Q1_temp_map);

    imshow("Q3 temperature map", Q3_temp_map);

    imshow("Rainfall map", rainfall_map);
}

void world_map::find_max()
{
    double max_altitude = 0;
    double min_temp = 1000;
    double max_temp = -1000;
    double max_rainfall = 0;

    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            if( world[i][j].altitude > max_altitude )
            {
                max_altitude = world[i][j].altitude;
            }
            if( world[i][j].Q2_Q4_temp > max_temp )
            {
                max_temp = world[i][j].Q2_Q4_temp;
            }
            if( world[i][j].Q2_Q4_temp < min_temp )
            {
                min_temp = world[i][j].Q2_Q4_temp;
            }
            if( world[i][j].rainfall > max_rainfall )
            {
                max_rainfall = world[i][j].rainfall;
            }
        }
    }

    std::cout << "max altitude : " << max_altitude << std::endl;
    std::cout << "max temperature : " << max_temp << std::endl;
    std::cout << "min temperature : " << min_temp << std::endl;
    std::cout << "max rainfall : " << max_rainfall << std::endl;
}
