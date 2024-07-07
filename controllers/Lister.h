#pragma once

#include <drogon/HttpController.h>
#include <string>
using namespace drogon;

class Lister : public drogon::HttpController<Lister> {
 public:
  METHOD_LIST_BEGIN
  METHOD_ADD(Lister::add_list, "/setlist", Post);
  METHOD_ADD(Lister::clear_list, "/clearlist", Delete);
  METHOD_ADD(Lister::print_list, "/printlist", Get);
  METHOD_LIST_END
  void add_list(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callbacki) const;
  void clear_list(
      const HttpRequestPtr &req,
      std::function<void(const HttpResponsePtr &)> &&callback) const;
  void print_list(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callbacki) const;
};
