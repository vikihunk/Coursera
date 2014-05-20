#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_LEN 8

//#define MAX_LEN       6

void merge(int arr[], int low, int mid, int high) {
        int i = 0, j = 0, k = 0, temp[MAX_LEN];

        i = low;
        j = mid + 1;
        k = 0;
        while (i <= mid && j <= high) {
                if (arr[i] <= arr[j]) {
                        temp[k] = arr[i];
                        i++;
                } else {
                        temp[k] = arr[j];
                        j++;
                }
                k++;
        }
        while (i <= mid)
                temp[k++] = arr[i++];

        while (j <= high)
                temp[k++] = arr[j++];

        k--;
        while (k >= 0) {
                arr[low + k] = temp[k];
                k--;
        }
}

void merge_sort(int arr[], int low, int high) {
        int mid;

        if(low < high) {
                mid = (low + high)/2;
                merge_sort(arr, low, mid);
                merge_sort(arr, mid+1, high);
                merge(arr, low, mid, high);
        }
}

uint32_t merge_count_split_inv(int arr[], int low, int mid, int high) {
        int i = 0, j = 0, k = 0, temp[MAX_LEN];
        uint32_t split_count = 0;

        i = low;
        j = mid + 1;
        k = 0;
        while (i <= mid && j <= high) {
                if (arr[i] <= arr[j]) {
                        temp[k] = arr[i];
                        i++;
                } else {
                        /* this is the case where array element 
                         * on right is smaller than the element
                         * on the left -
                         * No of inv = remaining elements in 
                         * the left array
                         */
                        split_count += (mid-i+1);
                        temp[k] = arr[j];
                        j++;
                }
                k++;
        }
        /* Right array is exhausted in the previous loop
         * write all the values in the left array to the
         * temp array
         */
        while (i <= mid) {
                temp[k++] = arr[i++];
        }

        /* Left array is exhausted in the previous loop
         * write all the values in the left array to the
         * temp array
         */
        while (j <= high) {
                temp[k++] = arr[j++];
        }

        k--;
        while (k >= 0) {
                arr[low + k] = temp[k];
                k--;
        }
        //printf("split_count: %d\n", split_count);
        return split_count;
}

int count_inversions(int arr[], int low, int high) {
        int left_inv = 0, right_inv = 0, split_inv = 0;
        int mid = 0;
        int count_inv = 0;
        if(low < high) {
                mid = (low + high)/2;
                count_inv = count_inversions(arr, low, mid);
                count_inv += count_inversions(arr, mid+1, high);
                count_inv += merge_count_split_inv(arr, low, mid, high);
                return count_inv;
        }
        return 0;
}

int main() {
        int array[MAX_LEN];
        FILE *fp;
        int i = 0, j = 0;
        uint32_t total_inv = 0;
        uint32_t boot_force_count_inv = 0;

        memset(&array, 0, MAX_LEN);

        //if(NULL == (fp = fopen("IntArray.txt", "r"))) {
        if(NULL == (fp = fopen("IntegerArray.txt", "r"))) {
                printf("Unable to read the file\n");
                return -1;
        }
        while(EOF != fscanf(fp, "%d", &array[i])) {
                //printf("[%d]: %d\n", i, array[i]);
                i++;
        }
        fclose(fp);
        //brute force calculation
        /*for(i=0; i<= (MAX_LEN-1); i++) {
                for(j=i+1; j<MAX_LEN; j++) {
                        if(array[i] > array[j])
                                boot_force_count_inv++;
                }
        }
        printf("Brute force method - total inversions: %u\n", boot_force_count_inv);  */
        total_inv = count_inversions(array, 0, MAX_LEN-1);
        printf("Total inversions: %u\n", total_inv);
        /*printf("Sorted array:\n");
        merge_sort(array, 0, MAX_LEN-1);
        for(i = 0; i < MAX_LEN; i++) {
                printf("[%d]: %d\n", i, array[i]); 
        } */
        return 0;
}
