// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream> 
using namespace std;

void printvec(const vector<int> V) { for (auto v : V) { cout << v << "\t"; } cout << endl; }
void printvecvec(const vector<vector<int>> V) { for (auto v : V) { printvec(v); } cout << endl; }

void BuildTopeInd(int N, vector<vector<int>>& M1, vector<int>& not_M2, vector<int>& M2_v)
{
	int N1 = N - 1;
	int N2 = N1 + (N - 2)*(N - 1) / 2;
	int N3 = N2 + (N - 3)*(N - 2)*(N - 1) / 6;
	M1 = vector<vector<int>>(N3, vector<int>(N, 0));
	set<int> M2;
	int count = 0;

	for (int i = 0; i < N1; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j < i + 1) { M1[count][j] = 1; }
			else { M1[count][j] = -1; }
		}
		if (i % 2 == 1) { M2.insert(count); }
		count++;
	}
	M2.insert(count);
	for (int i1 = 0; i1 < N1; i1++)
	{
		for (int i2 = i1 + 1; i2 < N1; i2++)
		{
			for (int j = 0; j < N; j++)
			{
				if (j < i1 + 1) { M1[count][j] = 1; }
				else if (j < i2 + 1) { M1[count][j] = -1; }
				else { M1[count][j] = 1; }
			}
			count++;
		}
	}

	M2.insert(count - 1);
	for (int i1 = 0; i1 < N1; i1++)
	{
		for (int i2 = i1 + 1; i2 < N1; i2++)
		{
			for (int i3 = i2 + 1; i3 < N1; i3++)
			{
				for (int j = 0; j < N; j++)
				{
					if (j < i1 + 1) { M1[count][j] = 1; }
					else if (j < i2 + 1) { M1[count][j] = -1; }
					else if (j < i3 + 1) { M1[count][j] = 1; }
					else { M1[count][j] = -1; }
				}
				if (i1 % 2 == 1 && i2 == i1 + 1 && i3 == i2 + 1)
				{
					M2.insert(count);
				}
				count++;
			}
		}
	}

	not_M2.clear();
	M2_v.clear();
	for (int i = 0; i < N3; i++)
	{
		if (M2.find(i) == M2.end()) { not_M2.push_back(i); }
		else { M2_v.push_back(i); }
	}

}

void nchoosek(vector<vector<int>>&M, int n, int m, const vector<int>& obj, const vector<int>& append = {})
{
	int cnum = 1;
	for (int i = 0; i < m; i++) { cnum *= (n - i); cnum /= (i + 1); }
	M = vector<vector<int>>(cnum, vector<int>(m + append.size(), 0));
	std::vector<bool> bitset(n - m, 0);
	bitset.resize(n, 1);
	int count1 = 0, count2 = 0;
	do {
		for (int i = 0; i < n; i++)
		{
			if (bitset[i]) {
				M[count1][count2] = obj[i];
				count2++;
			}
		}
		for (auto a : append)
		{
			M[count1][count2] = a;
			count2++;
		}
		count1++;
		count2 = 0;
	} while (next_permutation(bitset.begin(), bitset.end()));
}

void nchoosek(vector<vector<int>>&M, int n, int m)
{
	int cnum = 1;
	for (int i = 0; i < m; i++) { cnum *= (n - i); cnum /= (i + 1); }
	M = vector<vector<int>>(cnum, vector<int>(m, 0));
	std::vector<bool> bitset(n - m, 0);
	bitset.resize(n, 1);
	int count1 = 0, count2 = 0;
	do {
		for (int i = 0; i < n; i++)
		{
			if (bitset[i]) {
				M[count1][count2] = i;
				count2++;
			}
		}
		count1++;
		count2 = 0;
	} while (next_permutation(bitset.begin(), bitset.end()));
}

/*bool checkVCdim(vector<vector<int>>& M1, vector<int> topes)
{

	return 0;
}*/

uint64_t hash_quadruple(int u, int v, int x, int y, int total)
{
	uint64_t i = u;
	i *= total;
	i += v;
	i *= total;
	i += x;
	i *= total;
	i += y;
	return i;
}

void insert_quad(int u, int v, int x, int y, int total, set<uint64_t>& forbidden)
{

	//insert all permutation
	forbidden.insert(hash_quadruple(u, v, x, y, total));
	forbidden.insert(hash_quadruple(u, v, y, x, total));
	forbidden.insert(hash_quadruple(u, y, v, x, total));
	forbidden.insert(hash_quadruple(u, y, x, v, total));
	forbidden.insert(hash_quadruple(u, x, y, v, total));
	forbidden.insert(hash_quadruple(u, x, v, y, total));

	forbidden.insert(hash_quadruple(v, u, x, y, total));
	forbidden.insert(hash_quadruple(v, u, y, x, total));
	forbidden.insert(hash_quadruple(v, y, u, x, total));
	forbidden.insert(hash_quadruple(v, y, x, u, total));
	forbidden.insert(hash_quadruple(v, x, u, y, total));
	forbidden.insert(hash_quadruple(v, x, y, u, total));

	forbidden.insert(hash_quadruple(x, u, v, y, total));
	forbidden.insert(hash_quadruple(x, u, y, v, total));
	forbidden.insert(hash_quadruple(x, y, u, v, total));
	forbidden.insert(hash_quadruple(x, y, v, u, total));
	forbidden.insert(hash_quadruple(x, v, u, y, total));
	forbidden.insert(hash_quadruple(x, v, y, u, total));

	forbidden.insert(hash_quadruple(y, u, v, x, total));
	forbidden.insert(hash_quadruple(y, u, x, v, total));
	forbidden.insert(hash_quadruple(y, x, u, v, total));
	forbidden.insert(hash_quadruple(y, x, v, u, total));
	forbidden.insert(hash_quadruple(y, v, u, x, total));
	forbidden.insert(hash_quadruple(y, v, x, u, total));
}

void ConstructForbidden(const vector<vector<int>>& M1, set<uint64_t>& forbidden)
{
	int n = M1[0].size();
	//vector<vector<int>> quadruples;
	//nchoosek(quadruples, n, 4);
	//printvecvec(quadruples);
	//vector<vector<int>> cirs(n, vector<int>(7, 0));

	vector<int> mapi(n);

	for (int i = 0; i < n; i++)
	{
		mapi[i] = i ^ 1;
	}

	//printvec(mapi);
	for (int i = 0; i < n; i++)
	{
		int ii = mapi[i];
		for (int j = 0; j < i; j++)
		{
			int ij = mapi[j];
			for (int k = 0; k < j; k++)
			{
				int ik = mapi[k];
				for (int l = 0; l < k; l++)
				{
					int il = mapi[l];
					vector<int> t1, t2, t3, t4;

					for (int loop = 0; loop < M1.size(); loop++)
					{
						if (M1[loop][ii] == -M1[loop][ij] && M1[loop][ii] == M1[loop][ik] && M1[loop][ii] == M1[loop][il])
						{
							t1.push_back(loop);
						}
						if (M1[loop][ii] == M1[loop][ij] && M1[loop][ii] == -M1[loop][ik] && M1[loop][ii] == M1[loop][il])
						{
							t2.push_back(loop);
						}
						if (M1[loop][ii] == -M1[loop][ij] && M1[loop][ii] == -M1[loop][ik] && M1[loop][ii] == M1[loop][il])
						{
							t3.push_back(loop);
						}
						if (M1[loop][ii] == -M1[loop][ij] && M1[loop][ii] == M1[loop][ik] && M1[loop][ii] == -M1[loop][il])
						{
							t4.push_back(loop);
						}
					}

					for (auto tope1 : t1)
						for (auto tope2 : t2)
							for (auto tope3 : t3)
								for (auto tope4 : t4)
								{
									insert_quad(tope1, tope2, tope3, tope4, 100, forbidden); //100 suffice, and easy for debug
									//cout << tope1 << "\t" << tope2 << "\t" << tope3 << "\t" << tope4 << "\t" << ii << "\t" << ij << "\t" << ik << "\t" << il << endl;
								}
				}
			}
		}
	}
}

int main(int argc, char** argv)
{
	const int N = 6;

	vector<vector<int>> M1;

	vector<int> not_M2, M2;
	BuildTopeInd(N, M1, not_M2, M2);

	/*for(int i=0;i<M1.size();i++)
	{cout<<i<<"\t";printvec(M1[i]);}*/

	//printvecvec(M1);
	set<uint64_t> forbidden;

	ConstructForbidden(M1, forbidden);
//	cout << forbidden.size() << endl;

	/*vector<int> search;
	bool searchnext=true;
	while (!searchnext)
	{
		//if enough print
		if (search.size() == 10)
		{
			for (auto s : search) { cout << not_M2[s] << "\t"; }
			cout << endl;
		}

		//if not enough, extend
	}*/

	vector<vector<int>> M, index;
	nchoosek(M, 20, 10, not_M2, M2);
	nchoosek(index, 10, 4);
	//printvecvec(M);
	set<int> nice_tope;
	for (int i = 0; i < M.size(); i++)
	{
		bool valid = true;
		for (int j = 0; j < index.size(); j++)
		{
			uint64_t quadhash = hash_quadruple(M[i][index[j][0]], M[i][index[j][1]], M[i][index[j][2]], M[i][index[j][3]], 100);
			if (forbidden.find(quadhash) != forbidden.end()) { valid = false; break; }
		}
		if (valid) { sort(M[i].begin(),M[i].end());printvec(M[i]);}
		// for (auto m : M[i]) { nice_tope.insert(m); } }
//		if (i % 10000 == 1) { cerr << i << "\t" << M.size() << endl; }
	}

//	for (int i = 0; i < 25; i++) { if (nice_tope.find(i) == nice_tope.end()) { printvec(M1[i]); cout<<endl; } }

	//cin >> argc;
	return 0;
}
