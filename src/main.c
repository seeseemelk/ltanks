#include "utils.h"

#include <stdio.h>

static const char prog[] = "local function main() print(\"Hello\") end main()";

int main(int argc, char** argv)
{
	UNUSED(argc);
	UNUSED(argv);
	printf("Hello, world!\n");
}
