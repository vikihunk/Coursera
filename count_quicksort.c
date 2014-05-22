#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_LEN 10000

void swap(int *i, int *j) {
        if(*i == *j)
                return;
        *i = *i^*j;
        *j = *i^*j;
        *i = *i^*j;
}

void partition_around_pivot(int array[], int left, int right, int pivot) {
        int i,j;

        i = left+1;
        for (j = (left+1) ;  j <= right; j++) {
                if (array[j] < array[pivot]) {
                        swap(&array[i], &array[j]);
                        i++;
                }
        }
        swap(&array[left], &array[i-1]);
}

void quick_sort(int *, int, int);

int median(int arr[], int length) {
        int med = 0;
        //printf("%d %d %d\n", arr[0], arr[1], arr[2]);
        if(arr[0] > arr[1]) {
                med = arr[0];
                if(med > arr[2])
                        med = arr[2];
        } else {
                med = arr[1];
                if(med > arr[2])
                        med = arr[2];
        }
        //printf("returning: %d\n", med);
43         return med;
 44 }
 45 
 46 int choose_pivot(int array[], int left, int right) {
 47         //case 1: return first element
 48         //return left;
 49         //case 2: return final element
 50         //return right-1;
 51         //case 3: median of 1st, middle, right
 52         int middle = 0;
 53         int arr[3];
 54         if(((right-left)%2) == 0) {
 55                 middle = right-left-1;
 56         }
 57         arr[0] = array[left];
 58         arr[1] = array[middle];
 59         arr[2] = array[right];
 60         //printf("left:%d middle:%d right:%d\n", array[left], array[middle], array[right]);
 61         middle = median(arr, 3);
 62         return middle;
 63 }
 64 
 65 void quick_sort(int array[], int left, int right) {
 66         int pivot = 0;
 67         int length = (right-left);
 68         static int comparisons_count = 0;
 69         if(left < right) {
 70                 pivot = choose_pivot(array, left, right);
 71                 partition_around_pivot(array, left, right, pivot);
 72                 comparisons_count += (length-1);
 73                 quick_sort(array, 0, pivot);
 74                 quick_sort(array, pivot+1, length);
 75         }
 76         printf("Comparisons count:%d\n", comparisons_count);
 77 }
78 
 79 int main() {
 80         int array[MAX_LEN];
 81         FILE *fp;
 82         int i = 0, j = 0;
 83         uint32_t pivot = 0;
 84         uint32_t boot_force_count_inv = 0;
 85 
 86         memset(&array, 0, MAX_LEN);
 87 
 88         if(NULL == (fp = fopen("QuickSort.txt", "r"))) {
 89                 printf("Unable to read the file\n");
 90                 return -1;
 91         }
 92         while(EOF != fscanf(fp, "%d", &array[i])) {
 93                 //printf("[%d]: %d\n", i, array[i]);
 94                 i++;
 95         }
 96         fclose(fp);
 97         quick_sort(array, 0, MAX_LEN-1);
 98         printf("After sort:\n");
 99         for(i=0; i < MAX_LEN; i++) {
100                 //printf("[%d]: %d\n", i, array[i]);
101         }
102         return 0;
103 }
