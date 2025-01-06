#include "Login.h"
#include <iostream>


Login::Login() {};
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
        // Display the central menu
        DisplayMenu();
        std::cout << "Enter the option (1, 2 or 3): ";
        std::cin >> choice;

        switch (choice) {
            case '1':  // Admin functionality
                if (authenticateAdmin()) {
                    std::cout << "\nAdmin Access Granted.\n";
                    // Call admin functionality (to be implemented later)
                } else {
                    std::cout << "Admin login failed.\n";
                }
                break;

            case '2': {  // Applicant functionality
                std::cout << "\nApplicant Mode - No Password Required\n";
                JobApplication app;  
                char applicantChoice;

                do {
                    app.DisplayApplicantMenu();  // Display applicant menu
                    std::cout << "Enter your choice: ";
                    std::cin >> applicantChoice;

                    switch (applicantChoice) {
                        case '1':
                            app.ApplyForPosition();  // Apply for a job
                            break;

                        case '2':
                            app.ViewRecentApplications();  // View applications
                            break;

                        case '3':
                            std::cout << "Returning to the central menu...\n";
                            break;

                        default:
                            std::cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                } while (applicantChoice != '3');  // Exit applicant submenu
                break;
            }

            case '3':  // Exit the program
                std::cout << "Exiting the program. Goodbye!\n";
                break;

            default:  // Handle invalid input
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != '3');  // Loop until the user selects 'Exit' from the central menu
}