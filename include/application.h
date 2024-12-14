#pragma once

#include "thread_safe_queue.h"
#include <memory>

class transport;

constexpr int MAX_TRANSPORT_QUEUE_SIZE = 10;

class application {
public:
  application(std::unique_ptr<transport> in_transport);

  void run();

private:
  std::unique_ptr<transport> lsp_transport{};
  thread_safe_queue<std::string> message_queue{MAX_TRANSPORT_QUEUE_SIZE};

  void receive_messages();
  void process_messages();
};
