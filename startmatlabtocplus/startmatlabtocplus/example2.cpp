//#include<iostream>
//#include<cmath>
//#include <Eigen/Dense>
//
//using Eigen::MatrixXd;
//using namespace std;
//
//MatrixXd get_cnt(MatrixXd coordinate/*, MatrixXd seq*/, int n);
//int main12() {
//	int n;
//	cout << "how many coordinate you input?\n";
//	cin >> n;
//	MatrixXd coordinate(n, 2),result(1,2);
//	for (int i = 0; i < n; i++) for (int j = 0; j < 2; j++) cin >> coordinate(i, j);
//	if (n == 5) {  //tikness = 0.1
//		MatrixXd newcoordinate(7, 2);
//		for (int i = 0; i < 3; i++) for (int j = 0; j < 2; j++) newcoordinate(i, j) = coordinate(i, j);
//		newcoordinate(3, 0) = coordinate(4, 0);
//		newcoordinate(3, 1) = coordinate(4, 1);
//		newcoordinate(4, 0) = coordinate(4, 0);
//		newcoordinate(4, 1) = coordinate(4, 1) + 0.1;
//		newcoordinate(5, 0) = coordinate(3, 0)+ 0.1* (coordinate(3, 0)-coordinate(2, 0)/coordinate(3, 1) - coordinate(2, 1));
//		newcoordinate(5, 1) = coordinate(3, 1) + 0.1;
//		newcoordinate(6, 0) = coordinate(3, 0);
//		newcoordinate(6, 0) = coordinate(3, 1);
//		result = get_cnt(newcoordinate/*, seq*/, n+2);
//	}
//	else {
//		MatrixXd seq(n, 2);
//		for (int i = 0; i < n; i++) for (int j = 0; j < 2; j++) {
//			if (i + j + 1 < n)seq(i, j) = i + j + 1;
//			else seq(i, j) = 1;
//		}
//		result = get_cnt(coordinate/*, seq*/, n);
//	}
//	cout <<"centroid coordinate is "<< result;
//	return 0;
//}
//
////
////MatrixXd get_cnt(MatrixXd coordinate/*, MatrixXd seq*/, int n) {
////	MatrixXd result(1, 2);
////	for (int i = 0; i < n; i++) {
////		result(0, 0) += coordinate(i, 0);
////		result(0, 1) += coordinate(i, 1);
////	}
////	return result / n;
////}
//
//MatrixXd get_cnt(MatrixXd coordinate/*, MatrixXd seq*/, int n) {
//	MatrixXd result(1, 2);
//	double area=0,x=0,y=0;
//	for (int i = 0; i < n; i++) {
//		area = area + coordinate(i, 0) * coordinate((i + 1)%n, 1) - coordinate((i + 1) % n, 0) * coordinate(i, 1);
//		x = x +(coordinate(i, 0) + coordinate((i + 1) % n, 0)) * (coordinate(i, 0) * coordinate((i + 1) % n, 1) - coordinate((i + 1) % n, 0) * coordinate(i, 1));
//		y = y + (coordinate(i, 1) + coordinate((i + 1) % n, 1)) * (coordinate(i, 0) * coordinate((i + 1) % n, 1) - coordinate((i + 1) % n, 0) * coordinate(i, 1));
//	}
//	area *= 0.5;
//	result(0, 0) = x / area / 6;
//	result(0, 1) = y / area / 6;
//
//	return result;
//}
