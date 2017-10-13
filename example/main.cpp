#include <vector>
#include <iostream>
#include <lidx.h>

int main(int argc, char *argv[])
{
    lidx* indexer;
    int r;
    uint64_t* result;
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
