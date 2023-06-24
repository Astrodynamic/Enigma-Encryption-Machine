#include <gtest/gtest.h>

#include "machine.h"

TEST(ENIGMA, Enigma_test_1) {
  std::filesystem::path path_0{"config"};
  std::filesystem::path path_1{"file"};
  std::filesystem::path path_2{"file_encoded"};
  std::filesystem::path path_3{"file_encoded_decoded"};

  EnigmaMachine enigma;

  ASSERT_NO_THROW(enigma.Generate(3));
  ASSERT_NO_THROW(enigma.SaveConfig(path_0));
  ASSERT_NO_THROW(enigma.EncryptFile(path_1));
  ASSERT_NO_THROW(enigma.LoadConfig(path_0));
  ASSERT_NO_THROW(enigma.DecryptFile(path_2));

  std::ifstream f1(path_1), f2(path_3);
  std::string content1((std::istreambuf_iterator<char>(f1)),
                       (std::istreambuf_iterator<char>())),
      content2((std::istreambuf_iterator<char>(f2)),
               (std::istreambuf_iterator<char>()));
  ASSERT_EQ(content1, content2);
}