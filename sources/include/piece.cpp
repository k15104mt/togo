#include"piece.hpp"

using namespace std;

Piece::Piece(int pointNum,vector<Point> &data){
  cout<<"�R���X�g���N�^"<<endl;
  point.resize(pointNum);
  point.pushback(data);
  
}

int Piece::checkHit(Data &obj){  
  return 0;
}
