#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::ApplicantProfile
{
  // UC2 SSD
  class ManageProfile
  {
    public:
        ManageProfile();

        virtual std::vector<std::string>              getProfile( std::string username ) = 0;
        virtual void                                  changePassword()                   = 0;
        virtual ~ManageProfile()                                                         noexcept;


    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      ManageProfile & operator=( const ManageProfile &  rhs ) = default;  // copy assignment
      ManageProfile & operator=(       ManageProfile && rhs ) = default;  // move assignment
      

  };

  inline ManageProfile::~ManageProfile() noexcept = default;
}


