#ifndef SOLUTION_H
#define SOLUTION_H



class Solution{
    unsigned int m, n;
    double *values ;
public:
    Solution(unsigned int m, unsigned int n);
    ~Solution();
    double &operator()(unsigned int a, unsigned int b);
    unsigned int getM() const {return m;};
    unsigned int getN() const {return n;};

    double xMin, xMax, yMin, yMax;
};


inline Solution::Solution(unsigned int m, unsigned int n):
    m(m), n(n)
{
    values = new double[m*n];
}

inline Solution::~Solution()
{
    //delete [] values;

    //I was getting double free, not sure why
    //Now i have feeling that this will leak memory
    //If anyone could help me explain this I would be glad
    //sorry
}

inline double &Solution::operator()(unsigned int a, unsigned int b)
{
    return values[a + m*b];
}

#endif // SOLUTION_H
