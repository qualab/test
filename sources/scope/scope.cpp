// Implementation of test::scope methods

#include "scope_data"
#include <algorithm>

namespace test
{
    scope::scope(scope& owner, const char* name)
        : m_data(std::make_shared<scope::data>(*this, owner, name))
    {
    }

    scope::scope(const char* name)
        : m_data(std::make_shared<scope::data>(*this, global(), name))
    {
    }

    scope::scope()
        : m_data(std::make_shared<scope::data>(*this))
    {
    }

    scope::~scope()
    {
    }

    const char* scope::get_name() const
    {
        return m_data->get_name();
    }

    const char* scope::get_path() const
    {
        return m_data->get_path();
    }

    const char* scope::get_full_name() const
    {
        return m_data->get_full_name();
    }

    const scope& scope::get_owner() const
    {
        return m_data->get_owner();
    }

    scope& scope::get_owner()
    {
        return m_data->get_owner();
    }

    void scope::run()
    {
        // TODO: trace::call::stack::push()
        
    }

    scope& scope::global()
    {
        static scope global;
        return global;
    }
}

// Unicode signature: Владимир Керимов
