// https://leetcode.com/problems/longest-palindromic-substring/

#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <string_view>

class Solution0005 {
public:
    std::pair<int, std::string> longestPalindrome(std::string_view sv)
    {
        auto IsPalindrome = [](std::string_view sv) { return std::equal(std::cbegin(sv), std::next(std::cbegin(sv), sv.size() / 2), std::crbegin(sv)); };

        int pos = 0;
        int count = sv.size() != 0;

        for (int index = 0; index < sv.size(); ++index) {
            // Search "aba"-like string
            int distance = std::min(index, static_cast<int>(sv.size()) - index - 1);
            for (auto arm = (count - 1) / 2 + 1; arm <= distance; ++arm) {
                if (!IsPalindrome(sv.substr(index - arm, 2 * arm + 1)))
                    break;

                pos = index - arm;
                count = 2 * arm + 1;
            }

            // Search "abba"-like string
            distance = std::max(0, std::min(index, static_cast<int>(sv.size()) - index - 2));
            for (auto arm = count / 2; arm <= distance && index + 2 <= sv.size(); ++arm) {
                if (!IsPalindrome(sv.substr(index - arm, 2 * arm + 2)))
                    break;

                pos = index - arm;
                count = 2 * arm + 2;
            }
        }

        return std::make_pair(count, static_cast<std::string>(sv.substr(pos, count)));
    }
};

void TC0005(std::string str)
{
    std::cout << "[INPUT]  " << str << '\t';

    auto start = std::chrono::high_resolution_clock::now();
    auto res = Solution0005().longestPalindrome(str);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "[OUTPUT] " << res.first << ' ' << res.second << '\t';
    std::cout << "[TIME] " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << std::endl;
}

void Run0005()
{
    std::cout << "Run TCs of Problem 0005" << std::endl;

    TC0005("babad");
    TC0005("cbbd");
    TC0005("");
    TC0005("a");
    TC0005("aa");
    TC0005("ab");
    TC0005("aaa");
    TC0005("aab");
    TC0005("aba");
    TC0005("baa");
    TC0005("abc");
    TC0005("aaaa");
    TC0005("aaab");
    TC0005("aaba");
    TC0005("abaa");
    TC0005("baaa");
    TC0005("aabb");
    TC0005("abab");
    TC0005("abba");
    TC0005("baab");
    TC0005("aaaaaabaaa");
    TC0005("aaabaaaaaa");
    TC0005("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    std::cout << std::endl;
}