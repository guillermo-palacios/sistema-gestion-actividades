#include <usuario-registrado.cc>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::StartsWith;

TEST(UsuarioRegistrado, IBAN1) {

  std::string IBAN="ES7301826516296117921137";
 

  EXPECT_TRUE(EsIBANValido(IBAN));
}
TEST(UsuarioRegistrado, IBAN2) {
  std::string IBAN="ES5000751582046613194852";
  

  EXPECT_TRUE(EsIBANValido(IBAN));
}
TEST(UsuarioRegistrado, IBAN3) {
  std::string IBAN="ES1234567890987654233343";
 

  EXPECT_FALSE(EsIBANValido(IBAN));
}
TEST(UsuarioRegistrado, IBAN4) {
  std::string IBAN="ES2387652637812939812489";


  EXPECT_FALSE(EsIBANValido(IBAN));
}
TEST(UsuarioRegistrado, IBAN5) {
  std::string IBAN="ES9861239812398123981239";


  EXPECT_FALSE(EsIBANValido(IBAN));
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}