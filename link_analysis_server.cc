#include "base.h"
#include "format_helper.h"
#include "hits.h"
#include "input_helper.h"
#include "pagerank.h"
#include "glog/logging.h"
#include "server_http.hpp"

#include <memory>
#include <sstream>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

namespace {

void ResponseOk(std::shared_ptr<HttpServer::Response> response,
                json& j) {
  std::string content = j.dump();
  *response << "HTTP/1.1 200 OK\r\n"
            << "Content-Type: application/json\r\n"
            << "Content-Length: " << content.length() << "\r\n\r\n"
            << content;
}

}  // namespace

void PageRankPostHandler(
      std::shared_ptr<HttpServer::Response> response,
      std::shared_ptr<HttpServer::Request> request) {
  std::string content = request->content.string();
  LOG(INFO) << "Request contents: \n"
            << content;
  std::stringstream ss{content};
  PageRankInput params;
  ParsePageRankParams(params, ss);

  LOG(INFO) << "\nParams: \n" << params;
  json debug;
  std::vector<std::pair<int, double>> out;
  PageRank(params, out, debug, true);
  LOG(INFO) << "\nDebug\n" << debug.dump(2);
  ResponseOk(response, debug);
}

void HitsPostHandler(
      std::shared_ptr<HttpServer::Response> response,
      std::shared_ptr<HttpServer::Request> request) {
  std::string content = request->content.string();
  LOG(INFO) << "Request contents: \n"
            << content;
  std::stringstream ss{content};

  HitsInput params;
  std::vector<std::pair<int, double>> hubs;
  std::vector<std::pair<int, double>> auth;
  ParseHitsParams(params, ss);
  json debug;
  Hits(params, hubs, auth, debug, true);
  LOG(INFO) << "\nDebug:\n" << debug.dump(2);

  ResponseOk(response, debug);
}

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);

  if (argc != 3) {
    LOG(ERROR) << "./server 0.0.0.0 8080" << std::endl
               << "to start server (you can use other host port)" << std::endl;
    return 1;
  }

  HttpServer server;
  server.config.address = argv[1];
  int port = 8080;
  {
    std::stringstream ss{argv[2]};
    ss >> port;
  }
  server.config.port = port;
  server.config.thread_pool_size = 8;
  server.resource["^/pagerank$"]["POST"] = PageRankPostHandler;
  server.resource["^/hits$"]["POST"] = HitsPostHandler;
  std::thread server_thread([&server]() {
    // Start server
    server.start();
  });
  server_thread.join();
}