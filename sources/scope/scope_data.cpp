// Implementation of test::scope methods

#include "scope_data"
#include <stdexcept>

namespace test
{
    scope::data::data(scope& self)
        : m_self(self),
          m_owner(self),
          m_name(global_name),
          m_path(global_path),
          m_full_name(global_name)
    {
    }

    scope::data::data(scope& self, scope& owner, const char* name)
        : m_self(self), m_owner(owner), m_name(name)
    {
        if (&m_self == &m_owner && m_name == global_name)
        {
            m_path = global_path;
            m_full_name = global_name;
        }
        else
        {
            m_path = m_owner.get_path() + std::string(path_separator) + m_owner.get_name();
            m_full_name = m_path + std::string(path_separator) + m_name;
            auto& owner_inner = m_owner.m_data->m_inner;
            if (owner_inner.find(m_name) != owner_inner.end())
            {
                throw std::invalid_argument("Owner scope \"" + std::string(owner.get_full_name()) +
                                            "\" already has a scope with name \"" + m_name + '"');
            }
        }
    }

    const char* scope::data::get_name() const
    {
        return m_name.c_str();
    }

    const char* scope::data::get_path() const
    {
        return m_path.c_str();
    }

    const char* scope::data::get_full_name() const
    {
        return m_path.c_str();
    }

    const scope& scope::data::get_owner() const
    {
        return m_owner;
    }

    scope& scope::data::get_owner()
    {
        return m_owner;
    }
}

// Unicode signature: Владимир Керимов
