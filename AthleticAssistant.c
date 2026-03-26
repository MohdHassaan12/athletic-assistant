#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct food
{
    char *name;
    int calories;
    int fat;
    int vitamins;
    int protein;
    int carbohydrates;
};
void recommendExercise(int age, float bmi, int fitnessLevel)
{
    printf("\n\t\t\t\t\t\t\t\t\t\t\tExercise Recommendation:\n");

    if (age < 18)
    {
        printf("\t\t\t\t\t\t\t\t\tConsult a fitness expert for exercise recommendations for individuals under 18.\n");
        return;
    }

    if (bmi < 18.5)
    {
        printf("\n\t\t\t\t\t\t\t\t\tRecommended Exercise: Strength training and weight gain exercises.\n");
    }
    else if (bmi >= 18.5 && bmi <= 24.9)
    {
        printf("\n\t\t\t\t\t\t\t\t\tRecommended Exercise: Cardiovascular exercises and strength training for maintenance.\n");
    }
    else
    {
        printf("\n\t\t\t\t\t\t\t\t\tRecommended Exercise: Cardiovascular exercises and weight loss exercises.\n");
    }

    switch (fitnessLevel)
    {
        case 1:
            printf("\n\t\t\t\t\t\t\t\t\t\tFitness Level: Beginner\n");
            printf("\n\t\t\t\t\t\t\t\t\t\tRecommendation: Start with low-intensity exercises and gradually increase intensity.\n");
            break;
        case 2:
            printf("\n\t\t\t\t\t\t\t\t\t\t\tFitness Level: Intermediate\n");
            printf("\t\t\t\t\t\t\t\t\tRecommendation: Incorporate moderate-intensity exercises with intervals of high intensity.\n");
            break;
        case 3:
            printf("\n\t\t\t\t\t\t\t\t\t\t\tFitness Level: Advanced\n");
            printf("\t\t\t\t\t\t\t\t\tRecommendation: Engage in high-intensity exercises and interval training.\n");
            break;
        default:
            printf("\n\t\t\t\t\t\t\t\t\t\t\tInvalid fitness level input.\n");
            break;
    }
}

int main()
{
    float weight, height,target_weight, daily_calories,metre,h;
    int age,n,feet,w,fitnessLevel,gender,activityLevel,exit=0,weeks;
    float bmr, bmi,inch,kilogram,time,stamina,totalWeight,gainPerWeek,lossPerWeek;
    char athName[50], climate,health_status,choice,emp,key[10];

    system("clear");
    printf("\t\t\t\t\t\t\t\t\t\t\t       Welcome to\n");
    printf("\n\t\t\t\t\t\t\t\t\t\t\t     \033[4m\033[1mAthletic.astt!\033[0m\n");
    printf("\n\n\t\t\t\t\t\t\t\t\t\tReady to assist you towards healthier you.\n");
    printf("\n\n\n\n\n\n\t\tMay I have your name, please? ");
    fgets(athName, sizeof(athName), stdin);
    int len = strlen(athName);
    if (athName[len - 1] == '\n')
    {
        athName[len - 1] = '\0';
    }

    system("clear");
    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\033[4m\033[1mAthletic.astt!\033[0m\n");
    printf("\n\n\n\t\tHey %s, let's get started:\n",athName);
    printf("\n\n\n\t\tWhat's your gender (1: MALE / 2: FEMALE): ");
    scanf("%d", &gender);
    printf("\n\n\t\tEnter your age: ");
    scanf("%d", &age);
    printf("\n\n\t\tEnter your height(in centimeters): ");
    scanf("%f",&h);
    printf("\n\n\t\tEnter your weight(in Kilograms): ");
    scanf("%f", &weight);
    system("clear");
    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\033[4m\033[1mAthletic.astt!\033[0m\n");
    printf("\n\n\n\tThank You, for providing all the information. \n\n");
    printf("\n\tPress any key to Continue: ");
    scanf(" %c",&emp);
    system("clear");


    height = h/100;
    if (gender == 1)
    {
        bmr = 66 + (13.75 * weight) + (5 * h)- (6.75 * age);
    }
     else
    {
        bmr = 655 + (9.56 * weight) + (1.85 * h) - (4.68 * age);
    }
    bmi = weight / (height * height);

    while(!exit)
    {
        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\033[4m\033[1mAthletic.astt!\033[0m\n\n\n");
        printf("\n\tFollowing are the keys for available function :");
        printf("\n\n\t\t'b' for BMI & BMR.");
        printf("\n\t\t'w' for Weight Gain/Loss.");
        printf("\n\t\t's' to know your Stamina.");
        printf("\n\t\t'd' to get recommended Diet Plan.");
        printf("\n\t\t'e' to get recommended Exercise Plan.");
        printf("\n\t\t'q' to Quit.");
        printf("\n\n\n\n\tEnter desired choice. ");
        scanf(" %c",&choice);
        getchar();

        switch (choice)
        {
            case 'b':
                    system("clear");
                    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\033[4m\033[1mAthletic.astt!\033[0m\n");
                    printf("\n\n\t\t\t\t\t\t\t\t\t\t\tYour Body Mass Index (BMI) is %.2f\n", bmi);
                    printf("\n\t\t\t\t\t\t\t\t\t\t\tYour BMR is %.2f calories per day.\n", bmr);

                    if (bmi < 18.5)
                    {
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tYou are underweight.\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tEat a balanced diet with plenty of fruits and vegetables.\n");
                    }

                    else if (bmi >= 18.5 && bmi < 25)
                    {
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tYou are at a healthy weight.\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tMaintain your healthy eating habits and exercise regularly.\n");
                    }

                    else if (bmi >= 25 && bmi < 30)
                    {
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tYou are overweight.\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tEat a balanced diet with fewer calories and exercise regularly.\n");
                    }

                    else
                    {
                        if (bmi >= 30 && bmi < 35)
                        {
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tYou are obese, and you are class I obese\n");
                        }
                        else if (bmi >= 35 && bmi < 40)
                        {
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tYou are obese, and you are class II obese\n");
                        }
                        else
                        {
                            printf("\n\t\t\t\t\t\t\t\t\t\t\tYou are obese, and you are class III obese\n");
                        }

                        printf("\n\t\t\t\t\t\t\t\t\t\t\tEat a balanced diet with fewer calories and exercise regularly.\n");
                    }
                    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\tPress any key to Continue: ");
                    scanf(" %c",&emp);
                    system("clear");

                    break;

            case 'w':
                    system("clear");
                    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\033[4m\033[1mAthletic.astt!\033[0m\n");
                    printf("\n\t\t\t\t\t\t\t\t\t\t  Enter your target weight in kilograms: ");
                    scanf("%f", &target_weight);

                    if (target_weight > weight)
                    {
                        printf("\n\t\t\t\t\t\t\t\t\t\t  Enter your desired weight gain per week: ");
                        scanf("%f", &gainPerWeek);

                        totalWeight = weight;
                        weeks = (target_weight - weight) / gainPerWeek;

                        printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t   Weight Gain Program\n");
                        printf("\t\t\t\t\t\t\t\t\t\t\t   ====================\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tCurrent weight: %f\n", weight);
                        printf("\t\t\t\t\t\t\t\t\t\t\tTarget weight: %f\n", target_weight);
                        printf("\t\t\t\t\t\t\t\t\t\t\tDesired gain per week: %f\n", gainPerWeek);
                        printf("\t\t\t\t\t\t\t\t\t\t\tAccording to your desired, You can reached your Target Weight in %d weeks\n", weeks);
                    }

                    else if (target_weight < weight)
                    {
                        printf("\n\t\t\t\t\t\t\t\t\t\t  Enter your desired weight loss per week: ");
                        scanf("%f", &lossPerWeek);

                        totalWeight = weight;
                        weeks = (weight - target_weight) / lossPerWeek;

                        printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\t   Weight Loss Program\n");
                        printf("\t\t\t\t\t\t\t\t\t\t\t   ====================\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tCurrent weight: %f\n", weight);
                        printf("\t\t\t\t\t\t\t\t\t\t\tTarget weight: %f\n", target_weight);
                        printf("\t\t\t\t\t\t\t\t\t\t\tDesired loss per week: %f\n", lossPerWeek);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tAccording to your desired, You can reached your Target Weight in %d weeks\n", weeks);
                    }
                    daily_calories = (target_weight * 25) + ((age - 30) * 5);
                    printf("\n\t\t\t\t\t\t\t\t\t\t\tTo reach your target weight, you should consume %.2f calories per day.\n", daily_calories);
                    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t\tPress any key to Continue: ");
                    scanf(" %c",&emp);
                    system("clear");
                    break;

            case 's':
                    system("clear");
                    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\033[4m\033[1mAthletic.astt!\033[0m\n");
                    printf("\n\n\t\t\t\t\t\t\t\t\t\t\tEnter the time it took you to run 1 kilometer in minutes: ");
                    scanf("%f", &time);
                    stamina = 0.8 * (220 - age) + 0.2 * (weight / time) - 3;
                    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t%s Your stamina is: %.2f", athName,stamina);
                    printf("\n\n\t\t\t\t\t\t\t\t\t\t\tPress any key to Continue: ");
                    scanf(" %c",&emp);
                    system("clear");
                    break;

            case 'd':
                    system("clear");
                    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\033[4m\033[1mAthletic.astt!\033[0m\n");
                    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t   DEIT PLAN");
                    struct food foods[] =
                    {
                        {"Oatmeal", 300, 5, 10, 5, 25},
                        {"Whole-wheat toast", 200, 2, 5, 5, 15},
                        {"Yogurt with berries", 150, 0, 5, 10, 20},
                        {"Salad with grilled chicken or fish", 300, 10, 10, 20, 15},
                        {"Soup and salad", 250, 5, 5, 10, 20},
                        {"Whole-wheat sandwich on whole-grain bread", 350, 10, 10, 15, 20},
                        {"Salmon with roasted vegetables", 400, 15, 10, 20, 25},
                        {"Chicken stir-fry with brown rice", 450, 10, 10, 20, 25},
                        {"Lentil soup", 300, 5, 10, 15, 20},
                        {"Apple", 95, 0, 25, 0, 25 },
                        {"Banana", 105, 0, 10, 1, 27 },
                        {"Orange", 62, 0, 53, 0, 15 },
                        {"Grapefruit", 42, 0, 35, 0, 13 },
                        {"Berries", 52, 0, 10, 1, 15 },
                        {"Peanut butter", 190, 16, 0, 7, 5 },
                        {"Eggs", 155, 13, 0, 13, 1 },
                        {"Chicken breast", 165, 3, 0,31, 0 },
                    };
                    // Calculate calories burned during running
                    float caloriesBurnedPerMin = 0.035 * weight;
                    int totalCaloriesBurned = caloriesBurnedPerMin * time;

                    // Calculate recommended daily intake based on calories burned
                    float recommendedCalories = 2000 + totalCaloriesBurned;
                    float recommendedFat = (0.3 * recommendedCalories) / 9;
                    float recommendedVitamins = 50;
                    float recommendedProtein = (0.15 * recommendedCalories) / 4;
                    float recommendedCarbohydrates = (0.55 * recommendedCalories) / 4;

                    // Print recommended daily intake
                    printf("\n\t\t\t\t\t\t\t\t\t\t    ***** Recommended Daily Intake *****\n\n");
                    printf("\n\t\t\t\t\t\t\t\t\t\tCalories: %.2f\n", recommendedCalories);
                    printf("\n\t\t\t\t\t\t\t\t\t\tFat: %.2f\n", recommendedFat);
                    printf("\n\t\t\t\t\t\t\t\t\t\tVitamins: %.2f\n", recommendedVitamins);
                    printf("\n\t\t\t\t\t\t\t\t\t\tProtein: %.2f\n", recommendedProtein);
                    printf("\n\t\t\t\t\t\t\t\t\t\tCarbohydrates: %.2f\n", recommendedCarbohydrates);
                    // If the person's BMI is in the healthy range, print a healthy diet plan.
                    if (bmi < 18.5)
                    {
                        printf("\n\t\t\t\t\t\t\t\t\t\tHere is a healthy diet plan for you:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tBreakfast:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s (2 servings)\n", foods[0].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[2].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[14].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[11].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[9].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tLunch:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s (1 serving)\n", foods[3].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[4].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[15].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[10].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tDinner:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s (1 serving)\n", foods[6].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[5].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[12].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[16].name);
                    }

                    else if (bmi >= 18.5 && bmi <= 24.9)
                    {
                        printf("\n\t\t\t\t\t\t\t\t\t\tHere is a healthy diet plan for you:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tBreakfast:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[0].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[1].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[2].name);
                        printf("\n\n\t\t\t\t\t\t\t\t\t\t\tLunch:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[3].name);
                        printf("\n\t\t\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[4].name);
                        printf("\n\t\t\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[5].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tDinner:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[6].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[7].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[8].name);
                    }

                    else
                    {
                        // If the person's BMI is not in the healthy range, print a diet plan to help them lose weight.
                        printf("\n\t\t\t\t\t\t\t\t\t\tHere is a healthy diet plan for you:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tBreakfast:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[0].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[2].name);
                        printf("\n\n\t\t\t\t\t\t\t\t\t\t\tLunch:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[3].name);
                        printf("\n\t\t\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[4].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\tDinner:\n");
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[6].name);
                        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t* %s\n", foods[8].name);
                    }
                    printf("\n\n\n\tPress any key to Continue: ");
                    scanf(" %c",&emp);
                    system("clear");
                    break;

            case 'e':
                    system("clear");
                    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\033[4m\033[1mAthletic.astt!\033[0m\n");
                    printf("\n\t\t\t\t\t\t\t\t\tEnter your fitness level (1: Beginner, 2: Intermediate, 3: Advanced): ");
                    scanf("%d", &fitnessLevel);
                    recommendExercise(age, bmi, fitnessLevel);
                    printf("\n\t\t\t\t\t\t\t\t\tPress any key to Continue: ");
                    scanf(" %c",&emp);
                    system("clear");
                    break;

            case 'q':
                    system("clear");
                    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\033[4m\033[1mAthletic.astt!\033[0m\n");
                    printf("\n\n\t\t\t\t\t\t\t\t\t\t%s, Thank you for using my athletic.astt program!\n", athName);
                    printf("\n\n\t\t\t\t\t\t\t\t\t\tI'm so glad that you're finding it helpful.\n");
                    printf("\n\n\t\t\t\t\t\t\t\t\t\tI wish you all the best in your fitness journey.\n\n\n\n\n\n\n\n\n\n");
                    exit = 1;
                    break;

            default :
                    system("clear");
                    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\033[4m\033[1mAthletic.astt!\033[0m\n");
                    printf("\n\tInvalid choice. Please enter correct key.\n");
                    printf("\n\tPress any key to Continue: ");
                    scanf(" %c",&emp);
                    system("clear");
                    break;
        }
        printf("\n");
    }
    return 0;
}
