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
	Point getPutPoint(std::vector<Piece> &data, std::vector<putData> &already_put);	//�ݒu��������W�擾
	void cancelPut();																//�ݒu������O��
	std::vector<std::vector<Point>> areaPoint;										//���ݒu���G���A�̏��
	Geometry(std::vector<std::vector<Point>> &framePoint);							//�R���X�g���N�^
private:
	std::vector<std::vector<Point>> tmpAreaPoint;		//cancel�p�̐ݒu�O�G���A�ێ�
	int putNum;
};

#endif
