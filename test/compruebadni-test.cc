#include <usuario-registrado.cc>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::StartsWith;

TEST(UsuarioRegistrado, dni1) {

  std::string dni="15519424J";
 

  EXPECT_TRUE(compruebadni(dni));
}
TEST(UsuarioRegistrado, dni2) {
  std::string dni="53209440K";
  

  EXPECT_TRUE(compruebadni(dni));
}
TEST(UsuarioRegistrado, dni3) {
  std::string dni="53509490K";
 

  EXPECT_FALSE(compruebadni(dni));
}
TEST(UsuarioRegistrado, dni4) {
  std::string dni="532184400";


  EXPECT_FALSE(compruebadni(dni));
}
TEST(UsuarioRegistrado, dni5) {
  std::string dni="53209440P";


  EXPECT_FALSE(compruebadni(dni));
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}