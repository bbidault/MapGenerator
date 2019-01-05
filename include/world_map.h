#include "pixel.h"

struct pixel_coordinates
{
    int row;
    int col;
};

class world_map
{
    private:
        int height;
        int width;
        pixel **world;

    public:
        world_map()
        {
            height = 600;
            width = 1200;
            world = new pixel*[width];

            for( int i = 0 ; i < width ; i++ )
            {
                world[i] = new pixel[height];
            }
        }

        ~world_map()
        {
            delete [] world;
        }


        /** Topographic map functions **/
        
        ///
        void create_topography();

        ///
        void randomize_altitude( int prob );

        ///
        void dilation();

        ///
        void erosion();

        ///
        void average_altitude();

        ///
        void create_irregularities( int prob, int size );

        ///
        void randomize_sources();

        ///
        void color_topography();


        /** Heat map functions **/

        ///
        void create_heat();

        ///
        void average_temperature();

        ///
        void color_heat();


        /** Rainfall map functions **/

        ///
        void create_rainfall();

        ///
        void average_rainfall();

        ///
        void color_rainfall();


        /** other functions **/

        ///
        void display_map();

        ///
        void find_max();
};