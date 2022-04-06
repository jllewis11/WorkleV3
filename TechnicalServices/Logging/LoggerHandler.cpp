#include <memory>    // unique_ptr

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"


namespace TechnicalServices::Logging
{
  std::unique_ptr<LoggerHandler> LoggerHandler::create( std::ostream & loggingStream )
  {
    auto & persistantData  = TechnicalServices::Persistence::PersistenceHandler::instance();

    return std::make_unique<SimpleLogger>( loggingStream );
  }
}    // namespace TechnicalServices::Logging
