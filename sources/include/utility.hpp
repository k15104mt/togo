#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include<vector>
#include<cmath>

class Point{
public:
	int x,y;
	Point() {};
	Point(int x,int y):x(x),y(y){};

	Point operator + (Point &obj){return Point(x+obj.x,y+obj.y);};
	Point operator - (Point &obj){return Point(x-obj.x,y-obj.y);};
	Point & operator = (Point &obj){x = obj.x; y = obj.y; return *this;};
	Point & operator += (Point &obj) { x += obj.x; y += obj.y; return *this; };
	bool operator == (Point &obj){return x==obj.x && y==obj.y;};

	double size() { return sqrt(x*x + y*y); };
	void print() { printf("(%d,%d)", x, y); };
	void println() { printf("(%d,%d)\n", x, y); };
};

//�ݒu���
class putData {
public:
  putData(int, int, int, Point&);

  int piece_num;//�s�[�X
  int point_num;//��]
  int vertex_num;//���_
  Point base_point;//���_���ǂ̈ʒu��

};

//�x�N�g���������^�݂����Ȃ��̂��������͂�
using Vector = Point;

//���σB�I�I
int dot(Vector&,Vector&);
//�O�σB�I�I
int cross(Vector&,Vector&);

void move(std::vector<Point>&, Point);

//���ׂĂ̕ӂ����Č�����Ă�����̂��������ꍇ�͂P��Ԃ�
int crossLine(std::vector<Point>&,std::vector<Point>&);

//�������̃|���S���ɑ������̂��ׂĂ̒��_�������Ă���ꍇ�܂���
//�������̃|���S���ɑ������̂��ׂĂ̒��_�������Ă���ꍇ��1��Ԃ�
//�ԏ�ɂ���ꍇ�������ɓ����Ă�����̂Ƃ���
int inPolygon(std::vector<Point>&,std::vector<Point>&);

int collisionPiece(std::vector<Point>&,std::vector<Point>&);

int collisionFrame(std::vector<Point>&,std::vector<Point>&);

#endif
