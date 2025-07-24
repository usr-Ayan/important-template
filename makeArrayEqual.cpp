Minimum Increment / decrement to make array elements equal

Approach:  

Sort the array of Integers in increasing order.
Now, to make all elements equal with min cost. We will have to make the elements equal to the middle element of this sorted array. So, select the middle value, Let it be K. 
Note: In case of even numbers of elements, we will have to check for the costs of both middle elements and take the minimum.
If A[i] < K, Increment the element by K – A[i].
If A[i] > K, Decrement the element by A[i] – K.
Update cost of each operation performed.


// C++ program to find minimum Increment or
// decrement to make array elements equal
#include <bits/stdc++.h>
using namespace std;

// Function to return minimum operations need
// to be make each element of array equal
int minCost(int A[], int n)
{
	// Initialize cost to 0
	int cost = 0;

	// Sort the array
	sort(A, A + n);

	// Middle element
	int K = A[n / 2];

	// Find Cost
	for (int i = 0; i < n; ++i)
		cost += abs(A[i] - K);

	// If n, is even. Take minimum of the
	// Cost obtained by considering both
	// middle elements
	if (n % 2 == 0) {
		int tempCost = 0;

		K = A[(n / 2) - 1];

		// Find cost again
		for (int i = 0; i < n; ++i)
			tempCost += abs(A[i] - K);

		// Take minimum of two cost
		cost = min(cost, tempCost);
	}

	// Return total cost
	return cost;
}

// Driver Code
int main()
{
	int A[] = { 1, 6, 7, 10 };

	int n = sizeof(A) / sizeof(A[0]);

	cout << minCost(A, n);

	return 0;
}
