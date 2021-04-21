#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <string>
#include <vector>
#include <time.h>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> generateL(int length) {
    vector<int> makeList;
    for (int i = 0; i < length; i++) {
        makeList.push_back(rand() % length * 10 + 1);
    }
    return makeList;
}

vector<int> generateR(int length) {
    vector<int> makeList;
    int lowerBound = 1;
    for (int i = 0; i < length; i++) {
        makeList.push_back(rand() % (length * 10) + 1);
    }
    sort(makeList.begin(), makeList.end());
    return makeList;
}

vector<int> generateM(int length) {
    vector<int> makeList;
    int upperBound = length * 10;
    for (int i = 0; i < length; i++) {
        makeList.push_back(rand() % (length * 10) + 1);
    }
    sort(makeList.begin(), makeList.end());
    reverse(makeList.begin(), makeList.end());
    return makeList;
}

vector<int> generateV(int length) {
    vector<int> makeList;
    int upperBound = length * 10, lowerBound;
    for (int i = 0; i < length; i++) {
        if (i < length / 2) {
            makeList.push_back(rand() % upperBound + 1);
            upperBound = makeList[i];
        }
        else if (i == length / 2) {
            makeList.push_back(rand() % upperBound + 1);
            lowerBound = makeList[i];
        }
        else {
            makeList.push_back(rand() % (length * 10 - lowerBound + 1) +  lowerBound);
            lowerBound = makeList[i];
        }
    }
    return makeList;
}

vector<int> generateA(int length) {
    vector<int> makeList;
    int upperBound, lowerBound = 0;
    for (int i = 0; i < length; i++) {
        if (i < length / 2) {
            makeList.push_back(rand() % (length * 10 - lowerBound + 1) + lowerBound);
            lowerBound = makeList[i];
        }
        else if (i == length / 2) {
            makeList.push_back(rand() % (length * 10 - lowerBound + 1) + lowerBound);
            upperBound = makeList[i];
        }
        else {
            makeList.push_back(rand() % upperBound + 1);
            upperBound = makeList[i];
        }
    }
    return makeList;
}

void selection(vector<int> &targetList) {
    int temp;
    for (unsigned int i = 0; i < targetList.size() - 1; i++) {
        int mostIndex = i;
        for (unsigned int currentStep = i + 1; currentStep < targetList.size(); currentStep++) {
            if (targetList[mostIndex] < targetList[currentStep]) {
                mostIndex = currentStep;
            }
        }
        temp = targetList[i];
        targetList[i] = targetList[mostIndex];
        targetList[mostIndex] = temp;
    }
    return;
}

void insertion(vector<int> &targetList) {
    int temp;
    for (unsigned int i = 1; i < targetList.size(); i++) {
        for (unsigned int j = i; j > 0; j--) {
            if (targetList[j - 1] < targetList[j]) {
                temp = targetList[j];
                targetList[j] = targetList[j - 1];
                targetList[j - 1] = temp;
            }
            else {
                break;
            }
        }
    }
    return;
}

void bubble(vector<int> &targetList) {
    int temp;
    bool swapped;
    for (unsigned int i = 0; i < targetList.size() - 1; i++) {
        swapped = false;
        for (unsigned int j = 0; j < targetList.size() - i; j++) {
            if (targetList[j] < targetList[j + 1]) {
                temp = targetList[j];
                targetList[j] = targetList[j + 1];
                targetList[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return;
}

void quick(int begIndex, int endIndex, vector<int> &targetList) {
    if (begIndex < endIndex) {
        int pivotValue = targetList[endIndex];
        int newPivot = begIndex;
        int temp;
        for (int i = begIndex; i < endIndex; i++) {
            if (targetList[i] > pivotValue) {
                temp = targetList[i];
                targetList[i] = targetList[newPivot];
                targetList[newPivot] = temp;
                newPivot++;
            }
        }
        temp = targetList[endIndex];
        targetList[endIndex] = targetList[newPivot];
        targetList[newPivot] = temp;
        quick(begIndex, newPivot - 1, targetList);
        quick(newPivot + 1, endIndex, targetList);
    }
    return;
}

void shell(vector<int> &targetList) {
    unsigned int gap = 1;
    int temp;
    while (gap < targetList.size()/3) {
        gap = gap * 3 + 1;
    }
    while (gap > 0) {
        for (int i = gap; i < targetList.size(); i++) {
            temp = targetList[i];
            int j;
            for (j = i; j >= gap && targetList[j - gap] < temp; j -= gap) {
                    targetList[j] = targetList[j - gap];
            }
            targetList[j] = temp;
        }
        gap /= 3;
    }
    return;
}

void mrgArray(int begIndex, int midIndex, int endIndex, vector<int> &targetList) {
    int i = begIndex, j = midIndex + 1, step = 0;
    vector<int> newArray;
    while (i <= midIndex && j <= endIndex) {
        if (targetList[i] < targetList[j]) {
            newArray.push_back(targetList[j]);
            step++;
            j++;
        }
        else {
            newArray.push_back(targetList[i]);
            step++;
            i++;
        }
    }
    if (i <= midIndex) {
        while (i <= midIndex) {
            newArray.push_back(targetList[i]);
            step++;
            i++;
        }
    }
    if (j <= endIndex) {
        while (j <= endIndex) {
            newArray.push_back(targetList[j]);
            step++;
            j++;
        }
    }
    for (int i = 0; i <= endIndex - begIndex; i++) {
        targetList[begIndex + i] = newArray[i];
    }
}

void mrg(int begIndex, int endIndex, vector<int> &targetList) {
    int midIndex = (begIndex + endIndex)/2;
    if (begIndex != endIndex) {
        mrg(begIndex, midIndex, targetList);
        mrg(midIndex + 1, endIndex, targetList);
        mrgArray(begIndex, midIndex, endIndex, targetList);
    }
    return;
}

void counting(vector<int> &targetList) {
    int step = 0;
    vector<int> counter;
    for (int i = 0; i < targetList.size() * 10; i++) {
        counter.push_back(0);
    }
    for (int i = 0; i < targetList.size(); i++) {
        counter[targetList[i]]++;
    }
    for (int i = counter.size() - 1; i > 0; i--) {
        for (int j = 0; j < counter[i]; j++) {
            targetList[step] = i;
            step++;
        }
    }
    return;
}

void heapify(int i, int progress, vector<int> &targetList) {
    int temp, swapPoint = i;
    if (2 * i + 1 < targetList.size() - progress && targetList[swapPoint] > targetList[2 * i + 1]) {
        swapPoint = 2 * i + 1;
    }
    if (2 * i + 2 < targetList.size() - progress && targetList[swapPoint] > targetList[2 * i + 2]) {
        swapPoint = 2 * i + 2;
    }
    if (swapPoint != i) {
        temp = targetList[swapPoint];
        targetList[swapPoint] = targetList[i];
        targetList[i] = temp;
        heapify(swapPoint, progress, targetList);
    }
}

void heap(vector<int> &targetList) {

    for (int i = (targetList.size() / 2) - 1; i >= 0; i--) {
        heapify(i, 0, targetList);
    }
    for (int i = targetList.size() - 1; i >= 1; i--) {
        swap(targetList[0], targetList[i]);
        heapify(0, targetList.size() - i, targetList);
    }
    return;
}

int main() {
    srand(time(NULL));
    string inputMode;
    vector<int> sortList;
    fstream output;
    output.open("wyniki.txt", ios::out);
    cout << ">0< Input a string of integers. (n = 10)\n";
    cout << ">1< Generate random data. (n = 10000, 11000, 12000, 13000, 14000, ... , 20000\n";
    cin >> inputMode;
    while (inputMode != "0" && inputMode != "1") {
        cout << "Podaj 0 lub 1.\n";
        cin >> inputMode;
    }
    if (inputMode == "0") {
        int track = 0;
        int newInt;
        while (track++ < 10) {
            cin >> newInt;
            sortList.push_back(newInt);
        }
    }
    else {
        int track = 0;
        for (int i = 10000; i <= 20000; i += 1000) {
            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("selection," + to_string(i) + ",V,");
                vector<int> testVector = generateV(i);
                auto start = chrono::high_resolution_clock::now();
                selection(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Selection V - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("selection," + to_string(i) + ",A,");
                vector<int> testVector = generateA(i);
                auto start = chrono::high_resolution_clock::now();
                selection(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Selection A - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("selection," + to_string(i) + ",L,");
                vector<int> testVector = generateL(i);
                auto start = chrono::high_resolution_clock::now();
                selection(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Selection L - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("selection," + to_string(i) + ",R,");
                vector<int> testVector = generateR(i);
                auto start = chrono::high_resolution_clock::now();
                selection(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Selection R - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("selection," + to_string(i) + ",M,");
                vector<int> testVector = generateM(i);
                auto start = chrono::high_resolution_clock::now();
                selection(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Selection M - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("insertion," + to_string(i) + ",V,");
                vector<int> testVector = generateV(i);
                auto start = chrono::high_resolution_clock::now();
                insertion(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Insertion V - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("insertion," + to_string(i) + ",A,");
                vector<int> testVector = generateA(i);
                auto start = chrono::high_resolution_clock::now();
                insertion(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Insertion A - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("insertion," + to_string(i) + ",L,");
                vector<int> testVector = generateL(i);
                auto start = chrono::high_resolution_clock::now();
                insertion(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Insertion L - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("insertion," + to_string(i) + ",R,");
                vector<int> testVector = generateR(i);
                auto start = chrono::high_resolution_clock::now();
                insertion(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Insertion R - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("insertion," + to_string(i) + ",M,");
                vector<int> testVector = generateM(i);
                auto start = chrono::high_resolution_clock::now();
                insertion(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Insertion M - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("bubble," + to_string(i) + ",V,");
                vector<int> testVector = generateV(i);
                auto start = chrono::high_resolution_clock::now();
                bubble(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Bubble V - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("bubble," + to_string(i) + ",A,");
                vector<int> testVector = generateA(i);
                auto start = chrono::high_resolution_clock::now();
                bubble(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Bubble A - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("bubble," + to_string(i) + ",L,");
                vector<int> testVector = generateL(i);
                auto start = chrono::high_resolution_clock::now();
                bubble(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Bubble L - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("bubble," + to_string(i) + ",R,");
                vector<int> testVector = generateR(i);
                auto start = chrono::high_resolution_clock::now();
                bubble(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Bubble R - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("bubble," + to_string(i) + ",M,");
                vector<int> testVector = generateM(i);
                auto start = chrono::high_resolution_clock::now();
                bubble(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Bubble M - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("quick," + to_string(i) + ",V,");
                vector<int> testVector = generateV(i);
                auto start = chrono::high_resolution_clock::now();
                quick(0, i - 1, testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Quick V - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("quick," + to_string(i) + ",A,");
                vector<int> testVector = generateA(i);
                auto start = chrono::high_resolution_clock::now();
                quick(0, i - 1, testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Quick A - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("quick," + to_string(i) + ",L,");
                vector<int> testVector = generateL(i);
                auto start = chrono::high_resolution_clock::now();
                quick(0, i - 1, testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Quick L - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("quick," + to_string(i) + ",R,");
                vector<int> testVector = generateR(i);
                auto start = chrono::high_resolution_clock::now();
                quick(0, i - 1, testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Quick R - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("quick," + to_string(i) + ",M,");
                vector<int> testVector = generateM(i);
                auto start = chrono::high_resolution_clock::now();
                quick(0, i - 1, testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Quick M - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("shell," + to_string(i) + ",V,");
                vector<int> testVector = generateV(i);
                auto start = chrono::high_resolution_clock::now();
                shell(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Shell V - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("shell," + to_string(i) + ",A,");
                vector<int> testVector = generateA(i);
                auto start = chrono::high_resolution_clock::now();
                shell(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Shell A - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("shell," + to_string(i) + ",L,");
                vector<int> testVector = generateL(i);
                auto start = chrono::high_resolution_clock::now();
                shell(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Shell L - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("shell," + to_string(i) + ",R,");
                vector<int> testVector = generateR(i);
                auto start = chrono::high_resolution_clock::now();
                shell(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Shell R - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("shell," + to_string(i) + ",M,");
                vector<int> testVector = generateM(i);
                auto start = chrono::high_resolution_clock::now();
                shell(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Shell M - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("merge," + to_string(i) + ",V,");
                vector<int> testVector = generateV(i);
                auto start = chrono::high_resolution_clock::now();
                mrg(0, i - 1, testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Merge V - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("merge," + to_string(i) + ",A,");
                vector<int> testVector = generateA(i);
                auto start = chrono::high_resolution_clock::now();
                mrg(0, i - 1, testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Merge A - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("merge," + to_string(i) + ",L,");
                vector<int> testVector = generateL(i);
                auto start = chrono::high_resolution_clock::now();
                mrg(0, i - 1, testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Merge L - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("merge," + to_string(i) + ",R,");
                vector<int> testVector = generateR(i);
                auto start = chrono::high_resolution_clock::now();
                mrg(0, i - 1, testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Merge R - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("merge," + to_string(i) + ",M,");
                vector<int> testVector = generateM(i);
                auto start = chrono::high_resolution_clock::now();
                mrg(0, i - 1, testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Merge M - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("counting," + to_string(i) + ",V,");
                vector<int> testVector = generateV(i);
                auto start = chrono::high_resolution_clock::now();
                counting(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Counting V - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("counting," + to_string(i) + ",A,");
                vector<int> testVector = generateA(i);
                auto start = chrono::high_resolution_clock::now();
                counting(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Counting A - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("counting," + to_string(i) + ",L,");
                vector<int> testVector = generateL(i);
                auto start = chrono::high_resolution_clock::now();
                counting(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Counting L - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("counting," + to_string(i) + ",R,");
                vector<int> testVector = generateR(i);
                auto start = chrono::high_resolution_clock::now();
                counting(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Counting R - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("counting," + to_string(i) + ",M,");
                vector<int> testVector = generateM(i);
                auto start = chrono::high_resolution_clock::now();
                counting(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Counting M - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("heap," + to_string(i) + ",V,");
                vector<int> testVector = generateV(i);
                auto start = chrono::high_resolution_clock::now();
                heap(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Heap V - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("heap," + to_string(i) + ",A,");
                vector<int> testVector = generateA(i);
                auto start = chrono::high_resolution_clock::now();
                heap(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Heap A - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("heap," + to_string(i) + ",L,");
                vector<int> testVector = generateL(i);
                auto start = chrono::high_resolution_clock::now();
                heap(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Heap L - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("heap," + to_string(i) + ",R,");
                vector<int> testVector = generateR(i);
                auto start = chrono::high_resolution_clock::now();
                heap(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Heap R - DONE! " + to_string(i) + " " + to_string(track) + " \n";

            for (int j = 0; j < 10; j++) {
                string newline = "";
                newline.append("heap," + to_string(i) + ",M,");
                vector<int> testVector = generateM(i);
                auto start = chrono::high_resolution_clock::now();
                heap(testVector);
                auto done = chrono::high_resolution_clock::now();
                newline.append(to_string(chrono::duration_cast<chrono::microseconds>(done - start).count()) + "\n");
                output << newline;
            }
            track += 10;
            cout << "Heap M - DONE! " + to_string(i) + " " + to_string(track) + " \n";
        }
    }
    /*for (int i = 0; i < 10; i++) {
        cout << sortList[i] << " ";
    }*/
}
