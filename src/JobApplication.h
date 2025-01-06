#pragma once
#include <string>

class JobApplication {

    public:
    //constructor for attributes initialization
    JobApplication (std::string company, std::string title, std::string appStatus);

    void DisplayDetails () const;

    private:
    std::string CompanyName;
    std::string Jobtitle;
    std::string Status;

};