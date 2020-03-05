#include "pixel.h"

#ifndef WORLDMAP_H
#define WORLDMAP_H

// the height of the map
#define HEIGHT 600

// the width of the map
#define WIDTH 1200

// the axial tilt of the planet
#define AXIAL_TILT 23.4

// WorldMap class definition : array of pixels
class WorldMap
{
    private:
        int height;
        int width;
        Pixel * *world;

    public:
        // constructor
        WorldMap()
        {
            height = HEIGHT;
            width  = WIDTH;
            world  = new Pixel *[width];

            for ( int i = 0; i < width; i++ )
            {
                world[i] = new Pixel[height];
            }
        }

        // destructor
        ~WorldMap()
        {
            for ( int i = 0; i < width; i++ )
            {
                delete[] world[i];
            }
            delete[] world;
        }

        // Topographic map functions
        void createTopography();
        void randomizeAltitude( int prob );
        void dilation();
        void erosion();
        void averageAltitude();
        void createIrregularities( int prob,
                                   int size );
        void colorTopography();

        // Fresh water functions
        void setSeasAndLands();
        void visitSea( int aRow,
                       int aCol,
                       int aVisitedPixels );
        void setLands();
        void createSources();
        void generateRiver( int   aRow,
                            int   aCol,
                            float aWaterLeft );
        void setConnection( int aRow,
                            int aCol );
        void generateLake( int   aRow,
                           int   aCol,
                           float aWaterLeft );
        void createVectorOfLakes( int                             aRow,
                                  int                             aCol,
                                  std::vector<PixelCoordinates_T> &aLake );
        void findRiverLowestEnd( int   aRow,
                                 int   aCol,
                                 float aWaterLeft );
        void createVectorOfRivers( int                             aRow,
                                   int                             aCol,
                                   std::vector<PixelCoordinates_T> &aDrainageSystem );

        // Temperature map functions
        void createTemp();
        void averageTemperature();
        void colorTemp();

        // precipitation map functions
        void clearPrecipitation();
        void createPrecipitation();
        void averagePrecipitation();
        void colorPrecipitation();

        // biome map functions
        void setBiome();
        void colorBiome( bool aRealist );
        void averageBiomeColor();

        void displayMap();
        void findMax();
};

#endif // WORLDMAP_H
