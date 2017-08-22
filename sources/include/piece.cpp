#include"piece.hpp"
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
	Point min;min.x=0,min.y=0;				//���炷���߂Ɏ擾������W�ŏ��l

	for (int i = 0; i<4; i++){  			//4���](90�x����)
    //printf("--��]�p�^�[��[%d��/2]--\n", i); //debug
    for (int j = 0; j < num; j++) {
      tmp[j] = PointRotate((1.0 / 2.0)*i*PI, data[j]);
			//printf("�O%d,%d\n",tmp[j].x, tmp[j].y); //debug
			if(min.x>tmp[j].x)min.x=tmp[j].x;
			if(min.y>tmp[j].y)min.y=tmp[j].y;
    }

		if(min.x<0){
			for(int j=0;j<num;j++){
				tmp[j].x+=std::abs(min.x);
				//printf("��%d,%d\n",tmp[j].x, tmp[j].y); //debug
			}
		}
		if(min.y<0){
			for(int j=0;j<num;j++){
				tmp[j].y+=std::abs(min.y);
				//printf("��%d,%d\n",tmp[j].x, tmp[j].y); //debug
			}
		}
    point.push_back(tmp); //��̉�]�p�^�[����pushback
		min.x=0; min.y=0;
  }
}

std::vector<std::vector<Point>> Piece::getPoint(){
  return point;
}

int Piece::getSize() {
  return static_cast<int>(point[0].size());
}
