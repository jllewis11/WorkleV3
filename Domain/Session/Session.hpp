#pragma once

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "Domain/Session/SessionHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"


namespace Domain::Session
{
  class SessionBase : public SessionHandler
  {
  public:
    SessionBase( const std::string & description, const UserCredentials & credentials );

    // Operations
    std::vector<std::string> getCommands() override;                                                                           // retrieves the list of actions (commands)
    std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args ) override;    // executes one of the actions retrieved


    // Destructor
    ~SessionBase() noexcept override = 0;

  protected:
  public: 
    using DispatchTable = std::map<std::string, std::any ( * )( Domain::Session::SessionBase &, const std::vector<std::string> & )>;
    friend class Policy;

    // Instance Attributes
    std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
    TechnicalServices::Logging::LoggerHandler &                _logger    = *_loggerPtr;

    UserCredentials const                                      _credentials;
    std::string const                                          _name = "Undefined";
    DispatchTable                                              _commandDispatch;
  };    // class SessionBase


  struct AdministratorSession : SessionBase
  {
    AdministratorSession( const UserCredentials & credentials );
  };
  struct ApplicantSession : SessionBase
  {
    ApplicantSession( const UserCredentials & credentials );
  };
  struct CompanySession : SessionBase
  {
    CompanySession( const UserCredentials & credentials );
  };


}    // namespace Domain::Session
