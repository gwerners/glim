#pragma once
#include <string>
#include <vector>

// https://lucy.apache.org/docs/c/Lucy/Docs/Tutorial/BeyondSimpleTutorial.html
// https://lucy.apache.org/docs/c/Lucy/Docs/Tutorial/SimpleTutorial.html
// https://lucy.apache.org/docs/c/Clownfish.html
// https://lucy.apache.org/docs/c/Lucy/Docs/Tutorial.html
class SearchResult {
 public:
  SearchResult() = default;
  SearchResult(std::string _line,
               std::string _url,
               std::string _excerpt,
               std::string _highlighted);
  std::string line;
  std::string url;
  std::string excerpt;
  std::string highlighted;

  bool operator<(const SearchResult& other) const {
    return url.compare(other.url) < 0;
  }
};

class FullTextSearcher {
 public:
  FullTextSearcher(const std::string& path, const std::string& root);
  std::vector<SearchResult> search(const std::string& needle);

 private:
  std::string _indexPath;
  std::string _root;
};
