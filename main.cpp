/*
This program will help you find out how much your normal weight is. In case of discrepancy, help with advice.
*/

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

enum BodyMassIndexes
{
    SEVERE_THINNESS = 16,
    MODERATE_THINNESS = 17,
    SLIGHT_THINNESS = 19,
    NORMAL_BODY_WEIGHT = 25,
    OVERWEIGHT = 30,
    FIRST_LEVEL_OBESITY = 35,
    SECOND_LEVEL_OBESITY = 40
};


void flush(istream& in)
{
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    in.clear();
}

void wait_for_enter()
{
    cout << "Press [Enter] to continue . . ." << endl;
    cin.get();
}

void print_advice(double normalBodyWeigthMin, double normalBodyWeigthMax)
{
    cout << "Your normal body weight between " << normalBodyWeigthMin << " and " << normalBodyWeigthMax << " kg." << endl;
    cout << "Increase your calorie intake until you reach the right weight." << endl;
}

void print_wrong_input()
{
    cout << "You do not have the correct input." << endl;
    cout << "Restart and pay more attention, please!" << endl;
}

double calculate_height_index(double height)
{
    return pow((height / 100.00), 2);
}

double calculate_normal_body_weight(double bodyWeight, double weightLimit)
{
    return bodyWeight - weightLimit;
}

double calculate_metabolism_value(double bodyWeight, double height, double age)
{
    return (bodyWeight * 10) + (height * 6.25) - (5.0 * age) - 161;
}

double calculate_calorie_consumption(double bodyWeight, double height, double age)
{
    return 655 + (9.57 * bodyWeight) + (1.77 * height) + (4.7 * age);
}

bool is_in_range(double value, int min, int max)
{
    return value <= min || value > max || (isnan(value) != 0);
}

int main()
{
    cout << "This program will help you find out how much your normal weight is." << endl;
    cout << "In case of discrepancy, help with advice!" << endl;
    cout << "Just follow the instructions!" << endl;
    cout << endl;

    double bodyWeight = 0.0;
    double height = 0.0;
    double age = 0.0;
    double reduceValue = 0.0;
    
    cout << "Enter your body weight (kg), may not be an integer: ";
    cin >> bodyWeight;

    if (is_in_range(bodyWeight, 0, 350)) {
        print_wrong_input();
        flush(cin);
        wait_for_enter();

        return -1;
    }

    cout << "Enter your height (cm), may not be an integer: ";
    cin >> height;

    if (is_in_range(height, 0, 250)) {
        print_wrong_input();
        flush(cin);
        wait_for_enter();

        return -1;
    }
    
    cout << "Enter your age, it can only be an integer: ";
    cin >> age;

    if (is_in_range(age, 0, 130)) {
        print_wrong_input();
        flush(cin);
        wait_for_enter();

        return -1;
    }

    cout << endl;

    int bodyMassIndex = 0;
    double normalBodyWeightMin = 0.0;
    double normalBodyWeightMax = 0.0;

    bodyMassIndex = (int)(bodyWeight / calculate_height_index(height));
    normalBodyWeightMin = SLIGHT_THINNESS * calculate_height_index(height);
    normalBodyWeightMax = NORMAL_BODY_WEIGHT * calculate_height_index(height);

    if (bodyMassIndex < SEVERE_THINNESS) {
        cout << "You are seriously skinny!" << endl;
        print_advice(normalBodyWeightMin, normalBodyWeightMax);
        flush(cin);
        wait_for_enter();

        return 0;
    }
    else if (bodyMassIndex < MODERATE_THINNESS) {
        cout << "You are moderately skinny!" << endl;
        print_advice(normalBodyWeightMin, normalBodyWeightMax);
        flush(cin);
        wait_for_enter();

        return 0;
    }
    else if (bodyMassIndex < SLIGHT_THINNESS) {
        cout << "You are a little skinny!" << endl;
        print_advice(normalBodyWeightMin, normalBodyWeightMax);
        flush(cin);
        wait_for_enter();

        return 0;
    }
    else if (bodyMassIndex < NORMAL_BODY_WEIGHT) {
        cout << "Your weight is completely normal. Keep it!" << endl;
        flush(cin);
        wait_for_enter();

        return 0;
    }
    else if (bodyMassIndex < OVERWEIGHT) {
        cout << "You are overweight!" << endl;
    }
    else if (bodyMassIndex < FIRST_LEVEL_OBESITY) {
        cout << "You suffer from first-level obesity!" << endl;
    }
    else if (bodyMassIndex < SECOND_LEVEL_OBESITY) {
        cout << "You suffer from second-level obesity!" << endl;
    }
    else {
        cout << "You are severely obese!" << endl;
    }

    cout << "Your normal body weight between " << normalBodyWeightMin << " and " << normalBodyWeightMax << " kg." << endl;
    cout << "You need to lose at least " << calculate_normal_body_weight(bodyWeight, normalBodyWeightMax) << " kg!" << endl;
    cout << "We recommended losing 0.5 kg per week, but you can deviate from this." << endl;
    cout << "Enter that how much you want to reduce (in gramm) on your body weight per week: ";
    cin >> reduceValue;

    if (is_in_range(reduceValue, 0, (int)calculate_normal_body_weight(bodyWeight, normalBodyWeightMin) * 1000)) {
        print_wrong_input();
        flush(cin);
        wait_for_enter();

        return -1;
    }
    
    cout << endl;

    double dailyMetabolismValue = calculate_metabolism_value(bodyWeight, height, (double)age);
    double dailyCalorieConsumption = calculate_calorie_consumption(bodyWeight, height, (double)age);
    double diff = dailyCalorieConsumption - reduceValue;

    cout << "Your daily metabolism value: " << dailyMetabolismValue  << " kcal" << endl;
    cout << "The value of metabolism shows how much you definitely need to eat for your body to function properly." << endl;
    cout << "If you eat less than this, your metabolism may slow down and so you may have the opposite effect," << endl;
    cout << "your weight loss may stop after a while, even though you eat less." << endl;
    cout << "In addition, if fasting persists, you can also count on muscle loss," << endl;
    cout << "as the body covers the lack of energy from muscle uptake!" << endl;
    cout << "Your hair may loss, the quality of your skin may deteriorate," << endl;
    cout << "and the density of your bones may decrease due to a lack of vitamins." << endl;
    cout << "So you should not eat less than this permanently!" << endl;

    cout << endl;

    cout << "Your daily calorie consumption value: " << dailyCalorieConsumption << " kcal" << endl;
    cout << "That is all you can eat a day to keep your weight from growing." << endl;
    cout << "Correct daily carbohydrates, proteins and greases distribution in %:" << endl;
    cout << "Carbohydrate = 55 %" << endl;
    cout << "Protein = 15 %" << endl;
    cout << "Greas = 30 %" << endl;

    cout << endl;

    double dailyCalorieReduceWithSport = dailyMetabolismValue - diff;
    double dailyCalorieReduceWithMeal = reduceValue - dailyCalorieReduceWithSport;

    if (dailyCalorieReduceWithSport > 0) {
        cout << "Reduce your daily caloric intake with: " << dailyCalorieReduceWithMeal << " kcal" << endl;
        cout << "Plus calorie: " << dailyCalorieReduceWithSport << " kcal" << endl;
        cout << "If you want to lose weight, you need to cover the difference between the two numbers with a workout." << endl;
        cout << "Calculate how many calories(the plus calorie x 7) you need to burn in a week with workout." << endl;
    }
    else if (dailyCalorieReduceWithSport <= 0) {  
        cout << "It is enough to pay attention to the meal, so reduce your daily caloric with: " << -dailyCalorieReduceWithSport << " kcal" << endl;
    }

    flush(cin);
    wait_for_enter();
    return 0;
}

