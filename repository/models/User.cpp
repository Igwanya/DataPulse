#include "User.h"

User::User()
{

}

std::string User::gettitle() const
{
    return _title;
}

void User::setTitle(const std::string &newTitle)
{
    _title = newTitle;
}

std::string User::getsurname() const
{
    return _surname;
}

void User::setSurname(const std::string &newSurname)
{
    _surname = newSurname;
}

std::string User::getfullNames() const
{
    return _fullNames;
}

void User::setFullNames(const std::string &newFullNames)
{
    _fullNames = newFullNames;
}

std::string User::getstudentEmailAddress() const
{
    return _studentEmailAddress;
}

void User::setStudentEmailAddress(const std::string &newStudentEmailAddress)
{
    _studentEmailAddress = newStudentEmailAddress;
}

std::string User::getregistratonNumber() const
{
    return _registratonNumber;
}

void User::setRegistratonNumber(const std::string &newRegistratonNumber)
{
    _registratonNumber = newRegistratonNumber;
}

std::string User::getrole() const
{
    return _role;
}

void User::setRole(const std::string &newRole)
{
    _role = newRole;
}
