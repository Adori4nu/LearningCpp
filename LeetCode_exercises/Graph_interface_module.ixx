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
            if (!adjacency_list.find(vertex)) { // std::map .count(vertex) == 0
                adjacency_list.insert(vertex); // std::map [vertex] like an array for example
                return true;
            }
            return false;
        }

        auto addEdge(const NodeValueType& vertex1, const NodeValueType& vertex2) -> bool {
            auto vert1{adjacency_list.find(vertex1)}, vert2{adjacency_list.find(vertex2)};
            if (vert1 && vert2) {
                vert1->insert(vertex2);
                vert2->insert(vertex1);
                return true;
            }
            return false;
        }

        auto removeEdge(const NodeValueType& vertex1, const NodeValueType& vertex2) -> bool {
            auto vert1{ adjacency_list.find(vertex1) }, vert2{ adjacency_list.find(vertex2) };
            if (vert1 && vert2) {
                auto res1{ vert2->erase(vertex1) };
                auto res2{ vert1->erase(vertex2) };
                return res1 && res2;
            }
            return false;
        }

        auto removeVertex(const NodeValueType& vertex) -> bool {
            auto vert{ adjacency_list.find(vertex) };
            if (!vert) return false;

            // keys are all the connecting edges to vert from other vert we stored other vert name here
            auto keys = vert->keys();
            for(auto& key : keys) {
                if (auto vert_to_rm_edge{ adjacency_list.find(key) }) {
                    auto edge_rem_res{ vert_to_rm_edge->erase(vertex) };
                    if (!edge_rem_res) return false;
                }
            }
            return adjacency_list.erase(vertex);
        }

        friend std::ostream& operator<<(std::ostream& os, const Graph& graph) {
            os << "[ Graph ]\n";

            for (size_t i{0}; i < graph.adjacency_list.getBucketCount(); ++i) {
                auto vertex_node = graph.adjacency_list.getBucketHead(i);

                while (vertex_node)
                {
                    os << "[ Vertex: ]\n\033[1;33m[ " << vertex_node->key << " ]\033[0m : \n";

                    os << vertex_node->value << "\n";

                    vertex_node = vertex_node->next;
                }
                
            }
            return os;
        }

        size_t size() const { return adjacency_list.size(); }
    };
    #pragma endregion
}