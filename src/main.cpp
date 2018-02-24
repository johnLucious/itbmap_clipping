#include <applib>

using namespace std;

int main() {
    vector < Renderable * > bangunan = Renderable::parseFile("res/bangunanitb.txt");
    vector < Renderable * > jalan = Renderable::parseFile("res/jalanitb.txt");
}