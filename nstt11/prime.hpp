#ifndef PRIME_H
#define PRIME_H

#include <type_traits>

template <unsigned P, unsigned N = P - 1>
struct is_prime : std::bool_constant<(P % N > 0) && is_prime<P, N - 1>::value> {
};

template <unsigned P>
struct is_prime<P, 1> : std::true_type {};

template <>
struct is_prime<1, 0> : std::false_type {};

template <>
struct is_prime<0, 0> : std::false_type {};

template <unsigned N, unsigned K>
struct nth_prime
    : std::conditional_t<is_prime<K>::value, nth_prime<N - 1, K + 1>,
                         nth_prime<N, K + 1> > {};

template <unsigned K>
struct nth_prime<0, K> : std::integral_constant<unsigned, K - 1> {};

template <unsigned N>
struct nth_prime_v : nth_prime<N, 2> {};

#endif