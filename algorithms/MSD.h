#ifndef ALGS4_MSD_H
#define ALGS4_MSD_H


#include <string_view>

#include "Sorting.h"
#include "StringSorting.h"

class MSD : public StringSorting {
private:
    inline static int R = 256;
    static constexpr int M = 10;
    inline static std::vector<std::string> aux;

    class Insertion : public Sorting {
    private:
        static bool less(std::string_view v, std::string_view w, int d);

    public:
        static void sort(std::vector<std::string> &a, int lo, int hi, int d);
    };

    static void sort(std::vector<std::string> &a, int lo, int hi, int d);

public:
    static void sort(std::vector<std::string> &a);
};


#endif //ALGS4_MSD_H