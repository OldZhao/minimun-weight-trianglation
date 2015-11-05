//
//  main.cpp
//  triangulation
//
//  Created by yongfeipu on 15/11/2.
//  Copyright © 2015年 yongfeipu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#define column 2
using namespace std;

double count_distance;

double Euclid_distance(int i, int j, double **coordsarray){
    double distance = sqrt(pow(coordsarray[i][0]- coordsarray[j][0],2)+pow(coordsarray[i][1] - coordsarray[j][1],2));
    return distance;
}

int minitriangulation(int count_dot, double **coordsarray, double **perimeter, int **kpos){
    double temp;
    
    for (int i = 0; i < count_dot; ++i) {
        perimeter[i][i] = 0;
    }
    for (int i = 0; i < count_dot - 1; ++i) {
        perimeter[i][i + 1] = Euclid_distance(i, i + 1, coordsarray);
        //cout<<perimeter[i][i+1]<<endl;
    }
    cout<<endl;
    for (int l = 2; l < count_dot; ++l) {
        for (int i = 0; i < count_dot - l; ++i) {
            int j = i + l;
            perimeter[i][j] = 100000;
            for (int k = i + 1; k < j; ++k) {
                temp = perimeter[i][k] + perimeter[k][j] + Euclid_distance(i, j, coordsarray);
                //cout<<"i k j "<<i<<" "<<k<<" "<<j<<" : "<<temp<<endl;
                if(temp<perimeter[i][j]){
                    perimeter[i][j] = temp;
                    kpos[i][j] = k;
                }
                
            }
            //cout<<endl;
        }
    }
    return 0;
}

int printtriangule(int i, int j, int **kpos){
    if (i == j-1) {
        return 0;
    }
    cout<<"point-to-point links : V"<<i<<", V"<<kpos[i][j]<<", V"<<j<<endl;
    printtriangule(i, kpos[i][j], kpos);
    printtriangule(kpos[i][j], j, kpos);
    return 0;
}

int main(int argc, const char * argv[]) {
    ifstream file;
    string line;
    int count = 0;
    count_distance = 0;
    double sides = 0;
    file.open("test_30.txt", ios::binary);
    if(!file.is_open()){
        cout<<"data loaded unsuccessfully"<<endl;
        return 0;
    }
    getline(file, line);
    line.erase(line.begin());
    line.erase(line.begin());
    count = stoi(line);
    
    double **coords = new double*[count];// coords[][] save dots' coords
    for (int i = 0; i < count; ++i) {
        coords[i] = new double[column];
    }
    
    for(int i = 0; i < count; ++i) {
        double firstcoord, secondcoord;
        string::size_type sz;
        getline(file, line);
        line.erase(line.begin());
        line.erase(line.end()-1);
        firstcoord =  stod(line, &sz);
        secondcoord = stod(line.substr(sz+1));
        coords[i][0] = firstcoord;
        coords[i][1] = secondcoord;
//        cout<< firstcoord<<endl;
//        cout<<secondcoord<<endl;
    }
//    
//    for (int i = 0; i < count; ++i) {
//        cout << coords[i][0]<< ", "<< coords[i][1]<< endl;
//    }
//
    double **perimeter = new double*[count];
    for (int i = 0; i < count; ++i) {
        perimeter[i] = new double[count];
    }
    
    int **kpos = new int*[count];
    for (int i = 0; i < count; ++i) {
        kpos[i] = new int[count];
    }
    
    
    minitriangulation(count, coords, perimeter, kpos);
    printtriangule(0, count - 1, kpos);
    
    //cout<<count_distance;
    //cout<< perimeter[0][count-1];
    
    for (int i = 0; i < count - 1; ++i) {
        sides = perimeter[i][i + 1] + sides;
    }
    sides = sides + Euclid_distance(count - 1, 0, coords);
    count_distance =  perimeter[0][count - 1] * 2 - sides;
    cout<<"The minimun-weight triangulation of total edge length is: "<<count_distance<<endl;
    
    
    for (int i = 0; i < count; ++i) {
        delete[] coords[i];
    }
    
    delete[] coords;
    
    for (int i = 0; i < count; ++i) {
        delete[] perimeter[i];
    }
    delete [] perimeter;
    
    for (int i = 0; i < count; ++i) {
        delete[] kpos[i];
    }
    
    delete[] kpos;
    return 0;
}
