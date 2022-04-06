#pragma once

#include "Domain/JobList/ApplyJobsHandler.hpp"

namespace Domain::JobList
{
  class Jobs : public Domain::JobList::ApplyJobsHandler
  {
  public:
    
    using ApplyJobsHandler::ApplyJobsHandler;

    

    ~Jobs() noexcept override;
  }; 
  inline Jobs::~Jobs() noexcept
  {}


} 