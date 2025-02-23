module;

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

export module Graph;

import Set;
import Hash_Map;
export namespace myjunk
{
    #pragma region Graph Node based storages
    class Graph {
        
        myjunk::NodeMap<myjunk::NodeSet> adjacency_list;

    public:
        
        auto addVertex(std::string_view vertex) -> bool {
            
        }
    };
    #pragma endregion
}