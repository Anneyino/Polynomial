#include <iostream>
using namespace std;

class PolynomialTerm{
public:
	int p;//该项的系数
	int n;//该项的指数
	char x;//该项的主元
	char sign;//判断该项的符号正负
	PolynomialTerm() {
		p = 0;
		n = 0;
		x = '\0';
		sign = '\0';
	}
};

class Polynomial {
private:
	int termNumber;//多项式的项数
	PolynomialTerm* termArray;//用来表示多项式的数组
public:
	Polynomial();
	Polynomial(const Polynomial & poly);
	~Polynomial();
	void addTerm(int p,int n,char x,char sign);//加入新项
	void setOrder();//多项式项的顺序设定
	void inputPoly();//输入多项式
	void outputPoly();//输出多项式
	Polynomial operator*(Polynomial & poly);//多项式乘法
	Polynomial & operator=(Polynomial & poly);//多项式赋值
};

Polynomial::Polynomial()
{
	this->termNumber = 0;
	if(this->termNumber >0)
	termArray = new PolynomialTerm[this->termNumber];
}
Polynomial::Polynomial(const Polynomial & poly) {
	this->termNumber = poly.termNumber;
	termArray = new PolynomialTerm[this->termNumber];
	for (int k = 0; k < poly.termNumber; k++) {
		this->addTerm(poly.termArray[k].p, poly.termArray[k].n, poly.termArray[k].x,poly.termArray[k].sign);
	}
}

Polynomial::~Polynomial() {
	delete[] this->termArray;
}
void Polynomial::addTerm(int p, int n, char x,char sign){
	termNumber += 1;
	PolynomialTerm* tmp = new PolynomialTerm[termNumber];
	for (int i = 0; i < termNumber - 1; i++) {
		tmp[i] = termArray[i];
	}
	delete[] termArray;
	
	termArray = tmp;
	PolynomialTerm newTerm;
	newTerm.p = p;
	newTerm.n = n;
	newTerm.x = x;
	newTerm.sign = sign;
	termArray[termNumber-1] = newTerm;
	this->setOrder();
}
void Polynomial::setOrder() {
	
	for (int i = 0; i <termNumber; i++) {
		for (int j = i + 1; j < termNumber; j++) {
			if (termArray[i].n < termArray[j].n) {
				PolynomialTerm tmp = termArray[i];
				termArray[i] = termArray[j];
				termArray[j] = tmp;
			}
			else if (termArray[i].n == termArray[j].n) {
				if (termArray[i].sign == termArray[j].sign) {
					termArray[i].p += termArray[j].p;
					for (int k = i; k < termNumber - 1; k++) {
						termArray[k] = termArray[k + 1];
					}
					termNumber--;
				}
				else {
					if (termArray[i].p > termArray[j].p) {
						termArray[i].p -= termArray[j].p;
						for (int k = i; k < termNumber - 1; k++) {

							termArray[k] = termArray[k + 1];
						}
						termNumber--;
					}
					else {
						termArray[i].p = termArray[j].p - termArray[i].p;
						termArray[i].sign = termArray[j].sign;
						for (int k = i; k < termNumber - 1; k++) {
							termArray[k] = termArray[k + 1];
						}
						termNumber--;
					}
				}
			}
		}
	}
}

void Polynomial::inputPoly() {
	
	this->termNumber = 0;
	cout << "Please enter the coefficient, variable name and power in the right order and finally enter an '#' to stop input..." << endl;
	cout << "For example '+ 3 x 2 + 4 x 3 + 1 #'" << endl;
	int p;
	int n;
	char x;
	char sign;

	do {
		

		cin >> sign;
		if (sign == '#') {
			break;
		}
		loop:
		cin >> p >> x;
			if (x == '#') {
				this->addTerm(p, 0, '\0', sign);
				break;
			}
			else if (x == '+' || x == '-') {
				this->addTerm(p, 0, '\0', sign);
				goto loop;
			}
			cin >> n;
			this->addTerm(p, n, x,sign);
	} while (true);
}

void Polynomial::outputPoly(){
	cout << "The polynomial you get is:" << endl;
	for (int i = 0; i <termNumber; i++) {
		if (this->termArray[i].p != 0) {
			if (this->termArray[i].n != 0) {
				if (i == 0) {
					cout << this->termArray[i].p << this->termArray[i].x << "^" << this->termArray[i].n;
				}
				else {
					cout << this->termArray[i].sign << this->termArray[i].p << this->termArray[i].x << "^" << this->termArray[i].n;
				}
			}
			else {
				cout << this->termArray[i].sign << this->termArray[i].p;
			}
		}
	}
	cout << " " << endl;
}

Polynomial Polynomial::operator*( Polynomial & poly) {
	Polynomial res;
	res.termNumber = 0;
	for (int i = 0; i < termNumber; i++) {
		for (int j = 0; j < poly.termNumber; j++) {
			char x = 'x';


			char sign;
			if ((termArray[i].x != poly.termArray[i].x) && (termArray[i].x != '\0') && (poly.termArray[i].x != '\0')) {
				cout << "Please enter the the same name of unknown..." << endl;
			}
			int p = termArray[i].p * poly.termArray[j].p;
			int n = termArray[i].n + poly.termArray[j].n;
			/*if (n != 0) {
				x = 'x';
			}
			else {
				x = '\0';
			}*/
			if (termArray[i].sign == poly.termArray[j].sign) {
				sign = '+';
			}
			else {
				sign = '-';
			}
			res.addTerm(p, n, x, sign);
		}

	}
		return res;
	
}

	



Polynomial & Polynomial::operator=(Polynomial & poly){

	this->termNumber = poly.termNumber;
	this->termArray = new PolynomialTerm[this->termNumber];
	for (int i = 0; i < termNumber; i++) {
		this->termArray[i] = poly.termArray[i];
	}
	this->setOrder();
	return *this;
}