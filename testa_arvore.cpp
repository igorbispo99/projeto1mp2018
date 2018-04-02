#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "arvore.h"

TEST_CASE("Testando construtores", "[arvore]") {
  arvores::Arvore arvore_teste("arquivo_teste");
}