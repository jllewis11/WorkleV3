#include "UI/SimpleUI.hpp"

#include <any>         // any_cast()
#include <iomanip>     // setw()
#include <iostream>    // streamsize
#include <limits>      // numeric_limits
#include <memory>      // unique_ptr, make_unique<>()
#include <string>      // string, getline()
#include <vector>


#include "Domain/JobList/ApplyJobsHandler.hpp"
#include "Domain/JobList/Jobs.hpp"

#include "Domain/Session/SessionHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace UI
{
  // Default constructor
  SimpleUI::SimpleUI()
  : _jobHandler   ( std::make_unique<Domain::JobList::Jobs>()                     ),   // will replace these with factory calls in the next increment
    _loggerPtr     ( TechnicalServices::Logging::LoggerHandler::create()            ),
    _persistentData( TechnicalServices::Persistence::PersistenceHandler::instance() )
  {
    _logger << "Simple UI being used and has been successfully initialized";
  }




  // Destructor
  SimpleUI::~SimpleUI() noexcept
  {
    _logger << "Simple UI shutdown successfully";
  }




  // Operations
  void SimpleUI::launch()
  {
    // 1) Fetch Role legal value list
    std::vector<std::string> roleLegalValues = _persistentData.findRoles();


    // 2) Present login screen to user and get username, password, and valid role
    Domain::Session::UserCredentials credentials  = {"", "", {""}};           // ensures roles[0] exists
    auto &                           selectedRole = credentials.roles[0];     // convenience alias

    std::unique_ptr<Domain::Session::SessionHandler> sessionControl;

    do
    {
      std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );

      std::cout << "  Username: ";
      std::getline( std::cin, credentials.userName );

      std::cout << "  Password: ";
      std::getline( std::cin, credentials.passPhrase );


      // Fix later with no role selection -
      unsigned menuSelection;
      do
      {
        for( unsigned i = 0; i != roleLegalValues.size(); ++i )   std::cout << std::setw( 2 ) << i << " - " << roleLegalValues[i] << '\n';
        std::cout << "  role (0-" << roleLegalValues.size()-1 << "): ";
        std::cin  >> menuSelection;
      } while( menuSelection >= roleLegalValues.size() );

      selectedRole = roleLegalValues[menuSelection];


      // 3) Validate user is authorized for this role, and if so create session
      sessionControl = Domain::Session::SessionHandler::createSession( credentials );
      if( sessionControl != nullptr )
      {
        _logger << "Login Successful for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";
        break;
      }

      std::cout << "** Login failed\n";
      _logger << "Login failure for \"" + credentials.userName + "\" as role \"" + selectedRole + "\"";

    } while( true );


    // 4) Fetch functionality options for this role
    do
    {
      auto        commands = sessionControl->getCommands();
      std::string selectedCommand;
      unsigned    menuSelection;

      do
      {
        for( unsigned i = 0; i != commands.size(); ++i ) std::cout << std::setw( 2 ) << i << " - " << commands[i] << '\n';
        std::cout << std::setw( 2 ) << commands.size() << " - " << "Quit\n";

        std::cout << "  action (0-" << commands.size() << "): ";
        std::cin >> menuSelection;
      } while( menuSelection > commands.size() );

      if( menuSelection == commands.size() ) break;

      selectedCommand = commands[menuSelection];
      _logger << "Command selected \"" + selectedCommand + '"';


      /******************************************************************************************************************************
      **  5) The user interface will collect relevant information to execute the chosen command.  This section requires the UI to
      **     know what information to collect, and hence what the available commands are.  Our goal is loose (minimal) coupling, not
      **     no coupling. This can be achieved in a variety of ways, but one common way is to pass strings instead of strong typed
      **     parameters.
      ******************************************************************************************************************************/
      if ( selectedCommand == "All Jobs")
      {
        std::vector<std::vector<std::string>> allJobs = _persistentData.findJobs();
        //Print all jobs and all values in the vector vector 
        
        for (unsigned i = 0; i < allJobs.size(); i++)
        {
          std::cout << "Job #" << i << std::endl;
          for (unsigned j = 0; j < allJobs[i].size(); j++)
          {
            std::cout << allJobs[i][j] << " ";
          }
          std::cout << std::endl;
        }
        std::vector<std::string> parameters2( 5 );

        char choice;
        //Ask if they would like to apply to the job
        std::cout << "Would you like to apply to this job? (y/n): ";
        std::cin >> std::ws;
        std::cin >> choice;

        //If they want to apply, ask for the job number, name, email, resume.
        
        if (choice == 'y')
        {
          std::cout << "Enter job number: ";
          std::cin >> std::ws;
          std::getline( std::cin, parameters2[0] );

          std::cout << "Enter your name: ";
          std::cin >> std::ws;
          std::getline( std::cin, parameters2[1] );

          std::cout << "Enter your email: ";
          std::cin >> std::ws;
          std::getline( std::cin, parameters2[2] );

          std::cout << "Enter your resume: ";
          std::cin >> std::ws;
          std::getline( std::cin, parameters2[3] );

          std::cout << "Enter your phone number: ";
          std::cin >> std::ws;
          std::getline( std::cin, parameters2[4] );
        
          selectedCommand = "Apply";
          auto results = sessionControl->executeCommand( selectedCommand, parameters2 );
          if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
        }

      } else if (selectedCommand == "Filter Jobs")
      //Filter through Keyword
      {
        //Ask for keyword
        //Print Search for either Title, company 

        std::vector<std::string> parameters3( 1 );
        std::cout << "Enter keyword: ";
        std::cin >> std::ws;
        std::getline( std::cin, parameters3[0] );

        std::vector<std::vector<std::string>> allJobs = _persistentData.findJobs();
        //Search through allJobs and print out all jobs that match the keyword
        for (unsigned i = 0; i < allJobs.size(); i++)
        {
          if (allJobs[i][0].find(parameters3[0]) != std::string::npos)
          {
            std::cout << "Job #" << i << std::endl;
            for (unsigned j = 0; j < allJobs[i].size(); j++)
            {
              std::cout << allJobs[i][j] << " ";
            }
            std::cout << std::endl;
          }
        }
        std::vector<std::string> parameters4( 5 );

        char choice;
        //Ask if they would like to apply to the job
        std::cout << "Would you like to apply to this job? (y/n): ";
        std::cin >> std::ws;
        std::cin >> choice;

        //If they want to apply, ask for the job number, name, email, resume.
        
        if (choice == 'y')
        {
          std::cout << "Enter job number: ";
          std::cin >> std::ws;
          std::getline( std::cin, parameters4[0] );

          std::cout << "Enter your name: ";
          std::cin >> std::ws;
          std::getline( std::cin, parameters4[1] );

          std::cout << "Enter your email: ";
          std::cin >> std::ws;
          std::getline( std::cin, parameters4[2] );

          std::cout << "Enter your resume: ";
          std::cin >> std::ws;
          std::getline( std::cin, parameters4[3] );

          std::cout << "Enter your phone number: ";
          std::cin >> std::ws;
          std::getline( std::cin, parameters4[4] );
        
          selectedCommand = "Apply";
          auto results = sessionControl->executeCommand( selectedCommand, parameters4 );
          if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
        }


      }


      else if( selectedCommand == "Another command" ) /* ... */ {}

      else sessionControl->executeCommand( selectedCommand, {} );
    } while( true );

    _logger << "Ending session and terminating";
  }
}
