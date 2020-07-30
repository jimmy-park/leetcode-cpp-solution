#include <future>
#include <iostream>

#include "1114-Print-in-Order.h"

void Run1114(std::vector<int> order)
{
    PrintInOrder pio;
    auto first = [&pio] { return pio.first([] { std::cout << "first"; }); };
    auto second = [&pio] { return pio.second([] { std::cout << "second"; }); };
    auto third = [&pio] { return pio.third([] { std::cout << "third"; }); };

    std::vector<std::future<void>> tasks;

    for (auto i : order) {
        if (i == 1)
            tasks.emplace_back(std::async(std::launch::async, first));
        else if (i == 2)
            tasks.emplace_back(std::async(std::launch::async, second));
        else if (i == 3)
            tasks.emplace_back(std::async(std::launch::async, third));
    }

    for (auto& task : tasks)
        task.get();

    std::cout << std::endl;
}

int main()
{
    Run1114({ 1, 2, 3 });
    Run1114({ 1, 3, 2 });
    Run1114({ 2, 1, 3 });
    Run1114({ 2, 3, 1 });
    Run1114({ 3, 1, 2 });
    Run1114({ 3, 2, 1 });

    return 0;
}
