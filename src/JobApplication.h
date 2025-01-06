#pragma once
#include <string>

enum class ApplicationStatus {
    Received,
    In_Progress,
    Rejected,
    Withdrawn
};
class JobApplication {

    public:
    
    JobApplication ();
    //constructor for attributes initialization
    JobApplication (std::string company, std::string title);
    std::string EnumtoString() const;

    void DisplayApplicantMenu();
    void ApplyForPosition(); 
    void ViewRecentApplications();

    // Getter functions to access private variables
    std::string getCompanyName() const;
    std::string getJobTitle() const;
    ApplicationStatus getStatus() const;

    // Setter functions to modify the status
    void setStatus(ApplicationStatus newStatus);

    void withdraw();

    void DisplayDetails () const;

    private:
    std::string CompanyName;
    std::string Jobtitle;
    ApplicationStatus Status;
    bool isWithdrawn = false;

};