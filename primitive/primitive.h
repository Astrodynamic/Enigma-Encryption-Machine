#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

class Primitive {
 public:
  Primitive() = default;
  explicit Primitive(const std::vector<std::uint8_t> &config);
  explicit Primitive(const Primitive &other) = default;
  explicit Primitive(Primitive &&other) = default;
  Primitive &operator=(const Primitive &other) = default;
  Primitive &operator=(Primitive &&other) = default;
  virtual ~Primitive() = default;

  [[nodiscard]] virtual std::uint8_t Map(const std::uint8_t input) = 0;

  [[nodiscard]] const std::vector<std::uint8_t> &GetConfig() const;
  [[nodiscard]] static std::size_t GetConfigSize();

 protected:
  constexpr static std::size_t kConfigSize{
      static_cast<std::size_t>(std::numeric_limits<std::uint8_t>::max() + 1)};

  std::vector<std::uint8_t> m_config;
};
