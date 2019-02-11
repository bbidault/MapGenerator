#include "world_map.h"

int main(int argc, char** argv )
{
    world_map world;

    std::cout << "generating topography" << std::endl;
    world.create_topography();

    /// freshwater functions
    std::cout << "generating bodies of fresh water" << std::endl;
    world.create_precipitation();
    world.create_sources();
    world.clear_precipitation();
    std::cout << "generating precipitation" << std::endl;
    world.create_precipitation();

    std::cout << "generating temperatures" << std::endl;
    world.create_temp();

    /// color the maps
    world.color_topography();
    world.color_temp();
    world.color_precipitation();

    world.display_map();

    world.find_max();

    cv::waitKey(0);

    return 0;
}
