#include "director.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::StartsWith;

TEST(Director, ExpulsarAlumno1) {
  std::string dni = "26829726L";
  std::string nombre = "Antonio";
  std::string apellido = "Matas";
  std::string contrasena = "1234";
  std::string contrasena_director = "986532";
  Director d(dni, nombre, apellido, contrasena, contrasena_director);


  EXPECT_TRUE(d.ExpulsarAlumno(actividad, dni));
}
TEST(Director, ExpulsarAlumno2) {
  std::string dni = "26829725L";
  std::string nombre = "Pepe";
  std::string apellido = "Grillo";
  std::string contrasena = "1234";
  std::string contrasena_director = "986534";
  Director d(dni, nombre, apellido, contrasena, contrasena_director);


  EXPECT_FALSE(d.ExpulsarAlumno(actividad, dni));
}
TEST(Director, ExpulsarAlumno3) {
  std::string dni = "26829726P";
  std::string nombre = "Antonio";
  std::string apellido = "Matas";
  std::string contrasena = "1234";
  std::string contrasena_director = "986542";
  Director d(dni, nombre, apellido, contrasena, contrasena_director);


  EXPECT_FALSE(d.ExpulsarAlumno(actividad, dni));
}
TEST(Director, ExpulsarAlumno4) {
  std::string dni = "26828726L";
  std::string nombre = "Antonio";
  std::string apellido = "Matas";
  std::string contrasena = "1234";
  std::string contrasena_director = "9865632";
  Director d(dni, nombre, apellido, contrasena, contrasena_director);


  EXPECT_FALSE(d.ExpulsarAlumno(actividad, dni));
}
TEST(Director, ExpulsarAlumno1) {
  std::string dni = "26829726L";
  std::string nombre = "Antonio";
  std::string apellido = "Federico";
  std::string contrasena = "123862";
  std::string contrasena_director = "986532";
  Director d(dni, nombre, apellido, contrasena, contrasena_director);


  EXPECT_FALSE(d.ExpulsarAlumno(actividad, dni));
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}