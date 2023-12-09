#pragma once
#include <tuple>

template <std::size_t Index>
struct IndexWrapper {};

// Funci�n get para acceder al elemento por �ndice
template <std::size_t Index, typename... Types>
decltype(auto) getI(const std::tuple<Types...>& t, IndexWrapper<Index>) {
    return std::get<Index>(t);
}

template <typename... Types>
class MyTuple {
public:
    // Constructor que recibe los elementos de la tupla
    MyTuple(Types... elements) : tuple_(elements...) {}

    // Funci�n get para acceder al elemento por �ndice
    template <std::size_t Index>
    decltype(auto) get() const {
        return getI(tuple_, IndexWrapper<Index>());
    }

private:
    // Tupla interna
    std::tuple<Types...> tuple_;
};
