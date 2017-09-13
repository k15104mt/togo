#include"piece.hpp"
#include<algorithm>
#include<cstdlib>	// fabs()
#define NOMINMAX
#include<color.hpp>
#define PI 3.14159265358979

//どれだけ回転するかと基準点の座標を送り回転後の座標を返す
Point PointRotate(double angle, Point zeroPoint) {
	Point r;
	r.x = static_cast<int>(round(zeroPoint.x*cos(angle) - zeroPoint.y*sin(angle)));
	r.y = static_cast<int>(round(zeroPoint.x*sin(angle) + zeroPoint.y*cos(angle)));
	return r;
}

//頂点の順を逆に(反時計回り→時計回り)
void reverse(std::vector<Point> &data) {
	int	i, tmpx, tmpy,n=data.size();
	for (i = 0; i < n/ 2; ++i) {
		tmpx = data[i].x;
		tmpy = data[i].y;
		data[i].x = data[n - i - 1].x;
		data[i].y = data[n - i - 1].y;
		data[n - i - 1].x = tmpx;
		data[n - i - 1].y = tmpy;
	}
}

//保存済み図形(point)に生成した図形(tmp)と等しいものがあるかどうか
bool shapeEquals(std::vector<Point> &tmp , std::vector<std::vector<Point>> &point,int &num){
	for (int j = 0; j < point.size(); j++) {
		for (int k = 0; k < num; k++) {
			if (tmp[0] == point[j][k]) {
				int count = 0;
				int k_ = k;
				//setColor(F_ORANGE | F_INTENSITY); printf("[%d][%d](%d,%d)\n", j, k_, point[j][k_].x, point[j][k_].y); setColor();
				while (count<num) {
					if (k_ >= num)k_ = 0;
					if (tmp[count] == point[j][k_]) {
						//setColor(F_RED | F_INTENSITY); printf("tmp[%d]==point[%d][%d]\n", count, j, k_); setColor();
						count++;
					}
					else {
						//setColor(F_RED | F_INTENSITY); printf("合いませんでした\n"); setColor();
						break;
					}
					k_++;
				}
				if (count == num) {
					//printf("合いました！\n");
					return 1;
				}
			}
		}
		//printf("\n");
	}
	return 0;
}

Piece::Piece(std::vector<Point> &data){
  int num = data.size();     		//頂点数
  double sigma=0;					//面積を求める公式におけるシグマ
  std::vector<Point> tmp(num); 		//1回転パターンの一時格納配列
  //printf("num:%d\n", num);

  //ピースの面積を求める
  for (int i = 0; i < num; i++) {
	  if (i == num-1 ) {
		  sigma +=(double) (data[i].x * data[0].y - data[0].x * data[i].y);
	  }
	  else {
		  sigma +=(double)( data[i].x * data[i + 1].y - data[i + 1].x * data[i].y);
	  }
  }
  surface = fabs((1.0 / 2.0)*sigma);
  //printf("debug>面積は%lf\n", surface);
  
  for (int i = 0; i<4; i++){  			//4回回転(90度ずつ)
	Point min;	//ずらすために取得する座標最小値
	//setColor(F_CYAN | F_INTENSITY); printf("\n--回転パターン[%dπ/2]--\n", i); setColor();//debug
	for (int j = 0; j < num; j++) {
	  tmp[j] = PointRotate((1.0 / 2.0)*i*PI, data[j]);
	  if (j == 0) { min.x = tmp[j].x; min.y = tmp[j].y; }
	  min.x = std::min(min.x, tmp[j].x);
	  min.y = std::min(min.y, tmp[j].y);
	}
	move(tmp, Point(-min.x,-min.y));
	//for(int j=0;j<num;j++) printf("(%d,%d)\n", tmp[j].x, tmp[j].y); //debug
	
	if (i == 0 || !shapeEquals(tmp, point, num)) {
		point.push_back(tmp); //一つの回転パターンをpushback
		//printf("push_back\n");
	}

	//setColor(F_GREEN | F_INTENSITY); printf("\n--反転パターン[%dπ/2]--\n", i); setColor();
	for (int j = 0; j < num; j++) {
		tmp[j] = tmp[j] = PointRotate((1.0 / 2.0)*i*PI, data[j]);
		tmp[j].x *= -1;
		if (j == 0) { min.x = tmp[j].x; min.y = tmp[j].y; }
		min.x = std::min(min.x, tmp[j].x);
		min.y = std::min(min.y, tmp[j].y);
	}
	move(tmp, Point(-min.x, -min.y));
	reverse(tmp);
	//for (int j = 0; j<num; j++) printf("(%d,%d)\n", tmp[j].x, tmp[j].y); //debug

	if (!shapeEquals(tmp, point, num)) {
		point.push_back(tmp); //一つの反転パターンをpushback
		//printf("push_back\n");
	}
  }
}

std::vector<std::vector<Point>> Piece::getPoint() const{
  return point;
}

int Piece::getSize() {
  return static_cast<int>(point[0].size());
}

double Piece::getSurface() {
	return surface;
}