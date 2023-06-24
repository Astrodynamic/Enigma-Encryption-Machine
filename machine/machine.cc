#include "machine.h"

std::random_device EnigmaMachine::rd;
std::mt19937 EnigmaMachine::gen(EnigmaMachine::rd());
std::uniform_int_distribution<std::uint8_t> EnigmaMachine::dist(
    std::numeric_limits<std::uint8_t>::min(),
    std::numeric_limits<std::uint8_t>::max());

void EnigmaMachine::EncryptFile(const std::filesystem::path file) {
  std::ifstream input(file, std::ios::binary);

  std::string file_n = file.stem().string();
  std::string file_e = file.extension().string();
  std::string file_p = std::string("_encoded");
  std::filesystem::path out_file = file;
  out_file.replace_filename(file_n + file_p + file_e);
  std::ofstream output(out_file, std::ios::binary);

  ReadWrite(input, output);
}

void EnigmaMachine::DecryptFile(const std::filesystem::path file) {
  std::ifstream input(file, std::ios::binary);

  std::string file_n = file.stem().string();
  std::string file_e = file.extension().string();
  std::string file_p = std::string("_decoded");
  std::filesystem::path out_file = file;
  out_file.replace_filename(file_n + file_p + file_e);
  std::ofstream output(out_file, std::ios::binary);

  ReadWrite(input, output);
}

void EnigmaMachine::ReadWrite(std::ifstream& ifs, std::ofstream& ofs) {
  std::uint8_t byte;
  while (ifs.read(reinterpret_cast<char*>(&byte), sizeof(std::uint8_t))) {
    for (auto& rotor : m_rotors) {
      byte = rotor.Map(byte);
    }

    byte = m_reflector.Map(byte);

    for (auto it = m_rotors.rbegin(); it != m_rotors.rend(); ++it) {
      byte = it->Reverse(byte);
    }
    ofs.write(reinterpret_cast<char*>(&byte), sizeof(std::uint8_t));

    m_rotors[0].Rotate();
    ++m_rotate_config[0];
    for (std::size_t i = 1U; m_rotate_config[i - 1] == 256U; ++i) {
      m_rotate_config[i - 1] = 0;
      m_rotate_config[i] += 1;
      m_rotors[i].Rotate();
    }
  }
}

void EnigmaMachine::SaveConfig(const std::filesystem::path file) {
  std::ofstream output(file, std::ios::binary);

  if (output.is_open()) {
    std::size_t c_size = Primitive::GetConfigSize() * sizeof(std::uint8_t);
    std::uint8_t r_size = static_cast<std::uint8_t>(m_rotors.size());

    output.write(reinterpret_cast<const char*>(&r_size), sizeof(std::uint8_t));
    output.write(reinterpret_cast<const char*>(m_rotate_config.data()),
                 r_size * sizeof(std::uint8_t));
    for (const auto& rotor : m_rotors) {
      output.write(reinterpret_cast<const char*>(rotor.GetConfig().data()),
                   c_size);
      output.write(reinterpret_cast<const char*>(&(rotor.GetShift())),
                   sizeof(std::uint8_t));
    }
    output.write(reinterpret_cast<const char*>(m_reflector.GetConfig().data()),
                 c_size);
  }
  output.close();
}

void EnigmaMachine::LoadConfig(const std::filesystem::path file) {
  std::ifstream input(file, std::ios::binary);

  if (input.is_open()) {
    std::uint8_t size{};
    input.read(reinterpret_cast<char*>(&size), sizeof(std::uint8_t));

    m_rotate_config.resize(size);
    input.read(reinterpret_cast<char*>(m_rotate_config.data()),
               size * sizeof(std::uint8_t));

    m_rotors.resize(size);

    std::uint8_t shift{};
    std::vector<std::uint8_t> config(Primitive::GetConfigSize());
    std::size_t c_size = Primitive::GetConfigSize() * sizeof(std::uint8_t);
    for (std::size_t idx = 0; idx < m_rotors.size() && input.good(); ++idx) {
      input.read(reinterpret_cast<char*>(config.data()), c_size);
      input.read(reinterpret_cast<char*>(&shift), sizeof(std::uint8_t));
      m_rotors[idx] = Rotor(config, shift);
    }
    input.read(reinterpret_cast<char*>(config.data()), c_size);
    m_reflector = Reflector(config);
  }
  input.close();
}

void EnigmaMachine::Generate(const std::size_t rotors) {
  m_rotate_config.resize(rotors, 0);
  m_rotors.resize(rotors);

  std::vector<std::uint8_t> config(Primitive::GetConfigSize());
  std::iota(config.begin(), config.end(), 0);

  for (std::size_t i = 0; i < rotors; ++i) {
    std::shuffle(config.begin(), config.end(), gen);
    m_rotors[i] = Rotor(config, dist(gen));
  }

  for (std::size_t i = 0; i < config.size(); ++i) {
    if (i != config[config[i]]) {
      auto item = find(config.begin(), config.end(), i);
      std::swap(config[item - config.begin()], config[config[i]]);
    }
  }
  m_reflector = Reflector(config);
}