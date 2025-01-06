#include "JobApplicationManager.h"
#include "JobApplication.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>

// Constructor
JobApplicationManager::JobApplicationManager(const std::string &fileName) : fileName(fileName) {}

// Save a new application (single)
void JobApplicationManager::saveSingleApplication(const JobApplication &application) {
    std::ofstream outFile(fileName, std::ios::app); // Append mode
    if (outFile.is_open()) {
        outFile << application.getCompanyName() << "," << application.getJobTitle() << "," << application.EnumtoString() << "\n";
        outFile.close();
    } else {
        std::cerr << "Error: Could not open file to save application.\n";
    }
}

// Load all applications
std::vector<JobApplication> JobApplicationManager::loadApplications() {
    std::vector<JobApplication> applications;
    std::ifstream inFile(fileName);
    std::string line;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string company, title, status;

            // Parse the line
            if (std::getline(iss, company, ',') && std::getline(iss, title, ',') && std::getline(iss, status)) {
                applications.emplace_back(company, title, status);
            }
        }
        inFile.close();
    } else {
        std::cerr << "Error: Could not open file to load applications.\n";
    }

    return applications;
}

ApplicationStatus JobApplicationManager::stringToStatus(const std::string& status) {
    if (status == "Received") {
        return ApplicationStatus::Received;
    } else if (status == "In Progress") {
        return ApplicationStatus::In_Progress;
    } else if (status == "Rejected") {
        return ApplicationStatus::Rejected;
    } else if (status == "Withdrawn") {
        return ApplicationStatus::Withdrawn;
    } else {
        // Default case for invalid status
        return ApplicationStatus::In_Progress;  // Or handle the error in some way
    }
}

// Update an application's status
void JobApplicationManager::updateApplicationStatus(const std::string &applicantName, const std::string &newStatus) {
    std::vector<JobApplication> applications = loadApplications();
    bool found = false;

    for (auto &app : applications) {
        if (app.getJobTitle() == applicantName) {  // Match by applicant name (or job title)
            app.setStatus(stringToStatus(newStatus));  // Update status
            found = true;
            break;
        }
    }

    if (found) {
        saveApplications(applications);
        std::cout << "Application status updated successfully.\n";
    } else {
        std::cout << "Application not found.\n";
    }
}

// Delete an application
void JobApplicationManager::deleteApplication(const std::string &applicantName) {
    std::vector<JobApplication> applications = loadApplications();
    bool found = false;

    // Remove the application from the vector
    auto it = std::remove_if(applications.begin(), applications.end(),
        [&applicantName, &found](const JobApplication &app) {
            if (app.getJobTitle() == applicantName) {
                found = true; // Found the application to delete
                return true; // Mark for removal
            }
            return false; // Don't remove if not matching
        });

    // Only erase if an application was found
    if (found) {
        applications.erase(it, applications.end()); // Erase all marked elements
        saveApplications(applications); // Save the updated list
        std::cout << "Application deleted successfully.\n";
    } else {
        std::cout << "Application not found.\n";
    }
}

// Save all applications back to the file (multiple)
void JobApplicationManager::saveApplications(const std::vector<JobApplication> &applications) {
    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        for (const auto &app : applications) {
            outFile << app.getCompanyName() << "," << app.getJobTitle() << "," << app.EnumtoString() << "\n";
        }
        outFile.close();
    } else {
        std::cerr << "Error: Could not open file to save applications.\n";
    }
}