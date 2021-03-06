#pragma once

#include <map>
#include <stdexcept>    // domain_error, runtime_error
#include <string>
#include <vector>




namespace TechnicalServices::Persistence
{
  // Function argument type definitions
  struct UserCredentials
  {
    std::string               userName;
    std::string               passPhrase;
    std::vector<std::string>  roles;
    std::string               accNum;
  };


  class PersistenceHandler
  {
    public:
      // Exceptions
      struct PersistenceException : std::runtime_error   {using runtime_error       ::runtime_error;};
      struct   NoSuchUser         : PersistenceException {using PersistenceException::PersistenceException;};
      struct   NoSuchProperty     : PersistenceException {using PersistenceException::PersistenceException;};

      // Creation (Singleton)
      PersistenceHandler            (                            ) = default;
      PersistenceHandler            ( const PersistenceHandler & ) = delete;
      PersistenceHandler & operator=( const PersistenceHandler & ) = delete;
      static  PersistenceHandler & instance();


      // Operations
      virtual std::vector<std::string> findRoles()                                       = 0;   // Returns list of all legal roles
      virtual std::vector<std::vector<std::string> >findJobs()                           = 0;   // Returns list of all jobs
      virtual std::vector<std::vector<std::string> >findProfiles()                           = 0;
      virtual UserCredentials          findCredentialsByName( const std::string & name ) = 0;   // Returns credentials for specified user, throws NoSuchUser if user not found

      // Destructor
      virtual ~PersistenceHandler() noexcept = 0;
  };
} // namespace TechnicalServices::Persistence
