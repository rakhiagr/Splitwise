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

int32_t main()
{
    int no_transactions, friends;
    cin >> no_transactions >> friends;

    int x, y, amount;

    // A one dimentional array to store the net amount that each person will have to take at the end
    vector<int> net(100000, 0);
    while (no_transactions)
    {
        cin >> x >> y >> amount;
        net[x] -= amount;
        net[y] += amount;
    }

    //Using multiset so that we can have multiple equal values in a sorted order
    multiset<int> m;
    for (int i = 0; i < friends; i++)
    {
        if (net[i])
            m.insert(net[i]);
    }

    int count = 0;
    while (!m.empty())
    {
        auto low = m.begin();
        auto high = prev(m.end());

        //pop out two elements from start and end as they would be the max credit and max credit
        int debit = *low;
        int credit = *high;

        m.erase(low);
        m.erase(high);

        int settlement_amount = min(-debit, credit);
        count++;
        //Settlement
        debit += settlement_amount;
        credit -= settlement_amount;
        
        //The remainder of the settlement is pushed back into the multiset
        if(credit)
            m.insert(credit);
        if(debit)
            m.insert(debit);
    }
    cout<<"Total number of transactions required at the end : "<<count<<endl;
}