#include "application.h"
#include "protocol/request/request_parser.h"
#include "protocol/response/response.h"
#include "protocol/response/response_factory.h"
#include "transport/transport.h"
#include <format>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#if _WIN32
#include <fcntl.h>
#include <io.h>
#endif

namespace application_helper {
void init_logger() {
  auto new_logger = spdlog::basic_logger_mt("new_default_logger",
                                            "logs/new-default-log.txt", true);
  spdlog::set_default_logger(new_logger);
  spdlog::info("new logger log message");
  spdlog::flush_every(std::chrono::seconds(1));
}
} // namespace application_helper

application::application(std::unique_ptr<transport> in_transport)
    : lsp_transport{std::move(in_transport)},
      lsp_response_factory{std::make_unique<response_factory>()} {
  using namespace application_helper;
  init_logger();

#if _WIN32
  _setmode(_fileno(stdout), _O_BINARY);
#endif
}

application::~application() {}

void application::run() {
  spdlog::info("start lsp server");

  std::thread process_thread(&application::process_messages, this);
  std::thread receive_thread(&application::receive_messages, this);

  process_thread.join();
  receive_thread.join();
}

void application::process_messages() {
  while (true) {
    std::string new_message = message_queue.dequeue();

    const request req = request_parser::parse(new_message);
    spdlog::info("process request: {}", to_string(req.method));

    const response_message resp = lsp_response_factory->create(req);
    const std::string &response_str = resp.to_string();

    spdlog::info("write response: {}", response_str);

    lsp_transport->send(response_str);
  }
}

void application::receive_messages() {
  while (true) {
    message_queue.enqueue(lsp_transport->receive());
  }
}
