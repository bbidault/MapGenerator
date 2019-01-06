#include "world_map.h"

int main(int argc, char** argv )
{
    world_map world;

    world.create_topography();

    world.create_heat();

    world.create_rainfall();

    //world.randomize_sources();

    world.color_topography();
    
    world.color_heat();

    world.color_rainfall();

    world.display_map();

    world.find_max();

    cv::waitKey(0);

    return 0;
}
