#include <any>
#include <memory>       // unique_ptr
#include <stdexcept>    // runtime_error
#include <string>
#include <vector>

#include "Domain/ApplicantProfile/ManageProfile.hpp"
#include "Domain/ApplicantProfile/Profile.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::ApplicantProfile
{
  // ---------------------------------------------------------------------------------------------------------------------
  //                                       Profile class implementation
  // ---------------------------------------------------------------------------------------------------------------------
  //Contructors
  Profile::Profile()
  {
    std::cout << "Profile constructor called\n";
  };

  std::vector<std::string> Profile::getProfile( std::string username )
  {
    auto &                                persistantData = TechnicalServices::Persistence::PersistenceHandler::instance();
    std::vector<std::vector<std::string>> allProfiles    = persistantData.findProfiles();

    //loop through all profiles and find the one with the same username

    for( auto & profile : allProfiles )
    {
      if( profile[0] == username )
      {
        return profile;
      }
    }
  };

  void Profile::changePassword(){};


  Profile::~Profile() noexcept = default;


  // ---------------------------------------------------------------------------------------------------------------------
  //                                       ProfileResume class implementation
  // ---------------------------------------------------------------------------------------------------------------------
  //Contructors
  ProfileResume::ProfileResume()
  {
    std::cout << "ProfileResume constructor called\n";
  };

  std::vector<std::string> ProfileResume::getProfile( std::string username )
  {
    auto &                                persistantData = TechnicalServices::Persistence::PersistenceHandler::instance();
    std::vector<std::vector<std::string>> allProfiles    = persistantData.findProfiles();

    //loop through all profiles and find the one with the same username

    for( auto & profile : allProfiles )
    {
      if( profile[0] == username )
      {
        return profile;
      }
    }
  };

  void        ProfileResume::changePassword(){};


  std::string ProfileResume::setResume( std::string resume )
  {
    this->resume = resume;
    return resume;
  };

  std::string ProfileResume::getResume()
  {
    return resume;
  };

  ProfileResume::~ProfileResume() noexcept = default;


  // ---------------------------------------------------------------------------------------------------------------------
  //                                       ProfileSelfResume class implementation
  // ---------------------------------------------------------------------------------------------------------------------

  ProfileSelfResume::ProfileSelfResume()
  {
    std::cout << "ProfileSelfResume constructor called\n";
  };

  std::vector<std::string> ProfileSelfResume::getProfile( std::string username )
  {
    auto &                                persistantData = TechnicalServices::Persistence::PersistenceHandler::instance();
    std::vector<std::vector<std::string>> allProfiles    = persistantData.findProfiles();

    //loop through all profiles and find the one with the same username

    for( auto & profile : allProfiles )
    {
      if( profile[0] == username )
      {
        return profile;
      }
    }
  };

  void ProfileSelfResume::changePassword(){};

  void ProfileSelfResume::setResume( std::vector<std::string> temp )
  {
    this->resume.name       = temp[0];
    this->resume.email      = temp[1];
    this->resume.phone      = temp[2];
    this->resume.experience = temp[3];
    this->resume.education  = temp[4];
    this->resume.skills     = temp[5];
    this->resume.interests  = temp[6];
    this->resume.hobbies    = temp[7];
    this->resume.projects   = temp[8];
    this->resume.references = temp[9];
  };

  //std::vector<std::string>              getResume();
  std::vector<std::string> ProfileSelfResume::getResume()
  {
    std::vector<std::string> temp;
    temp.push_back( resume.name );
    temp.push_back( resume.email );
    temp.push_back( resume.phone );
    temp.push_back( resume.experience );
    temp.push_back( resume.education );
    temp.push_back( resume.skills );
    temp.push_back( resume.interests );
    temp.push_back( resume.hobbies );
    temp.push_back( resume.projects );
    temp.push_back( resume.references );
    return temp;
  };

  ProfileSelfResume::~ProfileSelfResume() noexcept = default;

  Domain::ApplicantProfile::Profile * Domain::ApplicantProfile::ProfileMaker::createProfile()
  {
    return new Domain::ApplicantProfile::Profile();
  };



  Domain::ApplicantProfile::ProfileResume * Domain::ApplicantProfile::ProfileResumeMaker::createProfile()
  {
    return new Domain::ApplicantProfile::ProfileResume();
  };

  Domain::ApplicantProfile::ProfileSelfResume * Domain::ApplicantProfile::ProfileSelfResumeMaker::createProfile()
  {
    return new Domain::ApplicantProfile::ProfileSelfResume();
  };



  Domain::ApplicantProfile::OGProfileMaker * Domain::ApplicantProfile::OGProfileMaker::createProfileMaker()
  {
    std::string type = "ProfileSelfResume";
    if( type == "Profile" )
    {
      return new Domain::ApplicantProfile::ProfileMaker();
    }
    else if( type == "ProfileResume" )
    {
      return new Domain::ApplicantProfile::ProfileResumeMaker();
    }
    else if( type == "ProfileSelfResume" )
    {
      return new Domain::ApplicantProfile::ProfileSelfResumeMaker();
    }
    else
    {
      throw std::runtime_error( "Invalid profile type" );
    }
  };
};    // namespace Domain::ApplicantProfile
