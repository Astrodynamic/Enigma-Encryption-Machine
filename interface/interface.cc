#include "interface.h"

const std::vector<std::string> Interface::AbstractInterface::m_menus{
    " -------------------------------------------------------------- \n"
    "|                          Enigma 1.0                          |\n"
    " -------------------------------------------------------------- \n",
    " -------------------------------------------------------------- \n"
    "|                       Select menu item                       |\n"
    " -------------------------------------------------------------- \n"
    "| 0. Exit                                                      |\n"
    "| 1. Loading the enigma configuration setting                  |\n"
    "| 2. Unloading the enigma configuration setting                |\n"
    "| 3. Information encoding                                      |\n"
    "| 4. Information decoding                                      |\n"
    "| 5. Genarate the enigma configuration setting                 |\n"
    " -------------------------------------------------------------- \n"
    " > ",
    " -------------------------------------------------------------- \n"
    "|                       Select menu item                       |\n"
    " -------------------------------------------------------------- \n"
    "| 0. Exit                                                      |\n"
    "| 1. Enter the full path to the file ...                       |\n"
    " -------------------------------------------------------------- \n"
    " > ",
    " -------------------------------------------------------------- \n"
    "|                       Select menu item                       |\n"
    " -------------------------------------------------------------- \n"
    "| 0. Exit                                                      |\n"
    "| 1. Enter number of rotors (1 - 255)                          |\n"
    " -------------------------------------------------------------- \n"
    " > ",
    " -------------------------------------------------------------- \n"
    "|             A file with that name does not exist             |\n"
    " -------------------------------------------------------------- \n",
    " -------------------------------------------------------------- \n"
    "|            Successful completion of the programme            |\n"
    " -------------------------------------------------------------- \n"};

Interface::Interface() {
  InitFuncMenus();
  ShowMenu(m_menus[MenuItem::kIntroduction]);
}

void Interface::InitFuncMenus() {
  m_funcs.resize(MenuFuncs::kMenuFuncsAll);

  m_funcs[MenuFuncs::kMainFuncMenu] = {
      std::bind(&Interface::Exit, this),
      std::bind(&Interface::RunMenu, this,
                std::ref(m_funcs[MenuFuncs::kLoadConf]), MenuItem::kLoadMenu),
      std::bind(&Interface::RunMenu, this,
                std::ref(m_funcs[MenuFuncs::kUnloadConf]), MenuItem::kLoadMenu),
      std::bind(&Interface::RunMenu, this,
                std::ref(m_funcs[MenuFuncs::kEncode]), MenuItem::kLoadMenu),
      std::bind(&Interface::RunMenu, this,
                std::ref(m_funcs[MenuFuncs::kDecode]), MenuItem::kLoadMenu),
      std::bind(&Interface::RunMenu, this,
                std::ref(m_funcs[MenuFuncs::kGenerate]),
                MenuItem::kGenerateMenu)};

  m_funcs[MenuFuncs::kLoadConf] = {
      std::bind(&Interface::Exit, this), [this]() -> bool {
        return RunProcessFile(std::bind(&EnigmaMachine::LoadConfig,
                                        std::ref(m_machine),
                                        std::placeholders::_1));
      }};

  m_funcs[MenuFuncs::kUnloadConf] = {
      std::bind(&Interface::Exit, this), [this]() -> bool {
        return RunProcessFile(std::bind(&EnigmaMachine::SaveConfig,
                                        std::ref(m_machine),
                                        std::placeholders::_1));
      }};

  m_funcs[MenuFuncs::kEncode] = {
      std::bind(&Interface::Exit, this), [this]() -> bool {
        return RunProcessFile(std::bind(&EnigmaMachine::EncryptFile,
                                        std::ref(m_machine),
                                        std::placeholders::_1));
      }};

  m_funcs[MenuFuncs::kDecode] = {
      std::bind(&Interface::Exit, this), [this]() -> bool {
        return RunProcessFile(std::bind(&EnigmaMachine::DecryptFile,
                                        std::ref(m_machine),
                                        std::placeholders::_1));
      }};

  m_funcs[MenuFuncs::kGenerate] = {std::bind(&Interface::Exit, this),
                                   [this]() -> bool {
                                     m_machine.Generate(CheckInputItem(0, 256));
                                     return false;
                                   }};
}

bool Interface::RunProcessFile(
    std::function<void(const std::filesystem::path& path)> func) {
  const auto [success, path]{CheckInputPathFile()};
  if (success) {
    func(path);
  } else {
    ShowMenu(m_menus[MenuItem::kNotExistMenus]);
  }
  return !success;
}

Interface::~Interface() { ShowMenu(m_menus[MenuItem::kCompletion]); }

void Interface::Exec() {
  RunMenu(m_funcs[MenuFuncs::kMainFuncMenu], MenuItem::kMainMenu);
}