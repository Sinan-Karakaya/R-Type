/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Iterator
*/
#pragma once

#include <tuple>

namespace RType::Runtime::ECS
{

    template <class... Containers>
    class Zipper;

    template <class... Containers>
    class ZipperIterator
    {
        template <class Container>
        using iterator = typename Container::iterator;

        template <class Container>
        using itReference = typename iterator<Container>::reference;

    public:
        using valueType = std::tuple<itReference<Containers>...>;
        using reference = valueType;
        using pointer = void;
        using differenceType = std::size_t;
        using iteratorCategory = std::forward_iterator_tag;
        using iteratorTuple = std::tuple<iterator<Containers>...>;

        friend Zipper<Containers...>;
        ZipperIterator(const iteratorTuple &itTuple, std::size_t max) : m_current(itTuple), m_max(max) {}

        ZipperIterator(const ZipperIterator &z) = default;

        ZipperIterator operator++()
        {
            incrAll(m_seq);
            return *this;
        }
        ZipperIterator &operator++(int)
        {
            incrAll(m_seq);
            return *this;
        }

        valueType operator*() { return toValue(m_seq); }

        valueType operator->() { return toValue(m_seq); }

        friend bool operator==(const ZipperIterator &lhs, const ZipperIterator &rhs)
        {
            return lhs.m_current == rhs.m_current;
        }

        friend bool operator!=(const ZipperIterator &lhs, const ZipperIterator &rhs) { return !(lhs == rhs); }

    private:
        template <std::size_t... Is>
        void incrAll(std::index_sequence<Is...>)
        {
            std::initializer_list<int> {(std::get<Is>(m_current)++, 0)...};
        }

        template <std::size_t... Is>
        bool allSet(std::index_sequence<Is...>)
        {
            return ((std::get<Is>(m_current) != std::get<Is>(m_current).end()) && ...);
        }

        template <std::size_t... Is>
        valueType toValue(std::index_sequence<Is...>)
        {
            return std::make_tuple(*std::get<Is>(m_current)...);
        }

    private:
        iteratorTuple m_current;
        std::size_t m_max;
        std::size_t idx;

        static constexpr std::index_sequence_for<Containers...> m_seq {};
    };

} // namespace RType::Runtime::ECS
