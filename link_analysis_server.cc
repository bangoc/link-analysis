#include "glog/logging.h"
#include "server_http.hpp"

#include <memory>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

void GraphPostHandler(
      std::shared_ptr<HttpServer::Response> response,
      std::shared_ptr<HttpServer::Request> request) {
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);

  HttpServer server;
  server.config.port = 8080;
  server.config.thread_pool_size = 8;
  server.resource["^/graph$"]["POST"] = GraphPostHandler;
  std::thread server_thread([&server]() {
    // Start server
    server.start();
  });
  server_thread.join();
}