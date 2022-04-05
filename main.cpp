#include <exception>
#include <iostream>
#include <locale>       // touuper(), locale()
#include <new>          // bad_alloc
#include <typeinfo>     // typeinfo.name()

#include "UI/UserInterfaceHandler.hpp"


int main( /*int argc, char argv[] */ )
{
  try
  {
    auto userInterface = UI::UserInterfaceHandler::createUI();
    userInterface->launch();


    std::cout << "\nProgram complete, initiating shutdown\n";
  }



  catch( const std::bad_alloc & ex )
  {
    std::cerr << "Fatal:  Uncaught memory allocation exception\n\n"
              << ex.what() << '\n';
  }

  catch( const std::exception & ex )
  {
    std::cerr << "Fatal:  Uncaught standard exception\n"
              << typeid( ex ).name() << '\n'
              << ex.what() << '\n';
  }

  catch( ... )
  {
    std::cerr << "Fatal:  Uncaught (unknown type) exception\n";
  }
}
