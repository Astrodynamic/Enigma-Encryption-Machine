#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>

#include "reflector.h"
#include "rotor.h"

class EnigmaMachine {
 public:
  EnigmaMachine() = default;
  EnigmaMachine(const EnigmaMachine &other) = delete;
  EnigmaMachine(EnigmaMachine &&other) = delete;
  EnigmaMachine &operator=(const EnigmaMachine &other) = delete;
  EnigmaMachine &operator=(EnigmaMachine &&other) = delete;
  ~EnigmaMachine() = default;

  void EncryptFile(const std::filesystem::path file);
  void DecryptFile(const std::filesystem::path file);
  void SaveConfig(const std::filesystem::path file);
  void LoadConfig(const std::filesystem::path file);
  void Generate(const std::size_t rotors);

 private:
  static std::random_device rd;
  static std::mt19937 gen;
  static std::uniform_int_distribution<std::uint8_t> dist;

  std::vector<std::size_t> m_rotate_config;
  std::vector<Rotor> m_rotors;
  Reflector m_reflector;

  void ReadWrite(std::ifstream &ifs, std::ofstream &ofs);
};