
#include <algorithm>
#include <functional>
// *********************************************************************************************************
// ******************************************** helper *****************************************************
// *********************************************************************************************************

template<typename ShieldPoints, typename AttackPower>
class Starship {
protected:
    ShieldPoints shieldPoints;
public:

    virtual ~Starship() = default;

    explicit Starship(ShieldPoints shieldPoints) : shieldPoints(shieldPoints) {}

    virtual ShieldPoints getShieldPoints() {
        return this->shieldPoints;
    }

    virtual void takeDamage(AttackPower attackPower) {
        this->shieldPoints -= std::min(attackPower, this->shieldPoints);
    }

    virtual int aliveCount() {
        return getShieldPoints() > 0 ? 1 : 0;
    }
};


template<typename Speed>
class MovingStarship {
protected:
    Speed speed;
public:

    virtual ~MovingStarship() = default;

    explicit MovingStarship(Speed speed) : speed(speed) {}

    Speed getSpeed() const {
        return speed;
    }
};

template<typename AttackPower>
class AttackerStarship {
protected:
    AttackPower attackPower;
public:

    virtual ~AttackerStarship() = default;

    AttackerStarship(AttackPower attackPower) :
        attackPower(attackPower) {}

    AttackPower getAttackPower() const {
        return attackPower;
    }
};


// *********************************************************************************************************
// ******************************************** rebelfleet *************************************************
// *********************************************************************************************************


template<typename ShieldPoints, typename Speed, typename AttackPower>
class RebelStarship :
    public Starship<ShieldPoints, AttackPower>,
    public MovingStarship<Speed> {

protected:

public:
    virtual ~RebelStarship() = default;

    RebelStarship(ShieldPoints shp, Speed sp) :
        MovingStarship<Speed>(sp),
        Starship<ShieldPoints, AttackPower>(shp) {}


};

template<typename ShieldPoints, typename Speed, typename AttackPower>
class Explorer :
    public RebelStarship<ShieldPoints, Speed, AttackPower> {
public:
    virtual ~Explorer() = default;

    Explorer(ShieldPoints shp, Speed sp) :
        RebelStarship<ShieldPoints, Speed, AttackPower>(shp, sp) {}
};

template<typename ShieldPoints, typename Speed, typename AttackPower>
class AggressiveRebel :
    public AttackerStarship<AttackPower>,
    public RebelStarship<ShieldPoints, Speed, AttackPower> {
public:
    virtual ~AggressiveRebel() = default;

    AggressiveRebel(ShieldPoints shp, Speed sp, AttackPower ap) :
        RebelStarship<ShieldPoints, Speed, AttackPower>(shp, sp), AttackerStarship<AttackPower>(ap) {}
};

template<typename ShieldPoints, typename Speed, typename AttackPower>
using StarCruiser = AggressiveRebel<ShieldPoints, Speed, AttackPower>;

template<typename ShieldPoints, typename Speed, typename AttackPower>
using XWing = AggressiveRebel<ShieldPoints, Speed, AttackPower>;

template<typename ShieldPoints, typename Speed, typename AttackPower>
XWing<ShieldPoints, Speed, AttackPower> createXWing(ShieldPoints shp, Speed sp, AttackPower ap) {
    return XWing<ShieldPoints, Speed, AttackPower>(shp, sp, ap);
}

template<typename ShieldPoints, typename Speed, typename AttackPower>
StarCruiser<ShieldPoints, Speed, AttackPower> createStarCruiser(ShieldPoints shp, Speed sp, AttackPower ap) {
    return StarCruiser<ShieldPoints, Speed, AttackPower>(shp, sp, ap);
}

template<typename ShieldPoints, typename Speed>
Explorer<ShieldPoints, Speed, ShieldPoints> createExplorer(ShieldPoints shp, Speed sp) {
    return Explorer<ShieldPoints, Speed, ShieldPoints>(shp, sp);
}


// *********************************************************************************************************
// ******************************************** imperialfleet **********************************************
// *********************************************************************************************************

template<typename ShieldPoints, typename AttackPower>
class ImperialStarship : public AttackerStarship<AttackPower>, public Starship<ShieldPoints, AttackPower> {
public:
    virtual ~ImperialStarship() = default;

    ImperialStarship(ShieldPoints shileldPoints, AttackPower attackPower) :
        AttackerStarship<AttackPower>(attackPower),
        Starship<ShieldPoints, AttackPower>(shileldPoints) {}
};

template<typename ShieldPoints, typename AttackPower>
using DeathStar = ImperialStarship<ShieldPoints, AttackPower>;

template<typename ShieldPoints, typename AttackPower>
using ImperialDestroyer = ImperialStarship<ShieldPoints, AttackPower>;

template<typename ShieldPoints, typename AttackPower>
using TIEFighter = ImperialStarship<ShieldPoints, AttackPower>;

template<typename ShieldPoints, typename AttackPower>
DeathStar<ShieldPoints, AttackPower> createDeathStar(ShieldPoints shp, AttackPower ap) {
    return DeathStar<ShieldPoints, AttackPower>(shp, ap);
}

template<typename ShieldPoints, typename AttackPower>
ImperialDestroyer<ShieldPoints, AttackPower> createImperialDestroyer(ShieldPoints shp, AttackPower ap) {
    return ImperialDestroyer<ShieldPoints, AttackPower>(shp, ap);
}

template<typename ShieldPoints, typename AttackPower>
TIEFighter<ShieldPoints, AttackPower> createTIEFighter(ShieldPoints shp, AttackPower ap) {
    return TIEFighter<ShieldPoints, AttackPower>(shp, ap);
}



template<typename ShieldPoints, typename AttackPower>
class Squadron : public AttackerStarship<AttackPower>, public Starship<ShieldPoints, AttackPower> {
private:

    using Ship = ImperialStarship<ShieldPoints, AttackPower>;


    struct AttackPowerMapper {
        AttackPower operator()(Ship &s){
            return s.getAttackPower();
        }
    };

    template<typename R, typename T, typename M>
    T reduce_vector(std::vector<R> &vec, M mapper) {
        T t;
        for(auto &s: vec){
            t += mapper(s);
        }
        return t;
    }

public:
    virtual ~Squadron() = default;

    Squadron(std::vector<Ship> ships) :
        AttackerStarship<AttackPower>(reduce_vector<Ship, AttackPower, AttackPowerMapper>(ships, AttackPowerMapper())),
        Starship<ShieldPoints, AttackPower>(0) {}
};


// *********************************************************************************************************
// ******************************************** battle *****************************************************
// *********************************************************************************************************
