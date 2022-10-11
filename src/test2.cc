#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "s21_decimal.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

s21_decimal case1[] = {{{1, 0, 0, 0}},           {{4, 0, 0, 0}},
                       {{40, 0, 0, 2147483648}}, {{40, 0, 0, 0}},
                       {{-1, -1, -1, 0}},        {{6, 0, 0, 131072}},
                       {{-1, -1, -1, 0}},        {{-1, -1, -1, 0}},
                       {{-1, -1, -1, 0}},        {{-1, -1, -1, 32768}}};

s21_decimal case2[] = {{{0, 0, 0, 0}},
                       {{1, 0, 0, 2147483648}},
                       {{33, 0, 0, 2147483648}},
                       {{33, 0, 0, 2147483648}},
                       {{-2, -1, -1, 2147483648}},
                       {{5, 0, 0, 2147844096}},
                       {{4, 0, 0, -2147450880}},
                       {{6, 0, 0, -2147450880}},
                       {{-1, -1, -1, 0}},
                       {{-1, -1, -1, 0}}};

s21_decimal result = {{0, 0, 0, 0}};

typedef struct {
    s21_decimal op1;
    int op2;
} test_struct_di;

typedef struct {
    s21_decimal op1;
    float op2;
    int result_code;
} test_struct_df;

typedef struct {
    s21_decimal op;
    s21_decimal wait;
} test_struct_dd;

typedef struct {
    s21_decimal op1;
    s21_decimal op2;
    s21_decimal wait;
    int result_code;
} test_struct_ddd;

typedef struct {
    s21_decimal op1;
    s21_decimal op2;
    int result_less;
    int result_less_or_equal;
    int result_greater;
    int result_greater_or_equal;
    int result_equal;
    int result_not_equal;
} test_struct_ddi;

test_struct_ddd test_pack_add[] = {
    {{{0x82e25aed, 0xf9e825ad, 0xb03ef094, 0x800e0000}},
     {{0x481b1f98, 0xfbfd896d, 0x00046d77, 0x80180000}},
     {{0xb629b5da, 0xf9ea0c7f, 0xb03ef094, 0x800e0000}},
     RESULT_SUCCESS},

    {{{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}},
     {{0x000001, 0x000000, 0x000000, 0x80000000}},
     {{0x000000, 0x000000, 0x000000, 0x000000}},
     MINLIMIT_ERROR},

    {{{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}},
     {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
     {{0xfffffffe, 0xffffffff, 0xffffffff, 0x00000000}},
     RESULT_SUCCESS},

    {{{0x00000555, 0x00000000, 0x00000000, 0x80000000}},
     {{0x00099999, 0x00000000, 0x00000000, 0x80000000}},
     {{0x00099EEE, 0x00000000, 0x00000000, 0x80000000}},
     RESULT_SUCCESS},

    {{{0xAAAAAAAA, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00999999, 0x00000000, 0x00000000, 0x00000000}},
     {{0xAB444443, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},

    {{{0x00000010, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000010, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000020, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},

    {{{0x7f7f7f7f, 0x00007f7f, 0x00000000, 0x00040000}},
     {{0x7f7f7f7f, 0x007f7f7f, 0x00000000, 0x00040000}},
     {{0xfefefefe, 0x007ffefe, 0x00000000, 0x00040000}},
     RESULT_SUCCESS},

    {{{0xffffffff, 0xffffffff, 0x00000000, 0x00000000}},
     {{0xffffffff, 0xffffffff, 0x00000000, 0x00000000}},
     {{0xfffffffe, 0xffffffff, 0x00000001, 0x00000000}},
     RESULT_SUCCESS},

    {{{0x7f7f7f7f, 0x00007f7f, 0x00000000, 0x00000000}},
     {{0x7f7f7f7f, 0x007f7f7f, 0x00000000, 0x80000000}},
     {{0x00000000, 0x007f0000, 0x00000000, 0x80000000}},
     RESULT_SUCCESS},

    {{{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}},
     {{0xffffffff, 0xffffffff, 0x00000000, 0x00000000}},
     {{0x00000000, 0x00000000, 0xffffffff, 0x80000000}},
     RESULT_SUCCESS},
};

START_TEST(test_add) {
    s21_decimal result;
    int result_code = s21_add(test_pack_add[_i].op1, test_pack_add[_i].op2, &result);
    ck_assert_int_eq(result_code, test_pack_add[_i].result_code);
    if (result_code == RESULT_SUCCESS) {
        ck_assert_mem_eq(&result, &test_pack_add[_i].wait, sizeof(s21_decimal));
    }
}
END_TEST


test_struct_ddd test_pack_sub[] = {
    {{{0x00000008, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000003, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000005, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},

    {{{0x00000fff, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000794, 0x00000000, 0x00000000, 0x00000000}},
     {{0x0000086b, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},

    {{{0xffffffff, 0xffffffff, 0x00ffffff, 0x80000000}},
     {{0x87654234, 0x00000567, 0x00000000, 0x00000000}},
     {{0x87654233, 0x00000567, 0x01000000, 0x80000000}},
     RESULT_SUCCESS},

    {{{0xffffffff, 0xffffffff, 0x00ffffff, 0x00000000}},
     {{0x87654234, 0x00000567, 0x00000000, 0x00000000}},
     {{0x789abdcb, 0xfffffa98, 0x00ffffff, 0x00000000}},
     RESULT_SUCCESS},

    {{{0x1c3957, 0x000000, 0x000000, 0x000000}},
     {{0x000006, 0x000000, 0x000000, 0x000000}},
     {{0x1c3951, 0x000000, 0x000000, 0x000000}},
     RESULT_SUCCESS},

    {{{0xfffffff6, 0xffffffff, 0x000009, 0x010000}},
     {{0xd401a48e, 0x000000, 0x000000, 0x000000}},
     {{0xb7ef926a, 0xfffffff7, 0x000009, 0x010000}},
     RESULT_SUCCESS},

    {{{0x54403d8c, 0x8b520559, 0x1fa981ad, 0x800c0000}},
     {{0x65f24dac, 0x07a9ab, 0x000000, 0x80060000}},
     {{0xd2927a8c, 0x9e9e7104, 0x1fa98138, 0x800c0000}},
     RESULT_SUCCESS},

    {{{0x910af4ca, 0xc045d5f2, 0x27e41b00, 0x150000}},
     {{0x11cdd185, 0xf5bc6fc0, 0x2d50f3f, 0x80100000}},
     {{0xd20de5bf, 0xa74e7221, 0x1c539ded, 0x110000}},
     RESULT_SUCCESS},

    {{{0xB92F18FC, 0xCB29DA8B, 0xF0EE80AE, 0x00110000}},
     {{0x7C273FEA, 0x565E5286, 0x00000102, 0x000A0000}},
     {{0xB32C07FC, 0x57CC1340, 0x56F358E7, 0x00110000}},
     RESULT_SUCCESS},

    {{{0x00000002, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000006, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000004, 0x00000000, 0x00000000, 0x80000000}},
     RESULT_SUCCESS},

    {{{0x00000002, 0x00000000, 0x00000000, 0x80000000}},
     {{0x00000006, 0x00000000, 0x00000000, 0x80000000}},
     {{0x00000004, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},
};

START_TEST(test_sub) {
    s21_decimal result;
    s21_sub(test_pack_sub[_i].op1, test_pack_sub[_i].op2, &result);
    ck_assert_mem_eq(&result, &test_pack_sub[_i].wait, sizeof(s21_decimal));
}
END_TEST


test_struct_ddd test_pack_mul[] = {
    {{{0x0000000a, 0x00000000, 0x0000000a, 0x00010000}},
     {{0x02433305, 0x9701bb81, 0x1c529ce7, 0x00050000}},
     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
     MAXLIMIT_ERROR},

    {{{0x0000000a, 0x00000000, 0x0000000a, 0x80010000}},
     {{0x02433305, 0x9701bb81, 0x1c529ce7, 0x00050000}},
     {{0x00000000, 0x00000000, 0x00000000, 0x80000000}},
     MINLIMIT_ERROR},

    {{{0x000000018, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},
     {{0x000000030, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},

    {{{0x00000002, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000004, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},

    {{{0xffffffff, 0x00000000, 0x00000000, 0x00030000}},
     {{0xcccc1234, 0xaaaaaabb, 0x00000000, 0x00080000}},
     {{0x3333edcc, 0x22216778, 0xaaaaaabb, 0x000b0000}},
     RESULT_SUCCESS},

    {{{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},

    {{{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},

    {{{0xB92F18FC, 0xCB29DA8B, 0xF0EE80AE, 0x80000000}},
     {{0x7C273FEA, 0x565E5286, 0x00000102, 0x80000000}},
     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
     MAXLIMIT_ERROR},

    {{{0xB92F18FC, 0xCB29DA8B, 0xF0EE80AE, 0x80110000}},
     {{0x7C273FEA, 0x565E5286, 0x00000102, 0x800A0000}},
     {{0x0DD89410, 0xFCA6D602, 0x72D0C9DB, 0x00050000}},
     RESULT_SUCCESS},

    {{{0xB92F18FC, 0xCB29DA8B, 0xF0EE80AE, 0x00110000}},
     {{0x7C273FEA, 0x565E5286, 0x00000102, 0x000A0000}},
     {{0x0DD89410, 0xFCA6D602, 0x72D0C9DB, 0x00050000}},
     RESULT_SUCCESS},

    {{{0xB92F18FC, 0xCB29DA8B, 0xF0EE80AE, 0x80110000}},
     {{0x7C273FEA, 0x565E5286, 0x00000102, 0x000A0000}},
     {{0x0DD89410, 0xFCA6D602, 0x72D0C9DB, 0x80050000}},
     RESULT_SUCCESS},

    {{{0xB92F18FC, 0xCB29DA8B, 0xF0EE80AE, 0x00110000}},
     {{0x7C273FEA, 0x565E5286, 0x00000102, 0x800A0000}},
     {{0x0DD89410, 0xFCA6D602, 0x72D0C9DB, 0x80050000}},
     RESULT_SUCCESS},
};

START_TEST(test_mul) {
    s21_decimal result;
    s21_mul(test_pack_mul[_i].op1, test_pack_mul[_i].op2, &result);
    ck_assert_mem_eq(&result, &test_pack_mul[_i].wait, sizeof(s21_decimal));
}
END_TEST

test_struct_ddd test_pack_div[] = {
    {{{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},
    {{{0x000186A0, 0x00000000, 0x00000000, 0x00000000}},
     {{0x0000000a, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00002710, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},
    {{{0x00000004, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},
    {{{0x3333edcc, 0x22216778, 0xaaaaaabb, 0x00000000}},
     {{0xffffffff, 0x00000000, 0x00000000, 0x00000000}},
     {{0xcccc1234, 0xaaaaaabb, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},
    {{{0x499602D2, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000005, 0x00000000, 0x00000000, 0x00000000}},
     {{0x0eb79a2a, 0x00000000, 0x00000000, 0x00000000}},
     RESULT_SUCCESS},
    {{{0x00000369, 0x00000000, 0x00000000, 0x00020000}},
     {{0x00000003, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000123, 0x00000000, 0x00000000, 0x00020000}},
     RESULT_SUCCESS},
    {{{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
     {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
     DIVBYZERO_ERROR},
    {{{0xCF6B7A15, 0x6BEF84A9, 0x00000028, 0x00100000}},
     {{0x00000010, 0x00000000, 0x00000000, 0x00000000}},
     {{0x65650D45, 0x83C2E293, 0x000062AF, 0x00140000}},
     RESULT_SUCCESS},

    {{{0xCF6B7A15, 0x6BEF84A9, 0x00000028, 0x00100000}},
     {{0x8CF31A51, 0x00000455, 0x00000000, 0x00000000}},
     {{0x47803385, 0x7B6F40D1, 0x00000008, 0x001C0000}},
     RESULT_SUCCESS},

    {{{0xCF6B7A15, 0x6BEF84A9, 0x00000028, 0x00100000}},
     {{0x8CF31A51, 0x00000455, 0x00000000, 0x80000000}},
     {{0x47803385, 0x7B6F40D1, 0x00000008, 0x801C0000}},
     RESULT_SUCCESS},

    {{{0xCF6B7A15, 0x6BEF84A9, 0x00000028, 0x80100000}},
     {{0x8CF31A51, 0x00000455, 0x00000000, 0x00000000}},
     {{0x47803385, 0x7B6F40D1, 0x00000008, 0x801C0000}},
     RESULT_SUCCESS},

    {{{0xCF6B7A15, 0x6BEF84A9, 0x00000028, 0x80100000}},
     {{0x8CF31A51, 0x00000455, 0x00000000, 0x80000000}},
     {{0x47803385, 0x7B6F40D1, 0x00000008, 0x001C0000}},
     RESULT_SUCCESS},

    {{{0xB92F18FC, 0xCB29DA8B, 0xF0EE80AE, 0x00000000}},
     {{0x7C273FEA, 0x565E5286, 0x00000102, 0x00000000}},
     {{0xF93DF44C, 0xE69EB74A, 0x328EC239, 0x00150000}},
     RESULT_SUCCESS},

    {{{0xB92F18FC, 0xCB29DA8B, 0xF0EE80AE, 0x80000000}},
     {{0x7C273FEA, 0x565E5286, 0x00000102, 0x00000000}},
     {{0xF93DF44C, 0xE69EB74A, 0x328EC239, 0x80150000}},
     RESULT_SUCCESS},

    {{{0xB92F18FC, 0xCB29DA8B, 0xF0EE80AE, 0x00000000}},
     {{0x7C273FEA, 0x565E5286, 0x00000102, 0x80000000}},
     {{0xF93DF44C, 0xE69EB74A, 0x328EC239, 0x80150000}},
     RESULT_SUCCESS},

    {{{0xB92F18FC, 0xCB29DA8B, 0xF0EE80AE, 0x80000000}},
     {{0x7C273FEA, 0x565E5286, 0x00000102, 0x80000000}},
     {{0xF93DF44C, 0xE69EB74A, 0x328EC239, 0x00150000}},
     RESULT_SUCCESS},
};

START_TEST(test_div) {
    s21_decimal result;
    int result_code = s21_div(test_pack_div[_i].op1, test_pack_div[_i].op2, &result);
    ck_assert_int_eq(result_code, test_pack_div[_i].result_code);
    if (result_code == RESULT_SUCCESS) {
        ck_assert_mem_eq(&result, &test_pack_div[_i].wait, sizeof(s21_decimal));
    }
}
END_TEST

test_struct_ddd test_pack_mod[] = {
    {{{0x00000011, 0x00000000, 0x00000000, 0x00010000}},
     {{0x00000007, 0x00000000, 0x00000000, 0x00010000}},
     {{0x00000003, 0x00000000, 0x00000000, 0x00010000}},
     RESULT_SUCCESS},

    {{{0x00000002, 0x00000000, 0x00000000, 0x00000000}},
     {{0x0000000b, 0x00000000, 0x00000000, 0x00010000}},
     {{0x00000009, 0x00000000, 0x00000000, 0x00010000}},
     RESULT_SUCCESS},

    {{{0x00002810, 0x00000000, 0x00000000, 0x00030000}},
     {{0x0000000b, 0x00000000, 0x00000000, 0x00010000}},
     {{0x00000164, 0x00000000, 0x00000000, 0x00030000}},
     RESULT_SUCCESS},

    {{{0x00000002, 0x00000000, 0x00000000, 0x00030000}},
     {{0x0000000b, 0x00000000, 0x00000000, 0x00010000}},
     {{0x00000002, 0x00000000, 0x00000000, 0x00030000}},
     RESULT_SUCCESS},

    {{{0xC046A714, 0x000043E6, 0x00000000, 0x00030000}},
     {{0x0000000b, 0x00000000, 0x00000000, 0x00010000}},
     {{0x000001B4, 0x00000000, 0x00000000, 0x00030000}},
    RESULT_SUCCESS},

    {{{0x9CE50C1C, 0x195CBDE1, 0x00065317, 0x000E0000}},
     {{0x45A70FC2, 0x00000001, 0x00000000, 0x00000000}},
     {{0x69CA8C1C, 0x025742C7, 0x0000730E, 0x000E0000}},
     RESULT_SUCCESS},

    {{{0x9CE50C1C, 0x195CBDE1, 0x00065317, 0x800E0000}},
     {{0x45A70FC2, 0x00000001, 0x00000000, 0x00000000}},
     {{0x69CA8C1C, 0x025742C7, 0x0000730E, 0x800E0000}},
     RESULT_SUCCESS},

    {{{0x9CE50C1C, 0x195CBDE1, 0x00065317, 0x000E0000}},
     {{0x45A70FC2, 0x00000001, 0x00000000, 0x80000000}},
     {{0x69CA8C1C, 0x025742C7, 0x0000730E, 0x000E0000}},
     RESULT_SUCCESS},
};

START_TEST(test_mod) {
    s21_decimal result;
    s21_mod(test_pack_mod[_i].op1, test_pack_mod[_i].op2, &result);
    ck_assert_mem_eq(&result, &test_pack_mod[_i].wait, sizeof(s21_decimal));
}
END_TEST

/*COMPARE TESTS*/

START_TEST(is_less) {
  s21_decimal case1[] = {{{10, 0, 0, 0}}, {{3, 0, 0, 0}},  {{9, 0, 0, 0}},
                         {{4, 0, 0, 0}},  {{0, 0, 0, 0}},  {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{10, 0, 0, 0}}, {{3, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}},  {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  s21_decimal case2[] = {{{2, 0, 0, 0}},  {{7, 0, 0, 0}}, {{2, 0, 0, 0}},
                         {{15, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{2, 0, 0, 0}}, {{15, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}}, {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  case1[2].bits[3] |= 1 << 31;
  case2[2].bits[3] |= 1 << 31;
  case1[3].bits[3] |= 1 << 31;
  case2[3].bits[3] |= 1 << 31;
  case1[5].bits[3] |= 1 << 31;
  case2[6].bits[3] |= 1 << 31;
  case2[7].bits[3] |= 1 << 31;
  case1[8].bits[3] |= 1 << 31;
  case1[9].bits[3] |= 1 << 31;
  case2[9].bits[3] |= 1 << 31;
  case1[11].bits[3] |= 1 << 31;
  case2[12].bits[3] |= 1 << 31;
  ck_assert_int_eq(s21_is_less(case1[0], case2[0]), 0);
  ck_assert_int_eq(s21_is_less(case1[1], case2[1]), 1);
  ck_assert_int_eq(s21_is_less(case1[2], case2[2]), 1);
  ck_assert_int_eq(s21_is_less(case1[3], case2[3]), 0);
  ck_assert_int_eq(s21_is_less(case1[4], case2[4]), 0);
  ck_assert_int_eq(s21_is_less(case1[5], case2[5]), 0);
  ck_assert_int_eq(s21_is_less(case1[6], case2[6]), 0);
  ck_assert_int_eq(s21_is_less(case1[7], case2[7]), 0);
  ck_assert_int_eq(s21_is_less(case1[8], case2[8]), 1);
  ck_assert_int_eq(s21_is_less(case1[9], case2[9]), 0);
  ck_assert_int_eq(s21_is_less(case1[10], case2[10]), 0);
  ck_assert_int_eq(s21_is_less(case1[11], case2[11]), 1);
  ck_assert_int_eq(s21_is_less(case1[12], case2[12]), 0);
}
END_TEST

START_TEST(is_less_or_equal) {
  s21_decimal case1[] = {{{10, 0, 0, 0}}, {{3, 0, 0, 0}},  {{9, 0, 0, 0}},
                         {{4, 0, 0, 0}},  {{0, 0, 0, 0}},  {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{10, 0, 0, 0}}, {{3, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}},  {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  s21_decimal case2[] = {{{2, 0, 0, 0}},  {{7, 0, 0, 0}}, {{2, 0, 0, 0}},
                         {{15, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{2, 0, 0, 0}}, {{15, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}}, {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  case1[2].bits[3] |= 1 << 31;
  case2[2].bits[3] |= 1 << 31;
  case1[3].bits[3] |= 1 << 31;
  case2[3].bits[3] |= 1 << 31;
  case1[5].bits[3] |= 1 << 31;
  case2[6].bits[3] |= 1 << 31;
  case2[7].bits[3] |= 1 << 31;
  case1[8].bits[3] |= 1 << 31;
  case1[9].bits[3] |= 1 << 31;
  case2[9].bits[3] |= 1 << 31;
  case1[11].bits[3] |= 1 << 31;
  case2[12].bits[3] |= 1 << 31;
  ck_assert_int_eq(s21_is_less_or_equal(case1[0], case2[0]), 0);
  ck_assert_int_eq(s21_is_less_or_equal(case1[1], case2[1]), 1);
  ck_assert_int_eq(s21_is_less_or_equal(case1[2], case2[2]), 1);
  ck_assert_int_eq(s21_is_less_or_equal(case1[3], case2[3]), 0);
  ck_assert_int_eq(s21_is_less_or_equal(case1[4], case2[4]), 1);
  ck_assert_int_eq(s21_is_less_or_equal(case1[5], case2[5]), 1);
  ck_assert_int_eq(s21_is_less_or_equal(case1[6], case2[6]), 1);
  ck_assert_int_eq(s21_is_less_or_equal(case1[7], case2[7]), 0);
  ck_assert_int_eq(s21_is_less_or_equal(case1[8], case2[8]), 1);
  ck_assert_int_eq(s21_is_less_or_equal(case1[9], case2[9]), 1);
  ck_assert_int_eq(s21_is_less_or_equal(case1[10], case2[10]), 1);
  ck_assert_int_eq(s21_is_less_or_equal(case1[11], case2[11]), 1);
  ck_assert_int_eq(s21_is_less_or_equal(case1[12], case2[12]), 0);
}
END_TEST

START_TEST(is_greater) {
  s21_decimal case1[] = {{{10, 0, 0, 0}}, {{3, 0, 0, 0}},  {{9, 0, 0, 0}},
                         {{4, 0, 0, 0}},  {{0, 0, 0, 0}},  {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{10, 0, 0, 0}}, {{3, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}},  {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  s21_decimal case2[] = {{{2, 0, 0, 0}},  {{7, 0, 0, 0}}, {{2, 0, 0, 0}},
                         {{15, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{2, 0, 0, 0}}, {{15, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}}, {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  case1[2].bits[3] |= 1 << 31;
  case2[2].bits[3] |= 1 << 31;
  case1[3].bits[3] |= 1 << 31;
  case2[3].bits[3] |= 1 << 31;
  case1[5].bits[3] |= 1 << 31;
  case2[6].bits[3] |= 1 << 31;
  case2[7].bits[3] |= 1 << 31;
  case1[8].bits[3] |= 1 << 31;
  case1[9].bits[3] |= 1 << 31;
  case2[9].bits[3] |= 1 << 31;
  case1[11].bits[3] |= 1 << 31;
  case2[12].bits[3] |= 1 << 31;
  ck_assert_int_eq(s21_is_greater(case1[0], case2[0]), 1);
  ck_assert_int_eq(s21_is_greater(case1[1], case2[1]), 0);
  ck_assert_int_eq(s21_is_greater(case1[2], case2[2]), 0);
  ck_assert_int_eq(s21_is_greater(case1[3], case2[3]), 1);
  ck_assert_int_eq(s21_is_greater(case1[4], case2[4]), 0);
  ck_assert_int_eq(s21_is_greater(case1[5], case2[5]), 0);
  ck_assert_int_eq(s21_is_greater(case1[6], case2[6]), 0);
  ck_assert_int_eq(s21_is_greater(case1[7], case2[7]), 1);
  ck_assert_int_eq(s21_is_greater(case1[8], case2[8]), 0);
  ck_assert_int_eq(s21_is_greater(case1[9], case2[9]), 0);
  ck_assert_int_eq(s21_is_greater(case1[10], case2[10]), 0);
  ck_assert_int_eq(s21_is_greater(case1[11], case2[11]), 0);
  ck_assert_int_eq(s21_is_greater(case1[12], case2[12]), 1);
}
END_TEST

START_TEST(is_greater_or_equal) {
  s21_decimal case1[] = {{{10, 0, 0, 0}}, {{3, 0, 0, 0}},  {{9, 0, 0, 0}},
                         {{4, 0, 0, 0}},  {{0, 0, 0, 0}},  {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{10, 0, 0, 0}}, {{3, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}},  {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  s21_decimal case2[] = {{{2, 0, 0, 0}},  {{7, 0, 0, 0}}, {{2, 0, 0, 0}},
                         {{15, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{2, 0, 0, 0}}, {{15, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}}, {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  case1[2].bits[3] |= 1 << 31;
  case2[2].bits[3] |= 1 << 31;
  case1[3].bits[3] |= 1 << 31;
  case2[3].bits[3] |= 1 << 31;
  case1[5].bits[3] |= 1 << 31;
  case2[6].bits[3] |= 1 << 31;
  case2[7].bits[3] |= 1 << 31;
  case1[8].bits[3] |= 1 << 31;
  case1[9].bits[3] |= 1 << 31;
  case2[9].bits[3] |= 1 << 31;
  case1[11].bits[3] |= 1 << 31;
  case2[12].bits[3] |= 1 << 31;
  ck_assert_int_eq(s21_is_greater_or_equal(case1[0], case2[0]), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[1], case2[1]), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[2], case2[2]), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[3], case2[3]), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[4], case2[4]), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[5], case2[5]), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[6], case2[6]), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[7], case2[7]), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[8], case2[8]), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[9], case2[9]), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[10], case2[10]), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[11], case2[11]), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(case1[12], case2[12]), 1);
}
END_TEST

START_TEST(is_equal) {
  s21_decimal case1[] = {{{10, 0, 0, 0}}, {{3, 0, 0, 0}},  {{9, 0, 0, 0}},
                         {{4, 0, 0, 0}},  {{0, 0, 0, 0}},  {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{10, 0, 0, 0}}, {{3, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}},  {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  s21_decimal case2[] = {{{2, 0, 0, 0}},  {{7, 0, 0, 0}}, {{2, 0, 0, 0}},
                         {{15, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{2, 0, 0, 0}}, {{15, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}}, {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  case1[2].bits[3] |= 1 << 31;
  case2[2].bits[3] |= 1 << 31;
  case1[3].bits[3] |= 1 << 31;
  case2[3].bits[3] |= 1 << 31;
  case1[5].bits[3] |= 1 << 31;
  case2[6].bits[3] |= 1 << 31;
  case2[7].bits[3] |= 1 << 31;
  case1[8].bits[3] |= 1 << 31;
  case1[9].bits[3] |= 1 << 31;
  case2[9].bits[3] |= 1 << 31;
  case1[11].bits[3] |= 1 << 31;
  case2[12].bits[3] |= 1 << 31;
  ck_assert_int_eq(s21_is_equal(case1[0], case2[0]), 0);
  ck_assert_int_eq(s21_is_equal(case1[1], case2[1]), 0);
  ck_assert_int_eq(s21_is_equal(case1[2], case2[2]), 0);
  ck_assert_int_eq(s21_is_equal(case1[3], case2[3]), 0);
  ck_assert_int_eq(s21_is_equal(case1[4], case2[4]), 1);
  ck_assert_int_eq(s21_is_equal(case1[5], case2[5]), 1);
  ck_assert_int_eq(s21_is_equal(case1[6], case2[6]), 1);
  ck_assert_int_eq(s21_is_equal(case1[7], case2[7]), 0);
  ck_assert_int_eq(s21_is_equal(case1[8], case2[8]), 0);
  ck_assert_int_eq(s21_is_equal(case1[9], case2[9]), 1);
  ck_assert_int_eq(s21_is_equal(case1[10], case2[10]), 1);
  ck_assert_int_eq(s21_is_equal(case1[11], case2[11]), 0);
  ck_assert_int_eq(s21_is_equal(case1[12], case2[12]), 0);
}
END_TEST

START_TEST(is_not_equal) {
  s21_decimal case1[] = {{{10, 0, 0, 0}}, {{3, 0, 0, 0}},  {{9, 0, 0, 0}},
                         {{4, 0, 0, 0}},  {{0, 0, 0, 0}},  {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{10, 0, 0, 0}}, {{3, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}},  {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  s21_decimal case2[] = {{{2, 0, 0, 0}},  {{7, 0, 0, 0}}, {{2, 0, 0, 0}},
                         {{15, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}},
                         {{0, 0, 0, 0}},  {{2, 0, 0, 0}}, {{15, 0, 0, 0}},
                         {{5, 0, 0, 0}},  {{5, 0, 0, 0}}, {{8, 0, 0, 0}},
                         {{8, 0, 0, 0}}};
  case1[2].bits[3] |= 1 << 31;
  case2[2].bits[3] |= 1 << 31;
  case1[3].bits[3] |= 1 << 31;
  case2[3].bits[3] |= 1 << 31;
  case1[5].bits[3] |= 1 << 31;
  case2[6].bits[3] |= 1 << 31;
  case2[7].bits[3] |= 1 << 31;
  case1[8].bits[3] |= 1 << 31;
  case1[9].bits[3] |= 1 << 31;
  case2[9].bits[3] |= 1 << 31;
  case1[11].bits[3] |= 1 << 31;
  case2[12].bits[3] |= 1 << 31;
  ck_assert_int_eq(s21_is_not_equal(case1[0], case2[0]), 1);
  ck_assert_int_eq(s21_is_not_equal(case1[1], case2[1]), 1);
  ck_assert_int_eq(s21_is_not_equal(case1[2], case2[2]), 1);
  ck_assert_int_eq(s21_is_not_equal(case1[3], case2[3]), 1);
  ck_assert_int_eq(s21_is_not_equal(case1[4], case2[4]), 0);
  ck_assert_int_eq(s21_is_not_equal(case1[5], case2[5]), 0);
  ck_assert_int_eq(s21_is_not_equal(case1[6], case2[6]), 0);
  ck_assert_int_eq(s21_is_not_equal(case1[7], case2[7]), 1);
  ck_assert_int_eq(s21_is_not_equal(case1[8], case2[8]), 1);
  ck_assert_int_eq(s21_is_not_equal(case1[9], case2[9]), 0);
  ck_assert_int_eq(s21_is_not_equal(case1[10], case2[10]), 0);
  ck_assert_int_eq(s21_is_not_equal(case1[11], case2[11]), 1);
  ck_assert_int_eq(s21_is_not_equal(case1[12], case2[12]), 1);
}
END_TEST

START_TEST(from_int_to_decimal) {
    s21_decimal cmp[]= {{{10000, 0, 0, 0}}, {{(unsigned)INT_MAX + 1, 0x0, 0x0, 0x80000000}}};
    int src[] = {10000, INT_MIN};
    s21_decimal result;
    int f_result[] = {0, 0};
    int check = s21_from_int_to_decimal(src[_i], &result);
    ck_assert_int_eq(check, f_result[_i]);
    ck_assert_int_eq(result.bits[0], cmp[_i].bits[0]);
    ck_assert_int_eq(result.bits[3], cmp[_i].bits[3]);
}
END_TEST

START_TEST(from_float_to_decimal) {
    s21_decimal cmp[]= {{{3, 0, 0, 0x00020000}}, {{1271234, 0, 0, 0x00040000}},
    {{1020000000, 0, 0, 0}},
    {{0, 0, 0, 0}}, {{0, 0, 0, 0}}, {{0, 0, 0, 0}}};
    s21_decimal result;
    float src[] = {0.03F, 127.1234F, 1.02E+09F, INFINITY, -INFINITY, NAN};
    int f_result[] = {0, 0, 0, 1, 1, 1};
    int check = s21_from_float_to_decimal(src[_i], &result);
    ck_assert_int_eq(check, f_result[_i]);
    ck_assert_int_eq(result.bits[0], cmp[_i].bits[0]);
    ck_assert_int_eq(result.bits[3], cmp[_i].bits[3]);
}
END_TEST

START_TEST(from_decimal_to_int) {
    s21_decimal src[] = {{{10000, 0, 0, 0}}, {{INT_MAX, 0, 0, 0}},
    {{(unsigned)INT_MAX + 1, 0, 0, 0x80000000}}, {{(unsigned)INT_MAX + 1, 0, 0, 0}},
    {{(unsigned)INT_MAX + 2, 0, 0, 0x80000000}}, {{0x173c1c7, 0, 0, 0x80070000}}};
    int result;
    int cmp[] = {10000, INT_MAX, INT_MIN, 0, 0, -2};
    int f_result[] = {0, 0, 0, 1, 1, 0};
    int check = s21_from_decimal_to_int(src[_i], &result);
    ck_assert_int_eq(check, f_result[_i]);
    ck_assert_int_eq(result, cmp[_i]);
}
END_TEST

START_TEST(from_decimal_to_float) {
    s21_decimal src[] = {{{0x0000fe65, 0, 0, 0x80030000}}, {{3, 0, 0, 0x00020000}},
    {{1271234, 0, 0, 0x00040000}}, {{1020000000, 0, 0, 0}}};
    float result;
    float cmp[] = {-65.125, 0.03F, 127.1234F, 1.02E+09F};
    int f_result[] = {0, 0, 0, 0};
    int check = s21_from_decimal_to_float(src[_i], &result);
    ck_assert_int_eq(check, f_result[_i]);
    ck_assert_float_eq(result, cmp[_i]);
}
END_TEST

test_struct_dd test_pack_floor[] = {
    {{{0x0000000f, 0x00000000, 0x00000000, 0x00010000}}, {{0x00000001, 0x00000000, 0x00000000, 0x00000000}}},
    {{{0x0000000f, 0x00000000, 0x00000000, 0x80010000}}, {{0x00000002, 0x00000000, 0x00000000, 0x80000000}}},
    {{{0xE110C39E, 0x00E1C0B3, 0x00000000, 0x80040000}}, {{0x7E419033, 0x000005C7, 0x00000000, 0x80000000}}},
    {{{0x000000ff, 0x00000000, 0x00000000, 0x80000000}}, {{0x000000ff, 0x00000000, 0x00000000, 0x80000000}}},
    {{{0xFF42F47D, 0x27D5BD5C, 0x00000004, 0x80120000}}, {{0x0000004D, 0x00000000, 0x00000000, 0x80000000}}},
    {{{0xFF42F47D, 0x27D5BD5C, 0x00000004, 0x00120000}}, {{0x0000004C, 0x00000000, 0x00000000, 0x00000000}}},
};

START_TEST(test_floor) {
    s21_decimal result;
    s21_floor(test_pack_floor[_i].op, &result);
    ck_assert_mem_eq(&result, &test_pack_floor[_i].wait, sizeof(s21_decimal));
}
END_TEST


test_struct_dd test_pack_round[] = {
    {{{0x00000011, 0x00000000, 0x00000000, 0x00010000}}, {{0x00000002, 0x00000000, 0x00000000, 0x00000000}}},
    {{{0x00000010, 0x00000000, 0x00000000, 0x00010000}}, {{0x00000002, 0x00000000, 0x00000000, 0x00000000}}},
    {{{0x00002810, 0x00000000, 0x00000000, 0x00030000}}, {{0x0000000a, 0x00000000, 0x00000000, 0x00000000}}},
    {{{0x00000010, 0x00000000, 0x00000000, 0x80010000}}, {{0x00000002, 0x00000000, 0x00000000, 0x80000000}}},
    {{{0x0000000f, 0x00000000, 0x00000000, 0x80010000}}, {{0x00000002, 0x00000000, 0x00000000, 0x80000000}}},
    {{{0x00000095, 0x00000000, 0x00000000, 0x80020000}}, {{0x00000001, 0x00000000, 0x00000000, 0x80000000}}},
    {{{0x442EF47D, 0x250F326C, 0x00000004, 0x80120000}}, {{0x0000004C, 0x00000000, 0x00000000, 0x80000000}}},
};

START_TEST(test_round) {
    s21_decimal result;
    s21_round(test_pack_round[_i].op, &result);
    ck_assert_mem_eq(&result, &test_pack_round[_i].wait, sizeof(s21_decimal));
}
END_TEST


test_struct_dd test_pack_truncate[] = {
    {{{0x0052f2, 0, 0, 0x040000}}, {{2, 0, 0, 0}}},
    {{{0x000052f2, 0x00000000, 0x00000000, 0x00040000}}, {{0x00000002, 0x00000000, 0x00000000, 0x00000000}}},
    {{{0x1b3d4441, 0x00000000, 0x00000000, 0x00060000}}, {{0x000001c9, 0x00000000, 0x00000000, 0x00000000}}},
    {{{0x000007d0, 0x00000000, 0x00000000, 0x00030000}}, {{0x00000002, 0x00000000, 0x00000000, 0x00000000}}},
    {{{0x00000000, 0x00000000, 0x00000000, 0x801b0000}}, {{0x00000000, 0x00000000, 0x00000000, 0x80000000}}},
    {{{0x00000003, 0x00000000, 0x00000000, 0x80000000}}, {{0x00000003, 0x00000000, 0x00000000, 0x80000000}}},
    {{{0x0021e884, 0x00000000, 0x00000000, 0x00060000}}, {{0x00000002, 0x00000000, 0x00000000, 0x00000000}}},
};

START_TEST(test_truncate) {
    s21_decimal result;
    s21_truncate(test_pack_truncate[_i].op, &result);
    ck_assert_mem_eq(&result, &test_pack_truncate[_i].wait, sizeof(s21_decimal));
}
END_TEST

test_struct_dd test_pack_negate[] = {
    {{{0x00000011, 0x00000000, 0x00000000, 0x00010000}}, {{0x00000011, 0x00000000, 0x00000000, 0x80010000}}},
    {{{0x00000010, 0x00000000, 0x00000000, 0x00010000}}, {{0x00000010, 0x00000000, 0x00000000, 0x80010000}}},
    {{{0x00002810, 0x00000000, 0x00000000, 0x00030000}}, {{0x00002810, 0x00000000, 0x00000000, 0x80030000}}},
    {{{0x00000010, 0x00000000, 0x00000000, 0x80010000}}, {{0x00000010, 0x00000000, 0x00000000, 0x00010000}}},
    {{{0x0000000f, 0x00000000, 0x00000000, 0x80010000}}, {{0x0000000f, 0x00000000, 0x00000000, 0x00010000}}},
    {{{0x00000095, 0x00000000, 0x00000000, 0x80020000}}, {{0x00000095, 0x00000000, 0x00000000, 0x00020000}}},
    {{{0x1b3d4441, 0x1b3d4441, 0x1b3d4441, 0x80020000}}, {{0x1b3d4441, 0x1b3d4441, 0x1b3d4441, 0x00020000}}},
};

START_TEST(test_negate) {
    s21_decimal result;
    s21_negate(test_pack_negate[_i].op, &result);
    ck_assert_mem_eq(&result, &test_pack_negate[_i].wait, sizeof(s21_decimal));
}

test_struct_di test_pack_fitd[] = {
    {{{10000, 0x00000000, 0x00000000, 0x00000000}}, 10000},
    {{{(unsigned)INT_MAX + 1, 0x00000000, 0x00000000, 0x80000000}}, INT_MIN},
};

START_TEST(test_fitd) {
    s21_decimal result;
    s21_from_int_to_decimal(test_pack_fitd[_i].op2, &result);
    ck_assert_mem_eq(&result, &test_pack_fitd[_i].op1, sizeof(s21_decimal));
}
END_TEST

test_struct_di test_pack_fdti[] = {
    {{{10000, 0x00000000, 0x00000000, 0x00000000}}, 10000},
    {{{INT_MAX, 0x00000000, 0x00000000, 0x00000000}}, INT_MAX},
    {{{(unsigned)INT_MAX + 1, 0x00000000, 0x00000000, 0x80000000}}, INT_MIN},
    {{{(unsigned)INT_MAX + 1, 0x00000000, 0x00000000, 0x00000000}}, 0},
    {{{(unsigned)INT_MAX + 2, 0x00000000, 0x00000000, 0x80000000}}, 0},
    {{{0x173c1c7, 0, 0, 0x80070000}}, -2},
};

START_TEST(test_fdti) {
    int result = 0;
    s21_from_decimal_to_int(test_pack_fdti[_i].op1, &result);
    ck_assert_int_eq(result, test_pack_fdti[_i].op2);
}
END_TEST

test_struct_df test_pack_fftd[] = {
    {{{3, 0, 0, 0x00020000}}, 0.03F, RESULT_SUCCESS},
    {{{1271234, 0, 0, 0x00040000}}, 127.1234F, RESULT_SUCCESS},
    {{{1020000000, 0, 0, 0}}, 1.02E+09F, RESULT_SUCCESS},
    {{{0, 0, 0, 0}}, 1.0F / 0.0F, RESULT_ERROR},
    {{{0, 0, 0, 0}}, -1.0F / 0.0F, RESULT_ERROR},
    {{{0, 0, 0, 0}}, NAN, RESULT_ERROR},
};

START_TEST(test_fftd) {
    s21_decimal result;
    int result_code = s21_from_float_to_decimal(test_pack_fftd[_i].op2, &result);
    ck_assert_int_eq(result_code, test_pack_fftd[_i].result_code);
    if (result_code == RESULT_SUCCESS) {
        ck_assert_mem_eq(&result, &test_pack_fftd[_i].op1, sizeof(s21_decimal));
    }
}
END_TEST

test_struct_df test_pack_fdtf[] = {
    {{{0x0000fe65, 0x00000000, 0x00000000, 0x80030000}}, -65.125, RESULT_SUCCESS},
    {{{1271234, 0, 0, 0x00040000}}, 127.1234F, RESULT_SUCCESS},
    {{{1020000000, 0, 0, 0}}, 1.02E+09F, RESULT_SUCCESS},
};

START_TEST(test_fdtf) {
    float result = 0;
    s21_from_decimal_to_float(test_pack_fdtf[_i].op1, &result);
    ck_assert_float_eq(result, test_pack_fdtf[_i].op2);
}
END_TEST

Suite *dec_test_suite(void) {
  Suite *s;
  TCase *tc_decimal;
  s = suite_create("Testing in progress");
  tc_decimal = tcase_create("Test Functions");
  int test_pack_size = sizeof(test_pack_add) / sizeof(test_struct_ddd);
    tcase_add_loop_test(tc_decimal, test_add, 0, test_pack_size);

    test_pack_size = sizeof(test_pack_sub) / sizeof(test_struct_ddd);
    tcase_add_loop_test(tc_decimal, test_sub, 0, test_pack_size);

    test_pack_size = sizeof(test_pack_mul) / sizeof(test_struct_ddd);
    tcase_add_loop_test(tc_decimal, test_mul, 0, test_pack_size);

    test_pack_size = sizeof(test_pack_div) / sizeof(test_struct_ddd);
    tcase_add_loop_test(tc_decimal, test_div, 0, test_pack_size);

    test_pack_size = sizeof(test_pack_mod) / sizeof(test_struct_ddd);
    tcase_add_loop_test(tc_decimal, test_mod, 0, test_pack_size);
  tcase_add_test(tc_decimal, is_less);
  tcase_add_test(tc_decimal, is_less_or_equal);
  tcase_add_test(tc_decimal, is_greater);
  tcase_add_test(tc_decimal, is_greater_or_equal);
  tcase_add_test(tc_decimal, is_equal);
  tcase_add_test(tc_decimal, is_not_equal);
  tcase_add_test(tc_decimal, from_int_to_decimal);
  tcase_add_test(tc_decimal, from_float_to_decimal);
  tcase_add_test(tc_decimal, from_decimal_to_int);
  tcase_add_test(tc_decimal, from_decimal_to_float);

    int test_pack_size_fitd = sizeof(test_pack_fitd) / sizeof(test_struct_di);
    tcase_add_loop_test(tc_decimal, test_fitd, 0, test_pack_size_fitd);

    int test_pack_size_fdti = sizeof(test_pack_fdti) / sizeof(test_struct_di);
    tcase_add_loop_test(tc_decimal, test_fdti, 0, test_pack_size_fdti);

    int test_pack_size_fftd = sizeof(test_pack_fftd) / sizeof(test_struct_df);
    tcase_add_loop_test(tc_decimal, test_fftd, 0, test_pack_size_fftd);

    int test_pack_size_fdtf = sizeof(test_pack_fdtf) / sizeof(test_struct_df);
    tcase_add_loop_test(tc_decimal, test_fdtf, 0, test_pack_size_fdtf);

  test_pack_size = sizeof(test_pack_floor) / sizeof(test_struct_dd);
    tcase_add_loop_test(tc_decimal, test_floor, 0, test_pack_size);

    test_pack_size = sizeof(test_pack_round) / sizeof(test_struct_dd);
    tcase_add_loop_test(tc_decimal, test_round, 0, test_pack_size);

    test_pack_size = sizeof(test_pack_truncate) / sizeof(test_struct_dd);
    tcase_add_loop_test(tc_decimal, test_truncate, 0, test_pack_size);

    test_pack_size = sizeof(test_pack_negate) / sizeof(test_struct_dd);
    tcase_add_loop_test(tc_decimal, test_negate, 0, test_pack_size);
  suite_add_tcase(s, tc_decimal);
  return s;
}

int main(void) {
  int number_failed;
  Suite *s = dec_test_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
