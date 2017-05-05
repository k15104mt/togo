#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

//���_���W������Point�^�\����
typedef struct{
  int x;
  int y;
}Point;

class Piece{
  private:
    vector<Point> point; //���_���i�[����Point�^���I�z��
  public:
    Piece(int pointNum,vector<Point> &data);  //�����F��̃s�[�X�̒��_���ƍ\���̔z��
    Point getPoint(int n);    //�����F�擾����s�[�X�̒��_��
};

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

int main() {
  vector<Point> data(5);
  
  //���f�[�^
  for(int i=0;i<5;i++){
    data[i].x=rand() %6+1;
    data[i].y=rand() %6+1;
  }

  Piece pieceObj(5,data);
  cout<<"Piece�I�u�W�F�N�g�쐬"<<endl;
  
  for(int i=0;i<5;i++){
    printf("�s�[�X[%d]:(%d,%d)\n",i,pieceObj.getPoint(i).x,pieceObj.getPoint(i).y);
  }
  return 0;
}
