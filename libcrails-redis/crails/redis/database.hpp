#ifndef  CRAILS_REDIS_DATABASE_HPP
# define CRAILS_REDIS_DATABASE_HPP

# include <crails/databases.hpp>
# include <sw/redis++/redis++.h>
# include <optional>

namespace Crails
{
  namespace Redis
  {
    class Database : public Crails::Databases::Database
    {
    public:
      Database(const Crails::Databases::DatabaseSettings&);
      ~Database() override;

      static const std::string ClassType() { return "redis"; }
      sw::redis::Transaction transaction() { return connection->transaction(); }

      sw::redis::Redis* operator->() { return &(*connection); }
      sw::redis::Redis* operator*() { return &(*connection); }

      void connect() override;
    private:
      sw::redis::ConnectionOptions options;
      std::optional<sw::redis::Redis> connection;
    };
  }
}

#endif
