#pragma one

#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <include/list/list.h>
extern std::string glob;

struct Leaflet {
  std::string name;
  int age;
};

struct Branch {
  std::vector<Leaflet> leaves;
  std::shared_ptr<std::mutex> write_lock;
};

extern Branch branch;

extern Lineardb::List list;