#include <unittest++/UnitTest++.h>
#include "modAlphaCipher.h"

SUITE(KeyTest) {
    TEST(ValidKey) {
        CHECK_EQUAL("БВГБВ",modAlphaCipher("БВГ").encrypt("ААААА"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("БВГДЕ",modAlphaCipher("БВГДЕЖЗИЙК").encrypt("ААААА"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("БВГБВ",modAlphaCipher("бвг").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("Б1"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("Б!!!"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("БВ Г"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"),cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture() {
        p = new modAlphaCipher("Б");
    }
    ~KeyB_fixture() {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("БВГДЕЖ",
                    p->encrypt("АБВГДЕ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("БВГДЕЖ",
                    p->encrypt("абвгде"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("БВГДЕЖЗИК",
                    p→encrypt("АБВ ГДЕ ЖЗИ!!!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("БВГД", p->encrypt("АБВГ123"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("1234+4321=5555"),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("АБВГДЕ",
                    modAlphaCipher("Я").encrypt("ЯАБВГД"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("АБВГДЕ",
                    p->decrypt("БВГДЕЖ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("БВГдеж"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p→decrypt("БВ,ГДЕ ЖЗ!!!"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("БВГ123"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("1234+4321=5555"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""),cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ЯАБВГД",
                    modAlphaCipher("Я").decrypt("АБВГДЕ"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
