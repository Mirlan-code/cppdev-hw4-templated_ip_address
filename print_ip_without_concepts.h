#include <iostream>
#include <vector>
#include <cstddef>
#include <list>
#include <tuple>

namespace WithoutConcepts {

/**
 * prints ip
 * @tparam T integral type
 * @param ip ip_representation
 * @param os output stream
 */
template<typename T>
inline typename std::enable_if<std::is_integral<T>::value, void>::type
PrintIp(const T& ip, std::ostream& os = std::cout) {
    T ipCopy = ip;
    uint8_t* res = reinterpret_cast<uint8_t*>(&ipCopy);
    for (int i = sizeof(ip) - 1; i >= 0; i--) {
        os << (unsigned int)res[i] << (i == 0 ? '\n' : '.');
    }
}

/**
 * prints ip
 * @tparam T string type
 * @param ip ip_representation
 * @param os output stream
 */
template<typename T>
inline typename std::enable_if<std::is_same<T, std::string>::value, void>::type
PrintIp(const T& ip, std::ostream& os = std::cout) {
    os << ip << std::endl;
}

template<typename T>
struct IsTuple : std::false_type {};
template<typename... Ts>
struct IsTuple<std::tuple<Ts...>> : std::true_type {};

template <typename T, typename Tuple>
struct IsTupleWithIdenticalTypes;
template <typename T, typename... Ts>
struct IsTupleWithIdenticalTypes<T, std::tuple<Ts...>> : std::conjunction<std::is_same<T, Ts>...>{};

/**
 * prints ip
 * @tparam T tuple with identical types
 * @param ip ip_representation
 * @param os output stream
 */
template<typename T>
inline typename std::enable_if<IsTupleWithIdenticalTypes<typename std::tuple_element<0, T>::type, T>::value, void>::type
PrintIp(const T& ip, std::ostream& os = std::cout) {
    std::vector<int> res;
    apply([&res](auto&&... args) {((res.push_back(args)), ...);}, ip);
    for (size_t i = 0; i < res.size(); i++) {
        os << res[i] << (i == res.size() - 1 ? '\n' : '.');
    }
}

/**
 * prints ip
 * @tparam T any other type that is not specified by others template specializations
 * @param ip ip_representation
 * @param os output stream
 */
template<typename T>
inline typename std::enable_if<!std::is_same<T, std::string>::value && !std::is_integral<T>::value && !IsTuple<T>::value, void>::type
PrintIp(const T& ip, std::ostream& os = std::cout) {
    for (auto i = ip.begin(); i != ip.end(); i++) {
        if (i != ip.begin()) {
            os << '.';
        }
        os << *i;
    }
    os << std::endl;
}

} // namespace WithoutConcepts