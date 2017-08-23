#include"piece.hpp"
#include<algorithm>
#include<cstdlib>	//// abs() for integer
#define PI 3.14159265358979

//�ǂꂾ����]���邩�Ɗ�_�̍��W�𑗂��]��̍��W��Ԃ�
Point PointRotate(double angle, Point zeroPoint) {
	Point r;
	r.x = round(zeroPoint.x*cos(angle) - zeroPoint.y*sin(angle));
	r.y = round(zeroPoint.x*sin(angle) + zeroPoint.y*cos(angle));
	return r;
}

//��]�ジ�炷���߂�x��y�̍ŏ��l���擾
Point MinPoint(std::vector<Point> &data){
	Point min;
	min.x=0;min.y=0;
	for(int i=0;i<data.size();i++){
		if(min.x>std::abs(data[i].x))min.x=data[i].x;
		if(min.y>std::abs(data[i].y))min.y=data[i].y;
	}
	return min;
}

Piece::Piece(std::vector<Point> &data){
  int num = data.size();     				//���_��
  std::vector<Point> tmp(num); 			//1��]�p�^�[���̈ꎞ�i�[�z��
  
  for (int i = 0; i<4; i++){  			//4���](90�x����)
	Point min;	//���炷���߂Ɏ擾������W�ŏ��l
	//printf("--��]�p�^�[��[%d��/2]--\n", i); //debug
	for (int j = 0; j < num; j++) {
	  tmp[j] = PointRotate((1.0 / 2.0)*i*PI, data[j]);
	  if (j == 0) { min.x = tmp[j].x; min.y = tmp[j].y; }
	  //printf("�O%d,%d\n",tmp[j].x, tmp[j].y); //debug
	  min.x = std::min(min.x, tmp[j].x);
	  min.y = std::min(min.y, tmp[j].y);
	}
	move(tmp, Point(-min.x,-min.y));
	point.push_back(tmp); //��̉�]�p�^�[����pushback
  }
}

std::vector<std::vector<Point>> Piece::getPoint(){
  return point;
}

int Piece::getSize() {
  return static_cast<int>(point[0].size());
}
