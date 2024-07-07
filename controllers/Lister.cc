#include "Lister.h"

#include "../include/common.h"
#include "../include/rapidjson/document.h"

namespace ldb = Lineardb;

unsigned long int number = 100;
void Lister::add_list(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) const {
  auto b = req->getBody();
  rapidjson::Document d;
  d.Parse(std::string(b).c_str());
  std::cout << d["ping"].GetString() << "\n";
  for (int i = 0; i < number; i++) {
    ldb::Leaf *p = new ldb::Leaf("mino", i);
    bool ok = list.insert(p);
    if (!ok) {
      delete p;
    };
  }
  std::vector<int> v = {1, 2, 3};
  Json::Value ret;
  ret["message"] = d["ping"].GetString();
  ret["errors"] = "none";

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