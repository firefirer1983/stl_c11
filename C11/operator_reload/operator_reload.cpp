#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <ostream>
#include <array>
#include <stdexcept>
#include <memory>

using namespace std;

class GTest : public ::testing::Test {

protected:
	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

class complex {
public:
	double real;
	double imag;

	complex() : real(0.0), imag(0.0) {}

	complex(double a, double b) : real(a), imag(b) {}

	void display() const { cout << real << " + " << imag << "i" << endl; }

	complex operator+(const complex &y) {
		cout << "In complex c+c" << endl;
		complex tmp;
		tmp.real = real + y.real;
		tmp.imag = imag + y.imag;
		return tmp;
	}

	complex operator+(const float &y) {
		cout << "In complex c+f" << endl;
		complex tmp;
		tmp.real = real + y;
		tmp.imag = imag;
		return tmp;
	}
};

complex operator+(const float &A, const complex &B) { // this is a global operator reload!
	cout << "In global f+c" << endl;

	complex C;
	C.real = A + B.real;
	C.imag = B.imag;
	return C;
}

TEST_F(GTest, WEAK_PTR_GTest) {
	complex c1(4.3, 5.8);
	complex c2(2.4, 3.7);
	complex c3;
	c3 = c1 + c2;
	c3.display();
	complex c4;
	c4 = 4 + c3;
	c4.display();
	complex c5 = c3 + 6;
	c5.display();

}

TEST_F(GTest, NetName_GTest) {
	const char divChar = '-';
	const char *netPostfix = "net";
	const char *usbBin = "ZY-3A200.bin";
	const char *netBin = "ZY-3A200-net.bin";
	char baseName[128];
	char fullName[128];
	memset(baseName, 0, sizeof(baseName));
	memset(fullName, 0, sizeof(fullName));
	strncpy(baseName, usbBin, strlen(usbBin) - strlen(".bin"));

	snprintf(fullName, sizeof(fullName), "%s%c%s.bin", baseName, divChar, netPostfix);
	printf("%s\n", fullName);
	EXPECT_STREQ(string(fullName).c_str(), string(netBin).c_str());
}

TEST_F(GTest, Strstr_GTest) {
	const char divChar = '-';
	const char *netPostfix = "net";
	const char *usbBin = "ZY-3A200.bin";
	const char *netBin = "ZY-3A200-net.bin";
	char baseName[128];
	memset(baseName, 0, sizeof(baseName));

	EXPECT_NE(strstr(netBin, baseName), nullptr);
}


class Vector {
public:
	// 默认构造函数
	Vector(std::initializer_list<double> lst) :
			sz_(lst.size()),
			ary_(new double[lst.size()]) {
		std::copy(lst.begin(), lst.end(), ary_);
		printf("Vector default constructor\n");
	}

	~Vector() {
		printf("Vector destructor\n");
		delete[] ary_;
		sz_ = 0;
	}

	// 拷贝构造函数
	Vector(const Vector &v) :
			sz_(v.sz_),
			ary_(new double[v.sz_]) {
		printf("Vector copy constructor\n");
		std::copy(v.ary_, v.ary_ + sz_, ary_);
	}

	Vector(Vector &&v) {
		printf("Vector move constructor\n");

	}

	// 拷贝赋值运算符
	Vector &operator=(const Vector &v) {
		printf("Vector operator=\n");
		delete[] ary_;
		sz_ = v.sz_;
		ary_ = new double[v.sz_];
		std::copy(v.ary_, v.ary_ + sz_, ary_);
		return *this;
	}

	size_t size() {
		return sz_;
	}

	void show() {
		for (int i = 0; i != static_cast<int>(sz_); i++) {
			printf("%f ", ary_[i]);
		}
		printf("\n");
	}

private:
	double *ary_;
	size_t sz_;
};

template<typename T>
class Vector {
public:
	Vector(const std::initializer_list<T> &lst) :
			sz_(lst.size()),
			ary_(new T[lst.size()]) {
		T *tmp = ary_;
		for (auto &m:lst) {
			*(tmp++) = m;
		}
	}

	Vector(const Vector &v) :
			sz_(v.sz_),
			ary_(new T[v.sz_]) {
		T *tmp = ary_;
		for (const T &m:v) {
			*(tmp++) = m;
		}
	}

	T *begin() {
		return ary_;
	}

	T *end() {
		return (ary_ + sz_);
	}

	~Vector() {
		delete[] ary_;
		sz_ = 0;
	}

private:
	T *ary_;
	size_t sz_;
};

TEST_F(GTest, Vector_GTest) {
	unique_ptr<Vector> pv;
	{
		try {
			Vector v1({0, 1, 2, 3, 4, 5});
			pv.reset(new Vector(v1));
			v1.show();

		} catch (std::bad_alloc) {
			printf("bad alloc\n");
		}
	}
	pv->show();
	Vector Va({10, 9, 8, 7, 6, 5});
	Vector Vb({0, 1, 2, 3, 4, 5});
	(Vb = Va).show();
}

int main(int argc, char *argv[]) {

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}