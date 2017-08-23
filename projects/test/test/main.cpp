#include"piece.hpp"
#include"utility.hpp"
#include"color.hpp"

#include<cstdio>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<stack>
#include<array>


std::vector<Point> framePoint;


//当たり判定
int checkHit(std::vector<Piece> &, std::vector<putData> &, putData &);

Point getPutPoint(std::vector<Piece> &, std::vector<putData> &);

//再帰
int solve(std::vector<Piece> &, std::vector<putData> &);


int main() {
  //QRコードの数
  int qrNum;
  std::cin >> qrNum;
  std::cin.ignore();

  //QRコードの数だけ入力を繰り返す
  std::vector<std::string> input;
  for (int i = 0; i < qrNum; ++i) {
	std::string temp;
	std::getline(std::cin, temp);
	input.push_back(temp);
  }


  std::vector<std::vector<Point>> piecePoint;
 

  for (int i = 0; i < static_cast<int>(input.size()); ++i) {
	//QRコードi番目の文字列

	//:でピースごとに区切る
	auto pieceStr = split(input[i], ':');
	for (int j = 1; j < static_cast<int>(pieceStr.size()); ++j) {
	  // で頂点ごとに区切る
	  auto numStr = split(pieceStr[j], ' ');

	  if (i == input.size() - 1 && j == pieceStr.size() - 1) {
		//最後のQRの最後のデータの場合はframePointに格納する
		for (int k = 1; k < static_cast<int>(numStr.size()); k += 2) {
		  Point pointTemp(stoi(numStr[k]), stoi(numStr[k + 1]));
		  framePoint.push_back(pointTemp);
		}
	  }
	  else {
		//角頂点の座標をpieceTemoに数字に変換して格納して、piecePointに追加する
		std::vector<Point> pieceTemp;
		for (int k = 1; k < static_cast<int>(numStr.size()); k += 2) {
		  Point pointTemp(stoi(numStr[k]), stoi(numStr[k + 1]));
		  pieceTemp.push_back(pointTemp);
		}
		piecePoint.push_back(pieceTemp);
	  }

	}
  }

  std::vector<Piece> data;

  for (int i = 0; i < static_cast<int>(piecePoint.size()); i++) {
	data.push_back(piecePoint[i]);
  }

  //------------------------------------------------------
  setColor(F_BLACK, B_WHITE|B_INTENSITY);

  for (int i = 0; i < static_cast<int>(piecePoint.size()); ++i) {
	std::cout << "piece[" << i << "]" << "(頂点数:" << piecePoint[i].size() << "):";
	for (auto j : piecePoint[i]) {
	  std::cout << "(" << j.x << "," << j.y << ") ";
	}
	std::cout << std::endl;
  }


  std::cout << "frame（頂点数:" << framePoint.size() << "):";
  for (auto i : framePoint) {
	std::cout << "(" << i.x << "," << i.y << ") ";
  }
  std::cout << std::endl;

  setColor();
//------------------------------------------------------
  int p = 0;
  for (auto i : data) {
	printf("%dピース\n",p);
	int n = 0;
	for (auto j : i.getPoint()) {
	  printf("	%d回転\n	  ", n);
	  for (auto k : j) {
		printf("(%d,%d) ", k.x, k.y);
	  }
	  printf("\n");
	  n++;
	}
	p++;
  }

  std::vector<putData> already_put;
  solve(data, already_put);



  for (auto i : already_put) {
	printf("%d %d (%d,%d)\n", i.piece_num, i.point_num,i.base_point.x,i.base_point.y);
  }

  FILE *fp;
  fopen_s(&fp,"out.txt","w");
  if (fp != NULL) {
	for (auto i : already_put) {
	  fprintf_s(fp, "%d %d (%d,%d)\n", i.piece_num, i.point_num, i.base_point.x, i.base_point.y);
	}
  }



  getchar();
  getchar();
  //再帰テスト用a
  //std::array<int, NUM> array = { 0,1,2,3 };
  //std::vector<int> vector
  //func(array, vector);

  return 0;
}


int checkHit(std::vector<Piece> &data, std::vector<putData> &already_put, putData &put) {
  std::vector<Point> cp1(data[put.piece_num].getPoint()[put.point_num]);
  //移動
  move(cp1, put.base_point);

  for (int i = 0; i < static_cast<int>(already_put.size()); ++i) {
	std::vector<Point> cp2(data[already_put[i].piece_num].getPoint()[already_put[i].point_num]);
	//移動
	move(cp2, already_put[i].base_point);

	if (collisionPiece(cp1, cp2)) {
	  printf("piece");
	  return 1;
	}
  }

  //これはずらさないとヤバそうなやつ//やっぱりこれはずらさなくてもよいやつ
  if (collisionFrame(framePoint, cp1)) {
	printf("frame");
	return 1;
  }

  return 0;
}


Point getPutPoint(std::vector<Piece> &data, std::vector<putData> &already_put) {
  Point tmp;
  scanf_s("%d %d", &tmp.x, &tmp.y);
  tmp.print();
  printf_s("に設置\n");
  return tmp;
}


int solve(std::vector<Piece> &data, std::vector<putData> &already_put) {
  if (data.size() == already_put.size()) {
	//全部置いたってこと
	return 1;
  }

  //全ピース見ていこうな
  for (int i = 0; i < static_cast<int>(data.size()); ++i) {//ピースの数
														   //今のピースがすでに置かれているかどうか
	if ([=]() {for (int j = 0; j < static_cast<int>(already_put.size()); ++j) { if (already_put[j].piece_num == i) { return 0; } }return 1; }()) {
	  for (int j = 0; j < static_cast<int>(data[i].getPoint().size()); ++j) {//回転の組み合わせの数
		for (int k = 0; k < static_cast<int>(data[i].getPoint()[j].size()); ++k) {//設置頂点

		  printf("今置きたいピース=%d\n", i);
		  Point tmp = getPutPoint(data, already_put);
		  putData put(i, j, k, tmp);
		  if (!checkHit(data, already_put, put)) {
			//もし当たり判定がokなら
			already_put.push_back(put);
			if (solve(data, already_put)) {
			  //もしreturn 1なら解き終わったってこと
			  return 1;
			}
		  }
		  else {
			setColor(F_RED | F_INTENSITY);
			printf_s("Hit!!!!\n");
			setColor();
		  }
		}
	  }
	}
  }

  //ここまで来たってことはダメだったってことだからpopしてバック
  already_put.pop_back();
  return 0;
}
