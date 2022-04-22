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
    int number_of_cities;
    cout << "The cities must be entered in the format of coordinates in 2-d plane\n";
    cout << "Enter the number of cities:";
    cin >> number_of_cities;
    for (int i = 0; i < number_of_cities; i++)
    {
        int X, Y;
        cin >> X >> Y;
        City city = City(X, Y);
        tourManager.addCity(city);
    }

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