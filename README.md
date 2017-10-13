lidx
====

Unicode compatible full text indexer based on LevelDB.

Requirements
============
- LevelDB
- ICU library

Build via GN
============================
```sh
git clone --depth 1 --single-branch -b cpp14 https://github.com/dyu/gn-build.git
git clone --depth 1 --single-branch -b master https://github.com/dyu/gn-deps.git
./gn-deps/fetch.sh
echo 'buildconfig = "//gn-build/config/BUILDCONFIG.gn"' > .gn
gn gen gn-out --args='gcc_cc="gcc" gcc_cxx="g++" symbol_level=0 is_debug=false is_clang=false is_official_build=true'
ninja -C gn-out
```

Run example
===========
```sh
mkdir -p target/data
./gn-out/example
```

How to use lidx
===============

```cpp
#include <vector>
#include <iostream>
#include <lidx.h>

int main(int argc, char *argv[])
{
    lidx * indexer;
    int r;
    uint64_t * result;
    size_t result_count;

    // Opens the index.
    indexer = lidx_new();
    lidx_open(indexer, "target/data/lidx");
    
    std::vector<std::string> names;
    names.push_back("George Washington");
    names.push_back("John Adams");
    names.push_back("Thomas Jefferson");
    names.push_back("George Michael");
    names.push_back("George Méliès");

    // Adds data to the index.
    for (size_t i = 0, len = names.size(); i < len; i++)
    {
        lidx_set(indexer, i, names[i].c_str());
    }
    
    std::cout << "\nSearching substr: as" << std::endl;
    lidx_search(indexer, "as", lidx_search_kind_substr, &result, &result_count);
    for (size_t i = 0; i < result_count; i++)
    {
        std::cout << "> " << names[result[i]] << std::endl;
    }
    free(result);

    std::cout << "\nSearching suffix: son" << std::endl;
    lidx_search(indexer, "son", lidx_search_kind_suffix, &result, &result_count);
    for (size_t i = 0; i < result_count; i++)
    {
        std::cout << "> " << names[result[i]] << std::endl;
    }
    free(result);
    
    std::cout << "\nSearching prefix: mel" << std::endl;;
    lidx_search(indexer, "mel", lidx_search_kind_prefix, &result, &result_count);
    for (size_t i = 0; i < result_count; i++)
    {
        std::cout << "> " << names[result[i]] << std::endl;
    }
    free(result);

    lidx_close(indexer);
    lidx_free(indexer);
    
    return 0;
}
```
