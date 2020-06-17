#ifndef GAMESYSTEM_H_
#define GAMESYSTEM_H_

class District;

class GameSystem {
public:
    GameSystem() {}
    virtual ~GameSystem() {}
    virtual void run(District* pDistrict) = 0;
};

#endif /* GAMESYSTEM_H_ */