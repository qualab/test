// Implementation of test::scope methods

#include <trace/call>
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

    void scope::run(const char* file, long long line)
    {
        using trace::call;
        auto warden = call::stack::push(
            call(get_full_name(), file, line)
        );
        each([file, line](scope& inner) {
            inner.run(file, line);
        });
    }

    scope& scope::global()
    {
        static scope global;
        return global;
    }

    void scope::each(const scope::handler& functor)
    {
        std::for_each(begin(), end(), functor);
    }

    scope::iterator scope::begin()
    {
        return m_data->begin();
    }

    scope::iterator scope::end()
    {
        return m_data->end();
    }

    scope::iterator scope::find(const char* name)
    {
        return m_data->find(name);
    }

    scope::iterator::iterator(scope::iterator::data&& new_data)
        : m_data(new(m_buffer) scope::iterator::data(std::move(new_data)))
    {
    }

    scope::iterator::iterator(const scope::iterator& another)
        : m_data(new(m_buffer) scope::iterator::data(*another.m_data))
    {
    }

    scope::iterator::iterator(scope::iterator&& temporary)
        : m_data(new(m_buffer) scope::iterator::data(std::move(*temporary.m_data)))
    {
    }

    scope::iterator::~iterator()
    {
        m_data->~data();
    }

    scope::iterator& scope::iterator::operator = (const scope::iterator& another)
    {
        *m_data = *another.m_data;
        return *this;
    }

    scope::iterator& scope::iterator::operator = (scope::iterator&& temporary)
    {
        *m_data = std::move(*temporary.m_data);
        return *this;
    }

    scope::iterator& scope::iterator::operator ++ ()
    {
        ++m_data->get_value();
        return *this;
    }

    scope::iterator& scope::iterator::operator -- ()
    {
        --m_data->get_value();
        return *this;
    }

    scope::iterator scope::iterator::operator ++ (int)
    {
        iterator result(*this);
        ++m_data->get_value();
        return result;
    }

    scope::iterator scope::iterator::operator -- (int)
    {
        iterator result(*this);
        --m_data->get_value();
        return *this;
    }

    const scope& scope::iterator::operator * () const
    {
        return m_data->get_value()->second;
    }

    scope& scope::iterator::operator * ()
    {
        return m_data->get_value()->second;
    }

    const scope* scope::iterator::operator -> () const
    {
        return &**this;
    }

    scope* scope::iterator::operator -> ()
    {
        return &**this;
    }

    bool scope::iterator::operator == (const scope::iterator& another) const
    {
        return m_data->get_value() == another.m_data->get_value();
    }

    bool scope::iterator::operator != (const scope::iterator& another) const
    {
        return m_data->get_value() != another.m_data->get_value();
    }
}

// Unicode signature: Владимир Керимов
