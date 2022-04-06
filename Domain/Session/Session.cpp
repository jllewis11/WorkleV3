#include "Domain/Session/Session.hpp"

#include <string>
#include <any>
#include <vector>

namespace  // anonymous (private) working area
{
  // 1)  First define all system events (commands, actions, requests, etc.)
  #define STUB(functionName)  std::any functionName( Domain::Session::SessionBase & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now


  // 2)  JL - Then define all system commands and possible functions with no implementations.
  //Applicant Functions
  STUB( getAllJobs   )
  STUB( filterJobs   )
  STUB( manageProfile)

  //Employer Functions
  STUB( getReviews   )


  //Admin Functions
  STUB( resetAccount )
  STUB( shutdown     )


  std::any checkoutBook( Domain::Session::SessionBase & session, const std::vector<std::string> & args )
  {
    // TO-DO  Verify there is such a book and the mark the book as being checked out by user
    std::string results = "Title \"" + args[0] + "\" checkout by \"" + session._credentials.userName + '"';
    session._logger << "checkoutBook:  " + results;
    return {results};
  }


  std::any apply(Domain::Session::SessionBase & session, std::vector<std::string> & args)
  {
    // TO-DO  Verify there is such a job and the mark the job as being applied by user
    std::string results = "Job \"" + args[0] + "\" applied by \"" + session._credentials.userName + '"';
    session._logger << "apply:  " + results;
    return {results};
  }
}    // anonymous (private) working area










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

    for( const auto & [command, function] : _commandDispatch ) availableCommands.emplace_back( command );

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
      // The type of result depends on function called.  Let's assume strings for now ...
      _logger << "Responding with: \"" + std::any_cast<const std::string &>( results ) + '"';
    }

    return results;
  }

  // 2) Now map the above system events to roles authorized to make such a request.  Many roles can request the same event, and many
  //    events can be requested by a single role.
  AdministratorSession::AdministratorSession( const UserCredentials & credentials ) : SessionBase( "Administrator", credentials )
  {
    _commandDispatch = { { "Reset Account", resetAccount },
                         { "Shutdown System", shutdown } };
  }




  ApplicantSession::ApplicantSession( const UserCredentials & credentials ) : SessionBase( "Borrower", credentials )
  {
    _commandDispatch = { { "All Jobs", getAllJobs },
                         { "Filter Jobs", filterJobs },
                         { "Manage Profile", manageProfile}};
  }




  CompanySession::CompanySession( const UserCredentials & credentials ) : SessionBase( "Company", credentials )
  {
    _commandDispatch = { { "Checkout Book", checkoutBook },
                         { "Get Reviews", getReviews }};
  }
}    // namespace Domain::Session