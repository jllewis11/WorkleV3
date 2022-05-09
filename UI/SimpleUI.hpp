#pragma once

#include <memory>    // std::unique_ptr

#include "Domain/Joblist/ApplyJobsHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

#include "UI/UserInterfaceHandler.hpp"




namespace UI
{

  class SimpleUI : public UI::UserInterfaceHandler
  {
    public:
      // Constructors
      SimpleUI();


      // Operations
      void launch() override;


      // Destructor
      ~SimpleUI() noexcept override;


    private:

      std::unique_ptr<TechnicalServices::Logging::LoggerHandler>            _loggerPtr;
      TechnicalServices::Persistence::PersistenceHandler                  & _persistentData;

      TechnicalServices::Logging::LoggerHandler                            & _logger = *_loggerPtr;
  };
} // namespace UI
