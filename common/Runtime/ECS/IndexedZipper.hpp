/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** IndexedZipper
*/

#pragma once

#include "Iterator.hpp"

namespace RType::Runtime::ECS
{

    template <class... Containers>
    class IndexedZipper
    {
    public:
        using iterator = ZipperIterator<Containers...>;
        using iteratorTuple = typename iterator::iteratorTuple;

        IndexedZipper(Containers &...cs)
            : m_begin(iteratorTuple(cs.begin()...), m_computeSize(cs...)), m_end(m_computeEnd(cs...))
        {
        }

        iterator begin() { return m_begin; }
        iterator end() { return m_end; }

    private:
        static std::size_t m_computeSize(Containers &...containers) { return std::min({containers.size()...}); }

        static iteratorTuple m_computeEnd(Containers &...containers) { return iteratorTuple(containers.end()...); }

    private:
        iteratorTuple m_begin;
        iteratorTuple m_end;
        std::size_t m_size;
    };

} // namespace RType::Runtime::ECS
