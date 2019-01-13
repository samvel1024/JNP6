#include"battle.h"

int main() {
  auto r = createXWing(10, 300000, 10);
  auto i1 = createTIEFighter(10, 10);
  auto i2 = createTIEFighter(10, 10);
  auto s = createSquadron({i1, i2});

  auto battle = SpaceBattle::Builder()
      .ship(r)
      .ship(s)
      .startTime(2)
      .maxTime(1337)
      .build();

  battle.tick(3);//time==2,zachodziatak
  battle.tick(2);
}