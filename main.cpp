#include "lib.h"

#include <iostream>
#include <vector>
#include <concepts>
#include <cstddef>
#include <list>
#include <tuple>

using namespace std;


//template<typename T, typename = typename enable_if<is_integral<T>::value, T>::type>
/// For integers
/// For integers
template<typename T>
inline typename enable_if<is_integral<T>::value, void>::type
PrintIp(const T& ip) {
    T ipCopy = ip;
    uint8_t* res = reinterpret_cast<uint8_t*>(&ipCopy);
    for (int i = sizeof(ip) - 1; i >= 0; i--) {
        cout << (unsigned int)res[i] << (i == 0 ? '\n' : '.');
    }
}

//template<typename T>
//concept IsString = is_same<T, string>::value;

/// For strings
/// For strings
template<typename T>
inline typename enable_if<is_same<T, string>::value, void>::type
PrintIp(const T& ip) {
    cout << ip << endl;
}

template<typename T>
struct is_tuple : std::false_type {};
template<typename... Ts>
struct is_tuple<std::tuple<Ts...>> : std::true_type {};

template <typename T, typename Tuple>
struct is_tuple_with_identic_types;
template <typename T, typename... Ts>
struct is_tuple_with_identic_types<T, tuple<Ts...>> : std::conjunction<std::is_same<T, Ts>...>{};

/// For tuple
/// For tuple
template<typename T>
inline typename enable_if<is_tuple_with_identic_types<typename tuple_element<0, T>::type, T>::value, void>::type
PrintIp(const T& ip) {
    vector<int> res;
    apply([&res](auto&&... args) {((res.push_back(args)), ...);}, ip);
    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i] << (i == res.size() - 1 ? '\n' : '.');
    }
}

/// For others
/// For others
template<typename T>
inline typename enable_if<!is_same<T, string>::value && !is_integral<T>::value && !is_tuple<T>::value, void>::type
PrintIp(const T& ip) {
    for (auto i = ip.begin(); i != ip.end(); i++) {
        if (i != ip.begin()) {
            cout << '.';
        }
        cout << *i;
    }
    cout << endl;
}


int main (int, char **) {
    PrintIp(int8_t{-1});
    PrintIp(int16_t{0});
    PrintIp(int32_t{2130706433});
    PrintIp(int64_t{8875824491850138409});
    PrintIp(string("Hello, World!"));
    PrintIp(vector<int>{100, 200, 300, 400});
    PrintIp(list<short>{400, 300, 200, 100});
    PrintIp(make_tuple(123, 456, 789, 0));
    return 0;
}
