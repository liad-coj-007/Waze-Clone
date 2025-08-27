#include <unordered_map>
#include "Graph.h"
#include <iostream>
#include <fstream>
#include "CompByDist.h"
using namespace std;
#include <nlohmann/json.hpp>
#include "Dist.h"

using json = nlohmann::json;


/**
 * @brief build a graph from 
 * a file
*/
Graph buildGraph();


/**
 * @brief build the nodes of the graph
*/
Graph BuildNodes();

/**
 * @brief check if the file open suceessfully
 * else throw error
*/
json CheckFile(const string& file_name);


void PrintDist(const Dist& dist);


int main() {
    Graph graph = buildGraph();
    CompDist comp;
    size_t final_idx = graph.size() - 1;
    DistFunction distfunc = graph.AStar(graph[0],
    graph[final_idx],comp);
    cout <<"Graph size: "  << graph.size() << endl;
    PrintDist(distfunc[graph[final_idx]]);
    return 0;
}

void PrintDist(const Dist& dist){
    const string msg = "dist = ";
    cout << msg;
    if(dist.is_inf){
        cout << "infty" << endl;
        return;
    }
    cout << dist.totaldist << endl;

}

Graph buildGraph(){
    Graph graph = BuildNodes();
    const string edge_database = "../data_base/edges.geojson";
    json js_file = CheckFile(edge_database);
    const string properties = "properties";
    const string src_key = "u";
    const string target_key = "v";
    for(auto& edge : js_file["features"]){
        size_t src = edge[properties][src_key];
        size_t target = edge[properties][target_key];
        graph.AddEdge(graph[src],graph[target],0);
    }
    return graph;
}

Graph BuildNodes(){
    const string nodedatabase_name = "../data_base/nodes.geojson";
    json js_file = CheckFile(nodedatabase_name);
    string nodes_data = "features";
    size_t size = js_file[nodes_data].size();
    const string cordinates ="coordinates";
    const string geomtry = "geometry";
    Graph graph(size);
    for(auto& node : js_file[nodes_data]){
        double lat = node[geomtry][cordinates][1];
        double lon = node[geomtry][cordinates][0];
        graph.AddVertex(lat,lon);
    }
    return graph;
}

json CheckFile(const string& file_name){
    std::ifstream file(file_name);
    if(!file.is_open()){
        string msg = "couldn't find a the file: " + file_name;
        throw std::runtime_error(msg);
    }
    json js_file;
    file >> js_file;
    file.close();
    return js_file;

}


