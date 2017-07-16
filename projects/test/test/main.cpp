#include"piece.hpp"
#include"utility.hpp"

#include<cstdio>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<stack>
#include<array>

#define NUM 4

int roop = 0;

void func(std::array<int, NUM> &array, std::vector<int> &vector) {
  //��ŌĂяo���ꂽ�Ƃ��ɑI������Ă��鐔���͑I�����Ȃ��悤����i�v���P�j
  for (int i = 0; i<static_cast<int>(array.size()); i++) {
	if (([&]() {int n = 1; for (auto j : vector) { if (i == j) { n = 0; } }return n; }())) {
	  vector.push_back(i);
	  func(array, vector);
	}
  }
  if (array.size() == vector.size()) {
	printf("%8d:", roop);
	for (auto i : vector) {
	  std::cout << array[i] << " ";
	}
	std::cout << std::endl;

	roop++;
  }
  vector.pop_back();
}

class put_data {
public:
  put_data(int,int,Point&);

  int piece_num;
  int point_num;
  Point base_point;

};

put_data::put_data(int piece_num, int point_num, Point &base_point) {
  this->piece_num = piece_num;
  this->point_num = point_num;
  this->base_point = base_point;
}


//�ċA
int solve(std::vector<Piece> &data,std::stack<int> &not_put){
  //�u���ꂸ�ɔ�΂��ꂽ�s�[�X�����邩
  if (!not_put.empty()) {
	std::stack<int> tmp;
	//��΂��ꂽ�s�[�X��u��
	for (int i = 0; i < static_cast<int>(not_put.size()); ++i) {
	  

	}
  }

  //�S�v�f���Ă�������
  for (int i = 0; i < static_cast<int>(data.size()); ++i) {


  }

}

//�����񕪊��̊֐�
std::vector<std::string> split(std::string, char);

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
  std::vector<Point> framePoint;

  for (int i = 0; i < input.size(); ++i) {
	//QR�R�[�hi�Ԗڂ̕�����

	//:�Ńs�[�X���Ƃɋ�؂�
	auto pieceStr = split(input[i], ':');
	for (int j = 1; j < pieceStr.size(); ++j) {
	  // �Œ��_���Ƃɋ�؂�
	  auto numStr = split(pieceStr[j], ' ');

	  if (i == input.size() - 1 && j == pieceStr.size() - 1) {
		//�Ō��QR�̍Ō�̃f�[�^�̏ꍇ��framePoint�Ɋi�[����
		for (int k = 1; k < numStr.size(); k += 2) {
		  Point pointTemp(stoi(numStr[k]), stoi(numStr[k + 1]));
		  framePoint.push_back(pointTemp);
		}
	  }
	  else {
		//�p���_�̍��W��pieceTemo�ɐ����ɕϊ����Ċi�[���āApiecePoint�ɒǉ�����
		std::vector<Point> pieceTemp;
		for (int k = 1; k < numStr.size(); k += 2) {
		  Point pointTemp(stoi(numStr[k]), stoi(numStr[k + 1]));
		  pieceTemp.push_back(pointTemp);
		}
		piecePoint.push_back(pieceTemp);
	  }

	}
  }



  /*�m�F�p
  for (int i = 0; i < piecePoint.size(); ++i) {
  std::cout << "piece[" << i << "]" << "(���_��:" << piecePoint[i].size() << "):";
  for (auto j : piecePoint[i]) {
  std::cout << "(" << j.x << "," << j.y << ") ";
  }
  std::cout << std::endl;
  }


  std::cout << "frame�i���_��:" << framePoint.size() << "):";
  for (auto i : framePoint) {
  std::cout << "(" << i.x << "," << i.y << ") ";
  }
  std::cout << std::endl;
  */


  //�ċA�e�X�g�pa
  //std::array<int, NUM> array = { 0,1,2,3 };
  //std::vector<int> vector
  //func(array, vector);

  return 0;
}


std::vector<std::string> split(std::string input, char spilit_character) {
  std::stringstream stream(input);

  std::vector<std::string> result;
  std::string temp;
  while (std::getline(stream, temp, spilit_character)) {
	result.push_back(temp);
  }

  return result;
}