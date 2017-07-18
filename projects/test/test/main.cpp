#include"piece.hpp"
#include"utility.hpp"

#include<cstdio>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<stack>
#include<array>


std::vector<Point> framePoint;

//�����蔻��
int checkHit(std::vector<Piece> &data, std::vector<putData> &already_put, putData &put) {
  std::vector<Point> cp1(data[put.piece_num].getPoint()[put.point_num]);
  //�ړ�
  for (auto i : cp1) {
	i.x += put.base_point.x;
	i.y += put.base_point.y;
  }

  for (int i = 0; i < already_put.size();++i) {
	std::vector<Point> cp2(data[already_put[i].piece_num].getPoint()[already_put[i].point_num]);
	for (auto j : cp2) {
	  j.x += already_put[i].base_point.x;
	  j.y += already_put[i].base_point.y;
	}
	if (collisionPiece(cp1, cp2)) {
	  return 1;
	}
  }

  if (collisionFrame(framePoint, cp1)){
	return 1;
  }
  

  return 0;
}

Point getPutPoint(std::vector<Piece> &data, std::vector<putData> &already_put) {

}

//�ċA
int solve(std::vector<Piece> &data, std::vector<putData> &already_put) {
  //�S�s�[�X���Ă�������
  for (int i = 0; i < static_cast<int>(data.size()); ++i) {//�s�[�X�̐�
	//���̃s�[�X�����łɒu����Ă��邩�ǂ���
	for (int j = 0; j < already_put.size(); ++j) {
	  if (already_put[j].piece_num == i) {
		break;
	  }
	}

	for (int j = 0; j < data[i].getPoint().size(); ++j) {//��]�̑g�ݍ��킹�̐�
	  for (int k = 0; k < data[i].getPoint()[j].size(); ++k) {//�ݒu���_
		/*


		�����ɐݒu�v���O����


		*/


		 Point tmp;
		 putData put(i, j, k, tmp);
		if (!checkHit(data,already_put,put)) {
		  //���������蔻�肪ok�Ȃ�
		  already_put.push_back(put);
		  if (solve(data, already_put)) {
			//����return 1�Ȃ�����I��������Ă���
			return 1;
		  }
		}
	  }
	}
  }

  if (data.size() == already_put.size()) {
	//�S���u�������Ă���
	return 1;
  }
  already_put.pop_back();
  return 0;
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
