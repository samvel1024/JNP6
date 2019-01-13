#ifndef JNP6_BATTLE
#define JNP6_BATTLE

#include <iostream>
#include "imperialfleet.h"
#include "rebelfleet.h"
#include <exception>

/**
 * The implementation of battle time
 * Provides method for checking if battle should take place now,
 * as well as methods to increment, reset, and manipulate time range.
 *
 * To provide a specific implementation for battle timing use SpaceBattle::Builder::battleTimer
 * @tparam T
 */
template<typename T>
class BattleTimer {
 protected:
  T now;
  T max;
 public:

  virtual ~BattleTimer() = default;

  virtual void set_start(T t) {
    now = t;
  }

  virtual void max_time(T t) {
    max = t;
  };

  virtual void tick(T t) {
    now = (now + t) % (max + 1);
  };

  virtual bool should_attack() = 0;
};

template<typename T>
class DefaultBattleTimer : public BattleTimer<T> {
 public:
  bool should_attack() override {
    return (this->now % 5 != 0) && (this->now % 2 == 0 || this->now % 3 == 0);
  }
};

class SpaceBattle {
 public:

  using Time = int;

  class Builder {
   private:
    std::vector<std::shared_ptr<ImperialStarship>> imperials;
    std::vector<std::shared_ptr<RebelStarship>> rebels;
    Time start_time;
    Time max_time;
    std::shared_ptr<BattleTimer<Time>> timer = std::make_shared<DefaultBattleTimer<Time>>();

    void validate(bool predicate, const std::string &msg) {
      if (!predicate) {
        throw std::invalid_argument(msg);
      }
    }

   public:
    virtual Builder &ship(const std::shared_ptr<RebelStarship> &r) {
      validate(r != nullptr, "Ship cannot be null");
      rebels.push_back(r);
      return *this;
    }

    virtual Builder &ship(const std::shared_ptr<ImperialStarship> &i) {
      validate(i != nullptr, "Ship cannot be null");
      imperials.push_back(i);
      return *this;
    }

    virtual Builder &startTime(const Time t) {
      validate(t >= 0, "Time cannot be negative");
      start_time = t;
      return *this;
    }

    virtual Builder &maxTime(const Time t) {
      validate(t >= 0, "Time cannot be negative");
      max_time = t;
      return *this;
    }

    virtual Builder &battleTimer(const std::shared_ptr<BattleTimer<Time>> &t) {
      validate(t != nullptr, "Timer cannot be null");
      timer = t;
      std::cout << "Assigned\n";
      return *this;
    }

    virtual SpaceBattle build() {
      validate(start_time <= max_time, "Max time cannot be less than start time");
      timer->set_start(start_time);
      timer->max_time(max_time);
      return SpaceBattle(timer, imperials, rebels);
    }

  };

 private:
  std::vector<std::shared_ptr<ImperialStarship>> imperials;
  std::vector<std::shared_ptr<RebelStarship>> rebels;
  std::shared_ptr<BattleTimer<Time>> timer;
  SpaceBattle(
      std::shared_ptr<BattleTimer<Time>> t,
      std::vector<std::shared_ptr<ImperialStarship>> imp,
      std::vector<std::shared_ptr<RebelStarship>> reb)
      : timer(std::move(t)), imperials(std::move(imp)), rebels(std::move(reb)) {
  }

  template<typename Ships>
  size_t count(Ships &v) const {
    size_t ans = 0;
    for (const auto &sh: v) {
      ans += sh->getAliveCount();
    }
    return ans;
  }

  void start_battle() {
    for (const auto &i : imperials) {
      for (const auto &r: rebels) {
        if (i->getShield() > 0 && r->getShield() > 0) {
          r->takeDamage(i->getAttackPower());
          r->defend(*i);
        }
      }
    }
  }

 public:

  void tick(Time t) {
    size_t reb = count(rebels);
    size_t imp = count(imperials);

    if (reb + imp == 0) {
      std::cout << "DRAW" << std::endl;
    } else if (reb == 0) {
      std::cout << "IMPERIUM WON" << std::endl;
    } else if (imp == 0) {
      std::cout << "REBELLION WON" << std::endl;
    } else {
      if (timer->should_attack()) {
        start_battle();
      }
      timer->tick(t);
    }
  }

  size_t countRebelFleet() const {
    return count(rebels);
  }

  size_t countImperialFleet() const {
    return count(imperials);
  }

};

#endif // JNP6_BATTLE


