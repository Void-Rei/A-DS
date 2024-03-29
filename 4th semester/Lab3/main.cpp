#include "floyd_warshall.h"
#include "customArray.h"

int main() {
    explore_text();
    allocate_matrix();
    read_text();
    print_matrix();

    cout << "Enter start city: ";
    string city_start;
    getline(cin, city_start);

    cout << "Enter end city: ";
    string city_end;
    getline(cin, city_end);

    int start_point = N_A;
    int end_point = N_A;
    start_point = _data.cities.find(city_start);
    end_point = _data.cities.find(city_end);

    if (start_point == N_A || end_point == N_A) {
        cout << "There's no such city...";
        return -1;
    }

    int cost = floyd_warshall(start_point, end_point);
    cout << "The nearest way cost is: " << cost << endl;

    for (int i = 0; i < _data.cities_count; i++)
        delete[] _data.cost_matrix[i];
    delete[] _data.cost_matrix;

    _data.cities.clear();

    return 0;
}