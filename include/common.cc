#include "common.h"

Branch branch = {{}, std::make_shared<std::mutex>()};
std::string glob = "Hello, Drogon!";
List list = List();