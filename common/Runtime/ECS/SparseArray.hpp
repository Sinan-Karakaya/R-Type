/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** SparseArray
*/

#pragma once

#include <vector>

namespace RType::Runtime::ECS
{

    template <typename Component>
    class SparseArray
    {
    public:
        using valueType = Component;
        using referenceType = valueType &;
        using constReferenceType = const valueType &;
        using container = std::vector<valueType>;
        using sizeType = typename container::size_type;
        using iterator = typename container::iterator;
        using constIterator = typename container::const_iterator;

    public:
        SparseArray() = default;
        SparseArray(const SparseArray &) = default;
        SparseArray(SparseArray &&) noexcept = default;
        ~SparseArray() = default;

        SparseArray &operator=(const SparseArray &) = default;
        SparseArray &operator=(SparseArray &&) noexcept = default;

        referenceType operator[](std::size_t idx) { return m_data[idx]; }
        constReferenceType operator[](std::size_t idx) const { return m_data[idx]; }

        iterator begin() { return m_data.begin(); }
        constIterator begin() const { return m_data.begin(); }
        constIterator cbegin() const { return m_data.cbegin(); }

        iterator end() { return m_data.end(); }
        constIterator end() const { return m_data.end(); }
        constIterator cend() const { return m_data.cend(); }

        sizeType size() const { return m_data.size(); }

        referenceType insert_at(sizeType pos, const Component &)
        {
            m_data.insert(m_data.begin() + pos, Component {});
            return m_data[pos];
        }
        referenceType insert_at(sizeType pos, Component &&)
        {
            m_data.insert(m_data.begin() + pos, Component {});
            return m_data[pos];
        }

        template <class... Params>
        referenceType emplace_at(sizeType pos, Params &&...params)
        {
            m_data.emplace(m_data.begin() + pos, std::forward<Params>(params)...);
            return m_data[pos];
        }

        void erase(sizeType pos) { m_data.erase(m_data.begin() + pos); }

        sizeType get_index(const valueType &value) const
        {
            auto it = std::find(m_data.begin(), m_data.end(), value);
            if (it == m_data.end())
                return -1;
            return std::distance(m_data.begin(), it);
        }

    private:
        container m_data;
    };

} // namespace RType::Runtime::ECS
