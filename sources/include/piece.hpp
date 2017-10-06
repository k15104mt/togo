#ifndef _PIECE_HPP_
#define _PIECE_HPP_
#define UP 1
#define RIGHT 2
#define LEFT 3
#define DOWN 4
#define UP_LEFT 5

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
  double surface;							//�s�[�X�ʐ�
  double minAngle;	//�s�[�X���̍ŏ��p�x
  double minSide;	//�s�[�X�̍ŏ��̕ӂ̒���
public:
  Piece(std::vector<Point> &data);
  std::vector<std::vector<Point>> getPoint() const;
  int getSize();
  double getMinAngle();
  double getMinSide();
  double getSurface();
  Point getShapeEdge(int eleNum,int putMode);	//����1:��]�ԍ�,����2:UP�Ƃ�LEFT
};

double calculateAngle(std::vector<Point> &point);
double calculateSurface(std::vector<Point> &data);
#endif
