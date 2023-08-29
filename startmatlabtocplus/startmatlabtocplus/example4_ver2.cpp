#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#define _USE_MATH_DEFINES

#include<fstream>
#include<iostream>
#include<string>
#include<cmath>
#include <vector>
#include <sstream>
#include <Eigen/Core>
#include<Eigen/Dense>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/eigen.hpp>
#include <iomanip>
#include <thread>
#include <chrono>
#include <future>
#include <math.h>

#include <unsupported/Eigen/CXX11/Tensor>

using namespace Eigen;
using namespace std;
using namespace boost::multiprecision;
typedef cpp_dec_float_50 double50;


Matrix<double50, -1, -1> ScaleFactor(Array<double50, -1, 1> Le, Matrix<double50, -1, -1> coef, Matrix<double50, -1, -1> M);
tuple<vector<Matrix<double50, -1, -1>>, vector<Matrix<double50, -1, -1>>, vector<Matrix<double50, -1, -1>>, vector<Matrix<double50, -1, -1>>> Rigid(Index NE, Matrix<double50, -1, -1> csc, MatrixXi cscc, Array<double50, -1, 1> alpha, double50 betaT, Array<double50, -1, 1> cT, Array<double50, -1, 1> cR, double50 betaR);
tuple<vector<Matrix<double50, -1, -1>>, Matrix<double50, -1, -1>, Matrix<double50, -1, -1>, vector<int>> probtune(vector<Matrix<double50, -1, -1>> coef, Matrix<double50, -1, -1> Q, Array<double50, -1, 1> Le, int t);
tuple<vector<Matrix<double50, -1, -1>>, vector<Matrix<double50, -1, -1>>, vector<Matrix<double50, -1, -1>>, ArrayXi> LW_InXD(Matrix<double50, -1, -1> csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef_s, vector<Matrix<double50, -1, -1>> coef_n, vector<Matrix<double50, -1, -1>> coef_z, vector<Matrix<double50, -1, -1>> coef_u, Array<double50, -1, 1> Le);
Matrix<double50, -1, -1> Inertia(vector<Matrix<double50, -1, -1>> coef1, vector<Matrix<double50, -1, -1>> coef2, Array<double50, -1, 1> Le);
tuple<vector<Matrix<double50, -1, -1>>, ArrayXi> WallBend(Matrix<double50, -1, -1> csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef_nWb, vector<Matrix<double50, -1, -1>> coef_n, vector<Matrix<double50, -1, -1>> coef_u, Array<double50, -1, 1> Le, int m);
Matrix<double50, -1, -1> shift(Matrix<double50, -1, -1> m1, int n);
tuple<vector<Matrix<double50, -1, -1>>, ArrayXi> NLW(Matrix<double50, -1, -1> csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef_s, vector<Matrix<double50, -1, -1>> coef_z, vector<Matrix<double50, -1, -1>> coef_u, Array<double50, -1, 1> Le);
vector<Matrix<double50, -1, -1>> nDirectional(Matrix<double50, -1, -1> csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef_s, vector<Matrix<double50, -1, -1>> coef_n);
tuple<vector<Matrix<double50, -1, -1>>, ArrayXi> ExtDist(Matrix<double50, -1, -1> csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef_s, vector<Matrix<double50, -1, -1>> coef_z, vector<Matrix<double50, -1, -1>> coef_u, Array<double50, -1, 1> Le);
Matrix<double50, -1, -1> eig(Matrix<double50, -1, -1> P, Matrix<double50, -1, -1> S);
tuple<vector<MatrixXi>, vector<MatrixXi>, vector<MatrixXi>, vector<MatrixXi>, vector<MatrixXd>, vector<MatrixXd>, VectorXd, VectorXi> sysmat(vector<MatrixXd> csc, vector<MatrixXi> cscc, vector<vector<MatrixXd>> coef_s, vector<vector<MatrixXd>> coef_n, vector<vector<MatrixXd>> coef_z, MatrixXd pnt, MatrixXi pnt_con, ArrayXi csnum, MatrixXd besz, ArrayXd t, MatrixXd enr, vector<VectorXd> zcoord, VectorXi Nel);
tuple<MatrixXi, MatrixXi, MatrixXd> Mass(MatrixXd csc, MatrixXi cscc, vector<MatrixXd> coef_s, vector<MatrixXd> coef_n, vector<MatrixXd> coef_z, double t, double L, double E, double nu, VectorXd Li1, int Neli);
tuple<MatrixXi, MatrixXi, MatrixXd> stiffness(MatrixXd csc, MatrixXi cscc, vector<MatrixXd> coef_s, vector<MatrixXd> coef_n, vector<MatrixXd> coef_z, double t, double L, double E, double nu, VectorXd Li1, int Neli);
tuple<ArrayXd, ArrayXd> LGQ(float N);
MatrixXd PSI(vector<MatrixXd> coef_s, vector<MatrixXd> coef_n, vector<MatrixXd> coef_z, int e, ArrayXd s, int d);



class Calculus
{
public:
    vector<Matrix<double50, -1, -1>> Intcoef(vector<Matrix<double50, -1, -1>> coef)
    {
        int NE = coef.size();
        Index NM = coef[0].cols(), NC = coef[0].rows();
        Array<double50, -1, 1> sp, spo;
        sp.setOnes(NC, 1);
        for (int i = 1; i < NC; i++)
        {
            sp(i, 0) = sp(i, 0) / i;
        }
        Matrix<double50, -1, -1> sp1(NC, NM);
        for (int i = 0; i < NM; i++)
        {
            sp1(all, i) = sp;
        }

        Matrix<double50, -1, -1> Icoef;
        Icoef.setZero(NC, NM);

        for (int i = 0; i < NE; i++)
        {
            Icoef.block(1, 0, NC - 1, NM) = coef[i].block(0, 0, NC - 1, NM).cwiseProduct(sp1.block(1, 0, NC - 1, NM));
            coef[i] = Icoef;
        }

        return coef;
    }
    vector<Matrix<double50, -1, -1>> Intcoef(vector<Matrix<double50, -1, -1>> coef, int n)
    {
        /*int NE = coef.size();
        Index NM = coef[0].cols(), NC = coef[0].rows();
        Order order;
        MatrixXi mo = order.ordermp(coef);
        for (int i = 0; i < mo.size(); i++)
            mo(i) = max(mo(i), 1);

        cout << mo << endl << endl;
        cout << endl;
        Matrix<double50, -1, 1> sp, spo;
        sp.setOnes(NC, 1);
        for (int i = 1;i < NC + 1;i++)
        {
            sp(i - 1, 0) = sp(i - 1, 0) / i;
        }
        Matrix<double50, -1, -1> Icoef1 = MatrixCast(coef, NC, NM * NE);
        Matrix<double50, -1, -1> Icoef2, Icoef3;
        Icoef2.setZero(NC, 1), Icoef3.setZero(NC, static_cast<Eigen::Index>(NM) * NE);
        int mm;
        for (int m = 0; m < NM; m++)
        {
            mm = mo(m);
            for (int j = 0; j < n; j++)
            {
                for (int i = 0; i < NE; i++)
                {
                    Icoef2.block(1, 0, NC - 1, 1) = (mm + j + 1) * Icoef1.block(0, static_cast<Eigen::Index>(i) * NM + m, NC - 1, 1).cwiseProduct(sp.block(0, 0, NC - 1, 1));
                    Icoef1.block(0, static_cast<Eigen::Index>(i) * NM + m, NC, 1) = Icoef2;
                }
            }
        }

        Tensor<double50, 3> Icoef = TensorCast(Icoef1, NC, NM, NE); // Cast Eigen::Matrix --> Eigen::Tensor*/

        return coef;
    }
    vector<Matrix<double50, -1, -1>> diffcoefmp(vector<Matrix<double50, -1, -1>> coef, int d)
    {
        vector<Matrix<double50, -1, -1>> Dcoef;
        if (d > 0)
        {
            int NE = coef.size();
            Index NM = coef[0].cols();
            Index NC = coef[0].rows();
            Array<double50, -1, 1> spow;
            spow.setLinSpaced(NC, 0, NC - 1);
            Matrix<double50, -1, -1> sp(NC, NM);
            for (int i = 0; i < NM; i++)
            {
                sp(all, i) = spow;
            }

            vector<Matrix<double50, -1, -1>> dcoef1 = coef, dcoef3 = coef;
            Matrix<double50, -1, -1> dcoef2;
            dcoef2.setZero(NC, NM);

            for (int i = 0; i < d; i++)
            {
                for (int j = 0; j < NE; j++)
                {
                    dcoef2.block(0, 0, NC - 1, NM) = dcoef1[j].block(1, 0, NC - 1, NM).cwiseProduct(sp.block(1, 0, NC - 1, NM));
                    dcoef1[j].block(0, 0, NC, NM) = dcoef2;
                    dcoef3[j] = dcoef2; // Check this loop
                }
            }
            Dcoef = dcoef3;
        }
        else
            Dcoef = coef;

        return Dcoef;
    }
    vector<MatrixXd> diffcoef(vector<MatrixXd> coef, int d)
    {
        vector<MatrixXd> Dcoef;
        if (d > 0)
        {
            int NE = coef.size();
            Index NM = coef[0].cols();
            Index NC = coef[0].rows();
            ArrayXd spow;
            spow.setLinSpaced(NC, 0, NC - 1);
            MatrixXd sp(NC, NM);
            for (int i = 0; i < NM; i++)
            {
                sp(all, i) = spow;
            }

            vector<MatrixXd> dcoef1 = coef, dcoef3 = coef;
            MatrixXd dcoef2;
            dcoef2.setZero(NC, NM);

            for (int i = 0; i < d; i++)
            {
                for (int j = 0; j < NE; j++)
                {
                    dcoef2.block(0, 0, NC - 1, NM) = dcoef1[j].block(1, 0, NC - 1, NM).cwiseProduct(sp.block(1, 0, NC - 1, NM));
                    dcoef1[j].block(0, 0, NC, NM) = dcoef2;
                    dcoef3[j] = dcoef2; // Check this loop
                }
            }
            Dcoef = dcoef3;
        }
        else
            Dcoef = coef;

        return Dcoef;
    }
};




class Center
{
private:
    class Rotation
    {
    public:
        Array<double50, -1, 1> Coordinates(Matrix<double50, -1, -1> csc, MatrixXi cscc, Array<double50, -1, 1> alpha, Array<double50, -1, 1> Le)
        {
            Array<double50, -1, 1> X = csc(cscc(all, 0), 0), Y = csc(cscc(all, 0), 1), cR(2, 1);
            cR(0) = (X.cwiseProduct(Le).sum() + Le.square().cwiseProduct(0.5 * cos(alpha)).sum()) / Le.sum();
            cR(1) = (Y.cwiseProduct(Le).sum() + Le.square().cwiseProduct(0.5 * sin(alpha)).sum()) / Le.sum();

            return cR;
        }
        double50 Angle(Matrix<double50, -1, -1> csc, MatrixXi cscc, Array<double50, -1, 1> alpha, Array<double50, -1, 1> Le, Array<double50, -1, 1> cR)
        {
            Array<double50, -1, 1> X = csc(cscc(all, 0), 0), Y = csc(cscc(all, 0), 1);
            Array<double50, -1, 1> xc = X - cR(0), yc = Y - cR(1);
            double50 a, b, c;
            a = yc.square().cwiseProduct(Le).sum() + Le.square().cwiseProduct(sin(alpha)).cwiseProduct(yc).sum() + Le.cube().cwiseProduct(sin(alpha).square()).sum() * 1 / 3;
            b = xc.square().cwiseProduct(Le).sum() + Le.square().cwiseProduct(cos(alpha).cwiseProduct(xc)).sum() + Le.cube().cwiseProduct(cos(alpha).square()).sum() * 1 / 3;
            c = xc.cwiseProduct(yc.cwiseProduct(Le)).sum() + Le.square().cwiseProduct(xc.cwiseProduct(sin(alpha))).sum() * 1 / 2 + Le.square().cwiseProduct(yc.cwiseProduct(cos(alpha))).sum() * 1 / 2 + Le.cube().cwiseProduct(sin(alpha).cwiseProduct(cos(alpha))).sum() * 1 / 3;

            return 0.5 * atan(2 * c / (b - a));
        }
        ArrayXd gcenter(MatrixXd csc, MatrixXi cscc, ArrayXd alpha, ArrayXd Le)
        {
            ArrayXd X = csc(cscc(all, 0), 0), Y = csc(cscc(all, 0), 1), cR(2, 1);
            cR(0) = (X.cwiseProduct(Le).sum() + Le.square().cwiseProduct(0.5 * cos(alpha)).sum()) / Le.sum();
            cR(1) = (Y.cwiseProduct(Le).sum() + Le.square().cwiseProduct(0.5 * sin(alpha)).sum()) / Le.sum();

            return cR;
        }
    };
    class Torsion
    {
    public:
        double50 Angle(Matrix<double50, -1, -1> csc, MatrixXi cscc, Array<double50, -1, 1> alpha, Array<double50, -1, 1> Le, double50 betaR)
        {
            double50 beta = 0.5 * atan2(Le.cwiseProduct(sin(2 * alpha)).sum(), Le.cwiseProduct(cos(2 * alpha)).sum());
            if (abs(cos(alpha - 0).cwiseProduct(sin(alpha - 0)).cwiseProduct(Le).sum()) < Le.sum() * 1e-14)
                beta = 0;
            else if (abs(cos(alpha - betaR).cwiseProduct(sin(alpha - betaR)).cwiseProduct(Le).sum()) < Le.sum() * 1e-14)
                beta = betaR;

            return beta;
        }
        Array<double50, -1, 1> Coordinates(Matrix<double50, -1, -1> csc, MatrixXi cscc, Array<double50, -1, 1> alpha, Array<double50, -1, 1> Le, double50 beta)
        {
            Array<double50, -1, 1> Xe = csc(cscc(all, 0), 0), Ye = csc(cscc(all, 0), 1);
            Matrix<double50, 2, 2> A1, a;
            Matrix<double50, -1, -1> A2(2, 1), b(2, 1);
            A1.setZero(), A2.setZero();
            for (int i = 0; i < cscc.rows(); i++)
            {
                a(0, 0) = Le(i) * sin(alpha(i)) * cos(alpha(i) - beta);
                a(0, 1) = -Le(i) * cos(alpha(i)) * cos(alpha(i) - beta);
                a(1, 0) = Le(i) * sin(alpha(i)) * sin(alpha(i) - beta);
                a(1, 1) = -Le(i) * cos(alpha(i)) * sin(alpha(i) - beta);

                b(0) = Le(i) * Xe(i) * sin(alpha(i)) * cos(alpha(i) - beta) - (Le(i) * Ye(i) * cos(alpha(i)) * cos(alpha(i) - beta));
                b(1) = Le(i) * Xe(i) * sin(alpha(i)) * sin(alpha(i) - beta) - (Le(i) * Ye(i) * cos(alpha(i)) * sin(alpha(i) - beta));

                A1 += a, A2 += b;
            }

            return A1.inverse() * A2;
        }
    };
public:
    Rotation Rot;
    Torsion Tor;
};


class Edge
{
private:
    Array<double50, -1, 1> var1;
    ArrayXd var2;
    Calculus operate;
public:
    Array<double50, -1, -1> Anglemp(Matrix<double50, -1, -1> csc, MatrixXi cscc)
    {
        var1.setZero(cscc.rows(), 1);
        ArrayXi e;
        for (int i = 0; i < cscc.rows(); i++)
        {
            e = cscc(i, all);
            var1(i) = atan2(csc(e(1), 1) - csc(e(0), 1), csc(e(1), 0) - csc(e(0), 0));
        }
        return var1;
    }
    ArrayXd Angle(MatrixXd csc, MatrixXi cscc)
    {
        var2.setZero(cscc.rows(), 1);
        ArrayXi e;
        for (int i = 0; i < cscc.rows(); i++)
        {
            e = cscc(i, all);
            var2(i) = atan2(csc(e(1), 1) - csc(e(0), 1), csc(e(1), 0) - csc(e(0), 0));
        }
        return var2;
    }
    Array<double50, -1, -1> Lengthmp(Matrix<double50, -1, -1> csc, MatrixXi cscc)
    {
        var1.setZero(cscc.rows(), 1);
        ArrayXi e;
        for (int i = 0; i < cscc.rows(); i++)
        {
            e = cscc(i, all);
            var1(i) = sqrt(pow((csc(e(1), 1) - csc(e(0), 1)), 2) + pow((csc(e(1), 0) - csc(e(0), 0)), 2));
        }
        return var1;
    }
    ArrayXd Length(MatrixXd csc, MatrixXi cscc)
    {
        var2.setZero(cscc.rows(), 1);
        ArrayXi e;
        for (int i = 0; i < cscc.rows(); i++)
        {
            e = cscc(i, all);
            var2(i) = sqrt(pow((csc(e(1), 1) - csc(e(0), 1)), 2) + pow((csc(e(1), 0) - csc(e(0), 0)), 2));
        }
        return var2;
    }
    Matrix<double50, -1, -1> Continuity(vector<Matrix<double50, -1, -1>> coef, int e, double50 s, int d)
    {
        Index NC = coef[0].rows(), NM = coef[0].cols();
        int NE = coef.size();
        vector<Matrix<double50, -1, -1>> dcoef = operate.diffcoefmp(coef, d);
        ArrayXi spow;
        Array<double50, -1, 1> ss;
        Matrix<double50, -1, -1> sp, fval;
        spow.setLinSpaced(NC, 0, NC - 1), ss.setOnes(NC, 1), sp.setZero(1, NC);
        ss *= s;
        for (int i = 0; i < NC; i++)
        {
            sp(i) = pow(ss(i), spow(i));
        }
        fval = sp * dcoef[e].block(0, 0, NC, NM);
        
        return fval;
    }
    MatrixXd Continuity2(vector<MatrixXd> coef, int e, ArrayXd s, int d)
    {
        int NC = coef[0].rows(), NM = coef[0].cols(), NE = coef.size(), NS = s.rows();
        vector<MatrixXd> dcoef = operate.diffcoef(coef, d);
        ArrayXi spow;
        MatrixXd fval, si(NS, NC);
        spow.setLinSpaced(NC, 0, NC - 1), si.setZero();
        for (int i = 0; i < NC; i++)
        {
            for (int j = 0; j < NS; j++)
                si(j, i) = pow(s(j), spow(i));
        }
        fval = si * dcoef[e].block(0, 0, NC, NM);
        return fval;
    }
};


class Continuity
{
public:
    tuple<vector<vector<int>>, vector<Matrix<double50, -1, -1>>, vector<Array<double50, -1, 1>>> Edges(Matrix<double50, -1, -1>  csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef, int t)
    {
        Index NC = csc.rows(), NM = coef[0].cols();
        Array<double50, -1, 1> alpha, Le, sc;
        VectorXi rng_r(2), edgv, rng_s;
        Edge edge;
        alpha = edge.Anglemp(csc, cscc);
        Le = edge.Lengthmp(csc, cscc);
        Matrix<double50, -1, -1> cont_cond{}, Z(Le.rows(), 1), f1, f2, f3, C, T(2, 2), Rxyf(2, NM), Rxy, Uxyf(2, NM), Uxy, temp1(1, 2), c0, c1, c2;
        vector<vector<int>> cont_edg;
        vector<Matrix<double50, -1, -1>> cont_Rxy;
        vector<Array<double50, -1, 1>> cont_sc;
        Z.setZero();
        vector<int> edg;
        vector<double50> ss;
        int count1 = 0, count2 = 0, count4;

        for (int i = 0; i < NC; i++)
        {
            edg.clear();
            ss.clear();
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < cscc.rows(); k++)
                {
                    if (cscc(k, j) == i)
                    {
                        edg.push_back(k);
                    }
                }
                if (j == 0)
                {
                    for (int k = 0; k < edg.size(); k++)
                    {
                        ss.push_back(Z(edg[k]));
                    }
                    count4 = ss.size();
                }
                else if (j == 1)
                    for (int k = count4; k < edg.size(); k++)
                    {
                        ss.push_back(Le(edg[k]));
                    }
            }
            sc.setZero(ss.size());
            for (int k = 0; k < ss.size(); k++)
                sc(k) = ss[k];
            cont_edg.push_back(edg);
            cont_sc.push_back(sc);
            if (t == 0) // OUT OF PLANE MODES
            {
                if (edg.size() > 1)
                {
                    count1 += edg.size() - 1;
                    cont_cond.conservativeResize(count1, NM);
                    for (int j = 0; j < edg.size() - 1; j++)
                    {
                        f1 = edge.Continuity(coef, edg[j], sc(j), 0);
                        f2 = edge.Continuity(coef, edg[static_cast<std::vector<int, std::allocator<int>>::size_type>(j) + 1], sc(static_cast<Eigen::Index>(j) + 1), 0);
                        cont_cond(count2, all) = f1 - f2;
                        count2++;
                    }
                }
                // Corner Angle Rotation
                if (edg.size() > 2)
                {
                    if (abs(sin(alpha(edg[0]) - alpha(edg[1]))) < 1E-10)
                        rng_r << 0, 2;
                    else
                        rng_r << 0, 1;

                    f1 = edge.Continuity(coef, edg[rng_r(0)], sc(rng_r(0)), 1);
                    f2 = edge.Continuity(coef, edg[rng_r(1)], sc(rng_r(1)), 1);
                    T << cos(alpha(edg[rng_r(1)])), -cos(alpha(edg[rng_r(0)])),
                        sin(alpha(edg[rng_r(1)])), -sin(alpha(edg[rng_r(0)]));
                    T = T / (sin(alpha(edg[rng_r(0)]) - alpha(edg[rng_r(1)])));
                    Rxyf(0, all) = f1, Rxyf(1, all) = f2;
                    Rxy = T * Rxyf;

                    cont_Rxy.push_back(Rxy);
                }
                else if (edg.size() == 2)
                {
                    f1 = edge.Continuity(coef, edg[0], sc(0), 1);
                    f2 = edge.Continuity(coef, edg[1], sc(1), 1);
                    T(0, 0) = cos(alpha(edg[1]));
                    T(0, 1) = -cos(alpha(edg[0]));
                    T(1, 0) = sin(alpha(edg[1]));
                    T(1, 1) = -sin(alpha(edg[0]));
                    T = T / (sin(alpha(edg[0]) - alpha(edg[1])));
                    Rxyf(0, all) = f1, Rxyf(1, all) = f2;
                    Rxy = T * Rxyf;


                    cont_Rxy.push_back(Rxy);
                }
            }
            else if (t == 1) // IN-PLANE MODES
            {
                if (edg.size() > 2)
                {
                    if (abs(sin(alpha(edg[0]) - alpha(edg[1]))) < 1E-10)
                        rng_r << 0, 2;
                    else
                        rng_r << 0, 1;

                    edgv.setZero(edg.size());
                    rng_s.setZero(edgv.size());

                    for (int j = 0; j < edg.size(); j++)
                        edgv(j) = j;

                    sort(edgv.begin(), edgv.end());
                    VectorXi::iterator it;//?

                    it = set_difference(edgv.begin(), edgv.end(), rng_r.begin(), rng_r.end(), rng_s.begin());
                    rng_s.conservativeResize(it - rng_s.begin());

                    f1 = edge.Continuity(coef, edg[rng_r(0)], sc(rng_r(0)), 0);
                    f2 = edge.Continuity(coef, edg[rng_r(1)], sc(rng_r(1)), 0);
                    T(0, 0) = -sin(alpha(edg[rng_r(1)]));
                    T(0, 1) = sin(alpha(edg[rng_r(0)]));
                    T(1, 0) = cos(alpha(edg[rng_r(1)]));
                    T(1, 1) = -cos(alpha(edg[rng_r(0)]));
                    T = T / (sin(alpha(edg[rng_r(0)]) - alpha(edg[rng_r(1)])));
                    Uxyf(0, all) = f1, Uxyf(1, all) = f2;
                    Uxy = T * Uxyf;

                    cont_Rxy.push_back(Uxy);
                    count1 += rng_s.size();
                    cont_cond.conservativeResize(count1, NM);

                    for (int j = 0; j < rng_s.size(); j++)
                    {
                        f3 = edge.Continuity(coef, edg[rng_s(j)], sc(rng_s(j)), 0);
                        temp1 << cos(alpha(edg[rng_s(j)])), sin(alpha(edg[rng_s(j)]));
                        cont_cond(count2, all) = f3 - temp1 * Uxy;
                        count2++;
                    }
                }
                else if (edg.size() == 2)
                {
                    f1 = edge.Continuity(coef, edg[0], sc(0), 0);
                    f2 = edge.Continuity(coef, edg[1], sc(1), 0);
                    T(0, 0) = -sin(alpha(edg[1]));
                    T(0, 1) = sin(alpha(edg[0]));
                    T(1, 0) = cos(alpha(edg[1]));
                    T(1, 1) = -cos(alpha(edg[0]));
                    T = T / (sin(alpha(edg[0]) - alpha(edg[1])));
                    Uxyf(0, all) = f1, Uxyf(1, all) = f2;
                    Uxy = T * Uxyf;

                    cont_Rxy.push_back(Uxy);
                }
            }
            else if (t == 2)// WALL BENDING MODES
            {
                if (edg.size() == 1)
                {
                    C = edge.Continuity(coef, edg[0], sc(0), 2);
                }
                else
                {
                    C.setZero(2 * edg.size(), NM);
                    c0.setZero(edg.size(), NM);
                    for (int j = 0; j < edg.size(); j++)
                    {
                        c0(j, all) = edge.Continuity(coef, edg[j], sc(j), 0);
                    }

                    c1.setZero(edg.size() - 1, NM);
                    for (int j = 0; j < edg.size() - 1; j++)
                    {
                        for (int k = 0; k < 2; k++)
                            c1(j, all) += edge.Continuity(coef, edg[j + k], sc(j + k), 1) * pow(-1, k);
                    }

                    c2.setZero(1, NM);
                    for (int j = 0; j < edg.size(); j++)
                    {
                        if (sc(j) == 0)
                            c2 += edge.Continuity(coef, edg[j], sc[j], 2) * (-1);
                        else
                            c2 += edge.Continuity(coef, edg[j], sc[j], 2);
                    }
                    C.block(0, 0, edg.size(), NM) = c0;
                    C.block(edg.size(), 0, edg.size() - 1, NM) = c1;
                    C.block(edg.size() + edg.size() - 1, 0, 1, NM) = c2;
                }
                count1 += C.rows();
                cont_cond.conservativeResize(count1, NM);
                cont_cond.block(count1 - C.rows(), 0, C.rows(), NM) = C;
            }
        }

        return make_tuple(cont_edg, cont_Rxy, cont_sc);
    }

    Matrix<double50, -1, -1> Constraint(Matrix<double50, -1, -1>  csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef, int t)
    {
        Index NC = csc.rows(), NM = coef[0].cols();
        Array<double50, -1, 1> alpha, Le, sc;
        VectorXi rng_r(2), edgv, rng_s;
        Edge edge;
        alpha = edge.Anglemp(csc, cscc);
        Le = edge.Lengthmp(csc, cscc);
        Matrix<double50, -1, -1> cont_cond{}, Z(Le.rows(), 1), f1, f2, f3, C, T(2, 2), Rxyf(2, NM), Rxy, Uxyf(2, NM), Uxy, temp1(1, 2), c0, c1, c2;
        vector<vector<int>> cont_edg;
        vector<Matrix<double50, -1, -1>> cont_Rxy;
        vector<Array<double50, -1, 1>> cont_sc;
        Z.setZero();
        vector<int> edg;
        vector<double50> ss;
        int count1 = 0, count2 = 0, count4;

        for (int i = 0; i < NC; i++)
        {
            edg.clear();
            ss.clear();
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < cscc.rows(); k++)
                {
                    if (cscc(k, j) == i)
                    {
                        edg.push_back(k);
                    }
                }
                if (j == 0)
                {
                    for (int k = 0; k < edg.size(); k++)
                    {
                        ss.push_back(Z(edg[k]));
                    }
                    count4 = ss.size();
                }
                else if (j == 1)
                    for (int k = count4; k < edg.size(); k++)
                    {
                        ss.push_back(Le(edg[k]));
                    }
            }
            sc.setZero(ss.size());
            for (int k = 0; k < ss.size(); k++)
                sc(k) = ss[k];
            cont_edg.push_back(edg);
            cont_sc.push_back(sc);
            if (t == 0) // OUT OF PLANE MODES
            {
                if (edg.size() > 1)
                {
                    count1 += edg.size() - 1;
                    cont_cond.conservativeResize(count1, NM);
                    for (int j = 0; j < edg.size() - 1; j++)
                    {
                        f1 = edge.Continuity(coef, edg[j], sc(j), 0);
                        f2 = edge.Continuity(coef, edg[static_cast<std::vector<int, std::allocator<int>>::size_type>(j) + 1], sc(static_cast<Eigen::Index>(j) + 1), 0);
                        cont_cond(count2, all) = f1 - f2;
                        count2++;
                    }
                }
                // Corner Angle Rotation
                if (edg.size() > 2)
                {
                    if (abs(sin(alpha(edg[0]) - alpha(edg[1]))) < 1E-10)
                        rng_r << 0, 2;
                    else
                        rng_r << 0, 1;

                    f1 = edge.Continuity(coef, edg[rng_r(0)], sc(rng_r(0)), 1);
                    f2 = edge.Continuity(coef, edg[rng_r(1)], sc(rng_r(1)), 1);
                    T << cos(alpha(edg[rng_r(1)])), -cos(alpha(edg[rng_r(0)])),
                        sin(alpha(edg[rng_r(1)])), -sin(alpha(edg[rng_r(0)]));
                    T = T / (sin(alpha(edg[rng_r(0)]) - alpha(edg[rng_r(1)])));
                    Rxyf(0, all) = f1, Rxyf(1, all) = f2;
                    Rxy = T * Rxyf;

                    cont_Rxy.push_back(Rxy);
                }
                else if (edg.size() == 2)
                {
                    f1 = edge.Continuity(coef, edg[0], sc(0), 1);
                    f2 = edge.Continuity(coef, edg[1], sc(1), 1);
                    T(0, 0) = cos(alpha(edg[1]));
                    T(0, 1) = -cos(alpha(edg[0]));
                    T(1, 0) = sin(alpha(edg[1]));
                    T(1, 1) = -sin(alpha(edg[0]));
                    T = T / (sin(alpha(edg[0]) - alpha(edg[1])));
                    Rxyf(0, all) = f1, Rxyf(1, all) = f2;
                    Rxy = T * Rxyf;

                    cont_Rxy.push_back(Rxy);
                }
            }
            else if (t == 1) // IN-PLANE MODES
            {
                if (edg.size() > 2)
                {
                    if (abs(sin(alpha(edg[0]) - alpha(edg[1]))) < 1E-10)
                        rng_r << 0, 2;
                    else
                        rng_r << 0, 1;

                    edgv.setZero(edg.size());
                    rng_s.setZero(edgv.size());

                    for (int j = 0; j < edg.size(); j++)
                        edgv(j) = j;

                    sort(edgv.begin(), edgv.end());
                    VectorXi::iterator it;

                    it = set_difference(edgv.begin(), edgv.end(), rng_r.begin(), rng_r.end(), rng_s.begin());
                    rng_s.conservativeResize(it - rng_s.begin());

                    f1 = edge.Continuity(coef, edg[rng_r(0)], sc(rng_r(0)), 0);
                    f2 = edge.Continuity(coef, edg[rng_r(1)], sc(rng_r(1)), 0);
                    T(0, 0) = -sin(alpha(edg[rng_r(1)]));
                    T(0, 1) = sin(alpha(edg[rng_r(0)]));
                    T(1, 0) = cos(alpha(edg[rng_r(1)]));
                    T(1, 1) = -cos(alpha(edg[rng_r(0)]));
                    T = T / (sin(alpha(edg[rng_r(0)]) - alpha(edg[rng_r(1)])));
                    Uxyf(0, all) = f1, Uxyf(1, all) = f2;
                    Uxy = T * Uxyf;

                    cont_Rxy.push_back(Uxy);
                    count1 += rng_s.size();
                    cont_cond.conservativeResize(count1, NM);

                    for (int j = 0; j < rng_s.size(); j++)
                    {
                        f3 = edge.Continuity(coef, edg[rng_s(j)], sc(rng_s(j)), 0);
                        temp1 << cos(alpha(edg[rng_s(j)])), sin(alpha(edg[rng_s(j)]));
                        cont_cond(count2, all) = f3 - temp1 * Uxy;
                        count2++;
                    }
                }
                else if (edg.size() == 2)
                {
                    f1 = edge.Continuity(coef, edg[0], sc(0), 0);
                    f2 = edge.Continuity(coef, edg[1], sc(1), 0);
                    T(0, 0) = -sin(alpha(edg[1]));
                    T(0, 1) = sin(alpha(edg[0]));
                    T(1, 0) = cos(alpha(edg[1]));
                    T(1, 1) = -cos(alpha(edg[0]));
                    T = T / (sin(alpha(edg[0]) - alpha(edg[1])));
                    Uxyf(0, all) = f1, Uxyf(1, all) = f2;
                    Uxy = T * Uxyf;

                    cont_Rxy.push_back(Uxy);
                }
            }
            else if (t == 2)// WALL BENDING MODES
            {
                if (edg.size() == 1)
                {
                    C = edge.Continuity(coef, edg[0], sc(0), 2);
                }
                else
                {
                    C.setZero(2 * edg.size(), NM);
                    c0.setZero(edg.size(), NM);
                    for (int j = 0; j < edg.size(); j++)
                    {
                        c0(j, all) = edge.Continuity(coef, edg[j], sc(j), 0);
                    }

                    c1.setZero(edg.size() - 1, NM);
                    for (int j = 0; j < edg.size() - 1; j++)
                    {
                        for (int k = 0; k < 2; k++)
                            c1(j, all) += edge.Continuity(coef, edg[j + k], sc(j + k), 1) * pow(-1, k);
                    }

                    c2.setZero(1, NM);
                    for (int j = 0; j < edg.size(); j++)
                    {
                        if (sc(j) == 0)
                            c2 += edge.Continuity(coef, edg[j], sc[j], 2) * (-1);
                        else
                            c2 += edge.Continuity(coef, edg[j], sc[j], 2);
                    }
                    C.block(0, 0, edg.size(), NM) = c0;
                    C.block(edg.size(), 0, edg.size() - 1, NM) = c1;
                    C.block(edg.size() + edg.size() - 1, 0, 1, NM) = c2;
                }
                count1 += C.rows();
                cont_cond.conservativeResize(count1, NM);
                cont_cond.block(count1 - C.rows(), 0, C.rows(), NM) = C;
            }
        }

        return cont_cond;
    }
};

class Extract
{
public:
    int CrossSection(string str)
    {
        stringstream ss;
        string temp;
        ss << str;
        int found = 0;
        while (found == 0) {
            ss >> temp;
            if (temp.length() > 0) {
                if (stringstream(temp) >> found) {}
                temp = "";
            }
        }
        return found;
    }

    RowVector2d EdgeLandT(string str)
    {
        stringstream ss;
        string temp;
        /* Storing the whole string into string stream */
        ss << str;

        /* Running loop till the end of the stream */
        RowVector2d found; found.setZero();
        int si = 0;
        while (!ss.eof()) {

            /* extracting word by word from stream */
            ss >> temp;

            /* Checking the given word is integer or not */
            if (temp.length() > 0) {
                if (stringstream(temp) >> found(si)) {
                    //cout << found << " ";
                    si++;
                }
            }
            /* To save from space at the end of string */
            temp = "";
        }

        return found;
    }

    RowVector4d Nodes(string str)
    {
        stringstream ss;
        string temp;
        ss << str;
        RowVector4d found; found.setZero();
        int si = 0;
        while (!ss.eof()) {
            ss >> temp;
            if (temp.length() > 0) {
                if (stringstream(temp) >> found(si)) {
                    si++;
                }
            }
            temp = "";
        }
        return found;
    }

    RowVector3i CSMandM(string str)
    {
        stringstream ss;
        string temp;
        ss << str;
        RowVector3i found; found.setZero();
        int si = 0;
        while (!ss.eof()) {
            ss >> temp;
            if (temp.length() > 0) {
                if (stringstream(temp) >> found(si)) {
                    si++;
                }
            }
            temp = "";
        }
        return found;
    }

    RowVector3d BCs(string str)
    {
        stringstream ss;
        string temp;
        ss << str;
        RowVector3d found; found.setZero();
        int si = 0;
        while (!ss.eof()) {
            ss >> temp;
            if (temp.length() > 0) {
                if (stringstream(temp) >> found(si)) {
                    si++;
                }
            }
            temp = "";
        }
        return found;
    }

    RowVector4d Material(string str)
    {
        stringstream ss;
        string temp;
        ss << str;
        RowVector4d found; found.setZero();
        int si = 0;
        while (!ss.eof()) {
            ss >> temp;
            if (temp.length() > 0) {
                if (stringstream(temp) >> found(si)) {
                    si++;
                }
            }
            temp = "";
        }
        return found;
    }

    RowVectorXd UserCross(string str)
    {
        stringstream ss;
        string temp;
        ss << str;
        RowVectorXd found; found.setZero(6);
        int si = 0;
        while (!ss.eof()) {
            ss >> temp;
            if (temp.length() > 0) {
                if (stringstream(temp) >> found(si)) {
                    si++;
                }
            }
            temp = "";
        }
        return found;
    }

    RowVectorXd Elements(string str)
    {
        stringstream ss;
        string temp;
        ss << str;
        RowVectorXd found; found.setZero(7);
        int si = 0;
        while (!ss.eof()) {
            ss >> temp;
            if (temp.length() > 0) {
                if (stringstream(temp) >> found(si)) {
                    si++;
                }
            }
            temp = "";
        }
        return found;
    }

    RowVectorXd Joint(string str)
    {
        stringstream ss;
        string temp;
        ss << str;
        RowVectorXd found; found.setZero(6);
        int si = 0;
        while (!ss.eof()) {
            ss >> temp;
            if (temp.length() > 0) {
                if (stringstream(temp) >> found(si)) {
                    si++;
                }
            }
            temp = "";
        }
        return found;
    }

    RowVectorXd Forces(string str, int n)
    {
        stringstream ss;
        string temp;
        ss << str;
        RowVectorXd found; found.setZero(n);
        int si = 0;
        while (!ss.eof()) {
            ss >> temp;
            if (temp.length() > 0) {
                if (stringstream(temp) >> found(si)) {
                    si++;
                }
            }
            temp = "";
        }
        return found;
    }
};
class Cross_Section
{
public:
    Vector<double50, -1> EdgeLength(Matrix<double50, -1, -1> csc, MatrixXi cscc)
    {
        Vector<double50, -1> Le;
        VectorXi e;
        Le.setZero(cscc.rows());
        for (int i = 0; i < cscc.rows(); i++)
        {
            e = cscc(i, all);
            Le(i) = sqrt(pow((csc(e(1), 1) - csc(e(0), 1)), 2) + pow((csc(e(1), 0) - csc(e(0), 0)), 2));
        }
        return Le;
    }
    Vector<double50, -1> EdgeAngle(Matrix<double50, -1, -1> csc, MatrixXi cscc)
    {
        Vector<double50, -1> alpha;
        VectorXi e;
        alpha.setZero(cscc.rows());
        for (int i = 0; i < cscc.rows(); i++)
        {
            e = cscc(i, all);
            alpha(i) = atan2(csc(e(1), 1) - csc(e(0), 1), csc(e(1), 0) - csc(e(0), 0));
        }
        return alpha;
    }
};

void removeRow(Eigen::MatrixXi& matrix, unsigned int rowToRemove)
{
    unsigned int numRows = matrix.rows() - 1;
    unsigned int numCols = matrix.cols();

    if (rowToRemove < numRows)
        matrix.block(rowToRemove, 0, numRows - rowToRemove, numCols) = matrix.block(rowToRemove + 1, 0, numRows - rowToRemove, numCols);

    matrix.conservativeResize(numRows, numCols);
}


tuple<vector<MatrixXd>, vector<MatrixXd>, vector<MatrixXd>, MatrixXi> Modegen(Matrix<cpp_dec_float_50, -1, -1> csc, MatrixXi cscc, int Mset, MatrixXi settab)
{
    Matrix<double50, -1, -1> cR, cT;
    Array<double50, -1, 1> alpha, Le;
    double50 betaR, betaT;
    ArrayXi stw, stx, ste;
    Edge edge;
    Center center;
    Index NE = cscc.rows();
    Tensor<double, 3> pp1, pp2, pp3;
    cout << "213412341234\n";
    alpha = edge.Anglemp(csc, cscc); // 각도 계산
    Le = edge.Lengthmp(csc, cscc); // 거리계싼
    cR = center.Rot.Coordinates(csc, cscc, alpha, Le); // 회전 좌표 계산
    betaR = center.Rot.Angle(csc, cscc, alpha, Le, cR); // 회전 각 계산
    betaT = center.Tor.Angle(csc, cscc, alpha, Le, betaR); // 토크 각 계산
    cT = center.Tor.Coordinates(csc, cscc, alpha, Le, betaT); // 토크 좌표 계산
    vector<Matrix<double50, -1, -1>> coef_s, coef_n, coef_z, coef_u, coef_ssb, coef_nnb;
    coef_ssb.resize(NE), coef_nnb.resize(NE);
    cout << "awegagawgawega\n";
    tie(coef_s, coef_n, coef_z, coef_u) = Rigid(NE, csc, cscc, alpha, betaT, cT, cR, betaR);// 강체모드
    settab(0, all) << 1, 3, 0;
    cout << "wg51a65eg16w\n";
    for (int i = 0; i < Mset; i++)
    {
        if (i == 0)
            tie(coef_s, coef_n, coef_z, stw) = LW_InXD(csc, cscc, coef_s, coef_n, coef_z, coef_u, Le);
        else
            std::tie(coef_z, stw) = NLW(csc, cscc, coef_s, coef_z, coef_u, Le);

        tie(coef_s, stx) = ExtDist(csc, cscc, coef_s, coef_z, coef_u, Le);
        coef_n = nDirectional(csc, cscc, coef_s, coef_n);

        tie(coef_nnb, ste) = WallBend(csc, cscc, coef_nnb, coef_n, coef_u, Le, i);

        settab(i + 1, all) = stw.transpose() + stx.transpose() + ste.transpose();
    }

    Index NMs = coef_s[0].cols(), NMswb = coef_nnb[0].cols(), NC = coef_s[0].rows(), NMz = coef_z[0].cols();
    vector<MatrixXd> Cs, Cn, Cz; Cs.resize(NE), Cn.resize(NE), Cz.resize(NE);

    for (int i = 0; i < NE; i++)
    {
        coef_s[i].conservativeResize(NC, NMs + NMswb);
        coef_n[i].conservativeResize(NC, NMs + NMswb);

        coef_s[i].block(0, NMs, NC, NMswb).setZero();
        coef_n[i].block(0, NMs, NC, NMswb) = coef_nnb[i];
        Cs[i].setZero(NC, NMs + NMswb);
        Cn[i].setZero(NC, NMs + NMswb);
        Cz[i].setZero(NC, NMz);
    }

    for (int i = 0; i < NE; i++)
    {
        for (int j = 0; j < NC; j++)
        {
            for (int k = 0; k < NMs + NMswb; k++)
            {
                Cs[i](j, k) = static_cast<double>(coef_s[i](j, k));
                Cn[i](j, k) = static_cast<double>(coef_n[i](j, k));
            }
            for (int k = 0; k < NMz; k++)
                Cz[i](j, k) = static_cast<double>(coef_z[i](j, k));
        }
    }

    return make_tuple(Cs, Cn, Cz, settab);
}

tuple<vector<Matrix<double50, -1, -1>>, vector<Matrix<double50, -1, -1>>, vector<Matrix<double50, -1, -1>>, vector<Matrix<double50, -1, -1>>> Rigid(Index NE, Matrix<double50, -1, -1> csc, MatrixXi cscc, Array<double50, -1, 1> alpha, double50 betaT, Array<double50, -1, 1> cT, Array<double50, -1, 1> cR, double50 betaR)
{
    std::cout << "Deriving Rigid Body Modes" << endl << endl;
    int order = 25;
    //Tensor<double50, 3> coef_s(order + 1, 3, NE), coef_n(order + 1, 3, NE), coef_z(order + 1, 3, NE), coef_u(order + 1, NE, NE);
    vector<Matrix<double50, -1, -1>> coef_s, coef_n, coef_z, coef_u;
    coef_s.resize(NE), coef_n.resize(NE), coef_z.resize(NE), coef_u.resize(NE);
    for (int i = 0; i < NE; i++)
    {
        coef_s[i].setZero(order + 1, 3);
        coef_n[i].setZero(order + 1, 3);
        coef_z[i].setZero(order + 1, 3);
        coef_u[i].setZero(order + 1, NE);
    }
    Vector<double50, -1> Xi, Yi;
    Xi = csc(cscc(all, 0), 0), Yi = csc(cscc(all, 0), 1);
    for (int i = 0; i < NE; i++)
    {
        coef_s[i](0, 0) = cos(alpha(i) - betaT); // 각도 - 토크각
        coef_s[i](0, 1) = sin(alpha(i) - betaT); 
        coef_s[i](0, 2) = (Xi(i) - cT(0)) * sin(alpha(i)) - (Yi(i) - cT(1)) * cos(alpha(i)); //(x좌표 - 토크 x좌표) * 사인(각도)-(y좌표 - 토크y좌표)*코사인(각도)

        coef_n[i](0, 0) = sin(alpha(i) - betaT);
        coef_n[i](0, 1) = -cos(alpha(i) - betaT);
        coef_n[i](0, 2) = -(Xi(i) - cT(0)) * cos(alpha(i)) - (Yi(i) - cT(1)) * sin(alpha(i));
        coef_n[i](1, 2) = double50(-1);

        coef_z[i](0, 0) = 1;
        coef_z[i](0, 1) = -(Xi(i) - cR(0)) * sin(betaR) + (Yi(i) - cR(1)) * cos(betaR);
        coef_z[i](0, 2) = -(Xi(i) - cR(0)) * cos(betaR) - (Yi(i) - cR(1)) * sin(betaR);
        coef_z[i](1, 1) = sin(alpha(i) - betaR);
        coef_z[i](1, 2) = -cos(alpha(i) - betaR);

        coef_u[i](0, i) = double50(1);
    }
    std::cout << "Rigid Body Modes Derived" << endl << endl;
    return make_tuple(coef_s, coef_n, coef_z, coef_u);
}

tuple<vector<Matrix<double50, -1, -1>>, vector<Matrix<double50, -1, -1>>, vector<Matrix<double50, -1, -1>>, ArrayXi> LW_InXD(Matrix<double50, -1, -1> csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef_s, vector<Matrix<double50, -1, -1>> coef_n, vector<Matrix<double50, -1, -1>> coef_z, vector<Matrix<double50, -1, -1>> coef_u, Array<double50, -1, 1> Le)
{
    std::cout << "Deriving Linear Warping and In-Extensional Distortion Modes" << endl << endl;
    Index NE = cscc.rows(), NC = coef_s[0].rows(), NMs = coef_s[0].cols(), NMu = coef_u[0].cols(), NMz = coef_z[0].cols();
    int count1 = 0;

    ArrayXi stw(3); stw.setZero();
    Matrix<double50, -1, -1>  C, eye;
    vector<Matrix<double50, -1, -1>> Phi_W, w1, w2; Phi_W.resize(NE);
    Calculus operate;
    Continuity cont;

    C.setZero(NE, (2 * NMu + NMs)), eye.setIdentity(NE, NE);
    C.block(0, NMu, NE, NE) = eye;
    w1 = operate.Intcoef(coef_s), w2 = operate.Intcoef(coef_u);

    for (int i = 0; i < NE; i++)
    {
        Phi_W[i].setZero(NC, 2 * NMu + NMs);

        Phi_W[i].block(0, 0, NC, NMu) = coef_u[i];
        Phi_W[i].block(0, NMu, NC, NMu) = w2[i];
        Phi_W[i].block(0, 2 * NMu, NC, NMs) = w1[i];
    }
    Matrix<double50, -1, -1> Pw = Inertia(Phi_W, Phi_W, Le);
    Matrix<double50, -1, -1> Qx = Inertia(coef_s, coef_u, Le) * C;
    Matrix<double50, -1, -1> Qw = Inertia(coef_z, Phi_W, Le);

    vector<vector<int>> cont_edg;
    vector<Matrix<double50, -1, -1>> cont_Rxy;
    vector<Array<double50, -1, 1>> cont_sc;
    Matrix<double50, -1, -1> Rw, Rx;

    tie(cont_edg, cont_Rxy, cont_sc) = cont.Edges(csc, cscc, Phi_W, 0);
    Rw = cont.Constraint(csc, cscc, Phi_W, 0);
    Rx = cont.Constraint(csc, cscc, coef_u, 1);
    
    Matrix<double50, -1, -1> S0, S, Si, x_w;
    vector<int> c, d;

    if (Rx.size() == 0)
    {
        S0.setZero(Qw.rows() + Qx.rows() + Rw.rows(), Qw.cols());
        S0.block(0, 0, Qw.rows(), Qw.cols()) = Qw;
        S0.block(Qw.rows(), 0, Qx.rows(), Qw.cols()) = Qx;
        S0.block(Qw.rows() + Qx.rows(), 0, Rw.rows(), Qw.cols()) = Rw;
    }
    else
    {
        S0.setZero(Qw.rows() + Qx.rows() + Rw.rows() + Rx.rows(), Qw.cols());
        S0.block(0, 0, Qw.rows(), Qw.cols()) = Qw;
        S0.block(Qw.rows(), 0, Qx.rows(), Qw.cols()) = Qx;
        S0.block(Qw.rows() + Qx.rows(), 0, Rw.rows(), Qw.cols()) = Rw;
        S0.block(Qw.rows() + Qx.rows() + Rw.rows(), 0, Rx.rows(), Qw.cols()) = Rx * C;
    }


    Si.setZero(S0.rows(), S0.cols());
    S.setZero(S0.rows(), S0.cols());
    for (int i = 0; i < S0.rows(); i++)
    {
        Si.block(0, 0, count1, S.cols()) = S.block(0, 0, count1, S.cols());
        Si.block(count1, 0, 1, S0.cols()) = S0(i, all);
        FullPivLU<Matrix<double50, -1, -1>> Lu1(Si);
        FullPivLU<Matrix<double50, -1, -1>> Lu2(S);
        if (Lu1.rank() > Lu2.rank())
        {
            S.block(0, 0, count1 + 1, S0.cols()) = Si.block(0, 0, count1 + 1, S0.cols());
            count1++;
        }
    }


    // ######## Linear Warping ######## \\

    std::tie(Phi_W, Pw, x_w, c) = probtune(Phi_W, S, Le, coef_u[0].cols());
    

    //phi_w = MatrixCast(Phi_W, NC, (2 * NMu + NMs) * NE);

    //std::cout << "No. of LW Modes: " << x_w.cols() << endl << endl;
    stw(0) += x_w.cols();
    Matrix<double50, -1, -1> sfw = ScaleFactor(Le, x_w, Pw);

    Matrix<double50, -1, -1> coef_zi;
    coef_zi.setZero(NC, x_w.cols() * NE);
    for (int i = 0; i < NE; i++)
    {
        coef_z[i].conservativeResize(NC, NMz + x_w.cols());
        coef_z[i].block(0, NMz, NC, x_w.cols()) = Phi_W[i] * x_w * sfw;
    }

    // ######## In-Extensional Distortion ######## \\

    Array<double50, -1, 1> wi, di;
    for (int i = 0; i < x_w.cols(); i++)
    {
        wi = x_w(all, i);
        di = x_w(c, i);
        if (wi.abs().maxCoeff() < di.abs().maxCoeff() * 1e5)
            d.push_back(i);
    }

    if (d.size() > 0)
    {
        Matrix<double50, -1, -1> rev_ed1 = x_w(c, d);
        Matrix<double50, -1, -1> Ped1 = Inertia(coef_u, coef_u, Le);
        Matrix<double50, -1, -1> sfed1 = ScaleFactor(Le, rev_ed1, Ped1);
        vector<Matrix<double50, -1, -1>> coef_si; coef_si.resize(NE);
        for (int i = 0; i < NE; i++)
        {
            coef_si[i].setZero(NC, x_w.cols());
            coef_si[i] = coef_u[i] * rev_ed1 * sfed1;
        }

        Matrix<double50, -1, -1> Ped2 = Inertia(coef_si, coef_si, Le);
        Matrix<double50, -1, -1> Semp;
        Matrix<double50, -1, -1> evec_ed = eig(Ped2, Semp);

        Matrix<double50, -1, -1> sfed2 = ScaleFactor(Le, evec_ed, Ped2);

        for (int i = 0; i < NE; i++)
        {
            coef_s[i].conservativeResize(NC, NMs + evec_ed.cols());
            coef_s[i].block(0, NMs, NC, evec_ed.cols()) = coef_si[i] * evec_ed * sfed2;
        }

        //std::cout << "No. of InExtDist Modes: " << evec_ed.cols() << endl << endl;
        stw(1) = evec_ed.cols();

        coef_n = nDirectional(csc, cscc, coef_s, coef_n);
    }
    /*else
        std::cout << "No. of InExtDist Modes: " << 0 << endl;

    std::cout << "Linear Warping and In-Extensional Distortion Modes Derived" << endl << endl;*/


    cout << "end LW_InXD ----------------------------------------------------------------------------------------------\n\n";
    return make_tuple(coef_s, coef_n, coef_z, stw);
}


tuple<vector<Matrix<double50, -1, -1>>, ArrayXi> ExtDist(Matrix<double50, -1, -1> csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef_s, vector<Matrix<double50, -1, -1>> coef_z, vector<Matrix<double50, -1, -1>> coef_u, Array<double50, -1, 1> Le)
{
    std::cout << "Deriving Extensional Distortion Modes" << endl << endl;
    int NE = Le.rows();
    Index NMz = coef_z[0].cols(), NMs = coef_s[0].cols(), NMu = coef_u[0].cols(), NC = coef_s[0].rows();
    int count1 = 0;
    Matrix<double50, -1, -1> Rx;
    ArrayXi stx(3); stx.setZero();
    Calculus operate;
    Continuity cont;

    vector<Matrix<double50, -1, -1>> w1 = operate.Intcoef(coef_z), Phi_X;
    Phi_X.resize(NE);
    vector<int> c;

    for (int i = 0; i < NE; i++)
    {
        Phi_X[i].setZero(NC, NMz + NMu);

        Phi_X[i].block(0, NMu, NC, NMz) = w1[i];
        Phi_X[i].block(0, 0, NC, NMu) = coef_u[i];
    }

    Matrix<double50, -1, -1> Px = Inertia(Phi_X, Phi_X, Le);
    Matrix<double50, -1, -1> Qx = Inertia(coef_s, Phi_X, Le);
    Rx = cont.Constraint(csc, cscc, Phi_X, 1);

    Matrix<double50, -1, -1> S0, Si, S;
    S0.setZero(Qx.rows() + Rx.rows(), Qx.cols());
    S0.block(0, 0, Qx.rows(), Qx.cols()) = Qx;
    S0.block(Qx.rows(), 0, Rx.rows(), Rx.cols()) = Rx;

    Si.setZero(S0.rows(), S0.cols());
    S.setZero(S0.rows(), S0.cols());
    for (int i = 0; i < S0.rows(); i++)
    {
        Si.block(0, 0, count1, S.cols()) = S.block(0, 0, count1, S.cols());
        Si.block(count1, 0, 1, S0.cols()) = S0(i, all);
        FullPivLU<Matrix<double50, -1, -1>> Lu1(Si);
        FullPivLU<Matrix<double50, -1, -1>> Lu2(S);
        if (Lu1.rank() > Lu2.rank())
        {
            S.block(0, 0, count1 + 1, S0.cols()) = Si.block(0, 0, count1 + 1, S0.cols());
            count1++;
        }
    }

    Matrix<double50, -1, -1> evec;
    std::tie(Phi_X, Px, evec, c) = probtune(Phi_X, S, Le, 0);

    std::cout << "No. of ExtDist Modes: " << evec.cols() << endl;
    stx(1) = evec.cols();

    Matrix<double50, -1, -1> sfxs = ScaleFactor(Le, evec, Px);

    for (int i = 0; i < NE; i++)
    {
        coef_s[i].conservativeResize(NC, NMs + evec.cols());
        coef_s[i].block(0, NMs, NC, evec.cols()) = Phi_X[i] * evec * sfxs;
    }

    std::cout << "Extensional Distortion Modes Derived" << endl << endl;
    return std::tie(coef_s, stx);
}


Matrix<double50, -1, -1> eig(Matrix<double50, -1, -1> P, Matrix<double50, -1, -1> S)
{
    Matrix<double50, -1, -1> evec;
    Array<double50, -1, 1> eval;
    EigenSolver<Matrix<double50, -1, -1>> eig1;
    eig1.compute(P);
    eval = eig1.eigenvalues().real();
    evec = eig1.eigenvectors().real();

    vector<int> rng1, rng2, rng, redundant, rnd1;

    for (int i = 0; i < eval.size(); i++)
    {
        if (isfinite(eval(i)) && eval(i) > 0)
            rng1.push_back(i);
    }
    for (int i = 0; i < eval.size(); i++)
    {
        if (eval.abs()(i) > eval.abs()(rng1).maxCoeff() * 1e-10)
            rng2.push_back(i);
    }
    for (int i = 0; i < rng1.size(); i++)
    {
        for (int j = 0; j < rng2.size(); j++)
        {
            if (rng1[i] == rng2[j])
                rng.push_back(rng2[j]);
        }
    }

    for (int i = 0; i < rng.size(); i++)
    {
        for (int j = 0; j < redundant.size(); j++)
        {
            if (i == redundant[j])
                rnd1.push_back(j);
        }

        if (rnd1.size() == 0 && i < rng.size())
        {
            double50 di = eval(rng[i]);
            for (int j = i + 1; j < rng.size(); j++)
            {
                double50 dj = eval(rng[j]);
                if (abs((di - dj)) < (abs(di) * 1e-20))
                    redundant.push_back(j);
            }
        }
    }

    vector<int> effrngv;
    VectorXi effective, rngv, redundv;
    rngv.setZero(rng.size());
    redundv.setZero(redundant.size());
    effective.setZero(rng.size());

    for (int j = 0; j < rng.size(); j++)
        rngv(j) = rng[j];

    for (int j = 0; j < redundant.size(); j++)
        redundv(j) = redundant[j];

    sort(rngv.begin(), rngv.end());
    sort(redundv.begin(), redundv.end());
    VectorXi::iterator it;

    it = set_difference(rngv.begin(), rngv.end(), redundv.begin(), redundv.end(), effective.begin());
    effective.conservativeResize(it - effective.begin());

    for (int i = 0; i < effective.size(); i++)
        for (int j = 0; j < rngv.size(); j++)
        {
            if (effective(i) == rngv[j])
                effrngv.push_back(j);
        }

    Matrix<double50, -1, -1> evec1 = evec(all, rngv(effrngv));
    Array<double50, -1, 1> eval1 = eval(rngv(effrngv));

    return evec1;
}

tuple<vector<Matrix<double50, -1, -1>>, ArrayXi> WallBend(Matrix<double50, -1, -1> csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef_nWb, vector<Matrix<double50, -1, -1>> coef_n, vector<Matrix<double50, -1, -1>> coef_u, Array<double50, -1, 1> Le, int m)
{
    std::cout << "Deriving Wall Bending Modes" << endl << endl;
    int NE = cscc.rows();
    Index NC = coef_n[0].rows(), NMnwb = coef_nWb[0].cols(), NMn = coef_n[0].cols(), NMu = coef_u[0].cols(), NCn = coef_nWb[0].rows();
    int NMtb = NMn + NMnwb;
    int count1 = 0;
    vector<Matrix<double50, -1, -1>> coef0; coef0.resize(NE);
    Calculus integ; Continuity cont;//??
    ArrayXi ste(3); ste.setZero();

    for (int i = 0; i < NE; i++)
    {
        coef0[i].setZero(NC, NMtb);

        coef0[i].block(0, 0, NCn, NMnwb) = coef_nWb[i];
        coef0[i].block(0, NMnwb, NC, NMn) = coef_n[i];
    }
    vector<Matrix<double50, -1, -1>> coef00 = integ.Intcoef(coef0);
    vector<Matrix<double50, -1, -1>> coef01 = integ.Intcoef(coef00);;
    vector<Matrix<double50, -1, -1>> coef1 = integ.Intcoef(coef_u);
    vector<Matrix<double50, -1, -1>> coef2 = integ.Intcoef(coef1);
    vector<Matrix<double50, -1, -1>> coef3 = integ.Intcoef(coef2);
    vector<Matrix<double50, -1, -1>> coef4 = integ.Intcoef(coef3);
    int NMtmod = NMtb + 5 * NMu;
    vector<Matrix<double50, -1, -1>> Phi_N; Phi_N.resize(NE);

    for (int i = 0; i < NE; i++)
    {
        Phi_N[i].setZero(NC, NMtmod);

        Phi_N[i].block(0, 0, NC, NMtb) = coef01[i];
        Phi_N[i].block(0, NMtb, NC, NMu) = coef_u[i];
        Phi_N[i].block(0, NMtb + NMu, NC, NMu) = coef1[i];
        Phi_N[i].block(0, NMtb + 2 * NMu, NC, NMu) = coef2[i];
        Phi_N[i].block(0, NMtb + 3 * NMu, NC, NMu) = coef3[i];
        Phi_N[i].block(0, NMtb + 4 * NMu, NC, NMu) = coef4[i];
    }

    Matrix<double50, -1, -1> Pn = Inertia(Phi_N, Phi_N, Le);
    Matrix<double50, -1, -1> Qn, Q1;
    vector<int> c;
    Q1 = cont.Constraint(csc, cscc, Phi_N, 2);
    if (NCn == 0)
    {
        Qn = Q1;
    }
    else
    {
        Matrix<double50, -1, -1> Q4 = Inertia(coef_nWb, Phi_N, Le);
        if (cscc.rows() == 2)
        {
            vector<Matrix<double50, -1, -1>> Q2; Q2.resize(NE);
            for (int i = 0; i < NE; i++)
            {
                Q2[i] = coef_n[i](all, 2);
            }
            Matrix<double50, -1, -1> Q3 = Inertia(Q2, Phi_N, Le);
            Qn.block(0, 0, Q1.rows(), Q1.cols()) = Q1;
            Qn.block(Q1.rows(), 0, Q3.rows(), Q3.cols()) = Q3;
            Qn.block(Q1.rows() + Q3.rows(), 0, Q4.rows(), Q4.cols()) = Q4;
        }
        else
        {
            Qn.setZero(Q1.rows() + Q4.rows(), Q1.cols());
            Qn.block(0, 0, Q1.rows(), Q1.cols()) = Q1;
            Qn.block(Q1.rows(), 0, Q4.rows(), Q4.cols()) = Q4;
        }
    }
    Matrix<double50, -1, -1> S0, Si, S;
    S0 = Qn;

    Si.setZero(S0.rows(), S0.cols());
    S.setZero(S0.rows(), S0.cols());
    for (int i = 0; i < S0.rows(); i++)
    {
        Si.block(0, 0, count1, S.cols()) = S.block(0, 0, count1, S.cols());
        Si.block(count1, 0, 1, S0.cols()) = S0(i, all);
        FullPivLU<Matrix<double50, -1, -1>> Lu1(Si);
        FullPivLU<Matrix<double50, -1, -1>> Lu2(S);
        if (Lu1.rank() > Lu2.rank())
        {
            S.block(0, 0, count1 + 1, S0.cols()) = Si.block(0, 0, count1 + 1, S0.cols());
            count1++;
        }
    }

    Matrix<double50, -1, -1> evec;
    std::tie(Phi_N, Pn, evec, c) = probtune(Phi_N, S, Le, 0);

    std::cout << "No. of WB Modes: " << evec.cols() << endl;
    ste(2) = evec.cols();

    Matrix<double50, -1, -1> sfnwb = ScaleFactor(Le, evec, Pn);

    for (int i = 0; i < NE; i++)
    {
        coef_nWb[i].conservativeResize(NC, NMnwb + evec.cols());

        coef_nWb[i].block(0, NMnwb, NC, evec.cols()) = Phi_N[i] * evec * sfnwb;
    }

    std::cout << "Wall Bending Modes Derived" << endl << endl;
    return make_tuple(coef_nWb, ste);
}

tuple<vector<Matrix<double50, -1, -1>>, ArrayXi> NLW(Matrix<double50, -1, -1> csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef_s, vector<Matrix<double50, -1, -1>> coef_z, vector<Matrix<double50, -1, -1>> coef_u, Array<double50, -1, 1> Le)
{
    std::cout << "Deriving Non-Linear Warping Modes" << endl << endl;
    int NE = Le.rows();
    Index NC = coef_s[0].rows(), NMs = coef_s[0].cols(), NMz = coef_z[0].cols(), NMu = coef_u[0].cols();
    int NMsu = NMs + NMu, count1 = 0;
    Calculus integ; Continuity cont;

    vector<Matrix<double50, -1, -1>> coef1 = integ.Intcoef(coef_s), Phi_W;
    Matrix<double50, -1, -1> Rw, S0, S{}, Si;
    ArrayXi stw(3); stw.setZero(); Phi_W.resize(NE);

    for (int i = 0; i < NE; i++)
    {
        Phi_W[i].setZero(NC, NMsu);

        Phi_W[i].block(0, 0, NC, NMs) = coef1[i];
        Phi_W[i].block(0, NMs, NC, NMu) = coef_u[i];
    }

    Matrix<double50, -1, -1> Pw = Inertia(Phi_W, Phi_W, Le);
    Matrix<double50, -1, -1> Qw = Inertia(coef_z, Phi_W, Le);

    Rw = cont.Constraint(csc, cscc, Phi_W, 0);

    S0.setZero(Qw.rows() + Rw.rows(), Qw.cols());
    S0.block(0, 0, Qw.rows(), Qw.cols()) = Qw;
    S0.block(Qw.rows(), 0, Rw.rows(), Qw.cols()) = Rw;

    Si.setZero(S0.rows(), S0.cols());
    S.setZero(S0.rows(), S0.cols());
    for (int i = 0; i < S0.rows(); i++)
    {
        Si.block(0, 0, count1, S.cols()) = S.block(0, 0, count1, S.cols());
        Si.block(count1, 0, 1, S0.cols()) = S0(i, all);
        FullPivLU<Matrix<double50, -1, -1>> Lu1(Si);//?
        FullPivLU<Matrix<double50, -1, -1>> Lu2(S);
        if (Lu1.rank() > Lu2.rank())
        {
            S.block(0, 0, count1 + 1, S0.cols()) = Si.block(0, 0, count1 + 1, S0.cols());
            count1++;
        }
    }

    Matrix<double50, -1, -1> evec;
    vector<int> c;
    std::tie(Phi_W, Pw, evec, c) = probtune(Phi_W, S, Le, 0);

    std::cout << "No. of NLW Modes: " << evec.cols() << endl;
    stw(0) = evec.cols();

    Matrix<double50, -1, -1> sfw = ScaleFactor(Le, evec, Pw);

    for (int i = 0; i < NE; i++)
    {
        coef_z[i].conservativeResize(NC, NMz + evec.cols());
        coef_z[i].block(0, NMz, NC, evec.cols()) = Phi_W[i] * evec * sfw;
    }

    std::cout << "Non-Linear Warping Modes(NLW) Derived----------------------------" << endl << endl;
    return std::tie(coef_z, stw);

}


class Equation
{
public:
    Matrix<double50, -1, -1> h1;
    ArrayXi h2;
    Matrix<double50, -1, -1> h(MatrixXi cscc, double50 s)
    {
        if (cscc.rows() == 2)
        {
            h1.setZero(1, 3);
            h1(0, 0) = 1;
            h1(0, 1) = s * s;
            h1(0, 2) = s * s * s;
        }
        else
        {
            h1.setZero(1, 4);
            h1(0, 0) = 1;
            h1(0, 1) = s;
            h1(0, 2) = s * s;
            h1(0, 3) = s * s * s;
        }
        return h1;
    }
    Matrix<double50, -1, -1> dh(MatrixXi cscc, double50 s)
    {
        if (cscc.rows() == 2)
        {
            h1.setZero(1, 3);
            h1(0, 0) = 0;
            h1(0, 1) = 2 * s;
            h1(0, 2) = 3 * s * s;
        }
        else
        {
            h1.setZero(1, 4);
            h1(0, 0) = 0;
            h1(0, 1) = 1;
            h1(0, 2) = 2 * s;
            h1(0, 3) = 3 * s * s;
        }
        return h1;
    }
    Matrix<double50, -1, -1> ddh(MatrixXi cscc, double50 s)
    {
        if (cscc.rows() == 2)
        {
            h1.setZero(1, 3);
            h1(0, 0) = 0;
            h1(0, 1) = 2;
            h1(0, 2) = 6 * s;
        }
        else
        {
            h1.setZero(1, 4);
            h1(0, 0) = 0;
            h1(0, 1) = 0;
            h1(0, 2) = 2;
            h1(0, 3) = 6 * s;
        }
        return h1;
    }
    ArrayXi rng(ArrayXi ne, int e)
    {
        int c = 0;
        for (int i = 0; i <= e; i++)
        {
            c += ne(i);
        }
        h2.setLinSpaced(ne(e), c - ne(e), c - 1);
        return h2;
    }
    ArrayXi hrng(ArrayXi ne, int e)
    {
        return h2.setLinSpaced(ne(e), 0, ne(e) - 1);
    }
};


class Hermite
{
private:
    double N1(double k) { return (pow(1 - k, 2) * (2 + k)) / 4; }
    double N2(double L, double k) { return (L / 8) * pow(1 - k, 2) * (1 + k); }
    double N3(double k) { return (pow(1 + k, 2) * (2 - k)) / 4; }
    double N4(double L, double k) { return (L / 8) * pow(1 + k, 2) * (k - 1); }
    double dN1(double L, double k) { return (pow(k - 1, 2) / 4 + ((2 * k - 2) * (k + 2)) / 4) * 2 / L; }
    double dN2(double L, double k) { return ((L * pow(k - 1, 2)) / 8 + (L * (2 * k - 2) * (k + 1)) / 8) * 2 / L; }
    double dN3(double L, double k) { return (-pow(k + 1, 2) / 4 - ((2 * k + 2) * (k - 2)) / 4) * 2 / L; }
    double dN4(double L, double k) { return ((L * pow(k + 1, 2)) / 8 + (L * (2 * k + 2) * (k - 1)) / 8) * 2 / L; }
    double ddN1(double L, double k) { return (3 * k) / 2 * pow(2 / L, 2); }
    double ddN2(double L, double k) { return ((L * (k + 1)) / 4 + (L * (2 * k - 2)) / 4) * pow(2 / L, 2); }
    double ddN3(double L, double k) { return -(3 * k) / 2 * pow(2 / L, 2); }
    double ddN4(double L, double k) { return ((L * (k - 1)) / 4 + (L * (2 * k + 2)) / 4) * pow(2 / L, 2); }

public:
    MatrixXd N(double L, double k, int Nmode)
    {
        MatrixXd eye(Nmode, Nmode), Ni(Nmode, 4 * Nmode);
        eye.setIdentity(), Ni.setZero();
        Ni.block(0, 0, Nmode, Nmode) = eye * N1(k);
        Ni.block(0, Nmode, Nmode, Nmode) = eye * N2(L, k);
        Ni.block(0, 2 * Nmode, Nmode, Nmode) = eye * N3(k);
        Ni.block(0, 3 * Nmode, Nmode, Nmode) = eye * N4(L, k);

        return Ni;
    }
    MatrixXd dN(double L, double k, int Nmode)
    {
        MatrixXd eye(Nmode, Nmode), Ni(Nmode, 4 * Nmode);
        eye.setIdentity(), Ni.setZero();
        Ni.block(0, 0, Nmode, Nmode) = eye * dN1(L, k);
        Ni.block(0, Nmode, Nmode, Nmode) = eye * dN2(L, k);
        Ni.block(0, 2 * Nmode, Nmode, Nmode) = eye * dN3(L, k);
        Ni.block(0, 3 * Nmode, Nmode, Nmode) = eye * dN4(L, k);

        return Ni;
    }
    MatrixXd ddN(double L, double k, int Nmode)
    {
        MatrixXd eye(Nmode, Nmode), Ni(Nmode, 4 * Nmode);
        eye.setIdentity(), Ni.setZero();
        Ni.block(0, 0, Nmode, Nmode) = eye * ddN1(L, k);
        Ni.block(0, Nmode, Nmode, Nmode) = eye * ddN2(L, k);
        Ni.block(0, 2 * Nmode, Nmode, Nmode) = eye * ddN3(L, k);
        Ni.block(0, 3 * Nmode, Nmode, Nmode) = eye * ddN4(L, k);

        return Ni;
    }
};

vector<Matrix<double50, -1, -1>> nDirectional(Matrix<double50, -1, -1> csc, MatrixXi cscc, vector<Matrix<double50, -1, -1>> coef_s, vector<Matrix<double50, -1, -1>> coef_n)
{
    int NE = coef_s.size(), Nc = csc.rows(), ord = coef_s[0].rows() - 1, NC = ord + 1;
    Index NMs = coef_s[0].cols(), NMn = coef_n[0].cols();

    Array<double50, -1, 1> alpha, Le, s;
    ArrayXi mi, nc(Nc, 1), ne(NE, 1);
    Edge edge; Continuity cont;
    alpha = edge.Anglemp(csc, cscc);
    Le = edge.Lengthmp(csc, cscc);
    vector<vector<int>> cont_edg;
    vector<Matrix<double50, -1, -1>> cont_Rxy, coef;
    vector<Array<double50, -1, 1>> cont_sc;
    vector<int> e, nrow = { 1,3,4 };
    Equation hf;

    Matrix<double50, -1, -1> C, V, Uxy, Ci, hval, Vi, c0, c1, c2, vej(2, 1), D;
    coef.resize(NE);

    for (int m = NMn; m < NMs; m++)
    {
        int countUxy = 0;
        mi.setLinSpaced(NE, m, m + (NE - 1) * NMs);
        for (int i = 0; i < NE; i++)
            coef[i] = coef_s[i](all, m);
        tie(cont_edg, cont_Rxy, cont_sc) = cont.Edges(csc, cscc, coef, 1);
        nc.setZero(), ne.setConstant(4);
        for (int i = 0; i < Nc; i++)
        {
            e = cont_edg[i];
            if (e.size() == 1)
            {
                nc(i) = 1;
                ne(e) = 3;
            }
            else
                nc(i) = e.size() * 2;
        }
        C.resize(nc.sum(), nc.sum());
        V.resize(nc.sum(), 1);
        C.setZero();
        V.setZero();
        for (int i = 0; i < Nc; i++)
        {
            e = cont_edg[i];
            s = cont_sc[i];

            if (e.size() == 1)
            {
                Ci.setZero(1, C.rows());
                hval = hf.ddh(cscc, s(0));
                Ci(0, hf.rng(ne, e[0])) = hval(0, hf.hrng(ne, e[0]));
            }
            else
            {
                Uxy = cont_Rxy[countUxy];
                countUxy++;
                Vi.resize(nc(i), 1);
                c0.resize(e.size(), C.rows());
                Vi.setZero();
                c0.setZero();
                for (int j = 0; j < e.size(); j++)
                {
                    hval = hf.h(cscc, s(j));
                    c0(j, hf.rng(ne, e[j])) = hval(0, hf.hrng(ne, e[j]));
                    vej(0, 0) = sin(alpha(e[j]));
                    vej(1, 0) = -cos(alpha(e[j]));
                    Vi(j, 0) = vej.cwiseProduct(Uxy).sum();
                }
                c1.resize(e.size() - 1, C.rows());
                c1.setZero();
                for (int j = 0; j < e.size() - 1; j++)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        hval = hf.dh(cscc, s(static_cast<Eigen::Index>(j) + k));
                        c1(j, hf.rng(ne, e[static_cast<std::vector<int, std::allocator<int>>::size_type>(j) + k])) = hval(0, hf.hrng(ne, e[static_cast<std::vector<int, std::allocator<int>>::size_type>(j) + k])) * pow(-1, k + 1);
                    }
                }
                c2.resize(1, C.rows());
                c2.setZero();
                for (int j = 0; j < e.size(); j++)
                {
                    hval = hf.ddh(cscc, s(j));
                    if (s(j) == 0)
                        c2(0, hf.rng(ne, e[j])) = hval(0, hf.hrng(ne, e[j])) * (-1);
                    else
                        c2(0, hf.rng(ne, e[j])) = hval(0, hf.hrng(ne, e[j]));
                }
                Ci.resize(c0.rows() + c1.rows() + c2.rows(), c2.cols());
                Ci.block(0, 0, c0.rows(), c0.cols()) = c0;
                Ci.block(c0.rows(), 0, c1.rows(), c0.cols()) = c1;
                Ci.block(c0.rows() + c1.rows(), 0, c2.rows(), c0.cols()) = c2;

                V(hf.rng(nc, i), 0) = Vi;
            }
            C(hf.rng(nc, i), all) = Ci;
        }
        D = C.inverse() * V;

        if (cscc.rows() == 2)
        {
            for (int j = 0; j < NE; j++)
            {
                coef_n[j].conservativeResize(NC, NMs);
                coef_n[j](nrow, m) = D(hf.rng(ne, j), 0);
            }
        }
        else
        {
            for (int j = 0; j < NE; j++)
            {
                coef_n[j].conservativeResize(NC, NMs);
                coef_n[j].block(0, m, hf.rng(ne, j).size(), 1) = D(hf.rng(ne, j), 0);
            }
        }
    }

    return coef_n;
}

class Order
{
public:
    MatrixXi ordermp(vector<Matrix<double50, -1, -1>> coef)
    {
        int NE = coef.size();
        Index NM = coef[0].cols(), NC = coef[0].rows();
        Array<double50, -1, 1> f;
        MatrixXi ord(NE, NM);
        vector<int> ord_ij;
        ord.setZero();
        for (int i = 0; i < NE; i++)
        {
            for (int j = 0; j < NM; j++)
            {
                ord_ij.clear();
                f = coef[i].block(0, j, NC, 1);
                for (int k = 0; k < f.rows(); k++)
                {
                    if (f(k) != 0)
                        ord_ij.push_back(k);
                }
                if (ord_ij.size() > 0)
                    ord(i, j) = ord_ij[ord_ij.size() - 1];
                else
                    ord(i, j) = 0;
            }
        }

        return ord;
    }
    MatrixXi order(vector<MatrixXd> coef)
    {
        int NE = coef.size();
        Index NM = coef[0].cols(), NC = coef[0].rows();
        ArrayXd f;
        MatrixXi ord(NE, NM);
        vector<int> ord_ij;
        ord.setZero();
        for (int i = 0; i < NE; i++)
        {
            for (int j = 0; j < NM; j++)
            {
                ord_ij.clear();
                f = coef[i].block(0, j, NC, 1);
                for (int k = 0; k < f.rows(); k++)
                {
                    if (f(k) != 0)
                        ord_ij.push_back(k);
                }
                if (ord_ij.size() > 0)
                    ord(i, j) = ord_ij[ord_ij.size() - 1];
                else
                    ord(i, j) = 0;
            }
        }

        return ord;
    }
};


tuple<ArrayXd, ArrayXd> LGQ(float N)
{
    double a = -1, b = 1;
    double Nn = N - 1;
    double N1 = Nn + 1, N2 = Nn + 2;
    ArrayXd xu, x0;
    xu.setLinSpaced(N1, -1, 1);
    x0.setLinSpaced(Nn + 1, 0, Nn);

    MatrixXd L, Lp, y, y0, one, w;
    y = cos((2 * x0 + 1) * M_PI / (2 * Nn + 2)) + (0.27 / N1) * sin(M_PI * xu * Nn / N2);
    L.setZero(N1, N2);
    one.setOnes(L.rows(), 1);
    y0 = y0.setOnes(y.rows(), 1) * 2;

    while ((y - y0).cwiseAbs().maxCoeff() > DBL_EPSILON)
    {
        L.block(0, 0, L.rows(), 1).setOnes();
        L.block(0, 1, L.rows(), 1) = y;

        for (int k = 1; k < N1; k++)
        {
            L.block(0, k + 1, L.rows(), 1) = ((2 * k + 1) * y.cwiseProduct(L.block(0, k, L.rows(), 1)) - k * L.block(0, k - 1, L.rows(), 1)) / (k + 1);
        }
        Lp = N2 * (L.block(0, N1 - 1, L.rows(), 1) - y.cwiseProduct(L.block(0, N2 - 1, L.rows(), 1))).cwiseProduct((one - y.cwiseProduct(y)).cwiseInverse());

        y0 = y;
        y = y0 - L.block(0, N2 - 1, L.rows(), 1).cwiseProduct(Lp.cwiseInverse());
    }
    w = (b - a) * one.cwiseProduct(((one - y.cwiseProduct(y)).cwiseProduct(Lp.cwiseProduct(Lp))).cwiseInverse()) * pow(N2 / N1, 2);

    return make_tuple(y.reverse(), w);

}

tuple<vector<Matrix<double50, -1, -1>>, Matrix<double50, -1, -1>, Matrix<double50, -1, -1>, vector<int>> probtune(vector<Matrix<double50, -1, -1>> coef, Matrix<double50, -1, -1> Q, Array<double50, -1, 1> Le, int t)
{
    Index Nf = coef[0].cols(), NC = coef[0].rows();
    int NE = coef.size();
    vector<Matrix<double50, -1, -1>> Coef = coef;
    vector<int> z, c2;
    ColPivHouseholderQR<Matrix<double50, -1, -1>> qr(Q);
    qr.compute(Q);
    Matrix<double50, -1, -1> P = qr.colsPermutation(), Qi, H, H1, Pi, S, d;
    Tensor<double50, 3> coef2;
    ArrayXi c, C, h;

    c.setZero(P.cols());
    for (int i = 0; i < P.cols(); i++)
    {
        for (int j = 0; j < P.rows(); j++)
        {
            if (P(j, i) == 1)
                c(i) = j;
        }
    }
    if (t != 0)
    {
        for (int i = t; i < t * 2; i++)
        {
            for (int j = 0; j < c.size(); j++)
            {
                if (i == c(j))
                {
                    c2.push_back(j);
                }
            }
        }
    }
    for (int i = 0; i < NE; i++)
    {
        coef[i] = Coef[i](all, c);
    }

    Pi = Inertia(coef, coef, Le);

    Matrix<double50, -1, -1> evec;
    Array<double50, -1, 1> eval;
    if (Q.rows() == 0)
    {
        EigenSolver<Matrix<double50, -1, -1>> eig1;
        eig1.compute(Pi);
        eval = eig1.eigenvalues().real();
        evec = eig1.eigenvectors().real();
    }
    else
    {
        Matrix<double50, -1, -1> QR = qr.matrixR();
        Matrix<double50, -1, -1> R = QR.triangularView<Upper>();
        Matrix<double50, -1, -1> R1 = R.block(0, 0, R.rows(), R.rows());
        Matrix<double50, -1, -1> R2 = R.block(0, R.rows(), R.rows(), R.cols() - R.rows());
        Matrix<double50, -1, -1> Z, Z1, Z2;
        Z1 = -R1.inverse() * R2;
        Z2.setIdentity(R2.cols(), R2.cols());
        Z.setZero(Z1.rows() + Z2.rows(), Z1.cols());
        Z.block(0, 0, Z1.rows(), Z1.cols()) = Z1;
        Z.block(Z1.rows(), 0, Z2.rows(), Z2.cols()) = Z2;

        Matrix<double50, -1, -1> M1 = Z.transpose() * Pi * Z;
        Matrix<double50, -1, -1> M2 = Z.transpose() * Z;

        GeneralizedEigenSolver<Matrix<double50, -1, -1>> eig1;
        eig1.compute(M1, M2);
        eval = eig1.eigenvalues().real();
        Matrix<double50, -1, -1> x1 = eig1.eigenvectors().real();

        evec = Z * x1;
    }
    vector<int> rng1, rng2, rng, redundant, rnd1;

    for (int i = 0; i < eval.size(); i++)
    {
        if (isfinite(eval(i)) && eval(i) > 0)
            rng1.push_back(i);
    }
    for (int i = 0; i < eval.size(); i++)
    {
        if (eval.abs()(i) > eval.abs()(rng1).maxCoeff() * 1e-15)
            rng2.push_back(i);
    }
    for (int i = 0; i < rng1.size(); i++)
    {
        for (int j = 0; j < rng2.size(); j++)
        {
            if (rng1[i] == rng2[j])
                rng.push_back(rng2[j]);
        }
    }

    for (int i = 0; i < rng.size(); i++)
    {
        for (int j = 0; j < redundant.size(); j++)
        {
            if (i == redundant[j])
                rnd1.push_back(j);
        }

        if (rnd1.size() == 0 && i < rng.size())
        {
            double50 di = eval(rng[i]);
            for (int j = i + 1; j < rng.size(); j++)
            {
                double50 dj = eval(rng[j]);
                if (abs((di - dj)) < (abs(di) * 1e-20))
                    redundant.push_back(j);
            }
        }
    }

    vector<int> effrngv;
    VectorXi effective, rngv, redundv;
    rngv.setZero(rng.size());
    redundv.setZero(redundant.size());
    effective.setZero(rng.size());

    for (int j = 0; j < rng.size(); j++)
        rngv(j) = rng[j];

    for (int j = 0; j < redundant.size(); j++)
        redundv(j) = redundant[j];

    sort(rngv.begin(), rngv.end());
    sort(redundv.begin(), redundv.end());
    VectorXi::iterator it;

    it = set_difference(rngv.begin(), rngv.end(), redundv.begin(), redundv.end(), effective.begin());
    effective.conservativeResize(it - effective.begin());

    for (int i = 0; i < effective.size(); i++)
        for (int j = 0; j < rngv.size(); j++)
        {
            if (effective(i) == rngv[j])
                effrngv.push_back(j);
        }

    Matrix<double50, -1, -1> evec1 = evec(all, rngv(effrngv));
    Array<double50, -1, 1> eval1 = eval(rngv(effrngv));

    return make_tuple(coef, Pi, evec1, c2);
}

Matrix<double50, -1, -1> ScaleFactor(Array<double50, -1, 1> Le, Matrix<double50, -1, -1> coef, Matrix<double50, -1, -1> M)
{
    int Nx = coef.cols();
    Matrix<double50, -1, -1> sf(Nx, Nx), cofT, cof, recip;
    sf.setZero();
    for (int i = 0; i < Nx; i++)
    {
        cofT = coef(all, i).transpose();
        cof = coef(all, i);
        recip = cofT * M * cof;
        sf(i, i) = sqrt(Le.sum() / recip(0, 0));
    }
    return sf;
}

tuple<vector<MatrixXi>, vector<MatrixXi>, vector<MatrixXi>, vector<MatrixXi>, vector<MatrixXd>, vector<MatrixXd>, VectorXd, VectorXi> sysmat(vector<MatrixXd> csc, vector<MatrixXi> cscc, vector<vector<MatrixXd>> coef_s, vector<vector<MatrixXd>> coef_n, vector<vector<MatrixXd>> coef_z, MatrixXd pnt, MatrixXi pnt_con, ArrayXi csnum, MatrixXd besz, ArrayXd t, MatrixXd enr, vector<VectorXd> zcoord, VectorXi Nel)
{
    double tol1 = 1e-8, tol2 = 8;
    int Nb = pnt_con.rows();
    vector<MatrixXi> Ki, Kj, Mi, Mj;
    vector<MatrixXd> Kall, Mall;
    VectorXd L(Nb);
    VectorXi Nmode(Nb);
    MatrixXd pnti, csci, KK, MM, MM1;
    double Li;
    int cs, rck = 0, bdof = 0;
    MatrixXi cscci, ki, kj, mi, mj;
    vector<MatrixXd> coef_si, coef_ni, coef_zi;
    VectorXd zcoordi, Le;
    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");
    for (int i = 0; i < Nb; i++)
    {
        cout << "BEAM NO.:  " << i << endl;
        pnti = pnt(pnt_con(i, all), all);
        Li = (pnti(1, all) - pnti(0, all)).norm();
        L(i) = Li;
        cs = csnum(i);
        csci = csc[cs];
        cscci = cscc[cs];
        coef_si = coef_s[cs];
        coef_ni = coef_n[cs];
        coef_zi = coef_z[cs];
        Nmode(i) = coef_si[0].cols() + coef_zi[0].cols();
        zcoordi = zcoord[i];
        Le = zcoordi.block(1, 0, zcoordi.size() - 1, 1) - zcoordi.block(0, 0, zcoordi.size() - 1, 1);

        tie(ki, kj, KK) = stiffness(csci, cscci, coef_si, coef_ni, coef_zi, t(i), Li, enr(i, 0), enr(i, 1), Le, INT_MAX); // enr ?
        tie(mi, mj, MM1) = Mass(csci, cscci, coef_si, coef_ni, coef_zi, t(i), Li, enr(i, 0), enr(i, 1), Le, INT_MAX);
        MM = MM1 * enr(i, 2);

        rck += KK.rows();

        Kall.push_back(KK);
        Mall.push_back(MM);

        if (i == 0)
        {
            Ki.push_back(ki);
            Kj.push_back(kj);
            Mi.push_back(mi);
            Mj.push_back(mj);
        }
        else
        {
            Ki.push_back(ki + MatrixXi::Ones(ki.rows(), ki.cols()) * bdof);
            Kj.push_back(kj + MatrixXi::Ones(kj.rows(), kj.cols()) * bdof);
            Mi.push_back(mi + MatrixXi::Ones(mi.rows(), mi.cols()) * bdof);
            Mj.push_back(mj + MatrixXi::Ones(mj.rows(), mj.cols()) * bdof);
        }

        bdof += (Nel(i) + 1) * Nmode(i) * 2;

    }
    cout << endl;

    return make_tuple(Ki, Kj, Mi, Mj, Kall, Mall, L, Nmode);
}

tuple<MatrixXi, MatrixXi, MatrixXd> stiffness(MatrixXd csc, MatrixXi cscc, vector<MatrixXd> coef_s, vector<MatrixXd> coef_n, vector<MatrixXd> coef_z, double t, double L, double E, double nu, VectorXd Li1, int Neli)
{
    std::cout << "Stiffness Matrix Computation Starts:----------------------------------" << endl << endl;
    int NE = cscc.rows(), tol = 2;
    int NMs = coef_s[0].cols(), NMz = coef_z[0].cols(), Nel, Nmode = NMs + NMz, Ndof = Nmode * 2;
    double E1 = E / (1 - pow(nu, 2));
    ArrayXd alpha, Le, Lei;
    VectorXd Li;
    MatrixXd Di(3, 3), D(3, 3);
    Edge edge;
    Order Ord;

    if (Neli != INT_MAX)
    {
        Nel = Neli;
        Li = Lei.Ones(Nel, 1) * L / Nel;
    }
    else
    {
        Nel = Li1.size();
        Li = Li1;
    }
    int tdof = Ndof * (Nel + 1);

    if (Nmode == 6)
    {
        Di << E, 0, 0,
            0, E, 0,
            0, 0, E / (2 * (1 - nu));
    }
    else
    {
        Di << 1, nu, 0,
            nu, 1, 0,
            0, 0, (1 - nu) / 2;
    }
    D = E1 * Di;
    alpha = edge.Angle(csc, cscc);
    Le = edge.Length(csc, cscc);

    MatrixXi ord(NE, NMs * 2 + NMz);
    ord.setZero();
    ord.block(0, 0, NE, NMs) = Ord.order(coef_s);
    ord.block(0, NMs, NE, NMs) = Ord.order(coef_n);
    ord.block(0, NMs * 2, NE, NMz) = Ord.order(coef_z);

    float degs = ord.maxCoeff() * 2, degz = 3 * 2;
    float Ngps = ceil((degs + 1) / 2) + tol;
    float Ngpz = ceil((degz + 1) / 2) + tol;

    ArrayXd GPs, WFs, GPz, WFz;
    std::tie(GPs, WFs) = LGQ(Ngps);
    std::tie(GPz, WFz) = LGQ(Ngpz);
    MatrixXi elnode(Nel, 2), one1;
    for (int i = 0; i < Nel; i++)
        elnode.block(i, 0, 1, elnode.cols()) << i + 1, i + 2;
    one1.setOnes(elnode.rows(), 1);

    MatrixXi eldof(Nel, Ndof * 2);
    eldof.setZero();
    for (int i = 0; i < Ndof; i++)
    {
        eldof.block(0, i, Nel, 1) = elnode.block(0, 0, Nel, 1) * Ndof - one1 * (Ndof - i);
        eldof.block(0, i + Ndof, Nel, 1) = elnode.block(0, 1, Nel, 1) * Ndof - one1 * (Ndof - i);
    }

    MatrixXd L1(2, 3), L2(2, 3), L3(2, 3), L4(3, 2), L5(3, 2), La, Lb, Lc, Ld, Lf;
    L1 << 1, 0, 0,
        0, 0, 1;
    L2 << 0, 1, 0,
        0, 0, 0;
    L3 << 0, 0, 0,
        0, 1, 0;
    L4 << 1, 0,
        0, 0,
        0, 1;
    L5 << 0, 0,
        0, 1,
        1, 0;

    La = L4 * L1, Lb = L5 * L1, Lc = L4 * L2, Ld = L4 * L3 + L5 * L2, Lf = L5 * L3;

    MatrixXd D1, D2, D3, D4, D5, D6, D7, D8, D9;
    D1 = La.transpose() * D * La;
    D2 = La.transpose() * D * Lb;
    D3 = Lb.transpose() * D * Lb;
    D4 = Lc.transpose() * D * Lc;
    D5 = Lc.transpose() * D * Ld;
    D6 = Ld.transpose() * D * Ld;
    D7 = Lc.transpose() * D * Lf;
    D8 = Ld.transpose() * D * Lf;
    D9 = Lf.transpose() * D * Lf;

    MatrixXd H1, H2, H3, H4, H5, H6, H7, H8, H9;
    H1.setZero(Nmode, Nmode);
    H2.setZero(Nmode, Nmode);
    H3.setZero(Nmode, Nmode);
    H4.setZero(Nmode, Nmode);
    H5.setZero(Nmode, Nmode);
    H6.setZero(Nmode, Nmode);
    H7.setZero(Nmode, Nmode);
    H8.setZero(Nmode, Nmode);
    H9.setZero(Nmode, Nmode);

    double tt = pow(t, 3) / 12, jcob, wf;
    ArrayXd s;
    MatrixXd F, dF, ddF, f, df, ddf;
    cout << "start PSI ------------------------------------------------------------------------ \n\n\n"<<NE<<endl<<endl;
    for (int i = 0; i < NE; i++)
    {
        jcob = Le(i) / 2;
        s = jcob * (GPs + 1);

        F = PSI(coef_s, coef_n, coef_z, i, s, 0);
        dF = PSI(coef_s, coef_n, coef_z, i, s, 1);
        ddF = PSI(coef_s, coef_n, coef_z, i, s, 2);
        //cout << "F PIS = \n" << F << endl << endl;
        //cout << "dF PIS = \n" << dF << endl << endl;
        //cout << "ddF PIS = \n" << ddF << endl << endl;
        for (int j = 0; j < Ngps; j++)
        {
            wf = WFs(j);
            f = F.block(0, (NMs + NMz) * j, 3, NMs + NMz);
            df = dF.block(0, (NMs + NMz) * j, 3, NMs + NMz);
            ddf = ddF.block(0, (NMs + NMz) * j, 3, NMs + NMz);

            H1 += df.transpose() * D1 * df * jcob * wf * t;
            H2 += df.transpose() * D2 * f * jcob * wf * t;
            H3 += f.transpose() * D3 * f * jcob * wf * t;
            H4 += ddf.transpose() * D4 * ddf * jcob * wf * tt;
            H5 += ddf.transpose() * D5 * df * jcob * wf * tt;
            H6 += df.transpose() * D6 * df * jcob * wf * tt;
            H7 += ddf.transpose() * D7 * f * jcob * wf * tt;
            H8 += df.transpose() * D8 * f * jcob * wf * tt;
            H9 += f.transpose() * D9 * f * jcob * wf * tt;
        }
        //cout << "f = \n" << f << endl << endl;
        //cout << "df = \n" << df << endl << endl;
        //cout << "ddf = \n" << ddf << endl << endl;
        //cout << "H1 = \n" << H1 << endl << endl;
        //cout << "H2 = \n" << H2 << endl << endl;
        //cout << "H3 = \n" << H3 << endl << endl;
        //cout << "H4 = \n" << H4 << endl << endl;
        //cout << "H5 = \n" << H5 << endl << endl;
        //cout << "H6 = \n" << H6 << endl << endl;
        //cout << "H7 = \n" << H7 << endl << endl;
        //cout << "H8 = \n" << H8 << endl << endl;
        //cout << "H9 = \n" << H9 << endl << endl;
    }

    cout << "end PSI ------------------------------------------------------------------------ \n\n\n";

    vector<double> Lij;
    for (int i = 0; i < Li.size(); i++)
        Lij.push_back(Li(i));

    auto end = Lij.end();
    for (auto it = Lij.begin(); it != end; ++it)
        end = remove(it + 1, end, *it);

    Lij.erase(end, Lij.end());

    VectorXd Ltype, Const;
    Ltype.setZero(Nel);
    MatrixXd k1, k2, k3, k4, k5, k6, k7, k8, k9;
    vector<MatrixXd> ke;
    double Lm;
    double ksi;
    Hermite shN;
    vector<int> Lij_m;

    for (int m = 0; m < Lij.size(); m++)
    {
        Lm = Lij[m];
        Lij_m.clear();
        for (int ii = 0; ii < Li.size(); ii++)
            if (Li(ii) == Lm)
                Lij_m.push_back(ii);

        Ltype(Lij_m) = Const.setConstant(Lij_m.size(), m);

        k1.setZero(Ndof * 2, Ndof * 2);
        k2.setZero(Ndof * 2, Ndof * 2);
        k3.setZero(Ndof * 2, Ndof * 2);
        k4.setZero(Ndof * 2, Ndof * 2);
        k5.setZero(Ndof * 2, Ndof * 2);
        k6.setZero(Ndof * 2, Ndof * 2);
        k7.setZero(Ndof * 2, Ndof * 2);
        k8.setZero(Ndof * 2, Ndof * 2);
        k9.setZero(Ndof * 2, Ndof * 2);

        jcob = Lm / 2;
        for (int i = 0; i < Ngpz; i++)
        {
            ksi = GPz(i);
            wf = WFz(i);

            k1 += shN.N(Lm, ksi, Nmode).transpose() * H1 * shN.N(Lm, ksi, Nmode) * jcob * wf;
            k2 += shN.N(Lm, ksi, Nmode).transpose() * H2 * shN.dN(Lm, ksi, Nmode) * jcob * wf;
            k3 += shN.dN(Lm, ksi, Nmode).transpose() * H3 * shN.dN(Lm, ksi, Nmode) * jcob * wf;
            k4 += shN.N(Lm, ksi, Nmode).transpose() * H4 * shN.N(Lm, ksi, Nmode) * jcob * wf;
            k5 += shN.N(Lm, ksi, Nmode).transpose() * H5 * shN.dN(Lm, ksi, Nmode) * jcob * wf;
            k6 += shN.dN(Lm, ksi, Nmode).transpose() * H6 * shN.dN(Lm, ksi, Nmode) * jcob * wf;
            k7 += shN.N(Lm, ksi, Nmode).transpose() * H7 * shN.ddN(Lm, ksi, Nmode) * jcob * wf;
            k8 += shN.dN(Lm, ksi, Nmode).transpose() * H8 * shN.ddN(Lm, ksi, Nmode) * jcob * wf;
            k9 += shN.ddN(Lm, ksi, Nmode).transpose() * H9 * shN.ddN(Lm, ksi, Nmode) * jcob * wf;
        }
        ke.push_back(k1 + k2 + k2.transpose() + k3 + k4 + k5 + k5.transpose() + k6 + k7 + k7.transpose() + k8 + k8.transpose() + k9);
    }

    VectorXd Ke(4 * Ndof * Ndof);
    MatrixXi edofs(2 * Ndof, Nel), Ki(2 * Ndof * 2 * Ndof, Nel), Kj(2 * Ndof * 2 * Ndof, Nel);
    MatrixXd Kall(2 * Ndof * 2 * Ndof, Nel);
    Ke.setZero(), edofs = eldof.transpose(), Ki.setZero(), Kj.setZero(), Kall.setZero();
    vector<MatrixXd> Kke;
    VectorXd en;
    for (int k = 0; k < Nel; k++)
    {
        for (int i = 0; i < 2 * Ndof; i++)
        {
            Ke.block(2 * Ndof * i, 0, 2 * Ndof, 1) = ke[Ltype(k)].block(0, i, 2 * Ndof, 1);
        }
        Kke.push_back(Ke);
    }
    for (int i = 0; i < Nel; i++)
        Kall.block(0, i, 2 * Ndof * 2 * Ndof, 1) = Kke[i];
    for (int i = 0; i < 2 * Ndof; i++)
    {
        Ki.block(2 * Ndof * i, 0, 2 * Ndof, Nel) = edofs;
        for (int j = 0; j < 2 * Ndof; j++)
            Kj.block(2 * Ndof * i + j, 0, 1, Nel) = edofs.block(i, 0, 1, Nel);
    }

    std::cout << "Stiffness Matrix Computed!" << endl << endl;

    return make_tuple(Ki, Kj, Kall);
}

tuple<MatrixXi, MatrixXi, MatrixXd> Mass(MatrixXd csc, MatrixXi cscc, vector<MatrixXd> coef_s, vector<MatrixXd> coef_n, vector<MatrixXd> coef_z, double t, double L, double E, double nu, VectorXd Li1, int Neli)
{
    std::cout << "Mass Matrix Computation Starts:" << endl << endl;

    int NE = cscc.rows(), tol = 2;
    int NMs = coef_s[0].cols(), NMz = coef_z[0].cols(), Nel, Nmode = NMs + NMz, Ndof = Nmode * 2;
    double E1 = E / (1 - pow(nu, 2));
    ArrayXd alpha, Le, Lei;
    VectorXd Li;
    MatrixXd Di(3, 3), D(3, 3);
    Edge edge;
    Order Ord;

    if (Neli != INT_MAX)
    {
        Nel = Neli;
        Li = Lei.Ones(Nel, 1) * L / Nel;
    }
    else
    {
        Nel = Li1.size();
        Li = Li1;
    }

    int tdof = Ndof * (Nel + 1);
    Di << 1, nu, 0,
        nu, 1, 0,
        0, 0, (1 - nu) / 2;
    D = E1 * Di;

    alpha = edge.Angle(csc, cscc);
    Le = edge.Length(csc, cscc);

    MatrixXi ord(NE, NMs * 2 + NMz);
    ord.setZero();
    ord.block(0, 0, NE, NMs) = Ord.order(coef_s);
    ord.block(0, NMs, NE, NMs) = Ord.order(coef_n);
    ord.block(0, NMs * 2, NE, NMz) = Ord.order(coef_z);


    float degs = ord.maxCoeff() * 2, degz = 3 * 2;
    float Ngps = ceil((degs + 1) / 2) + tol;
    float Ngpz = ceil((degz + 1) / 2) + tol;

    ArrayXd GPs, WFs, GPz, WFz;
    std::tie(GPs, WFs) = LGQ(Ngps);
    std::tie(GPz, WFz) = LGQ(Ngpz);

    MatrixXi elnode(Nel, 2), one1;
    for (int i = 0; i < Nel; i++)
        elnode.block(i, 0, 1, elnode.cols()) << i + 1, i + 2;
    one1.setOnes(elnode.rows(), 1);

    MatrixXi eldof(Nel, Ndof * 2);
    eldof.setZero();
    for (int i = 0; i < Ndof; i++)
    {
        eldof.block(0, i, Nel, 1) = elnode.block(0, 0, Nel, 1) * Ndof - one1 * (Ndof - i);
        eldof.block(0, i + Ndof, Nel, 1) = elnode.block(0, 1, Nel, 1) * Ndof - one1 * (Ndof - i);
    }

    MatrixXd Lm1(3, 3), Lm2(3, 3);
    Lm1 << 0, 1, 0,
        0, 0, 0,
        0, 0, 0;
    Lm2 << 0, 0, 0,
        0, 0, 0,
        0, 1, 0;

    MatrixXd Hm1, Hm2, Hm3, Hm4;
    Hm1.setZero(Nmode, Nmode);
    Hm2.setZero(Nmode, Nmode);
    Hm3.setZero(Nmode, Nmode);
    Hm4.setZero(Nmode, Nmode);

    double tt = pow(t, 3) / 12, jcob, wf;
    ArrayXd s;
    MatrixXd F, dF, f, df;

    for (int i = 0; i < NE; i++)
    {
        jcob = Le(i) / 2;
        s = jcob * (GPs + 1);

        F = PSI(coef_s, coef_n, coef_z, i, s, 0); // ?
        dF = PSI(coef_s, coef_n, coef_z, i, s, 1);
        //cout << "F PIS = \n" << F << endl << endl;
        //cout << "dF PIS = \n" << dF << endl << endl;
        for (int j = 0; j < Ngps; j++)
        {
            wf = WFs(j);
            f = F.block(0, (NMs + NMz) * j, 3, NMs + NMz);
            df = dF.block(0, (NMs + NMz) * j, 3, NMs + NMz);


            Hm1 += f.transpose() * f * jcob * wf * t;
            Hm2 += df.transpose() * Lm1.transpose() * Lm1 * df * jcob * wf * tt;
            Hm3 += df.transpose() * Lm1.transpose() * Lm2 * f * jcob * wf * tt;
            Hm4 += f.transpose() * Lm2.transpose() * Lm2 * f * jcob * wf * tt;
        }
        //cout << "f = \n" << f << endl << endl;
        //cout << "df = \n" << df << endl << endl;
        //cout << "Hm1 = \n" << Hm1 << endl << endl;
        //cout << "Hm2 = \n" << Hm2 << endl << endl;
        //cout << "Hm3 = \n" << Hm3 << endl << endl;
        //cout << "Hm4 = \n" << Hm4 << endl << endl;
    }

    vector<double> Lij;
    for (int i = 0; i < Li.size(); i++)
        Lij.push_back(Li(i));

    auto end = Lij.end();
    for (auto it = Lij.begin(); it != end; ++it)
        end = remove(it + 1, end, *it);

    Lij.erase(end, Lij.end());

    VectorXd Ltype, Const;
    Ltype.setZero(Nel);
    vector<MatrixXd> me;
    double Lm;
    double ksi;
    Hermite shN;
    vector<int> Lij_m;
    MatrixXd m1, m2, m3, m4;

    const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");
    for (int m = 0; m < Lij.size(); m++)
    {
        Lm = Lij[m];
        Lij_m.clear();
        for (int ii = 0; ii < Li.size(); ii++)
            if (Li(ii) == Lm)
                Lij_m.push_back(ii);

        Ltype(Lij_m) = Const.setConstant(Lij_m.size(), m);
        m1.setZero(Ndof * 2, Ndof * 2);
        m2.setZero(Ndof * 2, Ndof * 2);
        m3.setZero(Ndof * 2, Ndof * 2);
        m4.setZero(Ndof * 2, Ndof * 2);

        jcob = Lm / 2;
        for (int i = 0; i < Ngpz; i++)
        {
            ksi = GPz(i);
            wf = WFz(i);

            m1 += shN.N(Lm, ksi, Nmode).transpose() * Hm1 * shN.N(Lm, ksi, Nmode) * jcob * wf;
            m2 += shN.N(Lm, ksi, Nmode).transpose() * Hm2 * shN.N(Lm, ksi, Nmode) * jcob * wf;
            m3 += shN.N(Lm, ksi, Nmode).transpose() * Hm3 * shN.dN(Lm, ksi, Nmode) * jcob * wf;
            m4 += shN.dN(Lm, ksi, Nmode).transpose() * Hm4 * shN.dN(Lm, ksi, Nmode) * jcob * wf;
        }
        me.push_back(m1 + m2 + m3 + m3.transpose() + m4);
    }

    VectorXd Me(4 * Ndof * Ndof);
    MatrixXi edofs(2 * Ndof, Nel), Mi(2 * Ndof * 2 * Ndof, Nel), Mj(2 * Ndof * 2 * Ndof, Nel);
    MatrixXd MM((Nel + 1) * Ndof, (Nel + 1) * Ndof), Mall(2 * Ndof * 2 * Ndof, Nel);
    Me.setZero(), edofs = eldof.transpose(), Mi.setZero(), Mj.setZero(), Mall.setZero();
    vector<MatrixXd> Mme;
    MM.setZero();
    VectorXd en;
    for (int k = 0; k < Nel; k++)
    {
        for (int i = 0; i < 2 * Ndof; i++)
        {
            Me.block(2 * Ndof * i, 0, 2 * Ndof, 1) = me[Ltype(k)].block(0, i, 2 * Ndof, 1);
        }
        Mme.push_back(Me);
    }
    for (int i = 0; i < Nel; i++)
        Mall.block(0, i, 2 * Ndof * 2 * Ndof, 1) = Mme[i];
    for (int i = 0; i < 2 * Ndof; i++)
    {
        Mi.block(2 * Ndof * i, 0, 2 * Ndof, Nel) = edofs;
        for (int j = 0; j < 2 * Ndof; j++)
            Mj.block(2 * Ndof * i + j, 0, 1, Nel) = edofs.block(i, 0, 1, Nel);
    }

    std::cout << "Mass Matrix Computed!" << endl << endl;

    return make_tuple(Mi, Mj, Mall);
}


Matrix<double50, -1, -1> Inertia(vector<Matrix<double50, -1, -1>> coef1, vector<Matrix<double50, -1, -1>> coef2, Array<double50, -1, 1> Le)
{
    int NE = Le.rows();
    Index NC = coef1[0].rows() * 2, NM1 = coef1[0].cols(), NM2 = coef2[0].cols();

    Matrix<double50, -1, -1> c2;
    vector<Matrix<double50, -1, -1>> c3, c3i;
    Matrix<double50, -1, -1> J(NM1, NM2), val(1, NM2), s;
    Vector<double50, -1> p, c1;
    double50 c1k, Li;
    Calculus integ;

    c1.setZero(NC, 1), c2.setZero(NC, NM2), c3.resize(1), c3[0].setZero(NC, NM2);
    int n{};
    J.setZero();

    p.setLinSpaced(NC, 0, NC - 1);

    for (int i = 0; i < NM1; i++)
    {
        val.setZero();
        for (int e = 0; e < NE; e++)
        {
            Li = Le(e);
            s.setZero(1, NC);
            c1.block(0, 0, NC / 2, 1) = coef1[e].block(0, i, NC / 2, 1);
            c2.block(0, 0, NC / 2, NM2) = coef2[e];
            for (int j = 0; j < NC; j++)
            {
                s(j) = pow(Li, p(j));
                if (c1(j) != 0)
                {
                    n = j + 1;
                }
            }
            c3[0].setZero();
            if (n != 0)
            {
                for (int k = 1; k <= n; k++)
                {
                    c1k = c1(k - 1);
                    c3[0] += c1k * shift(c2, k - 1);
                }
                c3i = integ.Intcoef(c3);
                val += s * c3i[0];
            }
        }
        J.block(i, 0, 1, NM2) = val;
    }
    return J;
}
Matrix<double50, -1, -1> shift(Matrix<double50, -1, -1> m1, int n)
{
    int row1 = m1.rows(), col1 = m1.cols();
    ArrayXi r1;
    r1.setLinSpaced(static_cast<Eigen::Index>(row1) - n, 0, row1 - 1 - n);
    Matrix<double50, -1, -1> m2;
    m2.setZero(row1, col1);
    m2.block(n, 0, row1 - n, col1) = m1.block(0, 0, row1 - n, col1);

    return m2;
}

MatrixXd PSI(vector<MatrixXd> coef_s, vector<MatrixXd> coef_n, vector<MatrixXd> coef_z, int e, ArrayXd s, int d)
{
    int NMi = coef_s[0].cols(), NMo = coef_z[0].cols();
    MatrixXd fs, fn, fz;
    Edge edge;

    fs = edge.Continuity2(coef_s, e, s, d);
    fn = edge.Continuity2(coef_n, e, s, d);
    fz = edge.Continuity2(coef_z, e, s, d);
    /*cout << "fs = \n" << fs << endl << endl;
    cout << "fn = \n" << fn << endl << endl;
    cout << "fz = \n" << fz << endl << endl;*/
    MatrixXd fval;
    fval.setZero(3, (NMi + NMo) * s.rows());
    cout << "s.rows() = " << s.rows() << endl << endl;
    for (int i = 0; i < s.rows(); i++)
    {
        fval.block(0, (NMi + NMo) * i, 1, NMi) = fs.block(i, 0, 1, NMi);
        fval.block(1, (NMi + NMo) * i, 1, NMi) = fn.block(i, 0, 1, NMi);
        fval.block(2, (NMi + NMo) * i + NMi, 1, NMo) = fz.block(i, 0, 1, NMo);
    }
    //cout << "fval = \n" << fval << endl << endl;
    return fval;
}


int main() {
    ifstream inFile("test4.hob");

    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    //cout << inFile.rdbuf() << endl << endl;

    string tp, analysis;
    int si = 0, csnumi = 0, freq = 0;
    vector<int> sec, sectype, bcs, fcs, nw1;
    vector<RowVector<double50, -1>> dim;
    vector<RowVectorXd> Elements, Joints, UCross1, BoundCs, Forces, PShell, ShellElements;
    vector<RowVector3i> CSMandM;
    vector<RowVector2d> shelljoint;
    vector<Matrix<double50, -1, -1>> UserCross;
    Matrix<double50, -1, -1> UCross2;
    RowVector2d csdim;
    RowVector3d csdimch, FRF;
    RowVectorXd jointcheck;
    Extract dimensions;
    double csthick;
    vector<double> usthick;
    RowVector<double50, -1> csType(5), csTypei(6);
    vector<RowVector4d> Nodes, Materials;
    MatrixXd HO_Nodes, HO_Elements, HO_Joints, HO_Materials, HO_BCs, FEdge, FNode, HO_PShell, Shell, ShellJoints;
    MatrixXi ModenMat;
    ArrayXi NW1;

    while (getline(inFile, tp))
    {
        if (tp.substr(0, 11) == "*HO_SECTION")
        {
            //sec.push_back(si); // Number of Cross Sections and their places in the test file
            getline(inFile, tp); si++;
            getline(inFile, tp); si++;
            CSMandM.push_back(dimensions.CSMandM(tp));
            if (tp.find("OPEN") != string::npos)
            {
                sectype.push_back(0); // 0 means open Cross Section
                getline(inFile, tp); si++;
                csdim(0) = dimensions.EdgeLandT(tp)(0); // Extracting Edge Length and Thickness
                getline(inFile, tp); si++;
                csdim(1) = dimensions.EdgeLandT(tp)(0);
                csthick = dimensions.EdgeLandT(tp)(1);
                csType << csnumi + 1, sectype[csnumi], csdim, csthick;
                dim.push_back(csType);
                nw1.push_back(2);
            }
            else if (tp.find("RECT") != string::npos)
            {
                sectype.push_back(1); // 1 means closed cross section
                getline(inFile, tp); si++;
                csdim(0) = dimensions.EdgeLandT(tp)(0); // Extracting Edge Length and Thickness
                getline(inFile, tp); si++;
                csdim(1) = dimensions.EdgeLandT(tp)(0);
                csthick = dimensions.EdgeLandT(tp)(1);
                csType << csnumi + 1, sectype[csnumi], csdim, csthick;
                dim.push_back(csType);
                nw1.push_back(1);
            }
            else if (tp.find("USER") != string::npos)
            {
                sectype.push_back(2); // 2 means User Defined cross section
                UCross1.clear();
                getline(inFile, tp); si++;
                while (tp.length() > 1)
                {
                    UCross1.push_back(dimensions.UserCross(tp));
                    getline(inFile, tp); si++;
                }
                UCross2.setZero(UCross1.size(), 4);
                for (int i = 0; i < UCross1.size(); i++)
                    UCross2(i, all) = UCross1[i]({ 0,1,2,3 });
                UserCross.push_back(UCross2);
                usthick.push_back(UCross1[0](4));
                nw1.push_back(1);
            }
            else if (tp.find("CHAMFER") != string::npos)
            {
                sectype.push_back(3); // 3 means CHAMFERED cross section
                getline(inFile, tp); si++;
                csdimch(0) = dimensions.EdgeLandT(tp)(0); // Extracting Edge Length and Thickness
                getline(inFile, tp); si++;
                csdimch(1) = dimensions.EdgeLandT(tp)(0);
                getline(inFile, tp); si++;
                csdimch(2) = dimensions.EdgeLandT(tp)(0);
                csthick = dimensions.EdgeLandT(tp)(1);
                csTypei << csnumi + 1, sectype[csnumi], csdimch, csthick;
                dim.push_back(csTypei);
                nw1.push_back(1);
            }
            csnumi++;
        }
        else if (tp.substr(0, 12) == "*HO_ANALYSIS")
        {
            getline(inFile, tp); si++;
            analysis = tp;
        }
        else if (tp.substr(0, 12) == "*HO_MATERIAL")
        {
            getline(inFile, tp); si++;
            getline(inFile, tp); si++;
            // Length should be checked with > 1 not != 1
            //while (tp.length() != 1)
            while (tp.length() > 1)
            {
                Materials.push_back(dimensions.Material(tp));
                getline(inFile, tp); si++;
            }
        }
        else if (tp.substr(0, 10) == "*HO_PSHELL")
        {
            getline(inFile, tp); si++;
            getline(inFile, tp); si++;
            while (tp.empty() == 0)
            {
                PShell.push_back(dimensions.BCs(tp));
                getline(inFile, tp); si++;
            }

        }
        else if (tp.substr(0, 8) == "*HO_NODE")
        {
            getline(inFile, tp); si++;
            while (tp.length() > 1)
            {
                Nodes.push_back(dimensions.Nodes(tp));
                getline(inFile, tp); si++;
            }
        }
        else if (tp.substr(0, 8) == "*HO_BEAM")
        {
            getline(inFile, tp); si++;
            while (tp.length() > 1)
            {
                Elements.push_back(dimensions.Elements(tp));
                getline(inFile, tp); si++;
            }
        }
        else if (tp.substr(0, 9) == "*HO_SHELL")
        {
            getline(inFile, tp); si++;
            while (tp.empty() == 0)
            {
                ShellElements.push_back(dimensions.Joint(tp));
                getline(inFile, tp); si++;
            }
        }
        else if (tp.substr(0, 9) == "*HO_JOINT")
        {
            getline(inFile, tp); si++;
            getline(inFile, tp); si++;
            while (tp.length() > 1)
            {
                jointcheck = dimensions.Joint(tp);
                if (jointcheck({ 2,3,4,5 }) == RowVector4d::Zero())
                    shelljoint.push_back(jointcheck({ 0,1 }));
                else
                    Joints.push_back(jointcheck);
                getline(inFile, tp); si++;
                if (inFile.eof() != 0)
                {
                    jointcheck = dimensions.Joint(tp);
                    if (jointcheck({ 2,3,4,5 }) == RowVector4d::Zero())
                        shelljoint.push_back(jointcheck({ 0,1 }));
                    else
                        Joints.push_back(jointcheck);
                    tp = "";
                }
            }
        }
        else if (tp.substr(0, 7) == "*HO_SPC")
        {
            getline(inFile, tp); si++;
            while (tp.length() > 1)
            {
                if (tp.find("U") != string::npos)
                    bcs.push_back(0);                       // 0 for Rigid Body Modes
                else if (tp.find("W") != string::npos)
                    bcs.push_back(1);                       // 1 for Warping Modes
                else if (tp.find("X") != string::npos)
                    bcs.push_back(2);                       // 2 for Distortion Modes

                BoundCs.push_back(dimensions.BCs(tp));
                getline(inFile, tp); si++;
            }

        }
        else if (tp.substr(0, 9) == "*HO_FORCE")
        {
            getline(inFile, tp); si++;
            while (tp.length() > 1)
            {
                if (tp.find("F") != string::npos)
                {
                    fcs.push_back(0);                       // 0 for point force
                    Forces.push_back(dimensions.Forces(tp, 3));
                }
                else if (tp.find("B") != string::npos)
                {
                    fcs.push_back(1);                       // 1 for Warping force
                    Forces.push_back(dimensions.Forces(tp, 3));
                }
                else if (tp.find("Q") != string::npos)
                {
                    fcs.push_back(2);                       // 2 for Distortion force
                    Forces.push_back(dimensions.Forces(tp, 3));
                }
                else
                {
                    Forces.push_back(dimensions.Forces(tp, 5));
                }
                getline(inFile, tp); si++;
            }
        }
        else if (tp.substr(0, 8) == "*HO_EIGR")
        {
            getline(inFile, tp); si++;
            freq = dimensions.CSMandM(tp)(2);
        }
        else if (tp.substr(0, 8) == "*HO_FREQ")
        {
            getline(inFile, tp); si++;
            FRF = dimensions.BCs(tp);
        }
        si++;
    }
    inFile.close();

    ModenMat.setZero(CSMandM.size(), 3);
    for (int i = 0; i < CSMandM.size(); i++)
    {
        ModenMat(i, { 0,2 }) = CSMandM[i]({ 0,2 });
        ModenMat(i, 1) = CSMandM[i](1) - 1;
    }

    HO_Nodes.setZero(Nodes.size(), 4);
    for (int i = 0; i < Nodes.size(); i++)
        HO_Nodes(i, all) = Nodes[i];

    HO_Elements.setZero(Elements.size(), 7);
    for (int i = 0; i < Elements.size(); i++)
        HO_Elements(i, all) = Elements[i];

    HO_Joints.setZero(Joints.size(), 6);
    for (int i = 0; i < Joints.size(); i++)
        HO_Joints(i, all) = Joints[i];

    NW1.setZero(nw1.size());
    for (int i = 0; i < nw1.size(); i++)
        NW1(i) = nw1[i];

    for (int i = 0; i < HO_Elements.rows(); i++)
    {
        for (int j = 4; j < 7; j++)
            if (abs(HO_Elements(i, j)) < 1e-9)
                HO_Elements(i, j) = 0;
        HO_Elements(i, { 4,5,6 }) = HO_Elements(i, { 4,5,6 }) / HO_Elements(i, { 4,5,6 }).norm();
    }
    // Calculating Cross Section Coordinates

    int icp1 = 0, icp2 = 0, jp;
    double50 unitcheck;
    RowVector<double50, 2> csp1, csp2, csp3;
    Matrix<double50, -1, -1> UCross3;
    vector <RowVector<double50, 2>> csp;
    VectorXi cvec;
    vector<double50> Thickness;
    Matrix<double50, -1, -1> csc1;
    MatrixXi cscc1;
    vector<Matrix<double50, -1, -1>> csc;
    vector<MatrixXi> cscc;
    string units;

    if (dim.size() > 0)
        unitcheck = abs(dim[0](2));
    else if (UserCross.size() > 0)
        unitcheck = abs(UserCross[0](0, 0));
    else
        unitcheck = HO_Nodes(all, { 1,2,3 }).maxCoeff() / 10;

    if (unitcheck > 1)
    {
        units = "millimeters";
        for (int se = 0; se < sectype.size(); se++)
        {
            if (sectype[se] == 0 || sectype[se] == 1)
            {
                csc1.setZero(4, 2);
                csc1 << -dim[icp1](2) / 2 / 1000, -dim[icp1](3) / 2 / 1000,
                    dim[icp1](2) / 2 / 1000, -dim[icp1](3) / 2 / 1000,
                    dim[icp1](2) / 2 / 1000, dim[icp1](3) / 2 / 1000,
                    -dim[icp1](2) / 2 / 1000, dim[icp1](3) / 2 / 1000;

                csc.push_back(csc1);
                if (dim[icp1](1) == 0)
                {
                    cscc1.setZero(3, 2);
                    cscc1 << 0, 1,
                        1, 2,
                        2, 3;
                }
                else if (dim[icp1](1) == 1)
                {
                    cscc1.setZero(4, 2);
                    cscc1 << 0, 1,
                        1, 2,
                        2, 3,
                        3, 0;
                }
                cscc.push_back(cscc1);
                Thickness.push_back(dim[icp1](4) / 1000);
                icp1++;
            }
            else if (sectype[se] == 2)
            {
                UCross3 = UserCross[icp2];
                csp.clear();
                for (int j = 0; j < UCross3.rows(); j++)
                {
                    csp1 = UCross3(j, { 0,1 });
                    for (int k = 0; k < 2; k++)
                    {
                        if (csp.size() == 0)
                            csp.push_back(csp1);
                        else
                        {
                            jp = 0;
                            for (int m = 0; m < csp.size(); m++)
                                if (csp1 == csp[m])
                                    jp++;
                            if (jp == 0)
                                csp.push_back(csp1);
                        }
                        csp1 = UCross3(j, { 2,3 });
                    }
                }
                csc1.setZero(csp.size(), 2);
                cscc1.setZero(UCross3.rows(), 2);
                cvec.setLinSpaced(csp.size(), 0, csp.size() - 1);
                for (int i = 0; i < cvec.size(); i++)
                {
                    for (int j = 0; j < UCross3.rows(); j++)
                    {
                        if (csp[cvec(i)] == UCross3(j, { 0,1 }))
                            cscc1(j, 0) = cvec(i);
                        if (csp[cvec(i)] == UCross3(j, { 2,3 }))
                            cscc1(j, 1) = cvec(i);
                    }
                    csc1(i, all) = csp[i] / 1000;
                }
                csc1(all, 0) = -csc1(all, 0);
                csc.push_back(csc1);
                cscc.push_back(cscc1);
                Thickness.push_back(usthick[icp2] / 1000);
                icp2++;
            }
            else if (sectype[se] == 3)
            {
                csc1.setZero(8, 2);
                csc1 << (-dim[icp1](2) / 2 + dim[icp1](4)) / 1000, -dim[icp1](3) / 2 / 1000,
                    (dim[icp1](2) / 2 - dim[icp1](4)) / 1000, -dim[icp1](3) / 2 / 1000,
                    dim[icp1](2) / 2 / 1000, (-dim[icp1](3) / 2 + dim[icp1](4)) / 1000,
                    dim[icp1](2) / 2 / 1000, (dim[icp1](3) / 2 - dim[icp1](4)) / 1000,
                    (dim[icp1](2) / 2 - dim[icp1](4)) / 1000, dim[icp1](3) / 2 / 1000,
                    (-dim[icp1](2) / 2 + dim[icp1](4)) / 1000, dim[icp1](3) / 2 / 1000,
                    -dim[icp1](2) / 2 / 1000, (dim[icp1](3) / 2 - dim[icp1](4)) / 1000,
                    -dim[icp1](2) / 2 / 1000, (-dim[icp1](3) / 2 + dim[icp1](4)) / 1000;

                csc.push_back(csc1);
                cscc1.setZero(8, 2);
                cscc1 << 0, 1,
                    1, 2,
                    2, 3,
                    3, 4,
                    4, 5,
                    5, 6,
                    6, 7,
                    7, 0;
                cscc.push_back(cscc1);
                Thickness.push_back(dim[icp1](5) / 1000);
                icp1++;
            }
        }
    }
    else
    {
        units = "meters";
        for (int se = 0; se < sectype.size(); se++)
        {
            if (sectype[se] == 0 || sectype[se] == 1)
            {
                csc1.setZero(4, 2);
                csc1 << -dim[icp1](2) / 2, -dim[icp1](3) / 2,
                    dim[icp1](2) / 2, -dim[icp1](3) / 2,
                    dim[icp1](2) / 2, dim[icp1](3) / 2,
                    -dim[icp1](2) / 2, dim[icp1](3) / 2;

                csc.push_back(csc1);
                if (dim[icp1](1) == 0)
                {
                    cscc1.setZero(3, 2);
                    cscc1 << 0, 1,
                        1, 2,
                        2, 3;
                }
                else if (dim[icp1](1) == 1)
                {
                    cscc1.setZero(4, 2);
                    cscc1 << 0, 1,
                        1, 2,
                        2, 3,
                        3, 0;
                }
                cscc.push_back(cscc1);
                Thickness.push_back(dim[icp1](4));
                icp1++;
            }
            else if (sectype[se] == 2)
            {
                UCross3 = UserCross[icp2];
                csp.clear();
                for (int j = 0; j < UCross3.rows(); j++)
                {
                    csp1 = UCross3(j, { 0,1 });
                    for (int k = 0; k < 2; k++)
                    {
                        if (csp.size() == 0)
                            csp.push_back(csp1);
                        else
                        {
                            jp = 0;
                            for (int m = 0; m < csp.size(); m++)
                                if (csp1 == csp[m])
                                    jp++;
                            if (jp == 0)
                                csp.push_back(csp1);
                        }
                        csp1 = UCross3(j, { 2,3 });
                    }
                }
                csc1.setZero(csp.size(), 2);
                cscc1.setZero(UCross3.rows(), 2);
                cvec.setLinSpaced(csp.size(), 0, csp.size() - 1);
                for (int i = 0; i < cvec.size(); i++)
                {
                    for (int j = 0; j < UCross3.rows(); j++)
                    {
                        if (csp[cvec(i)] == UCross3(j, { 0,1 }))
                            cscc1(j, 0) = cvec(i);
                        if (csp[cvec(i)] == UCross3(j, { 2,3 }))
                            cscc1(j, 1) = cvec(i);
                    }
                    csc1(i, all) = csp[i];
                }
                csc1(all, 0) = -csc1(all, 0);
                csc.push_back(csc1);
                cscc.push_back(cscc1);
                Thickness.push_back(usthick[icp2]);
                icp2++;
            }
            else if (sectype[se] == 3)
            {
                csc1.setZero(8, 2);
                csc1 << (-dim[icp1](2) / 2 + dim[icp1](4)), -dim[icp1](3) / 2,
                    (dim[icp1](2) / 2 - dim[icp1](4)), -dim[icp1](3) / 2,
                    dim[icp1](2) / 2, (-dim[icp1](3) / 2 + dim[icp1](4)),
                    dim[icp1](2) / 2, (dim[icp1](3) / 2 - dim[icp1](4)),
                    (dim[icp1](2) / 2 - dim[icp1](4)), dim[icp1](3) / 2,
                    (-dim[icp1](2) / 2 + dim[icp1](4)), dim[icp1](3) / 2,
                    -dim[icp1](2) / 2, (dim[icp1](3) / 2 - dim[icp1](4)),
                    -dim[icp1](2) / 2, (-dim[icp1](3) / 2 + dim[icp1](4));

                csc.push_back(csc1);
                cscc1.setZero(8, 2);
                cscc1 << 0, 1,
                    1, 2,
                    2, 3,
                    3, 4,
                    4, 5,
                    5, 6,
                    6, 7,
                    7, 0;
                cscc.push_back(cscc1);
                Thickness.push_back(dim[icp1](5));
                icp1++;
            }
        }
    }
    Array<double50, -1, 1> alpha, Le, cR;
    double50 beta;
    for (int i = 0; i < csc.size(); i++)
    {
        if (sectype[i] == 2)
        {
            if (cR(0) != 0 && cR(1) != 0)
            {
                csc[i](all, 0) -= cR(0) * Vector<double50, -1>::Ones(csc[i].rows());
                csc[i](all, 1) -= cR(1) * Vector<double50, -1>::Ones(csc[i].rows());
            }
        }
    }

    HO_Materials.setZero(Materials.size(), 4);
    for (int i = 0; i < Materials.size(); i++)
    {
        if (units == "millimeters")
        {
            HO_Materials(i, { 0,2 }) = Materials[i]({ 0,2 });
            HO_Materials(i, 1) = Materials[i](1) * 1e6;
            HO_Materials(i, 3) = Materials[i](3) * 1e12;
        }
        else if (units == "meters")
        {
            HO_Materials(i, { 0,2 }) = Materials[i]({ 0,2 });
            HO_Materials(i, 1) = Materials[i](1);
            HO_Materials(i, 3) = Materials[i](3);
        }
    }

    VectorXd thick(Thickness.size());
    thick.setZero();
    for (int i = 0; i < Thickness.size(); i++)
        thick(i) = double(Thickness[i]);

    vector<int> iN;
    MatrixXi Node_Place(HO_Nodes.rows(), 2);
    for (int i = 0; i < HO_Nodes.rows(); i++)
    {
        iN.clear();
        for (int j = 0; j < HO_Elements.rows(); j++)
        {
            if (HO_Nodes(i, 0) == HO_Elements(j, 2))
                iN.push_back(j);
            if (HO_Nodes(i, 0) == HO_Elements(j, 3))
                iN.push_back(j);
        }
        Node_Place(i, 0) = HO_Nodes(i, 0);
        Node_Place(i, 1) = iN.size();
    }
    vector<int> nE;
    for (int i = 0; i < Node_Place.rows(); i++)
        if (Node_Place(i, 1) == 1)
        {
            for (int j = 0; j < HO_Elements.rows(); j++)
                if (Node_Place(i, 0) == HO_Elements(j, 2))
                    nE.push_back(i);

        }

    MatrixXi NodeEnds = Node_Place(nE, all);

    int kN, jN, iNj = 0;
    bool check1;
    vector<RowVectorXd> belem;
    MatrixXd beam1, pnt1(2, 3);
    vector<MatrixXd> beam, beamcoord;
    vector<int> csnum1;
    MatrixXd besz(HO_Joints.rows(), 8);
    besz.setZero();

    while (iNj < NodeEnds.rows())
    {
        kN = NodeEnds(iNj, 0);
        check1 = true;
        belem.clear();
        pnt1.setZero();
        while (check1)
        {
            jN = kN;
            for (int i = 0; i < HO_Elements.rows(); i++)
            {
                for (int j = 0; j < HO_Joints.rows(); j++)
                {
                    if (kN == HO_Joints(j, 0))
                    {
                        besz(j, 0) = beam.size();
                        besz(j, 1) = HO_Joints(j, 1) - 1;
                    }
                    if (kN == HO_Joints(j, 3))
                    {
                        besz(j, 4) = beam.size();
                        besz(j, 5) = HO_Joints(j, 4) - 1;
                    }
                }
                if (kN == HO_Elements(i, 2))
                {
                    belem.push_back(HO_Elements(i, all));
                    kN = HO_Elements(i, 3);
                    break;
                }
            }
            if (kN == jN)
            {
                check1 = false;
                beam1.setZero(belem.size(), 7);
                for (int k = 0; k < belem.size(); k++)
                    beam1(k, all) = belem[k];
                if (beam1.rows() != 0)
                {
                    beam.push_back(beam1);
                    csnum1.push_back(beam1(0, 1));
                }
                for (int i = 0; i < HO_Nodes.rows(); i++)
                {
                    if (beam1(0, 2) == HO_Nodes(i, 0))
                        pnt1(0, all) = HO_Nodes(i, { 1, 2, 3 });
                    if (beam1(beam1.rows() - 1, 3) == HO_Nodes(i, 0))
                        pnt1(1, all) = HO_Nodes(i, { 1, 2, 3 });
                }
                beamcoord.push_back(pnt1);
            }
        }
        iNj++;
    }

    RowVectorXi csnum(csnum1.size());
    for (int i = 0; i < csnum1.size(); i++)
    {
        for (int j = 0; j < CSMandM.size(); j++)
            if (csnum1[i] == CSMandM[j](0))
                csnum(i) = j;
    }

    Cross_Section csLA;
    int b1, b2, e1, e2;
    RowVectorXd p11, p12, p21, p22;

    for (int i = 0; i < besz.rows(); i++)
    {
        b1 = besz(i, 0), b2 = besz(i, 4);
        e1 = besz(i, 1), e2 = besz(i, 5);
        besz(i, 2) = double(csLA.EdgeLength(csc[csnum(b1)], cscc[csnum(b1)])(e1)) * HO_Joints(i, 2);
        besz(i, 6) = double(csLA.EdgeLength(csc[csnum(b2)], cscc[csnum(b2)])(e2)) * HO_Joints(i, 5);

        p11 = beamcoord[b1](0, all);
        for (int j = 0; j < HO_Nodes.rows(); j++)
            if (HO_Joints(i, 0) == HO_Nodes(j, 0))
                p12 = HO_Nodes(j, { 1, 2, 3 });

        if (units == "millimeters")
            besz(i, 3) = ((p12 - p11) / 1000).norm();
        else
            besz(i, 3) = (p12 - p11).norm();


        p21 = beamcoord[b2](0, all);
        for (int j = 0; j < HO_Nodes.rows(); j++)
            if (HO_Joints(i, 3) == HO_Nodes(j, 0))
                p22 = HO_Nodes(j, { 1, 2, 3 });

        if (units == "millimeters")
            besz(i, 7) = ((p22 - p21) / 1000).norm();
        else
            besz(i, 7) = (p22 - p21).norm();
    }

    MatrixXd xdir(beam.size(), 3), pnts(beam.size() * 2, 3);
    MatrixXi pnt_con_s(beam.size(), 2);
    xdir.setZero(), pnts.setZero();
    RowVector3d ydir, zdir, zi;
    VectorXd zcoordi;
    vector<VectorXd> zcoord;
    double nd1, nd2;

    for (int i = 0; i < beam.size(); i++)
    {
        ydir = beam[i](0, { 4, 5, 6 });
        nd1 = beam[i](0, 2);
        nd2 = beam[i](beam[i].rows() - 1, 3);
        for (int j = 0; j < HO_Nodes.rows(); j++)
        {
            if (nd1 == HO_Nodes(j, 0))
                p11 = HO_Nodes(j, { 1, 2, 3 });
            if (nd2 == HO_Nodes(j, 0))
                p12 = HO_Nodes(j, { 1, 2, 3 });
        }

        if (units == "millimeters")
        {
            zi = (p12 - p11) / 1000;
            zdir = zi / zi.norm();
            xdir(i, all) = ydir.cross(zdir);
            pnts({ 2 * i, 2 * i + 1 }, all) = beamcoord[i] / 1000;
        }
        else
        {
            zi = (p12 - p11);
            zdir = zi / zi.norm();
            xdir(i, all) = ydir.cross(zdir);
            pnts({ 2 * i, 2 * i + 1 }, all) = beamcoord[i];
        }

        zcoordi.setZero(beam[i].rows() + 1);
        for (int j = 0; j < beam[i].rows(); j++)
        {
            nd2 = beam[i](j, 3);
            for (int k = 0; k < HO_Nodes.rows(); k++)
                if (nd2 == HO_Nodes(k, 0))
                    p12 = HO_Nodes(k, { 1, 2, 3 });

            if (units == "millimeters")
            {
                zi = (p12 - p11) / 1000;
                zcoordi(j + 1) = sqrt(pow(zi(0), 2) + pow(zi(1), 2) + pow(zi(2), 2));
            }
            else
            {
                zi = (p12 - p11);
                zcoordi(j + 1) = sqrt(pow(zi(0), 2) + pow(zi(1), 2) + pow(zi(2), 2));
            }
        }
        zcoord.push_back(zcoordi);
    }

    vector<RowVector2d> bni, bci;

    for (int i = 0; i < Forces.size(); i++)
    {
        if (beam.size() > 0)
        {
            for (int j = 0; j < beam.size(); j++)
            {
                for (int k = 0; k < beam[j].rows(); k++)
                {
                    if (Forces[i](0) == beam[j](k, 2))
                    {
                        bni.push_back({ j,k });
                        break;
                    }
                    else if (Forces[i](0) == beam[j](k, 3))
                    {
                        bni.push_back({ j,k + 1 });
                        break;
                    }
                }
            }
        }

    }

    for (int i = 0; i < BoundCs.size(); i++)
    {
        for (int j = 0; j < beam.size(); j++)
        {
            for (int k = 0; k < beam[j].rows(); k++)
            {
                if (BoundCs[i](0) == beam[j](k, 2))
                {
                    bci.push_back({ j,k });
                    break;
                }
                else if (BoundCs[i](0) == beam[j](k, 3))
                {
                    bci.push_back({ j,k + 1 });
                    break;
                }
            }
        }
    }


    FNode.setZero(fcs.size(), 5);
    FEdge.setZero(Forces.size() - fcs.size(), 6);
    int fni = 0, fei = 0;
    for (int i = 0; i < Forces.size(); i++)
    {
        if (Forces[i].size() == 3)
        {
            FNode(fni, 0) = fcs[fni];
            FNode(fni, { 1,2 }) = bni[i];
            FNode(fni, { 3,4 }) = Forces[i]({ 1,2 });
            fni++;
        }
        else if (Forces[i].size() == 5)
        {
            FEdge(fei, { 0,1 }) = bni[i];
            FEdge(fei, { 2,3,4,5 }) = Forces[i]({ 1,2,3,4 });
            fei++;
        }
    }

    HO_BCs.setZero(bci.size(), 5);
    for (int i = 0; i < bci.size(); i++)
    {
        HO_BCs(i, 0) = bcs[i];
        HO_BCs(i, { 1,2 }) = bci[i];
        HO_BCs(i, { 3,4 }) = BoundCs[i]({ 1,2 });
    }

    VectorXi Nel, Nn; Nel.setZero(zcoord.size());
    for (int i = 0; i < zcoord.size(); i++)
        Nel(i) = zcoord[i].size() - 1;
    Nn = Nel + VectorXi::Ones(Nel.size());

    vector<RowVector3d> pnts1;
    for (int i = 0; i < pnts.rows(); i++)
        pnts1.push_back(pnts(i, all));

    std::sort(pnts1.begin(), pnts1.end(), [](Eigen::RowVectorXd const& t1, Eigen::RowVectorXd const& t2) { return t1(0) < t2(0); });
    auto it = std::unique(pnts1.begin(), pnts1.end());
    pnts1.resize(std::distance(pnts1.begin(), it));

    MatrixXd pnt_s(pnts1.size(), 3);
    for (int i = 0; i < pnts1.size(); i++)
        pnt_s(i, all) = pnts1[i];

    if (units == "millimeters")
    {
        for (int i = 0; i < beamcoord.size(); i++)
            for (int j = 0; j < pnt_s.rows(); j++)
            {
                if (beamcoord[i](0, all) / 1000 == pnt_s(j, all))
                    pnt_con_s(i, 0) = j;
                if (beamcoord[i](1, all) / 1000 == pnt_s(j, all))
                    pnt_con_s(i, 1) = j;
            }
    }
    else
    {
        for (int i = 0; i < beamcoord.size(); i++)
            for (int j = 0; j < pnt_s.rows(); j++)
            {
                if (beamcoord[i](0, all) == pnt_s(j, all))
                    pnt_con_s(i, 0) = j;
                if (beamcoord[i](1, all) == pnt_s(j, all))
                    pnt_con_s(i, 1) = j;
            }
    }

    for (int i = 0; i < csc.size(); ++i)
        cout << "csc[" << i << "] =\n" << csc[i] << endl << endl;//
    for (int i = 0; i < cscc.size(); ++i)
        cout << "cscc[" << i << "] =\n" << cscc[i] << endl << endl;
    cout << "csnum =\n" << csnum << endl << endl;
    cout << "xdir=\n" << xdir << "\n\n";
    cout << "pnt_s =\n" << pnt_s << endl << endl;
    cout << "pnt_con_s =\n" << pnt_con_s << endl << endl;
    cout << "besz =\n" << besz << endl << endl;
    cout << "thick =\n" << thick << endl << endl;
    cout << "ModenMat =\n" << ModenMat << endl << endl;
    cout << "HO_Materials =\n" << HO_Materials << endl << endl;
    cout << "FNode =\n" << FNode << endl << endl;
    cout << "FEdge =\n" << FEdge << endl << endl;
    cout << "HO_BCs =\n" << HO_BCs << endl << endl;
    for (int i = 0; i < zcoord.size(); ++i)
        cout << "zcoord[" << i << "] =\n" << zcoord[i] << endl << endl;
    cout << "Nel =\n" << Nel << endl << endl;
    cout << "Nn =\n" << Nn << endl << endl;
    cout << "analysis =\n" << analysis << endl << endl;
    cout << "freq =\n" << freq << endl << endl;
    cout << "NW1 =\n" << NW1 << endl << endl;
    cout << "FRF =\n" << FRF << endl << endl;
    cout << "units =\n" << units << endl << endl;
    int freqn = 0, un;
    freq = freqn;
    if (freqn == 0)
        freqn = 20;

    if (units == "millimeters")
        un = 1000;
    else
        un = 1;

    MatrixXd enr_s(csnum.size(), 3);
    VectorXd t_s(csnum.size());
    for (int i = 0; i < csnum.size(); i++)
    {
        t_s(i) = thick(csnum(i)); // 두께받기
        for (int j = 0; j < HO_Materials.rows(); j++)
            if (ModenMat(csnum(i), 1) + 1 == HO_Materials(j, 0))
                enr_s(i, all) = HO_Materials(j, { 1,2,3 });  //재료 물성치 받기
    }

    //cout << "ModenMat =\n" << ModenMat << endl << endl;
    //cout << "enr_s =\n" << enr_s << endl << endl;


    //cout << "Deriving Cross-Sectional Modes!!" << endl << endl;
    VectorXi Mset(ModenMat.rows());
    for (int i = 0; i < ModenMat.rows(); i++)
    {
        if (ModenMat(i, 2) == 0)
            Mset(i) = 2;
        else
            Mset(i) = ModenMat(i, 2);
    }
    Matrix<double50, -1, -1> csc_i, cT;
    MatrixXi cscc_i, settab_i;
    double50 betaR, betaT;
    vector<MatrixXd> coef_s_i, coef_n_i, coef_z_i;
    vector<vector<MatrixXd>> coef_s, coef_n, coef_z;
    vector<MatrixXi> settab;
    MatrixXi modeNo(csc.size(), 4);

    for (int i = 0; i < csc.size(); i++)
    {
        cout << "Cross_Section no.:  " << i << endl << endl;
        csc_i = csc[i];
        cscc_i = cscc[i];
        settab_i.setZero(Mset(i) + 1, 3);
        //cout << "Mset(i) =\n" << Mset(i) << endl << endl;
        //cout << "settab_i =\n" << settab_i << endl << endl;

        tie(coef_s_i, coef_n_i, coef_z_i, settab_i) = Modegen(csc_i, cscc_i, Mset(i), settab_i); // Mset(i) for diiferent mode sets for different crosssections
        settab_i(1, 0) += 2;
        modeNo(i, all) << i, coef_s_i[0].cols(), coef_n_i[0].cols(), coef_z_i[0].cols();
        coef_s.push_back(coef_s_i);
        coef_n.push_back(coef_n_i);
        coef_z.push_back(coef_z_i);
        settab.push_back(settab_i);
    }
   /* for(int i = 0 ; i <coef_z.size();i++)
    for (int j = 0; j < coef_z[i].size(); ++j)
        cout << "coef_z[" << i << "]["<<j<<"] = \n" << coef_z[i][j] << endl << endl;
    for (int i = 0; i < coef_n.size(); i++)
        for (int j = 0; j < coef_n[i].size(); ++j)
            cout << "coef_n[" << i << "][" << j << "] = \n" << coef_n[i][j] << endl << endl;

    for (int i = 0; i < coef_s.size(); i++)
        for (int j = 0; j < coef_s[i].size(); ++j)
            cout << "coef_s[" << i << "][" << j << "] = \n" << coef_s[i][j] << endl << endl;*/

    cout << "Cross-sectional Modes Derived!!" << endl << endl;
    vector<MatrixXd> cscd; cscd.resize(csc.size());
    for (int j = 0; j < csc.size(); j++)
    {
        cscd[j].setZero(csc[j].rows(), 2);
        for (int i = 0; i < csc[j].rows(); i++)
        {
            cscd[j](i, 0) = static_cast<double>(csc[j](i, 0));
            cscd[j](i, 1) = static_cast<double>(csc[j](i, 1));
        }
    }
    for (int i = 0; i < cscd.size(); ++i)
        cout << "cscd[" << i << "] =\n" << cscd[i] << endl << endl;//

    cout << "Starting Stiffness and Mass Matrices Derivations!" << endl << endl;
    VectorXd L;
    vector<MatrixXi> Ki, Kj, Mi, Mj;
    vector<MatrixXd> Kall, Mall;
    vector<Matrix3d> shellTransform;
    VectorXi Nmode;
    MatrixXd Kse, Mse;
    MatrixXi ShellNdof;
    VectorXi Nels;
    Nels = Nel;
    tie(Ki, Kj, Mi, Mj, Kall, Mall, L, Nmode) = sysmat(cscd, cscc, coef_s, coef_n, coef_z, pnt_s, pnt_con_s, csnum, besz, t_s, enr_s, zcoord, Nels);

    cout << "Stiffness and Mass Matrices Derived!" << endl << endl;

	return 0;
}

