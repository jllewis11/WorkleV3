#pragma once

#include "Domain/JobList/ApplyJobsHandler.hpp"

namespace Domain::JobList
{
  class Jobs : public Domain::JobList::ApplyJobsHandler
  {
  public:
    // Constructors
    using ApplyJobsHandler::ApplyJobsHandler;  // inherit constructors

    // Operations

    ~Jobs() noexcept override;
  }; // class Jobs
  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Jobs::~Jobs() noexcept
  {}


}  // namespace Domain::Library
