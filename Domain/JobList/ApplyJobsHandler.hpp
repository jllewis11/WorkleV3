#pragma once

#include <any>
#include <memory>       // unique_ptr
#include <stdexcept>    // runtime_error
#include <string>
#include <vector>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::JobList
{
  // UC2 SSD
  class ApplyJobsHandler
  {
  public:
    ApplyJobsHandler();

    virtual std::vector <std::vector<std::string>> getJobs( const std::vector<std::string> & args ) = 0;

    virtual ~ApplyJobsHandler() noexcept;


  protected:
    // Copy assignment operators, protected to prevent mix derived-type assignments
    ApplyJobsHandler & operator=( const ApplyJobsHandler & rhs ) = default;    // copy assignment
    ApplyJobsHandler & operator=( ApplyJobsHandler && rhs ) = default;         // move assignment
  };

  inline ApplyJobsHandler::~ApplyJobsHandler() noexcept = default;
}    // namespace Domain::ApplicantProfile
