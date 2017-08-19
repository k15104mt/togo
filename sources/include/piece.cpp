#include"piece.hpp"
#define PI 3.14159265358979

//�ǂꂾ����]���邩�Ɗ�_�̍��W�𑗂��]��̍��W��Ԃ�
Point PointRotate(double angle, Point zeroPoint) {
	Point r;
	r.x = round(zeroPoint.x*cos(angle) - zeroPoint.y*sin(angle));
	r.y = round(zeroPoint.x*sin(angle) + zeroPoint.y*cos(angle));
	return r;
}

Piece::Piece(std::vector<Point> &data){
  int num = data.size();     //���_��
  std::vector<Point> tmp(num); //1��]�p�^�[���̈ꎞ�i�[�z��

  for (int i = 0; i<4; i++){  //4���](90�x����)
    //printf("--��]�p�^�[��[%d��/2]--\n", i); //debug
    for (int j = 0; j < num; j++) {
      tmp[j] = PointRotate((1.0 / 2.0)*i*PI, data[j]);
			//printf("%d,%d\n",tmp[j].x, tmp[j].y); //debug
    }
    point.push_back(tmp); //��̉�]�p�^�[����pushback
  }
}

std::vector<std::vector<Point>> Piece::getPoint(){
  return point;
}

int Piece::getSize() {
  return static_cast<int>(point[0].size());
}
