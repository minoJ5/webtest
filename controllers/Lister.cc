#include "Lister.h"

#include "../include/common.h"
unsigned long int number = 1'000'000;
void Lister::add_list(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) const {

  for (int i = 0; i < number; i++) {
    Leaf p("mino", i);
    list.insert(p);
  }
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
  list.print_list();
  auto resp = HttpResponse::newHttpResponse();
  callback(resp);
}