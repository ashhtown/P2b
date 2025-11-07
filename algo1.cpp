
// FIRST comparable algorithm
// heapsort (MAX HEAP!) descending order usage rates and best counters in said generation (like no comparing gen 1 to gen 7)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "pokemon.h"
//#include "pokeFile.cpp"

//Sample Pokémon data to simulate input from a CSV or database
std::vector<Pokemon> generateTestData() {
    return {
        {"Pikachu", "Electric", "", 55, 90, 0.0, 0.21, 1},
        {"Charizard", "Fire", "Flying", 84, 100, 0.0, 0.76, 1},
        {"Blastoise", "Water", "", 83, 78, 0.0, 0.64, 1},
        {"Garchomp", "Dragon", "Ground", 130, 102, 0.0, 0.89, 4},
        {"Lucario", "Fighting", "Steel", 110, 90, 0.0, 0.55, 4},
        {"Greninja", "Water", "Dark", 103, 122, 0.0, 0.83, 6}
    };
}

// Filters Pokémon by generation
std::vector<Pokemon> filterByGeneration(const std::vector<Pokemon>& all, int gen) {
    std::vector<Pokemon> result;
    for (const auto& p : all) {
        if (p.generation == gen)
            result.push_back(p);
    }
    return result;
}

// QuickSort helper for partitioning based on usage rate
int partition(std::vector<Pokemon>& arr, int low, int high) {
    float pivot = arr[high].usageRate;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j].usageRate > pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Recursive QuickSort using usage rate in descending order
void quickSort(std::vector<Pokemon>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Merge function for MergeSort
void merge(std::vector<Pokemon>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Pokemon> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].usageRate >= R[j].usageRate) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Recursive MergeSort on usage rate, descending
void mergeSort(std::vector<Pokemon>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Maintains max-heap property for usage rate
void heapify(std::vector<Pokemon>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].usageRate > arr[largest].usageRate)
        largest = left;

    if (right < n && arr[right].usageRate > arr[largest].usageRate)
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// HeapSort to sort Pokémon by usage rate in descending order
void heapSort(std::vector<Pokemon>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }

    std::reverse(arr.begin(), arr.end());
}

int main() {
    std::vector<Pokemon> allPokemons = generateTestData();

    // QuickSort test
    std::vector<Pokemon> gen1_quick = filterByGeneration(allPokemons, 1);
    std::cout << "Gen 1 Pokémon BEFORE QuickSort:\n";
    for (const auto& p : gen1_quick)
        std::cout << "- " << p.name << " (Usage Rate: " << p.usageRate << ")\n";

    quickSort(gen1_quick, 0, gen1_quick.size() - 1);
    std::cout << "\nGen 1 Pokémon AFTER QuickSort:\n";
    for (const auto& p : gen1_quick)
        std::cout << "- " << p.name << " (Usage Rate: " << p.usageRate << ")\n";

    // MergeSort test
    std::vector<Pokemon> gen1_merge = filterByGeneration(allPokemons, 1);
    mergeSort(gen1_merge, 0, gen1_merge.size() - 1);
    std::cout << "\nGen 1 Pokémon AFTER MergeSort:\n";
    for (const auto& p : gen1_merge)
        std::cout << "- " << p.name << " (Usage Rate: " << p.usageRate << ")\n";

    // HeapSort test
    std::vector<Pokemon> gen1_heap = filterByGeneration(allPokemons, 1);
    heapSort(gen1_heap);
    std::cout << "\nGen 1 Pokémon AFTER HeapSort:\n";
    for (const auto& p : gen1_heap)
        std::cout << "- " << p.name << " (Usage Rate: " << p.usageRate << ")\n";

    return 0;
}
