#pragma once
#include <string>
#include <vector>

#define CFISH_USE_SHORT_NAMES
#define LUCY_USE_SHORT_NAMES

#include "Clownfish/String.h"
#include "Lucy/Analysis/EasyAnalyzer.h"
#include "Lucy/Document/Doc.h"
#include "Lucy/Index/Indexer.h"
#include "Lucy/Plan/FullTextType.h"
#include "Lucy/Plan/Schema.h"
#include "Lucy/Plan/StringType.h"

class FullTextIndexer {
 public:
  FullTextIndexer(const std::string& indexPath,
                  const std::string& source,
                  const std::vector<std::string>& extensions);
  void update();

 private:
  void handleDir(Indexer* indexer, const char* root, const char* name);

  const std::string& _indexPath;
  const std::string& _indexSource;
  const std::vector<std::string> _indexExtensions;
};
