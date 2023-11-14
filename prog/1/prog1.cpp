#include <iostream>

using namespace std;

void my_merge(int d[], int temp1[], int h[], int temp2[], int idex[], int temp3[], int l, int m, int r) {
    //  merge d[l ... m-1] and d[m ... r], h[l ... m-1] and h[m ... r], idex[l ... m-1] and idex[m ... r]
    int counter = l;    // counter points to the current temp location
    int ll = l, rr = m; // ll points to left part, rr points to right part
    while(ll <= m-1 && rr <= r) {
        if(h[ll] > h[rr]) {
            temp1[counter] = d[ll];
            temp2[counter] = h[ll];
            temp3[counter] = idex[ll];
            counter++;
            ll++;
        }
        else if(h[ll] < h[rr]) {
            temp1[counter] = d[rr];
            temp2[counter] = h[rr];
            temp3[counter] = idex[rr];
            counter++;
            rr++;
        }
        else {  // h[ll] = h[rr], this time need sort them with (*d)[] in non-decrease order
            if(d[ll] < d[rr]) {
                temp1[counter] = d[ll];
                temp2[counter] = h[ll];
                temp3[counter] = idex[ll];
                ll++;
            } else {
                temp1[counter] = d[rr];
                temp2[counter] = h[rr];
                temp3[counter] = idex[rr];
                rr++;
            }
            counter++;
        }
    }
    while(ll <= m-1) {  // if there is nothing rest in right part
        temp1[counter] = d[ll];
        temp2[counter] = h[ll];
        temp3[counter] = idex[ll];
        ll++;
        counter++;
    }
    while(rr <= r) {    // if there is nothing rest in left part
        temp1[counter] = d[rr];
        temp2[counter] = h[rr];
        temp3[counter] = idex[rr];
        rr++;
        counter++;
    }
    for(int i = l; i <= r; ++i) {   // copy temp array value into d[] h[] and idex[]
        d[i] = temp1[i];
        h[i] = temp2[i];
        idex[i] = temp3[i];
    }
}

void cut_merge(int d[], int temp1[], int h[], int temp2[], int idex[], int temp3[], int n, int len) {
    int i;
    for(i = 1; i <= n - 2 * len; i += 2 * len)  // cut the whole array into pieces of length len, and merge every neighbour pairs of them.
        my_merge(d, temp1, h, temp2, idex, temp3, i, i+len, i+2*len-1);
    if(i + len <= n)    // if the rest can be considered to be two parts
        my_merge(d, temp1, h, temp2, idex, temp3, i, i+len, n); // merge them
    else {  // else, simply copy it into temp array
        for(; i <= n; ++i) {
            temp1[i] = d[i];
            temp2[i] = h[i];
            temp3[i] = idex[i];
        }
    }
}

void mergesort(int d[], int h[] , int idex[], int n) {
    int len = 1;    // len stores the current sorted length of each part.
    int *temp1 = new int[n+1];  // temp1, temp2, temp3 stores sorted d[], h[], idex[] respectively
    int *temp2 = new int[n+1];
    int *temp3 = new int[n+1];
    while(len <= n) {   // increase the length until we get a sorted array
        cut_merge(d, temp1, h, temp2, idex, temp3, n, len);
        len *= 2;
    }
    delete [] temp1;    // clear the allocation memory
    delete [] temp2;
    delete [] temp3;
}

int main() {

    // initialize variables
    int n;  // number of trials
    scanf("%d", &n); // input n from stdin

    int *d = new int[n+1];  // d[] in the problem stated
    int *h = new int[n+1];  // h[] in the problem stated
    int *idex = new int[n+1];  // idex[] store the initial index of trials
    long long tot_h = 0;    // total happiness
    bool isOccupy[n+1];  // isOccupy[i] store the state of day i, day i is scheduled => isOccupy[i] = true
    int schedule[n+1];   // schedule[i] stores the scheduled trial on day i

    // initialize isOccupy
    for(int i = 0; i <= n; ++i) {
        isOccupy[i] = 0;    // initialize the isOccupty[]
        idex[i] = i;    // initialize the idex[]
        schedule[i] = -1;   // initialize the schedule[]
    }

    // input d[] from stdin
    for(int i = 1; i <= n; ++i)
        scanf("%d", &d[i]);
    // input h[] from stdin
    for(int i = 1; i <= n; ++i)
        scanf("%d", &h[i]);
    // sort trials based on happiness of each trial in the non-increase order
    // if reach two identical happiness, sort by the corresponding d[] in the non-decrease order
    mergesort(d, h, idex, n);
    // traverse the trials, and do the greedy algorithm
    for(int i = 1; i <= n; ++i) {
        if(!isOccupy[d[i]]) {   // if day d[i] is available, then choose to go current trial on day d[i]
            isOccupy[d[i]] = 1;
            schedule[d[i]] = idex[i];
            tot_h += h[i];
        } else {                // otherwise, find another day that is as late as possible to schedule the current trial
            for(int j = d[i] - 1; j > 0; j--) {
                if(!isOccupy[j]) {  // if the day is found, then schedule the day with current trial
                    isOccupy[j] = 1;
                    schedule[j] = idex[i];
                    tot_h += h[i];
                    break;
                }
            }
        }
    }

    // do the output
    cout << tot_h << endl;
    for(int i = 1; i < n; ++i)
        printf("%d ", schedule[i]);
    cout << schedule[n] << endl;

    delete[] d;
    delete[] h;
    delete[] idex;

    return 0;
}
