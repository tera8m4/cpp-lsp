#include <doctest/doctest.h>
#include <thread_safe_queue.h>

TEST_CASE("thread_safe_queue basic operations") {
    thread_safe_queue<int> queue(3);

    SUBCASE("Enqueue and dequeue single item") {
        queue.enqueue(42);
        CHECK(queue.size() == 1);
        int value = queue.dequeue();
        CHECK(value == 42);
        CHECK(queue.is_empty());
    }

    SUBCASE("Multiple enqueue and dequeue operations") {
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);
        CHECK(queue.size() == 3);

        int value1 = queue.dequeue();
        int value2 = queue.dequeue();
        int value3 = queue.dequeue();

        CHECK(value1 == 1);
        CHECK(value2 == 2);
        CHECK(value3 == 3);
        CHECK(queue.is_empty());
    }

    SUBCASE("Blocking behavior when queue is full") {
        std::thread producer([&]() {
            queue.enqueue(10);
            queue.enqueue(20);
            queue.enqueue(30);
            // The following enqueue will block until a dequeue occurs
            queue.enqueue(40);
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        CHECK(queue.size() == 3);

        std::thread consumer([&]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            int value = queue.dequeue();
            CHECK(value == 10);
        });

        producer.join();
        consumer.join();
        CHECK(queue.size() == 3); // After consumer, 3 items remain
    }
}

