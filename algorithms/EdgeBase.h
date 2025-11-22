#ifndef ALGS4_EDGEBASE_H
#define ALGS4_EDGEBASE_H


namespace algs4 {
    class EdgeBase {
    protected:
        int v, w;
        double weight_;

        EdgeBase(int v, int w, double weight) : v(v), w(w), weight_(weight) {}
        ~EdgeBase() = default;

    public:
        double weight() const { return weight_; }
    };
}


#endif //ALGS4_EDGEBASE_H
