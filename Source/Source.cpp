// Source.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "../DualNumber/dual_number.hpp"
#include <iostream>

int main()
{
	const double elemx = 1.0;
	const double elemy = 2.0;

	DualNumber<2> x(elemx, 0);
	DualNumber<2> y(elemy, 1);
	DualNumber<2> z = DualNumber<2>(2.0) * x * x + DualNumber<2>(3.0) * y * y;

	std::cout << "partial x at x = 1.0:" << z.getFprime()[0] << std::endl;
	std::cout << "partial y at y = 2.0:" << z.getFprime()[1] << std::endl;

	return 0;
}