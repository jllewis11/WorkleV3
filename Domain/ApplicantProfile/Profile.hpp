#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

#include "Domain/ApplicantProfile/ManageProfile.hpp"

namespace Domain::ApplicantProfile
{
  class Profile : public ManageProfile
  {
  public:
    Profile();

    std::vector<std::string> getProfile( std::string username ) override;
    void                     changePassword() override;
    ~Profile();

  protected:
    // Copy assignment operators, protected to prevent mix derived-type assignments
    Profile & operator=( const Profile & rhs ) = default;    // copy assignment
    Profile & operator=( Profile && rhs ) = default;         // move assignment
  private:
    // "Tiffany West", "3456", "11", "Front-end Developer at Amazon", "Minnesota", "Bachelors in Computer Science"
    std::vector<std::string> profile;
  };


  class ProfileResume : public ManageProfile
  {
  public:
    ProfileResume();
    std::vector<std::string> getProfile( std::string username ) override;
    void                     changePassword() override;
    std::string              setResume( std::string resume );
    std::string              getResume();
    ~ProfileResume();

  protected:
    // Copy assignment operators, protected to prevent mix derived-type assignments
    ProfileResume & operator=( const ProfileResume & rhs ) = default;    // copy assignment
    ProfileResume & operator=( ProfileResume && rhs ) = default;         // move assignment
  private:
    std::string resume = "file.txt";
  };
  struct OGProfileMaker
  {
    static OGProfileMaker *                           createProfileMaker();

    virtual Domain::ApplicantProfile::ManageProfile * createProfile() = 0;
  };

  struct ProfileMaker : OGProfileMaker
  {
    Profile * createProfile() override;
  };

  struct ProfileResumeMaker : OGProfileMaker
  {
    ProfileResume * createProfile() override;
  };

};    // namespace Domain::ApplicantProfile

