#include "TechnicalServices/Persistence/SimpleDB.hpp"

#include <fstream>    // streamsize
#include <iomanip>    // quoted()
#include <limits>     // numeric_limits
#include <memory>     // make_unique()
#include <string>
#include <vector>

#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"





namespace
{

  struct ignore
  {
    char _seperator;
    ignore( char delimiter = '\n' ) : _seperator( delimiter ) {}
  };

  std::istream & operator>>( std::istream & s, ignore && delimiter )
  {
    s.ignore( std::numeric_limits<std::streamsize>::max(), delimiter._seperator );
    return s;
  }
}    // namespace




namespace TechnicalServices::Persistence
{
 
  SimpleDB::SimpleDB() : _loggerPtr( std::make_unique<TechnicalServices::Logging::SimpleLogger>())
  {
    _logger << "Simple DB being used and has been successfully initialized";
  }




  SimpleDB::~SimpleDB() noexcept
  {
    _logger << "Simple DB shutdown successfully";
  }




  std::vector<std::string> SimpleDB::findRoles()
  {
    return { "Applicant", "Company", "Administrator" };
  }

  std::vector<std::vector<std::string> > SimpleDB::findJobs()
  {
    return { { "Software Engineer I", "Amazon","Full Time", "false", "100000"},
             { "Software Engineer II", "Amazon", "Full Time", "false", "145000"},
             { "Software Engineer III", "Amazon", "Full Time", "false", "210000"},
             { "Software Engineer I", "Microsoft","Full Time", "false", "120000"},
             { "Software Engineer II", "Microsoft","Full Time", "false", "150000"},
             { "Software Engineer III", "Microsoft","Full Time", "true", "220000"},
             {"Site Reliability Engineer I", "Amazon", "Full Time", "false", "100000"},
             {"Site Reliability Engineer II", "Amazon", "Full Time", "false", "145000"},
             {"Site Reliability Engineer III", "Amazon", "Full Time", "false", "210000"},
             {"Site Reliability Engineer I", "Microsoft","Full Time", "false", "120000"},
             {"Site Reliability Engineer II", "Microsoft","Full Time", "false", "150000"},
             {"Site Reliability Engineer III", "Microsoft","Full Time", "true", "220000"},
             {"Site Reliability Engineer I", "Google","Full Time", "false", "120000"},
             {"Site Reliability Engineer II", "Google","Full Time", "false", "150000"},
             {"Site Reliability Engineer III", "Google","Full Time", "true", "220000"}};
  }

  std::vector<std::vector<std::string> > SimpleDB::findProfiles()
  {
    return { { "Tiffany West", "3456", "11", "Front-end Developer at Amazon", "Minnesota", "Bachelors in Computer Science"},
             { "John Doe", "9481", "6", "Front-end Developer at Fedex", "Minnesota", "Bachelors in Computer Science"},
             { "Timothy Jackson", "7895", "5", "Full-stack Developer at Twitter", "California", "Bachelors in Computer Science"},
             { "Ray Miles", "2578", "2", "Software Engineer at Bungie", "Seattle", "Bachelors in Computer Science"},
             { "Lily Smith", "9985", "8", "Data Scientist at Amazon", "California", "Bachelors in Computer Science"},
             { "Jane Doe", "4869", "6", "Technical Lead at Meta", "California", "Masters in Computer Science"}};
  }



  UserCredentials SimpleDB::findCredentialsByName( const std::string & name )
  {
    static std::vector<UserCredentials> storedUsers =
    {
    // Username    Pass Phrase         Authorized roles
      {"Jane",    "Doe",              {"Applicant",     "Company"   }},
      {"John",    "Doe",              {"Applicant"                  }},
      {"Mary",    "Smith",            {"Administrator"              }}
    };

    for( const auto & user : storedUsers ) if( user.userName == name ) return user;

    // Name not found, log the error and throw something
    std::string message = __func__;
    message += " attempt to find user \"" + name + "\" failed";

    _logger << message;
    throw PersistenceHandler::NoSuchUser( message );
  }

} // namespace TechnicalServices::Persistence
