#include<iostream>
#include<array>
#include<vector>
#include<cstdio>
#include<string>
#include<sstream>
#include"utility.hpp"

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

std::vector<std::string> spilit(std::string input,char spilit_character) {
	std::stringstream stream(input);
	
	std::vector<std::string> result;
	std::string temp;
	while(std::getline(stream, temp, spilit_character)){
		result.push_back(temp);
	}
	
	return result;
}

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
		auto pieceStr = spilit(input[i], ':');
		for (int j = 1; j < pieceStr.size(); ++j) {
			// �Œ��_���Ƃɋ�؂�
			auto numStr = spilit(pieceStr[j], ' ');

			if (i == input.size() - 1 && j == pieceStr.size()-1) {
				//�Ō��QR�̍Ō�̃f�[�^�̏ꍇ��framePoint�Ɋi�[����
				for (int k = 1; k < numStr.size(); k += 2) {
					Point pointTemp;
					pointTemp.x = stoi(numStr[k]);
					pointTemp.y = stoi(numStr[k + 1]);
					framePoint.push_back(pointTemp);
				}
			}
			else {
				//�p���_�̍��W��pieceTemo�ɐ����ɕϊ����Ċi�[���āApiecePoint�ɒǉ�����
				std::vector<Point> pieceTemp;
				for (int k = 1; k < numStr.size(); k += 2) {
					Point pointTemp;
					pointTemp.x = stoi(numStr[k]);
					pointTemp.y = stoi(numStr[k + 1]);
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

	
	//std::array<int, NUM> array = { 0,1,2,3 };
	//std::vector<int> vector;

	//func(array, vector);

	return 0;
}