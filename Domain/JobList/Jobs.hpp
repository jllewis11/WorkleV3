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

namespace Domain::JobList
{
  class Jobs : public Domain::JobList::ApplyJobsHandler
  {
  public:
    Jobs();
    std::vector<std::vector<std::string>>  getJobs( const std::vector<std::string> & args ) override;

    ~Jobs() noexcept override;
  }; 
  inline Jobs::~Jobs() noexcept
  {}

  class FilterUserJobs : public Domain::JobList::ApplyJobsHandler
  {
  public:
    FilterUserJobs();
    std::vector<std::vector<std::string>>  getJobs( const std::vector<std::string> & args ) override;

    ~FilterUserJobs() noexcept override;
  };

  inline FilterUserJobs::~FilterUserJobs() noexcept
  {}

  class FilterKeywordJobs : public Domain::JobList::ApplyJobsHandler
  {
  public:
    FilterKeywordJobs();
    std::vector<std::vector<std::string>>  getJobs( const std::vector<std::string> & args ) override;

    ~FilterKeywordJobs() noexcept override;
  };

  inline FilterKeywordJobs::~FilterKeywordJobs() noexcept
  {}
} 