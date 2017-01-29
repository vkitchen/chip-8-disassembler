#include "unity.h"
#include "string2.h"

void test_string_append(void)
	{
	struct string *s = string_new_c("cat");
	string_append_c(s, "dog");
	TEST_ASSERT_EQUAL_STRING(s->str, "catdog");
	}

int main(void)
	{
	UNITY_BEGIN();
	RUN_TEST(test_string_append);
	return UNITY_END();
	}
