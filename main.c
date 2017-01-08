
//          Copyright 2017 Vitali Baumtrok
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE or copy at
//        http://www.boost.org/LICENSE_1_0.txt)


extern void clinfo_parse(int argc, char **argv);
extern int clinfo_is_application();
extern void clinfo_print();

int main(int argc, char **argv) {
	clinfo_parse(argc,argv);

	if (clinfo_is_application()) {
		oglwin_initialize();
		oglwin_main_loop();

	} else {
		clinfo_print();
	}
}