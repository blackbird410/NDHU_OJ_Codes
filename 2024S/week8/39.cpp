// http://blog.csdn.net/shuangde800/article/details/11271011

#include <algorithm>
#include <iostream>
#include <vector>

class TrainManager {
private:
    std::vector<int> carWeights;

public:
    void inputCarWeights(int nCars) {
        carWeights.resize(nCars);
        for (int i = 0; i < nCars; ++i) {
            std::cin >> carWeights[i];
        }
    }

    int getLongestTrain() {
        int n = carWeights.size();
        if (n == 0) return 0;

        std::vector<int> LIS, LDS;
        int maxLen = 0;

        for (int i = n - 1; i >= 0; --i) {
            int len1, len2;

            auto it = std::lower_bound(LDS.begin(), LDS.end(), carWeights[i]);
            if (it == LDS.end()) {
                LDS.push_back(carWeights[i]);
                len2 = LDS.size();
            } else {
                *it = carWeights[i];
                len2 = it - LDS.begin() + 1;
            }

            it = std::lower_bound(LIS.begin(), LIS.end(), -carWeights[i]);
            if (it == LIS.end()) {
                LIS.push_back(-carWeights[i]);
                len1 = LIS.size();
            } else {
                *it = -carWeights[i];
                len1 = it - LIS.begin() + 1;
            }

            maxLen = std::max(maxLen, len1 + len2 - 1);
        }

        return maxLen;
    }

    void cleanStation() {
        carWeights.clear();
    }
};

int main() {
    int testCases = 0;
    TrainManager manager;

    std::cin >> testCases;
    while (testCases > 0) {
        int nCars;
        std::cin >> nCars;
        manager.inputCarWeights(nCars);
        std::cout << manager.getLongestTrain() << std::endl;
        manager.cleanStation();
        --testCases;
    }

    return 0;
}
