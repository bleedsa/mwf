#include <M.h>

M::M::~M() {
	if (rows == 0 && cols == 0) return;
	delete ptr[rows*cols];
}
