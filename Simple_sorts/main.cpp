#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>
#include "profile.h"

using namespace std;

template<class Iterator>
void fill_random(Iterator first, Iterator last) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution distribution;
    for(auto it = first; it != last; it++) *it = distribution(generator);
}

template<class Iterator>
void fill_asc(Iterator first, Iterator last) {
    iota(first, last, 1);
}

template<class Iterator>
void fill_des(Iterator first, Iterator last) {
    iota(first, last, 1);
    reverse(first, last);
}

template<class Iterator>
void bubble_sort(Iterator begin, Iterator end) {
    unsigned long long comps = 0, swaps = 0;
    for(auto first = begin; first != prev(end); first++) {
        for (auto second = next(first); second != end; second++) {
            comps++;
            if (*second < *first) {
                swap(*first, *second); swaps++;
            }
        }
    }
    clog << "Range: " << distance(begin, end) << ", Comps: " << comps << ", Swaps: " << swaps << ", Sum: " << comps + swaps << endl;
}

template<class Iterator>
void insert_sort(Iterator begin, Iterator end) {
    unsigned long long comps = 0, swaps = 0;
    for (auto first = begin + 1; first != end; ++first) {
        comps++;
        for (auto second = first; second != begin && *second < *prev(second); --second){
            swap(*prev(second), *second); swaps++; comps++;
        }
    }

    clog << "Range: " << distance(begin, end) << ", Comps: " << comps << ", Swaps: " << swaps << ", Sum: " << comps + swaps << endl;
}

int main() {
    {
        clog << "<---- Bubble sort ---->" << endl;
        //Random
        vector<int> data_100(100); fill_random(data_100.begin(), data_100.end());
        vector<int> data_1000(1'000); fill_random(data_1000.begin(), data_1000.end());
        vector<int> data_10000(10'000); fill_random(data_10000.begin(), data_10000.end());
        vector<int> data_100000(100'000); fill_random(data_100000.begin(), data_100000.end());
        { LOG_DURATION("100 elements")
            bubble_sort(data_100.begin(), data_100.end());
        }
        { LOG_DURATION("1'000 elements")
            bubble_sort(data_1000.begin(), data_1000.end());
        }
        { LOG_DURATION("10'000 elements")
            bubble_sort(data_10000.begin(), data_10000.end());
        }
        { LOG_DURATION("100'000 elements")
            bubble_sort(data_100000.begin(), data_100000.end());
        }

        //Ascending
        vector<int> asc_data_100(100); fill_asc(asc_data_100.begin(), asc_data_100.end());
        vector<int> asc_data_1000(1'000); fill_asc(asc_data_1000.begin(), asc_data_1000.end());
        vector<int> asc_data_10000(10'000); fill_asc(asc_data_10000.begin(), asc_data_10000.end());
        vector<int> asc_data_100000(100'000); fill_asc(asc_data_100000.begin(), asc_data_100000.end());
        { LOG_DURATION("Asc 100 elements")
            bubble_sort(asc_data_100.begin(), asc_data_100.end());
        }
        { LOG_DURATION("Asc 1'000 elements")
            bubble_sort(asc_data_1000.begin(), asc_data_1000.end());
        }
        { LOG_DURATION("Asc 10'000 elements")
            bubble_sort(asc_data_10000.begin(), asc_data_10000.end());
        }
        { LOG_DURATION("Asc 100'000 elements")
            bubble_sort(asc_data_100000.begin(), asc_data_100000.end());
        }

        //Descending
        vector<int> des_data_100(100); fill_des(des_data_100.begin(), des_data_100.end());
        vector<int> des_data_1000(1'000); fill_des(des_data_1000.begin(), des_data_1000.end());
        vector<int> des_data_10000(10'000); fill_des(des_data_10000.begin(), des_data_10000.end());
        vector<int> des_data_100000(100'000); fill_des(des_data_100000.begin(), des_data_100000.end());
        { LOG_DURATION("Des 100 elements")
            bubble_sort(des_data_100.begin(), des_data_100.end());
        }
        { LOG_DURATION("Des 1'000 elements")
            bubble_sort(des_data_1000.begin(), des_data_1000.end());
        }
        { LOG_DURATION("Des 10'000 elements")
            bubble_sort(des_data_10000.begin(), des_data_10000.end());
        }
        { LOG_DURATION("Des 100'000 elements")
            bubble_sort(des_data_100000.begin(), des_data_100000.end());
        }
    }
    {
        clog << "<---- Insertion sort ---->" << endl;
        //Random
        vector<int> data_100(100); fill_random(data_100.begin(), data_100.end());
        vector<int> data_1000(1'000); fill_random(data_1000.begin(), data_1000.end());
        vector<int> data_10000(10'000); fill_random(data_10000.begin(), data_10000.end());
        vector<int> data_100000(100'000); fill_random(data_100000.begin(), data_100000.end());
        { LOG_DURATION("100 elements")
            insert_sort(data_100.begin(), data_100.end());
        }
        { LOG_DURATION("1'000 elements")
            insert_sort(data_1000.begin(), data_1000.end());
        }
        { LOG_DURATION("10'000 elements")
            insert_sort(data_10000.begin(), data_10000.end());
        }
        { LOG_DURATION("100'000 elements")
            insert_sort(data_100000.begin(), data_100000.end());
        }

        //Ascending
        vector<int> asc_data_100(100); fill_asc(asc_data_100.begin(), asc_data_100.end());
        vector<int> asc_data_1000(1'000); fill_asc(asc_data_1000.begin(), asc_data_1000.end());
        vector<int> asc_data_10000(10'000); fill_asc(asc_data_10000.begin(), asc_data_10000.end());
        vector<int> asc_data_100000(100'000); fill_asc(asc_data_100000.begin(), asc_data_100000.end());
        { LOG_DURATION("Asc 100 elements")
            insert_sort(asc_data_100.begin(), asc_data_100.end());
        }
        { LOG_DURATION("Asc 1'000 elements")
            insert_sort(asc_data_1000.begin(), asc_data_1000.end());
        }
        { LOG_DURATION("Asc 10'000 elements")
            insert_sort(asc_data_10000.begin(), asc_data_10000.end());
        }
        { LOG_DURATION("Asc 100'000 elements")
            insert_sort(asc_data_100000.begin(), asc_data_100000.end());
        }

        //Descending
        vector<int> des_data_100(100); fill_des(des_data_100.begin(), des_data_100.end());
        vector<int> des_data_1000(1'000); fill_des(des_data_1000.begin(), des_data_1000.end());
        vector<int> des_data_10000(10'000); fill_des(des_data_10000.begin(), des_data_10000.end());
        vector<int> des_data_100000(100'000); fill_des(des_data_100000.begin(), des_data_100000.end());
        { LOG_DURATION("Des 100 elements")
            insert_sort(des_data_100.begin(), des_data_100.end());
        }
        { LOG_DURATION("Des 1'000 elements")
            insert_sort(des_data_1000.begin(), des_data_1000.end());
        }
        { LOG_DURATION("Des 10'000 elements")
            insert_sort(des_data_10000.begin(), des_data_10000.end());
        }
        { LOG_DURATION("Des 100'000 elements")
            insert_sort(des_data_100000.begin(), des_data_100000.end());
        }
    }
    return 0;
}