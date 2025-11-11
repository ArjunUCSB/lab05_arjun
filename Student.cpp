#include "Student.h"
#include <sstream>
#include <string>

Student::Student(int perm, std::string lastName, std::string firstAndMiddleNames) {
  this->perm = perm;
  this->lastName = lastName;
  this->firstAndMiddleNames = firstAndMiddleNames;
}

Student::Student(std::string csvString) {
  std::istringstream iss(csvString);
  std::string permAsString;
  getline(iss, permAsString, ',');
  this->perm = std::stoi(permAsString);
  getline(iss, this->lastName, ',');
  getline(iss, this->firstAndMiddleNames, '\n');
}

int Student::getPerm() const {
  return perm;
}

std::string Student::getLastName() const {
  return lastName;
}

std::string Student::getFirstAndMiddleNames() const {
  return firstAndMiddleNames;
}

std::string Student::getFullName() const {
  return firstAndMiddleNames + " " + lastName;
}

std::string Student::toString() const {
  std::ostringstream oss;
  oss << "[" << perm << "," << lastName << "," << firstAndMiddleNames << "]";
  return oss.str();
}


