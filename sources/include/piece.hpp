#ifndef _PIECE_HPP_
#define _PIECE_HPP_
#define UP 0
#define RIGHT 1
#define LEFT 2
#define DOWN 3
#define UP_LEFT 4

#include<vector>
#include"utility.hpp"

struct D_Point {
	double x;
	double y;
};

class Piece {
private:
	std::vector<std::vector<Point>> point;	//���_���W
	std::vector < std::vector<Point> > shapeEdge;	//�e��]��Ԃł̏�A�E�A���A���A����̒��_���W
	double surface;	//�s�[�X�ʐ�
	double minAngle;	//�s�[�X���̍ŏ��p�x
	//double minSide;	//�s�[�X�̍ŏ��̕ӂ̒���
   // std::vector< std::vector<std::pair<int, int>>> edgeNum;	//�e�[�̓_�̗v�f�ԍ�(��E��������̏��Ɋi�[),vector�́A�e��]�v�f�̒��ɁA�e�㉺���E�̃y�A������
	std::vector<std::vector<int>> edgeNum;	//�e�[�̓_�̒��_�ԍ�(��E��������̏�)
public:
	Piece(std::vector<Point> &data);
	std::vector<std::vector<Point>> getPoint() const;
	int getSize();
	double getMinAngle();
	//double getMinSide();
	double getSurface();
	Point getShapeEdge(int eleNum, int putMode);	//����1:��]�ԍ�,����2:UP�Ƃ�LEFT
	//std::pair<int,int> getEdgeNum(int rotateNum,int putMode);		//�s�[�X�̒[�̗v�f�ԍ�(����:��]�ԍ�,UP�Ƃ�LEFT)
	int getEdgeNum(int rotateNum, int putMode);		//�s�[�X�̒[�̗v�f�ԍ�(����:��]�ԍ�,UP�Ƃ�LEFT)
};

int shapeEquals(std::vector<Point> &tmp, std::vector<std::vector<Point>> &point);
double calculateSide(std::vector<Point> &point);
double calculateAngle(std::vector<Point> &point);
double calculateSurface(std::vector<Point> &data);
#endif
