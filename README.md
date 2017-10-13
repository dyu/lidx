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

## Run example
```sh
mkdir -p target
./gn-out/example
```

How to use lidx
===============

```
lidx * indexer;
int r;
uint64_t * result;
size_t result_count;

// Opens the index.
indexer = lidx_new();
lidx_open(indexer, "index.lidx");

// Adds data to the index.
lidx_set(indexer, 0, "George Washington");
lidx_set(indexer, 1, "John Adams");
lidx_set(indexer, 2, "Thomas Jefferson");
lidx_set(indexer, 3, "George Michael");
lidx_set(indexer, 4, "George Méliès");

// Search "geor".
print("searching geor");
lidx_search(indexer, "geor", lidx_search_kind_suffix, &result, &result_count);
for(size_t i = 0 ; i < result_count ; i ++) {
  printf("found: %i\n", result[i]);
}
// returns 0, 3 and 4.
free(result);

// Search "mel".
print("searching mel");
lidx_search(indexer, "mel", lidx_search_kind_suffix, &result, &result_count);
for(size_t i = 0 ; i < result_count ; i ++) {
  printf("found: %i\n", result[i]);
}
// return 4
free(result);

lidx_close(indexer);
lidx_free(indexer);
```
