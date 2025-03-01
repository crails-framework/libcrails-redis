#include "database.hpp"
#include <crails/shared_vars.hpp>

using namespace Crails;
using namespace Crails::Redis;

Database::Database(const Databases::DatabaseSettings& settings) : Databases::Database("redis")
{
  options.host = cast<std::string>(settings, "hostname", "0.0.0.0");
  options.port = cast<unsigned short>(settings, "port", 6379);
}

Database::~Database()
{
}

void Database::connect()
{
  connection = sw::redis::Redis(options);
}
