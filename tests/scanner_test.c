#include "../src/scanner.h"
#include <criterion/criterion.h>
#include <stdio.h>

Test(scanner, should_skip_spaces_and_return_EOF_token)
{
	char *source = "          ";
	init_scanner(source);
	Token result = scan_token();

	cr_assert(result.type == TOKEN_EOF);
}
