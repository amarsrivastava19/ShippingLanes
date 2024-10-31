#include "graph.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

// Load nodes from CSV file
std::unordered_map<std::string, Node> loadNodes(const std::string& filePath) {
    std::unordered_map<std::string, Node> nodes;
    std::ifstream file(filePath);
    std::string line, word;

    std::getline(file, line);  // Skip header
    while (std::getline(file, line)) {
        std::stringstream s(line);
        Node node;

        std::getline(s, word, ',');
        node.id = trim(word);
        std::getline(s, word, ',');
        node.latitude = std::stod(trim(word));
        std::getline(s, word, ',');
        node.longitude = std::stod(trim(word));

        nodes[node.id] = node;  // Store node by ID
    }

    return nodes;
}

std::unordered_map<std::string, Node> loadNodesFromString(const std::string& csvData) {
    std::unordered_map<std::string, Node> nodes;
    std::istringstream file(csvData);
    std::string line, word;

    std::getline(file, line);  // Skip header
    while (std::getline(file, line)) {
        std::stringstream s(line);
        Node node;

        std::getline(s, word, ',');
        node.id = word;  // Assuming trim is handled or not needed
        std::getline(s, word, ',');
        node.latitude = std::stod(word);
        std::getline(s, word, ',');
        node.longitude = std::stod(word);

        nodes[node.id] = node;  // Store node by ID
    }

    return nodes;
}


std::unordered_map<std::string, std::vector<Edge>> loadEdges(const std::string& filePath) {
    std::unordered_map<std::string, std::vector<Edge>> adjList;
    std::ifstream file(filePath);
    std::string line, word;

    std::getline(file, line);  // Skip header
    while (std::getline(file, line)) {
        std::stringstream s(line);
        Edge edge;

        // Read edge data
        std::getline(s, word, ',');
        edge.from = trim(word);
        std::getline(s, word, ',');
        edge.to = trim(word);
        std::getline(s, word, ',');
        edge.length = std::stod(trim(word));

        // Add the edge in one direction
        adjList[edge.from].push_back(edge);

        // Add the reverse edge (for bidirectional graph)
        Edge reverseEdge = { edge.to, edge.from, edge.length };
        adjList[edge.to].push_back(reverseEdge);
    }

    return adjList;
}


std::unordered_map<std::string, std::vector<Edge>> loadEdgesFromString(const std::string& csvData) {
    std::unordered_map<std::string, std::vector<Edge>> adjList;
    std::istringstream file(csvData);
    std::string line, word;

    std::getline(file, line);  // Skip header
    while (std::getline(file, line)) {
        std::stringstream s(line);
        Edge edge;

        // Read edge data
        std::getline(s, word, ',');
        edge.from = word;  // Assuming trim is handled or not needed
        std::getline(s, word, ',');
        edge.to = word;
        std::getline(s, word, ',');
        edge.length = std::stod(word);

        // Add the edge in one direction
        adjList[edge.from].push_back(edge);

        // Add the reverse edge (for bidirectional graph)
        Edge reverseEdge = { edge.to, edge.from, edge.length };
        adjList[edge.to].push_back(reverseEdge);
    }

    return adjList;
}