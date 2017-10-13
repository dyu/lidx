
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

    // Adds data to the index.
    lidx_set(indexer, 0, "George Washington");
    lidx_set(indexer, 1, "John Adams");
    lidx_set(indexer, 2, "Thomas Jefferson");
    lidx_set(indexer, 3, "George Michael");
    lidx_set(indexer, 4, "George Méliès");

    // Search "geor".
    std::cout << "searching geor" << std::endl;
    lidx_search(indexer, "geor", lidx_search_kind_suffix, &result, &result_count);
    for(size_t i = 0 ; i < result_count ; i ++) {
      std::cout << "found: " << result[i] << std::endl;
    }
    // returns 0, 3 and 4.
    free(result);

    // Search "mel".
    std::cout << "searching mel" << std::endl;;
    lidx_search(indexer, "mel", lidx_search_kind_suffix, &result, &result_count);
    for(size_t i = 0 ; i < result_count ; i ++) {
       std::cout << "found: " << result[i] << std::endl;
    }
    // return 4
    free(result);

    lidx_close(indexer);
    lidx_free(indexer);
    
    return 0;
}
