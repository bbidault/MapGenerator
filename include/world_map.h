#include "pixel.h"

/// the height of the map
#define HEIGHT 600

/// the width of the map
#define WIDTH 1200

/// the axial tilt of the planet
#define AXIAL_TILT 23.4

/// WorldMap class definition : array of pixels
class WorldMap
{
    private:
        int height;
        int width;
        Pixel * *world;

    public:
        /// constructor
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

        /// destructor
        ~WorldMap()
        {
            for ( int i = 0; i < width; i++ )
            {
                delete[] world[i];
            }
            delete[] world;
        }

        /** Topographic map functions **/

        /// main topography function
        void createTopography();

        /** generates random high points on the map
         *
         * @param probability of altitude > 0
         */
        void randomizeAltitude( int prob );

        /// dilate points of altitude > 0
        void dilation();

        /// erode points of altitude > 0
        void erosion();

        /// average altitude across the map
        void averageAltitude();

        /** create random altutude irregularities
         *
         * @param probability of irregularity
         * @param size of irregularity
         */
        void createIrregularities( int prob,
                                   int size );

        /// color topographic map
        void colorTopography();

        /** Fresh water functions **/

        /// initializes seas, lakes and lands status
        void setSeasLakesLands();

        /** set sea status
         *
         * @param latitute of next pixel
         * @param longitude of next pixel
         */
        void visitSea( int i,
                       int j,
                       int k );

        /// set lake and land status
        void setLakesLands();

        /// generate sources in locations of high precipitation
        void createSources();

        /** generate a river from source
         *
         * @param latitude of the source
         * @param longitude of the source
         */
        void generateRiver( int i,
                            int j );

        /** update rivers and lakes connection status
         *
         * @param latitude of the source
         * @param longitude of the source
         */
        void setConnection( int i,
                            int j );

        /** generate a lake from a river
         *
         * @param latitude of the source
         * @param longitude of the source
         */
        void generateLake( int i,
                           int j );

        /** create a vector listing all the pixels of a lake
         *
         * @param latitude of the lake
         * @param longitude of the lake
         * @param total lake
         */
        void visitLake( int                             i,
                        int                             j,
                        std::vector<PixelCoordinates_T> &lake );

        /** Temperature map functions **/

        /// generate temperature map from longitude and altitude
        void createTemp();

        /// average temperature across the map
        void averageTemperature();

        /// color temperature map
        void colorTemp();

        /** precipitation map functions **/

        /// clear precipitation values
        void clearPrecipitation();

        /// generate precipitation map from water mass locations and air currents
        void createPrecipitation();

        /// average precipitation across the map
        void averagePrecipitation();

        /// color precipitation map
        void colorPrecipitation();

        /** biome map functions **/

        /// evaluate pixel biome from temperature and precipitation
        void setBiome();

        /// color biome map
        void colorBiome( bool aRealist );

        ///  average biome color map
        void averageBiomeColor();

        /** other functions **/

        /// display topographic, temperature and precipitation maps
        void displayMap();

        /// display max max altitude, max and min temperature and max precipitation
        void findMax();
};
