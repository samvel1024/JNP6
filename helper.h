#ifndef JNP6_HELPER
#define JNP6_HELPER

#include <vector>

class Starship {
 public:
  using ShieldPoints = int;
  using AttackPower = int;
 protected:
  ShieldPoints shieldPoints;
 public:

  virtual ~Starship() = default;

  explicit Starship(ShieldPoints shieldPoints) : shieldPoints(shieldPoints) {}

  virtual ShieldPoints getShield() const {
    return this->shieldPoints;
  }

  virtual void takeDamage(AttackPower attackPower) {
    this->shieldPoints -= std::min(attackPower, this->shieldPoints);
  }

  virtual int getAliveCount() const {
    return getShield() > 0 ? 1 : 0;
  }
};

class MovingStarship {
 public:
  using Speed = int;
 protected:
  Speed speed;
 public:

  virtual ~MovingStarship() = default;

  explicit MovingStarship(Speed speed) : speed(speed) {}

  Speed getSpeed() const {
    return speed;
  }
};

class AttackerStarship {
 public:
  using AttackPower = Starship::AttackPower;
 protected:
  AttackPower attackPower;
 public:

  virtual ~AttackerStarship() = default;

  AttackerStarship(AttackPower attackPower) :
      attackPower(attackPower) {}

  virtual AttackPower getAttackPower() const {
    return attackPower;
  }
};

#endif // JNP6_HELPER
