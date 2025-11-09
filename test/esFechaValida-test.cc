#include <usuario-registrado.cc>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::StartsWith;

TEST(UsuarioRegistrado, esFechavalida1) {

  int dia = 14;
  int mes = 10;
  int anio = 2023;

  EXPECT_TRUE(esFechaValida(dia, mes, anio));
}
TEST(UsuarioRegistrado, esFechavalida2) {

  int dia = 34;
  int mes = 10;
  int anio = 2023;

  EXPECT_FALSE(esFechaValida(dia, mes, anio));
}
TEST(UsuarioRegistrado, esFechavalida3) {

  int dia = 14;
  int mes = 14;
  int anio = 2023;

  EXPECT_FALSE(esFechaValida(dia, mes, anio));
}
TEST(UsuarioRegistrado, esFechavalida4) {

  int dia = 14;
  int mes = 10;
  int anio = 2029;

  EXPECT_FALSE(esFechaValida(dia, mes, anio));
}
TEST(UsuarioRegistrado, esFechavalida5) {

  int dia = 15;
  int mes = 08;
  int anio = 2020;

  EXPECT_TRUE(esFechaValida(dia, mes, anio));
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}