## Build and requirements

- cmake >= 3.0.0
- recent version of gcc or Clang.
- Current project uses C++17 and follows [C++ core guidelines]'(https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- Only one external dependency is used for Parsing JSON (https://github.com/nlohmann/json) it's embedded in the source code as a single include.

- IDE : vscode but it's optional.

**How to build**

run this shell script at the project root: `build.sh`

## How to run/Testing

> **Important**: In the formalization of the input data: if there is an Edge from 0 to 1 this does not mean that there is an edge from 1 to 0: this information must be explicitely defined in the adjacency matrix. **This lines up with realistic uses cases where routes can be in a unique direction**
> See example of graph3.json where we have bidirectional routes

Examples of graphs are in the examples/ folder.

Once build done, you can run the program as follows:

`./build/shortest_path ./examples/graph3.json 0 4 1`

output: `0 --> 3 --> 1 --> 4`

Command line arguments uage: `exePath <json_file> <src_vertex_id> <dest_vertex_id> <metric_type(1|2)>`

## What i would have done if i had more time

- Use a third party cli arguments parser
- Performance benchmarks on Huge graphs
- Data visualisation for fun and profit
