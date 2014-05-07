#include <stdio.h>
#include <string.h>

#define MAX_LEN 8

void merge(int arr[], int low, int mid, int high) {
        int i, j, k, temp[MAX_LEN];

        i = low;
        j = mid + 1;
        k = 0;
        while (i <= mid && j <= high) {
                if (arr[i] <= arr[j])
                        temp[k++] = arr[i++];
                else
                        temp[k++] = arr[j++];
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


int merge_count_split_inv(int arr[], int length) {
        return 0;
}

int count_inversions(int arr[], int length) {
        int left_inv, right_inv, split_inv;
        if(length == 1)
                return 0;
        left_inv = count_inversions(arr, length/2);
        right_inv = count_inversions((arr+length/2), length/2);
        split_inv = merge_count_split_inv(arr, length);

        return (left_inv + right_inv + split_inv);
}

int main() {
        int array[MAX_LEN];
        FILE *fp;
        int i = 0;
        int total_inv;

        memset(&array, 0, MAX_LEN);

        if(NULL == (fp = fopen("IntArray.txt", "r"))) {
                printf("Unable to read the file\n");
                return -1;
        }
        while(EOF != fscanf(fp, "%d", &array[i])) {
                printf("[%d]: %d\n", i, array[i]);
                i++;
        }
        fclose(fp);
        printf("Sorted array:\n");
        merge_sort(array, 0, MAX_LEN-1);
        for(i = 0; i < MAX_LEN; i++) {
                printf("[%d]: %d\n", i, array[i]);
        }
        total_inv = count_inversions(array, MAX_LEN);
        //printf("Total inversions: %d\n", total_inv);
        return 0;
}
