#include "Dailyhub/Core/dotenv.hpp"

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

// Exemplo de função que você quer testar (pode estar em outro arquivo .h/.cpp)
std::string saudacao(const std::string& nome) {
  if (nome.empty()) {
    return "Olá, Mundo!";
  } else {
    return "Olá, " + nome + "!";
  }
}

int soma(int a, int b) {
  return a + b;
}

bool ehPar(int numero) {
  return (numero % 2 == 0);
}

std::vector<int> filtraPares(const std::vector<int>& numeros) {
  std::vector<int> pares;
  for (int numero : numeros) {
    if (ehPar(numero)) {
      pares.push_back(numero);
    }
  }
  return pares;
}

// Testes usando Google Test
TEST(SaudacaoTest, NomeVazio) {
  ASSERT_EQ("Olá, Mundo!", saudacao(""));
}

TEST(SaudacaoTest, NomeValido) {
  ASSERT_EQ("Olá, João!", saudacao("João"));
}

TEST(SomaTest, NumerosPositivos) {
  ASSERT_EQ(5, soma(2, 3));
}

TEST(SomaTest, NumerosNegativos) {
  ASSERT_EQ(-5, soma(-2, -3));
}

TEST(EhParTest, NumeroPar) {
  ASSERT_TRUE(ehPar(4));
}

TEST(EhParTest, NumeroImpar) {
  ASSERT_FALSE(ehPar(5));
}

TEST(FiltraParesTest, ListaVazia) {
  std::vector<int> numeros = {};
  std::vector<int> paresEsperados = {};
  ASSERT_EQ(paresEsperados, filtraPares(numeros));
}

TEST(FiltraParesTest, ListaComParesEImpares) {
  std::vector<int> numeros = {1, 2, 3, 4, 5, 6};
  std::vector<int> paresEsperados = {2, 4, 6};
  ASSERT_EQ(paresEsperados, filtraPares(numeros));
}

TEST(FiltraParesTest, ListaSomenteImpares) {
  std::vector<int> numeros = {1, 3, 5, 7};
  std::vector<int> paresEsperados = {};
  ASSERT_EQ(paresEsperados, filtraPares(numeros));
}

TEST(FiltraParesTest, ListaSomentePares) {
  std::vector<int> numeros = {2, 4, 6, 8};
  std::vector<int> paresEsperados = {2, 4, 6, 8};
  ASSERT_EQ(paresEsperados, filtraPares(numeros));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
