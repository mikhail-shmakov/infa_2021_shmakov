#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Thing
{
    int weight;
    int value;

    Thing(int w, int v)
    {
        weight = w;
        value = v;
    }
};

struct Goods
{
    vector<Thing> contain;

    Goods(vector<Thing> t_cont)
    {
        contain = t_cont;
    }
};

struct BackPack
{
    int b_weight;

    BackPack(int w)
    {
        b_weight = w;
    }

    int solveMaxValue(Goods mass)
    {
        vector<int> v_contain;
        v_contain.push_back(0);
        for (int i = 1; i <= b_weight; ++i)
        {
            int b = -1;
            int t_b;
            for (int j = 0; j < mass.contain.size(); ++j)
            {
                if (mass.contain[j].weight <= i)
                {
                    t_b = v_contain[i - mass.contain[j].weight] + mass.contain[j].value;
                    b = (b > t_b) ? b : t_b;
                }
            }
            v_contain.push_back(b);
        }
        return v_contain[b_weight];
    }
};

int main()
{
    Thing a(1, 2); // weight, value
    Thing b(1, 3);
    Thing c(2, 3);
    Thing d(3, 4);
    Thing e(4, 10);
    Thing f(5, 1);

    vector<Thing> t_vec;
    t_vec.push_back(a);
    t_vec.push_back(b);
    t_vec.push_back(c);
    t_vec.push_back(d);
    t_vec.push_back(e);

    Goods apt(t_vec);

    int back_weight = 10;
    BackPack pack(back_weight);
    cout << "Goods for: " << pack.solveMaxValue(apt) << endl;
}
