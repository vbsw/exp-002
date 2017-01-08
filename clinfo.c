
//          Copyright 2017 Vitali Baumtrok
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE or copy at
//        http://www.boost.org/LICENSE_1_0.txt)


#include <stdio.h>
#include <string.h>

extern const char *const version_string;

#define STATE_NO_ARGUMENTS 0
#define STATE_HELP 1
#define STATE_COPYRIGHT 2
#define STATE_VERSION 3
#define STATE_UNKNOWN_ARGUMENT 4
#define STATE_TOO_MANY_ARGUMENTS 5

static int clinfo_state = STATE_NO_ARGUMENTS;
static char* clinfo_unknown_argument = 0;

static void clinfo_print_help_hint() {
	printf("Use --help for description on valid aguments.");
}

static void clinfo_print_no_arguments() {
	printf("No arguments available!\n");
}

static void clinfo_print_help() {
	printf("Usage:\n");
	printf("   exp002                Starts application.\n");
	printf("   exp002 --help         Prints this help.\n");
	printf("   exp002 --copyright    Prints copyright and copying conditions.\n");
	printf("   exp002 --version      Prints version.\n");
}

static void clinfo_print_copyright() {
	printf("Copyright 2017 Vitali Baumtrok (vbsw@mailbox.org)\n");
	printf("Distributed under the Boost Software License, Version 1.0.\n");
	printf("(See accompanying file LICENSE or copy at\n");
	printf("http://www.boost.org/LICENSE_1_0.txt)\n");
}

static void clinfo_print_version() {
	printf("%s\n",version_string);
}

static void clinfo_print_unknown_argument() {
	if (clinfo_unknown_argument) {
		printf("Unknown argument: %s\n",clinfo_unknown_argument);
	} else {
		printf("Unknown argument: ???\n");
	}
}

static void clinfo_print_too_many_arguments() {
	printf("too many arguments\n");
}

static int clinfo_is_help(const char *const arg) {
	return    !strcmp(arg,"help")
	       || !strcmp(arg,"-help")
	       || !strcmp(arg,"--help")
	       || !strcmp(arg,"-h");
}

static int clinfo_is_copyright(const char *const arg) {
	return    !strcmp(arg,"copyright")
	       || !strcmp(arg,"-copyright")
	       || !strcmp(arg,"--copyright")
	       || !strcmp(arg,"-c");
}

static int clinfo_is_version(const char *const arg) {
	return    !strcmp(arg,"version")
	       || !strcmp(arg,"-version")
	       || !strcmp(arg,"--version")
	       || !strcmp(arg,"-v");
}

static int clinfo_parse_argument(const char *const arg) {
	if (clinfo_is_help(arg)) {
		return STATE_HELP;

	} else if (clinfo_is_copyright(arg)) {
		return STATE_COPYRIGHT;

	} else if (clinfo_is_version(arg)) {
		return STATE_VERSION;

	} else {
		return STATE_UNKNOWN_ARGUMENT;
	}
}

/* ---------------------------- */
/*      exported functions      */
/* ---------------------------- */

void clinfo_parse(int argc, char **argv) {
	clinfo_unknown_argument = 0;

	if (argc <= 1) {
		clinfo_state = STATE_NO_ARGUMENTS;

	} else if (argc == 2) {
		clinfo_state = clinfo_parse_argument(argv[1]);

		if (clinfo_state == STATE_UNKNOWN_ARGUMENT) {
			clinfo_unknown_argument = argv[1];
		}

	} else {
		clinfo_state = STATE_TOO_MANY_ARGUMENTS;
		clinfo_unknown_argument = 0;
	}
}

int clinfo_is_application() {
	return clinfo_state == STATE_NO_ARGUMENTS;
}

void clinfo_print() {
	switch (clinfo_state) {
		case STATE_NO_ARGUMENTS:
			clinfo_print_no_arguments();
			break;
		case STATE_HELP:
			clinfo_print_help();
			break;
		case STATE_COPYRIGHT:
			clinfo_print_copyright();
			break;
		case STATE_VERSION:
			clinfo_print_version();
			break;
		case STATE_UNKNOWN_ARGUMENT:
			clinfo_print_unknown_argument();
			clinfo_print_help_hint();
			break;
		case STATE_TOO_MANY_ARGUMENTS:
			clinfo_print_too_many_arguments();
			clinfo_print_help_hint();
			break;
	}
}
