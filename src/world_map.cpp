#include "world_map.h"
#include "common.h"

/**
 * @brief display topographic, temperature and precipitation maps
 */
void WorldMap::displayMap()
{
    cv::Mat topographicMap( height, width, CV_8UC3 );

    cv::Mat q2Q4TempMap( height, width, CV_8UC3 );

    cv::Mat q1TempMap( height, width, CV_8UC3 );

    cv::Mat q3TempMap( height, width, CV_8UC3 );

    cv::Mat precipitationMap( height, width, CV_8UC3 );

    cv::Mat biomeMap( height, width, CV_8UC3 );

    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            topographicMap.at<cv::Vec3b>( cv::Point( i, j ) ) = world[i][j].topographyColor;

            q2Q4TempMap.at<cv::Vec3b>( cv::Point( i, j ) ) = world[i][j].q2Q4TempColor;

            q1TempMap.at<cv::Vec3b>( cv::Point( i, j ) ) = world[i][j].q1TempColor;

            q3TempMap.at<cv::Vec3b>( cv::Point( i, j ) ) = world[i][j].q3TempColor;

            precipitationMap.at<cv::Vec3b>( cv::Point( i, j ) ) = world[i][j].precipitationColor;

            biomeMap.at<cv::Vec3b>( cv::Point( i, j ) ) = world[i][j].biomeColor;
        }
    }

    imshow( "Topographic map", topographicMap );

    //    imshow("Q2 and Q4 temperature map", q2Q4TempMap);
    //
    //    imshow("Q1 temperature map", q1TempMap);
    //
    //    imshow("Q3 temperature map", q3TempMap);
    //
    //    imshow("Precipitation map", precipitationMap);

    imshow( "Biomes map", biomeMap );
}

/**
 * @brief display max max altitude, max and min temperature and max precipitation
 */
void WorldMap::findMax()
{
    double maxAltitude      = 0;
    double minTemp          = 1000;
    double maxTemp          = -1000;
    double maxPrecipitation = 0;

    for ( int i = 0; i < width; i++ )
    {
        for ( int j = 0; j < height; j++ )
        {
            if ( world[i][j].altitude > maxAltitude )
            {
                maxAltitude = world[i][j].altitude;
            }
            if ( world[i][j].q2Q4Temp > maxTemp )
            {
                maxTemp = world[i][j].q2Q4Temp;
            }
            if ( world[i][j].q2Q4Temp < minTemp )
            {
                minTemp = world[i][j].q2Q4Temp;
            }
            if ( world[i][j].precipitation > maxPrecipitation )
            {
                maxPrecipitation = world[i][j].precipitation;
            }
        }
    }

    std::cout << "max altitude : " << maxAltitude << std::endl;
    std::cout << "max temperature : " << maxTemp << std::endl;
    std::cout << "min temperature : " << minTemp << std::endl;
    std::cout << "max precipitation : " << maxPrecipitation << std::endl;
}
