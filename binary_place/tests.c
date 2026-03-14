#include <stdio.h>
#include "tests.h"
#include "b_place.h"

int tests(){
    int flag = 1;
    int arr1[] = {1, 2, 3, 3, 3, 5, 5, 7, 7, 8, 8};   // test_1
    size_t n1 = 11;

    if (flag) {
        if (bin_place(arr1, n1, -1) != 0) { flag = 0; printf("Fail: -1 -> 0\n"); }
    }
    if (flag) {
        if (bin_place(arr1, n1, 0) != 0) { flag = 0; printf("Fail: 0 -> 0\n"); }
    }
    if (flag) {
        if (bin_place(arr1, n1, 1) != 1) { flag = 0; printf("Fail: 1 -> 1\n"); }
    }
    if (flag) {
        if (bin_place(arr1, n1, 2) != 2) { flag = 0; printf("Fail: 2 -> 2\n"); }
    }
    if (flag) {
        if (bin_place(arr1, n1, 3) != 5) { flag = 0; printf("Fail: 3 -> 5\n"); }
    }
    if (flag) {
        if (bin_place(arr1, n1, 4) != 5) { flag = 0; printf("Fail: 4 -> 5\n"); }
    }
    if (flag) {
        if (bin_place(arr1, n1, 5) != 7) { flag = 0; printf("Fail: 5 -> 7\n"); }
    }
    if (flag) {
        if (bin_place(arr1, n1, 6) != 7) { flag = 0; printf("Fail: 6 -> 7\n"); }
    }
    if (flag) {
        if (bin_place(arr1, n1, 7) != 9) { flag = 0; printf("Fail: 7 -> 9\n"); }
    }
    if (flag) {
        if (bin_place(arr1, n1, 8) != 11) { flag = 0; printf("Fail: 8 -> 11\n"); }
    }
    if (flag) {
        if (bin_place(arr1, n1, 9) != 11) { flag = 0; printf("Fail: 9 -> 11\n"); }
    }

    int arr2[] = {10, 20, 30, 40};  //test_2
    size_t n2 = 4;

    if (flag) {
        if (bin_place(arr2, n2, -1) != 0) { flag = 0; printf("Fail: arr2 5 -> 0\n"); }
    }
    if (flag) {
        if (bin_place(arr2, n2, 10) != 1) { flag = 0; printf("Fail: arr2 10 -> 1\n"); }
    }
    if (flag) {
        if (bin_place(arr2, n2, 50) != 4) { flag = 0; printf("Fail: arr2 50 -> 4\n"); }
    }

    int arr3[] = {1, 2, 5, 5, 5};  //test_3
    size_t n3 = 5;

    if (flag) {
        if (bin_place(arr3, n3, 5) != 5) { flag = 0; printf("Fail: arr3 5 -> 5\n"); }
    }
    if (flag) {
        if (bin_place(arr3, n3, 6) != 5) { flag = 0; printf("Fail: arr3 6 -> 5\n"); }
    }

    if (flag) {
        printf("All tests OK\n");
        return 0;
    } else {
        printf("Tests FAILED\n");
        return 1;
    }
}