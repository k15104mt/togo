#include"utility.hpp"

putData::putData(int piece_num, int point_num, int vertex_num, Point &base_point) :
  piece_num(piece_num), point_num(point_num), vertex_num(vertex_num), base_point(base_point) {}


//���σB�I�I
int dot(Vector &a,Vector &b){
  return a.x * b.x + a.y * b.y;
}

//�O�σB�I�I
int cross(Vector &a,Vector &b){
  return a.x * b.y - a.y * b.x;
}

//��̐����̎n�_�A�I�_����A�������m���������Ă��邩��Ԃ�
//���������s�ȏꍇ�͌������Ă��Ȃ����̂ƂȂ�
int cl(Point &Line1Start,Point &Line1End,
              Point &Line2Start,Point &Line2End){
    
  if((((Line1Start.x-Line1End.x)*(Line2Start.y-Line1Start.y)+
  (Line1Start.y-Line1End.y)*(Line1Start.x-Line2Start.x))*
		((Line1Start.x-Line1End.x)*(Line2End.y-Line1Start.y)+
    (Line1Start.y-Line1End.y)*(Line1Start.x-Line2End.x))<0) &&
		(((Line2Start.x-Line2End.x)*(Line1Start.y-Line2Start.y)+
    (Line2Start.y-Line2End.y)*(Line2Start.x-Line1Start.x))*
		((Line2Start.x-Line2End.x)*(Line1End.y-Line2Start.y)+
    (Line2Start.y-Line2End.y)*(Line2Start.x-Line1End.x))<0)){
			return 1;
		}
    
	return 0;
}

int crossLine(std::vector<Point> &data1,std::vector<Point> &data2){
  for(int i=0;i<static_cast<int>(data1.size());++i){
   for(int j=0;j<static_cast<int>(data2.size());++j){
      if(cl(data1[i],data1[(i+1)%static_cast<int>(data1.size())],
                   data2[j],data2[(j+1)%static_cast<int>(data2.size())])){
        return 1;
      }
    }
  }
	return 0;
}

//data1��data�Q�̒��_�����ׂē����Ă�
int inPolygon(std::vector<Point> &data1,std::vector<Point> &data2){
  //data2��i�Ԗڂ̓_��data1�̃|���S�����ɂ��邩�ǂ���
  for(int i=0;i<static_cast<int>(data2.size());++i){
    double x = 0.0;
	int flag=1;
    for(int j=0;j<static_cast<int>(data1.size());++j){
      Vector a = data1[(j+1)%data1.size()]-data2[i];
      Vector b = data1[j]-data2[i];

	  if (data1[j].x == data2[i].x && data1[j].y == data2[i].y) {
		flag = 0;
		break;
	  }
      
      if(dot(a,b) <= 0 && cross(a,b) == 0){
		flag = 0;
        break;
      }


      //�p�x��ϋɓI�ɑ����Ă�����
      if(cross(a,b)<0) x+=(acos((double)(dot(a,b))/(a.size()*b.size()))*180.0/acos(-1.0));
  	  if(cross(a,b)>0) x+=-1.0*(acos((double)(dot(a,b))/(a.size()*b.size()))*180.0/acos(-1.0));	
    }
    
    //�V��ɂ��Ȃ��A360����Ȃ��Ƃ��͂������ƏI��点��
    //���������덷���l�����銴���ɂ����ق�������
    if(flag && x!=360){
	  return 0;
    }
  }
  
  return 1;
}


int collisionPiece(std::vector<Point> &data1,std::vector<Point> &data2){
  //������ł�������Ă����瓖�����Ă���i����͂����j
  if(crossLine(data1,data2)){
    return 1;
  }
  
  if(inPolygon(data1,data2) || inPolygon(data2,data1)){
    return 1;
  }

  for (int i = 0; i<static_cast<int>(data2.size()); ++i) {
	for (int j = 0; j<static_cast<int>(data1.size()); ++j) {
	  Vector a = data1[(j + 1) % data1.size()] - data2[i];
	  Vector b = data1[j] - data2[i];
	  Vector c = data1[(j + 1) % data1.size()] - data1[j];
	  Vector d = data2[(i + 1) % data2.size()] - data2[i];
	  //�O�ς����s�ȂƂ����x�N�g�������s
	  if (cross(c, d) == 0) {
		//�ǂ��炩�̒��_���݂̂��Е��̕ӂ̒��ɑ��݂��Ă���Ȃ�Hit!!
		Vector e = data1[(j + 1) % data1.size()] - data2[(i + 1) % data2.size()];
		Vector f = data1[j] - data2[(i + 1) % data2.size()];

		if ((dot(a, b) < 0 && dot(e, f) > 0) || (dot(a, b) > 0 && dot(e, f) < 0)) {
		  return 1;
		}

	  }
	}
  }

  return 0;  
}

int collisionFrame(std::vector<Point> &data1,std::vector<Point> &data2){
  if(crossLine(data1,data2)){
    return 1;
  }
  
  if(!inPolygon(data1,data2)){
    return 1;
  }
  
  return 0;  
}

