// vector::pop_back
#include <iostream>
#include <vector>

#include <cstdlib>
#include <ctime>

using namespace std;



//display vector 
void display_vector(const vector<int> &v)//const means we don't want to change the value of input
{
	for (auto x : v) std::cout << x << " ";//c++11 version, auto: We are also using the keyword auto instead of specifying the data type thread, which we can do whenever the 
		                   //compiler can unambiguously guess what the correct type should be. 
	//std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " ")); //prior to c++11 version diaplay	
}

// swap elements
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}


// Bubble Sort Function for ascending Order, stable, in place (only need 1 extra memory to hold temp value during swap), average and worst case: O(N2)(meaning N square); best case(already sorted array): O(N). 
void BubbleSort(vector <int> &num)
{
	int flag = 1;    // set flag to 1 to start first pass
	int numLength = num.size();
	for (int i = 0; (i < numLength) && flag; i++)
	{
		flag = 0;
		for (int j = 0; j < (numLength - 1 - i); j++) // Last i elements are already in place
		{
			if (num[j] > num[j+1])       // Descending order simply changes to <
			{
				swap(num[j], num[j + 1]);
				flag = 1;                // indicates that a swap occurred.
			}
		}
	}
	return;    //arrays are passed to functions by address; nothing is returned
}


// Selection Sort Function for ascending Order, unstable, in place (only need 1 extra memory to hold temp value during swap), best,average and worst: O(N2)(meaning N square).
void SelectionSort(vector <int> &num)
{
	int numLength = num.size();
	for (int i = 0; i < numLength; i++)
	{
		int min = i;
		for (int j = i+1; j < numLength; j++)
		{
			if (num[j] < num[min])       // Descending order simply changes to >
			{
				min = j;
			}			
		}
		swap(num[i], num[min]);
	}
	return;
}

// Insertion Sort Function for ascending Order, stable, in place, average and worst case: O(N2)(meaning N square); best case(already sorted array): O(N).
void InsertionSort(vector <int> &num)
{
	int numLength = num.size();
	for (int i = 0; i < numLength; i++)
	{
		for (int j = i; (j > 0) && (num[j - 1] > num[j]); j--)
		{
			//if ( num[j - 1] > num[j])       //swap a[i] with rach larger entry to its left
			{
				swap(num[j], num[j - 1]);//swap a[i] with rach larger entry to its left
			}
			//else
			//	break;
		}
	}
	return;
}


// Shell Sort Function for ascending Order, stable, in place, average and worst case: O(N power 1.5); best case(already sorted array): O(N).
void ShellSort(vector <int> &num)
{
	int numLength = num.size();
	int h = 1;
	while (h < numLength / 3) h = 3*h + 1; //1, 4, 13, 40, 121, ... 3x+1 increment sequence

	while (h >= 1) //h-sort array for decresing sequence of h, for example: 40, 13, 4, 1
	{
		for (int i = h; i < numLength; i++)
		{
			for (int j = i; (j >= h) &&(num[j-h]>num[j]); j-=h) //insertion sort with stride length h
			{
				swap(num[j], num[j-h]);				
			}
		}
		h = h / 3;
	}
	return;
}

// Merges two subarrays of num[].
// First subarray is num[l..m]
// Second subarray is num[m+1..r]
void merge(vector <int> &num, int lo, int mi, int hi)
{
	vector <int> aux = num;//temp array to facilitate merging
	int i = lo, j = mi + 1;
	for (int k = lo; k <= hi; k++)
	{
		if (i > mi) num[k] = aux[j++];
		else if (j > hi) num[k] = aux[i++];
		else if (aux[j] < aux[i]) num[k] = aux[j++];
		else num[k] = aux[i++];
	}

}

// Merge Sort Function for ascending Order, stable, O(N) space, best, average and worst case: O(N logN).
// lo is for lowest index and hi is for highest index of the sub-array of num to be sorted 
void mergeSort(vector <int> &num, int lo, int hi)
{
	if (lo < hi)
	{
		// Same as (l+r)/2, but avoids overflow for large lo and hi
		int mi = lo + (hi - lo) / 2;

		// Sort first and second halves
		mergeSort(num, lo, mi);
		mergeSort(num, mi + 1, hi);

		merge(num, lo, mi, hi);
	}
}


/* This function takes first element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(vector <int> &num, int lo, int hi)
{
	int pivot = num[lo];    // pivot
	int i = lo, j = hi + 1;
	while (true)
	{
		while (num[++i] < pivot) if (i == hi)break;//find item on left to swap
		while (num[--j] > pivot) if (j == lo)break; //find item on right to swap
		if (i >= j)break;
		swap(num[i], num[j]);
	}
	swap(num[lo], num[j]);
	return j;
}

// Quick Sort Function for ascending Order, unstable, in-place, best and average case:  O(N logN); worst case: O(N2).
// lo is for lowest index and hi is for highest index of the sub-array of num to be sorted 
void quickSort(vector <int> &num, int lo, int hi)
{
	if (hi > lo)
	{
		/* pi is partitioning index, num[pi] is now at right place */
		int pi = partition(num, lo, hi);
		//printf("to sort low=%d, pi-1=%d \n", lo, pi - 1);
		//printf("to sort pi+1=%d, hign=%d \n", pi + 1, hi);
		// sort elements of each half recursively 
		quickSort(num, lo, pi - 1);
		quickSort(num, pi + 1, hi);
	}
}

//Heap Sort facility function
void sink(vector <int> &num, int k, int N)
{
	while ((2 * k + 1) <= N)//left = 2 * k + 1 child exisits
	{
		int j = 2 * k + 1; // left = 2 * k + 1
		if ((j < N) && (num[j] < num[j + 1])) j++; //This step is to find larger child. Note: j<N meaning (j+1) <=N, so (j+1) right child is in array. 
		if (num[k] >= num[j]) break;
		swap(num[k], num[j]);
		k = j; //sink down to child
	}
}

// Heap Sort Function for ascending Order, unstable, in-place, worst and average case:  O(N logN); best case: O(N).
void heapSort(vector <int> &num)
{
	int N = num.size();
	for (int k = (N - 1) / 2; k >= 0; k--)//bottom up build max heap	
		sink(num, k, N);	

	// One by one extract an element from heap
	int i = N - 1;
	while (i > 0)
	{
		// Move current root to end
		swap(num[0], num[i]);
		// call max heapify on the reduced heap
		sink(num, 0, --i);
	}
}

int main(int argc, char *argv[])
{
	vector<int> myvector;
	srand((unsigned)time(0));

	for (int i = 0; i < 20; i++)
	{
		myvector.push_back(rand());
	}
	display_vector(myvector);
	cout << endl;

	//BubbleSort(myvector);
	//SelectionSort(myvector);
	//InsertionSort(myvector);
	//ShellSort(myvector);
	//mergeSort(myvector, 0, myvector.size() - 1);
	//quickSort(myvector, 0, myvector.size() - 1);
	heapSort(myvector);


	display_vector(myvector);
	cout << endl;

	getchar();
	return 0;
}
