#include "Domain/Session/Session.hpp"

#include <string>
#include <any>
#include <vector>

#include "Domain/ApplicantProfile/ManageProfile.hpp"
#include "Domain/ApplicantProfile/Profile.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"


namespace 
{
  #define STUB( functionName ) std::any functionName( Domain::Session::SessionBase & , const std::vector<std::string> & ) \
                        {return {};}    // Stubbed for now
  STUB( getAllJobs   )
  STUB( filterJobs   )
  STUB( getReviews   )
  STUB( resetAccount )
  STUB( shutdown     )

  std::any apply( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    // TO-DO  Verify there is such a job and the mark the job as being applied by user
    std::string results = "Job \"" + args[0] + "\" applied by \"" + session._credentials.userName + '"';
    session._logger << "apply:  " + results;
    return {results};
  }


  std::any manageProfile( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
      Domain::ApplicantProfile::OGProfileMaker * pfmaker = Domain::ApplicantProfile::OGProfileMaker::createProfileMaker();
      
      //pf get profile
      Domain::ApplicantProfile::ManageProfile * profile= pfmaker->createProfile();

      std::vector<std::string> pf = profile->getProfile(session._credentials.userName);


      auto &                                   _persistantData = TechnicalServices::Persistence::PersistenceHandler::instance();

      std::vector<std::vector<std::string>>     allProfiles     = _persistantData.findProfiles();

      std::string                               results = "Profile retrieved for \"" + session._credentials.userName + '"' + "\n";


      allProfiles[1].emplace( allProfiles[1].begin() + 3, args[1] );
      for( int i = 0; i < allProfiles[1].size(); ++i )
      {
        std::cout << allProfiles[1][i] << ", ";
      }
      std::cout << std::endl;

      std::cout << "ManageProfile Added:  " + args[0];

      delete pfmaker;
      delete profile;
      return {results};

  }

}  




namespace Domain::Session
{
  SessionBase::SessionBase( const std::string & description, const UserCredentials & credentials ) : _credentials( credentials ), _name( description )
  {
    _logger << "Session \"" + _name + "\" being used and has been successfully initialized";
  }




  SessionBase::~SessionBase() noexcept
  {
    _logger << "Session \"" + _name + "\" shutdown successfully";
  }




  std::vector<std::string> SessionBase::getCommands()
  {
    std::vector<std::string> availableCommands;
    availableCommands.reserve( _commandDispatch.size() );

    for( const auto & [command, function] : _commandDispatch ) 
    {
      if( command != "Apply" ) availableCommands.emplace_back( command );

    }
    

    return availableCommands;
  }

  std::any SessionBase::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
    std::string parameters;
    for( const auto & arg : args ) parameters += '"' + arg + "\"  ";
    _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

    auto it = _commandDispatch.find( command );
    if( it == _commandDispatch.end() )
    {
      std::string message = __func__;
      message += " attempt to execute \"" + command + "\" failed, no such command";

      _logger << message;
      throw BadCommand( message );
    }

    auto results = it->second( *this, args );

    if( results.has_value() )
    {
      _logger << "Responding with: \"" + std::any_cast<const std::string &>( results ) + '"';
    }

    return results;
  }

  AdministratorSession::AdministratorSession( const UserCredentials & credentials ) : SessionBase( "Administrator", credentials )
  {
    _commandDispatch = { { "Reset Account", resetAccount },
                         { "Shutdown System", shutdown } };
  }




  ApplicantSession::ApplicantSession( const UserCredentials & credentials ) : SessionBase( "Applicant", credentials )
  {
    _commandDispatch = { { "All Jobs", getAllJobs           },
                         { "Filter Jobs", filterJobs },
                         { "Manage Profile", manageProfile  },
                         { "Apply", apply                   } };
  }




  CompanySession::CompanySession( const UserCredentials & credentials ) : SessionBase( "Company", credentials )
  {
    _commandDispatch = { { "Get Reviews", getReviews }};
  }
}    // namespace Domain::Session

