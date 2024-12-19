#pragma once

#include "thread_safe_queue.h"
#include <memory>

class transport;
class response_factory;

constexpr int MAX_TRANSPORT_QUEUE_SIZE = 10;

class application {
public:
  application(std::unique_ptr<transport> in_transport);
  ~application();

  void run();

private:
  std::unique_ptr<transport> lsp_transport{};
  std::unique_ptr<response_factory> lsp_response_factory{};
  thread_safe_queue<std::string> message_queue{MAX_TRANSPORT_QUEUE_SIZE};

  void receive_messages();
  void process_messages();
};
