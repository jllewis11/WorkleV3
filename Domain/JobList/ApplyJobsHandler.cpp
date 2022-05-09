#pragma once

#include <any>
#include <memory>       // unique_ptr
#include <stdexcept>    // runtime_error
#include <string>
#include <vector>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

#include "Domain/JobList/ApplyJobsHandler.hpp"

namespace Domain::JobList
{
  ApplyJobsHandler::ApplyJobsHandler(){};
};    // namespace Domain::JobList
