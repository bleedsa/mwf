#ifndef __MWF_M_H__
#define __MWF_M_H__

#include <cassert>
#include <msgpack.hpp>

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

		inl X pack(msgpack::sbuffer buf) -> V {
			X p = msgpack::packer<msgpack::sbuffer>(&buf);
			p.pack(rows);
			p.pack(cols);
			for (S i = 0; i < rows*cols; i++) {
				p.pack(ptr[i]);
			}
		}
	};

	template<typename T>
	inl X unpack(msgpack::sbuffer buf) -> M<T> {
		msgpack::unpacker un;

		/* feed the buffer */
		un.reserve_buffer(buf.size());
		memcpy(un.buffer(), buf.data(), buf.size());
		un.buffer_consumed(buf.size());

		/* stream deserialize */
		msgpack::object_handle rows, cols;
		un.next(rows);
		un.next(cols);
		S r, c;
		rows.get().convert(r), cols.get().convert(c);

		X ret = M<T>(c, r);
		msgpack::object_handle obj;
		for (S i = 0; i < r*c; i++) {
			un.next(obj);
			obj.get().convert(ret.at(i));
		}

		return ret;
	}
}

#endif
