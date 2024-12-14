#include "application.h"
#include "transport/transport.h"
#include <format>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

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
    : lsp_transport{std::move(in_transport)} {
  using namespace application_helper;
  init_logger();
}

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
    spdlog::info("recvied: {}", new_message);
  }
}

void application::receive_messages() {
  while (true) {
    message_queue.enqueue(lsp_transport->receive());
  }
}
