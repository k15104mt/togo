#ifndef _GEOMETRY_HPP_
#define _GEOMETRY_HPP_
#define MAX 256	//NOT�����Ƃ��Ŏg���Œ蒷�z��̗v�f��(�����x�N�g���Ⓒ�_��)


#include"utility.hpp"
#include"piece.hpp"
#include<vector>



class Geometry {
public:
	Point getPutPoint(std::vector<Piece> &data, std::vector<putData> &already_put,int putMode);	//�ݒu��������W�擾,UP,RIGHT,DOWN,RIGHT,UP_LEFT
	void cancelPut();																//�ݒu������O��
	std::vector<std::vector<Point>> areaPoint;										//���ݒu���G���A�̏��
	bool canPut(std::vector<Piece> &data, std::array<int, 100> &isPut);	//�G���A�ʐ�<���ݒu�s�[�X�ʐς̏ꍇ0���C�t�Ȃ�1��Ԃ�
	Geometry(std::vector<std::vector<Point>> &framePoint);							//�R���X�g���N�^
private:
	std::vector<std::vector<std::vector<Point>>> tmpAreaPoint;		//cancel�p�̐ݒu�O�G���A�ێ�
	double minSurface;		//���������G���A�̍ŏ��ʐ�
	double minAngle;		//���������G���A�̍ŏ��p�x
	//int putNum;
};

#endif
