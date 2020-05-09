#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<stdlib.h>
#include<ctime>
#include <unordered_map>
#include<stdio.h>
#include<unordered_set>
#include<numeric>
#include<set>
#include<array>


using namespace std;

void CoutTime(clock_t starttime) { // ��ʱ������
    clock_t endtime = clock();
    double endtime1 = (double(endtime) - double(starttime)) / CLOCKS_PER_SEC;
    cout << endtime1 << "s" << endl;
}

void read(string filename, vector<vector<int>>& a) { //��ȡ.csv�ļ�����ȡ������洢��a, 
    string line;
    vector<int> b; //��ȡһ�еĵ�Ԫ�������ַ���ȡ����
    ifstream Fil(filename);
    if (Fil.fail()) { cout << "File not found" << endl; return; }
    while (getline(Fil, line))
    {
        b.clear();
        int linepos = 0;
        char c;
        int linemax = int(line.length());
        while (linepos < linemax)
        {
            c = line[linepos];
            if (isdigit(c)) {
                b.push_back(c - '0');
            }
            ++linepos;
        }
        a.push_back(b);
    }
    Fil.close();
    return;
}

template <size_t SIZE>
inline void insertSort1(array<int, SIZE>& arr1, int length) {
    for (int i = 1; i < length; i++) {
        for (int j = i - 1; j >= 0 && arr1[j + 1] < arr1[j]; j--) {
            swap(arr1[j], arr1[j + 1]);
        }
    }
}


template<typename iterator>
struct ArrayHasher {
    auto operator()(const iterator& arr)const {
        rsize_t sum = arr[0];
        for (auto it = arr.begin(); it != arr.end(); it++) {
            sum = sum ^ hash<size_t>{}(*it);
        }
        return hash<size_t>{}(sum);
    }
};

template<typename iterator>
using ArrayHashSet = std::unordered_set<iterator, ArrayHasher<iterator>>;

class Solution {
public:
    void iniadjs() {    //�����ڴ�ռ�
        adjS1 = createdArray2D(numTA, numTB);      //  cout << "iniadjs1";
        adjS3 = createdArray2D(numTA, numTB);       // cout << "iniadjs3";
        adjS5 = createdArray2D(numTA, numTB);       // cout << "iniadjs5";
        adjS2 = createdArray2D(numTA, numTA);       // cout << "iniadjs2";
        adjS4 = createdArray2D(numTA, numTA);       // cout << "iniadjs4";
    }
    void setadjs12345() { //���� ��i���Ŀ���ͨ�ĵ㣬��Ϊ��֦�ж�
        iniadjs();
        for (int i = 0; i < numTA; i++) {
            for (int j = 0; j < adjV[i]; j++) {
                adjS1[i][adjarray[i][j] - numTA] = true;
            }
        }
        for (int i = 0; i < numTA; i++) {
            for (int j = 0; j < adjV[i]; j++) {
                int aij = adjarray[i][j];
                for (int k = 0; k < adjV[aij]; k++) {
                    adjS2[i][adjarray[aij][k]] = true;
                }
            }
        }
        for (int i = 0; i < numTA; i++) {
            for (int j = 0; j < numTA; j++) {
                if (adjS2[i][j]) {
                    for (int k = 0; k < numTB; k++) {
                        if (adjS1[j][k]) {
                            adjS3[i][k] = true;
                        }
                    }
                }
            }
        }
        // 4
        for (int i = 0; i < numTA; i++) {
            for (int j = i; j < numTA; j++) {
                if (adjS2[i][j]) {
                    for (int k = 0; k < numTA; k++) {
                        if (adjS2[j][k]) {
                            adjS4[i][k] = true;
                            adjS4[k][i] = true;
                        }
                    }
                }
            }
        }
        //5
        for (int i = 0; i < numTA; i++) {
            for (int j = 0; j < numTA; j++) {
                if (adjS4[i][j]) {
                    for (int k = 0; k < numTB; k++) {
                        if (adjS1[j][k]) {
                            adjS5[i][k] = true;
                        }
                    }
                }
            }
        }
    }
    void setcount(int num, int numTA1, int numTB1) { //�����������������������A��B������
        step = num;
        numTA = numTA1;
        numTB = numTB1;
        numTotalAB = numTA + numTB;
        visited = new int[numTotalAB]; //�����������
        cout << "Set count is ok. Maximum number of names:  " << step << endl;
    }
    void setstar(int star) {  //�����������
        memset(visited, false, numTotalAB * sizeof(int));
        start = star;
    }
    void setadjV(const vector<vector<int>>& adj, int numTotalAB) {  // �ڽ�����
        adjV = new int[numTotalAB];    //�ڽ�������ÿ���ڵ�����ڽڵ���
        adjarray = new int* [numTotalAB];//�ڽ�����
        for (int i = 0; i < numTotalAB; i++) {
            int i_Size = adj[i].size();
            adjV[i] = i_Size;
            adjarray[i] = new int[i_Size];
            for (int j = 0; j < i_Size; j++) {
                adjarray[i][j] = adj[i][j];
            }
        }
    }
    void coutsumname(clock_t starttime) { //������
        clock_t endtime = clock();
        double endtime1 = (double(endtime) - double(starttime)) / CLOCKS_PER_SEC;
        ofstream ofs;
        ofs.open("result.txt", ios::out);
        if (!ofs) {
            cout << "creat result.txt";
            system("result.txt");
        }
        ofs << " time " << endtime1 << "s" << endl;
        for (int i = 4; i < 15; i++, i++) {

            ofs << i << " names: " << Hash_name_num[i] << ";\n";
        }
        ofs.close();
        for (int i = 4; i < 15; i++, i++) {
            std::cout << i << " names: " << Hash_name_num[i] << ";\n";
        }
    }
    void mysetclear() {
        myArrSet6.clear();
        myArrSet8.clear();
        myArrSet10.clear();
        myArrSet12.clear();
        myArrSet14.clear();
    }
    void mysetreserve() {   //Ԥ�����ڴ�
        myArrSet6.reserve(256);
        myArrSet8.reserve(512);
        myArrSet10.reserve(4096);
        myArrSet12.reserve(31921 * 2);
        myArrSet14.reserve(690598 * 6);
    }
    void hash_num(void) {
        Hash_name_num[14] += myArrSet14.size();
        Hash_name_num[12] += myArrSet12.size();
        Hash_name_num[10] += myArrSet10.size();
        Hash_name_num[8] += myArrSet8.size();
        Hash_name_num[6] += myArrSet6.size();
    }
    void DFS(int stapos) { //DFS      
        visited[stapos] = true;  // ��� �ڵ� stapos Ϊ �ѷ��ʹ��Ľڵ�        
        temp[length] = stapos;
        length++;
        int i = adjV[stapos];  //�ڵ�stapos�ڽӽڵ�������������
        if (length == 1) {  // ��һ���ڵ����һ���ڵ㲻�������ĸ���
            i--;
        }
        while (i--) {
            int k = adjarray[stapos][i]; // ��i������Ϊk;
            if (k == start && length > 3) {  // �ص���ʼ�ڵ㣬������
                if (temp[1] < temp[length - 1]) {
                    if (length == 12) {
                        memcpy(&temparr11[0], temp + 1, 11 * sizeof(int));
                        swap(temparr11[0], temparr11[5]);
                        swap(temparr11[2], temparr11[7]);
                        swap(temparr11[4], temparr11[9]);
                        insertSort1(temparr11, 11);
                        temparrul3[0] = temparr11[0];
                        for (int i = 1; i < 5; i++) {
                            temparrul3[0] = (temparrul3[0] << 12) + temparr11[i];
                        }
                        temparrul3[1] = temparr11[5];
                        for (int i = 6; i < 10; i++) {
                            temparrul3[1] = (temparrul3[1] << 12) + temparr11[i];
                        }
                        temparrul3[2] = temparr11[10];
                        myArrSet12.insert(temparrul3);
                    }
                    else if (length == 10) {
                        memcpy(&temparr9[0], temp + 1, 9 * sizeof(int));
                        swap(temparr9[0], temparr9[5]);
                        swap(temparr9[2], temparr9[7]);
                        insertSort1(temparr9, 9);
                        temparrul2[0] = temparr9[0];
                        for (int i = 1; i < 5; i++) {
                            temparrul2[0] = (temparrul2[0] << 12) + temparr9[i];
                        }
                        temparrul2[1] = temparr9[5];
                        for (int i = 6; i < 9; i++) {
                            temparrul2[1] = (temparrul2[1] << 12) + temparr9[i];
                        }
                        myArrSet10.insert(temparrul2);
                    }
                    else if (length == 8) {
                        memcpy(&temparr7[0], temp + 1, 7 * sizeof(int));
                        swap(temparr7[0], temparr7[3]);
                        swap(temparr7[2], temparr7[5]);
                        insertSort1(temparr7, 7);
                        temparrui4[0] = (temparr7[0] << 12) + temparr7[1];
                        temparrui4[1] = (temparr7[2] << 12) + temparr7[3];
                        temparrui4[2] = (temparr7[4] << 12) + temparr7[5];
                        temparrui4[3] = temparr7[6];
                        myArrSet8.insert(temparrui4);
                    }
                    else if (length == 6) {
                        memcpy(&temparr5[0], temp + 1, 5 * sizeof(int));
                        swap(temparr5[0], temparr5[3]);
                        insertSort1(temparr5, 5);
                        temparrui3[0] = (temparr5[0] << 12) + temparr5[1];
                        temparrui3[1] = (temparr5[2] << 12) + temparr5[3];
                        temparrui3[2] = temparr5[4];
                        myArrSet6.emplace(temparrui3);
                    }
                    else if (length == 4) {
                        Hash_name_num[4] ++;
                    }
                }
            }
            else if (!visited[k] && k > start) {    //// ȥ�� ��i������Ϊ�Ѿ��������� { // ȥ���Ѿ����ʹ��Ľڵ�;
                if (length < 9) {
                    DFS(k);
                }
                else if (length == 12) {
                    if (adjS2[start][k]) {
                        DFS(k);
                    }
                }
                else if (length == 13) { //�Ѿ���¼��13������ ����������һ��
                    if (adjS1[start][k - numTA] && (temp[1] < k)) {
                        memcpy(&temparr13[0], temp + 1, 12 * sizeof(int));
                        swap(temparr13[0], temparr13[7]);
                        swap(temparr13[2], temparr13[9]);
                        swap(temparr13[4], temparr13[11]);
                        temparr13[12] = k;
                        insertSort1(temparr13, 13);
                        temparrul3[0] = temparr13[0];
                        for (int i = 1; i < 5; i++) {
                            temparrul3[0] = (temparrul3[0] << 12) + temparr13[i];
                        }
                        temparrul3[1] = temparr13[5];
                        for (int i = 6; i < 10; i++) {
                            temparrul3[1] = (temparrul3[1] << 12) + temparr13[i];
                        }
                        temparrul3[2] = (long long(temparr13[10]) << 24) + (temparr13[11] << 12) + temparr13[12];
                        myArrSet14.insert(temparrul3);
                    }
                }
                else if (length == 9) {  //�Ѿ������˼�¼��9������
                    if (adjS5[start][k - numTA]) { //��֦ �ж�5���ܷ�ص���ʼ�ڵ�;
                        DFS(k);
                    }
                }
                else if (length == 10) {
                    if (adjS4[start][k]) {
                        DFS(k);
                    }
                }
                else if (length == 11) {
                    if (adjS3[start][k - numTA]) {
                        DFS(k);
                    }
                }
            }
        }
        visited[stapos] = false;
        length--;
        temp[length] = 0;
    }
    void freeall() {  //�ͷŶѿռ�
        freeArray2D(adjS1, numTA);
        freeArray2D(adjS2, numTA);
        freeArray2D(adjS3, numTA);
        freeArray2D(adjS4, numTA);
        freeArray2D(adjS5, numTA);
        freeArray2D(adjarray, numTA);
        delete[] visited;
        delete[] adjV;
    }
private:
    int temp[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };  //����·��
    array<int, 13> temparr13 = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };  //����Ļ��ڵ㣬Ȼ������
    array<int, 11> temparr11 = { 0,0,0,0,0,0,0,0,0,0,0 };
    array<int, 9> temparr9 = { 0,0,0,0,0,0,0,0,0 };
    array<int, 7> temparr7 = { 0,0,0,0,0,0,0 };
    array<int, 5> temparr5 = { 0,0,0,0,0 };

    array<int, 4> temparrui4 = { 0,0,0,0 }; // unordered_set ������ݡ�
    array<int, 3> temparrui3 = { 0,0,0 };
    array<long long, 2> temparrul2 = { 0,0 };
    array<long long, 3> temparrul3 = { 0,0,0 };

    ArrayHashSet<array<long long, 3>> myArrSet14;   // unordered_set  ����
    ArrayHashSet<array<long long, 3>> myArrSet12;
    ArrayHashSet<array<long long, 2>> myArrSet10;
    ArrayHashSet<array<int, 4>> myArrSet8;
    ArrayHashSet<array<int, 3>> myArrSet6;
    int* adjV = nullptr;
    int** adjarray = nullptr;
    int numTA = 0, numTB = 0, start = 0;
    int numTotalAB = 0;   //   numTA + numTB;
    int length = 0;  //�Ѿ���¼��������Ŀ
    int step = 0;  // ����
    int Hash_name_num[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; // �洢������������Ϊ4,6,8,10,12,14�ĵļ�Ʒ������
    int* visited = nullptr;
    int** adjS1 = nullptr;
    int** adjS2 = nullptr;
    int** adjS3 = nullptr;
    int** adjS4 = nullptr;
    int** adjS5 = nullptr;
    int** createdArray2D(int rows, int cols) { //����ռ�
        int** array2D = new int* [rows];
        for (int i = 0; i < rows; ++i)
        {
            array2D[i] = new int[cols]();
            memset(array2D[i], 0, sizeof(int) * cols);
        }
        return array2D;
    }
    void freeArray2D(int** array2D, int rows) { //�ͷŶѿռ�
        for (int i = 0; i < rows; ++i)
        {
            delete[] array2D[i];
        }
        delete[] array2D;
    }
};


int main() {
    clock_t starttime = clock();  // ��ʼ��ʱ
    string filename = "./Example.csv"; //6912,3840,25344,577920,11781824,230278656 �ڶ��׶ε�һ������
    //string filename = "./Example421h.csv"; //64, 384,5920,56704,667392,7854016  ��һ�׶ε�һ������
    //string filename = "./Example427.csv";// 128,448,4832,50624,608704,7199808  
    vector<vector<int>> a(0);
    read(filename, a);
    int numTA = int(a.size());
    int numTB = int(a[0].size());
    int numTotalAB = numTA + numTB;
    cout << "total numbers of tribal A: " << numTA << endl;
    cout << "total numbers of tribal B: " << numTB << endl;
    cout << " read time :  ";
    CoutTime(starttime);
    vector<vector<int>> adjarray(numTotalAB);  // ת��������ʽ�ڽӱ�
    for (int i = 0; i < numTA; i++) {
        for (int j = 0; j < numTB; j++) {
            if (a[i][j]) {
                adjarray.at(i).push_back(numTA + j);
                adjarray.at(numTA + j).push_back(i);
            }
        }
    }
    a.clear();
    Solution solt1;
    solt1.setcount(14, numTA, numTB);
    solt1.setadjV(adjarray, numTotalAB);
    solt1.setadjs12345();
    if (numTotalAB > 2000) {// set Ԥ�����ڴ�
        solt1.mysetreserve();
    }
    /*cout << "InI time:    ";
    CoutTime(starttime);*/
    //numTA = 2; 
    for (int i = 0; i < numTA; i++) {
        cout << "\r i = " << i << "   " << i * 100 / numTA << "% ";
        solt1.setstar(i);
        solt1.mysetclear();
        solt1.DFS(i);
        solt1.hash_num();
    }
    cout << endl;
    solt1.coutsumname(starttime);
    solt1.freeall();
    cout << "time:    "; CoutTime(starttime);
    system("pause");
    return 1;
}
