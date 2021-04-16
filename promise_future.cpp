#include <thread>
#include <iostream>
#include <future>
#include <cstdlib>
#include <ctime>
#include <vector>

int main()
{
    // Create a producer lambda
    auto producer = [](std::promise<std::string>&& prom) {
        std::srand(std::time(nullptr));
        std::string item = "My string " + std::to_string(std::rand());
        // Make sure to add sleep so that we can check if consumer blocks
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        prom.set_value(item);
    };

    // Create a consumer lambda
    auto consumer = [](std::future<std::string>&& fut) {
        std::cout << "[Tid : " << std::this_thread::get_id() << "] Consumer started" << std::endl;
        auto tmp = fut.get();
        std::cout << "[Tid : " << std::this_thread::get_id() << "] Consumer consumed a string :" << tmp.c_str() << std::endl;
    };

    std::vector<std::thread> myThreads;
    for(auto i =0; i<5; i++)
    {
        // Create a promise
        std::promise<std::string> myProm;

        // Associate future with the promise
        std::future<std::string> myFut(myProm.get_future());

        // Spawn threads
        myThreads.push_back(std::thread(producer, std::move(myProm)));
        myThreads.push_back(std::thread(consumer, std::move(myFut)));
    }

    // Wait for threads to exit
    for(std::thread& th : myThreads)
    {
        th.join();
    }
    return 0;
}