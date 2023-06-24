#include "reflector.h"

Reflector::Reflector(const std::vector<std::uint8_t> &config)
    : Primitive(config) {}

Reflector::Reflector(const Reflector &other) : Primitive(other) {
  *this = other;
}

Reflector::Reflector(Reflector &&other) : Primitive(other) {
  *this = std::move(other);
}

Reflector &Reflector::operator=(const Reflector &other) {
  if (this != &other) {
    this->m_config = other.m_config;
  }
  return *this;
}

Reflector &Reflector::operator=(Reflector &&other) {
  if (this != &other) {
    this->m_config = std::move(other.m_config);
  }
  return *this;
}

[[nodiscard]] std::uint8_t Reflector::Map(const std::uint8_t input) {
  return m_config[input];
}