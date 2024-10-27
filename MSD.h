#ifndef MSD_H
#define MSD_H


#include <string>
#include <vector>
#include "Sorting.h"
#include <string_view>

class MSD : public Sorting {
private:
    inline static int R = 256;
    inline static const int M = 10;
    inline static std::vector<std::string> aux;

    class Insertion : public Sorting {
    private:
        static bool less(std::string_view v, std::string_view w, int d);

    public:
        static void sort(std::vector<std::string> &a, int lo, int hi, int d);
    };

    static char charAt(const std::string &s, int d) { return d < s.length() ? s[d] : -1; }

    static void sort(std::vector<std::string> &a, int lo, int hi, int d);

public:
    static void sort(std::vector<std::string> &a);
};


#endif //MSD_H
