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
    template <typename NodeValueType>
    class Graph {

        myjunk::NodeMap<NodeValueType, myjunk::NodeSet<NodeValueType>> adjacency_list;

    public:
        
        auto addVertex(const NodeValueType& vertex) -> bool {
            
        }
    };
    #pragma endregion
}