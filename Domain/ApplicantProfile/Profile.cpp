#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

#include "Domain/ApplicantProfile/ManageProfile.hpp"
#include "Domain/ApplicantProfile/Profile.hpp"

namespace Domain::ApplicantProfile
{

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

    void                                  ProfileResume::changePassword(){};


    std::string                           ProfileResume::setResume( std::string resume )
    {
        this->resume = resume;
        return resume;
    };

    std::string ProfileResume::getResume()
    {
        return resume;
    };

    ProfileResume::~ProfileResume() noexcept = default;


    Domain::ApplicantProfile::Profile * Domain::ApplicantProfile::ProfileMaker::createProfile()
    {
      return new Domain::ApplicantProfile::Profile();
    };



    Domain::ApplicantProfile::ProfileResume * Domain::ApplicantProfile::ProfileResumeMaker::createProfile()
    {
      return new Domain::ApplicantProfile::ProfileResume();
    };


  Domain::ApplicantProfile::OGProfileMaker * Domain::ApplicantProfile::OGProfileMaker::createProfileMaker()
    {
      std::string type = "Profile";
      if( type == "Profile" )
      {
        return new Domain::ApplicantProfile::ProfileMaker();
      }
      else if( type == "ProfileResume" )
      {
        return new Domain::ApplicantProfile::ProfileResumeMaker();
      }
      else
      {
        throw std::runtime_error( "Invalid profile type" );
      }
    };
};    // namespace Domain::ApplicantProfile

