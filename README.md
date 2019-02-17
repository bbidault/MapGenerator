# MapGenerator

MapGenerator is an earth-like planet generator/simulator. It auto-generates a planet by following a set of physical rules that apply to the earth. The application generates and displays a topographic map, a precipitation map, a set of temperature maps and a biomes map.

## Dependencies

MapGenerator depends on the OpenCV library. You can find installation instructions for Linux [here](https://docs.opencv.org/3.4/d7/d9f/tutorial_linux_install.html).

## Building

To build the project, clone the repository and run `cmake` and `make`.

```
git clone https://github.com/bbidault/MapGenerator.git
cd MapGenerator
mkdir build
cd build
cmake ..
make
```

To run the project, use the resulting executable.

```
./MapGenerator
```