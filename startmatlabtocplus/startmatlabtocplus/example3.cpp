//#include<fstream>
//#include<iostream>
//#include<string>
//#include<cmath>
//#include<Eigen/Dense>
//#include <unsupported/Eigen/CXX11/Tensor>
//
//using Eigen::MatrixXd;
//using namespace std;
///*
//2 3 -5 0 -4 6 -8 9 -10 11 -12
//5 -4 7 -6 9 -8 11 -10 13 0 15
//1 2 -3 4 -5  6 -7 8 -9 10 0
//-3 4 0 6 -7 8 -9 10 -11 12 -13
//7 -6 5 -4 3 -2 1 -10 9 -8 7
//1 2 -3 4 0 6 -7 8 -9 10 -11
//0 -8 12 -16 20 -24 28 -32 36 -40 44
//-2 3 -4 5 -6 7 -8 9 0 11 -12
//6 -5 4 -3 2 -1 0 -9 8 -7 6
//-4 6 -8 10 -12 14 -16 18 -20 22 0
//*/
//
//
//int main3_1() {
//	MatrixXd input(11, 10), derivate(11, 10), integral(12, 10);
//	cout << "give 10 equations\n";
//	for (int i = 0; i < 10; i++) for (int j = 10; j >= 0; j--) cin >> input(j, i);
//	cout << input<<"\n";
//	for (int i = 0; i < 10; i++) for (int j = 0; j <= 10; j++) {
//		derivate(j, i) = input(j+1, i) * (j + 1);
//		if (j == 10) derivate(j, i) = 0;
//	}
//	cout << "derivate is \n" << derivate << "\n";
//	for (int i = 0; i < 10; i++) for (int j = 0; j <= 10; j++) {
//		integral(j+1, i) = input(j, i) / (j + 1);
//		if (j == 0) integral(j, i) = 0;
//	}
//	cout << "integral is \n" << integral;
//	return 0;
//
//}
//
//int main21() {
//	ifstream in("new-frq.dat");
//	string str;
//	int eigenvalue = 0;
//	Eigen::Tensor<double, 3> tensor(12, 371, 6);
//	tensor.setZero();
//	if(in.is_open()) {
//		while (1) {
//			getline(in, str);
//			if (str == "            NOTE") {
//				getline(in, str);
//				for (int i = 0; i < 371; i++) {
//					in>> str;
//					for (int j = 0; j < 6; j++) {
//						in >> tensor(eigenvalue, i, j);
//					}
//				}
//				if (eigenvalue == 11) break;
//				eigenvalue++;
//			}
//
//
//		}
//
//	}
//	else {
//		cout << "file open fail";
//		return 1;
//	}
//	cout << tensor;
//	in.close();
//	return 0;
//}
//
//
//
//int main23() { // 알리 코드
//	ifstream in("new-frq.dat");
//	string str;
//	int eigenvalue = 0;
//	vector<MatrixXd> eigvectors;
//	MatrixXd eigvec(371, 6);
//	eigvec.setZero();
//	Eigen::Tensor<double, 3> tensor(371, 6, 12);
//	tensor.setZero();
//	if (in.is_open()) {
//		while (1) {
//			getline(in, str);
//			if (str == "            NOTE") {
//				getline(in, str);
//				for (int i = 0; i < 371; i++) {
//					in >> str;
//					for (int j = 0; j < 6; j++) {
//						in >> eigvec(i, j);
//						in >> tensor(i, j, eigenvalue);
//					}
//				}
//				eigvectors.push_back(eigvec);
//				if (eigenvalue == 11) break;
//				eigenvalue++;
//			}
//
//
//		}
//
//	}
//	else {
//		cout << "file open fail";
//		return 1;
//	}
//
//	for (int i = 0; i < eigvectors.size(); i++)
//		cout << eigvectors[i] << endl << endl;
//
//	cout << tensor;
//	in.close();
//	return 0;
//}
