#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

// Cannot use any kind of loops
// Can only use STL algorithms and ranges/views

Corpus tokenize(std::string& source) {
  /* TODO: Implement this method */
  // Step 1: Get the iterators to all space characters
  auto spaces = find_all(source.begin(), source.end(), ::isspace);

  // Step 2: Generate the tokens between consecutive space chars
  Corpus tokens;
  // 1st range is [0, n-1], 2nd range is [1, n]
  std::transform(spaces.begin(), --spaces.end(), ++spaces.begin(),
                 std::inserter(tokens, tokens.end()), // insert at the end
                 [&source](auto it1, auto it2) {
                   // Each token will be between 2 space iterators
                   return Token{source, it1, it2};
                 });

  // Step 3: Remove any whitespace tokens
  std::erase_if(tokens, [](Token token) { return token.content.empty(); });

  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  namespace rv = std::ranges::views;

  auto view =
      source |
      // Step 1: Skip correctly spelled words (filter away words that are in the dictionary)
      rv::filter([&dictionary](Token token) { return !dictionary.contains(token.content); }) |
      // Step 2: Transform into Misspellings with one-edit away words (levenshtein dist of 1)
      rv::transform([&dictionary](Token token) {
        auto view = dictionary | rv::filter([&token](std::string word) {
                      return levenshtein(token.content, word) == 1;
                    });
        std::set<std::string> suggestions(view.begin(), view.end());
        return Misspelling{token, suggestions};
      }) |
      // Step 3: Filter out the empty misspellings with no suggestions
      rv::filter([](Misspelling mis) { return !mis.suggestions.empty(); });

  return std::set<Misspelling>(view.begin(), view.end());
};

/* Helper methods */

#include "utils.cpp"