// Implementation of test::scope methods

#include "scope_data"
#include <stdexcept>

namespace test
{
    namespace
    {
        const std::string GLOBAL_NAME = "";
        const std::string GLOBAL_PATH = "";
        const std::string GLOBAL_FULL_NAME = "";
        const std::string PATH_SEPARATOR = "/";
    }

    scope::data::data(scope& self)
        : m_self(self),
          m_owner(self),
          m_name(GLOBAL_NAME),
          m_path(GLOBAL_PATH),
          m_full_name(GLOBAL_FULL_NAME)
    {
    }

    scope::data::data(scope& self, scope& owner, const char* name)
        : m_self(self),
          m_owner(owner),
          m_name(name)
    {
        m_path = m_owner.get_full_name() + PATH_SEPARATOR;
        m_full_name = m_path + m_name;
        auto& owner_inner = m_owner.m_data->m_inner;
        if (owner_inner.find(m_name) != owner_inner.end())
        {
            throw std::invalid_argument("Owner scope \"" + std::string(owner.get_full_name()) +
                                        "\" already has a scope with name \"" + m_name + '"');
        }
        owner_inner.insert(std::make_pair(m_name, m_self));
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

    scope::iterator scope::data::begin()
    {
        return iterator(m_inner.begin());
    }

    scope::iterator scope::data::end()
    {
        return iterator(m_inner.end());
    }

    scope::iterator scope::data::find(const char* name)
    {
        return iterator(m_inner.find(name));
    }

    scope::iterator::data::data(const scope::iterator::data::value_type& value)
        : m_value(value)
    {
    }

    void scope::iterator::data::set_value(const scope::iterator::data::value_type& value)
    {
        m_value = value;
    }

    const scope::iterator::data::value_type& scope::iterator::data::get_value() const
    {
        return m_value;
    }

    scope::iterator::data::value_type& scope::iterator::data::get_value()
    {
        return m_value;
    }
}

// Unicode signature: Владимир Керимов
