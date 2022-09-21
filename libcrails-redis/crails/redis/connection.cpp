#include "connection.hpp"
#include <crails/databases.hpp>

using namespace Crails::Redis;
using namespace std;

const string Connection::default_configuration_name = "redis";

Connection::Connection()
{
  require(default_configuration_name);
}

Connection::Connection(const string& name)
{
  require(name.length() ? name : default_configuration_name);
}

void Connection::require(const string& name)
{
  if (database_name != name || !database)
  {
    database_name = name;
    database = &CRAILS_DATABASE(Redis, name);
  }
}
