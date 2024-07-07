#include "parser.h"

#include <cassert>
#include <cstdio>
#include <string>
#include <iostream>

void testing() {
  std::string s;
  s = R"({
    "hello" : "world",
    "t" : true,
    "f" : false,
    "n" : null,
    "i" : 123,
    "pi" : 3.1416,
    "a" : [ "1", "2", "3", "4"]
  })";
  rj::Document d;
  d.Parse(s.c_str());
  std::cout << d.HasMember("hello") << "\n";
  std::cout << d["hello"].IsString() << "\n";
  std::cout << d["hello"].GetString() << "\n";
  printf("hello = %s\n", d["hello"].GetString());
  const rj::Value& a = d["a"];
  assert(a.IsArray());
  for (rj::SizeType i = 0; i < a.Size(); i++)  // Uses SizeType instead of size_t
    printf("a[%d] = %s\n", i, a[i].GetString());
}