#include "work.h"

#include <chrono>
#include <format>
#include <future>
#include <iostream>
#include <syncstream>
#include <thread>

namespace {

constexpr int SLOW_SECONDS = 7;
constexpr int QUICK_SECONDS = 1;

void run_step(const std::string& name, int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    std::osyncstream(std::cout) << name << '\n';
}

}  // namespace

void slow(const std::string& name) {
    run_step(name, SLOW_SECONDS);
}

void quick(const std::string& name) {
    run_step(name, QUICK_SECONDS);
}

void work() {
    const auto start = std::chrono::steady_clock::now();

    std::promise<void> c2_done_promise;
    std::future<void> c2_done = c2_done_promise.get_future();

    // Launch one additional thread for the independent branch: C2 (7s) -> D2 (1s).
    std::future<void> d2_done = std::async(std::launch::async, [promise = std::move(c2_done_promise)]() mutable {
        slow("C2");
        promise.set_value();
        quick("D2");
    });

    // Main thread executes the critical path: A (1s) -> B (7s) -> C1 (1s) -> D1 (1s) -> F (1s).
    quick("A");
    slow("B");
    quick("C1");

    // D1 depends on C1 (already finished in main) and C2 (from the worker thread).
    c2_done.wait();
    quick("D1");

    // F depends on D1 (already finished in main) and D2 (from the worker thread).
    d2_done.wait();
    quick("F");

    const std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
    std::osyncstream(std::cout) << std::format("Execution time: {:.2f} seconds.\nWork is done!\n", elapsed.count());
}