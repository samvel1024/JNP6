


#include "helper.h"
#include <cassert>
#include <vector>
#include <numeric>


int main() {
    auto  explorer = createExplorer(10, 20);
    assert(explorer.getShieldPoints() == 10);
    assert(explorer.getSpeed() == 20);

    auto xw = createXWing(10, 100, 1000);
    assert(xw.getShieldPoints() == 10);
    assert(xw.getSpeed() == 100);
    assert(xw.getAttackPower() == 1000);

    auto fighter = createTIEFighter(50, 9);

    assert(fighter.getAttackPower() == 9);
    assert(fighter.getShieldPoints() == 50);

    auto squadron = Squadron<int, int>({createDeathStar(1, 2), fighter});



    std::vector<ImperialStarship<int, int>> vec{createTIEFighter(1, 2), createImperialDestroyer(2, 3)};
}