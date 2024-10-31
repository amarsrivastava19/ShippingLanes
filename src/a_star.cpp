#include "a_star.h"
#include <queue>
#include <limits>
#include <cmath>
#include "haversine.h"
#include <iostream>

// Custom comparator for priority queue
struct NodeDistance {
    std::string id;
    double fScore;

    bool operator>(const NodeDistance& other) const {
        return fScore > other.fScore;
    }
};





Route AStarSearch(
    const std::unordered_map<std::string, Node>& nodes,
    const std::unordered_map<std::string, std::vector<Edge>>& adjList,
    const Node& startNode, const Node& goalNode) {

    std::priority_queue<NodeDistance, std::vector<NodeDistance>, std::greater<NodeDistance>> openSet;
    std::unordered_map<std::string, double> gScore;
    std::unordered_map<std::string, double> fScore;
    std::unordered_map<std::string, std::string> cameFrom;

    // Initialize scores for each node
    for (const auto& nodePair : nodes) {
        gScore[nodePair.first] = std::numeric_limits<double>::infinity();
        fScore[nodePair.first] = std::numeric_limits<double>::infinity();
    }
    gScore[startNode.id] = 0;
    fScore[startNode.id] = haversine(startNode.latitude, startNode.longitude, goalNode.latitude, goalNode.longitude);

    openSet.push({ startNode.id, fScore[startNode.id] });

    while (!openSet.empty()) {
        NodeDistance current = openSet.top();
        openSet.pop();

        if (current.id == goalNode.id) {
            Route route;
            route.Distance = gScore[current.id];

            // Reconstruct path and fill Route
            std::vector<std::string> path;
            std::string temp = current.id;
            while (cameFrom.find(temp) != cameFrom.end()) {
                path.push_back(temp);
                temp = cameFrom[temp];
            }
            path.push_back(startNode.id);
            std::reverse(path.begin(), path.end());
            route.NodePath = path;

            // Add coordinates to CoordinatePath
            for (const auto& nodeId : path) {
                const auto& node = nodes.at(nodeId);
                route.CoordinatePath.emplace_back(node.latitude, node.longitude);
            }

            return route;
        }

        if (adjList.find(current.id) == adjList.end()) continue;

        // Explore neighbors
        for (const auto& edge : adjList.at(current.id)) {
            if (nodes.find(edge.to) == nodes.end()) continue;

            // Calculate distance using haversine function
            const auto& fromNode = nodes.at(current.id);
            const auto& toNode = nodes.at(edge.to);
            double edgeDistance = haversine(fromNode.latitude, fromNode.longitude, toNode.latitude, toNode.longitude);

            double tentative_gScore = gScore[current.id] + edgeDistance;

            if (tentative_gScore < gScore[edge.to]) {
                cameFrom[edge.to] = current.id;
                gScore[edge.to] = tentative_gScore;
                fScore[edge.to] = gScore[edge.to] +
                    haversine(toNode.latitude, toNode.longitude, goalNode.latitude, goalNode.longitude);

                openSet.push({ edge.to, fScore[edge.to] });
            }
        }
    }

    std::cerr << "No path found!" << std::endl;
    return Route{}; // Return empty Route if no path is found
}

//
//std::vector<std::string> AStarSearch(
//    const std::unordered_map<std::string, Node>& nodes,
//    const std::unordered_map<std::string, std::vector<Edge>>& adjList,
//    const Node& startNode, const Node& goalNode) {
//
//    std::priority_queue<NodeDistance, std::vector<NodeDistance>, std::greater<NodeDistance>> openSet;
//    std::unordered_map<std::string, double> gScore;
//    std::unordered_map<std::string, double> fScore;
//    std::unordered_map<std::string, std::string> cameFrom;
//
//    if (nodes.find(startNode.id) == nodes.end()) {
//        //std::cerr << "Start node not found!" << std::endl;
//        return {};
//    }
//    if (nodes.find(goalNode.id) == nodes.end()) {
//        //std::cerr << "Goal node not found!" << std::endl;
//        return {};
//    }
//
//    for (const auto& nodePair : nodes) {
//        gScore[nodePair.first] = std::numeric_limits<double>::infinity();
//        fScore[nodePair.first] = std::numeric_limits<double>::infinity();
//    }
//
//    gScore[startNode.id] = 0;
//    fScore[startNode.id] = haversine(startNode.latitude, startNode.longitude, goalNode.latitude, goalNode.longitude);
//    openSet.push({ startNode.id, fScore[startNode.id] });
//
//    while (!openSet.empty()) {
//        NodeDistance current = openSet.top();
//        openSet.pop();
//
//        //std::cout << "Processing node: " << current.id << std::endl;
//
//        if (current.id == goalNode.id) {
//            std::vector<std::string> path;
//            std::string temp = current.id;
//            while (cameFrom.find(temp) != cameFrom.end()) {
//                path.push_back(temp);
//                temp = cameFrom[temp];
//            }
//            path.push_back(startNode.id);
//            std::reverse(path.begin(), path.end());
//            return path;
//        }
//
//        if (adjList.find(current.id) == adjList.end()) {
//            //std::cerr << "No neighbors found for node: " << current.id << std::endl;
//            continue;
//        }
//
//        for (const auto& edge : adjList.at(current.id)) {
//            // Check if the target node exists
//            if (nodes.find(edge.to) == nodes.end()) {
//                //std::cerr << "Edge points to a non-existent node: " << edge.to << std::endl;
//                continue;
//            }
//
//            double tentative_gScore = gScore[current.id] + edge.length;
//
//            if (tentative_gScore < gScore[edge.to]) {
//                cameFrom[edge.to] = current.id;
//                gScore[edge.to] = tentative_gScore;
//                fScore[edge.to] = gScore[edge.to] +
//                    haversine(nodes.at(edge.to).latitude, nodes.at(edge.to).longitude, goalNode.latitude, goalNode.longitude);
//
//                openSet.push({ edge.to, fScore[edge.to] });
//            }
//        }
//    }
//
//    std::cerr << "No path found!" << std::endl;
//    return {};
//}
//
