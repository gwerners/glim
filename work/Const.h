#pragma once

// clang-format off

constexpr const char* CONFIG_JSON_FILENAME = "config.json";

constexpr const char* CONFIG_JSON =
R"json({
    "debug" : false,
    "index" : "glim.idx",
    "extensions": [
      ".txt", ".csv", ".log",
      ".c", ".h", ".cpp", ".hpp", ".cxx", ".hxx",
      ".java", ".kt", ".swift",
      ".py", ".rb", ".pl", ".php",
      ".js", ".ts", ".jsx", ".tsx",
      ".html", ".htm", ".css", ".scss", ".sass",
      ".go", ".rs", ".dart",
      ".sh", ".bash", ".zsh", ".fish",
      ".lua", ".r", ".m", ".vbs",
      ".xml", ".json", ".yaml", ".yml", ".toml",
      ".md", ".markdown", ".rst",
      ".ini", ".conf", ".cfg", ".env"
    ]
})json";

// MESSAGES
constexpr const char* MSG_START                 = "starting app...\n";
constexpr const char* START_UPDATE_INDEX_MSG    = "Started index update\n";
constexpr const char* UPDATE_INDEX_MSG          = "Update index[{}] source {}\n";
constexpr const char* FINISHED_UPDATE_INDEX_MSG = "Finished index update\n";
// clang-format on
