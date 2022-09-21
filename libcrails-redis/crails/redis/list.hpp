#ifndef  CRAILS_REDIS_LIST_HPP
# define CRAILS_REDIS_LIST_HPP

# include <string>
# include <string_view>
# include <sw/redis++/redis++.h>
# include <crails/utils/backtrace.hpp>
# include <boost/lexical_cast.hpp>
# include <vector>
# include <list>
# include <optional>

namespace Crails
{
  namespace Redis
  {
    template<typename VALUE_TYPE, typename HANDLE>
    class SortedList
    {
    public:
      typedef std::pair<VALUE_TYPE, double> value_type;

      SortedList(HANDLE& connection, std::string_view key) : connection(connection), key(key)
      {
      }

      void insert(const value_type& value)
      {
        emplace(value.first, value.second);
      }

      void emplace(VALUE_TYPE value, double score)
      {
        connection->zadd(key, boost::lexical_cast<std::string>(value), score);
      }

      std::optional<value_type> pop_front()
      {
        return connection->zpopmin(key);
      }

      std::optional<value_type> pop_back()
      {
        return connection->zpopmax(key);
      }

      template<typename CONTAINER>
      void copy(CONTAINER& container, long long from, long long to) const
      {
        connection->zrange(key, from, to, std::back_inserter(container));
      }

      template<typename CONTAINER>
      void copy(CONTAINER& container) const
      {
        copy(container, 0, -1);
      }

      std::size_t count(double from, double to, sw::redis::BoundType bound_type = sw::redis::BoundType::OPEN) const
      {
        return connection->zcount(key, sw::redis::BoundedInterval<double>(from, to, bound_type));
      }

      std::size_t count() const
      {
        return connection->zcount(key, sw::redis::UnboundedInterval<double>());
      }

    private:
      std::string_view key;
      HANDLE& connection;
    };

    template<typename VALUE_TYPE, typename HANDLE>
    class List
    {
    public:
      typedef VALUE_TYPE value_type;

      List(HANDLE& connection, std::string_view value) : connection(connection), key(value)
      {
      }

      void push_back(const VALUE_TYPE value)
      {
        connection->rpush(key, boost::lexical_cast<std::string>(value));
      }

      void push_front(const VALUE_TYPE value)
      {
        connection->lpush(key, boost::lexical_cast<std::string>(value));
      }

      VALUE_TYPE pop_back()
      {
        std::optional<std::string> result = connection->rpop(key);
        if (!result)
          throw boost_ext::out_of_range("nothing to pop");
        return boost::lexical_cast<VALUE_TYPE>(*result);
      }

      VALUE_TYPE pop_front()
      {
        std::optional<std::string> result = connection->lpop(key);
        if (!result)
          throw boost_ext::out_of_range("nothing to pop");
        return boost::lexical_cast<VALUE_TYPE>(*result);
      }

      VALUE_TYPE at(long long position) const
      {
        std::optional<std::string> result = connection->lindex(key, position);
        if (!result)
          throw boost_ext::out_of_range("nothing to pop");
        return boost::lexical_cast<VALUE_TYPE>(*result);
      }

      VALUE_TYPE operator[](long long position) { return at(position); } const

      std::size_t size() const
      {
        return connection->llen(key);
      }

      std::vector<VALUE_TYPE> to_vector() const
      {
        std::vector<VALUE_TYPE> result;
        append_to(result);
        return result;
      }

      void append_to(std::vector<VALUE_TYPE>& array) const
      {
        connection->lrange(key, 0, -1, std::back_inserter(array));
      }

    private:
      std::string_view key;
      HANDLE& connection;
    };
  }
}

#endif
