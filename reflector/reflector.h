#pragma once

#include "primitive.h"

class Reflector final : virtual public Primitive {
 public:
  Reflector() = default;
  explicit Reflector(const std::vector<std::uint8_t> &config);
  explicit Reflector(const Reflector &other);
  explicit Reflector(Reflector &&other);
  Reflector &operator=(const Reflector &other);
  Reflector &operator=(Reflector &&other);
  ~Reflector() = default;

  [[nodiscard]] virtual std::uint8_t Map(
      const std::uint8_t input) final override;
};
