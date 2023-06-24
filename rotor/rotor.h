#pragma once

#include <algorithm>
#include <iostream>

#include "primitive.h"

class Rotor final : virtual public Primitive {
 public:
  Rotor() = default;
  Rotor(const std::vector<std::uint8_t> &config, std::uint8_t shift);
  explicit Rotor(const Rotor &other);
  explicit Rotor(Rotor &&other);
  Rotor &operator=(const Rotor &other);
  Rotor &operator=(Rotor &&other);
  ~Rotor() = default;

  void SetShift(std::uint8_t shift);
  [[nodiscard]] const std::uint8_t &GetShift() const;

  [[nodiscard]] virtual std::uint8_t Map(
      const std::uint8_t input) final override;
  [[nodiscard]] std::uint8_t Reverse(const std::uint8_t input);

  void Rotate();

 private:
  std::uint8_t m_shift{0};
};