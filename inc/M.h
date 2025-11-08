#ifndef __MWF_M_H__
#define __MWF_M_H__

#include <u.h>

namespace M {
	template<typename T>
	struct M {
		S rows;
		S cols;
		T *ptr;

		inl M() : rows{0}, cols{0}, ptr{nullptr} {}
		inl M(S c, S r) : rows{r}, cols{c}, ptr{new T[r*c]} {}
		~M();

		inl X at(S x, S y) -> T* {
			return &ptr[x + cols * y];
		}
	};
}

#endif
