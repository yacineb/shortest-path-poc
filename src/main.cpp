#include "file_source.hpp"
#include <string>

int main(int argc, char **argv) {
  // parse input arguments
  const char *fpath;
  Graph::VertexId src,dest;
  Graph::MetricType criteria;
  try
  {
      fpath = argv[1];
      src = std::stoi(argv[2]);
      dest = std::stoi(argv[3]);
      criteria = static_cast<Graph::MetricType>(std::stoi(argv[4]));
  }
  catch (...)
  {
    std::cout << "cli arguments parse failed. Usage: <json_file> <src_vertex_id> <dest_vertex_id> <metric_type>" << std::endl;
    return 1;
  }

  auto graph = data_source::parse_graph_data(fpath);
  auto path = graph->find_shortest_path(src, dest, criteria);

  if (!path.has_value()) {
    std::cout << "There is no path between the given vertices" << std::endl;
    return 1;
  }

  // print shortest path
  for(auto& vertex : path.value())
  {
    std::cout << vertex << (vertex == dest ?  "\n" : " --> ");
  }

  return 0;
}
