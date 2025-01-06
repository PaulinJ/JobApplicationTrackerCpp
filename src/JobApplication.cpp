#include "JobApplication.h"
#include <iostream>
#include <fstream>



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