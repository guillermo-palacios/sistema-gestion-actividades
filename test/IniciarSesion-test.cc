#include "usuario.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::StartsWith;

TEST(Usuario, InicioSesion1) {

  std::string nombre="Juan", apellido="Perez";
  Usuario u(nombre, apellido);
  std::string dni="15519424J";
  std::string contrasena="MiContrasenia";
  std::string contrasena_director="empty";

  EXPECT_TRUE(u.IniciarSesion(dni, contrasena, contrasena_director));
}
TEST(Usuario, InicioSesion2) {

  std::string nombre="Juan", apellido="Perez";
  Usuario u(nombre, apellido);
  std::string dni="53209440K";
  std::string contrasena="UnaContraseniaVieja";
  std::string contrasena_director="986532";

  EXPECT_TRUE(u.IniciarSesion(dni, contrasena, contrasena_director));
}
TEST(Usuario, InicioSesion3) {

  std::string nombre="Juan", apellido="Perez";
  Usuario u(nombre, apellido);
  std::string dni="53209440K";
  std::string contrasena="UnaContraseniaVieja";
  std::string contrasena_director="123456";

  EXPECT_FALSE(u.IniciarSesion(dni, contrasena, contrasena_director));
}
TEST(Usuario, InicioSesion4) {

  std::string nombre="Juan", apellido="Perez";
  Usuario u(nombre, apellido);
  std::string dni="53218440K";
  std::string contrasena="UnaContraseniaVieja";
  std::string contrasena_director="986532";

  EXPECT_FALSE(u.IniciarSesion(dni, contrasena, contrasena_director));
}
TEST(Usuario, InicioSesion5) {

  std::string nombre="Juan", apellido="Perez";
  Usuario u(nombre, apellido);
  std::string dni="53209440K";
  std::string contrasena="UnaContraseniaNueva";
  std::string contrasena_director="986532";

  EXPECT_FALSE(u.IniciarSesion(dni, contrasena, contrasena_director));
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}