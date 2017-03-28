/* 
 * TODO: put your own comments here. Also you should leave comments on
 * each of your methods.
 */

#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
using namespace std;

double getHeight(double a, double b);
void drawSerpinskiiTriangles(GWindow &w, double leftX, double leftY, double size, int order);
void drawTriangle(GWindow &w, double leftX, double leftY, double size);


int gcd(int a, int b) {
    if(a%b == 0){
        cout << "gcd(" << a << ", " << b << ") = " << b << endl;
        return b;
    }else{
        cout << "gcd(" << a << ", " << b << ") = gcd(" << b << ", " << a % b << ")" << endl;
        return gcd(b, a%b);
    }
}


void serpinskii(GWindow &w, int leftX, int leftY, int size, int order) {
    double mleftX = leftX;
    double mleftY = leftY;
    double mSize = size;
    drawSerpinskiiTriangles(w, mleftX, mleftY, mSize, order);
}

double getHeight(double c, double a) {
    return sqrt(c * c - a * a);
}

void drawTriangle(GWindow &w, double leftX, double leftY, double size) {
    double height = getHeight(size, size / 2);
    double rightX = leftX + size;
    double bottomY = leftY + height;
    double bottomX = leftX + size/2;
    w.drawLine(leftX, leftY, rightX, leftY); // draw top side
    w.drawLine(leftX, leftY, bottomX, bottomY); // draw left side
    w.drawLine(rightX, leftY, bottomX, bottomY); // draw right side
}

void drawSerpinskiiTriangles(GWindow &w, double leftX, double leftY, double size, double order)
{
    if(order == 0){
        drawTriangle(w, leftX, leftY, size);
    }else{
        order--;
        double halfSize = size/2;
        double height = getHeight(halfSize, halfSize/2);
        drawSerpinskiiTriangles(w, leftX, leftY, size, order);
        drawSerpinskiiTriangles(w, leftX + halfSize, leftY, halfSize, order);
        drawSerpinskiiTriangles(w, leftX + halfSize/2, leftY + height, halfSize, order);
    }
}

int floodFill(GBufferedImage& image, int x, int y, int newColor) {
    // your code here
    cout << "[recursion flood fill called]" << endl;
    return 0;
}

void personalCurriculum(Map<string, Vector<string>> & prereqMap,string goal) {
    // your code here
    cout << "[recursion personal curriculum called]" << endl;
}

string generate(Map<string, Vector<string> > & grammar, string symbol) {
    // your code here
    cout << "[recursion generate called]" << endl;
    return "";
}
