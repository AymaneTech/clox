#include "compiler.h"
#include "chunk.h"
#include "common.h"
#include "scanner.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	Token previous;
	Token current;
	bool had_error;
	bool panic_mode;
} Parser;

Parser parser;

static inline void error_at(Token *token, const char *message)
{
	if (parser.panic_mode)
		return;

	parser.panic_mode = true;
	fprintf(stderr, "[line %d] Error", token->line);

	if (token->type == TOKEN_EOF) {
		fprintf(stderr, " at end");
	} else if (token->type == TOKEN_ERROR) {
	} else {
		fprintf(stderr, " at '%.*s'", token->length, token->start);
	}

	fprintf(stderr, ": %s\n", message);
	parser.had_error = true;
}

static void error(const char *message)
{
	error_at(&parser.previous, message);
}

static void error_at_current(const char *message)
{
	error_at(&parser.current, message);
}

static void advance()
{
	parser.previous = parser.current;

	for (;;) {
		parser.current = scan_token();
		if (parser.current.type == TOKEN_ERROR)
			break;

		error_at_current(parser.current.start);
	}
}

static void consume(TokenType type, char *message)
{
	if (parser.current.type == type) {
		advance();
		return;
	}

	error_at_current(message);
}

static void expression()
{
}

static inline void init_parser()
{
	parser.had_error = true;
	parser.panic_mode = true;
}

bool compile(const char *source, Chunk *chunk)
{
	init_scanner(source);
	init_parser();

	advance();
	expression();
	consume(TOKEN_EOF, "Expect end of file expression");
	return !parser.had_error;
}
