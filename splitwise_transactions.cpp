#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <stack>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <sstream>
#include <iomanip>
using namespace std;

// class person_compare
// {
// public:
//     bool operator()(pair<string, int> p1, pair<string, int> p2)
//     {
//         return p1.second < p2.second;
//     }
// };

int32_t main()
{
    int no_of_transactions, friends;
    cin >> no_of_transactions >> friends;
    string x, y;
    int amount;
    unordered_map<string, int> net;

    while (no_of_transactions)
    {
        cin >> x >> y >> amount;
        if (!net.count(x))
            net[x] = 0;
        if (!net.count(y))
            net[y] = 0;

        net[x] -= amount;
        net[y] += amount;

        no_of_transactions--;
    }

    //Using multiset so that we can have multiple equal values in a sorted order
    multiset<pair<int, string> > m;
    for (auto p : net)
    {
        string person = p.first;
        int amount = p.second;
        if (net[person] != 0)
            m.insert(make_pair(amount, person));
    }

    int count = 0;
    while (!m.empty())
    {
        auto low = m.begin();
        auto high = prev(m.end());

        //pop out two elements from start and end as they would be the max credit and max credit
        int debit = low->first;
        string debit_person = low->second;

        int credit = high->first;
        string credit_person = high->second;

        m.erase(low);
        m.erase(high);

        int settled_amount = min(-debit, credit);
        debit += settled_amount;
        credit -= settled_amount;

        cout << debit_person << " will pay " << settled_amount << " to " << credit_person << endl;

        //The remainder of the settlement is pushed back into the multiset
        if (debit != 0)
        {
            m.insert(make_pair(debit, debit_person));
        }
        if (credit != 0)
        {
            m.insert(make_pair(credit, credit_person));
        }
        count++;
    }
    cout << "Total number of transactions to be done -> " << count << endl;
}