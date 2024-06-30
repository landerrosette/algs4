#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <filesystem>
#include "Selection.h"
#include "Insertion.h"
#include "Shell.h"
#include "Merge.h"
#include "MergeBU.h"
#include "Quick.h"
#include "Quick3way.h"
#include "Heap.h"
#include "MaxPQ.h"
#include "SequentialSearchST.h"

template<class SortAlgorithm>
void testSort(const std::filesystem::path &dataFilePath) {
    std::ifstream dataFile(dataFilePath);
    std::vector<std::string> a;
    std::string word;
    while (dataFile >> word) a.push_back(word);
    std::cout << "Before: ";
    SortAlgorithm::show(a);
    SortAlgorithm::sort(a);
    assert(SortAlgorithm::isSorted(a));
    std::cout << "After:  ";
    SortAlgorithm::show(a);
}

void testPQ(MaxPQ<std::string> &&pq, const std::filesystem::path &dataFilePath) {
    std::ifstream dataFile(dataFilePath);
    std::string word;
    while (dataFile >> word) {
        if (word != "-") {
            pq.insert(word);
        } else if (!pq.isEmpty()) {
            std::cout << pq.delMax() << " ";
        }
    }
    std::cout << "(" << pq.size() << " left on pq)" << "\n";
}

void testST(ST<std::string, int> &&st, const std::filesystem::path &dataFilePath) {
    std::ifstream dataFile(dataFilePath);
    std::string word;
    int i = 0;
    while (dataFile >> word) {
        st.put(word, i);
        ++i;
    }

    // print keys using getKeys()
    std::cout << "Testing getKeys()\n";
    std::cout << "--------------------------------\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << st.get(s) << "\n";
    }
    std::cout << "--------------------------------\n\n";

    // remove the first few keys
    int size = st.size();
    for (int j = 0; j < size / 2; ++j) {
        st.remove(st.getKeys()[0]);
    }
    std::cout << "After removing the first " << size / 2 << " keys" << "\n";
    std::cout << "--------------------------------\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << st.get(s) << "\n";
    }
    std::cout << "--------------------------------\n\n";

    // remove all the remaining keys
    while (!st.isEmpty()) {
        std::cout << "Removing " << st.getKeys()[st.size() / 2] << "\n";
        st.remove(st.getKeys()[st.size() / 2]);
    }
    std::cout << "After removing the remaining keys\n";
    std::cout << "--------------------------------\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << st.get(s) << "\n";
    }
    std::cout << "--------------------------------\n\n";
}

int main(int argc, char *argv[]) {
    std::filesystem::path dataFilePath(argv[1]);
    std::string dataFileName = dataFilePath.filename().string();
    if (dataFileName == "words3.txt") {
        // 测试排序算法
        // % algs4 words3.txt
        std::cout << "Testing selection sort\n";
        std::cout << "--------------------------------\n";
        testSort<Selection>(dataFilePath);
        std::cout << "--------------------------------\n\n";
        std::cout << "Testing insertion sort\n";
        std::cout << "--------------------------------\n";
        testSort<Insertion>(dataFilePath);
        std::cout << "--------------------------------\n\n";
        std::cout << "Testing shellsort\n";
        std::cout << "--------------------------------\n";
        testSort<Shell>(dataFilePath);
        std::cout << "--------------------------------\n\n";
        std::cout << "Testing mergesort\n";
        std::cout << "--------------------------------\n";
        testSort<Merge>(dataFilePath);
        std::cout << "--------------------------------\n\n";
        std::cout << "Testing bottom-up mergesort\n";
        std::cout << "--------------------------------\n";
        testSort<MergeBU>(dataFilePath);
        std::cout << "--------------------------------\n\n";
        std::cout << "Testing quicksort\n";
        std::cout << "--------------------------------\n";
        testSort<Quick>(dataFilePath);
        std::cout << "--------------------------------\n\n";
        std::cout << "Testing 3-way quicksort\n";
        std::cout << "--------------------------------\n";
        testSort<Quick3way>(dataFilePath);
        std::cout << "--------------------------------\n\n";
        std::cout << "Testing heapsort\n";
        std::cout << "--------------------------------\n";
        testSort<Heap>(dataFilePath);
        std::cout << "--------------------------------\n\n";
    } else if (dataFileName == "tinyPQ.txt") {
        // 测试优先队列
        // % algs4 tinyPQ.txt
        std::cout << "Testing priority queue\n";
        std::cout << "--------------------------------\n";
        testPQ(MaxPQ<std::string>(10), dataFilePath);
        std::cout << "--------------------------------\n\n";
    } else if (dataFileName == "tinyST.txt") {
        // 测试搜索算法
        // % algs4 tinyST.txt
        std::cout << "Testing sequential search symbol table\n";
        testST(SequentialSearchST<std::string, int>(), dataFilePath);
        std::cout << "\n";
        std::cout << "Testing binary search symbol table\n";
    }
    return 0;
}
