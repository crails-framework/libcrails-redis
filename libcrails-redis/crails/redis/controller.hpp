#ifndef  CRAILS_REDIS_CONTROLLER_HPP
# define CRAILS_REDIS_CONTROLLER_HPP

# include <crails/controller.hpp>
# include <crails/http_response.hpp>
# include "connection.hpp"

namespace Crails
{
  namespace Redis
  {
    template<class SUPER = Crails::Controller, class DATABASE = Redis::Connection>
    class Controller : public SUPER
    {
    protected:
      DATABASE database;
    public:
      Controller(Context& context) : SUPER(context)
      {
      }
    };
  }
}

#endif
