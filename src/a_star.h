#ifndef A_STAR_H
#define A_STAR_H

#include "graph.h"
#include <vector>
#include <string>
#include <unordered_map>


Route AStarSearch(
    const std::unordered_map<std::string, Node>& nodes,
    const std::unordered_map<std::string, std::vector<Edge>>& adjList,
    const Node& startNode, const Node& goalNode);


//std::vector<std::string> AStarSearch(
//    const std::unordered_map<std::string, Node>& nodes,
//    const std::unordered_map<std::string, std::vector<Edge>>& adjList,
//    const Node& startNode, const Node& goalNode);

#endif