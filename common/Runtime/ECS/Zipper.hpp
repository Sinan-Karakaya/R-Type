/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Zipper
*/

#pragma once

#include "Iterator.hpp"

namespace RType::Runtime::ECS
{

template <class... Containers>
class Zipper
{
  public:
    using iterator = ZipperIterator<Containers...>;
    using iteratorTuple = typename iterator::iteratorTuple;

    Zipper(Containers &...cs)
        : m_begin(makeIteratorTuple(std::index_sequence_for<Containers...>(), cs.begin()...)),
          m_end(makeIteratorTuple(std::index_sequence_for<Containers...>(), cs.end()...))
    {
    }

    iterator begin()
    {
        return iterator(m_begin, m_computeSize(m_begin));
    }

    iterator end()
    {
        return iterator(m_end, m_computeSize(m_end));
    }

  private:
    static std::size_t m_computeSize(Containers &...containers)
    {
        return std::min({containers.size()...});
    }

    static iteratorTuple m_computeEnd(Containers &...containers)
    {
        return iteratorTuple(containers.end()...);
    }

    template <std::size_t... Is, typename... ContainerIterators>
    iteratorTuple makeIteratorTuple(std::index_sequence<Is...>, ContainerIterators... iterators)
    {
        return iteratorTuple(std::make_pair(iterators, iterators)...);
    }

  private:
    iteratorTuple m_begin;
    iteratorTuple m_end;
    std::size_t m_size;
};

} // namespace RType::Runtime::ECS
