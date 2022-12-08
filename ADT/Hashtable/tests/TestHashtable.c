#include "../src/hashtable/hashtable.h"
#include "../external/unity/src/unity.h"

static size_t CAPACITY = 5;
static htbl_T tbl;

void setUp(void)
{
    tbl = htbl_new(CAPACITY);
}

void tearDown(void)
{
    htbl_free(&tbl);
}

void test_htbl_create(void)
{
    TEST_ASSERT_NULL(htbl_new(0)); // Cannot create a zero capacity table
}

void test_htbl_free(void)
{
    htbl_T temp = htbl_new(10);
    TEST_ASSERT_NOT_NULL(temp);

    htbl_free(&temp);
    TEST_ASSERT_NULL(temp);
}

/*
 * There's something tickling the back of my head thats saying duplicating the
 * tests across key types isn't a good testing strategy. 
 */
void test_htbl_put_and_remove(void)
{
    char *key = "test_key";
    char *value = "test_value";
 
    TEST_ASSERT_EQUAL(1, htbl_put(tbl, key, value));
    TEST_ASSERT_EQUAL_STRING(value, htbl_remove(tbl, key));
    TEST_ASSERT_NULL(htbl_find(tbl, key));
}

void test_htbl_put_update(void)
{
    TEST_ASSERT_EQUAL(1, htbl_put(tbl, "KEY1", "original"));
    TEST_ASSERT_EQUAL_STRING("original", htbl_find(tbl, "KEY1"));

    TEST_ASSERT_EQUAL(0, htbl_put(tbl, "KEY1", "updated"));
    TEST_ASSERT_EQUAL_STRING("updated", htbl_find(tbl, "KEY1"));
}

void test_htbl_remove_fail(void)
{
    TEST_ASSERT_NULL(htbl_remove(tbl,"KEY DNE"));
}

/* LOAD_FACTOR_THRESHOLD defined in hashtable header */
void test_htbl_resize(void)
{
    TEST_ASSERT_EQUAL(1, htbl_put(tbl, "KEY1", "Key1's value"));
    TEST_ASSERT_EQUAL(1, htbl_put(tbl, "KEY2", "Key2's value"));
    TEST_ASSERT_EQUAL(1, htbl_put(tbl, "KEY3", "Key3's value"));
    TEST_ASSERT_EQUAL(1, htbl_put(tbl, "KEY4", "Key4's value"));
    TEST_ASSERT_EQUAL(1, htbl_put(tbl, "KEY5", "Key5's value"));  // Triggers resize
    TEST_ASSERT_EQUAL(CAPACITY * 2, htbl_capacity(tbl));

    /* Confirm everything was rehashed */
    TEST_ASSERT_EQUAL_STRING("Key1's value", htbl_find(tbl, "KEY1"));
    TEST_ASSERT_EQUAL_STRING("Key2's value", htbl_find(tbl, "KEY2"));
    TEST_ASSERT_EQUAL_STRING("Key3's value", htbl_find(tbl, "KEY3"));
    TEST_ASSERT_EQUAL_STRING("Key4's value", htbl_find(tbl, "KEY4"));
    TEST_ASSERT_EQUAL_STRING("Key5's value", htbl_find(tbl, "KEY5"));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_htbl_create);
    RUN_TEST(test_htbl_free);
    RUN_TEST(test_htbl_put_and_remove);
    RUN_TEST(test_htbl_put_update);
    RUN_TEST(test_htbl_remove_fail);
    RUN_TEST(test_htbl_resize);
    return UNITY_END();
}