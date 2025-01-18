#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

double multiplication(double x1, double y1, double x2, double y2, double x3, double y3) {
    return (x2 - x1) * (y3 - y1) - (x3 - x2) * (y2 - y1);
}

int are_you_convex(int count_of_peaks, ...) {
    if (count_of_peaks < 3) {
        return -1;
    }
    //array of X
    double* xs = (double*)malloc(count_of_peaks * sizeof(double));
    if (xs == NULL) {
        return 2;
    }
    //array of Y
    double* ys = (double*)malloc(count_of_peaks * sizeof(double));
    if (ys == NULL) {
        free(xs);
        return 2;
    }
    //array of multiplications
    double* multiplications = (double*)malloc(count_of_peaks * sizeof(double));
    if (multiplications == NULL) {
        free(xs);
        free(ys);
        return 2;
    }

    va_list coordinates_list;
    va_start(coordinates_list, count_of_peaks);

    //write coordinates in the array
    for (int i = 0; i < count_of_peaks; i++) {
        xs[i] = va_arg(coordinates_list, double);
        ys[i] = va_arg(coordinates_list, double);
    }

    for (int i = 0; i < count_of_peaks; i++) {
        int j = (i + 1) % count_of_peaks;
        int k = (i + 2) % count_of_peaks;
        multiplications[i] = multiplication(xs[i], ys[i], xs[j], ys[j], xs[k], ys[k]);
    }

    int all_positive = 1;
    int all_negative = 1;
    for (int i = 0; i < count_of_peaks; ++i) {
        if (multiplications[i] <= 0) {
            all_positive = 0;
        }
        if (multiplications[i] >= 0) {
            all_negative = 0;
        }
    }

    free(xs);
    free(ys);
    free(multiplications);
    va_end(coordinates_list);

    if (all_positive || all_negative) {
        return 0;
    }
    else {
        return 5;
    }
}

int main() {
    switch (are_you_convex(5, 0.0, 0.0, 1.0, 0.0, 1.5, 1.0, 0.5, 1.5, 0.0, 1.0)) {
    case 0:
        printf("The polygon is convex.\n");
        break;
    case -1:
        printf("Not enough peaks.\n");
        break;
    case 2:
        printf("Error with memory.\n");
        break;
    case 5:
        printf("The polygon is not convex.\n");
        break;
    default:
        printf("Unknown error.\n");
        break;
    }

    return 0;
}
