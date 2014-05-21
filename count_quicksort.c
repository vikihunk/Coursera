#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_LEN 10

void swap(int *i, int *j) {
	*i = *i^*j;
	*j = *i^*j;
	*i = *i^*j;
}

void partition_around_pivot(int array[], int left, int right, int pivot) {
	int i,j;
	
	if (left == 0) {
		return;
	}
	i = left+1;
	for (j = i;  j < right; j++) {
		if (array[j] < array[pivot]) {
			swap(&array[i], &array[pivot]);
		}
		i++;
	}
	swap(&array[left], &array[i-1]);
}

int choose_pivot(int array[], int length) {
	//case 1: return first element
	return 0;
}

void quick_sort(int array[], int left, int right) {
	int pivot = 0;
	int length = (right-left);
	if (length == 1) {
		return;
	}
	pivot = choose_pivot(array, length);
	partition_around_pivot(array, left, right, pivot);
	quick_sort(array, 0, pivot);
	quick_sort(array, pivot+1, length);
}

int main() {
        int array[MAX_LEN];
        FILE *fp;
        int i = 0, j = 0;
        uint32_t pivot = 0;
        uint32_t boot_force_count_inv = 0;

        memset(&array, 0, MAX_LEN);

        if(NULL == (fp = fopen("quicksort_short.txt", "r"))) {
                printf("Unable to read the file\n");
                return -1;
        }
        while(EOF != fscanf(fp, "%d", &array[i])) {
                printf("[%d]: %d\n", i, array[i]);
                i++;
        }
        fclose(fp);
	quick_sort(array, 0, MAX_LEN-1);
        while(EOF != fscanf(fp, "%d", &array[i])) {
                printf("[%d]: %d\n", i, array[i]);
                i++;
        }
        return 0;
}
