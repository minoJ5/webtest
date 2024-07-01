#include "Lister.h"

#include "../include/common.h"
unsigned long int number = 1000000;
void Lister::add_list(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) const {
  for (int i = 0; i < number; i++) {
    Leaf *p = new Leaf("mino", i);
    // std::cout << p << "\n";
    bool ok = list.insert(p);
    if (!ok) {
      delete p;
    };
  }
  // Leaf* p = new Leaf("mino", 29);
  // list.insert(p);
  // Leaf *p2 = new Leaf("mino", 28);
  // list.insert(p2);
  Json::Value ret;
  ret["message"] = "Hello, World!";
  auto resp = HttpResponse::newHttpJsonResponse(ret);
  callback(resp);
};
void Lister::clear_list(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) const {
  for (int i = 0; i < number; i++) {
    list.delete_node_map(i);
  }
  auto resp = HttpResponse::newHttpResponse();
  callback(resp);
}
void Lister::print_list(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) const {
  std::cout << "out!\n";
  // std::cout << list.head << "\n";
  // std::cout << list.finder->get(0) << "\n";
  list.print_list();
  auto resp = HttpResponse::newHttpResponse();
  callback(resp);
}