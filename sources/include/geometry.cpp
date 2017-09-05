#include"geometry.hpp"
#include<cstdlib>
#include<math.h>
#define PI 3.1415926535

int	ap = 0, ax[256], ay[256], bp = 0, bx[256], by[256];	// ���͐}�`�̋L���p	ap,bp:���_��
int	rc = 0, rp[256], rx[256][256], ry[256][256];		// ���Z��}�`�̋L���p
int	vn = 0, vx1[256], vy1[256], vx2[256], vy2[256];	// �x�N�g���̋L���p
int	tcnt = 0, tp, tx[256], ty[256], used[256];		// �ꎞ�L���p

void OnNot();
void OnMerge();
void OnClean();
double CheckAngle(int n, int *x, int *y);
void Reverse(int n, int *x, int *y);



//�Ƃ肠�������_����ԍ���̕����ɐݒu����Ƃ���
Point getPutPoint(std::vector<Piece> &data, std::vector<putData> &already_put, std::vector<std::vector<Point>> areaPoint) {
	if (already_put.size() == 0) {
		return areaPoint[0][0];
	}
	int b;			//���������� y=-x+b ��b
	Point point;	//�Ԃ�l
	printf("debug>alreadysize:%d\ndebug>areasize:%d\n\n", already_put.size(),areaPoint.size());

	////�s�[�X�Ɛݒu�����C���ݒu���̐}�`���_�����߂�

	for (int i = 0; i < already_put.size(); i++) {	//�ݒu�s�[�X��
		printf("debug>�ݒu�s�[�X[%d]\n",i);
		for (int k = 0; k < areaPoint.size(); k++) {	//�����G���A��
			printf("debug>�m�F�����G���A[%d]\n", k);
			printf("\n--NOT����[%d]--\n", i);	//debug
			//std::vector<std::vector<Point>> putPiece;	//�t���[����NOT��������s�[�X���	//�Ȃɂ���

			bp = areaPoint[k].size() + 1;										//NOT���͐}�`���_��(�t���[��)
			ap = data[already_put[i].piece_num].getPoint()[0].size() + 1;	//NOT���͐}�`���_��(�s�[�X)
			printf("bp:%d,ap:%d\n", bp, ap);		//debug

			for (int j = 0; j < bp - 1; j++) {	//NOT�����Ŏg���ϐ��i�[
				bx[j] = areaPoint[k][j].x;	//���v�C���i�t���[�����̈�����g���ĂȂ��j
				by[j] = areaPoint[k][j].y;
				printf("b[%d](%d,%d)\n", j, bx[j], by[j]);	//debug
			}
			bx[bp - 1] = bx[0];
			by[bp - 1] = by[0];
			puts("--");

			for (int j = 0; j < ap - 1; j++) {	//NoT�����Ŏg���ϐ��i�[
				ax[j] = data[already_put[i].piece_num].getPoint()[already_put[i].point_num][j].x + already_put[i].base_point.x;	//���������ǐݒu�s�[�X�擾���Ă�
				ay[j] = data[already_put[i].piece_num].getPoint()[already_put[i].point_num][j].y + already_put[i].base_point.y;
				printf("a[%d](%d,%d)\n", j, ax[j], ay[j]);	//debug
			}
			ax[ap - 1] = ax[0];	//���
			ay[ap - 1] = ay[0];	//���

			OnNot();	//not�������s��
						/*
						////debug
						printf("debug>rc:%d\n", rc);
						for (int i = 0; i < rc; ++i) {
						printf("--i:%d--\n", i);
						for (int j = 0; j < rp[i]; ++j) {
						printf("(%d,%d)\n", rx[i][j], ry[i][j]);
						}
						}*/

			areaPoint.erase(areaPoint.begin()+k);	//��U���Ă�G���A�폜���팸����
			////NOT�ŏo�����ݒu�s�[�X���ƃt���[������������
			//���ݒu�G���A�̍X�V
			for (int i = 0; i < rc; i++) {
				std::vector<Point> Tmp;
				for (int j = 0; j < rp[i]; j++) {
					Point tmp;
					tmp.x = rx[i][j]; tmp.y = ry[i][j];
					Tmp.push_back(tmp);
				}
				areaPoint.insert(areaPoint.begin()+k,Tmp);
			}
			//printf("rc=%d\n", rc);

			for (int i = 0; i < rc; i++) {
				printf("area[%d]=", i);
				for (int j = 0; j < rp[i]; j++) {
					printf("{%d,%d},", rx[i][j], ry[i][j]);
				}
				printf("\n");
			}
			

			for (int i = 0; i < areaPoint.size(); i++) {
				printf("area[%d]:",i);
				for (int j = 0; j < areaPoint[i].size(); j++) {
					printf("{%d,%d},",areaPoint[i][j].x, areaPoint[i][j].y);

					if (i == j&&i == 0) {	//�b��̍���
						b = areaPoint[i][j].x + areaPoint[i][j].y;
						point.x = areaPoint[i][j].x; point.y=areaPoint[i][j].y;
					}
					else if (b>areaPoint[i][j].x + areaPoint[i][j].y) {	//�ŏ�
						b = areaPoint[i][j].x + areaPoint[i][j].y;
						point.x = areaPoint[i][j].x; point.y = areaPoint[i][j].y;
					}
					else if (b== areaPoint[i][j].x + areaPoint[i][j].y &&point.x>areaPoint[i][j].x) {	//b�̒l�������Ȃ��x������������D��
						b = areaPoint[i][j].x + areaPoint[i][j].y;
						point.x = areaPoint[i][j].x; point.y = areaPoint[i][j].y;
					}

				}
				printf("\n");
			}


			/*	�����Ή��̂��߃S�~�Ɖ�����
			//�o�������ݒu�����_�̂����C�ł�����̍��W���擾����
			for (int i = 0; i < rc;i++) {
				for (int j = 0; j < rp[i]; j++) {
					if (k == j &&  k == 0) {	//�b���b�ŏ��l
						b = rx[i][j] + ry[i][j];
						point.x = rx[i][j]; point.y = ry[i][j];
					}

					else if (b > rx[i][j] + ry[i][j]) {	//�ŏ�
						b = rx[i][j] + ry[i][j];
						point.x = rx[i][j]; point.y = ry[i][j];
					}

					else if (b == rx[i][j] + ry[i][j] && point.x > rx[i][j]) {	//b�̒l�������Ȃ��x������������D��
						b = rx[i][j] + ry[i][j];
						point.x = rx[i][j]; point.y = ry[i][j];
					}
				}
			}*/

			printf("debug>����(%d,%d),b:%d\n", point.x, point.y,b);
			//�����܂ł����ƍX�V
		}
		printf("\n--------------\n\n");
	}



	

	return point;
}



// ptr: �폜�ʒu  last: �z�񖖔��ʒu�i�Ō�̗v�f�̎��j
void erase(int *ptr, int *last) {
	while (++ptr < last)
		*(ptr - 1) = *ptr;       //  �v�f���ЂƂO�ɂ��炷
}
// ���_�̋Ȃ���p�x�̍��v�����߂�
double CheckAngle(int n, int *x, int *y) {
	int	i;
	double	a1, a2, ang, total;

	total = 0;
	x[n] = x[1];
	y[n] = y[1];
	for (i = 1; i < n; ++i)
	{
		a1 = atan2(y[i] - y[i - 1], x[i] - x[i - 1]);
		a2 = atan2(y[i + 1] - y[i], x[i + 1] - x[i]);
		ang = a2 - a1;
		while (ang > PI) ang -= (2 * PI);
		while (ang < -PI) ang += (2 * PI);
		total += ang;
	}
	return total;
}

// ���_�̕��я��𔽓]����
void Reverse(int n, int *x, int *y) {
	int	i, tmpx, tmpy;
	for (i = 0; i < n / 2; ++i) {
		tmpx = x[i];
		tmpy = y[i];
		x[i] = x[n - i - 1];
		y[i] = y[n - i - 1];
		x[n - i - 1] = tmpx;
		y[n - i - 1] = tmpy;
	}
}

// �}�`�̕ӂ��x�N�g���ɕ���
void AddVector(int n, int *x, int *y) {
	for (int i = 1; i < n; ++i) {
		if (y[i - 1] != y[i]) {
			// �����ł͂Ȃ��x�N�g��������o�^
			// ���W��10�{�ɂ��ēo�^(((���Ȃ�����
			vx1[vn] = x[i - 1];
			vy1[vn] = y[i - 1];
			vx2[vn] = x[i];
			vy2[vn] = y[i];
			++vn;
		}
	}
	//printf("debug>addV vn=%d\n",vn);
}

// �������t�ł҂�����d�Ȃ��Ă���x�N�g���y�A������
void DeleteVectorPair() {
	for (int i = 0; i < vn - 1; ++i) {
		for (int j = i + 1; j < vn; ++j) {
			if ((vx1[i] == vx2[j]) && (vy1[i] == vy2[j]) && (vx2[i] == vx1[j]) && (vy2[i] == vy1[j])) {
				//printf("debug> Vector deleted.\n");
				// �x�N�g��j������
				--vn;
				if (j != vn) {
					// �Ō�̃x�N�g����j���㏑��
					vx1[j] = vx1[vn];
					vy1[j] = vy1[vn];
					vx2[j] = vx2[vn];
					vy2[j] = vy2[vn];
				}
				// �x�N�g��i������
				--vn;
				if (i != vn) {
					// �Ō�̃x�N�g����i���㏑��
					vx1[i] = vx1[vn];
					vy1[i] = vy1[vn];
					vx2[i] = vx2[vn];
					vy2[i] = vy2[vn];
				}
				// �ύX�����̂ŁA�x�N�g��i ����Ē����B
				--i;
				break;
			}
		}
	}
}

// �x�N�g������_����ђ��_�̂����W�ŕ���
void CutVector() {
	int	i, j, k, cutn, cuty[256], cx, cy;
	double	a, b, c, d, e, f, y;
	// �������t�ł҂�����d�Ȃ��Ă���x�N�g���y�A������
	DeleteVectorPair();
	//printf("debug>cut vn=%d\n",vn);
	  // �x�N�g���̌�_��y���W�Ńx�N�g���𕪒f
	for (i = 0; i < vn - 1; ++i) {
		a = vy2[i] - vy1[i];
		b = vx1[i] - vx2[i];
		c = vx2[i] * vy1[i] - vy2[i] * vx1[i];
		for (j = i + 1; j < vn; ++j) {
			d = vy2[j] - vy1[j];
			e = vx1[j] - vx2[j];
			f = vx2[j] * vy1[j] - vy2[j] * vx1[j];
			if (b*d - a*e != 0) {
				y = (a*f - c*d) / (b*d - a*e);
				
				if ((y < 10 * 10) || (y > 310 * 10)) continue;
				cy = (int)(y + 0.5);
				if (ceil(y)!=floor(y)) {
					printf("debug>y�������ł�\n");
				}
				if ((((cy > vy1[i]) && (cy < vy2[i])) || ((cy < vy1[i]) && (cy > vy2[i]))) &&
					(((cy > vy1[j]) && (cy < vy2[j])) || ((cy < vy1[j]) && (cy > vy2[j])))) {
					// �x�N�g��i��j�͌������Ă���B
					// ���x�N�g������_�ŕ�������B
					// �x�N�g��i,j��ύX���A�������đ������x�N�g���𖖔��ɒǉ��B
					cx = (int)((c*e - b*f) / (b*d - a*e) + 0.5);
					if (ceil(((c*e - b*f) / (b*d - a*e) )) != floor(((c*e - b*f) / (b*d - a*e) ))) {
						printf("debug>x�������ł�\n");
					}
					vx2[vn] = vx2[i];
					vy2[vn] = vy2[i];
					vx2[i] = vx1[vn] = cx;
					vy2[i] = vy1[vn] = cy;
					++vn;
					vx2[vn] = vx2[j];
					vy2[vn] = vy2[j];
					vx2[j] = vx1[vn] = cx;
					vy2[j] = vy1[vn] = cy;
					++vn;
					if (vn > 253) {
						printf("�x�N�g�����̍ő�𒴂��Ă��܂��܂���\n");
						vn = 0;
						return;
					}
					// �ύX�����̂ŁA�x�N�g��i ����Ē����B
					--i;
					break;
				}
			}
		}
	}

	//// �x�N�g���̒��_��y���W�Ńx�N�g���𕪒f����B
	// �n�_��y���W�𒲂ׂ�B
	cutn = 0;
	for (i = 0; i < vn; ++i) {
		for (j = 0; j < cutn; ++j) {
			if (vy1[i] == cuty[j]) break;
		}
		if (j == cutn) {
			// ���o�^�Ȃ�o�^�B
			cuty[cutn] = vy1[i];
			++cutn;
		}
	}
	// ���ׂ�y���W�Ńx�N�g���𕪒f
	for (i = 0; i < cutn; ++i) {
		k = vn;
		for (j = 0; j < k; ++j) {
			if (((vy1[j] < cuty[i]) && (vy2[j] > cuty[i])) || ((vy1[j] > cuty[i]) && (vy2[j] < cuty[i]))) {
				vx2[vn] = vx2[j];
				vy2[vn] = vy2[j];
				vx2[j] = vx1[vn] = (int)(0.5 + vx1[j] + (vx2[j] - vx1[j])*(cuty[i] - vy1[j]) / (vy2[j] - vy1[j]));
				vy2[j] = vy1[vn] = cuty[i];
				++vn;
				//printf("debug>vn=%d\n",vn);
				if (vn > 254) {
					printf("debug>vn���ő�\n");
					vn = 0;
					return;
				}
			}
		}
	}
	// �������t�ł҂�����d�Ȃ��Ă���x�N�g���y�A������
	DeleteVectorPair();
	//printf("debug>cutn=%d\n",cutn);

}

// �Q�̃x�N�g�����r����B
int CompareVector(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
	// �����W���傫�����́A�����W�������Ȃ炘���W�����������̂���ʁB
	// �`���a�@�Ȃ�|�P��Ԃ��B
	// �`���a�@�Ȃ�O��Ԃ��B
	// �`���a�@�Ȃ�P��Ԃ��B
	// ���O�̏����ɂ��Q�̃x�N�g���͌������Ă��Ȃ��͂��B
	// �܂��A�����W�͈̔͂͂҂����蓯�����A�S���d�Ȃ�Ȃ����̂ǂ��炩�ɂȂ��Ă���͂��B

	if (ay1 + ay2 < by1 + by2) return -1;
	if (ay1 + ay2 > by1 + by2) return 1;
	if (ax1 + ax2 < bx1 + bx2) return 1;
	if (ax1 + ax2 > bx1 + bx2) return -1;
	return 0;
}

// �x�N�g�����\�[�g����By���傫�����̂�D��By�������Ȃ�x�̏��������̂�D��B
void SortVector() {
	// �q�[�v�\�[�g���g�p�B
	int	i, j, k, n;
	int	x1, y1, x2, y2;

	n = vn;
	for (k = n / 2; k >= 1; k--)
	{
		i = k;
		x1 = vx1[i - 1];
		y1 = vy1[i - 1];
		x2 = vx2[i - 1];
		y2 = vy2[i - 1];
		while ((j = 2 * i) <= n)
		{
			if ((j < n) && (CompareVector(vx1[j - 1], vy1[j - 1], vx2[j - 1], vy2[j - 1], vx1[j], vy1[j], vx2[j], vy2[j]) > 0)) j++;
			if (CompareVector(x1, y1, x2, y2, vx1[j - 1], vy1[j - 1], vx2[j - 1], vy2[j - 1]) <= 0) break;
			vx1[i - 1] = vx1[j - 1];
			vy1[i - 1] = vy1[j - 1];
			vx2[i - 1] = vx2[j - 1];
			vy2[i - 1] = vy2[j - 1];
			i = j;
		}
		vx1[i - 1] = x1;
		vy1[i - 1] = y1;
		vx2[i - 1] = x2;
		vy2[i - 1] = y2;
	}
	while (n > 1)
	{
		x1 = vx1[n - 1];
		y1 = vy1[n - 1];
		x2 = vx2[n - 1];
		y2 = vy2[n - 1];
		vx1[n - 1] = vx1[0];
		vy1[n - 1] = vy1[0];
		vx2[n - 1] = vx2[0];
		vy2[n - 1] = vy2[0];
		n--;
		i = 1;
		while ((j = 2 * i) <= n)
		{
			if ((j < n) && (CompareVector(vx1[j - 1], vy1[j - 1], vx2[j - 1], vy2[j - 1], vx1[j], vy1[j], vx2[j], vy2[j]) > 0)) j++;
			if (CompareVector(x1, y1, x2, y2, vx1[j - 1], vy1[j - 1], vx2[j - 1], vy2[j - 1]) <= 0) break;
			vx1[i - 1] = vx1[j - 1];
			vy1[i - 1] = vy1[j - 1];
			vx2[i - 1] = vx2[j - 1];
			vy2[i - 1] = vy2[j - 1];
			i = j;
		}
		vx1[i - 1] = x1;
		vy1[i - 1] = y1;
		vx2[i - 1] = x2;
		vy2[i - 1] = y2;
	}
}

// �m�n�s����
void OnNot() {
	//double	ang;
	int	i, j, yy;

	//// �}�`�`�͉E���A�}�`�a�͍����ɂ���B

	// �}�`�`�ɂ���
	//ang = CheckAngle(ap,ax,ay);
	//if ((ang > 2*PI-0.1) && (ang < 2*PI+0.1))
		//Reverse(ap,ax,ay);
	//else if (!((ang > -2*PI-0.1) && (ang < -2*PI+0.1)))
	//	("�}�`�`�͂˂���Ă��܂��B����ɏ����ł��܂���B");

	// �}�`�a�ɂ���
	//ang = CheckAngle(bp,bx,by);
	//if ((ang > -2*PI-0.1) && (ang < -2*PI+0.1))
	Reverse(bp, bx, by);
	//else if (!((ang > 2*PI-0.1) && (ang < 2*PI+0.1)))
		//("�}�`�a�͂˂���Ă��܂��B����ɏ����ł��܂���B");

	// �x�N�g���ɕ���
	vn = 0;
	AddVector(ap, ax, ay);
	AddVector(bp, bx, by);
	CutVector();

	// �x�N�g�����\�[�g
	SortVector();

	// ���Z���ʂ𒊏o
	rc = 0;
	rp[rc] = 0;
	yy = 0;
	for (i = 0; i < vn; ++i) {
		if (vy1[i] + vy2[i] != yy) {
			yy = vy1[i] + vy2[i];
			j = 0;
		}
		if (vy1[i] < vy2[i])
			++j;
		else
			--j;

		if ((rp[rc] == 0) && (j == 1)) {
			rp[rc] = 5;
			rx[rc][0] = rx[rc][4] = vx1[i];
			ry[rc][0] = ry[rc][4] = vy1[i];
			rx[rc][1] = vx2[i];
			ry[rc][1] = vy2[i];
		}
		else if ((rp[rc] > 0) && (j == 0)) {
			rx[rc][2] = vx1[i];
			ry[rc][2] = vy1[i];
			rx[rc][3] = vx2[i];
			ry[rc][3] = vy2[i];
			++rc;
			rp[rc] = 0;
		}
	}
	tcnt = 0;
	OnMerge();
	//printf("rp[rc]:%d\n", rp[rc]);

	for (int i = 0; i < rc; ++i) {
		/*for (int j = 0; j < rp[i]; ++j) {
			if (i != 0 && rx[i][j] == rx[i][j] && ry[i][j] == ry[i][j-1]) {
				printf("debug>(%d,%d)��(%d,%d)�폜\n",rx[i][j], ry[i][j], rx[i][j - 1], ry[i][j - 1]);
				erase(std::begin(rx[i]) + i , std::end(rx[i]) );
				rp[i]--;
			}
		}*/
		Reverse(rp[i], rx[i], ry[i]);
	}
	OnClean();
}

// ���o�}�`���̊O�`��(x1,y)-(x2,y)�ɐڂ���}�`�𒲍�����B
void MergeObject(int n, int x1, int x2, int y) {
	int	i;

	if (x1 < x2)
	{
		for (i = 0; i < rc; ++i)
		{
			// �}�[�W�ς݂Ȃ玟��
			if (used[i] > 0) continue;

			// ���ӂ̂����W������Ă��邩�A���ɐ�����O�p�`�Ȃ玟��
			if ((ry[i][4] != y) || (rx[i][3] == rx[i][4])) continue;

			// ���ӂ̂��͈͂��O��Ă����玟��
			if ((rx[i][3] <= x1) || (rx[i][4] >= x2)) continue;

			// �����܂ŗ��ꂽ��ӂŐڂ��Ă���B
			++used[i];

			// �����ɂ͂ݏo���Ă���ꍇ�A�͂ݏo���������𒲍��B
			if (rx[i][4] < x1) MergeObject(i, x1, rx[i][4], y);

			// �������_����P���W�ł͂Ȃ��ꍇ�A�}�[�W��}�`�ɒ��_��ǉ��B
			if (rx[i][4] != x1)
			{
				tx[tp] = rx[i][4];
				ty[tp] = y;
				++tp;
			}

			// ���㒸�_���}�[�W��}�`�ɒǉ��B
			tx[tp] = rx[i][1];
			ty[tp] = ry[i][1];
			++tp;

			// ��ɐ�����O�p�`�łȂ��ꍇ�A�}�`�̏�ӂ𒲍����A�}�[�W��}�`�ɉE�㒸�_��ǉ��B
			if (rx[i][1] != rx[i][2])
			{
				MergeObject(i, rx[i][1], rx[i][2], ry[i][1]);
				tx[tp] = rx[i][2];
				ty[tp] = ry[i][2];
				++tp;
			}

			// �E�����_����Q���W�ł͂Ȃ��ꍇ�A�}�[�W��}�`�ɒ��_��ǉ��B
			if (rx[i][3] != x2)
			{
				tx[tp] = rx[i][3];
				ty[tp] = y;
				++tp;
			}

			// �}�`���E���ɂ͂ݏo���Ă���ꍇ�A�͂ݏo���������𒲍��B
			if (rx[i][3] > x2) MergeObject(i, rx[i][3], x2, y);
		}
	}
	else
	{
		for (i = rc - 1; i >= 0; --i)
		{
			// �}�[�W�ς݂Ȃ玟��
			if (used[i] > 0) continue;

			// ��ӂ̂����W������Ă��邩�A��ɐ�����O�p�`�Ȃ玟��
			if ((ry[i][1] != y) || (rx[i][1] == rx[i][2])) continue;

			// ��ӂ̂��͈͂��O��Ă����玟��
			if ((rx[i][2] <= x2) || (rx[i][1] >= x1)) continue;

			// �����܂ŗ��ꂽ��ӂŐڂ��Ă���B
			++used[i];

			// �E���ɂ͂ݏo���Ă���ꍇ�A�͂ݏo���������𒲍��B
			if (rx[i][2] > x1) MergeObject(i, x1, rx[i][2], y);

			// �E�㒸�_����P���W�ł͂Ȃ��ꍇ�A�}�[�W��}�`�ɒ��_��ǉ��B
			if (rx[i][2] != x1)
			{
				tx[tp] = rx[i][2];
				ty[tp] = y;
				++tp;
			}

			// �E�����_���}�[�W��}�`�ɒǉ��B
			tx[tp] = rx[i][3];
			ty[tp] = ry[i][3];
			++tp;

			// ���ɐ�����O�p�`�łȂ��ꍇ�A�}�`�̉��ӂ𒲍����A�}�[�W��}�`�ɍ������_��ǉ��B
			if (rx[i][3] != rx[i][4])
			{
				MergeObject(i, rx[i][3], rx[i][4], ry[i][3]);
				tx[tp] = rx[i][0];
				ty[tp] = ry[i][0];
				++tp;
			}

			// ���㒸�_����Q���W�ł͂Ȃ��ꍇ�A�}�[�W��}�`�ɒ��_��ǉ��B
			if (rx[i][1] != x2)
			{
				tx[tp] = rx[i][1];
				ty[tp] = y;
				++tp;
			}

			// �}�`�������ɂ͂ݏo���Ă���ꍇ�A�͂ݏo���������𒲍��B
			if (rx[i][1] < x2) MergeObject(i, rx[i][1], x2, y);
		}
	}
}

// �}�[�W����
void OnMerge() {
	int	i, j;

	// ���s�ς݂��A�}�`��������Ή������Ȃ��B
	if ((tcnt > 0) || (rc == 0)) return;

	// �}�[�W�ς݃t���O��������
	for (i = 0; i < rc; ++i) used[i] = 0;

	for (i = 0; i < rc; ++i)
	{
		if (used[i] > 0)
			continue; // �}�[�W�ς݂Ȃ玟��
		else
			++used[i]; // �����łȂ���΃}�[�W�ς݃t���O�𗧂Ă�B

					   // �E��ƉE���̍��W���}�[�W��}�`�ɒǉ��B
		tp = 0;
		tx[tp] = rx[i][2];
		ty[tp] = ry[i][2];
		++tp;
		tx[tp] = rx[i][3];
		ty[tp] = ry[i][3];
		++tp;

		// �}�`�����ɐ�����O�p�`�Ŗ����ꍇ�A���ӂ𒲍����A�������_���}�[�W��}�`�ɒǉ��B
		if (rx[i][3] != rx[i][4])
		{
			MergeObject(i, rx[i][3], rx[i][4], ry[i][3]);
			tx[tp] = rx[i][4];
			ty[tp] = ry[i][4];
			++tp;
		}

		// ����̍��W���}�[�W��}�`�ɒǉ��B
		tx[tp] = rx[i][1];
		ty[tp] = ry[i][1];
		++tp;

		// �}�`����ɐ�����O�p�`�Ŗ����ꍇ�A��ӂ𒲍����A�E�㒸�_���}�[�W��}�`�ɒǉ��B
		if (rx[i][1] != rx[i][2])
		{
			MergeObject(i, rx[i][1], rx[i][2], ry[i][1]);
			tx[tp] = rx[i][2];
			ty[tp] = ry[i][2];
			++tp;
		}

		// �}�[�W�������ʂ𒊏o�}�`�ɏ㏑���R�s�[����B
		// �㏑�������}�`�̓}�[�W�ς݂Ȃ̂Ŗ��Ȃ��B
		if (used[tcnt] == 0) printf("�}�[�W�ς݂łȂ��}�`���㏑������Ă��܂��I");
		for (j = 0; j < tp; ++j)
		{
			rx[tcnt][j] = tx[j];
			ry[tcnt][j] = ty[j];
		}
		rp[tcnt] = tp;
		++tcnt;
	}
	rc = tcnt;

}

// �璷�_�폜�̏���
void OnClean() {
	int	i, j;
	double	a, b, c, len;

	if (tcnt == 0) return; // �}�[�W�O�Ȃ�߂�B

	for (i = 0; i < rc; ++i)
	{
		tx[0] = rx[i][0];
		ty[0] = ry[i][0];
		tp = 1;
		for (j = 1; j < rp[i] - 1; ++j)
		{
			// ����(tx[tp-1],ty[tp-1])-(rx[i][j+1],ry[i][j+1])�ɑ΂���
			// �_(rx[i][j],ry[i][j])���琂�������낵�����A
			// ���̒������P�ʒ������Ȃ�璷�_�Ƃ݂Ȃ��B

			// �����̕����� ax+by+c=0�C�����̒��� len
			a = ry[i][j + 1] - ty[tp - 1];
			b = tx[tp - 1] - rx[i][j + 1];
			c = rx[i][j + 1] * ty[tp - 1] - ry[i][j + 1] * tx[tp - 1];
			len = (a * rx[i][j] + b * ry[i][j] + c) / sqrt(a * a + b * b);
			if ((len >= 0.5) || (len <= -0.5))
			{
				// �����������̂ŏ璷�_�ł͂Ȃ��B
				tx[tp] = rx[i][j];
				ty[tp] = ry[i][j];
				++tp;
			}
		}
		// �I�n�_��v������
		tx[tp] = rx[i][0];
		ty[tp] = ry[i][0];
		++tp;

		// �璷�_�폜��̍��W�Ń��X�g���㏑��
		for (j = 0; j < tp; ++j)
		{
			rx[i][j] = tx[j];
			ry[i][j] = ty[j];
		}
		rp[i] = tp;
	}

}
