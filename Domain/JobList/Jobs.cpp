#pragma once

#include <any>
#include <memory>       // unique_ptr
#include <stdexcept>    // runtime_error
#include <string>
#include <vector>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

#include "Domain/JobList/ApplyJobsHandler.hpp"
#include "Domain/JobList/Jobs.hpp"

namespace Domain::JobList
{
  Jobs::Jobs()
  {
    std::cout << "Jobs Controller created" << std::endl;
  };

  std::vector<std::vector<std::string>> Jobs::getJobs( const std::vector<std::string> & args )
  {
    auto &                                persistantData = TechnicalServices::Persistence::PersistenceHandler::instance();
    std::vector<std::vector<std::string>> allJobs        = persistantData.findJobs();

    return allJobs;
  }


  FilterUserJobs::FilterUserJobs()
  {
    std::cout << "FilterUserJobs Controller created" << std::endl;
  }

  std::vector<std::vector<std::string>> FilterUserJobs::getJobs( const std::vector<std::string> & args )
  {
    auto &                                persistantData = TechnicalServices::Persistence::PersistenceHandler::instance();
    std::vector<std::vector<std::string>> allJobs        = persistantData.findJobs();

    for( auto & job : allJobs )
    {
      //Jobs 0 equals to title of job. See if it matches with the user's previous jobs
      if( job[0] != args[0] )
      {
        allJobs.erase( std::remove( allJobs.begin(), allJobs.end(), job ), allJobs.end() );
      }
    }

    return allJobs;
  }




  FilterKeywordJobs::FilterKeywordJobs()
  {
    std::cout << "FilterKeywordJobs Controller created" << std::endl;
  }

  std::vector<std::vector<std::string>> FilterKeywordJobs::getJobs( const std::vector<std::string> & args )
  {
    auto &                                persistantData = TechnicalServices::Persistence::PersistenceHandler::instance();
    std::vector<std::vector<std::string>> allJobs        = persistantData.findJobs();
    //Return all jobs that contain the keyword
    for( auto & job : allJobs )
    {
      if( job[0].find( args[0] ) == std::string::npos )
      {
        allJobs.erase( std::remove( allJobs.begin(), allJobs.end(), job ), allJobs.end() );
      }
    }

    return allJobs;
  }


};    // namespace Domain::JobList