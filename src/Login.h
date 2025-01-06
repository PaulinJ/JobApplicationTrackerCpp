#pragma once
#include <string>
#include "JobApplication.h"

class Login {
    public:
   Login();
    
    // Menu and login logic
    void runMenu();  
    bool authenticateAdmin(); // Admin authentication function
    void DisplayMenu();  // Function to display the menu
};