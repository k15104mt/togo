#include"utility.hpp"

#include<sstream>



std::vector<std::string> split(std::string input, char spilit_character) {
  std::stringstream stream(input);

  std::vector<std::string> result;
  std::string temp;
  while (std::getline(stream, temp, spilit_character)) {
	result.push_back(temp);
  }

  return result;
}


putData::putData(int piece_num, int point_num, int vertex_num, Point &base_point) :
  piece_num(piece_num), point_num(point_num), vertex_num(vertex_num), base_point(base_point) {}


//���σB�I�I
int dot(Vector &a, Vector &b) {
  return a.x * b.x + a.y * b.y;
}

//�O�σB�I�I
int cross(Vector &a, Vector &b) {
  return a.x * b.y - a.y * b.x;
}

//�n���ꂽvector�̒l�𒼐ڕς��邩�璍��
void move(std::vector<Point> &data, Point movingDistance) {
  for (auto &i : data) {
	i += movingDistance;
  }
}


//��̐����̎n�_�A�I�_����A�������m���������Ă��邩��Ԃ�
//���������s�ȏꍇ�͌������Ă��Ȃ����̂ƂȂ�
int cl(Point &Line1Start, Point &Line1End,
  Point &Line2Start, Point &Line2End) {

  if ((((Line1Start.x - Line1End.x)*(Line2Start.y - Line1Start.y) +
	(Line1Start.y - Line1End.y)*(Line1Start.x - Line2Start.x))*
	((Line1Start.x - Line1End.x)*(Line2End.y - Line1Start.y) +
	(Line1Start.y - Line1End.y)*(Line1Start.x - Line2End.x)) < 0) &&
	  (((Line2Start.x - Line2End.x)*(Line1Start.y - Line2Start.y) +
	(Line2Start.y - Line2End.y)*(Line2Start.x - Line1Start.x))*
		((Line2Start.x - Line2End.x)*(Line1End.y - Line2Start.y) +
		(Line2Start.y - Line2End.y)*(Line2Start.x - Line1End.x)) < 0)) {
	return 1;
  }

  return 0;
}

int crossLine(std::vector<Point> &data1, std::vector<Point> &data2) {
  for (int i = 0; i < static_cast<int>(data1.size()); ++i) {
	for (int j = 0; j < static_cast<int>(data2.size()); ++j) {
	  if (cl(data1[i], data1[(i + 1) % static_cast<int>(data1.size())],
		data2[j], data2[(j + 1) % static_cast<int>(data2.size())])) {
		return 1;
	  }
	}
  }
  return 0;
}

//data1��data�Q�̒��_�����ׂē����Ă�
int inPolygon(std::vector<Point> &data1, std::vector<Point> &data2) {
  for (int i = 0; i < static_cast<int>(data2.size()); ++i) {
	for (int j = 0; j < static_cast<int>(data1.size()); ++j) {

	  if (data1[j] == data2[i]) {
		if (cross(data1[j] - data1[(j + data1.size() - 1) % data1.size()],
		  data1[(j + 1) % data1.size()] - data1[(j + data1.size() - 1) % data1.size()]) > 0) {

		  if (cross(data1[(j + data1.size() - 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) <= 0 &&
			cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) >= 0) {

		  }
		  else {
			return 0;
		  }

		}
		else if (cross(data1[j] - data1[(j + data1.size() - 1) % data1.size()],
		  data1[(j + 1) % data1.size()] - data1[(j + data1.size() - 1) % data1.size()]) < 0) {

		  if (cross(data1[(j + data1.size() - 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) > 0 &&
			cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) < 0) {
			return 0;
		  }

		}
	  }

	  /*
	  if (data1[j] == data2[i]) {
	  if (cross(data1[j] -data1[(j + data1.size() - 1) % data1.size()],
	  data1[(j + 1) % data1.size()] - data1[(j + data1.size() - 1) % data1.size()])>0) {

	  if (cross(data1[(j + data1.size() - 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) >= 0 &&
	  cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) <= 0) {
	  return 0;
	  }

	  }
	  else if (cross(data1[j] - data1[(j + data1.size() - 1) % data1.size()],
	  data1[(j + 1) % data1.size()] - data1[(j + data1.size() - 1) % data1.size()])<0) {

	  if (cross(data1[(j + data1.size() - 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) <= 0 &&
	  cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) >= 0) {
	  printf("(%d %d)\n", cross(data1[(j + data1.size() - 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i])
	  , cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]));

	  return 0;
	  }

	  }
	  }*/
	  /*
	  if (data1[j] == data2[i] &&
	  cross(data1[(j + data1.size() - 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) >= 0 &&
	  cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] -data2[i]) <= 0) {
	  printf("%d %d\n", j, i);
	  return 0;
	  }
	  */
	}


	//data2��i�Ԗڂ̓_��data1�̃|���S�����ɂ��邩�ǂ���
	double x = 0.0;
	int flag = 1;
	for (int j = 0; j < static_cast<int>(data1.size()); ++j) {
	  Vector a = data1[(j + 1) % data1.size()] - data2[i];
	  Vector b = data1[j] - data2[i];

	  if (data1[j] == data2[i]) {
		flag = 0;
		break;
	  }

	  if (dot(a, b) <= 0 && cross(a, b) == 0) {
		flag = 0;
		break;
	  }


	  //�p�x��ϋɓI�ɑ����Ă�����
	  if (cross(a, b) < 0) x += (acos((double)(dot(a, b)) / (a.size()*b.size()))*180.0 / acos(-1.0));
	  if (cross(a, b) > 0) x += -1.0*(acos((double)(dot(a, b)) / (a.size()*b.size()))*180.0 / acos(-1.0));
	}

	//�V��ɂ��Ȃ��A360����Ȃ��Ƃ��͂������ƏI��点��
	//���������덷���l�����銴���ɂ����ق�������
	if (flag && (x >= 360.01 || x <= 359.99)) {
	  return 0;
	}
  }
  return 1;
}

int inEvenOnePolygon(std::vector<Point> &data1, std::vector<Point> &data2) {
  //1�ł������Ă���_������Ȃ�return 1;
  for (int i = 0; i < static_cast<int>(data2.size()); ++i) {
	double x = 0.0;
	int flag = 1;
	for (int j = 0; j < static_cast<int>(data1.size()); ++j) {
	  Vector a = data1[(j + 1) % data1.size()] - data2[i];
	  Vector b = data1[j] - data2[i];

	  //���_��ɂ���ꍇ
	  if (data1[j] == data2[i]) {
		if (cross(data1[j] - data1[(j + data1.size() - 1) % data1.size()],
		  data1[(j + 1) % data1.size()] - data1[(j + data1.size() - 1) % data1.size()]) > 0) {

		  if (cross(data1[(j + data1.size() - 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) < 0 &&
			cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) > 0) {
			//�������_�������Ă���Ȃ�
			return 1;
		  }
		  else {

			//����ȊO�̏ꍇ�ŕ��s�ȃx�N�g��������ꍇ�A���̃x�N�g�����m�̌����������Ȃ�����Ă���
			/*
			if (cross(data1[j] - data1[(j + data1.size() - 1) % data1.size()], data2[(i + 1) % data2.size()] - data2[i]) == 0 &&
			dot(data1[j] - data1[(j + data1.size() - 1) % data1.size()], data2[(i + 1) % data2.size()] - data2[i]) > 0) {
			return 1;
			}*/

			if (cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) == 0 &&
			  dot(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i])  > 0) {
			  return 1;
			}

		  }
		}
		else if (cross(data1[j] - data1[(j + data1.size() - 1) % data1.size()],
		  data1[(j + 1) % data1.size()] - data1[(j + data1.size() - 1) % data1.size()]) < 0) {

		  if (cross(data1[(j + data1.size() - 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) >= 0 &&
			cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) <= 0) {

			//����ȊO�̏ꍇ�ŕ��s�ȃx�N�g��������ꍇ�A���̃x�N�g�����m�̌����������Ȃ�����Ă���
			/*
			if (cross(data1[j] - data1[(j + data1.size() - 1) % data1.size()], data2[(i + 1) % data2.size()] - data2[i]) == 0 &&
			dot(data1[j] - data1[(j + data1.size() - 1) % data1.size()], data2[(i + 1) % data2.size()] - data2[i]) > 0) {
			return 1;
			}*/

			if (cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) == 0 &&
			  dot(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i])  > 0) {
			  return 1;
			}

		  }
		  else {
			//�������_�������Ă���Ȃ�
			return 1;
		  }
		}
		flag = 0;
		break;
	  }
	  else if (dot(a, b) <= 0 && cross(a, b) == 0) {//������ɂ���ꍇ
		if (data2[i] != data1[(j + 1) % data1.size()]) {
		  if (cross(b, data2[(i + data2.size() - 1) % data2.size()] - data2[i]) < 0 ||
			cross(a, data2[(i + 1) % data2.size()] - data2[i]) > 0) {
			return 1;
		  }
		  else {
			if (cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) == 0 &&
			  dot(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) > 0) {
			  return 1;
			}
		  }
		}

		flag = 0;
		break;
	  }

	  //�p�x��ϋɓI�ɑ����Ă�����
	  if (cross(a, b) < 0) x += (acos((double)(dot(a, b)) / (a.size()*b.size()))*180.0 / acos(-1.0));
	  if (cross(a, b) > 0) x += -1.0*(acos((double)(dot(a, b)) / (a.size()*b.size()))*180.0 / acos(-1.0));
	}

	//���_��ɂ��Ȃ��Ē�����ɂ��Ȃ��Ȃ�360�̂Ƃ��͓����Ă��邩��I���
	//���������덷���l�����銴���ɂ����ق�������
	if (flag && (359.99 <= x && x <= 360.01)) {
	  return 1;
	}
  }
  return 0;
}

int collisionPiece(std::vector<Point> &data1, std::vector<Point> &data2) {
  //������ł�������Ă����瓖�����Ă���i����͂����j
  if (crossLine(data1, data2)) {
	//printf("cl");
	return 1;
  }

  if (inEvenOnePolygon(data1, data2) || inEvenOnePolygon(data2, data1)) {
	return 1;
  }

  return 0;
}

//data1 == frame
int collisionFrame(std::vector<Point> &data1, std::vector<Point> &data2) {

  if (crossLine(data1, data2)) {
	//printf("cl");
	return 1;
  }

  if (!inPolygon(data1, data2)) {
	//printf("in");
	return 1;
  }

  /*
  //1�ł������Ă��Ȃ��_������Ȃ�return 1;
  for (int i = 0; i < static_cast<int>(data2.size()); ++i) {
  double x = 0.0;
  int flag = 1;
  for (int j = 0; j < static_cast<int>(data1.size()); ++j) {
  Vector a = data1[(j + 1) % data1.size()] - data2[i];
  Vector b = data1[j] - data2[i];

  //���_��ɂ���ꍇ
  if (data1[j] == data2[i]) {
  if (cross(data1[j] - data1[(j + data1.size() - 1) % data1.size()],
  data1[(j + 1) % data1.size()] - data1[(j + data1.size() - 1) % data1.size()]) > 0) {

  if (cross(data1[(j + data1.size() - 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) <= 0 &&
  cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) >= 0) {

  if (cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) == 0 &&
  (data2[(i + 1) % data2.size()] - data2[i]).size() > (data1[(j + 1) % data1.size()] - data1[j]).size()) {
  //printf("long");
  //return 1;
  }

  }
  else {
  //�������_�������Ă��Ȃ��Ȃ�
  return 1;
  }
  }
  else if (cross(data1[j] - data1[(j + data1.size() - 1) % data1.size()],
  data1[(j + 1) % data1.size()] - data1[(j + data1.size() - 1) % data1.size()]) < 0) {

  if (cross(data1[(j + data1.size() - 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) > 0 &&
  cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) < 0) {
  //�������_�������Ă��Ȃ��Ȃ�
  return 1;
  }
  else {
  if (cross(data1[(j + 1) % data1.size()] - data1[j], data2[(i + 1) % data2.size()] - data2[i]) == 0 &&
  (data2[(i + 1) % data2.size()] - data2[i]).size() > (data1[(j + 1) % data1.size()] - data1[j]).size()) {
  //printf("long");
  //return 1;
  }
  }
  }
  flag = 0;
  break;
  }
  else if (dot(a, b) <= 0 && cross(a, b) == 0) {//������ɂ���ꍇ
  if (data2[i] != data1[(j + 1) % data1.size()]) {
  if (cross(b, data2[(i + data2.size() - 1) % data2.size()] - data2[i]) <= 0 &&
  cross(a, data2[(i + 1) % data2.size()] - data2[i]) >= 0) {

  if (cross(a, data2[(i + 1) % data2.size()] - data2[i]) == 0 &&
  (data2[(i + 1) % data2.size()] - data2[i]).size() > a.size()) {
  //printf("long");
  //return 1;
  }

  }
  else {
  return 1;
  }
  }

  flag = 0;
  break;
  }

  //�p�x��ϋɓI�ɑ����Ă�����
  if (cross(a, b) < 0) x += (acos((double)(dot(a, b)) / (a.size()*b.size()))*180.0 / acos(-1.0));
  if (cross(a, b) > 0) x += -1.0*(acos((double)(dot(a, b)) / (a.size()*b.size()))*180.0 / acos(-1.0));
  }

  //���_��ɂ��Ȃ��Ē�����ɂ��Ȃ��Ȃ�360�̂Ƃ��͓����Ă��邩��I���
  //���������덷���l�����銴���ɂ����ق�������
  if (flag && (x < 359.99 || 360.01 < x)) {
  return 1;
  }
  }
  */

  return 0;
}


int collisionNotPutArea(std::vector<std::vector<Point>>& notPut, std::vector<Point>& piece){
  //����������Ă���Ȃ炱���ł͂���
  for (int i = 0; i < static_cast<int>(notPut.size()); ++i) {
	if (crossLine(notPut[i], piece)) {
	  return 1;
	}
  }
  
  //���ݒu�̈�̐������J��Ԃ�
  for (int i = 0; i < static_cast<int>(notPut.size()); ++i) {
	//�s�[�X�̒��_�����ԂɌ��Ă���
	for (int j = 0; j < static_cast<int>(piece.size()); ++j) {
	  double x = 0.0;
	  int flag = 1;

	  //���ݒu�̈�̕ӂ̐������J��Ԃ�
	  for (int k = 0; k < static_cast<int>(notPut[i].size()); ++k) {
		Vector npn = notPut[i][k]                                             - piece[j];
		Vector npf = notPut[i][(k+1)% notPut[i].size()]                       - piece[j];

		Vector pf = piece[(j + 1) % piece.size()] - piece[j];

		if (notPut[i][k] == piece[j]) {//���ݒu�̈�̒��_��ɂ���ꍇ
		  Vector c1 = notPut[i][k]                          - notPut[i][(k + notPut[i].size() - 1) % notPut[i].size()];
		  Vector c2 = notPut[i][(k + 1) % notPut[i].size()] - notPut[i][(k + notPut[i].size() - 1) % notPut[i].size()];

		  Vector nb = notPut[i][(k + notPut[i].size() - 1) % notPut[i].size()] - notPut[i][k];
		  Vector nf = notPut[i][(k + 1) % notPut[i].size()] - notPut[i][k];
		  Vector nbr = notPut[i][k] - notPut[i][(k + notPut[i].size() - 1) % notPut[i].size()];


		  if (cross(c1,c2) > 0) {//�s�p�̏ꍇ
			if (cross(nb, pf) <= 0 && cross(nf, pf) >= 0) {//�����Ă���܂��͕��s

			  //�������s�̂Ƃ��A�x�N�g���̌������t�Ȃ�O��
			 // if (cross(nbr, pf) == 0 && dot(nbr, pf) < 0) { return 1; }
			  if (cross(nf, pf) == 0 && dot(nf, pf) < 0) { return 1; }

			  // �������s�̂Ƃ��A�s�[�X�̃x�N�g�������ݒu��蒷���Ȃ�O��
			  if (cross(nf, pf) == 0 && nf.size() < pf.size()) {return 1;}
			}else {//�O��
			  return 1;
			}
		  }else if(cross(c1,c2) < 0){
			//�݊p�̏ꍇ

			if (cross(nb, pf) > 0 && cross(nf, pf) < 0) {//�O��
			  return 1;
			}else {//�����Ă���܂��͕��s

			  //�������s�̂Ƃ��A�x�N�g���̌������t�Ȃ�O��
			 // if (cross(nbr, pf) == 0 && dot(nbr, pf) < 0) { return 1; }
			  if (cross(nf, pf) == 0 && dot(nf, pf) < 0) { return 1; }

			  //�������s�̂Ƃ��A�s�[�X�̃x�N�g�������ݒu��蒷���Ȃ�O��
			  if (cross(nf, pf) == 0 && nf.size() < pf.size()) {return 1; }
			}
		  }

		  flag = 0;
		  break;
		}else if (dot(npf,npn)<=0 && cross(npf,npn)==0) {//������ɂ���ꍇ
		  //���ݒu�̈�̎��̒��_��ɂ���Ȃ玟�ɔ���������z��
		  if (notPut[i][(k + 1) % notPut[i].size()] != piece[j]) {
			if (cross(npn, pf) > 0 && cross(npf, pf) < 0) {//�O��
			  return 1;
			}else {//���s�ňႤ�����Ȃ�O��
			  Vector nf = notPut[i][(k + 1) % notPut[i].size()] - notPut[i][k];
			  if (cross(nf, pf) == 0 && dot(nf,pf)<0) {return 1;}

			  //�������s�̂Ƃ��A�s�[�X�̃x�N�g�������ݒu��蒷���Ȃ�O��
			  if (cross(npf, pf) == 0 && npf.size() < pf.size()) { return 1; }
			}

			flag = 0;
			break;
		  }

		  
		}

		//�p�x��ϋɓI�ɑ����Ă�����
		if (cross(npf, npn) < 0) x += (acos((double)(dot(npf, npn)) / (npf.size()*npn.size()))*180.0 / acos(-1.0));
		if (cross(npf, npn) > 0) x += -1.0*(acos((double)(dot(npf, npn)) / (npf.size()*npn.size()))*180.0 / acos(-1.0));
	  }

	  //���_��ɂ��Ȃ��Ē�����ɂ��Ȃ��Ȃ�360����Ȃ��Ƃ��͊O������Ă��邩��I���
	  if (flag && (x <= 359.99 ||360.01 <= x)) {
		return 1;
	  }
	}
  }

  return 0;
}
