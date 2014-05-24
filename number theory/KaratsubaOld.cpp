#include <math.h>
#include "Karatsuba.h"

vector<int> karatsuba(vector<int> &p1, vector<int> &p2) 
{
    vector<int> res;
    if (p1.size() <= 1 && p2.size() <= 1) { // N == 1
        int p1_0, p2_0;
        if (p1.empty()) 
        {
            p1_0 = 0;
        }
        else {
            p1_0 = p1[0];
        }
        if (p2.empty()) 
        {
            p2_0 = 0;
        }
        else 
        {
            p2_0 = p2[0];
        }
        res.push_back(p1_0*p2_0);
        return res;
    }

    vector<int> p1_L, p1_U, p2_L, p2_U, p1_LU, p2_LU;
    int N;
    int deg_p1 = p1.size()-1;
    int deg_p2 = p2.size()-1;

    if (deg_p1 > deg_p2) 
    {
        N = deg_p1 + 1;
        p1_L.resize(N/2);
        p1_U.resize(N-N/2);
        p2_L.resize(min(static_cast<int>(p2.size()),N/2));
        p2_U.resize(min(static_cast<int>(p2.size()-p2_L.size()),N-N/2));
    }
    else if (deg_p1 < deg_p2) 
    {
        N = deg_p2 + 1;
        p2_L.resize(N/2);
        p2_U.resize(N-N/2);
        p1_L.resize(min(static_cast<int>(p1.size()),N/2));
        p1_U.resize(min(static_cast<int>(p1.size()-p1_L.size()),N-N/2));
    }
    else // deg_p1 == deg_p2
    { 
        N = deg_p1 + 1;
        p1_L.resize(N/2);
        p2_L.resize(N/2);
        p1_U.resize(N-N/2);
        p2_U.resize(N-N/2);
    }

    for (int i = 0; i < p1.size(); ++i) 
    {
        if (i == N/2)
            break;
        p1_L[i] = p1[i];
    }

    for (int i = 0; i < p2.size(); ++i) 
    {
        if (i == N/2)
            break;        
        p2_L[i] = p2[i];
    }

    // p1_U.resize(min(static_cast<int>(p1.size()-p1_L.size()),N-N/2));
    for (int i = 0; i < p1_U.size(); ++i) 
    {
        if (i == N) {
            break;
        }
        p1_U[i] = p1[i+N/2];
    }

    // p2_U.resize(min(static_cast<int>(p2.size()-p2_L.size()),N-N/2));
    for (int i = 0; i < p2_U.size(); ++i) 
    {
        if (i == N) {
            break;
        }        
        p2_U[i] = p2[i+N/2];
    }

    for (int i = 0; i < p1_L.size(); ++i) 
    {
        p1_LU.push_back(p1_L[i]);
    }
    for (int i = 0; i < p1_U.size(); ++i) 
    {
        if (i >= p1_LU.size())
            p1_LU.push_back(p1_U[i]);
        else {
            p1_LU[i] += p1_U[i];
        }
    }
    for (int i = 0; i < p2_L.size(); ++i) 
    {
        p2_LU.push_back(p2_L[i]);
    }
    for (int i = 0; i < p2_U.size(); ++i) 
    {
        if (i >= p2_LU.size()) 
        {
            p2_LU.push_back(p2_U[i]);
        }
        else 
        {
            p2_LU[i] += p2_U[i];
        }
    }    

    vector<int> R0 = karatsuba(p1_L,p2_L);
    vector<int> R1 = karatsuba(p1_U,p2_U);
    vector<int> R01 = karatsuba(p1_LU, p2_LU);

    res.resize(deg_p1 + deg_p2 + 1,0); // degree of the new polynomial = deg(p1) + deg(p2)
    for (int i = 0; i < R0.size(); ++i) 
    {
        res[i] = R0[i];
    }

    for (int i = 0; i < R01.size(); ++i) 
    {
        int R0_i, R1_i;
        if (R0.size() <= i) 
        {
            R0_i = 0;
        }
        else 
        {
            R0_i = R0[i];
        }
        if (R1.size() <= i) 
        {
            R1_i = 0;
        }
        else 
        {
            R1_i = R1[i];
        }
        res[N/2+i] += (R01[i] - R0_i - R1_i);
    }

    for (int i = 0; i < R1.size(); ++i) 
    {

        if (R1[i] == 0)
            continue;
        if (N%2 == 0) // uneven degree
        { 
            res[N+i] += R1[i];
        }
        else // even degree
        { 
            res[N+i-1] += R1[i];
        }
    }
    return res;
}



