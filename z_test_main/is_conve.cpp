#include <iostream>
using namespace std;

class Distance {
	private:
	int kilometer, meter;

	public:
	Distance()
	  : kilometer(0)
	  , meter(0) {}
	explicit Distance(int newDist) {
		kilometer = newDist / 1000;
		meter	  = newDist % 1000;
	}
		 operator int() { return kilometer * 1000 + meter; }
	void PrintDistance() { cout << "Distance is " << kilometer << "km " << meter << "m\n"; }
};

// int
// main() {
// 	Distance d(2030);
// 	int		 nDist = d;
// 	cout << "Value is " << nDist << endl;

// 	return 0;
// }

void
DistanceFunc(int nDist) {
	cout << "Value is " << nDist << endl;
}

int
main() {
	Distance d(2030);
	DistanceFunc(d);

	return 0;
}
