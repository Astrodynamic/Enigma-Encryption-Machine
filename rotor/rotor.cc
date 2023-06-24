#include "rotor.h"

Rotor::Rotor(const std::vector<std::uint8_t> &config, std::uint8_t shift)
    : Primitive(config), m_shift(shift) {}

Rotor::Rotor(const Rotor &other) : Primitive(other) { *this = other; }

Rotor::Rotor(Rotor &&other) : Primitive(other) { *this = std::move(other); }

Rotor &Rotor::operator=(const Rotor &other) {
  if (this != &other) {
    this->m_config = other.m_config;
    this->m_shift = other.m_shift;
  }
  return *this;
}

Rotor &Rotor::operator=(Rotor &&other) {
  if (this != &other) {
    this->m_config = std::move(other.m_config);
    this->m_shift = std::move(other.m_shift);
  }
  return *this;
}

[[nodiscard]] std::uint8_t Rotor::Map(const std::uint8_t input) {
  return this->m_config[static_cast<std::uint8_t>(input + this->m_shift)];
}

[[nodiscard]] std::uint8_t Rotor::Reverse(const std::uint8_t input) {
  auto item = std::find(this->m_config.begin(), this->m_config.end(), input);
  return static_cast<std::uint8_t>(item - this->m_config.begin()) -
         this->m_shift;
}

const std::uint8_t &Rotor::GetShift() const { return m_shift; }

void Rotor::SetShift(std::uint8_t shift) { this->m_shift = shift; }

void Rotor::Rotate() { ++this->m_shift; }