#include <stdio.h>
#include <stdlib.h>
#include <extopts/extopts.h>
#include <extopts/extmods.h>

#include "common.h"


int opts_help;

struct extopt tobin_opts[] = {
/*
  Options TODO:
  -o TYPE, --out TYPE - output value datatype
  -d, --diff          - show xor-difference between two first expression results
 */
	EXTOPTS_HELP(&opts_help),
	EXTOPTS_END
};

void tobin_help(void)
{
	extmod_print_desc(extmod);
	printf("Options:\n");
	extmod_print_opts(extmod);
}

int eval(char *exp)
{
	return strtol(exp, NULL, 0);
}

void print_output(int val)
{
	printf("31     24  23     16\n"
		   "%d%d%d%d %d%d%d%d  %d%d%d%d %d%d%d%d\n"
		   "15      8  7       0\n"
		   "%d%d%d%d %d%d%d%d  %d%d%d%d %d%d%d%d\n",
		   (val >> 31) & 0x1,
		   (val >> 30) & 0x1,
		   (val >> 29) & 0x1,
		   (val >> 28) & 0x1,
		   (val >> 27) & 0x1,
		   (val >> 26) & 0x1,
		   (val >> 25) & 0x1,
		   (val >> 24) & 0x1,
		   (val >> 23) & 0x1,
		   (val >> 22) & 0x1,
		   (val >> 21) & 0x1,
		   (val >> 20) & 0x1,
		   (val >> 19) & 0x1,
		   (val >> 18) & 0x1,
		   (val >> 17) & 0x1,
		   (val >> 16) & 0x1,
		   (val >> 15) & 0x1,
		   (val >> 14) & 0x1,
		   (val >> 13) & 0x1,
		   (val >> 12) & 0x1,
		   (val >> 11) & 0x1,
		   (val >> 10) & 0x1,
		   (val >> 9) & 0x1,
		   (val >> 8) & 0x1,
		   (val >> 7) & 0x1,
		   (val >> 6) & 0x1,
		   (val >> 5) & 0x1,
		   (val >> 4) & 0x1,
		   (val >> 3) & 0x1,
		   (val >> 2) & 0x1,
		   (val >> 1) & 0x1,
		   val & 0x1);
}

int tobin_main(int argc, char *argv[])
{
	int ret = 0;
	int result;
	int i;

	ret = extopts_get(&argc, argv, tobin_opts);
	if (opts_help) {
		tobin_help();
		goto end;
	}

	for (i = 0; i < argc; i++) {
		result = eval(argv[i]);
		if (i > 0)
			printf("\n");
		print_output(result);
	}

end:
	return ret;
}

EXTMOD_DECL(tobin, tobin_main, tobin_opts,
			"Binary calculator",
			"Usage: embox-tobin [OPTION]... EXPRESSION\n"
			"This utility implements basic binary calculator functions with central ability\n"
			"to output result of expression in readable binary form.\n"
			"\n"
			"Options:\n"
			"[[OPTIONS]]\n"
			"It works only with integer data types.\n"
			"Supported operators: +, -, /, %, <<, >>, (, )\n"
			"Supported types:\n"
			"  s8  - signed   8-bit\n"
			"  u8  - unsigned 8-bit\n"
			"  s16 - signed   16-bit\n"
			"  u16 - unsigned 16-bit\n"
			"  s32 - signed   32-bit\n"
			"  u32 - unsigned 32-bit\n"
			"  s64 - signed   64-bit\n"
			"  u64 - unsigned 64-bit\n"
			"Data type for each used value can be specified in () right before the value\n"
			"itself.\n"
			"\n"
			"Examples:\n"
			"$ embox-tobin 0xee488f120\n"
			"$ embox-tobin \"4 + 8 << (2 - 1)\"\n"
			"$ embox-tobin (s16)0x52ea \"(s32)((u16)0x18 << 5) + 0x8937ffee\"")
