#include "usuario-registrado.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::StartsWith;

TEST(UsuarioRegistrado, AnularPreinscripcion1) {

  std::string nombre="Juan", apellido="Perez";
  std::string dni="15519433J";
  std::string contrasena="MiContrasenia";
  UsuarioRegistrado ur(dni, nombre, apellido, contrasena);
  std::string nombreActividad="Curso en C";

  EXPECT_FALSE(ur.AnularPreinscripcion(nombreActividad, dni));
}

TEST(UsuarioRegistrado, AnularPreinscripcion2) {

  std::string nombre="Juan", apellido="Perez";
  std::string dni="66671441F";
  std::string contrasena="MiContrasenia";
  UsuarioRegistrado ur(dni, nombre, apellido, contrasena);
  std::string nombreActividad="No existe";

  EXPECT_FALSE(ur.AnularPreinscripcion(nombreActividad, dni));
}

TEST(UsuarioRegistrado, AnularPreinscripcion3) {

  std::string nombre="Juan", apellido="Perez";
  std::string dni="66671441F";
  std::string contrasena="MiContrasenia";
  UsuarioRegistrado ur(dni, nombre, apellido, contrasena);
  std::string nombreActividad="Paseo por la montana";

  EXPECT_TRUE(ur.AnularPreinscripcion(nombreActividad, dni));
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}