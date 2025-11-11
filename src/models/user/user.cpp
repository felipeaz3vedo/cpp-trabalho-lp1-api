#include "models/user/user.h"

#include <algorithm> 

User::User(
    int id,
    string name,
    string email,
    UserType type)
{
    this->id = id;
    this->name = name;
    this->email = email;
    this->type = type;

    this->validate();
}

int User::getId() const
{
    return this->id;
}

string User::getName() const
{
    return this->name;
}

void User::setName(string name)
{
    this->name = name;
    this->validateName();
}

string User::getEmail() const
{
    return this->email;
}

void User::setEmail(string email)
{
    this->email = email;
    this->validateEmail();
}

UserType User::getType() const
{
    return this->type;
}

void User::validate()
{
    this->validateName();
    this->validateEmail();
}

void User::validateName()
{
    bool onlySpaces = true;

    for (char c : this->name) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            onlySpaces = false;
            break;
        }
    }

    if (this->name.empty() || onlySpaces) {
        throw ValidationException("Field 'name' must not be empty.");
    }
}

void User::validateEmail()
{
    if (this->email.empty()) {
        throw ValidationException("Field 'email' must not be empty.");
    }

    for (char c : this->email) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            throw ValidationException("Field 'email' must not contain spaces.");
        }
    }

    size_t atPos = this->email.find('@');
    if (atPos == string::npos || atPos == 0 || atPos == this->email.size() - 1) {
        throw ValidationException("Field 'email' must be a valid email address.");
    }

    size_t dotPos = this->email.find('.', atPos);
    if (dotPos == string::npos || dotPos == atPos + 1 || dotPos == this->email.size() - 1) {
        throw ValidationException("Field 'email' must be a valid email address.");
    }
}
