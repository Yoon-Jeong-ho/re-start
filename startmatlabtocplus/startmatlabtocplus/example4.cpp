////#include<fstream>
////#include<iostream>
////#include<string>
////#include<cmath>
////#include<Eigen/Dense>
////#include <unsupported/Eigen/CXX11/Tensor>
////
////using namespace Eigen;
////using namespace std;
////
////int main44() {
////	ifstream in("Tjoint_diap_xdir2.hob");
////	string str, analysis,model,material,sectiontype;
////	int intmp;
////	char tmp, jointtype,spctype[2],f;
////	vector<MatrixXd> eigvectors;
////	VectorXd material_properties(4),sectionlength(2),sectionthick(2),force(3);
////	MatrixXd eigvec(32, 7),nodecoordination(46,4),storebeam(44,7),joint(6,6),spc(2,3),coordinate(4,2),seq(4,2);
////	eigvec.setZero();
////	material_properties.setZero();
////
////	if (in.is_open()) {
////		while (!in.eof()) {
////			getline(in, str);
////			if (str == "*HO_ANALYSIS") {
////				getline(in, analysis);
////			}
////			else if (str == "*HO_MODEL") {
////				getline(in, model);
////			}
////			else if (str == "*HO_MATERIAL") {
////				getline(in, material);
////				for (int i = 0; i < 3; i++) {
////					in >> material_properties(i);
////					in >> tmp;
////				}
////				in >> material_properties(3);
////			}
////			else if (str == "*HO_SECTION") {
////				getline(in, str);
////				in >> sectiontype;
////				getline(in, str);
////				in >> sectionlength(0);
////				in >> tmp;
////				in >> sectionthick(0);
////				in >> sectionlength(1);
////				in >> tmp;
////				in >> sectionthick(1);
////				coordinate(0, 0) = sectionlength(0)*0.5;
////				coordinate(0, 1) = sectionlength(1) * 0.5*( - 1);
////				coordinate(1, 0) = sectionlength(0) * 0.5;
////				coordinate(1, 1) = sectionlength(1) * 0.5;
////				coordinate(2, 0) = sectionlength(0) * 0.5 * (-1);
////				coordinate(2, 1) = sectionlength(1) * 0.5 ;
////				coordinate(3, 0) = sectionlength(0) * 0.5 * (-1);
////				coordinate(3, 1) = sectionlength(1) * 0.5 * (-1);
////				seq << 1, 2,
////					2, 3,
////					3, 4,
////					4, 1;
////
////			}
////			else if (str == "*HO_NODE") {
////				for (int i = 0; i < 46; i++) {
////					for (int j = 0; j < 3; j++) {
////						in >> nodecoordination(i, j);
////						in >> tmp;
////					}
////					in >>nodecoordination(i, 3);
////				}
////			}
////			else if (str == "*HO_BEAM") {
////				for (int i = 0; i < 44; i++) {
////					for (int j = 0; j < 6; j++) {
////						in >> storebeam(i, j);
////						in >> tmp;
////					}
////					in >> storebeam(i, 6);
////				}
////			}
////			else if (str == "*HO_JOINT") {
////				in >> jointtype;
////				getline(in, str);
////				for (int i = 0; i < 6; i++) {
////					for (int j = 0; j < 5; j++) {
////						in >> joint(i, j);
////						in >> tmp;
////					}
////					in >> joint(i, 5);
////				}
////			}
////			else if (str == "*HO_SPC") {
////				for (int i = 0; i < 2; i++) {
////					in >> spc(i, 0);
////					in >> tmp;
////					in >> spctype[i];
////					in >> tmp;
////					in >> spc(i, 1);
////					in >> tmp;
////					in >> spc(i, 2);
////				}
////			}
////			else if (str == "*HO_FORCE") {
////				in >> force(0);
////				in >> tmp;
////				in >> f;
////				in >> tmp;
////				in >> force(1);
////				in >> tmp;
////				in >> force(2);
////			}
////
////		}
////
////	}
////	else {
////		cout << "file open fail";
////		return 1;
////	}
////
////
////	int start2 = -1, start1 = -1,count = 0,flag=0;
////	for (int i = 0; i < 44; i++) {
////		for (int j = 0; j < 44; j++) {
////			if (storebeam(i, 2) == storebeam(j, 3))break;
////			if (j == 43) start1 = i;
////		}
////		if (start1 != -1) break;
////	}
////
////	for (int i = start1+1; i < 44; i++) {
////		for (int j = 0; j < 44; j++) {
////			if (storebeam(i, 2) == storebeam(j,3))break;
////			if (j == 43) start2 = i;
////		}
////		if (start2 != -1) break;
////	}
////	
////	while (1) {
////		for (int i = 0; i < 44; i++) {
////			if (storebeam(start1, 3) == storebeam(i, 2)) {// connection
////				eigvec(count, all) = storebeam(start1, all);
////				count++;
////				start1 = i;
////				break;
////			}
////			if (i == 43) {
////				flag = 1;
////				break;
////			}
////		}
////		if (flag == 1) {
////			eigvec(count, all) = storebeam(start1, all);
////			break;
////		}
////	}
////	eigvectors.push_back(eigvec);
////	eigvec.setZero();
////	count = 0;
////	flag = 0;
////	while (1) {
////		for (int i = 0; i < 44; i++) {
////			if (storebeam(start2, 3) == storebeam(i, 2)) {// connection
////				eigvec(count, all) = storebeam(start2, all);
////				count++;
////				start2 = i;
////				break;
////			}
////			if (i == 43) {
////				flag = 1;
////				break;
////			}
////		}
////		if (flag == 1) {
////			eigvec(count, all) = storebeam(start2, all);
////			break;
////		}
////	}
////	eigvectors.push_back(eigvec);
////	cout <<"This is the "<<analysis << " Analysis of "<< model <<" Model."<<endl;
////	cout <<"element " << material_properties(0) << " " << material << "(E = " << material_properties(1) << ", nu = " << material_properties(2) << ", rho = " << material_properties(3) << ")" << endl;
////	cout<<"Section Type = "<< sectiontype << " sectionlength = " << sectionlength.transpose() << " sectionthick = "<< sectionthick.transpose() << endl;
////	cout <<" coordinate is = \n" << coordinate << endl << "seq is = \n" << seq << endl;
////	cout << nodecoordination << endl;
////	//cout << storebeam << endl;
////	cout << "joint type is = " << jointtype << endl << joint<<endl;
////	cout <<"spc = \n" << spc << endl;
////	cout <<"force = " << force.transpose() << endl;
////	for (int i = 0; i < eigvectors.size(); i++)
////		cout << eigvectors[i] << endl << endl;
////
////	in.close();
////	return 0;
////}
//////
//////cout << storebeam << endl << endl;
//////RowVectorXd beamele, startbeams(2);
//////vector<RowVectorXd> beams;
//////MatrixXd beami;
//////vector<MatrixXd> Beam;
//////startbeams << 1, 8;
//////double node;
//////
//////
//////for (int k = 0; k < startbeams.size(); k++)
//////{
//////	node = storebeam(k, 2);
//////	beams.clear();
//////	for (int i = 0; i < storebeam.rows(); i++)
//////	{
//////		for (int j = 0; j < storebeam.rows(); j++)
//////		{
//////			if (node == storebeam(j, 2))
//////			{
//////				cout << storebeam(j, all) << endl;
//////				node = storebeam(j, 3);
//////				beams.push_back(storebeam(j, all));
//////				break;
//////			}
//////
//////		}
//////	}
//////	beami.setZero(beams.size(), 7);
//////	for (int i = 0; i < beams.size(); i++)
//////		beami(i, all) = beams[i];
//////
//////	Beam.push_back(beami);
//////}
//////
//////for (int i = 0; i < 2; i++)
//////	cout << Beam[i] << endl << endl;
//
//
//int main4() {
//	ifstream in("Tjoint_diap_xdir2.hob");
//	string str, analysis, model, material, sectiontype;
//	int intmp;
//	char tmp, jointtype, spctype[2], f;
//	vector<MatrixXd> eigvectors;
//	VectorXd material_properties(4), sectionlength(2), sectionthick(2), force(3);
//	MatrixXd eigvec(32, 7), nodecoordination(46, 4), storebeam(44, 7), joint(6, 6), spc(2, 3), coordinate(4, 2), seq(4, 2);
//	eigvec.setZero();
//	material_properties.setZero();
//
//	if (in.is_open()) {
//		while (!in.eof()) {
//			getline(in, str);
//			if (str == "*HO_ANALYSIS") {
//				getline(in, analysis);
//			}
//			else if (str == "*HO_MODEL") {
//				getline(in, model);
//			}
//			else if (str == "*HO_MATERIAL") {
//				getline(in, material);
//				for (int i = 0; i < 3; i++) {
//					in >> material_properties(i);
//					in >> tmp;
//				}
//				in >> material_properties(3);
//			}
//			else if (str == "*HO_SECTION") {
//				getline(in, str);
//				in >> sectiontype;
//				getline(in, str);
//				in >> sectionlength(0);
//				in >> tmp;
//				in >> sectionthick(0);
//				in >> sectionlength(1);
//				in >> tmp;
//				in >> sectionthick(1);
//				coordinate(0, 0) = sectionlength(0) * 0.5;
//				coordinate(0, 1) = sectionlength(1) * 0.5 * (-1);
//				coordinate(1, 0) = sectionlength(0) * 0.5;
//				coordinate(1, 1) = sectionlength(1) * 0.5;
//				coordinate(2, 0) = sectionlength(0) * 0.5 * (-1);
//				coordinate(2, 1) = sectionlength(1) * 0.5;
//				coordinate(3, 0) = sectionlength(0) * 0.5 * (-1);
//				coordinate(3, 1) = sectionlength(1) * 0.5 * (-1);
//				seq << 1, 2,
//					2, 3,
//					3, 4,
//					4, 1;
//
//			}
//			else if (str == "*HO_NODE") {
//				for (int i = 0; i < 46; i++) {
//					for (int j = 0; j < 3; j++) {
//						in >> nodecoordination(i, j);
//						in >> tmp;
//					}
//					in >> nodecoordination(i, 3);
//				}
//			}
//			else if (str == "*HO_BEAM") {
//				for (int i = 0; i < 44; i++) {
//					for (int j = 0; j < 6; j++) {
//						in >> storebeam(i, j);
//						in >> tmp;
//					}
//					in >> storebeam(i, 6);
//				}
//			}
//			else if (str == "*HO_JOINT") {
//				in >> jointtype;
//				getline(in, str);
//				for (int i = 0; i < 6; i++) {
//					for (int j = 0; j < 5; j++) {
//						in >> joint(i, j);
//						in >> tmp;
//					}
//					in >> joint(i, 5);
//				}
//			}
//			else if (str == "*HO_SPC") {
//				for (int i = 0; i < 2; i++) {
//					in >> spc(i, 0);
//					in >> tmp;
//					in >> spctype[i];
//					in >> tmp;
//					in >> spc(i, 1);
//					in >> tmp;
//					in >> spc(i, 2);
//				}
//			}
//			else if (str == "*HO_FORCE") {
//				in >> force(0);
//				in >> tmp;
//				in >> f;
//				in >> tmp;
//				in >> force(1);
//				in >> tmp;
//				in >> force(2);
//			}
//
//		}
//
//	}
//	else {
//		cout << "file open fail";
//		return 1;
//	}
//
//	int start[2] = { -1,-1 }, count = 0;
//	for (int i = 0; i < 44; i++) {
//		for (int j = 0; j < 44; j++) {
//			if (storebeam(i, 2) == storebeam(j, 3))break;
//			if (j == 43) start[0] = i;
//		}
//		if (start[0] != -1) break;
//	}
//
//	for (int i = start[0] + 1; i < 44; i++) {
//		for (int j = 0; j < 44; j++) {
//			if (storebeam(i, 2) == storebeam(j, 3))break;
//			if (j == 43) start[1] = i;
//		}
//		if (start[1] != -1) break;
//	}
//
//	vector<RowVectorXd> beams;
//	MatrixXd beami;
//	vector<MatrixXd> Beam;
//	intmp = 0;
//	for (int k = 0; k < 2; k++)
//	{
//		beams.clear();
//		beams.push_back(storebeam(start[k], all));
//		for (int i = 0; i < storebeam.rows(); i++)
//		{
//			for (int j = 0; j < storebeam.rows(); j++)
//			{
//				if (storebeam(start[k], 3) == storebeam(j, 2))
//				{
//					start[k] = j;
//					beams.push_back(storebeam(j, all));
//					break;
//				}
//
//			}
//		}
//		beami.setZero(beams.size(), 7);
//		for (int i = 0; i < beams.size(); i++)
//			beami(i, all) = beams[i];
//		Beam.push_back(beami);
//	}
//
//	cout << "This is the " << analysis << " Analysis of " << model << " Model." << endl;
//	cout << "element " << material_properties(0) << " " << material << "(E = " << material_properties(1) << ", nu = " << material_properties(2) << ", rho = " << material_properties(3) << ")" << endl;
//	cout << "Section Type = " << sectiontype << " sectionlength = " << sectionlength.transpose() << " sectionthick = " << sectionthick.transpose() << endl;
//	cout << " coordinate is = \n" << coordinate << endl << "seq is = \n" << seq << endl;
//	cout << nodecoordination << endl;
//	cout << "joint type is = " << jointtype << endl << joint << endl;
//	cout << "spc = \n" << spc << endl;
//	cout << "force = " << force.transpose() << endl;
//	for (int i = 0; i < 2; i++)cout << Beam[i] << endl << endl;
//	in.close();
//	return 0;
//}
