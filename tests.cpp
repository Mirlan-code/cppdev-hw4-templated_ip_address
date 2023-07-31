#include "print_ip_concepts.h"
#include "print_ip_without_concepts.h"
#include <gtest/gtest.h>

using namespace std;

TEST(TestsIpPrint, TestInt8) {
    stringstream s1, s2;
    WithoutConcepts::PrintIp(int8_t{-1}, s1);
    WithConcepts::PrintIp(int8_t{-1}, s2);
    string res = "255\n";
    ASSERT_EQ(s1.str(), res);
    ASSERT_EQ(s1.str(), s2.str());
}

TEST(TestsIpPrint, TestInt16) {
    stringstream s1, s2;
    WithoutConcepts::PrintIp(int16_t{0}, s1);
    WithConcepts::PrintIp(int16_t{0}, s2);
    string res = "0.0\n";
    ASSERT_EQ(s1.str(), res);
    ASSERT_EQ(s1.str(), s2.str());
}

TEST(TestsIpPrint, TestInt32) {
    stringstream s1, s2;
    WithoutConcepts::PrintIp(int32_t{2130706433}, s1);
    WithConcepts::PrintIp(int32_t{2130706433}, s2);
    string res = "127.0.0.1\n";
    ASSERT_EQ(s1.str(), res);
    ASSERT_EQ(s1.str(), s2.str());
}

TEST(TestsIpPrint, TestInt64) {
    stringstream s1, s2;
    WithoutConcepts::PrintIp(int64_t{8875824491850138409}, s1);
    WithConcepts::PrintIp(int64_t{8875824491850138409}, s2);
    string res = "123.45.67.89.101.112.131.41\n";
    ASSERT_EQ(s1.str(), res);
    ASSERT_EQ(s1.str(), s2.str());
}

TEST(TestsIpPrint, TestString) {
    stringstream s1, s2;
    WithoutConcepts::PrintIp(string("Hello, World!"), s1);
    WithConcepts::PrintIp(string("Hello, World!"), s2);
    string res = "Hello, World!\n";
    ASSERT_EQ(s1.str(), res);
    ASSERT_EQ(s1.str(), s2.str());
}

TEST(TestsIpPrint, TestVector) {
    stringstream s1, s2;
    WithoutConcepts::PrintIp(vector<int>{100, 200, 300, 400}, s1);
    WithConcepts::PrintIp(vector<int>{100, 200, 300, 400}, s2);
    string res = "100.200.300.400\n";
    ASSERT_EQ(s1.str(), res);
    ASSERT_EQ(s1.str(), s2.str());
}

TEST(TestsIpPrint, TestList) {
    stringstream s1, s2;
    WithoutConcepts::PrintIp(list<short>{400, 300, 200, 100}, s1);
    WithConcepts::PrintIp(list<short>{400, 300, 200, 100}, s2);
    string res = "400.300.200.100\n";
    ASSERT_EQ(s1.str(), res);
    ASSERT_EQ(s1.str(), s2.str());
}

TEST(TestsIpPrint, TestTuple) {
    stringstream s1, s2;
    WithoutConcepts::PrintIp(make_tuple(123, 456, 789, 0), s1);
    WithConcepts::PrintIp(make_tuple(123, 456, 789, 0), s2);
    string res = "123.456.789.0\n";
    ASSERT_EQ(s1.str(), res);
    ASSERT_EQ(s1.str(), s2.str());
}