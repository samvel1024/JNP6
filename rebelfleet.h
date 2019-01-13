#ifndef JNP6_REBEL
#define JNP6_REBEL
#include "helper.h"

class RebelStarship :
    public Starship,
    public MovingStarship {

 protected:

 public:
  ~RebelStarship() override = default;

  RebelStarship(Starship::ShieldPoints shp, MovingStarship::Speed sp) :
      MovingStarship(sp),
      Starship(shp) {}

  virtual void defend(Starship &attacker) = 0;

};


class Explorer :
    public RebelStarship {
 public:
  virtual ~Explorer() = default;

  Explorer(Starship::ShieldPoints shp, MovingStarship::Speed sp) :
      RebelStarship(shp, sp) {}

  void defend(Starship &attacker) override {
    // Do nothing
  }
};

class AggressiveRebel :
    public AttackerStarship,
    public RebelStarship {
 public:
  virtual ~AggressiveRebel() = default;

  AggressiveRebel(Starship::ShieldPoints shp, MovingStarship::Speed sp, Starship::AttackPower ap) :
      RebelStarship(shp, sp), AttackerStarship(ap) {}

  void defend(Starship &attacker) override {
    attacker.takeDamage(this->attackPower);
  }
};

using StarCruiser = AggressiveRebel;

using XWing = AggressiveRebel;

std::shared_ptr<XWing> createXWing(Starship::ShieldPoints shp, MovingStarship::Speed sp, Starship::AttackPower ap) {
  return std::make_shared<XWing>(shp, sp, ap);
}

std::shared_ptr<StarCruiser> createStarCruiser(Starship::ShieldPoints shp,
                                               MovingStarship::Speed sp,
                                               Starship::AttackPower ap) {
  return std::make_shared<StarCruiser>(shp, sp, ap);
}

std::shared_ptr<Explorer> createExplorer(Starship::ShieldPoints shp, MovingStarship::Speed sp) {
  return std::make_shared<Explorer>(shp, sp);
}

#endif // JNP6_REBEL
