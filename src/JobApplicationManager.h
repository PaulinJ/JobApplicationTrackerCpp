#pragma once
#include "JobApplication.h"
#include <vector>
#include <string>

class JobApplicationManager {
public:
    // Constructor
    JobApplicationManager(const std::string &fileName);
    static ApplicationStatus stringToStatus(const std::string& status);
    // Core operations
    void saveSingleApplication(const JobApplication &application);  // For saving a single application
    std::vector<JobApplication> loadApplications();
    void updateApplicationStatus(const std::string &applicantName, const std::string &newStatus);
    void deleteApplication(const std::string &applicantName);
    void saveApplications(const std::vector<JobApplication> &applications);  // For saving multiple applications

private:
    std::string fileName;  // Path to the file storing applications
};