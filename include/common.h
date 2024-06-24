#ifndef COMMON_H
#define COMMON_H

#include <memory>
#include <mutex>
#include <string>
#include <vector>

extern std::string glob;

struct Leaf
{
    std::string name;
    int age;
};

struct Branch
{
    std::vector<Leaf> leaves;
    std::unique_ptr<std::mutex> write_lock;
};

extern Branch branch;

#endif