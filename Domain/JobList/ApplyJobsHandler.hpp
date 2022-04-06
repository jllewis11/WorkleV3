#pragma once

namespace Domain::JobList
{
  // Library Package within the Domain Layer Abstract class
  class ApplyJobsHandler
  {
    public:

      virtual ~ApplyJobsHandler() noexcept = 0;

    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      ApplyJobsHandler & operator=( const ApplyJobsHandler &  rhs ) = default;  // copy assignment
      ApplyJobsHandler & operator=(       ApplyJobsHandler && rhs ) = default;  // move assignment

  };    // class MaintainBooksHandler





  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline ApplyJobsHandler::~ApplyJobsHandler() noexcept = default;


} // namespace Domain::Library
