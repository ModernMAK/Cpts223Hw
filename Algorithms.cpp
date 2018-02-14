#include "Algorithms.h"
int maxSubSum1(const vector<int> & a)
{
	int maxSum = 0;
	for (int i = 0; i < a.size(); ++i)
		for (int j = i; j < a.size(); ++j)
		{
			int thisSum = 0;

			for (int k = i; k <= j; ++k)
				thisSum += a[k];

			if (thisSum > maxSum)
				maxSum = thisSum;
		}

	return maxSum;
}

int maxSubSum2(const vector<int> & a)
{
	int maxSum = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		int thisSum = 0;
		for (int j = i; j < a.size(); ++j)
		{
			thisSum += a[j];
				
			if (thisSum > maxSum)
				maxSum = thisSum;
		}
	}
	return maxSum;
}

int max3(int l ,int r, int border)
{
	if (l < r)
		return (r < border) ? border : r;
	else
		return (l < border) ? border : l;
}
int maxSumRec(const vector<int> & a, int left, int right)
{
	if (left == right) // Base case
		return (a[left] > 0) ? a[left] : 0;
	
	int center = (left + right) / 2;
	int maxLeftSum = maxSumRec(a, left, center);
	int maxRightSum = maxSumRec(a, center + 1, right);
	
	int maxLeftBorderSum = 0, leftBorderSum = 0;
	for (int i = center; i >= left; --i)
	{
		leftBorderSum += a[i];
		if (leftBorderSum > maxLeftBorderSum)
			maxLeftBorderSum = leftBorderSum;
	}
	
	int maxRightBorderSum = 0, rightBorderSum = 0;
	for (int j = center + 1; j <= right; ++j)
	{
		rightBorderSum += a[j];
		if (rightBorderSum > maxRightBorderSum)
			maxRightBorderSum = rightBorderSum;
	}
	
	return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}
int maxSubSum3(const vector<int> & a)
{
	 return maxSumRec(a, 0, a.size() - 1);
}

int maxSubSum4(const vector<int> & a)
{
	int maxSum = 0, thisSum = 0;
	for (int j = 0; j < a.size(); ++j)
	{
		thisSum += a[j];
		
		if (thisSum > maxSum)
			maxSum = thisSum;
		else if (thisSum < 0)
			thisSum = 0;
	}
	
	return maxSum;
}

double timeAlgo(AlgoDelagate algo, const vector<int> & vector, int * const & maxSum)
{
	clock_t start = clock();
	*maxSum = algo(vector);
	clock_t end = clock();
	double time = (double)(end - start) / CLOCKS_PER_SEC;
	return time;
}

AlgoDelagate fetchAlgo(int j)
{
	j = (j < 0 ? -j : j);
	j %= 4;
	switch (j)
	{
	case 0:
		return &maxSubSum1;
	case 1:
		return &maxSubSum2;
	case 2:
		return &maxSubSum3;
	case 3:
		return &maxSubSum4;
	}
}
