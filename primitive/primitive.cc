#include "primitive.h"

Primitive::Primitive(const std::vector<std::uint8_t> &config)
    : m_config{config} {}

const std::vector<std::uint8_t> &Primitive::GetConfig() const {
  return m_config;
}

[[nodiscard]] std::size_t Primitive::GetConfigSize() { return kConfigSize; }