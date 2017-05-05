#ifndef _PIECE_HPP_
#define _PIECE_HPP_

#include<vector>
#include"utility.hpp"

class Piece{
  private:
    std::vector<Point> point; //���_���i�[����Point�^���I�z��
  public:
    Piece(int pointNum,std::vector<Point> &data);  //�����F��̃s�[�X�̒��_���ƍ\���̔z��
    Point getPoint(int n);    //�����F�擾����s�[�X�̒��_��
};


#endif
