#include "Login.h"
#include <iostream>

bool Login::authenticateAdmin() {
    const std::string adminPassword = "admin123"; 
    std::string enteredPassword;
    
    std::cout << "Enter password for Admin: ";
    std::cin >> enteredPassword;
    
    while (enteredPassword != adminPassword) {
        std::string position;
        std::cin.ignore(100000, '\n'); // Clear the input buffer
        std::cout << "Incorrect Password! Retry? (Yes/No): ";
        std::cin >> position;

        while (position != "Yes" && position != "Y" && position != "No" && position != "N") {
            std::cout << "Please enter either Yes/Y or No/N: ";
            std::cin.clear();
            std::cin >> position;
        }

        if (position == "Yes" || position == "Y") {
            std::cout << "Password: ";
            std::cin >> enteredPassword;
        }
        else {
            std::cout << "Exited.\n";
            return false;  // Exit if user decides not to retry
        }
    }
    
    return true;  // Successfully authenticated
}

void Login::DisplayMenu() {
    std::cout << "\n=== Job Application Tracker ===\n";
    std::cout << "1. Open as Admin\n";
    std::cout << "2. Open as Applicant\n";
    std::cout << "3. Exit\n";
}

void Login::runMenu() {
    char choice;

    do {
        DisplayMenu();  // Show the menu options
        std::cout << "Enter the option (1, 2 or 3): ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                if (authenticateAdmin()) {
                    std::cout << "\nAdmin Access Granted.\n";
                    // Handle admin functionalities here

                }
                else {
                    std::cout << "Admin login failed.\n";
                }
                
                break;
            case '2':
                std::cout << "\nApplicant Mode - No Password Required\n";
                // Handle applicant functionalities here
                break;
            case '3':
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice! Please select 1, 2, or 3.\n";
                break;
        }

        std::cout << "Do you want to go back to the central menu? (Yes/No): ";
        std::string position;
        std::cin >> position;

        while (position != "Yes" && position != "Y" && position != "No" && position != "N") {
            std::cout << "Please enter either Yes/Y or No/N: ";
            std::cin.clear();
            std::cin >> position;
        }

        if (position == "No" || position == "N") {
            std::cout << "Exited.\n";
            break;
        }

    } while (choice != '3');  // Loop until the user selects 'Exit'
}