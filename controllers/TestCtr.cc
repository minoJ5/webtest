#include "TestCtr.h"

#include "../include/common.h"

void TestCtrl::add_leaf(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const
{
    Leaf l = Leaf{"mino", 28};
    // from_json(njson::json::parse(b), p);
    {
        std::lock_guard<std::mutex> guard(*branch.write_lock);
        for (int i = 0; i < 10000000; i++){
        branch.leaves.push_back(l);
        }
    }
    // res.body = b;
    printf("%ld\n", branch.leaves.size());
    Json::Value ret;
    ret["message"] = "Hello, World!";
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
};
void TestCtrl::clear_branch(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const
{
    branch.leaves.clear();
    branch.leaves.shrink_to_fit();
    printf("%ld\n", branch.leaves.size());
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_HTML);
    resp->setBody("Hello World!");
    callback(resp);
};