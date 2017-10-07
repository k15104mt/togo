#include"piece.hpp"
#include<algorithm>
#include<cstdlib>	// fabs()
#define NOMINMAX
#include<color.hpp>
#define PI 3.14159265358979

//std::vector<Point> calculateEdge(std::vector<Point> &areaPoint, std::vector<std::vector<std::pair<int, int>>> &shapeNum);
std::vector<Point> calculateEdge(std::vector<Point> &areaPoint, std::vector<std::vector<int>> &edgeNum);
double calculateAngle(std::vector<Point> &point);
double calculateSide(std::vector<Point> &point);

//�ǂꂾ����]���邩�Ɗ�_�̍��W�𑗂��]��̍��W��Ԃ�
Point PointRotate(double angle, Point zeroPoint) {
  Point r;
  r.x = static_cast<int>(round(zeroPoint.x*cos(angle) - zeroPoint.y*sin(angle)));
  r.y = static_cast<int>(round(zeroPoint.x*sin(angle) + zeroPoint.y*cos(angle)));
  return r;
}

//���_�̏����t��(�����v��聨���v���)
void reverse(std::vector<Point> &data) {
  int	i, tmpx, tmpy, n = data.size();
  for (i = 0; i < n / 2; ++i) {
	tmpx = data[i].x;
	tmpy = data[i].y;
	data[i].x = data[n - i - 1].x;
	data[i].y = data[n - i - 1].y;
	data[n - i - 1].x = tmpx;
	data[n - i - 1].y = tmpy;
  }
}

//�ۑ��ςݐ}�`(point)�ɐ��������}�`(tmp)�Ɠ��������̂����邩�ǂ���
int shapeEquals(std::vector<Point> &tmp, std::vector<std::vector<Point>> &point) {
	int num = point[0].size();
  for (int j = 0; j < static_cast<int>(point.size()); j++) {
	for (int k = 0; k < num; k++) {
	  if (tmp[0] == point[j][k]) {
		int count = 0;
		int k_ = k;
		//setColor(F_ORANGE | F_INTENSITY); printf("[%d][%d](%d,%d)\n", j, k_, point[j][k_].x, point[j][k_].y); setColor();
		while (count<num) {
		  if (k_ >= num)k_ = 0;
		  if (tmp[count] == point[j][k_]) {
			//setColor(F_RED | F_INTENSITY); printf("tmp[%d]==point[%d][%d]\n", count, j, k_); setColor();
			count++;
		  }
		  else {
			//setColor(F_RED | F_INTENSITY); printf("�����܂���ł���\n"); setColor();
			break;
		  }
		  k_++;
		}
		if (count == num) {
		  //printf("�����܂����I\n");
		  return j;
		}
	  }
	}
	//printf("\n");
  }
  return -1;
}


Piece::Piece(std::vector<Point> &data) {
  int num = data.size();     		//���_��
  double sigma = 0;					//�ʐς����߂�����ɂ�����V�O�}
  std::vector<Point> tmp(num); 		//1��]�p�^�[���̈ꎞ�i�[�z��
									//printf("num:%d\n", num);

									//�s�[�X�̖ʐς����߂�
  for (int i = 0; i < num; i++) {
	if (i == num - 1) {
	  sigma += (double)(data[i].x * data[0].y - data[0].x * data[i].y);
	}
	else {
	  sigma += (double)(data[i].x * data[i + 1].y - data[i + 1].x * data[i].y);
	}
  }
  surface = fabs((1.0 / 2.0)*sigma);
  //printf("debug>�ʐς�%lf\n", surface);

  //////////////////////////////��]���č��W//////////////////////////////////////////
  for (int i = 0; i<4; i++) {  			//4���](90�x����)
	Point min;	//���炷���߂Ɏ擾������W�ŏ��l
	//setColor(F_CYAN | F_INTENSITY); printf("\n--��]�p�^�[��[%d��/2]--\n", i); setColor();//debug
	for (int j = 0; j < num; j++) {
	  tmp[j] = PointRotate((1.0 / 2.0)*i*PI, data[j]);
	  if (j == 0) { min.x = tmp[j].x; min.y = tmp[j].y; }
	  min.x = std::min(min.x, tmp[j].x);
	  min.y = std::min(min.y, tmp[j].y);
	}
	move(tmp, Point(-min.x, -min.y));
	//for(int j=0;j<num;j++) printf("(%d,%d)\n", tmp[j].x, tmp[j].y); //debug

	if (i == 0 || shapeEquals(tmp, point)!=-1) {
	  point.push_back(tmp); //��̉�]�p�^�[����pushback
	  shapeEdge.push_back(calculateEdge(tmp,edgeNum));		//�[�̍��W���i�[
	}

	//setColor(F_GREEN | F_INTENSITY); printf("\n--���]�p�^�[��[%d��/2]--\n", i); setColor();
	for (int j = 0; j < num; j++) {
	  tmp[j] = tmp[j] = PointRotate((1.0 / 2.0)*i*PI, data[j]);
	  tmp[j].x *= -1;
	  if (j == 0) { min.x = tmp[j].x; min.y = tmp[j].y; }
	  min.x = std::min(min.x, tmp[j].x);
	  min.y = std::min(min.y, tmp[j].y);
	}
	move(tmp, Point(-min.x, -min.y));
	reverse(tmp);
	//for (int j = 0; j<num; j++) printf("(%d,%d)\n", tmp[j].x, tmp[j].y); //debug

	if (shapeEquals(tmp, point)!=-1) {
	  point.push_back(tmp); //��̔��]�p�^�[����pushback
	  shapeEdge.push_back(calculateEdge(tmp,edgeNum));		//�[�̍��W���i�[
	}
  }
  minAngle= calculateAngle(point[0]);
 // minSide = calculateSide(point[0]);
}

std::vector<std::vector<Point>> Piece::getPoint() const {
  return point;
}

int Piece::getSize() {
  return static_cast<int>(point[0].size());
}

double Piece::getSurface() {
  return surface;
}

//double Piece::getMinSide() {
//	return minSide;
//}

double Piece::getMinAngle() {
	return minAngle;
}

//std::pair<int, int> Piece::getEdgeNum(int rotateNum,int putMode) {
int Piece::getEdgeNum(int rotateNum, int putMode) {
	return edgeNum[rotateNum][putMode];
}


// �}�`�̏㉺���E���_���i�[
//std::vector<Point> calculateEdge(std::vector<Point> &areaPoint, std::vector<std::vector<std::pair<int, int>>> &edgeNum) {
std::vector<Point> calculateEdge(std::vector<Point> &areaPoint, std::vector<std::vector<int>> &edgeNum) {
  int tall;			//���������� y=-x+b ��b
  Point up, left, right, down,upperLeft;
  std::vector<Point> tmp;
  /*
  std::vector<std::pair<int, int>> tmpNum;
  std::pair<int, int> upN;
  std::pair<int, int> rightN;
  std::pair<int, int> leftN;
  std::pair<int, int> downN;
  std::pair<int, int> up_leftN;
  */
  std::vector<int> tmpNum(5);


  for (int i = 0; i < (int)areaPoint.size(); i++) {
	//printf("{%d,%d} ", areaPoint[i].x, areaPoint[i].y);

	if (i == 0) {	//�b��
	  tall = areaPoint[i].x + areaPoint[i].y;
	  upperLeft= areaPoint[i];
	  up = left = right = down = upperLeft=areaPoint[i];
	  //upN.first = leftN.first = rightN.first = downN.first = up_leftN.first = edgeNum.size();
	  //upN.second = leftN.second = rightN.second = downN.second = up_leftN.second = edgeNum.size();
	}
	else if (tall > areaPoint[i].x + areaPoint[i].y) {	//�ŏ�
	  tall = areaPoint[i].x + areaPoint[i].y;
	  upperLeft = areaPoint[i]; 
	  //up_leftN.second = i;
	  tmpNum[UP_LEFT] = i;
	}
	else if (tall == areaPoint[i].x + areaPoint[i].y &&upperLeft.x > areaPoint[i].x) {	//tall�̒l�������Ȃ��x������������D��
		tall = areaPoint[i].x + areaPoint[i].y;
		upperLeft = areaPoint[i];
		//up_leftN.second = i;
		tmpNum[UP_LEFT] = i;
	}
	//��
	if (up.y > areaPoint[i].y || (up.y==areaPoint[i].y&&up.x>areaPoint[i].x )) {
		up = areaPoint[i];
		//upN.second = i;
		tmpNum[UP] = i;
	}
	//��
	if (down.y < areaPoint[i].y || (down.y == areaPoint[i].y&&down.x > areaPoint[i].x)) {
		down = areaPoint[i];
		//downN.second = i;
		tmpNum[DOWN] = i;
	}
	//��
	if (left.x > areaPoint[i].x || (left.x == areaPoint[i].x&&left.y > areaPoint[i].y)) {
		left = areaPoint[i];
		//leftN.second = i;
		tmpNum[LEFT] = i;
	}
	//�E
	if (right.x < areaPoint[i].x || (right.x == areaPoint[i].x&&right.y > areaPoint[i].y)) {
		right = areaPoint[i];
		//rightN.second = i;
		tmpNum[RIGHT] = i;
	}
  }

  tmp.push_back(up);
  tmp.push_back(right);
  tmp.push_back(left);
  tmp.push_back(down);
  tmp.push_back(upperLeft);
  /*tmpNum.push_back(upN);
  tmpNum.push_back(rightN);
  tmpNum.push_back(leftN);
  tmpNum.push_back(downN);
  tmpNum.push_back(up_leftN);*/
  edgeNum.push_back(tmpNum);
  //printf("��(%d,%d) �E(%d,%d) ��(%d,%d) ��(%d,%d)\n",up.x,up.y,right.x, right.y, left.x, left.y ,down.x, down.y);
  //printf("�b�荶��(%d,%d),tall:%d\n", point.x, point.y, tall);
  return tmp;
}

Point Piece::getShapeEdge(int eleNum, int putMode) {
  return shapeEdge[eleNum][putMode];
}

//�x�N�g���̒������v�Z����
double get_vector_length(Point v) {
	return pow((v.x * v.x) + (v.y * v.y), 0.5);
}

double calculateAngle(std::vector<Point> &point) {
	Point a, b,C,P,Q;	//aux:�⏕���̃x�N�g��
	double angle,min=360;
	for (int i = 0; i < static_cast<int>(point.size()); i++) {
		//�x�N�g���ɂ��Ă�
		if (i == 0) {
			a = point[0] - point[point.size() - 1];
			C = point[point.size() - 1];
		}
		else {
			a = point[i] - point[i - 1];
			C = point[i - 1];
		}

		if (i == point.size() - 1) {
			b = point[0] - point[i];
			Q = point[0];
		}
		else {
			b = point[i + 1] - point[i];
			Q = point[i+1];
		}

		P = point[i];

		//�x�N�g��A��B�̒������v�Z����
		double length_A = get_vector_length(a);
		double length_B = get_vector_length(b);
		//���ςƃx�N�g���������g���Ċp�x�����߂�
		angle =acos( dot(a, b) / (length_A*length_B));
		angle =180- (angle*180.0 / PI);

		if (((P.x - C.x)*(Q.y - C.y) - (P.y - C.y)*(Q.x - C.x)) < 0) {
			angle = 360 - angle;
		}
		//printf("�x�N�g��(%d,%d)��(%d,%d)�̊p�x��%lf\n", a.x, a.y, b.x, b.y, angle);
		if (angle < min)min = angle;	//�ŏ��l�擾
		
	}
	
	return min;
}

double calculateSide(std::vector<Point> &point) {
	Point a, b;
	double len,min=100000;

	for (int i = 0; i < static_cast<int>(point.size()); i++) {
		a = point[i];
		if (i == point.size()-1)b = point[0];
		else b = point[i + 1];

		len = sqrt((double)(b.x-a.x)*(b.x - a.x)+(b.y-a.y)*(b.y - a.y));
		if (i == 0 || len<min)min = len;
	}
	return min;
}

//�ʐς��擾
double calculateSurface(std::vector<Point> &data) {
	int num = data.size();     		//���_��
	double sigma = 0;					//�ʐς����߂�����ɂ�����V�O�}

										//�ʐς����߂�
	for (int i = 0; i < num; i++) {
		if (i == num - 1) {
			sigma += (double)(data[i].x * data[0].y - data[0].x * data[i].y);
		}
		else {
			sigma += (double)(data[i].x * data[i + 1].y - data[i + 1].x * data[i].y);
		}
	}

	return fabs((1.0 / 2.0)*sigma);
}