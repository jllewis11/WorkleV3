#include <exception>
#include <iostream>
#include <locale>       // touuper(), locale()
#include <new>          // bad_alloc
#include <typeinfo>     // typeinfo.name()

#include "UI/UserInterfaceHandler.hpp"


int main( /*int argc, char argv[] */ )
{

    auto userInterface = UI::UserInterfaceHandler::createUI();
    userInterface->launch();


    std::cout << "\nProgram complete, initiating shutdown\n";

}
