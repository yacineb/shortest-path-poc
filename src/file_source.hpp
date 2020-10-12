#include <iostream>
#include "json.hpp"
#include <fstream>
#include "graph.hpp"

using Json = nlohmann::json;

namespace data_source {
  auto parse_graph_data(const char *fpath){
    std::ifstream f(fpath);

    if (!f.is_open())
    {
      throw "File not Open";
    }

    Json json;
    f >> json;


    std::vector<std::vector<std::pair<Graph::VertexId, Graph::EdgeData>>> graph_data;

    for (auto& row : json) {
      std::vector<std::pair<Graph::VertexId, Graph::EdgeData>> edges;
      for(auto& edge_data : row)
      {
        Graph::EdgeData data { edge_data.at("distance_km"),  edge_data.at("gas_cost"),};

        if (data.distance_km < 0.0 || data.gas_cost < 0.0) {
          throw "Graph data error: edge weights must be positive numbers";
        }

        edges.push_back(std::pair<Graph::VertexId, Graph::EdgeData>(edge_data["vertex_id"], data ));
      }
      graph_data.push_back(edges);
    }

    return std::make_unique<Graph>(graph_data);
  }
}

