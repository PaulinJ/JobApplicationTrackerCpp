#pragma once
#include <string>

class Login {
    public:
    Login();

    // Menu and login logic
    void runMenu();  
    bool authenticateAdmin(); // Admin authentication function
    void DisplayMenu();  // Function to display the menu
};