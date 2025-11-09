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
		~M() {
			*ref -= 1;
			if (rows != 0 && cols != 0 && !(*ref > 0)) {
				delete[] ptr;
				delete ref;
			}
		}

		/* boilerplate rc stuff */
		inl M(con M &x)
			: rows{x.rows}, cols{x.cols}, ptr{x.ptr}, ref{x.ref}
		{
			*ref += 1;
		}
		inl M(con M &&x)
			: rows{x.rows}, cols{x.cols}, ptr{x.ptr}, ref{x.ref}
		{
			*ref += 1;
		}
		inl X operator=(con M &x) -> con M& {
			rows = x.rows, cols = x.cols, ptr = x.ptr, ref = x.ref;
			*ref += 1;
		}

		inl X at(S x, S y) -> T* {
			X i = x + cols * y;
			assert(i < rows*cols);
			return &ptr[x + cols * y];
		}
	};
}

#endif
