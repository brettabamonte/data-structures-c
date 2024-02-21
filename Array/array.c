#include <stdio.h>
#include <stdlib.h>

struct Array
{
    int A[10];
    int size;
    int length;
};

void display(struct Array arr)
{
    int i;
    printf("\nElements are\n");
    for (i = 0; i < arr.length; i++)
    {
        printf("%d ", arr.A[i]);
    }
}

void append(struct Array *arr, int x)
{
    // Check if length is less than size of array
    if (arr->length < arr->size)
        arr->A[arr->length++] = x;
}

void insert(struct Array *arr, int index, int x)
{
    // Check index is valid
    if (index >= 0 && index <= arr->length)
    {
        // Copy elements to new positions
        for (int i = arr->length; i > index; i--)
            arr->A[i] = arr->A[i - 1];
        arr->A[index] = x;
        arr->length++;
    }
}

int delete(struct Array *arr, int index)
{
    if (index >= 0 && index < arr->length)
    {
        int x = arr->A[index];

        for (int i = index; i < arr->length - 1; i++)
            arr->A[i] = arr->A[i + 1];
        arr->length--;

        return x;
    }

    return 0;
}

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

// Uses tranposition to improve linear search
int linearSearch(struct Array *arr, int key)
{
    for (int i = 0; i < arr->length; i++)
    {
        if (key == arr->A[i])
        {
            swap(&arr->A[i], &arr->A[i - 1]);
            return i - 1;
        }
    }

    return -1;
}

int binarySearch(struct Array arr, int key)
{
    int l, mid, h;
    l = 0;
    h = arr.length - 1;

    while (l <= h)
    {
        mid = (l + h) / 2;
        if (key == arr.A[mid])
        {
            return mid;
        }
        else if (key < arr.A[mid])
        {
            h = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    return -1;
}

void set(struct Array *arr, int index, int x)
{
    if (index < 0 || index >= arr->length)
        return;

    arr->A[index] = x;

    return;
}

int get(struct Array arr, int index)
{
    if (index < 0 || index >= arr.length)
        return -1;

    return arr.A[index];
}

int recursiveBinarySearch(int a[], int l, int h, int key)
{

    int mid;

    if (l <= h)
    {
        mid = (l + h) / 2;
        if (key == a[mid])
            return mid;
        else if (key < a[mid])
            return RBinarySearch(a, l, mid - 1, key);
        else
            return RBinarySearch(a, mid + 1, h, key);
    }

    return -1;
}

void insertSort(struct Array *arr, int x)
{

    int i = arr->length - 1;

    if (arr->length == arr->size)
        return;

    while (i >= 0 && arr->A[i] > x)
    {
        arr->A[i + 1] = arr->A[i];
        i--;
    }

    arr->A[i + 1] = x;
    arr->length++;
}

int isSorted(struct Array arr)
{
    for (int i = 0; i < arr.length - 1; i++)
    {
        if (arr.A[i] > arr.A[i + 1])
            return 0;
    }
    return 1;
}

void rearrange(struct Array *arr)
{
    // Create two pointers
    int i, j;
    i = 0;
    j = arr->length - 1;

    // Keep looping until pointers cross
    while (i < j)
    {
        // Increment/decrement pointers to find negative and positive numbers
        while (arr->A[i] < 0)
            i++;
        while (arr->A[j] >= 0)
            j--;

        // Swap values
        if (i < j)
            swap(&arr->A[i], &arr->A[j]);
    }
}

struct Array *merge(struct Array *arr1, struct Array *arr2)
{
    int i, j, k;
    i = j = k = 0;
    struct Array *arr3 = (struct Array *)malloc(sizeof(struct Array));

    // Merge arrays until we reach end of one of the copied arrays
    while (i < arr1->length && j < arr2->length)
    {
        if (arr1->A[i] < arr2->A[j])
            arr3->A[k++] = arr1->A[i++];
        else
            arr3->A[k++] = arr2->A[j++];
    }

    // Copy remaining elements
    for (; i < arr1->length; i++)
        arr3->A[k++] = arr1->A[i];
    for (; j < arr2->length; j++)
        arr3->A[k++] = arr2->A[j];

    arr3->length = arr1->length + arr2->length;
    arr3->size = arr1->size + arr2->size;

    return arr3;
}

// Union operation on two sorted sets
struct Array *unionFunc(struct Array *arr1, struct Array *arr2)
{
    int i, j, k;
    i = j = k = 0;
    struct Array *arr3 = (struct Array *)malloc(sizeof(struct Array));

    // Merge arrays until we reach end of one of the copied arrays
    while (i < arr1->length && j < arr2->length)
    {
        if (arr1->A[i] < arr2->A[j])
            arr3->A[k++] = arr1->A[i++];
        else if (arr2->A[j] < arr1->A[i])
            arr3->A[k++] = arr2->A[j++];
        else
        {
            arr3->A[k++] = arr1->A[i++];
            j++;
        }
    }

    // Copy remaining elements
    for (; i < arr1->length; i++)
        arr3->A[k++] = arr1->A[i];
    for (; j < arr2->length; j++)
        arr3->A[k++] = arr2->A[j];

    arr3->length = k;
    arr3->size = 10;

    return arr3;
}

// Intersection operation on two sorted sets
struct Array *intersection(struct Array *arr1, struct Array *arr2)
{
    int i, j, k;
    i = j = k = 0;
    struct Array *arr3 = (struct Array *)malloc(sizeof(struct Array));

    // Only copy elements in both arrays
    while (i < arr1->length && j < arr2->length)
    {
        if (arr1->A[i] < arr2->A[j])
            i++;
        else if (arr2->A[j] < arr1->A[i])
            j++;
        else if (arr1->A[i] == arr2->A[j])
        {
            arr3->A[k++] = arr1->A[i++];
            j++;
        }
    }

    arr3->length = k;
    arr3->size = 10;

    return arr3;
}

// Difference operation on two sorted sets
struct Array *difference(struct Array *arr1, struct Array *arr2)
{
    int i, j, k;
    i = j = k = 0;
    struct Array *arr3 = (struct Array *)malloc(sizeof(struct Array));

    // Only copy elements in both arrays
    while (i < arr1->length && j < arr2->length)
    {
        if (arr1->A[i] < arr2->A[j])
            arr3->A[k++] = arr1->A[i++];
        else if (arr2->A[j] < arr1->A[i])
            j++;
        else if (arr1->A[i] == arr2->A[j])
        {
            i++;
            j++;
        }
    }

    // Copy remaining elements
    for (; i < arr1->length; i++)
        arr3->A[k++] = arr1->A[i];

    arr3->length = k;
    arr3->size = 10;

    return arr3;
}

/* Finds multiple missing elements in a sorted array.
   Missing elements being numbers in sequence of natural numbers */
void findMissingElementsSorted(struct Array arr)
{
    int diff = arr.A[0] - 0;
    int i;
    // Iterate through each element
    for (i = 0; i < arr.length; i++)
    {
        // Check if diff doesn't match
        if (arr.A[i] - i != diff)
        {
            while (diff < arr.A[i] - i)
            {
                printf("%d ", i + diff);
                diff++;
            }
        }
    }

    return;
}

void findMissingElementsUnsorted(struct Array arr)
{
    int l, h;

    // Get min/max and size of arr
    for (int i = 0; i < arr.length; i++)
    {
        if (i == 0)
        {
            l = arr.A[i];
            h = arr.A[i];
        }
        else
        {
            if (arr.A[i] < l)
                l = arr.A[i];
            else if (arr.A[i] > h)
                h = arr.A[i];
        }
    }

    // Create hash table and set elements to 0
    int *hash = (int *)malloc(h * sizeof(int));
    for (int i = 0; i < h; i++)
        hash[i] = 0;

    // Set hash table values to 1 if element is present
    for (int i = 0; i < arr.length; i++)
        hash[arr.A[i]]++;
    // Print indexs of values that are set to 0
    for (int i = 1; i < h; i++)
        if (hash[i] == 0)
            printf("%d\n", i);

    return;
}

// Find pair of elements in unsorted array that their sum is = k
// Uses hashtable
void findPairWithSumKUnsorted(struct Array arr, int k)
{

    int largEle;
    // Find largest value
    for (int e = 0; e < arr.length; e++)
        if (arr.A[e] > largEle)
            largEle = arr.A[e];

    // Re-size hash table and init to 0
    int *hashTable = (int *)malloc(largEle * sizeof(int));
    for (int e = 0; e < largEle; e++)
    {
        hashTable[e] = 0;
    }

    // Scan each element
    for (int i = 0; i < arr.length - 1; i++)
    {
        // If corresponding value is in hash table. Print values
        if (hashTable[k - arr.A[i]] != 0)
            printf("%d + %d = %d\n", arr.A[i], k - arr.A[i], k);
        hashTable[arr.A[i]]++;
    }
}

int main()
{
    struct Array arr1 = {{2, 6, 10, 15, 25}, 10, 5};
    struct Array arr2 = {{3, 6, 7, 15, 20}, 10, 5};

    // Sorted
    struct Array arr3 = {{5, 6, 7, 10, 11, 12, 14}, 10, 7};
    // Unsorted
    struct Array arr4 = {{1, 2, 3, 8, 9, 12}, 10, 6};

    findPairWithSumKUnsorted(arr4, 10);

    return 0;
}
