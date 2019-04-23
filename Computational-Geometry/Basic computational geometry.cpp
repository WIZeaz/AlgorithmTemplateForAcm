const double PI=acos(-1.0);
const double eps=1e-8;

inline int sgn(double x) {
	if(fabs(x)<eps)return 0;
	if(x<0)return -1;
	return 1;
}

struct Point {
	double x,y;
	Point() {};
	Point(double _x,double _y):x(_x),y(_y) {};
	Point operator + (const Point &a)const {
		return Point(x+a.x,y+a.y);
	}
	Point operator - (const Point &a)const {
		return Point(x-a.x,y-a.y);
	}
	double operator * (const Point &a)const {
		return x*a.x+y*a.y;
	}
	double operator ^ (const Point &a)const {
		return x*a.y-y*a.x;
	}
};

struct Line {
	Point s,e;
	Line() {};
	Line(Point _s,Point _e) {
		s=_s,e=_e;
	}
	// 两直线相交  0代表重合 1代表平行 2代表相交
	pair<int,Point> operator & (const Line &a)const {
		Point res=s;
		if(sgn((s-e)^(a.s-a.e))==0) {
			if(sgn((s-a.e)^(a.s-a.e))==0)return make_pair(0,res);
			return make_pair(1,res);
		}
		double t=((s-a.s)^(a.s-a.e))/((s-e)^(a.s-a.e));
		res.x+=(e.x-s.x)*t;
		res.y+=(e.y-s.y)*t;
		return make_pair(2,res);
	}
	// 两线段相交 0代表不相交 1代表相交(不穿过) 2代表相交(穿过)
	pair<int,Point> operator ^ (const Line &a)const {
		Point res=s;
		double cmp1=sgn((a.s-s)^(a.e-s))*sgn((a.s-e)^(a.e-e)),cmp2=sgn((s-a.s)^(e-a.s))*sgn((s-a.e)^(e-a.e));
		if(cmp1==1||cmp2==1)return make_pair(0,res);

		double t=((s-a.s)^(a.s-a.e))/((s-e)^(a.s-a.e));
		res.x+=(e.x-s.x)*t;
		res.y+=(e.y-s.y)*t;
		if(cmp1+cmp2==-2)return make_pair(2,res);
		else return make_pair(1,res);
	}
} ;

double dist(Point a,Point b) {
	return sqrt((a-b)*(a-b));
}
