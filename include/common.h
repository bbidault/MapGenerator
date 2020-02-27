#include "ctime"
#include "opencv2/opencv.hpp"

#ifndef COMMON_H
#define COMMON_H

// square root of 2
#define SQRT_2 sqrt( 2 )

bool between( double aX,
              double aA,
              double aB );

namespace TopographyColors
{
    const cv::Vec3b Altitude0  = { 171, 120, 9 };
    const cv::Vec3b Altitude1  = { 216, 171, 113 };
    const cv::Vec3b Altitude2  = { 222, 178, 121 };
    const cv::Vec3b Altitude3  = { 227, 185, 132 };
    const cv::Vec3b Altitude4  = { 234, 193, 141 };
    const cv::Vec3b Altitude5  = { 240, 201, 150 };
    const cv::Vec3b Altitude6  = { 247, 210, 161 };
    const cv::Vec3b Altitude7  = { 251, 219, 172 };
    const cv::Vec3b Altitude8  = { 255, 227, 185 };
    const cv::Vec3b Altitude9  = { 255, 236, 198 };
    const cv::Vec3b Altitude10 = { 254, 242, 216 };
    const cv::Vec3b Altitude11 = { 165, 208, 172 };
    const cv::Vec3b Altitude12 = { 139, 191, 148 };
    const cv::Vec3b Altitude13 = { 143, 198, 168 };
    const cv::Vec3b Altitude14 = { 150, 204, 189 };
    const cv::Vec3b Altitude15 = { 171, 215, 209 };
    const cv::Vec3b Altitude16 = { 181, 228, 225 };
    const cv::Vec3b Altitude17 = { 192, 235, 239 };
    const cv::Vec3b Altitude18 = { 163, 214, 222 };
    const cv::Vec3b Altitude19 = { 157, 202, 211 };
    const cv::Vec3b Altitude20 = { 130, 185, 202 };
    const cv::Vec3b Altitude21 = { 107, 167, 195 };
    const cv::Vec3b Altitude22 = { 90, 152, 185 };
    const cv::Vec3b Altitude23 = { 83, 135, 170 };
    const cv::Vec3b Altitude24 = { 124, 154, 172 };
    const cv::Vec3b Altitude25 = { 154, 174, 186 };
    const cv::Vec3b Altitude26 = { 184, 195, 202 };
    const cv::Vec3b Altitude27 = { 216, 222, 224 };
    const cv::Vec3b Altitude28 = { 242, 244, 245 };
}

namespace TempColors
{
    //const cv::Vec3b
}

namespace PrecipitationColors
{
    //const cv::Vec3b
}

namespace biomeColors
{
    //const cv::Vec3i
}

#endif // COMMON_H
