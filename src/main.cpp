#include "world_map.h"

int main( int argc, char * *argv )
{
    WorldMap world;

    std::cout << "generating topography" << std::endl;
    world.createTopography();

    // freshwater functions
    std::cout << "generating bodies of fresh water" << std::endl;
    world.createPrecipitation();
    world.createSources();
    world.clearPrecipitation();
    std::cout << "generating precipitation" << std::endl;
    world.createPrecipitation();

    std::cout << "generating temperatures" << std::endl;
    world.createTemp();

    std::cout << "generating biomes" << std::endl;
    world.setBiome();

    // color the maps
    world.colorTopography();
    world.colorTemp();
    world.colorPrecipitation();
    world.colorBiome( true );

    for ( int i = 0; i < 3; i++ )
    {
        world.averageBiomeColor();
    }

    world.displayMap();

    world.findMax();

    cv::waitKey( 0 );

    return 0;
}
