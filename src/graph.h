#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>


struct Node {
    std::string id;
    double latitude;
    double longitude;
};

struct Edge {
    std::string from;
    std::string to;
    double length;
};


struct Route {
    std::vector<std::string> NodePath;
    std::vector < std::tuple<double,double>> CoordinatePath;
    double Distance;
};

std::unordered_map<std::string, Node> loadNodes(const std::string& filePath);
std::unordered_map<std::string, std::vector<Edge>> loadEdgesFromString(const std::string& csvData);
std::unordered_map<std::string, Node> loadNodesFromString(const std::string& csvData);
std::unordered_map<std::string, std::vector<Edge>> loadEdges(const std::string& filePath);

#endif
