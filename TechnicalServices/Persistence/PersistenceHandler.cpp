#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"

namespace TechnicalServices::Persistence
{
  PersistenceHandler::~PersistenceHandler() noexcept = default;




  PersistenceHandler & PersistenceHandler::instance()
  {

    using SelectedDatabase = SimpleDB;

    static SelectedDatabase instance;    
    return instance;
  }
}    // namespace TechnicalServices::Persistence
