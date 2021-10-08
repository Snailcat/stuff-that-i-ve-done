#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <compare>
#include <algorithm>

class Competition {
public:
    Competition(const std::string& compName, double compPrize)
        : compName(compName), compPrize(compPrize) {}
    virtual std::string toString() {
        return std::string("Competition name: " + compName + "\nThe prize is: " + std::to_string(compPrize));
    }
    auto operator <=>(const Competition& other) const { return compPrize <=> other.compPrize; }
    std::string getCompName() { return compName; }
    double getCompPrice() { return compPrize; }
    virtual ~Competition() = default;

private:
    std::string compName;
    double compPrize;
};

class Biatlon : public Competition {
public:
    Biatlon(const std::string& compName, double compPrize, const int resultScore)
        : resultScore(resultScore), Competition(compName,compPrize) {}
    virtual std::string toString() override {
        return Competition::toString() + "\nShot targets: " + std::to_string(resultScore);
    }
    int getResultScore() { return resultScore; }
    virtual ~Biatlon() = default;
private:
    size_t resultScore;
};

class SkiRace : public Biatlon {
public:
    SkiRace(const std::string& compName, double compPrize,
        const int resultScore, std::size_t finishTime)
        : finishTime(finishTime), Biatlon(compName, compPrize, resultScore) {}
    virtual std::string toString() override {
        return Biatlon::toString() + "\nFastest time: " + std::to_string(finishTime);
    }
    virtual ~SkiRace() = default;
private:
    std::size_t finishTime;
};
template<typename T>
void printVectorToString(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << "----------------------------\n";
        std::cout << elem->toString() << std::endl;
        std::cout << "----------------------------\n";
    }
}

int main() {
    std::vector<std::unique_ptr<Competition>> competitions;
    competitions.emplace_back(std::make_unique<SkiRace>("Sorevnovania Gonki", 3000, 100, 300));
    competitions.emplace_back(std::make_unique<Biatlon>("Postrelat po mishenyam na lizah))))", 4000, 120));
    competitions.emplace_back(std::make_unique<Biatlon>("Ruzhia delayt buh", 3000, 400));
    std::cout << "\nSort by competition name\n";
    auto nameComparator = [](const auto& l, const auto& r) {return l->getCompName() < r->getCompName(); };
    std::sort(competitions.begin(), competitions.end(), nameComparator);
    printVectorToString(competitions);
    std::cout << "\nSort by competition prize\n";
    auto soundComparator = [](const auto& l, const auto& r) {return l->getCompPrice() < r->getCompPrice(); };
    std::sort(competitions.begin(), competitions.end(), soundComparator);
    printVectorToString(competitions);
    return 0;
}
