#include "print_ip_without_concepts.h"

#include <vector>
#include <concepts>
#include <list>
#include <tuple>

using namespace std;

int main (int, char **) {
    WithoutConcepts::PrintIp(int8_t{-1});
    WithoutConcepts::PrintIp(int16_t{0});
    WithoutConcepts::PrintIp(int32_t{2130706433});
    WithoutConcepts::PrintIp(int64_t{8875824491850138409});
    WithoutConcepts::PrintIp(string("Hello, World!"));
    WithoutConcepts::PrintIp(vector<int>{100, 200, 300, 400});
    WithoutConcepts::PrintIp(list<short>{400, 300, 200, 100});
    WithoutConcepts::PrintIp(make_tuple(123, 456, 789, 0));
    return 0;
}
