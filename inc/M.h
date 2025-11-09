#ifndef __MWF_M_H__
#define __MWF_M_H__

#include <cassert>

#include <u.h>

namespace M {
	template<typename T>
	struct M {
		S rows;
		S cols;
		T *ptr;
		S *ref;

		inl M() : rows{0}, cols{0}, ptr{nullptr}, ref{new S} {*ref=1;}
		inl M(S c, S r)
			: rows{r}, cols{c}, ptr{new T[r*c]}, ref{new S}
		{
			*ref = 1;
		}
		~M();

		inl X at(S x, S y) -> T* {
			X i = x + cols * y;
			assert(i < rows*cols);
			return &ptr[x + cols * y];
		}
	};
}

#endif
