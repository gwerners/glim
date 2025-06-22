#include "Cmd.h"
#include <fmt/core.h>  // fmt::print, fmt::format
#include <fmt/core.h>
#include <fmt/ranges.h>
#include "Const.h"

#include "nlohmann/json.hpp"

using json = nlohmann::json;

void usage(const std::string& programName) {
  fmt::print("Usage: {} [options]\n", programName);
  fmt::print("Options:\n");
  fmt::print("  -d <dir>      Source directory\n");
  fmt::print("  -i <index>    Index storage directory (for searching)\n");
  fmt::print("  -s <string>   String to search\n");
  fmt::print("  -r <regexp>   Regular expression to filter search\n");
  fmt::print("  -c            Show help for internal json config\n");
  fmt::print(
      "  -o <string>   Write json result to this file instead of stdout\n");
  fmt::print("  -h            Show this help\n");
}

CommandLineArgs parseCommandLine(int argc,
                                 char** argv,
                                 const std::string& defaultIndex) {
  CommandLineArgs args;
  std::string programName = argv[0];
  args.index = defaultIndex;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-h") {
      args.helpRequested = true;
    } else if (arg == "-c") {
      args.helpConfig = true;
    } else if (arg == "-d" && i + 1 < argc) {
      args.directory = argv[++i];
    } else if (arg == "-i" && i + 1 < argc) {
      args.index = argv[++i];
    } else if (arg == "-s" && i + 1 < argc) {
      args.searchString = argv[++i];
    } else if (arg == "-r" && i + 1 < argc) {
      args.regexPattern = argv[++i];
    } else if (arg == "-o" && i + 1 < argc) {
      args.output = argv[++i];
    } else {
      fmt::print(stderr, "Error: Invalid or incomplete argument near '{}'\n",
                 arg);
      usage(programName);
      exit(EXIT_FAILURE);
    }
  }

  // Se nenhum argumento válido foi passado, mostra ajuda
  if (args.directory.empty() && args.index.empty() &&
      args.searchString.empty() && args.regexPattern.empty() &&
      !args.helpRequested) {
    args.helpRequested = true;
  }

  return args;
}

void print_config_description() {
  fmt::print("Configuration File Description (JSON format):\n");
  fmt::print("------------------------------------------------\n\n");

  fmt::print(
      "This configuration file can be placed in the same directory as the "
      "binary.\n"
      "If not found, this default template will be used internally.\n\n");

  fmt::print("Fields:\n");
  fmt::print("-------\n");

  fmt::print(
      "  \"debug\": boolean\n"
      "      When true, enables verbose debug output. Not required for normal "
      "operation.\n\n");

  fmt::print(
      "  \"index\": string\n"
      "      Path and filename where the index files will be stored and "
      "updated.\n"
      "      Example: \"glim.idx\" or \"/path/to/index/glim.idx\"\n\n");

  fmt::print(
      "  \"extensions\": array of strings\n"
      "      List of file extensions to be indexed by the indexer.\n"
      "      Only files ending with these extensions will be included in the "
      "index.\n"
      "      Supported example extensions include:\n"
      "        - Text/Data: .txt, .csv, .log\n"
      "        - C/C++: .c, .h, .cpp, .hpp, .cxx, .hxx\n"
      "        - Java/Kotlin/Swift: .java, .kt, .swift\n"
      "        - Python/Ruby/Perl/PHP: .py, .rb, .pl, .php\n"
      "        - JavaScript/TypeScript: .js, .ts, .jsx, .tsx\n"
      "        - Web: .html, .htm, .css, .scss, .sass\n"
      "        - Go/Rust/Dart: .go, .rs, .dart\n"
      "        - Shell Scripts: .sh, .bash, .zsh, .fish\n"
      "        - Others: .lua, .r, .m, .vbs, .xml, .json, .yaml, .yml, .toml\n"
      "        - Docs/Config: .md, .markdown, .rst, .ini, .conf, .cfg, .env\n");
  json data;
  data = json::parse(CONFIG_JSON);
  fmt::print("Example:\n");
  fmt::print("{}\n", data.dump(4));
}
