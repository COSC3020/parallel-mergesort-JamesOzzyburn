/*Sources
https://www.geeksforgeeks.org/multithreading-in-cpp/ //Threading
https://stackoverflow.com/questions/76398544/why-is-ref-cref-needed-for-reference-arguments-to-a-function-passed-to-stdth //Passing by reference with threads
https://www.geeksforgeeks.org/sorting-a-vector-in-c/# //Easy was to sort to check for correctness
*/


#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN //To set up the testing framework
#include "doctest.h" //Same comment as above

using namespace std;

//This function combines the smaller arrays
void merge(vector<int>& array, int left, int mid, int right)
{
    //Make some temporary arrays these are just used to combine
    vector<int> leftArray(array.begin() + left, array.begin() + mid + 1);
    vector<int> rightArray(array.begin() + mid + 1, array.begin() + right + 1);

    //Makes indexes for leftSubarray, rightSubarray and merged array
    int leftIndex = 0, rightIndex = 0;
    int mergedIndex = left;

    //Merge the two temp arrays into original. I decided to use while loops for this as using for loops got a little tricky with passing around the indexes but it doesnt really matter
    while (leftIndex < leftArray.size() && rightIndex < rightArray.size()) { //Bounds check
        if (leftArray[leftIndex] <= rightArray[rightIndex]) { //Left is smaller
            array[mergedIndex] = leftArray[leftIndex];
            leftIndex++;
        }
        else { //Right is smaller
            array[mergedIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        mergedIndex++;
    }

    //We also need these two loops to add the remaning data that wasnt swapped around
    while (leftIndex < leftArray.size()) {
        array[mergedIndex] = leftArray[leftIndex];
        leftIndex++;
        mergedIndex++;
    }
    while (rightIndex < rightArray.size()) {
        array[mergedIndex] = rightArray[rightIndex];
        rightIndex++;
        mergedIndex++;
    }
}

//This is the recursive function which performs merge sort
void parallel_merge_sort(vector<int>& array, int leftIndex, int rightIndex, int depth = 0)
{
    if (leftIndex >= rightIndex) { //If left is greater then right its already sorted se we just return
        return;
    }

    int middleIndex = (leftIndex + rightIndex) / 2; //Find the middle

    if (depth < 2) { //We only want to add another thread when it makes sense to (I set the depth to 2 as from my testing that seemed to run the fastest on my laptop with the g++ 13.2.0 compiler)
        thread leftThread(parallel_merge_sort, ref(array), leftIndex, middleIndex, depth + 1); //Create our leftThread and call. Use ref() to make a reference as to not copy the array around
        thread rightThread(parallel_merge_sort, ref(array), middleIndex + 1, rightIndex, depth + 1); //Create our rightThread and call
        leftThread.join();
        rightThread.join();
    }
    else { //When we get to a certain depth we dont want to add more threads as it doesnt really get us anything
        parallel_merge_sort(array, leftIndex, middleIndex, depth + 1);
        parallel_merge_sort(array, middleIndex + 1, rightIndex, depth + 1);
    }

    merge(array, leftIndex, middleIndex, rightIndex); //Merge up all of the results
}


//Testing
TEST_CASE("Testing merge sort with 10,000 randomized arrays with a length of length 1,000") {
    for (int i = 0; i < 10000; i++) { //Total of 10,000 tests
        vector<int> tempV1;
        vector<int> tempV2;
        for (int j = 0; j < 1000; j++) {
            int temp = rand() % 10000000;
            tempV1.push_back(temp);
            tempV2.push_back(temp);
        }
        parallel_merge_sort(tempV1, 0, tempV1.size() - 1);
        sort(tempV2.begin(), tempV2.end());
        CHECK(tempV1 == tempV2);
    }
}
