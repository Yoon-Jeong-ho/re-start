//#include<iostream> 
//#include<cmath>
//#include <Eigen/Dense>
//
//using Eigen::MatrixXd;
//using namespace std;
//
//double get_len(double x1, double y1, double x2, double y2);
//double get_ang(double x1, double y1, double x2, double y2);
//
//
//int main_124124() {
//	MatrixXd coordinate(4, 2), seq(4,2);
//	double length[4], angle[4],x1,y1,x2,y2;
//	int x;
//	for (int i = 0; i < 4; i++)  for (int j = 0 ; j < 2 ; j++) cin >> coordinate(i,j);
//	seq << 1, 2,
//		2, 3,
//		3, 4,
//		4, 1;
//	for (int i = 0; i < 4; i++) {
//		x = seq(i, 0) - 1;
//		x1 = coordinate(x, 0);
//		y1 = coordinate(x, 1);
//		x = seq(i, 1) - 1;
//		x2= coordinate(x, 0); 
//		y2= coordinate(x, 1);
//		length[i] = get_len(x1,y1,x2,y2);
//		angle[i] = get_ang(x1,y1,x2,y2);
//	}
//	for (int i = 0; i < 4; i++) cout << length[i] << " ";
//	cout << "\n";
//	for (int i = 0; i < 4; i++) cout << angle[i] << " ";
//	return 0;
//}
//
//double get_len(double x1, double y1, double x2, double y2) {
//	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
//}
//double get_ang(double x1, double y1, double x2, double y2) {
//	return atan2(y2 - y1, x2 - x1);
//}
