#include "Domain/Session/Session.hpp"

#include <string>
#include <any>
#include <vector>

namespace 
{

  #define STUB(functionName)  std::any functionName( Domain::Session::SessionBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }


  // 2)  JL - Then define all system commands and possible functions with no implementations.
  //Applicant Functions
  STUB( getAllJobs      )
  STUB( filterJobs      )
  STUB( manageName      )
  STUB( manageJob       )
  STUB( manageLocation  )
  STUB( manageEducation )
  STUB( managePassword  )
  STUB( managepassPhrase)
  STUB( apply)

  //Employer Functions
  STUB( getReviews   )


  //Admin Functions
  STUB( resetAccount )
  STUB( shutdown     )


  std::any apply(Domain::Session::SessionBase & session, std::vector<std::string> & args)
  {
    
    // TO-DO  Verify there is such a job and the mark the job as being applied by user
    std::string results = "Job \"" + args[0] + "\" applied by \"" + session._credentials.userName + '"';
    session._logger << "apply:  " + results;
    return {results};
  }

  std::any managepassPhrase(Domain::Session::SessionBase & session, std::vector<std::string> & args)
  {


      if( session._credentials.passPhrase == args[0] )
    {
      std::string results             = "Password changed to: " + args[1] + "\" for user \"" + session._credentials.userName;
      session._credentials.passPhrase = args[1];
      return { results };
    }
    else
    {
      std::string results = "Incorrect password: " + args[0] + "\" for user \"" + session._credentials.userName;
      return { results };
    }
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
    _commandDispatch = { { "All Jobs", getAllJobs },
                         { "Filter Jobs", filterJobs },
                         { "Manage Name", manageName },
                         { "Manage Job", manageJob},
                         { "Manage Location", manageLocation},
                         { "Manage Education", manageEducation},
                         { "Manage Password", managePassword},
                         { "Apply", apply }};
  }




  CompanySession::CompanySession( const UserCredentials & credentials ) : SessionBase( "Company", credentials )
  {
    _commandDispatch = { { "Get Reviews", getReviews }};
  }
}    // namespace Domain::Session