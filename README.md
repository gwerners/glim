# 🔍 Glim — CLI File Indexer & Search Engine

> A fast and efficient command-line file indexer and search engine with json output, built in C++.

**Glim** is a command-line tool that indexes directories and enables fast searches for keywords or regular expressions, with structured output (JSON by default). Ideal for developers who need to quickly search content across large projects or repositories without grep.

---

## Features

- ✅ Fast indexing of multiple directories
- ✅ Search by plain text or regular expression
- ✅ Output in JSON/XML (JSON by default)
- ✅ Configurable via JSON config file (`glim.json`)
- ✅ Customizable file extensions to index
- ✅ Debug mode support

---

## Requirements

- C++17 or newer
- Libraries used:
  - [`nlohmann/json`](https://github.com/nlohmann/json)  – JSON manipulation
  - [`fmt`](https://github.com/fmtlib/fmt)  – Formatted output

---

## Building

Clone the repository:

```bash
git clone https://github.com/seu-usuario/glim.git 
cd glim
./run.bash
```

## Usage

Creating a new search index:
```bash
./glim -d /caminho/para/dir1 -i glim.idx
```

Search word using an index
```bash
./glim -i glim.idx -e "image"
```

Search word using regular expression as filter
```bash
./glim -i glim.idx -e "image" -r "\b\d{3}\b"  
```

## Authors

- **Gabriel Wernersbach** - *Initial work* - [gwerners](https://github.com/gwerners) 

## License

This project is licensed under the MIT License – see the [LICENSE.md](LICENSE.md) file for details.*
