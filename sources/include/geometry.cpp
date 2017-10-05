#include"geometry.hpp"
#include"color.hpp"
#include<array>
#include<cstdlib>
#include<math.h>
#define PI 3.1415926535

void OnNot(int &ap,int &bp, std::vector<Point> &a, std::vector<Point> &b,int &rc,int *rp, std::vector<std::vector<D_Point>> &r);
void OnMerge(int &tcnt, int &tp, double *tx, double *ty, double *used, std::vector<std::vector<D_Point>> &r, int &rc, int *rp);
void OnClean(int &tcnt, int &tp, double *tx, double *ty, double *used, std::vector<std::vector<D_Point>> &r, int &rc, int *rp);
Point getPoint(std::vector<std::vector<Point>> &areaPoint,int putMode);				//�G���A���̍�����W���擾
double calculateSurface(std::vector<Point> &data);				//�ʐς��擾

//�R���X�g���N�^
Geometry::Geometry(std::vector<std::vector<Point>> &framePoint) {
	areaPoint = framePoint;
	//putNum = 0;
}

//�Ƃ肠�������_����ԍ���̕����ɐݒu����Ƃ���
Point Geometry::getPutPoint(std::vector<Piece> &data, std::vector<putData> &already_put,int putMode){
	Point point;	//�Ԃ�l
	Point tmp;
	int putNum;
	int	ap=0, bp=0;	// ���͐}�`�̋L���p	ap,bp:���_��
	std::vector<Point> a;
	std::vector<Point> b;

	int	rc=0, rp[MAX];		// ���Z��}�`�̋L���p
	std::vector<std::vector<D_Point>> r;
	std::vector<std::vector<Point>> tmpArea;

	r.resize(MAX);
	for (int i = 0; i < MAX; i++) {
		r[i].resize(MAX);
	}

	//setColor(F_CYAN|F_INTENSITY, B_BLACK); printf("\n�ݒu�s�[�X�ԍ�:%d\n�����G���A��:%d\n", already_put.size()-1, areaPoint.size()); 
	//printf("<�����t���[�����W>\n"); for (int i = 0; i < (int)areaPoint.size(); i++) { printf("area[%d]:", i); for (int j = 0; j < (int)areaPoint[i].size(); j++) { printf("{%d,%d} ", areaPoint[i][j].x, areaPoint[i][j].y); }printf("\n"); }setColor();

	tmpAreaPoint.push_back(areaPoint);	//�ݒu�O��Ԃ�ۑ�

	if (already_put.size() <= 0) {
		return getPoint(areaPoint,putMode);
	}

	////�s�[�X�Ɛݒu�����C���ݒu���̐}�`���_�����߂�
	for (int i = 0; i < (int)areaPoint.size(); i++) {	//�����G���A��
		putNum = already_put.size()-1;
		a.clear();	//�X�V
		b.clear();

		//printf("--�m�F�����G���A[%d]--\n", i);

		bp = areaPoint[i].size() + 1;									//NOT���͐}�`���_��(�t���[��)
		ap = data[already_put[putNum].piece_num].getPoint()[0].size() + 1;	//NOT���͐}�`���_��(�s�[�X)

		for (int j = 0; j < bp - 1; j++) {	//NOT�����Ŏg���ϐ��i�[
			tmp = areaPoint[i][j];
			b.push_back(tmp);
			//setColor(F_ORANGE); printf("{%d,%d} ", b[j].x, b[j].y); setColor();	//debug
		}
		tmp = b[0];
		b.push_back(tmp);
		//printf("\n--\n");	//debug

		for (int j = 0; j < ap - 1; j++) {	//NOT�����Ŏg���ϐ��i�[
			tmp.x = data[already_put[putNum].piece_num].getPoint()[already_put[putNum].point_num][j].x + already_put[putNum].base_point.x;	//���������ǐݒu�s�[�X�擾���Ă�
			tmp.y = data[already_put[putNum].piece_num].getPoint()[already_put[putNum].point_num][j].y + already_put[putNum].base_point.y;
			a.push_back(tmp);
			//setColor(F_ORANGE); printf("{%d,%d} ",  a[j].x, a[j].y); setColor();	//debug
		}
		//printf("\n");
		tmp = a[0];	//���
		a.push_back(tmp);
		OnNot(ap, bp, a, b, rc, rp, r);

		areaPoint.erase(areaPoint.begin() + i);	//��U���Ă�G���A�폜���팸����
												////NOT�ŏo�����ݒu�s�[�X���ƃt���[������������
												//���ݒu�G���A�̍X�V
		for (int i = 0; i < rc; i++) {
			std::vector<Point> Tmp;
			for (int j = 0; j < rp[i]; j++) {
				tmp.x = static_cast<int>(r[i][j].x + 0.5);
				tmp.y = static_cast<int>(r[i][j].y + 0.5);
				Tmp.push_back(tmp);
			}
			areaPoint.insert(areaPoint.begin() + i, Tmp);
			tmpArea.push_back(Tmp);
		}

		//�����܂ł����ƍX�V
	}
	areaPoint = tmpArea;
	point = getPoint(areaPoint,putMode);
	if (areaPoint.size() == 0) {
		setColor(F_RED | F_INTENSITY); printf("�G���[�F�G���A���S�Ė��܂�܂���(getPutPoint)\n"); setColor();
		return Point(-1, -1);
	}

	//�����G���A�̍ŏ��ʐς��i�[
	for (int i = 0; i < areaPoint.size(); i++) {
		double surface = calculateSurface(areaPoint[i]);
		if (i == 0 || minSurface > surface)minSurface = surface;

		double angle=calculateAngle(areaPoint[i]);
		if (i == 0 || minAngle > angle)minAngle = angle;

	}	


	//putNum++;
	return point;
}

//�ݒu������O��
void Geometry::cancelPut() {
	areaPoint = tmpAreaPoint[tmpAreaPoint.size()-1];
	tmpAreaPoint.pop_back();
	//putNum--;
}

// ptr: �폜�ʒu  last: �z�񖖔��ʒu�i�Ō�̗v�f�̎��j
void erase(int *ptr, int *last) {
	while (++ptr < last)
		*(ptr - 1) = *ptr;       //  �v�f���ЂƂO�ɂ��炷
}
// ���_�̋Ȃ���p�x�̍��v�����߁C���v���Ȃ�1���C�����v���Ȃ�-1���C�˂���Ă���Ȃ�0��Ԃ�
int CheckAngle(std::vector<Point> point) {
	int	i,n=point.size();
	double	a1, a2, ang, total;

	total = 0;
	point[n].x = point[1].x;
	point[n].y = point[1].y;
	for (i = 1; i < n; ++i)
	{
		a1 = atan2(point[i].y - point[i - 1].y, point[i].x - point[i - 1].x);
		a2 = atan2(point[i + 1].y - point[i].y, point[i + 1].x - point[i].x);
		ang = a2 - a1;
		while (ang > PI) ang -= (2 * PI);
		while (ang < -PI) ang += (2 * PI);
		total += ang;
	}
	if ((total > 2 * PI - 0.1) && (total < 2 * PI + 0.1))return -1;			//�����v���
	else if (!((ang > -2 * PI - 0.1) && (ang < -2 * PI + 0.1)))return 0;	//�˂���Ă���}�`
	
	return 1;	//����Ȏ��v���}�`
}

// ���_�̕��я��𔽓]����
void Reverse(int n,std::vector<Point> &point) {
	Point tmp;
	int	i;
	for (i = 0; i < n / 2; ++i) {
		tmp = point[i];
		point[i] = point[n - i - 1];
		point[n - i - 1] = tmp;
	}
}

// ���_�̕��я��𔽓]����
void Reverse(int n, std::vector<D_Point> &point) {
	D_Point tmp;
	int	i;
	for (i = 0; i < n / 2; ++i) {
		tmp = point[i];
		point[i] = point[n - i - 1];
		point[n - i - 1] = tmp;
	}
}

// �}�`�̕ӂ��x�N�g���ɕ���
void AddVector(int n, std::vector<Point> &point, double *vx1,double *vy1,double *vx2,double *vy2,int &vn) {
	for (int i = 1; i < n; ++i) {
		if (point[i - 1].y != point[i].y) {
			// �����ł͂Ȃ��x�N�g��������o�^
			// ���W��10�{�ɂ��ēo�^(((�����Ȃ����܂���
			vx1[vn] = point[i - 1].x;
			vy1[vn] = point[i - 1].y;
			vx2[vn] = point[i].x;
			vy2[vn] = point[i].y;
			++vn;
		}
	}
	//printf("debug>addV vn=%d\n",vn);
}

// �������t�ł҂�����d�Ȃ��Ă���x�N�g���y�A������
void DeleteVectorPair(double *vx1, double *vy1, double *vx2, double *vy2, int &vn) {
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
void CutVector(double *vx1, double *vy1, double *vx2, double *vy2, int &vn) {
	int	i, j, k, cutn;
	double	a, b, c, d, e, f, y,cuty[MAX], cx, cy;
	// �������t�ł҂�����d�Ȃ��Ă���x�N�g���y�A������
	DeleteVectorPair(vx1, vy1, vx2, vy2, vn);
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
				//cy = (int)(y + 0.5);
				cy = y;
				//printf("cy:%lf,",y);
				if ((((cy > vy1[i]) && (cy < vy2[i])) || ((cy < vy1[i]) && (cy > vy2[i]))) &&
					(((cy > vy1[j]) && (cy < vy2[j])) || ((cy < vy1[j]) && (cy > vy2[j])))) {
					// �x�N�g��i��j�͌������Ă���B
					// ���x�N�g������_�ŕ�������B
					// �x�N�g��i,j��ύX���A�������đ������x�N�g���𖖔��ɒǉ��B
					//cx = (int)((c*e - b*f) / (b*d - a*e));
					cx = (c*e - b*f) / (b*d - a*e);
					//printf("cx:%lf", (c*e - b*f) / (b*d - a*e));
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
					if (vn > MAX-3) {
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
				//vx2[j] = vx1[vn] = (int)(0.5 + vx1[j] + (vx2[j] - vx1[j])*(cuty[i] - vy1[j]) / (vy2[j] - vy1[j]));
				vx2[j] = vx1[vn] = vx1[j] + (vx2[j] - vx1[j])*(cuty[i] - vy1[j]) / (vy2[j] - vy1[j]);
				vy2[j] = vy1[vn] = cuty[i];
				++vn;
				//printf("debug>vn=%d\n",vn);
				if (vn > MAX-2) {
					printf("debug>vn���ő�\n");
					vn = 0;
					return;
				}
			}
		}
	}
	// �������t�ł҂�����d�Ȃ��Ă���x�N�g���y�A������
	DeleteVectorPair(vx1, vy1, vx2, vy2, vn);
	//printf("debug>cutn=%d\n",cutn);

}

// �Q�̃x�N�g�����r����B
int CompareVector(double ax1, double ay1, double ax2, double ay2, double bx1, double by1, double bx2, double by2) {
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
void SortVector(double *vx1, double *vy1, double *vx2, double *vy2, int &vn) {
	// �q�[�v�\�[�g���g�p�B
	int	i, j, k, n;
	double	x1, y1, x2, y2;

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
void OnNot(int &ap, int &bp, std::vector<Point> &a, std::vector<Point> &b, int &rc, int *rp, std::vector<std::vector<D_Point>> &r) {
	int	vn = 0;
	double vx1[MAX], vy1[MAX], vx2[MAX], vy2[MAX];	// �x�N�g���̋L���p
	int	tcnt = 0, tp;
	double tx[MAX], ty[MAX], used[MAX];		// �ꎞ�L���p

	//double	ang;
	int	i, j;
	double yy;

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
	Reverse(b.size(),b);
	//else if (!((ang > 2*PI-0.1) && (ang < 2*PI+0.1)))
		//("�}�`�a�͂˂���Ă��܂��B����ɏ����ł��܂���B");

	// �x�N�g���ɕ���
	vn = 0;
	AddVector(ap, a, vx1, vy1, vx2,vy2, vn);
	AddVector(bp, b, vx1, vy1, vx2, vy2, vn);
	CutVector(vx1, vy1, vx2, vy2, vn);

	// �x�N�g�����\�[�g
	SortVector(vx1, vy1, vx2, vy2, vn);

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
			r[rc][0].x = r[rc][4].x = vx1[i];
			r[rc][0].y = r[rc][4].y = vy1[i];
			r[rc][1].x = vx2[i];
			r[rc][1].y = vy2[i];
		}
		else if ((rp[rc] > 0) && (j == 0)) {
			r[rc][2].x = vx1[i];
			r[rc][2].y = vy1[i];
			r[rc][3].x = vx2[i];
			r[rc][3].y = vy2[i];
			++rc;
			rp[rc] = 0;
		}
	}
	tcnt = 0;
	OnMerge(tcnt,tp,tx, ty,used, r, rc, rp);
	//printf("rp[rc]:%d\n", rp[rc]);

	for (int i = 0; i < rc; ++i) {
		Reverse(rp[i], r[i]);
	}
	OnClean(tcnt, tp, tx, ty, used, r, rc, rp);
}

// ���o�}�`���̊O�`��(x1,y)-(x2,y)�ɐڂ���}�`�𒲍�����B
void MergeObject(int n, double x1, double x2, double y,int	&tcnt,int &tp,double *tx,double *ty,double *used, std::vector<std::vector<D_Point>> &r,int &rc) {
	int	i;

	if (x1 < x2)
	{
		for (i = 0; i < rc; ++i)
		{
			// �}�[�W�ς݂Ȃ玟��
			if (used[i] > 0) continue;

			// ���ӂ̂����W������Ă��邩�A���ɐ�����O�p�`�Ȃ玟��
			if ((r[i][4].y != y) || (r[i][3].x == r[i][4].x)) continue;

			// ���ӂ̂��͈͂��O��Ă����玟��
			if ((r[i][3].x <= x1) || (r[i][4].x >= x2)) continue;

			// �����܂ŗ��ꂽ��ӂŐڂ��Ă���B
			++used[i];

			// �����ɂ͂ݏo���Ă���ꍇ�A�͂ݏo���������𒲍��B
			if (r[i][4].x < x1) MergeObject(i, x1, r[i][4].x, y, tcnt,tp,tx,ty,used,r,rc);

			// �������_����P���W�ł͂Ȃ��ꍇ�A�}�[�W��}�`�ɒ��_��ǉ��B
			if (r[i][4].x != x1)
			{
				tx[tp] = r[i][4].x;
				ty[tp] = y;
				++tp;
			}

			// ���㒸�_���}�[�W��}�`�ɒǉ��B
			tx[tp] = r[i][1].x;
			ty[tp] = r[i][1].y;
			++tp;

			// ��ɐ�����O�p�`�łȂ��ꍇ�A�}�`�̏�ӂ𒲍����A�}�[�W��}�`�ɉE�㒸�_��ǉ��B
			if (r[i][1].x != r[i][2].x)
			{
				MergeObject(i, r[i][1].x, r[i][2].x, r[i][1].y, tcnt, tp, tx, ty, used, r, rc);
				tx[tp] = r[i][2].x;
				ty[tp] = r[i][2].y;
				++tp;
			}

			// �E�����_����Q���W�ł͂Ȃ��ꍇ�A�}�[�W��}�`�ɒ��_��ǉ��B
			if (r[i][3].x != x2)
			{
				tx[tp] = r[i][3].x;
				ty[tp] = y;
				++tp;
			}

			// �}�`���E���ɂ͂ݏo���Ă���ꍇ�A�͂ݏo���������𒲍��B
			if (r[i][3].x > x2) MergeObject(i, r[i][3].x, x2, y, tcnt, tp, tx, ty, used, r, rc);
		}
	}
	else
	{
		for (i = rc - 1; i >= 0; --i)
		{
			// �}�[�W�ς݂Ȃ玟��
			if (used[i] > 0) continue;

			// ��ӂ̂����W������Ă��邩�A��ɐ�����O�p�`�Ȃ玟��
			if ((r[i][1].y != y) || (r[i][1].x == r[i][2].x)) continue;

			// ��ӂ̂��͈͂��O��Ă����玟��
			if ((r[i][2].x <= x2) || (r[i][1].x >= x1)) continue;

			// �����܂ŗ��ꂽ��ӂŐڂ��Ă���B
			++used[i];

			// �E���ɂ͂ݏo���Ă���ꍇ�A�͂ݏo���������𒲍��B
			if (r[i][2].x > x1) MergeObject(i, x1, r[i][2].x, y, tcnt, tp, tx, ty, used, r, rc);

			// �E�㒸�_����P���W�ł͂Ȃ��ꍇ�A�}�[�W��}�`�ɒ��_��ǉ��B
			if (r[i][2].x != x1)
			{
				tx[tp] = r[i][2].x;
				ty[tp] = y;
				++tp;
			}

			// �E�����_���}�[�W��}�`�ɒǉ��B
			tx[tp] = r[i][3].x;
			ty[tp] = r[i][3].y;
			++tp;

			// ���ɐ�����O�p�`�łȂ��ꍇ�A�}�`�̉��ӂ𒲍����A�}�[�W��}�`�ɍ������_��ǉ��B
			if (r[i][3].x != r[i][4].x)
			{
				MergeObject(i, r[i][3].x, r[i][4].x, r[i][3].y, tcnt, tp, tx, ty, used, r, rc);
				tx[tp] = r[i][0].x;
				ty[tp] = r[i][0].y;
				++tp;
			}

			// ���㒸�_����Q���W�ł͂Ȃ��ꍇ�A�}�[�W��}�`�ɒ��_��ǉ��B
			if (r[i][1].x != x2)
			{
				tx[tp] = r[i][1].x;
				ty[tp] = y;
				++tp;
			}

			// �}�`�������ɂ͂ݏo���Ă���ꍇ�A�͂ݏo���������𒲍��B
			if (r[i][1].x < x2) MergeObject(i, r[i][1].x, x2, y, tcnt, tp, tx, ty, used, r, rc);
		}
	}
}

// �}�[�W����
void OnMerge(int &tcnt, int &tp, double *tx, double *ty, double *used, std::vector<std::vector<D_Point>> &r, int &rc,int *rp) {
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
		tx[tp] = r[i][2].x;
		ty[tp] = r[i][2].y;
		++tp;
		tx[tp] = r[i][3].x;
		ty[tp] = r[i][3].y;
		++tp;

		// �}�`�����ɐ�����O�p�`�Ŗ����ꍇ�A���ӂ𒲍����A�������_���}�[�W��}�`�ɒǉ��B
		if (r[i][3].x != r[i][4].x)
		{
			MergeObject(i, r[i][3].x, r[i][4].x, r[i][3].y,tcnt, tp, tx, ty, used, r, rc);
			tx[tp] = r[i][4].x;
			ty[tp] = r[i][4].y;
			++tp;
		}

		// ����̍��W���}�[�W��}�`�ɒǉ��B
		tx[tp] = r[i][1].x;
		ty[tp] = r[i][1].y;
		++tp;

		// �}�`����ɐ�����O�p�`�Ŗ����ꍇ�A��ӂ𒲍����A�E�㒸�_���}�[�W��}�`�ɒǉ��B
		if (r[i][1].x != r[i][2].x)
		{
			MergeObject(i, r[i][1].x, r[i][2].x, r[i][1].y, tcnt, tp, tx, ty, used, r, rc);
			tx[tp] = r[i][2].x;
			ty[tp] = r[i][2].y;
			++tp;
		}

		// �}�[�W�������ʂ𒊏o�}�`�ɏ㏑���R�s�[����B
		// �㏑�������}�`�̓}�[�W�ς݂Ȃ̂Ŗ��Ȃ��B
		if (used[tcnt] == 0) printf("�}�[�W�ς݂łȂ��}�`���㏑������Ă��܂��I");
		for (j = 0; j < tp; ++j)
		{
			r[tcnt][j].x = tx[j];
			r[tcnt][j].y = ty[j];
		}
		rp[tcnt] = tp;
		++tcnt;
	}
	rc = tcnt;

}

// �璷�_�폜�̏���
void OnClean(int &tcnt, int &tp, double *tx, double *ty, double *used, std::vector<std::vector<D_Point>> &r, int &rc, int *rp) {
	int	i, j;
	double	a, b, c, len;

	if (tcnt == 0) return; // �}�[�W�O�Ȃ�߂�B

	for (i = 0; i < rc; ++i)
	{
		tx[0] = r[i][0].x;
		ty[0] = r[i][0].y;
		tp = 1;
		for (j = 1; j < rp[i] - 1; ++j)
		{
			// ����(tx[tp-1],ty[tp-1])-(r[i][j+1].x,r[i][j+1].y)�ɑ΂���
			// �_(r[i][j].x,r[i][j].y)���琂�������낵�����A
			// ���̒������P�ʒ������Ȃ�璷�_�Ƃ݂Ȃ��B���Ƃ��Ă������C���W�������łȂ����Clen��0�Ȃ�璷�_�Ƃ݂Ȃ��ɕύX

			// �����̕����� ax+by+c=0�C�����̒��� len
			a = r[i][j + 1].y - ty[tp - 1];
			b = tx[tp - 1] - r[i][j + 1].x;
			c = r[i][j + 1].x * ty[tp - 1] - r[i][j + 1].y * tx[tp - 1];
			len = (a * r[i][j].x + b * r[i][j].y + c) / sqrt(a * a + b * b);
			
			if (fabs(len)<DBL_EPSILON || len==-0) {	//���������_�^�ɂ�����len==0�Ɠ�������
				//setColor(F_CYAN | F_INTENSITY, B_BLACK); printf("(%2lf,%2lf) len:%lf > �璷�_\n", r[i][j].x, r[i][j].y, len); setColor();
			}
			else if (floor( r[i][j].x)!=ceil(r[i][j].x) || floor(r[i][j].x) != ceil(r[i][j].x)) {	//���W�������łȂ��Ƃ�
				//setColor(F_RED | F_INTENSITY, B_BLACK); printf("(%2lf,%2lf) len:%lf > �璷�_\n", r[i][j].x, r[i][j].y, len); setColor();
			}
			else {
				//printf("(%2lf,%2lf) len:%lf\n", r[i][j].x, r[i][j].y, len);
				// �����������̂ŏ璷�_�ł͂Ȃ��B
				tx[tp] = r[i][j].x;
				ty[tp] = r[i][j].y;
				++tp;
			}

			/*
			if ((len >= 0.5) || (len <= -0.5)){	
				// �����������̂ŏ璷�_�ł͂Ȃ��B
				tx[tp] = r[i][j].x;
				ty[tp] = r[i][j].y;
				++tp;
			}*/

		}
		// �I�n�_��v������
		tx[tp] = r[i][0].x;
		ty[tp] = r[i][0].y;
		++tp;

		// �璷�_�폜��̍��W�Ń��X�g���㏑��
		for (j = 0; j < tp; ++j)
		{
			r[i][j].x = tx[j];
			r[i][j].y = ty[j];
		}
		rp[i] = tp;
	}

}

// �G���A���ł̍�����W�𒲂ׂ�1UP,2RIGHT,3LEFT,4DOWN,5UP_LEFT
Point getPoint(std::vector<std::vector<Point>> &areaPoint,int putMode){
	Point point;
	int tall;			//���������� y=-x+b ��b
	//setColor(F_RED | F_INTENSITY, B_BLACK); printf("%d�Ŗ��߂܂�\n", putMode); setColor();
	for (int i = 0; i < (int)areaPoint.size(); i++) {
		//printf("area[%d]:", i);
		for (int j = 0; j < (int)areaPoint[i].size(); j++) {
			//printf("{%d,%d} ", areaPoint[i][j].x, areaPoint[i][j].y);

			if (i == j&&i == 0) {	//�b��̍���
				if(putMode==5)tall = areaPoint[i][j].x + areaPoint[i][j].y;
				point = areaPoint[i][j];
			}
			//�e�������Ƃōł��������̒��_���i�[
			else if ((putMode == 5 && tall > areaPoint[i][j].x + areaPoint[i][j].y) ||
			(putMode == 1 && areaPoint[i][j].y < point.y) ||
			(putMode == 2 && areaPoint[i][j].x > point.x) ||
			(putMode == 3 && areaPoint[i][j].x < point.x) ||
			(putMode == 4 && areaPoint[i][j].y > point.y)) 
			{
				if (putMode == 5)tall = areaPoint[i][j].x + areaPoint[i][j].y;
				point= areaPoint[i][j]; 
			}
			//�������ꍇ�����Ɋ񂹂�,tall�̒l�������Ȃ��x������������D��(5)
			else if ((putMode==5 && tall == areaPoint[i][j].x + areaPoint[i][j].y &&point.x>areaPoint[i][j].x)||
				((putMode == 1||putMode==4) && areaPoint[i][j].y == point.y && areaPoint[i][j].x < point.x)||
				((putMode == 2||putMode==3) && areaPoint[i][j].x == point.x && areaPoint[i][j].y < point.y)
				) {	
				if (putMode == 5)tall = areaPoint[i][j].x + areaPoint[i][j].y;
				point= areaPoint[i][j]; 
			}

		}
		//printf("\n");
	}
	//printf("���W(%d,%d)\n", point.x, point.y);
	return point;
}

//�ʐς��擾
double calculateSurface(std::vector<Point> &data) {
	int num = data.size();     		//���_��
	double sigma = 0;					//�ʐς����߂�����ɂ�����V�O�}
	
	//�ʐς����߂�
	for (int i = 0; i < num; i++) {
		if (i == num - 1) {
			sigma += (double)(data[i].x * data[0].y - data[0].x * data[i].y);
		}
		else {
			sigma += (double)(data[i].x * data[i + 1].y - data[i + 1].x * data[i].y);
		}
	}

	return fabs((1.0 / 2.0)*sigma);
}

//�G���A�ʐ�<���ݒu�s�[�X�ʐς̏ꍇ0���C�t�Ȃ�1��Ԃ�
bool Geometry::canPut(std::vector<Piece> &data,std::array<int,100> &isPut) {
	for (int i = 0; i < data.size(); i++) {
		if (isPut[i]==0) {
			double surface = calculateSurface(data[i].getPoint()[0]);
			if (surface > minSurface)return 0;	//���̎��_�ł����ݒu�ł��Ȃ�
		}
	}
	


	return 1;	//��ʂ茩�ĖʐςƂ��Ă͑��v
}