#include<cstdio>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<array>
#include<thread>
#include<chrono>


#include"piece.hpp"
#include"utility.hpp"
#include"color.hpp"
#include"geometry.hpp"

std::vector<std::vector<Point>> framePoint;

//�����蔻��
int checkHit(const std::vector<Piece> &,const std::vector<putData> &,const putData &, Geometry &);

//�ċA
int solve(int, std::vector<Piece> &, std::vector<putData> &, std::array<int, 100> &, Geometry &);


class thread {
public:
  thread(int, std::vector<Piece> &);

  std::thread t;
  std::vector<putData> already_put;
private:
  std::array<int, 100> isPut;
  Geometry geometry;

};

thread::thread(int start,std::vector<Piece>& data):geometry(framePoint){

  for (int i = 0; i < 100; ++i) {
	isPut[i] = 0;
  }

  t = std::thread(solve, start, std::ref(data), std::ref(already_put), std::ref(isPut), std::ref(geometry));
}

int count=0;

int main() {

 //QR�R�[�h�̐�
  int qrNum;
  std::cin >> qrNum;
  std::cin.ignore();

  //QR�R�[�h�̐��������͂��J��Ԃ�
  std::vector<std::string> input;
  for (int i = 0; i < qrNum; ++i) {
	std::string temp;
	std::getline(std::cin, temp);
	input.push_back(temp);
  }


  std::vector<std::vector<Point>> piecePoint;
  framePoint.resize(1);

  for (int i = 0; i < static_cast<int>(input.size()); ++i) {
	//QR�R�[�hi�Ԗڂ̕�����

	//:�Ńs�[�X���Ƃɋ�؂�
	auto pieceStr = split(input[i], ':');
	for (int j = 1; j < static_cast<int>(pieceStr.size()); ++j) {
	  // �Œ��_���Ƃɋ�؂�
	  auto numStr = split(pieceStr[j], ' ');

	  if (i == input.size() - 1 && j == pieceStr.size() - 1) {
		//�Ō��QR�̍Ō�̃f�[�^�̏ꍇ��framePoint�Ɋi�[����
		for (int k = 1; k < static_cast<int>(numStr.size()); k += 2) {
		  Point pointTemp(stoi(numStr[k]), stoi(numStr[k + 1]));
		  framePoint[0].push_back(pointTemp);
		}
	  }
	  else {
		//�p���_�̍��W��pieceTemo�ɐ����ɕϊ����Ċi�[���āApiecePoint�ɒǉ�����
		std::vector<Point> pieceTemp;
		for (int k = 1; k < static_cast<int>(numStr.size()); k += 2) {
		  Point pointTemp(stoi(numStr[k]), stoi(numStr[k + 1]));
		  pieceTemp.push_back(pointTemp);
		}
		piecePoint.push_back(pieceTemp);
	  }

	}
  }

  std::vector<Piece> data;

  for (int i = 0; i < static_cast<int>(piecePoint.size()); i++) {
	data.push_back(piecePoint[i]); 
  }

  //------------------------------------------------------
  setColor(F_BLACK, B_WHITE|B_INTENSITY);

  for (int i = 0; i < static_cast<int>(piecePoint.size()); ++i) {
	std::cout << "piece[" << i << "]" << "(���_��:" << piecePoint[i].size() << "):";
	for (auto j : piecePoint[i]) {
	  j.print();
	}
	std::cout << std::endl;
  }


  std::cout << "frame�i���_��:" << framePoint[0].size() << "):";
  for (auto i : framePoint[0]) {
	i.print();
  }
  std::cout << std::endl;

  setColor();
//------------------------------------------------------
  int p = 0;
  for (auto i : data) {
	printf("%d�s�[�X\n",p);
	int n = 0;
	for (auto j : i.getPoint()) {
	  printf("	%d��]\n	  ", n);
	  for (auto k : j) {
		printf("(%d,%d) ", k.x, k.y);
	  }
	  printf("\n");
	  n++;
	}
	p++;
  }


  std::vector<putData> already_put;
  std::array<int, 100> isPut = {0};
  Geometry geometry(framePoint);

  //�v���J�n
  auto start = std::chrono::system_clock::now();

  solve(0, data, already_put, isPut, geometry);
  

  printf("%d\n", count);
  //�v���I��
  auto end = std::chrono::system_clock::now();

  auto dur = end - start;
  auto hour = std::chrono::duration_cast<std::chrono::hours>(dur).count();
  auto min = std::chrono::duration_cast<std::chrono::minutes>(dur).count() % 60;
  auto sec = std::chrono::duration_cast<std::chrono::seconds>(dur).count() % 60;

  printf("���s���� %02d:%02d:%02lld\n", hour, min, sec);

  //�񓚕\��
  setColor(F_GREEN | F_INTENSITY);
  for (auto i : already_put) {
	printf("%d %d (%d,%d)\n", i.piece_num, i.point_num,i.base_point.x,i.base_point.y);
  }
  setColor();

  /*�t�@�C���o��
  FILE *fp;
  fopen_s(&fp,"out.txt","w");
  if (fp != NULL) {
	for (auto i : already_put) {
	  fprintf_s(fp, "%d %d (%d,%d)\n", i.piece_num, i.point_num, i.base_point.x, i.base_point.y);
	}
  }
  */

  getchar();
  getchar();

  return 0;
}


int checkHit(const std::vector<Piece> &data,const std::vector<putData> &already_put,const putData &put,Geometry &geometry) {
  count++;

  std::vector<Point> cp1(data[put.piece_num].getPoint()[put.point_num]);
  //�ړ�
  move(cp1, put.base_point);
  
  /*
  for (int i = 0; i < static_cast<int>(already_put.size()); ++i) {
	std::vector<Point> cp2(data[already_put[i].piece_num].getPoint()[already_put[i].point_num]);
	//�ړ�
	move(cp2, already_put[i].base_point);

	if (collisionPiece(cp1, cp2)) {
	  return 1;
	}
  }
  
  int flag = 0;
  for (int i = 0; i < static_cast<int>(framePoint.size()); i++) {
	if (!collisionFrame(framePoint[i], cp1)) {
	  flag = 1;
	}
  }
  
  if (!flag) {
	//printf("frame");
	return 1;
  }*/

  
  if (collisionNotPutArea(geometry.areaPoint, cp1)) {
	return 1;
  }
  

  return 0;
}

int solve(int start,std::vector<Piece> &data, std::vector<putData> &already_put,std::array<int,100> &isPut, Geometry &geometry) {
  if (data.size() == already_put.size()) {
	//�S���u�������Ă���
	return 1;
  }

  //�S�s�[�X���Ă�������
  Point tmp = geometry.getPutPoint(data, already_put);
  for (int i = 0; i < static_cast<int>(data.size()); ++i) {//�s�[�X�̐�
	int ii;
	ii = (i + start) % data.size();

	/*
	if (already_put.size() == 0) {

	  ii = (i + start) % data.size();

	}else {

	  ii = i;

	}*/

	//���̃s�[�X�����łɒu����Ă��邩�ǂ���
	if(isPut[ii]==0){
	  for (int j = 0; j < static_cast<int>(data[ii].getPoint().size()); ++j) {//��]�̑g�ݍ��킹�̐�

		 // printf("(%2d,%2d,%2d) --> (%3d,%3d) result -->", ii, j, k,tmp.x,tmp.y);
		  putData put(ii, j, 0, Point(tmp.x-data[ii].getUpperLeft(j).x,tmp.y-data[ii].getUpperLeft(j).y));
		  if (!checkHit(data, already_put, put,geometry)) {
			//���������蔻�肪ok�Ȃ�
			//setColor(F_CYAN | F_INTENSITY);
			//printf("       put\n");
			//setColor();
			already_put.push_back(put);
			isPut[ii]=1;
			
			if (solve(start,data, already_put,isPut,geometry)) {
			  //����return 1�Ȃ�����I��������Ă���
			  return 1;
			}
		  }else{
			//setColor(F_RED | F_INTENSITY);
			//printf_s("Hit!!!!\n");
			//setColor();
		  }
	  }
	}
  }

  //�����܂ŗ������Ă��Ƃ̓_�����������Ă��Ƃ�����pop���ăo�b�N
  if (already_put.size()) {
	//setColor(F_ORANGE | F_INTENSITY);
	//printf("back  depth = %10d\n", already_put.size());
	//setColor();

	isPut[already_put[already_put.size()-1].piece_num] = 0;
	geometry.cancelPut();
	already_put.pop_back();
  }
  else {
	//setColor(F_ORANGE | F_INTENSITY);
	//printf("back  depth = %10d\n",0);
	//setColor();
  }

  return 0;
}
