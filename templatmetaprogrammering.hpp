//
//  templatmetaprogrammering.hpp
//
//  Created by Espen Næss on 02.05.15.
//  Copyright (c) 2015 Espen Næss. All rights reserved.
//

#include <iostream>
#include <type_traits>
#include <vector>
#include <cstdio>

// templatmetaprogrammering med typeliste ved bruk av parameterpakker
template <typename T, typename... BlantTs>
struct er_i_typesettet;

template <typename T, typename... BlantTs>
struct er_i_typesettet <T, T, BlantTs...> {
    static const bool resultat = true;
};

template <typename T, typename FT, typename... BlantTs>
struct er_i_typesettet <T, FT, BlantTs...> : er_i_typesettet<T, BlantTs...> {};

template <typename T>
struct er_i_typesettet <T> {
    static const bool resultat = false;
};

// Testkode på å telle typeparametere - metaprogrammering

template <typename T, typename... BlantTs>
struct test_T;

template <typename T, typename FT, typename... BlantTs>
struct test_T<T, FT, BlantTs...> {
    static const int resultat = 1 + test_T<T, BlantTs...>::resultat;
};

template <typename T>
struct test_T<T> {
    static const int resultat = 1;
};

// SFINAE programmering

template <typename T>
struct Har_Constructor {
    template <typename U, typename = decltype(declval<U>().d)>
    static uint8_t SFINAE(U&&);
    template <typename U>
    static uint32_t SFINAE(...);

    static const bool verdi = (sizeof(SFINAE(declval<T>())) == sizeof(uint8_t));
};
