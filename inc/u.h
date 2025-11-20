#ifndef __PLUG_U_H__
#define __PLUG_U_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <mutex>
#include <format>
#include <iostream>

#define Z(x)(sizeof(x))
#define mv(x...)(std::move(x))
#define MMV(x,y,z)(memmove(x,y,z))
#define streq(x,y)(0==strcmp((x),(y)))
#define CASE(f,x...)case f: {x;break;}
#define X_G(x)(std::lock_guard<std::mutex>(x))

#define fatal(f...){ \
	std::string _x=std::format("\x1b[31m[FATAL]\x1b[0m " f); \
	std::cout<<_x<<std::endl; \
	exit(-1); \
}
#define log_(f...){ \
	std::string _x=std::format("\x1b[36m[LOG]\x1b[0m " f); \
	std::cout<<_x<<std::endl; \
}
#define elog(f...){ \
	std::string _x=std::format("\x1b[31m[ERR]\x1b[0m " f); \
	std::cout<<_x<<std::endl; \
}

/* llvm */
using u8=uint8_t;
using u16=uint16_t;
using u32=uint32_t;
using u64=uint64_t;
using i16=int16_t;
using i32=int32_t;
using i64=int64_t;
using f64=double;

/* k */
#define inl [[clang::always_inline]]
#define sta static
#define con const
#define X auto
using V=void;
using I=i32;
using F=float;
using C=char;
using CC=const char;
using S=size_t;

namespace U {
	bool init(CC *n);
	bool init();
}

#endif
