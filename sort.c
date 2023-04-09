#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated

void heapify(int arr[], int n, int i)
{
    // Find largest among root, left child and right child
 
    // Initialize largest as root
    int max = i;
    int L = (2 * i) + 1;  // Grabs index of left child
    int R = (2 * i) + 2; // Grabs index of right child
	if (L < n && arr[L] > arr[max]){
		max = L;
	}
    if (R < n && arr[R] > arr[max]){
		 max = R;
	}
    if (max != i) {
		// Swap values
		int temp = arr[i];
		arr[i] = arr[max];
		arr[max] = temp;
        heapify(arr, n, max);
    }
}

void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
 
        heapify(arr, n, i);
 
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
 
        // Swap values
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
        heapify(arr, i, 0);
    }
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated

void merge (int *pData, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Allocate space for holding array
	int *leftSide = (int*)malloc(n1 * sizeof(int));
	int *rightSide = (int*)malloc(n2 * sizeof(int));;
	extraMemoryAllocated += n1 * sizeof(int) + n2* sizeof(int);

	for (i = 0; i < n1; i++){ // Loads data from larger array to smaller arrays
		leftSide[i] = pData[l+i];
	}
	for (j = 0; j < n2; j++){
		rightSide[j] = pData[m + 1 + j];
	}

	i = 0; j = 0; k = l; // Resets variables

	while (i < n1 && j < n2) // Sorts into merged array
    {
        if (leftSide[i] <= rightSide[j])
        {
            pData[k] = leftSide[i];
            i++;
        }
        else
        {
        	pData[k] = rightSide[j];
            j++;
        }
        k++;
    }
	while (i < n1)
	{ // Transfers remaining elements
		pData[k] = leftSide[i];
		i++;
		k++;
	}
	while (j < n2)
	{ // Transfers remaining elements
		pData[k] = rightSide[j];
		j++;
		k++;
	}
}

void mergeSort(int *pData, int l, int r)
{
	if (l < r){
		int m = (l+r) / 2; // Calculates middle index;
		mergeSort(pData, l, m);
		mergeSort(pData, m+1, r);
		merge(pData, l, m, r);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	if (dataSz-100 < 0){
		for (int i = 0; i < dataSz; i++){
			printf("%d ", pData[i]);
		}
		printf("\n");
	}
	else {
		int i, sz = dataSz - 100;
		printf("\tData:\n\t");
		for (i = 0; i<100 ; ++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n\t");
	
		for (i = sz; i < dataSz; ++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n\n");
	}
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}