#ifndef __MWF_SYN_H__
#define __MWF_SYN_H__

#include <future>

#include <u.h>

namespace syn {
	template<typename F=V, typename... Ts>
	inl X launch(X... args) -> std::future<F> {
		return std::async(std::launch::async, args...);
	}
}

#endif
