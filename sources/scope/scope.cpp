// Implementation of test::scope methods

#include "scope_data"

namespace test
{
    scope::scope(scope& owner, const char* name)
        : m_data(std::make_shared<scope::data>(owner, name))
    {
    }

    scope::scope(const char* name)
        : m_data(std::make_shared<scope::data>(global(), name))
    {
    }

    scope::scope()
        : m_data(std::make_shared<scope::data>(*this, global_name))
    {
    }

    scope::~scope()
    {
    }

    const char* scope::get_name() const
    {
    }

    const char* scope::get_path() const
    {
    }

    const scope& scope::get_owner() const
    {
    }

    scope& scope::get_owner()
    {
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
