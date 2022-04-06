#pragma once

namespace Domain::JobList
{
  // UC2 SSD
  class ApplyJobsHandler
  {
    public:

      virtual ~ApplyJobsHandler() noexcept = 0;

    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      ApplyJobsHandler & operator=( const ApplyJobsHandler &  rhs ) = default;  // copy assignment
      ApplyJobsHandler & operator=(       ApplyJobsHandler && rhs ) = default;  // move assignment

  };

  inline ApplyJobsHandler::~ApplyJobsHandler() noexcept = default;



