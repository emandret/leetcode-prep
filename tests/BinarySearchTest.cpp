#include <catch2/catch_test_macros.hpp>

#include "BinarySearch.hpp"

TEST_CASE("Binary Search")
{
    vector<int> nums{-1, 0, 3, 5, 9, 12};
    BinarySearch s;
    SECTION("Sample test")
    {
        int target = 9;
        int ans = 4;
        REQUIRE(s.search(nums, target) == ans);
    }
    SECTION("Missing target")
    {
        int target = 2;
        int ans = -1;
        REQUIRE(s.search(nums, target) == ans);
    }
}
