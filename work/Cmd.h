#ifndef CMD_H
#define CMD_H
#include <string>
#include <vector>

struct CommandLineArgs {
  std::string directory;
  std::string index;
  std::string searchString;
  std::string regexPattern;
  std::string output;
  bool helpRequested = false;
  bool helpConfig = false;
};

void usage(const std::string& programName);
CommandLineArgs parseCommandLine(int argc,
                                 char** argv,
                                 const std::string& defaultIndex);
void print_config_description();

#endif  // CMD_H
