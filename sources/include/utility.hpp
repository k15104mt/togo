#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

struct Point{
  int x;
  int y;
};

//��̐����̎n�_�A�I�_����A�������m���������Ă��邩��Ԃ�
//���������s�ȏꍇ�͌������Ă��Ȃ����̂ƂȂ�
int crossLine(Point Line1Start,Point Line1End,Point Line2Start,Point Line2End);

#endif
