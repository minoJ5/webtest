#pragma once

#include <drogon/HttpController.h>
using namespace drogon;

class TestCtrl : public drogon::HttpController<TestCtrl>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(TestCtrl::add_leaf, "/setleaf", Get);
    METHOD_ADD(TestCtrl::clear_branch, "/clear", Delete);
    METHOD_LIST_END
    void add_leaf(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callbacki) const;
    void clear_branch(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const;
};
