#ifndef JNP6_IMPERIAL
#define JNP6_IMPERIAL
#include "helper.h"

class ImperialStarship : public AttackerStarship, public Starship {
 public:
  virtual ~ImperialStarship() = default;

  ImperialStarship(Starship::ShieldPoints shileldPoints, Starship::AttackPower attackPower) :
      AttackerStarship(attackPower),
      Starship(shileldPoints) {}
};

using DeathStar = ImperialStarship;

using ImperialDestroyer = ImperialStarship;


using TIEFighter = ImperialStarship;

class Squadron : public ImperialStarship {
 private:
  std::vector<std::shared_ptr<ImperialStarship>> ships;

  template<typename R, typename T, typename M>
  T map_sum_vec(T init, std::vector<R> &vec, M mapper) {
    T t = init;
    for (auto &s: vec) {
      t += mapper(s);
    }
    return t;
  }

 public:
  Squadron(std::vector<std::shared_ptr<ImperialStarship>> sh) :
      ships(sh),
      ImperialStarship(
          map_sum_vec(0, sh, [](auto &s) { return s->getShield(); }),
          map_sum_vec(0, sh, [](auto &s) { return s->getAttackPower(); })) {

  }

  int getAliveCount() override {
    return map_sum_vec(0, ships, [](auto &s) { return s->getAliveCount(); });
  }

  void takeDamage(AttackerStarship::AttackPower attackPower) override {
    for (const auto &sh : ships) {
      sh->takeDamage(attackPower);
    }
    shieldPoints = map_sum_vec(0, ships, [](auto &s) { return s->getShield(); });
  }

};

std::shared_ptr<DeathStar> createDeathStar(Starship::ShieldPoints shp, Starship::AttackPower ap) {
  return std::make_shared<DeathStar>(shp, ap);
}

std::shared_ptr<ImperialDestroyer> createImperialDestroyer(Starship::ShieldPoints shp, Starship::AttackPower ap) {
  return std::make_shared<ImperialDestroyer>(shp, ap);
}

std::shared_ptr<TIEFighter> createTIEFighter(Starship::ShieldPoints shp, Starship::AttackPower ap) {
  return std::make_shared<TIEFighter>(shp, ap);
}

std::shared_ptr<Squadron> createSquadron(std::vector<std::shared_ptr<ImperialStarship>> sh) {
  return std::make_shared<Squadron>(std::move(sh));
}

#endif // JNP6_IMPERIAL


