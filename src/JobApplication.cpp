#include "JobApplication.h"
#include <iostream>
#include <fstream>
#include <vector>   


 JobApplication::JobApplication (): 
 CompanyName("Unknown"), Jobtitle("Unknown"), Status(ApplicationStatus::In_Progress) {};

JobApplication::JobApplication (std::string company, std::string title)
:CompanyName(company), Jobtitle(title), Status(ApplicationStatus::In_Progress) {};

std::string JobApplication::EnumtoString() const {
    switch (Status) {
        case ApplicationStatus::Received:
            return "Received";
        case ApplicationStatus::In_Progress:
            return "In Progress";
        case ApplicationStatus::Rejected:
            return "Rejected";
        case ApplicationStatus::Withdrawn:
            return "Withdrawn";
        default:
            return "Unknown Status";
    }
}

void JobApplication::DisplayDetails () const {
    std::cout << "Company Name: " << CompanyName <<std::endl;
    std::cout << "Job Title: " <<Jobtitle <<std::endl;
    std::cout <<"Status: " <<EnumtoString() <<std::endl;
}
// Getter functions to access private variables
std::string JobApplication::getCompanyName() const {
    return CompanyName;
}

std::string JobApplication::getJobTitle() const {
    return Jobtitle;
}

ApplicationStatus JobApplication::getStatus() const {
    return Status;
}

// Setter functions to modify the status
void JobApplication::setStatus(ApplicationStatus newStatus) {
    Status = newStatus;
}
void JobApplication::DisplayApplicantMenu() {
    std::cout << "\n=== Applicant Menu ===\n";
    std::cout << "1. Apply for a position \n";
    std::cout << "2. View recent applications \n";
    std::cout << "3. Exit\n";
}
void JobApplication::ApplyForPosition() {
    std::string name, id, companyName, jobTitle;
     // Get applicant's personal information
    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Enter your ID: ";
    std::cin >> id;


    std::cout << "Enter company name: ";
    std::cin >> companyName;
    std::cout << "Enter job title: ";
    std::cin >> jobTitle;
    

    // Create a new JobApplication with 'In_Progress' status
    JobApplication newApplication(companyName, jobTitle);
    
    // Save the application to a file (For simplicity, appending to a file here)
    std::ofstream file("applications.txt", std::ios::app);
    if (file.is_open()) {
        file << name << "," << id << "," << companyName << "," << jobTitle << ",In_Progress\n";
        std::cout << "Application submitted successfully.\n";
    } else {
        std::cout << "Error saving the application.\n";
    }
    file.close();
}
void JobApplication::ViewRecentApplications() {
    std::string name, id, line;
    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Enter your ID: ";
    std::cin >> id;
    
    //reading recent applications based on name and ID
    std::ifstream file("applications.txt");
    std::vector<std::string> lines; // To store all lines temporarily
    bool found = false;
    
    bool withdrawn = false; // Track if any application is withdrawn

    if (file.is_open()) {
        while (std::getline(file, line)) {
            size_t pos1 = line.find(",");
            size_t pos2 = line.find(",", pos1 + 1);
            size_t pos3 = line.find(",", pos2 + 1);
            size_t pos4 = line.find(",", pos3 + 1);

            std::string fileName = line.substr(0, pos1);
            std::string fileId = line.substr(pos1 + 1, pos2 - pos1 - 1);

            if (fileName == name && fileId == id) {
                std::string fileCompany = line.substr(pos2 + 1, pos3 - pos2 - 1);
                std::string fileJobTitle = line.substr(pos3 + 1, pos4 - pos3 - 1);
                std::string fileStatus = line.substr(pos4 + 1);

                std::cout << "Recent Application:\n";
                std::cout << "Name: " << fileName << "\n";
                std::cout << "ID: " << fileId << "\n";
                std::cout << "Company: " << fileCompany << "\n";
                std::cout << "Job Title: " << fileJobTitle << "\n";
                std::cout << "Status: " << fileStatus << "\n";
                found = true;

                std::string withdrawOption;
                std::cout << "Do you want to withdraw this application? (Yes/No): ";
                std::cin >> withdrawOption;

                if (fileStatus == "Rejected" || fileStatus == "Withdrawn") {
                   std::cout << "This application cannot be withdrawn.\n";    
                   continue;
                   }

                if (withdrawOption == "Yes" || withdrawOption == "Y") {
                    std::cout << "Withdrawing application...\n";
                    withdrawn = true; // Mark as withdrawn
                    continue; // Skip adding this line to the vector
                }
            }
            lines.push_back(line); // Add line to the list if not withdrawn
        }
        file.close();

        // Rewrite the file without the withdrawn applications
        std::ofstream outFile("applications.txt");
        if (outFile.is_open()) {
            for (const std::string &savedLine : lines) {
                outFile << savedLine << "\n";
            }
            outFile.close();
        } else {
            std::cout << "Error updating the file.\n";
        }

        if (!found) {
            std::cout << "No recent applications found.\n";
        } else if (withdrawn) {
            std::cout << "Application withdrawn successfully.\n"; // Confirm withdrawal
        }

    } else {
        std::cout << "Error reading applications file.\n";
    }
}
