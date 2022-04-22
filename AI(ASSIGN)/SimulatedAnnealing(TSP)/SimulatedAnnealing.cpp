#include <bits/stdc++.h>
#include "Tour.hpp"
#include "TourManager.hpp"

using namespace std;
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
double acceptanceProbability(int energy, int newEnergy, double temperature)
{
    if (newEnergy < energy)
    {
        return 1.0;
    }

    return exp((energy - newEnergy) / temperature);
}

int main(int argc, char *argv[])
{
    TourManager tourManager;

    // Create and add our cities
    City city = City(60, 200);
    tourManager.addCity(city);
    City city2 = City(180, 200);
    tourManager.addCity(city2);
    City city3 = City(80, 180);
    tourManager.addCity(city3);
    City city4 = City(140, 180);
    tourManager.addCity(city4);
    City city5 = City(20, 160);
    tourManager.addCity(city5);
    City city6 = City(100, 160);
    tourManager.addCity(city6);
    City city7 = City(200, 160);
    tourManager.addCity(city7);
    City city8 = City(140, 140);
    tourManager.addCity(city8);
    City city9 = City(40, 120);
    tourManager.addCity(city9);
    City city10 = City(100, 120);
    tourManager.addCity(city10);
    City city11 = City(180, 100);
    tourManager.addCity(city11);
    City city12 = City(60, 80);
    tourManager.addCity(city12);
    City city13 = City(120, 80);
    tourManager.addCity(city13);
    City city14 = City(180, 60);
    tourManager.addCity(city14);
    City city15 = City(20, 40);
    tourManager.addCity(city15);
    City city16 = City(100, 40);
    tourManager.addCity(city16);
    City city17 = City(200, 40);
    tourManager.addCity(city17);
    City city18 = City(20, 20);
    tourManager.addCity(city18);
    City city19 = City(60, 20);
    tourManager.addCity(city19);
    City city20 = City(160, 20);
    tourManager.addCity(city20);

    double temp = 10000;

    double coolingRate = 0.003;

    // initial random setting.
    Tour currentSolution = Tour(tourManager);
    currentSolution.generateIndividual();
    Tour best = Tour(currentSolution.getTour());

    std::cout << "Initial solution distance: " << best.getDistance() << std::endl;

    const int N0 = 500;
    const double P0 = 0.95;
    const double ln_p0 = log(P0);
    double sum_of_deltas = 0.0;
    for (int i = 0; i < N0;)
    {
        Tour newSolution = Tour(currentSolution.getTour());

        int tourPos1 = (int)(newSolution.tourSize() * fRand(0.0, 1.0));

        int tourPos2 = (int)(newSolution.tourSize() * fRand(0.0, 1.0));

        City citySwap1 = newSolution.getCity(tourPos1);
        City citySwap2 = newSolution.getCity(tourPos2);

        newSolution.setCity(tourPos2, citySwap1);
        newSolution.setCity(tourPos1, citySwap2);

        int currentEnergy = currentSolution.getDistance();
        int neighbourEnergy = newSolution.getDistance();

        if (neighbourEnergy > currentEnergy) // strictly postive transitions
        {
            sum_of_deltas += neighbourEnergy - currentEnergy;
            i++;
        }
    }

    double T0 = -(sum_of_deltas / N0) / ln_p0;
    std::cout << "Initial temperature: " << T0 << std::endl;
    temp = T0;

    while (temp > 1)
    {
        for (int markovChainLength = 0; markovChainLength < 50; markovChainLength++)
        {
            Tour newSolution = Tour(currentSolution.getTour());

            int tourPos1 = (int)(newSolution.tourSize() * fRand(0.0, 1.0));

            int tourPos2 = (int)(newSolution.tourSize() * fRand(0.0, 1.0));

            City citySwap1 = newSolution.getCity(tourPos1);
            City citySwap2 = newSolution.getCity(tourPos2);

            newSolution.setCity(tourPos2, citySwap1);
            newSolution.setCity(tourPos1, citySwap2);

            int currentEnergy = currentSolution.getDistance();
            int neighbourEnergy = newSolution.getDistance();

            if (acceptanceProbability(currentEnergy, neighbourEnergy, temp) > fRand(0.0, 1.0))
            {
                currentSolution = Tour(newSolution.getTour());
                markovChainLength++;
            }
        }

        if (currentSolution.getDistance() < best.getDistance())
        {
            best = Tour(currentSolution.getTour());
        }

        // std::cout << best.getDistance() << std::endl;
        temp *= 1 - coolingRate;

        cout << "\nCoordinates of the cities are:\n";
        for (int i = 0; i < best.tourSize(); i++)
        {
            cout << "X:" << best.getCity(i).getX() << " Y:" << best.getCity(i).getY() << "\n";
        }
        for (int i = 0; i < best.tourSize() - 1; i++)
        {

            cout << "\nCurrent edges:\n";
            cout << " From X:" << best.getCity(i).getX() << " Y:" << best.getCity(i).getY() << " To X:";
            cout << best.getCity(i + 1).getX() << " Y:" << best.getCity(i + 1).getY() << "\n";
        }
    }

    std::cout << "Final solution distance: " + std::to_string(best.getDistance()) << std::endl;
    std::cout << "Tour: " + best.toString() << std::endl;

    cout << "\nCoordinates of the cities are:\n";
    for (int i = 0; i < best.tourSize(); i++)
    {
        cout << "X:" << best.getCity(i).getX() << " Y:" << best.getCity(i).getY() << "\n";
    }
    for (int i = 0; i < best.tourSize() - 1; i++)
    {

        cout << "\nCurrent edges:\n";
        cout << " From X:" << best.getCity(i).getX() << " Y:" << best.getCity(i).getY() << " To X:";
        cout << best.getCity(i + 1).getX() << " Y:" << best.getCity(i + 1).getY() << "\n";
    }

    return 0;
}