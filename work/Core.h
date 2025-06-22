#pragma once
#include <string>
#include "Cmd.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class CorePrivData {
 public:
  CorePrivData(){};
  bool _debug;
  std::string _index;
  std::vector<std::string> _extensions;
};
class Core {
 public:
  Core();
  void configure();
  void updateIndexes(const CommandLineArgs& cla);
  void run(int argc, char* argv[]);

 private:
  void saveJsonToFile(const json& j, const std::string& filepath);

  bool exists(const std::string&);
  std::string readFile(const std::string&);
  CorePrivData _priv;
};
