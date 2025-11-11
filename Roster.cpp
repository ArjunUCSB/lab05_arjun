#include "Roster.h"
#include <cstdlib>
#include <fstream>
#include <cassert>

Roster::Roster() {
  numStudents = 0;
  for (int i = 0; i < ROSTER_MAX; i++) {
    students[i] = NULL;
  }
}

void Roster::resetRoster() {
  while (numStudents > 0) {
    delete students[numStudents - 1];
    numStudents--;
  }
}

void Roster::addStudentsFromFile(std::string filename) {
  std::ifstream ifs;
  ifs.open(filename);
  if (ifs.fail()) {
    std::cerr << "Could not open input file: " << filename << std::endl;
    exit(2);
  }
  addStudentsFromStream(ifs);
}

void Roster::addStudentsFromStream(std::istream &is) {
  resetRoster();
  std::string thisLine;
  getline(is, thisLine);
  if (is.eof() || is.fail()) {
    std::cerr << "Unable to read first line of input stream" << std::endl;
    exit(3);
  }
  getline(is, thisLine);
  while (!is.eof() && !is.fail()) {
    Student *sPtr = new Student(thisLine);
    students[numStudents] = sPtr;
    numStudents++;
    getline(is, thisLine);
  }
}

int Roster::getNumStudents() const {
  return numStudents;
}

Student Roster::getStudentAt(int index) const {
  return *students[index];
}

std::string Roster::toString() const {
  std::string result = "{\n";
  for (int i = 0; i < numStudents; i++) {
    result += students[i]->toString();
    if (i < numStudents - 1)
      result += ",\n";
    else
      result += "\n";
  }
  result += "}\n";
  return result;
}

int Roster::indexOfMaxPermAmongFirstKStudents(int k) const {
  int maxIndex = 0;
  for (int i = 1; i < k; i++) {
    if (students[i]->getPerm() > students[maxIndex]->getPerm()) {
      maxIndex = i;
    }
  }
  return maxIndex;
}

void Roster::sortByPermHelper(int k) {
  int im = indexOfMaxPermAmongFirstKStudents(k);
  Student *temp = students[im];
  students[im] = students[k - 1];
  students[k - 1] = temp;
}

void Roster::sortByPerm() {
  for (int k = numStudents; k > 1; k--) {
    sortByPermHelper(k);
  }
}

