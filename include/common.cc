#include "common.h"


Branch branch = {{}, std::make_unique<std::mutex>()};
std::string glob = "Hello, Drogon!";