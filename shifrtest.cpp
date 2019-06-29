#include <unittest++/UnitTest++.h>
#include "shifr.h"

shifr enc;

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("iteefxltlrdo", enc.encrypt("littleredfox", 2));
    }
    TEST(LongKey) {
        CHECK_EQUAL("tedxileoltrf", enc.encrypt("littleredfox", 3));
    }

}

struct KeyB_fixture {
    shifr * p;
    KeyB_fixture() {
        p = new shifr();
    }
    ~KeyB_fixture() {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ITEEFXLTLRDO",
                    p->encrypt("LITTLEREDFOX", 2));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("iteefxltlrdo",
                    p->encrypt("littleredfox", 2));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWithbothcase) {
        CHECK_EQUAL("ITEefxLTLrdo",
                    p->encrypt("LITTLEredfox", 2));
    }
   
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt("", 2),encryptException);
    }
 TEST_FIXTURE(KeyB_fixture,Stringwithdigs) {
        CHECK_THROW(p->encrypt("little123redfox", 2),encryptException);
    }
 TEST_FIXTURE(KeyB_fixture, shortString) {
        CHECK_THROW(p->encrypt("y", 2),encryptException);
    }
 TEST_FIXTURE(KeyB_fixture, keyequalString) {
        CHECK_THROW(p->encrypt("ye", 2),encryptException);
    }
 TEST_FIXTURE(KeyB_fixture, Stringwithprep) {
        CHECK_THROW(p→encrypt("little!redfox!!!", 2),encryptException);
    }
}

SUITE(DecryptText)
{
     TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("littleredfox",
                    p->decrypt("iteefxltlrdo ", 2));
    }
 TEST_FIXTURE(KeyB_fixture, upCaseString) {
        CHECK_EQUAL("LITTLEREDFOX",
                    p->decrypt("ITEEFXLTLRDO ", 2));
    }
    TEST_FIXTURE(KeyB_fixture, Stringwithdigs) {
        CHECK_THROW(p->decrypt("iteefx23", 2),encryptException);
    }
    TEST_FIXTURE(KeyB_fixture, Stringwithpunct) {
        CHECK_THROW(p→decrypt("iteefx!!!", 2),encryptException);
    }
    TEST_FIXTURE(KeyB_fixture, emptyString) {
        CHECK_THROW(p->decrypt("", 2),encryptException);
    }
    TEST_FIXTURE(KeyB_fixture, shortString) {
        CHECK_THROW(p->decrypt("y", 2),encryptException);
    }
TEST_FIXTURE(KeyB_fixture, equalkeyString) {
        CHECK_THROW(p->decrypt("ye", 2),encryptException);
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
