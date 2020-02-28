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

namespace biomeColors
{
    const cv::Vec3i PolarDesert                  = { 255, 255, 255 };
    const cv::Vec3i PolarDesertRealist           = { 185, 185, 185 };
    const cv::Vec3i Sea                          = { 50, 10, 11 };
    const cv::Vec3i SeaRealist                   = { 216, 171, 113 };
    const cv::Vec3i Lake                         = { 50, 10, 11 };
    const cv::Vec3i LakeRealist                  = { 171, 120, 9 };
    const cv::Vec3i AlpineTundra                 = { 235, 240, 240 };
    const cv::Vec3i AlpineTundraRealist          = { 215, 182, 158 };
    const cv::Vec3i Tundra                       = { 140, 173, 189 };
    const cv::Vec3i TundraRealist                = { 195, 209, 150 };
    const cv::Vec3i DrySteppe                    = { 65, 99, 112 };
    const cv::Vec3i DrySteppeRealist             = { 61, 122, 146 };
    const cv::Vec3i TemperateSteppe              = { 29, 86, 71 };
    const cv::Vec3i TemperateSteppeRealist       = { 100, 234, 246 };
    const cv::Vec3i Taiga                        = { 11, 49, 37 };
    const cv::Vec3i TaigaRealist                 = { 89, 98, 0 };
    const cv::Vec3i Chapparals                   = { 89, 133, 157 };
    const cv::Vec3i ChapparalsRealist            = { 144, 107, 134 };
    const cv::Vec3i TemperateForest              = { 11, 74, 48 };
    const cv::Vec3i TemperateForestRealist       = { 82, 220, 155 };
    const cv::Vec3i MontaneForest                = { 10, 38, 22 };
    const cv::Vec3i MontaneForestRealist         = { 142, 141, 50 };
    const cv::Vec3i SubtropicalRainForest        = { 13, 84, 57 };
    const cv::Vec3i SubtropicalRainForestRealist = { 9, 115, 9 };
    const cv::Vec3i AridDesert                   = { 175, 229, 254 };
    const cv::Vec3i AridDesertRealist            = { 50, 77, 139 };
    const cv::Vec3i XericShrubland               = { 121, 168, 212 };
    const cv::Vec3i XericShrublandRealist        = { 72, 106, 178 };
    const cv::Vec3i SemiAridDesert               = { 141, 190, 246 };
    const cv::Vec3i SemiAridDesertRealist        = { 125, 177, 218 };
    const cv::Vec3i GrassSavanna                 = { 46, 117, 101 };
    const cv::Vec3i GrassSavannaRealist          = { 73, 195, 199 };
    const cv::Vec3i TreeSavanna                  = { 14, 88, 62 };
    const cv::Vec3i TreeSavannaRealist           = { 19, 158, 164 };
    const cv::Vec3i SubtropicalDryForest         = { 29, 76, 73 };
    const cv::Vec3i SubtropicalDryForestRealist  = { 43, 132, 107 };
    const cv::Vec3i MonsoonForest                = { 47, 119, 106 };
    const cv::Vec3i MonsoonForestRealist         = { 100, 139, 100 };
    const cv::Vec3i TropicalRainForest           = { 9, 58, 38 };
    const cv::Vec3i TropicalRainForestRealist    = { 0, 81, 0 };
}

#endif // COMMON_H
