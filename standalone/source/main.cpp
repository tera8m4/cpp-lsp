#include <application.h>
#include <memory>
#include <transport/stdio_transport.h>

int main() {
  application app{std::make_unique<stdio_transport>()};
  app.run();
  return 0;
}
