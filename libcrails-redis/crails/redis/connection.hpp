#ifndef  CRAILS_REDIS_CONNECTION_HPP
# define CRAILS_REDIS_CONNECTION_HPP

# include <sw/redis++/redis++.h>
# include <string_view>
# include "database.hpp"
# include "list.hpp"

namespace Crails
{
  namespace Redis
  {
    class Connection
    {
    public:
      Connection();
      Connection(const std::string&);

      void require(const std::string& name);
 
      sw::redis::Redis* operator->() const { return **database; }
      sw::redis::Redis* operator*() const { return **database; }

      template<typename TYPE>
      List<TYPE, Connection> make_list(std::string_view key) { return List<TYPE, Connection>(*this, key); }

      template<typename TYPE>
      SortedList<TYPE, Connection> make_sorted_list(std::string_view key) { return SortedList<TYPE, Connection>(*this, key); }

    private:
      Database* database = nullptr;
      std::string database_name;
      static const std::string default_configuration_name;
    };
  }
}

#endif
