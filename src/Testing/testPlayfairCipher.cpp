//! Unit Tests for MPAGSCipher PlayfairCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PlayfairCipher.hpp"

TEST_CASE("Playfair Cipher encryption", "[playfair]")
{
    PlayfairCipher pc{"playfairexample"};
    REQUIRE(pc.applyCipher("HIDETHEGOLDINTHETREESTUMP", CipherMode::Encrypt) == "BMODZBXDNABEKUDMUIXMMOUVIF");
}

TEST_CASE("Playfair Cipher decryption", "[playfair]")
{
    PlayfairCipher pc{"playfairexample"};
    REQUIRE(pc.applyCipher("BMODZBXDNABEKUDMUIXMMOUVIF", CipherMode::Decrypt) == "HIDETHEGOLDINTHETREXESTUMP");
}