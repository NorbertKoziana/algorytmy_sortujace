#include <iostream>
#include <time.h>
using namespace std;

void generate_numbers(int* numbers, int size);
void print_numbers(int* numbers, int size);
void merge_sort(int* numbers, int p, int q);
void merge_arrays(int* numbers, int p, int q, int k);



int* sorted;//public variable

int main() {
	int count_numbers;
	cout << "How many numbers should I generate and sort?" << endl;
	cin >> count_numbers;
	
	int* numbers = new int[count_numbers];
	sorted = new int[count_numbers];

	generate_numbers(numbers, count_numbers);

	print_numbers(numbers, count_numbers);

	merge_sort(numbers, 0, count_numbers -1);

	print_numbers(numbers, count_numbers);
	delete[] numbers;
	delete[] sorted;
	return 0;
}


void generate_numbers(int* numbers, int size) {
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		numbers[i] = rand();
	}
}

void print_numbers(int* numbers, int size) {
	cout << "NUMBERS:" << endl;
	for (int i = 0; i < size; i++) {
		cout<<numbers[i]<<endl;
	}
	cout << "--------------" << endl;
}

void merge_sort(int* numbers, int p, int q) {
	//q - index of first item in current subarray; q - index of last item
	int size = (q - p) + 1;

	if (size == 1) {
		return;
	}
	else {//divide by half
		merge_sort(numbers, p, p +(size/2) - 1);
		merge_sort(numbers, p + (size / 2), q);

		//two parts are now sorted so we have to merge them
		merge_arrays(numbers, p, q, p + (size / 2));
	}
}


void merge_arrays(int* numbers, int p, int q, int k) {//p - beginning of array/first subarray; q - end of array; k - beggining of second subarray
	int index=p; //index of empty place in array "sorted"


	int i = p, j = k;//p - beggining of merged array; q - end of merged array
	while (index<=q) {
		if ( (j > q) || (numbers[i] <= numbers[j]) && i<k && j<q+1 ) {//(j > q) --> if second array runned out of values; (i<k && j<q+1) if i and j are in good scope
			sorted[index] = numbers[i];
			index++;
			i++;
		}
		else{
			sorted[index] = numbers[j];
			index++;
			j++;
		}
	}

	//copy data from sorted to orignal array;
	for (int i = p; i <= q; i++) {
		numbers[i]= sorted[i];
	}
}


