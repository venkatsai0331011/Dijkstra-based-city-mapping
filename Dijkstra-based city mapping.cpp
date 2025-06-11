#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <climits>
using namespace std;

typedef pair<int, int> CityDistance;

class CityGraph {
    map<string, int> cityIndexMap;
    vector<string> indexToCity;
    vector<vector<CityDistance>> edges;
    int totalCities;

public:
    CityGraph() {
        totalCities = 0;
    }

    int getCityIndex(const string& name) {
        if (cityIndexMap.count(name) == 0) {
            cityIndexMap[name] = totalCities++;
            indexToCity.push_back(name);
            edges.emplace_back();
        }
        return cityIndexMap[name];
    }

    void connectCities(const string& from, const string& to, int dist) {
        int u = getCityIndex(from);
        int v = getCityIndex(to);
        edges[u].push_back({v, dist});
        // Uncomment for undirected
        // edges[v].push_back({u, dist});
    }

    void calculateShortestPaths(const string& startCity) {
        if (!cityIndexMap.count(startCity)) {
            cout << "City not found: " << startCity << endl;
            return;
        }

        int start = cityIndexMap[startCity];
        vector<int> minDist(totalCities, INT_MAX);
        minDist[start] = 0;

        priority_queue<CityDistance, vector<CityDistance>, greater<CityDistance>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            CityDistance top = pq.top();
    		pq.pop();

    		int currDist = top.first;
    		int u = top.second;

            if (currDist > minDist[u]) continue;

            for (auto& neighbor : edges[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (minDist[u] + weight < minDist[v]) {
                    minDist[v] = minDist[u] + weight;
                    pq.push({minDist[v], v});
                }
            }
        }

        cout << "Shortest paths from " << startCity << ":\n";
        for (int i = 0; i < totalCities; ++i) {
            cout << indexToCity[i] << " : ";
            if (minDist[i] == INT_MAX)
                cout << "Not Reachable\n";
            else
                cout << minDist[i] << "\n";
        }
    }
};

int main() {
    CityGraph g;

    g.connectCities("X", "Y", 4);
    g.connectCities("X", "Z", 6);
    g.connectCities("Y", "Z", 2);
    g.connectCities("Z", "W", 1);

    string start;
    cout << "Enter starting city: ";
    cin >> start;

    g.calculateShortestPaths(start);

    return 0;
}

