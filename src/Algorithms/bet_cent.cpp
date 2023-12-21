#include "bet_cent.h"
#include <random>

using namespace std;

map<int, int> BetweenessCentrality::getAllScores(const Graph& graph, bool showProgress, bool displayResults) {
    airport_ids_ = graph.getIDs(); 

    Dijkstras d;

    int total_paths = 0;

    ProgressBar pb;
    double numerator = 0;
    double total_size = airport_ids_.size() * airport_ids_.size();
    for (size_t id1 = 0; id1 < airport_ids_.size(); id1++) {
        for (size_t id2 = 0; id2 < airport_ids_.size(); id2++) {
            if (showProgress) {
                pb.setProgress(numerator / total_size);
                cout << pb;
            }
            if (airport_ids_[id1] != airport_ids_[id2]) {
                total_paths++;
                vector<int> shortest_path = d.getPath(graph, airport_ids_[id1], airport_ids_[id2]);
                if (shortest_path.size() > 2) {
                    for (size_t i = 1; i < shortest_path.size() - 1; i++) {
                        int current_airport = shortest_path[i];
                        if (airport_scores_.find(current_airport) != airport_scores_.end())
                            airport_scores_[current_airport]++;
                        else
                            airport_scores_[current_airport] = 1;
                    }
                }
            } else {
                if (airport_scores_.find(airport_ids_[id1]) == airport_scores_.end())
                    airport_scores_[airport_ids_[id1]] = 0;
                if (airport_scores_.find(airport_ids_[id2]) == airport_scores_.end())
                    airport_scores_[airport_ids_[id2]] = 0;
            }
            numerator++;
        }
    }

    if (showProgress) {
        pb.setProgress(1);
        cout << pb << endl;
    }

    if (displayResults) {

        cout << "Total Paths: " << total_paths << endl;

        cout << "Betweeness Scores:" << endl;

        for (auto i : airport_scores_) {
            cout << "Airport " << i.first << ": " << i.second << endl;
        }

        cout << "-------------" << endl;

    }

    return airport_scores_;
}

map<int, int> BetweenessCentrality::getProbabilisticScores(const Graph& graph, int sampleSize, bool skipNonPaths, 
    bool showProgress, bool displayResults) {

    vector<int> airport_ids_ = graph.getIDs();

    int sampled = 0;

    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, graph.size() - 1);

    ProgressBar pb;

    while (sampled < sampleSize) {
        if (showProgress) {
            pb.setProgress((double) sampled / sampleSize);
            cout << pb;
        }

        int id1 = airport_ids_[distribution(generator)];
        int id2 = airport_ids_[distribution(generator)];

        while (id1 == id2 || airport_scores_.find(id2) != airport_scores_.end())
            id2 = airport_ids_[distribution(generator)];

        Dijkstras d;
        vector<int> shortest_path = d.getPath(graph, id1, id2);
        if (shortest_path.size() == 0/* && skipNonPaths == false*/) {
            if (airport_scores_.find(id1) == airport_scores_.end()) airport_scores_[id1] = 0;
            if (airport_scores_.find(id2) == airport_scores_.end()) airport_scores_[id2] = 0;
        }
        else if (shortest_path.size() > 0) {
            for (size_t i = 1; i < shortest_path.size() - 1; i++) {
                int current_airport = shortest_path[i];
                if (airport_scores_.find(current_airport) != airport_scores_.end()) {
                    airport_scores_[current_airport]++;
                } else {
                    airport_scores_[current_airport] = 1;
                }
            }
            sampled++;
        }
    }

    if (showProgress) {
        pb.setProgress(1);
        cout << pb << endl;
    }

    if (displayResults) {

        cout << "Number Samples: " << sampled  << " Airports Added: " << airport_scores_.size() << endl;

        cout << "Betweeness Scores:" << endl;

        for (auto i : airport_scores_) {
            cout << "Airport " << i.first << ": " << i.second << endl;
        }

        cout << "-------------" << endl;

    }

    return airport_scores_;
}

set<int> BetweenessCentrality::getAirportsWithMinFrequency(int frequency) {
    set<int> score_vector;
    for (auto i : airport_scores_) {
        if (i.second >= frequency) {
            score_vector.insert(i.first);
        }
    }
    return score_vector;
}
