#include"piece.hpp"

using namespace std;

//Piece�R���X�g���N�^
Piece::Piece(int pointNum,vector<Point> &data){
  cout<<"�R���X�g���N�^"<<endl;
  point.resize(pointNum); //point�̃��T�C�Y
  point = data;           //���_���W�i�[
  
}

//�s�[�X���W�̃Q�b�^�[
Point Piece::getPoint(int n){
  return point[n];
}