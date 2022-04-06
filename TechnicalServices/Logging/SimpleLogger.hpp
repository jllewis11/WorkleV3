#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>      // localtime()
#include <iomanip>    // put_time()

#include "TechnicalServices/Logging/LoggerHandler.hpp"


namespace TechnicalServices::Logging
{
  class SimpleLogger : public TechnicalServices::Logging::LoggerHandler
  {
    public:
      //Constructors
      SimpleLogger( std::ostream & loggingStream = std::clog);

      // Operations
      SimpleLogger & operator<< ( const std::string & message ) override;

      // Destructor
      ~SimpleLogger() noexcept override;


    protected:
      std::ostream & _loggingStream;
  }; // class SimpleLogger


  inline SimpleLogger::SimpleLogger( std::ostream & loggingStream )
    : _loggingStream( loggingStream )
  {

    _loggingStream << std::unitbuf;

    *this << "Simple Logger being used and has been successfully initialized";
  }


  inline SimpleLogger::~SimpleLogger() noexcept
  {
    *this << "Simple Logger shutdown successfully";
  }



  inline SimpleLogger & SimpleLogger::operator<< ( const std::string & message )
  {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    
      std::tm destination;
      ::localtime_s(&destination, &now);
      _loggingStream << std::put_time( &destination, "%Y-%m-%d %X" ) << " | ";
    
    #else
      _loggingStream << std::put_time( std::localtime( &now ), "%Y-%m-%d %X" ) << " | ";
    #endif

    _loggingStream << message << '\n';

    return *this;
  }

} // namespace TechnicalServices::Logging
