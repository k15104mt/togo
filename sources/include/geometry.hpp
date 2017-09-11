#ifndef _GEOMETRY_HPP_
#define _GEOMETRY_HPP_
#define MAX 256

#include"utility.hpp"
#include"piece.hpp"
#include<vector>

struct D_Point {
	double x;
	double y;
};

class Geometry {
public:
	Point getPutPoint(std::vector<Piece> &data, std::vector<putData> &already_put);
	std::vector<std::vector<Point>> areaPoint;
	Geometry(std::vector<std::vector<Point>> framePoint);
private:
	int putNum;
	int getPutNum() { return putNum; }
};

//����(�s�[�X���,�ݒu���,�t���[�����)�ō��㒸�_���W��Ԃ�
Point getPutPoint(std::vector<Piece>&, std::vector<putData>&,std::vector<std::vector<Point>>);

//����(�}�`��񑦂�Point��vector)�ŕԂ�l�͎��v���Ȃ�1���C�����v���Ȃ�-1���C�˂���Ă���Ȃ�0
int CheckAngle(std::vector<Point> point);

#endif
