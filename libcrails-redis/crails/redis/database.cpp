#include "database.hpp"
#include <crails/any_cast.hpp>

using namespace Crails;
using namespace Crails::Redis;

Database::Database(const Databases::DatabaseSettings& settings) : Databases::Database("redis")
{
  options.host = defaults_to<const char*>(settings, "hostname", "0.0.0.0");
  options.port = defaults_to<unsigned short>(settings, "port", 6379);
}

Database::~Database()
{
}

void Database::connect()
{
  connection = sw::redis::Redis(options);
}
