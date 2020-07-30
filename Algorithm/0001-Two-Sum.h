// https://leetcode.com/problems/two-sum/

#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

class Solution0001 {
public:
    // Since C++20, use std::span<T> when passing containers
    // std::vector<int> twoSum(std::span<int> nums, int target) {
    std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        // Currently, clang does not support polymorphic memory resource library which is in C++17
        // std::array<std::byte, 2048> stack_buffer;
        // std::pmr::monotonic_buffer_resource pool { std::data(stack_buffer), std::size(stack_buffer) };
        // std::pmr::unordered_map<int, int> hash_map { &pool };

        std::unordered_map<int, int> hash_map;

        // Since C++20, we can initialize in range-based for loop
        for (int index = 0; auto num : nums) {
            // Since C++20, use contains() instead of find() for searching key
            // But contains() is not yet implemented in clang
            // if (hash_map.contains(target - num))
            //     return { hash_map.at(target - num), index };

            // For now, use init-statement in if statement (C++17)
            if (auto search = hash_map.find(target - num); search != hash_map.end())
                return { search->second, index };

            // Since C++17, we can use try_emplace instead of emplace
            // If a key already exists in the container, does nothing
            hash_map.try_emplace(num, index++);
        }

        return {};
    }
};

void TC0001(std::vector<int> input, int target)
{
    std::cout << "[INPUT]  ";
    for (auto i : input)
        std::cout << i << ',';
    std::cout << " target: " << target << std::endl;

    auto ret = Solution0001().twoSum(input, target);

    std::cout << "[OUTPUT] " << ret[0] << ',' << ret[1] << std::endl;
}

void Run0001()
{
    std::cout << "Run TCs of Problem 0001" << std::endl;

    TC0001({ 2, 7, 11, 15 }, 9);

    std::cout << std::endl;
}