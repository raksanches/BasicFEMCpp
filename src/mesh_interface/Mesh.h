#pragma once

#include <fstream>
#include <stdio.h>
#include "Geometry.h"

#ifdef _WIN32
#include <direct.h>
#define getCurrentDir _getcwd
#define remove "del "
#else
#include <unistd.h>
#define getCurrentDir getcwd
#define remove "rm "
#endif

std::string getCurrentWorkingDir();

std::pair<std::string, bool> createMesh(Geometry* geometry, const std::string& elementType = "T3", const std::string& algorithm = "AUTO", std::string geofile = std::string(), const std::string& gmshPath = std::string(), const bool& plotMesh = true, const bool& showInfo = false);