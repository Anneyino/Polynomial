#include "stdafx.h"
#include "Polynomial.h"
using namespace std;
int main()
{   
	int a;
	Polynomial ah;
	Polynomial bh;
	Polynomial ch;
	ah.inputPoly();//input polynomial a
	ah.outputPoly();
	bh.inputPoly();
	bh.outputPoly();
	ch = ah*bh;
	ch.outputPoly();//output the result
	cin >> a;
	return 0;
}
/**
+ 12 x 5 + 3 x 2 + 2 #
+ 3 x 2 + 2 x 6 #
**/