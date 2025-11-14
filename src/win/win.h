#ifndef __TRHS_WIN_H__
#define __TRHS_WIN_H__

#include <mutex>

#include <u.h>

namespace win {
	I open();
	I main();

	/* win state */
	enum WinT {
		WIN_OPEN = 0,
		WIN_MAIN,
	};

	extern WinT WIN_T;
	extern std::mutex WIN_X;

	sta I (*WIN_FS[])() = {
		[WIN_OPEN]=open,
		[WIN_MAIN]=main,
	};

	inl sta X this_win() -> I {
		I (*f)() = WIN_FS[WIN_T];
		return f();
	}
}

#endif
