#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

namespace Config {

    const std::string dataDir = "/Users/Tiannan/GitHub/4611/CSCI4611_Project_03/EarthquakeVisualization/data";

    const std::string textureFile = dataDir + "/earth-256s.bmp";

    const std::string quakeFile = dataDir + "/earthquakes.txt";

    const float timeWindow = 365*24*3600;

}

#endif
