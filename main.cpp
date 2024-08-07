#include <iostream>
#include <string>
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
#include "BinarySearchST.h"
#include "BST.h"
#include "RedBlackBST.h"
#include "SeparateChainingHashST.h"
#include "tests/testSort.h"
#include "tests/testPQ.h"
#include "tests/testST.h"

int main(int argc, char *argv[]) {
    std::filesystem::path dataFilePath(argv[1]);
    std::string dataFileName = dataFilePath.filename().string();
    if (dataFileName == "words3.txt") {
        // 测试排序算法
        // % algs4 words3.txt
        std::cout << "Testing selection sort" << "\n";
        std::cout << "--------------------------------" << "\n";
        testSort<Selection>(dataFilePath);
        std::cout << "--------------------------------" << "\n" << "\n";
        std::cout << "Testing insertion sort" << "\n";
        std::cout << "--------------------------------" << "\n";
        testSort<Insertion>(dataFilePath);
        std::cout << "--------------------------------" << "\n" << "\n";
        std::cout << "Testing shellsort" << "\n";
        std::cout << "--------------------------------" << "\n";
        testSort<Shell>(dataFilePath);
        std::cout << "--------------------------------" << "\n" << "\n";
        std::cout << "Testing mergesort" << "\n";
        std::cout << "--------------------------------" << "\n";
        testSort<Merge>(dataFilePath);
        std::cout << "--------------------------------" << "\n" << "\n";
        std::cout << "Testing bottom-up mergesort" << "\n";
        std::cout << "--------------------------------" << "\n";
        testSort<MergeBU>(dataFilePath);
        std::cout << "--------------------------------" << "\n" << "\n";
        std::cout << "Testing quicksort" << "\n";
        std::cout << "--------------------------------" << "\n";
        testSort<Quick>(dataFilePath);
        std::cout << "--------------------------------" << "\n" << "\n";
        std::cout << "Testing 3-way quicksort" << "\n";
        std::cout << "--------------------------------" << "\n";
        testSort<Quick3way>(dataFilePath);
        std::cout << "--------------------------------" << "\n" << "\n";
        std::cout << "Testing heapsort" << "\n";
        std::cout << "--------------------------------" << "\n";
        testSort<Heap>(dataFilePath);
        std::cout << "--------------------------------" << "\n" << "\n";
    } else if (dataFileName == "tinyPQ.txt") {
        // 测试优先队列
        // % algs4 tinyPQ.txt
        std::cout << "Testing priority queue" << "\n";
        std::cout << "--------------------------------" << "\n";
        testPQ(MaxPQ<std::string>(10), dataFilePath);
        std::cout << "--------------------------------" << "\n" << "\n";
    } else if (dataFileName == "tinyST.txt") {
        // 测试搜索算法
        // % algs4 tinyST.txt
        std::cout << "Testing sequential search symbol table" << "\n";
        testBasicST(SequentialSearchST<std::string, int>(), dataFilePath);
        std::cout << "Testing binary search symbol table" << "\n";
        testOrderedST(BinarySearchST<std::string, int>(20), dataFilePath);
        std::cout << "Testing binary search tree" << "\n";
        testOrderedST(BST<std::string, int>(), dataFilePath);
        std::cout << "Testing red-black binary search tree" << "\n";
        testOrderedST(RedBlackBST<std::string, int>(), dataFilePath);
        std::cout << "Testing separate chaining hash symbol table" << "\n";
        testBasicST(SeparateChainingHashST<std::string, int>(3), dataFilePath);
    }
    return 0;
}
