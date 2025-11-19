#include <fs.h>

X fs::png_files(std::string d) -> std::vector<std::string> {
	X r = std::vector<std::string>();
	for (X &i : std::fs::directory_iterator(d)) {
		X p = i.path(); /* path */
		if (p.extension() == std::fs::path(".cpp")) r.push_back(p);
	}
	return r;
}

X fs::bmp_files(std::string d) -> std::vector<std::string> {
	X r = std::vector<std::string>();
	for (X &i : std::fs::directory_iterator(d)) {
		X p = i.path();
		if (p.extension() == std::fs::path(".bmp")) {
			r.push_back(p);
			log_("loaded \x1b[35m{}\x1b[0m", p.c_str());
		}
	}
	return r;
}
