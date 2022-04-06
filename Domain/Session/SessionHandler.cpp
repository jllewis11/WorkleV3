#include "Domain/Session/SessionHandler.hpp"

#include <algorithm>    // std::any_of()
#include <memory>       // unique_ptr, make_unique<>()
#include <stdexcept>    // logic_error
#include <string>

#include "Domain/Session/Session.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace Domain::Session
{
  SessionHandler::~SessionHandler() noexcept = default;




  // returns a specialized object specific to the specified role
  std::unique_ptr<SessionHandler> SessionHandler::createSession( const UserCredentials & credentials )
  {

    // Authenticate the requester
    try
    {
      auto &          persistentData    = TechnicalServices::Persistence::PersistenceHandler::instance();
      UserCredentials credentialsFromDB = persistentData.findCredentialsByName( credentials.userName );

      if(    credentials.userName   == credentialsFromDB.userName
          && credentials.passPhrase == credentialsFromDB.passPhrase
          && std::any_of( credentialsFromDB.roles.cbegin(), credentialsFromDB.roles.cend(),
                          [&]( const std::string & role ) { return credentials.roles.size() > 0 && credentials.roles[0] == role; }
                        )
        )
      {
        // If authenticated user is authorized for the selected role, create a session specific for that role
        if( credentials.roles[0] == "Applicant"      ) return std::make_unique<Domain::Session::ApplicantSession>     ( credentials );
        if( credentials.roles[0] == "Company"     ) return std::make_unique<Domain::Session::CompanySession>    ( credentials );
        if( credentials.roles[0] == "Administrator" ) return std::make_unique<Domain::Session::AdministratorSession>( credentials );

        throw std::logic_error( "Invalid role requested in function " + std::string(__func__) ); // Just in case error
      }
    }
    catch( const TechnicalServices::Persistence::PersistenceHandler::NoSuchUser & ) {}  // Catch and ignore this anticipated condition

    return nullptr;

  }
} // namespace Domain::Session
