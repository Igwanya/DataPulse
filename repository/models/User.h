#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
    User();

    enum TITLES {
        Mr,
        Mrs,
        Miss
    };

    enum ROLES
    {
        Administrator,
        Student,
        Staff
    };

    std::string gettitle() const;
    void setTitle(const std::string &newTitle);

    std::string getsurname() const;
    void setSurname(const std::string &newSurname);

    std::string getfullNames() const;
    void setFullNames(const std::string &newFullNames);

    std::string getstudentEmailAddress() const;
    void setStudentEmailAddress(const std::string &newStudentEmailAddress);

    std::string getregistratonNumber() const;
    void setRegistratonNumber(const std::string &newRegistratonNumber);
    // TODO:: include profile photo
    std::string getrole() const;
    void setRole(const std::string &newRole);

private:
    std::string _title;
    std::string _surname;
    std::string _fullNames;
    std::string _studentEmailAddress;
    std::string _registratonNumber;
    std::string _role;
};

#endif // USER_H
