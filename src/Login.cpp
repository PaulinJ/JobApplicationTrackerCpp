#include "Login.h"
#include <fstream>
#include <vector>
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
void Login::viewAllApplications() {
    std::ifstream inputFile("applications.txt");
    std::vector<std::string> applications;
    std::string line;

    // Read applications into a vector for easy manipulation
    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            applications.push_back(line);
        }
        inputFile.close();
    } else {
        std::cerr << "Error: Could not open the applications file.\n";
        return;
    }

    if (applications.empty()) {
        std::cout << "No applications found.\n";
        return;
    }

    bool exitMenu = false;
    while (!exitMenu) {
        std::cout << "\n=== All Applications ===\n";
        for (size_t i = 0; i < applications.size(); ++i) {
            std::cout << i + 1 << ". " << applications[i] << "\n";
        }

        std::cout << "\nSelect an application to Approve/Reject (0 to Exit): ";
        size_t choice;
        std::cin >> choice;

        if (choice == 0) {
            exitMenu = true;  // Exit menu
        } else if (choice > 0 && choice <= applications.size()) {
            // Admin chooses to approve/reject
            std::cout << "\nSelected: " << applications[choice - 1] << "\n";
            std::cout << "1. Approve\n2. Reject\nEnter your choice: ";
            int decision;
            std::cin >> decision;

            if (decision == 1) {
                applications[choice - 1] += " [APPROVED]";
                std::cout << "Application Approved.\n";
            } else if (decision == 2) {
                applications[choice - 1] += " [REJECTED]";
                std::cout << "Application Rejected.\n";
            } else {
                std::cout << "Invalid choice. Returning to menu.\n";
            }
        } else {
            std::cout << "Invalid selection. Please try again.\n";
        }
    }

    // Write the updated applications back to the file
    std::ofstream outputFile("applications.txt");
    if (outputFile.is_open()) {
        for (const auto &app : applications) {
            outputFile << app << "\n";
        }
        outputFile.close();
    } else {
        std::cerr << "Error: Could not save the updated applications.\n";
    }
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
                    char adminChoice;
        do {
            std::cout << "\n=== Admin Menu ===\n";
            std::cout << "1. View all applications\n";
            std::cout << "2. Exit Admin Menu\n";
            std::cout << "Enter your choice: ";
            std::cin >> adminChoice;

            switch (adminChoice) {
                case '1':
                    viewAllApplications();  // View all applications
                    break;

                case '2':
                    std::cout << "Exiting Admin Menu...\n";
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } while (adminChoice != '2');  // Loop until admin chooses to exit
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

    } while (choice != '3'); 
}