#include <iostream>
#include <vector>
#include <concepts>
#include <cstddef>
#include <list>
#include <tuple>

namespace WithConcepts {

template<std::integral T>
void PrintIp(const T &ip, std::ostream& os = std::cout) {
    T ipCopy = ip;
    uint8_t *res = reinterpret_cast<uint8_t *>(&ipCopy);
    for (int i = sizeof(ip) - 1; i >= 0; i--) {
        os << (unsigned int) res[i] << (i == 0 ? '\n' : '.');
    }
}

template<typename T> requires std::is_same<T, std::string>::value
void PrintIp(const T &ip, std::ostream& os = std::cout) {
    os << ip << std::endl;
}

template<typename T>
concept Tuple =
requires (T a) {
    std::tuple_size<T>::value;
    std::get<0>(a);
};

template<typename T>
concept TupleWithIdenticalTypes =
requires (T a) {
    std::tuple_size<T>::value;
    std::get<0>(a);
    std::conjunction<std::is_same<typename std::tuple_element<0, T>::type, T>>::value;
};

template<TupleWithIdenticalTypes T>
void PrintIp(const T &ip, std::ostream& os = std::cout) {
    std::vector<int> res;
    apply([&res](auto &&... args) { ((res.push_back(args)), ...); }, ip);
    for (size_t i = 0; i < res.size(); i++) {
        os << res[i] << (i == res.size() - 1 ? '\n' : '.');
    }
}

template<typename T> requires (!std::is_same<T, std::string>::value) && (!std::is_integral<T>::value) && (!Tuple<T>)
void PrintIp(const T &ip, std::ostream& os = std::cout) {
    for (auto i = ip.begin(); i != ip.end(); i++) {
        if (i != ip.begin()) {
            os << '.';
        }
        os << *i;
    }
    os << std::endl;
}

} // namespace WithConcepts