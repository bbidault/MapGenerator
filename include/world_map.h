#include "pixel.h"

/// the height of the map
#define HEIGHT 600

/// the width of the map
#define WIDTH 1200

/// the axial tilt of the planet
#define AXIAL_TILT 23.4


/// world_map class definition : array of pixels
class world_map
{
    private:
        int height;
        int width;
        pixel **world;

    public:
        /// constructor
        world_map()
        {
            height = HEIGHT;
            width = WIDTH;
            world = new pixel*[width];

            for( int i = 0 ; i < width ; i++ )
            {
                world[i] = new pixel[height];
            }
        }

        /// destructor
        ~world_map()
        {
            delete [] world;
        }


        /** Topographic map functions **/

        /// main topography function
        void create_topography();

        /** generates random high points on the map
         * 
         * @param probability of altitude > 0
         */
        void randomize_altitude( int prob );

        /// dilate points of altitude > 0
        void dilation();

        /// erode points of altitude > 0
        void erosion();

        /// average altitude across the map
        void average_altitude();

        /** create random altutude irregularities
         * 
         * @param probability of irregularity
         * @param size of irregularity
         */
        void create_irregularities( int prob, int size );

        /// color topographic map
        void color_topography();


        /** Fresh water functions **/

        /// initializes seas, lakes and lands status
        void set_seas_lakes_lands();

        /** set sea status
         * 
         * @param latitute of next pixel
         * @param longitude of next pixel
         */
        void visit_sea( int i, int j, int k );

        /// set lake and land status
        void set_lakes_lands();

        /// generate sources in locations of high precipitation
        void create_sources();

        /** generate a river from source
         * 
         * @param latitude of the source
         * @param longitude of the source
         */
        void generate_river( int i, int j );

        /** update rivers and lakes connection status
         * 
         * @param latitude of the source
         * @param longitude of the source
         */
        void set_connection( int i, int j );

        /** generate a lake from a river
         * 
         * @param latitude of the source
         * @param longitude of the source
         */
        void generate_lake( int i, int j );

        /** create a vector listing all the pixels of a lake
         * 
         * @param latitude of the lake
         * @param longitude of the lake 
         * @param total lake
         */
        void visit_lake( int i, int j, std::vector <pixel_coordinates> &lake );


        /** Temperature map functions **/

        /// generate temperature map from longitude and altitude
        void create_temp();

        /// average temperature across the map
        void average_temperature();

        /// color temperature map
        void color_temp();


        /** precipitation map functions **/

        /// clear precipitation values
        void clear_precipitation();

        /// generate precipitation map from water mass locations and air currents
        void create_precipitation();

        /// average precipitation across the map
        void average_precipitation();

        /// color precipitation map
        void color_precipitation();


        /** biome map functions **/

        /// evaluate pixel biome from temperature and precipitation
        void set_biome();

        /// color biome map
        void color_biome();


        /** other functions **/

        /// display topographic, temperature and precipitation maps
        void display_map();

        /// display max max altitude, max and min temperature and max precipitation
        void find_max();
};
