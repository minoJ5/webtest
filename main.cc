#include <drogon/drogon.h>

#include <chrono>
#include <iomanip>
#include <thread>

#include "include/common.h"

void status() {
  while (true) {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    // Convert to local time
    auto local_time = std::localtime(&now_c);
    std::cout << "running! " << std::put_time(local_time, "%F %T") << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}
int main() {
  // trantor::EventLoop* loop = drogon::app().getLoop();
  // loop->queueInLoop([] {
  //   status();
  // });
  // std::thread t(status);
  drogon::app().setDocumentRoot("./static");
  auto error404 = drogon::HttpResponse::newFileResponse("static/Error404.html");
  error404->setExpiredTime(0);
  drogon::app().setCustom404Page(error404);
  // Set HTTP listener address and port
  drogon::app().setThreadNum(12);
  printf("starting!\n");
  drogon::app().addListener("0.0.0.0", 5555);
  // Load config file
  // drogon::app().loadConfigFile("../config.json");
  // drogon::app().loadConfigFile("../config.yaml");
  // Run HTTP framework,the method will block in the internal event loop
  drogon::app().run();
  // t.join();
  return 0;
}
