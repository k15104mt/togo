#ifndef _PIECE_HPP_
#define _PIECE_HPP_

#include<vector>
#include"utility.hpp"

struct D_Point {
	double x;
	double y;
};

class Piece {
private:
  std::vector<std::vector<Point>> point;	//���_���W
  std::vector<Point> upperLeft;	//�e��]��Ԃł̍��㒸�_���W
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
  Point getUpperLeft(int);
};


#endif
