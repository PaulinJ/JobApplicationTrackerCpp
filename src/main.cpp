#include "Login.h"
#include "JobApplication.h"
#include <iostream>

int main (){
    
    std::cout << "=== Welcome to Job Application Tracker ===\n";

    Login loginSystem;
    loginSystem.runMenu();

    return 0;
    
}