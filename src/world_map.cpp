#include "world_map.h"
#include "common.h"


void world_map::display_map( )
{
    cv::Mat topographic_map( height, width, CV_8UC3 );

    cv::Mat Q2_Q4_temp_map( height, width, CV_8UC3 );

    cv::Mat Q1_temp_map( height, width, CV_8UC3 );

    cv::Mat Q3_temp_map( height, width, CV_8UC3 );

    cv::Mat precipitation_map( height, width, CV_8UC3 );

    for( int i = 0 ; i < width ; i++ )
    {
        for( int j = 0 ; j < height ; j++ )
        {
            topographic_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].topography_color;

            Q2_Q4_temp_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].Q2_Q4_temp_color;

            Q1_temp_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].Q1_temp_color;

            Q3_temp_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].Q3_temp_color;

            precipitation_map.at<cv::Vec3b>(cv::Point(i,j)) = world[i][j].precipitation_color;
        }
    }

    imshow("Topographic map", topographic_map);

    imshow("Q2 and Q4 temperature map", Q2_Q4_temp_map);

    imshow("Q1 temperature map", Q1_temp_map);

    imshow("Q3 temperature map", Q3_temp_map);

    imshow("Precipitation map", precipitation_map);
}
