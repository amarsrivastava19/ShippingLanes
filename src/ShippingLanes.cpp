#include <iostream>
#include "graph.h"
#include "a_star.h"
#include "haversine.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "ctpl_stl.h"
#include "edges.h"
#include "nodes.h"
#include <pybind11/pybind11.h>
#include <future>

using namespace std;
namespace py = pybind11;


const Node& findClosestNode(const std::unordered_map<std::string, Node>& nodes, const double& lat, const double& lon) {
    const Node* closestNode = nullptr;
    double minDistance = std::numeric_limits<double>::infinity();

    for (const auto& pair : nodes) {
        const Node& node = pair.second;
        double distance = haversine(lat, lon, node.latitude, node.longitude);
        if (distance < minDistance) {
            minDistance = distance;
            closestNode = &node;
        }
    }
    return *closestNode;
}

void findAndPrintPath(const std::unordered_map<std::string, Node>& nodes,
    const std::unordered_map<std::string, std::vector<Edge>>& adjList,
    const double& startLat, const double& startLon,
    const double& goalLat, const double& goalLon) {

    // Find the closest nodes to the start and goal coordinates
    const Node& startNode = findClosestNode(nodes, startLat, startLon);
    const Node& goalNode = findClosestNode(nodes, goalLat, goalLon);

    // Run the A* search algorithm to find the shortest path
    //std::vector<std::string> path = AStarSearch(nodes, adjList, startNode, goalNode);

    //Print the start and end nodes
    //std::cout << "YOUR START NODE IS : " << startNode.id << std::endl;
    //std::cout << "YOUR END NODE IS : " << goalNode.id << std::endl;

     //Print the result of the pathfinding
    //if (!path.empty()) {
    //    std::cout << "Shortest path found:\n";
    //    for (const std::string& nodeId : path) {
    //        std::cout << nodeId << " ";
    //    }
    //    std::cout << std::endl;
    //}
    //else {
    //    std::cout << "No path found." << std::endl;
    //}
}



Route calculateRoute(const unordered_map<string, Node>& nodes,
                    const unordered_map<string, vector<Edge>>& adjList,
                    const double& startLat, 
                    const double& startLon, const double& goalLat, const double& goalLon) {

    Route result;
    vector<tuple<double, double>> coordinates;

    const Node& startNode = findClosestNode(nodes, startLat, startLon);
    const Node& goalNode = findClosestNode(nodes, goalLat, goalLon);

    result = AStarSearch(nodes, adjList, startNode, goalNode);

    //for (int i = 0; i < result.NodePath.size(); ++i) {
    //    string tempID = result.NodePath[i];
    //    Node tempNode = nodes.at(tempID);

    //    result.CoordinatePath.push_back(make_tuple(tempNode.latitude, tempNode.longitude));
    //
    //}

    return result;


};

vector<Route> findRoutes(const vector<vector<double>>& input) {

    vector<future<Route>> futures(input.size());
    vector<Route> result(input.size());
    unordered_map<string, Node> nodes = loadNodesFromString(nodes_hpp);
    unordered_map<string, vector<Edge>> adjList = loadEdgesFromString(edges_hpp);
    ctpl::thread_pool pool(2);

    // Collect futures in the same order as the input, storing each at the correct index
    for (int i = 0; i < input.size(); ++i) {
        double startLat = input[i][0];
        double startLon = input[i][1];
        double goalLat = input[i][2];
        double goalLon = input[i][3];

        futures[i] = pool.push([&nodes, &adjList, startLat, startLon, goalLat, goalLon](int) {
            return calculateRoute(nodes, adjList, startLat, startLon, goalLat, goalLon);
            });
    }

    // Retrieve each future in the original order
    for (int i = 0; i < futures.size(); ++i) {
        result[i] = futures[i].get();  // Assigning to the exact index in `result` ensures order
    }

    return result;
}



//int main()
//{
//
//
//
//    //vector<vector<double>> routeData = {
//    //{40.712776, -74.005974, 34.052235, -118.243683}, // New York City to Los Angeles
//    //{34.052235, -118.243683, 41.878113, -87.629799}, // Los Angeles to Chicago
//    //{41.878113, -87.629799, 29.760427, -95.369804},  // Chicago to Houston
//    //{29.760427, -95.369804, 33.448376, -112.074036}, // Houston to Phoenix
//    //{33.448376, -112.074036, 39.739236, -104.990251} // Phoenix to Denver
//    //};
//
//    //auto startTime = std::chrono::high_resolution_clock::now();
//    //
//
//    //vector<Route> tempResult = findRoutes(routeData);
//
//    //auto endTime = std::chrono::high_resolution_clock::now();
//    //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
//
//    //std::cout << "A* Search took " << duration << " milliseconds." << std::endl;
//
//    //for (int i = 0; i < tempResult[4].NodePath.size(); ++i) {
//    //
//    //    cout << tempResult[4].NodePath[i] << endl;
//    //}
//
//    //cout << "Your route distance is: " << tempResult[4].Distance * 1.06 << endl;
//
//    return 0;
//}


PYBIND11_MODULE(ShippingLanes, m) {
    m.def("findRoutes", &findRoutes, R"pbdoc(
        Calculates Routes for a 2D vector of origin and destination coordinates (lats & longs).
    )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}






//std::cout << "Loaded Nodes:\n";
//for (const auto& pair : nodes) {
//    const Node& node = pair.second;
//    std::cout << "Node ID: " << node.id
//        << ", Latitude: " << node.latitude
//        << ", Longitude: " << node.longitude << "\n";
//}


//std::cout << "Loaded Edges:\n";
//for (const auto& pair : adjList) {
//    const std::string& fromNode = pair.first;
//    const std::vector<Edge>& edges = pair.second;

//    for (const auto& edge : edges) {
//        std::cout << "Edge from Node " << edge.from
//            << " to Node " << edge.to
//            << ", Length: " << edge.length << "\n";
//    }
//}


//const Node& startNode = findClosestNode(nodes, startLat, startLon);
//const Node& goalNode = findClosestNode(nodes, goalLat, goalLon);
//std::vector<std::string> path = AStarSearch(nodes, adjList, startNode, goalNode);
//cout << "YOUR START NODE IS : " << startNode.id << endl;
//cout << "YOUR END NODE IS : " << goalNode.id << endl;
//
//if (!path.empty()) {
//    std::cout << "Shortest path found:\n";
//    for (const std::string& nodeId : path) {
//        std::cout << nodeId << " ";
//    }
//    std::cout << std::endl;
//}
//else {
//    std::cout << "No path found." << std::endl;
//}


    //// Input lat/long for start and destination
    //double startLat = 41.5868;
    //double startLon =-93.6250;
    //double goalLat = 30.2672;
    //double goalLon = -97.7431;