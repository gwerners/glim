#include "Core.h"
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <sys/stat.h>
#include <fstream>
#include <list>
#include <regex>

#include "Cmd.h"
#include "Const.h"
#include "FullTextIndexer.h"
#include "FullTextSearcher.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace nlohmann {
template <>
struct adl_serializer<SearchResult> {
  static void to_json(json& j, const SearchResult& result) {
    j = json{{"line", result.line},
             {"url", result.url},
             {"excerpt", result.excerpt},
             {"highlighted", result.highlighted}};
  }

  static void from_json(const json& j, SearchResult& result) {
    j.at("line").get_to(result.line);
    j.at("url").get_to(result.url);
    j.at("excerpt").get_to(result.excerpt);
    j.at("highlighted").get_to(result.highlighted);
  }
};
}  // namespace nlohmann
std::list<SearchResult> loadResultsFromJson(const json& j) {
  std::list<SearchResult> results;

  if (!j.contains("results") || !j["results"].is_array()) {
    fmt::print(stderr, "Error: Invalid or missing 'results' array in JSON.\n");
    return results;
  }

  for (const auto& item : j["results"]) {
    SearchResult result = item.get<SearchResult>();  // agora funciona!
    results.push_back(result);
  }

  return results;
}

void Core::saveJsonToFile(const json& j, const std::string& filepath) {
  std::ofstream file(filepath);

  if (!file.is_open()) {
    fmt::print(stderr, "Error: missing file '{}'.\n", filepath);
    return;
  }
  try {
    file << j.dump(2);
    if (_priv._debug) {
      fmt::print("JSON saved '{}'\n", filepath);
    }
  } catch (const std::exception& e) {
    fmt::print(stderr, "Error while saving JSON '{}': {}\n", filepath,
               e.what());
  }

  file.close();
}
bool Core::exists(const std::string& filename) {
  struct stat buffer;
  return (stat(filename.c_str(), &buffer) == 0);
}

std::string Core::readFile(const std::string& filename) {
  std::ifstream t(filename);
  std::string ret = std::string((std::istreambuf_iterator<char>(t)),
                                std::istreambuf_iterator<char>());
  if (_priv._debug) {
    fmt::print(fg(fmt::color::blue), "{}:{} - {} contents[{}]\n", __FUNCTION__,
               __LINE__, filename, ret);
  }
  return ret;
}

Core::Core() {}

void Core::configure() {
  std::string filename(CONFIG_JSON_FILENAME);
  json data;
  if (exists(filename)) {
    data = json::parse(readFile(filename));
  } else {
    data = json::parse(CONFIG_JSON);
  }
  _priv._debug = data["debug"];
  _priv._index = data["index"];
  _priv._extensions = data["extensions"];
}

void Core::updateIndexes(const CommandLineArgs& cla) {
  if (_priv._debug) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::green),
               START_UPDATE_INDEX_MSG);
  }
  if (_priv._debug) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::green), UPDATE_INDEX_MSG,
               _priv._index, cla.directory);
  }
  FullTextIndexer indexer(_priv._index, cla.directory, _priv._extensions);
  indexer.update();

  if (_priv._debug) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::green),
               FINISHED_UPDATE_INDEX_MSG);
  }
}
void Core::run(int argc, char** argv) {
  if (_priv._debug) {
    fmt::print(fmt::emphasis::bold | fg(fmt::color::green), MSG_START);
  }
  configure();
  CommandLineArgs cla = parseCommandLine(argc, argv, _priv._index);
  if (cla.helpConfig) {
    print_config_description();
    exit(EXIT_FAILURE);
  }
  if (cla.helpRequested) {
    std::string programName = argv[0];
    usage(programName);
    exit(EXIT_FAILURE);
  }
  if (!cla.directory.empty()) {
    updateIndexes(cla);
  }
  if (!cla.index.empty() && !cla.searchString.empty()) {
    if (_priv._debug) {
      fmt::print("index[{}] query is [{}]\n", cla.index, cla.searchString);
    }
    if (cla.directory.empty()) {
      fmt::print("root directory is empty. Url will have incomplete path\n");
    }
    FullTextSearcher searcher(cla.index, cla.directory);
    auto results = searcher.search(cla.searchString);

    std::optional<std::regex> re;
    std::smatch match;
    if (!cla.regexPattern.empty()) {
      try {
        re.emplace(cla.regexPattern);
      } catch (const std::regex_error& e) {
        fmt::print("Regex inválida: {}\n", e.what());
        exit(EXIT_FAILURE);
      }
    }
    json j;
    j["results"] = json::array();
    for (auto& entry : results) {
      if (re.has_value()) {
        if (std::regex_search(entry.excerpt, match, *re)) {
          j["results"].push_back(json(entry));
        }
      } else {
        j["results"].push_back(json(entry));
      }
    }
    if (cla.output.empty()) {
      fmt::print("{}\n", j.dump(2));
    } else {
      saveJsonToFile(j, cla.output);
    }
    /* loading example
    auto result = loadResultsFromJson(j);
    for (auto& entry : result) {
      if (_priv._debug) {
      fmt::print("{} {} {}\n", entry.line, entry.url, entry.excerpt);
      }
    }*/
  }
  return;
}
