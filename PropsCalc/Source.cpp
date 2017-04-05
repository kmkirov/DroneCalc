#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class c
{
public:

	c() { cout << " c constr" << endl; }

	~c() { cout << " c destr" << endl; }
};

class A 
{
public:
	c cc;
	std::string a;
	A(int p=5) { cout << " A constr" << endl; }

	~A() { cout << " A destr" << endl; }
};

class B : public A
{
public:
	B(int c) { cout << "B constr" << endl; }
	~B() { cout << "B destr" << endl; }
};

int main() 
{
	/*vector<A> a1;
	a1.reserve(10);
	A* a = new B(2);
	delete a;*/

	std::unique_ptr<c[]> p(new c[10]);
	

}



//// design of drone calc

class CMRMotor;
class CMRPropeller;


class CInfoReaderImpl 
{
public:
	virtual CMRMotor     getMotorDetails() = 0;
	virtual CMRPropeller getPopellerDetails() = 0;
};

class CDBInfoReaderImpl : public CInfoReaderImpl
{
	CMRMotor     getMotorDetails();
	CMRPropeller getPopellerDetails();
};





class CDroneCalcAlgorithmeImpl 
{
public:
	CMRMotor getBestMotor();
	CMRPropeller getBestPropeller();
	
private:



	CMRMotor m_bestMotor;
	CMRPropeller m_bestPropeller;
};

