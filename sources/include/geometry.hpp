#ifndef _GEOMETRY_HPP_
#define _GEOMETRY_HPP_

#include"utility.hpp"
#include"piece.hpp"
#include<vector>

//����(�s�[�X���,�ݒu���,�t���[�����)�ō��㒸�_���W��Ԃ�
Point getPutPoint(std::vector<Piece>&, std::vector<putData>&,std::vector<std::vector<Point>>);

//����(�}�`��񑦂�Point��vector)�ŕԂ�l�͎��v���Ȃ�1���C�����v���Ȃ�-1���C�˂���Ă���Ȃ�0
int CheckAngle(std::vector<Point> point);

#endif
