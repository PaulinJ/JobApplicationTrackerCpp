#include "JobApplication.h"
#include <iostream>

JobApplication::JobApplication (std::string company, std::string title, std::string appStatus)
:CompanyName(company), Jobtitle(title), Status(appStatus) {};
void JobApplication::DisplayDetails () const {
    std::cout << "Company Name: " << CompanyName <<std::endl;
    std::cout << "Job Title: " <<Jobtitle <<std::endl;
    std::cout <<"Status: " <<Status <<std::endl;
}
