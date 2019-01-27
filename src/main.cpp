#include "world_map.h"

int main(int argc, char** argv )
{
    world_map world;

    world.create_topography();

    /// freshwater functions
    world.create_rainfall();
    world.create_sources();
    world.clear_rainfall();
    world.create_rainfall();

    world.create_heat();

    /// color the maps
    world.color_topography();
    world.color_heat();
    world.color_rainfall();

    world.display_map();

    world.find_max();

    cv::waitKey(0);

    return 0;
}
