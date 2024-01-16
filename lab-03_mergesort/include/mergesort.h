#ifndef LAB_03_MERGESORT_MERGESORT_H
#define LAB_03_MERGESORT_MERGESORT_H

int mergesort(
        void *array,
        unsigned long long elements, unsigned long long element_size,
        int (*comparator)(const void *, const void *)
);

#endif //LAB_03_MERGESORT_MERGESORT_H
