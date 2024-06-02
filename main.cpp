#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class Point
{
private:
    int id_point, id_cluster;
    vector<double> values;
    string name;

public:
    Point(int id_point, const vector<double>& values, const string& name = "")
            : id_point(id_point), values(values), name(name), id_cluster(-1) {}

    int getID() const { return id_point; }

    void setCluster(int id_cluster) { this->id_cluster = id_cluster; }

    int getCluster() const { return id_cluster; }

    double getValue(int index) const { return values[index]; }

    int getTotalValues() const { return values.size(); }

    void addValue(double value) { values.push_back(value); }

    const string& getName() const { return name; }
};

class Cluster
{
private:
    int id_cluster;
    vector<double> central_values;
    vector<Point> points;

public:
    Cluster(int id_cluster, const Point& point)
            : id_cluster(id_cluster), central_values(point.getTotalValues())
    {
        for (int i = 0; i < point.getTotalValues(); i++)
            central_values[i] = point.getValue(i);
        points.push_back(point);
    }

    void addPoint(const Point& point) { points.push_back(point); }

    bool removePoint(int id_point)
    {
        auto it = remove_if(points.begin(), points.end(), [id_point](const Point& p) { return p.getID() == id_point; });
        if (it != points.end()) {
            points.erase(it, points.end());
            return true;
        }
        return false;
    }

    double getCentralValue(int index) const { return central_values[index]; }

    void setCentralValue(int index, double value) { central_values[index] = value; }

    const Point& getPoint(int index) const { return points[index]; }

    int getTotalPoints() const { return points.size(); }

    int getID() const { return id_cluster; }
};

class KMeans
{
private:
    int K, total_values, total_points, max_iterations;
    vector<Cluster> clusters;

    int getIDNearestCenter(const Point& point) const
    {
        double min_dist = numeric_limits<double>::max();
        int id_cluster_center = 0;

        for (int i = 0; i < K; i++) {
            double dist = 0.0;
            for (int j = 0; j < total_values; j++) {
                dist += pow(clusters[i].getCentralValue(j) - point.getValue(j), 2.0);
            }
            dist = sqrt(dist);

            if (dist < min_dist) {
                min_dist = dist;
                id_cluster_center = i;
            }
        }

        return id_cluster_center;
    }

public:
    KMeans(int K, int total_points, int total_values, int max_iterations)
            : K(K), total_points(total_points), total_values(total_values), max_iterations(max_iterations) {}

    void run(vector<Point>& points)
    {
        if (K > total_points) return;

        vector<int> prohibited_indexes;

        for (int i = 0; i < K; i++) {
            while (true) {
                int index_point = rand() % total_points;
                if (find(prohibited_indexes.begin(), prohibited_indexes.end(), index_point) == prohibited_indexes.end()) {
                    prohibited_indexes.push_back(index_point);
                    points[index_point].setCluster(i);
                    clusters.emplace_back(i, points[index_point]);
                    break;
                }
            }
        }

        for (int iter = 1; iter <= max_iterations; iter++) {
            bool done = true;

            for (auto& point : points) {
                int id_old_cluster = point.getCluster();
                int id_nearest_center = getIDNearestCenter(point);

                if (id_old_cluster != id_nearest_center) {
                    if (id_old_cluster != -1)
                        clusters[id_old_cluster].removePoint(point.getID());

                    point.setCluster(id_nearest_center);
                    clusters[id_nearest_center].addPoint(point);
                    done = false;
                }
            }

            for (auto& cluster : clusters) {
                for (int j = 0; j < total_values; j++) {
                    int total_points_cluster = cluster.getTotalPoints();
                    double sum = 0.0;
                    if (total_points_cluster > 0) {
                        for (int p = 0; p < total_points_cluster; p++) {
                            sum += cluster.getPoint(p).getValue(j);
                        }
                        cluster.setCentralValue(j, sum / total_points_cluster);
                    }
                }
            }

            if (done) {
                cout << "Break in iteration " << iter << "\n\n";
                break;
            }

        }

//        for (const auto& cluster : clusters) {
//            cout << "Cluster " << cluster.getID() + 1 << endl;
//            for (int j = 0; j < cluster.getTotalPoints(); j++) {
//                const Point& point = cluster.getPoint(j);
//                cout << "Point " << point.getID() + 1 << ": ";
//                for (int p = 0; p < total_values; p++) {
//                    cout << point.getValue(p) << " ";
//                }
//                if (!point.getName().empty()) {
//                    cout << "- " << point.getName();
//                }
//                cout << endl;
//            }
//
//            cout << "Cluster values: ";
//            for (int j = 0; j < total_values; j++) {
//                cout << cluster.getCentralValue(j) << " ";
//            }
//            cout << "\n\n";
//        }
    }
    void printClusters() {
        for (const auto& cluster : clusters) {
            cout << "Cluster " << cluster.getID() + 1 << endl;
            for (int j = 0; j < cluster.getTotalPoints(); j++) {
                const Point& point = cluster.getPoint(j);
                cout << "Point " << point.getID() + 1 << ": ";
                for (int p = 0; p < total_values; p++) {
                    cout << point.getValue(p) << " ";
                }
                if (!point.getName().empty()) {
                    cout << "- " << point.getName();
                }
                cout << endl;
            }

            cout << "Cluster values: ";
            for (int j = 0; j < total_values; j++) {
                cout << cluster.getCentralValue(j) << " ";
            }
            cout << "\n\n";
        }
    }
};



int main()
{
    srand(time(nullptr));

    int total_points, total_values, K, max_iterations, has_name;
    cin >> total_points >> total_values >> K >> max_iterations >> has_name;

    vector<Point> points;
    for (int i = 0; i < total_points; i++) {
        vector<double> values(total_values);
        for (int j = 0; j < total_values; j++) {
            cin >> values[j];
        }
        string point_name;
        if (has_name) {
            cin >> point_name;
            points.emplace_back(i, values, point_name);
        } else {
            points.emplace_back(i, values);
        }
    }

    KMeans kmeans(K, total_points, total_values, max_iterations);
    kmeans.run(points);
    kmeans.printClusters();
    return 0;
}