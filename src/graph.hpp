#include <algorithm>
#include <limits>
#include <optional>
#include <set>
#include <vector>

#define INF std::numeric_limits<float>().infinity()

class Graph {
public:
  using VertexId = size_t;
  enum MetricType : u_char { GasCost, DistanceKm };

  // metadata attached to an edge
  struct EdgeData {
    float distance_km;
    float gas_cost;

    float get_weight(MetricType &type) const {
      switch (type) {
      case MetricType::DistanceKm:
        return distance_km;
      case MetricType::GasCost:
        return gas_cost;
      default:
        return 0.0;
      }
    }
  };

private:
  // a representation of a planar graph
  // https://en.wikipedia.org/wiki/Adjacency_matrix
  std::vector<std::vector<std::pair<VertexId, EdgeData>>> _adjacency_matrix;

  // finds the nearest neightbour for the given vertex src which was not
  // visited yet
  std::optional<VertexId>
  find_nearest_neigbour(const std::set<VertexId> &subgraph,
                        const std::vector<float> &distances) const {
    auto min = INF;
    std::optional<VertexId> nearest;
    for (auto &vertex_id : subgraph) {
      if (distances[vertex_id] < min) {
        min = distances[vertex_id];
        nearest = vertex_id;
      }
    }
    return nearest;
  }

public:
  Graph() = default;
  ~Graph() = default;

  Graph(const std::vector<std::vector<std::pair<VertexId, EdgeData>>> &adjacency_matrix)
   : _adjacency_matrix(adjacency_matrix){}

  std::optional<std::vector<VertexId>>
  find_shortest_path(VertexId src, VertexId dest,
                     MetricType criteria) const {
    const auto vertex_nb = this->_adjacency_matrix.size();

    if (src >= vertex_nb || dest >= vertex_nb){
      throw "invalid arguments: 'src' and 'dest' are out of graph bounds";
    }

    // trivial case short-circuiting
    if (src == dest) {
      std::vector<VertexId> result{ src };
      return result;
    }

    // init distances between source node and other nodes (distances[i] =
    // distance from 'src' to 'i')
    std::vector<float> distances(vertex_nb);
    std::fill(distances.begin(), distances.end(), INF);
    distances[src] = 0;

    /* list of predecessors vertices used for computing path between src and dest vertices */
    std::vector<VertexId> predecessors(vertex_nb);

    // I do a BFS on the graph (parcours en largeur)
    std::set<VertexId> subgraph;
    for (VertexId id = 0; id < vertex_nb; id++) {
      subgraph.insert(id);
    }
    while (!subgraph.empty()) {
      const auto nearest = this->find_nearest_neigbour(subgraph, distances);

      // This means there is no path between source et destination vertices
      if (!nearest.has_value()) {
        predecessors.clear();
        break;
      }

      auto _nearest = nearest.value();

      subgraph.erase(_nearest);

      // computes new distances for all of the neighbours of source vertex
      for (const auto &[neighbour_id, edge_data] : this->_adjacency_matrix[_nearest]) {
        const auto candidate_distance =
            distances[_nearest] + edge_data.get_weight(criteria);

        if (distances[neighbour_id] > candidate_distance) {
          distances[neighbour_id] = candidate_distance;
          predecessors[neighbour_id] = _nearest;
        }
      }

      // stop walking graph once destination node is met
      if (_nearest == dest) {
        break;
      }
    }

    // when there is no possible path between source and destination vertex
    if (predecessors.empty()) {
      return {};
    }

    // reconstruct path between src and dest vertices from predecessors map
    // this can never result into an infinite loop because there is a path between the src and dest vertices
    std::vector<VertexId> shortest_path;
    auto                  v = dest;

    do {
      shortest_path.insert(shortest_path.begin(), v);
      v = predecessors[v];

    } while (v != src);
    shortest_path.insert(shortest_path.begin(), src);

    return shortest_path;
  }
};
