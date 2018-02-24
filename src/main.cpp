#include <applib>

using namespace std;

int main() {
	// vector<Renderable * > bangunan;
	// vector<Renderable * > jalan;
	vector<Renderable * > bangunan = Renderable::parseFile("res/bangunanitb.txt", 1,20,20,255);
    vector<Renderable * > jalan = Renderable::parseFile("res/jalan2.txt", 1.37, 20,20,20);
  jalan.insert(jalan.end(),bangunan.begin(), bangunan.end());

    Canvas* canvas = new Canvas(jalan);
    ViewportDriver vDriver(0,0,canvas);
}