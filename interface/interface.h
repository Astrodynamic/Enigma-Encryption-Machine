#pragma once

#include "ainterface.h"
#include "machine.h"

class Interface final : virtual public AbstractInterface {
 public:
  Interface();
  explicit Interface(const Interface &other) = delete;
  explicit Interface(Interface &&other) = delete;
  Interface &operator=(const Interface &other) = delete;
  Interface &operator=(Interface &&other) = delete;
  ~Interface();

  virtual void Exec() final override;

 private:
  enum MenuFuncs : std::size_t {
    kMainFuncMenu = 0U,
    kLoadConf,
    kUnloadConf,
    kEncode,
    kDecode,
    kGenerate,
    kMenuFuncsAll
  };

  enum MenuItem : std::size_t {
    kIntroduction = 0U,
    kMainMenu,
    kLoadMenu,
    kGenerateMenu,
    kNotExistMenus,
    kCompletion
  };

  EnigmaMachine m_machine;

  void InitFuncMenus();
  bool RunProcessFile(
      std::function<void(const std::filesystem::path &path)> func);
};