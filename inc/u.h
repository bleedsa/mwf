#ifndef __PLUG_U_H__
#define __PLUG_U_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define Z(x)(sizeof(x))
#define mv(x...)(std::move(x))
#define MMV(x,y,z)(memmove(x,y,z))
#define streq(x,y)(0==strcmp((x),(y)))
#define fatal(f...){fprintf(stderr,"[FATAL] " f);putc('\n',stdout);exit(-1);}
#define log_(f...){printf("[LOG] " f);putc('\n',stdout);}

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
	I init(CC *n);
	I init();
}

#endif
