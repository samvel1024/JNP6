

#include "battle.h"
#include "imperialfleet.h"
#include "rebelfleet.h"
#include <cassert>
#include <vector>
#include <numeric>
#include <iostream>

int main() {
  auto ex = createExplorer(10, 20);
  assert(ex->getShield() == 10);
  assert(ex->getSpeed() == 20);

  auto xw = createXWing(10, 100, 1000);
  assert(xw->getShield() == 10);
  assert(xw->getSpeed() == 100);
  assert(xw->getAttackPower() == 1000);

  auto f = createTIEFighter(50, 9);

  assert(f->getAttackPower() == 9);
  assert(f->getShield() == 50);
  auto ds = createDeathStar(1, 2);
//  auto sq = Squadron<int, int>({ds, f});

  auto xwing = createXWing(100, 300000, 50);
  auto explorer = createExplorer(150, 400000);
  auto cruiser = createStarCruiser(1234, 100000, 11);
  auto deathStar = createDeathStar(10000, 75);
  auto fighter = createTIEFighter(50, 9);
  auto destroyer = createImperialDestroyer(150, 20);
  auto squadron = createSquadron({deathStar, fighter});

  auto battle = SpaceBattle::Builder()
      .ship(squadron)
      .startTime(2)
      .maxTime(23)
      .ship(xwing)
      .ship(explorer)
      .build();

//  std::vector<ImperialStarship<int, int>> vec{createTIEFighter(1, 2), createImperialDestroyer(2, 3)};

}