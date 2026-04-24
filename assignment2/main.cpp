/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Olivia Rodrigo"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::unordered_set<std::string> get_applicants(std::string filename) {
  // STUDENT TODO: Implement this function.
  std::unordered_set<std::string> names;
  std::ifstream file(filename); 
  std::string line;
  while (std::getline(file, line)) {
    names.insert(line);
  }
  return names;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::unordered_set<std::string>& students) {
  // STUDENT TODO: Implement this function.
  std::queue<const std::string*> q;

  char first = name[0];
  int i = name.find(' ');
  char last = name[i + 1];

  for (const std::string& s : students) { // IMPORTANT! Containers have CONST references to the keys/elements inside of them!!
    int i = s.find(' ');
    if (s[0] == first && s[i + 1] == last) {
      q.push(&s);
    }
  }
  return q;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  // STUDENT TODO: Implement this function.
  if (matches.empty()) {
    return "NO MATCHES FOUND.";
  }

  // Queue doesn't support random indexing (so we gotta just continuously pop)
  // Also this way of random is biased towards the front so it's not recommended (outdated)
  srand(time(nullptr)); // seeds random number based on current time since epoch
  int end = rand() % matches.size();
  for (int i = 0; i < end; i++) {
    matches.pop();
  }

  return *matches.front();
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
