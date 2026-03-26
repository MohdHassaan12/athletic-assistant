
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
    printf("\nExercise Recommendation:\n");

    if (age < 18)
    {
        printf("Consult a fitness expert for exercise recommendations for individuals under 18.\n");
        return;
    }

    if (bmi < 18.5)
    {
        printf("\nRecommended Exercise: Strength training and weight gain exercises.\n");
    }
    else if (bmi >= 18.5 && bmi <= 24.9)
    {
        printf("\nRecommended Exercise: Cardiovascular exercises and strength training for maintenance.\n");
    }
    else
    {
        printf("\nRecommended Exercise: Cardiovascular exercises and weight loss exercises.\n");
    }

    switch (fitnessLevel)
    {
        case 1:
            printf("\nFitness Level: Beginner\n");
            printf("Recommendation: Start with low-intensity exercises and gradually increase intensity.\n");
            break;
        case 2:
            printf("\nFitness Level: Intermediate\n");
            printf("Recommendation: Incorporate moderate-intensity exercises with intervals of high intensity.\n");
            break;
        case 3:
            printf("\nFitness Level: Advanced\n");
            printf("Recommendation: Engage in high-intensity exercises and interval training.\n");
            break;
        default:
            printf("\nInvalid fitness level input.\n");
            break;
    }
}


int main()
{
    float weight, height,target_weight, daily_calories,metre,h;
    int age,n,feet,w,fitnessLevel,gender,activityLevel,exit=0,weeks;
    float bmr, bmi,inch,kilogram,time,stamina,totalWeight,gainPerWeek,lossPerWeek;
    char athName[50], climate,health_status,choice,emp;

    system("clear");

    printf("\t\t\t\t\t\t\t\tHello, I'm Athletic.astt!\n");
    printf("\t\t\t\t\t\t\tReady to assist you towards healthier you.\n");

    printf("\n\t\t\t\t\t\tMay I have your name, please? ");
    fgets(athName, sizeof(athName), stdin);
    int len = strlen(athName);
    if (athName[len - 1] == '\n')
    {
        athName[len - 1] = '\0';
    }

    system("clear");
    printf("\t\t\t\t\t\t\t\t\t\t\t\tAthletic.astt!");

    printf("\n\n\nHey %s, let's get started:\n",athName);

    printf("\nWhat's your gender (1: MALE / 2: FEMALE): ");
    scanf("%d", &gender);

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Enter your height(in centimeters): ");
    scanf("%f",&h);

    printf("Enter your weight(in Kilograms): ");
    scanf("%f", &weight);

    system("clear");
    printf("\t\t\t\t\t\t\t\t\t\t\t\tAthletic.astt!");

    printf("\n\nThank You, for providing all the information. \n\n");

    printf("\nPress any key to Continue");
    scanf(" %c",&emp);

    system("clear");

    printf("\t\t\t\t\t\t\t\t\t\t\t\tAthletic.astt!");

    height = h/100;
    if (gender == 1)
    {
        bmr = 66 + (13.75 * weight) + (5 * height) - (6.75 * age);
    }
     else
    {
        bmr = 655 + (9.56 * weight) + (1.85 * height) - (4.68 * age);
    }
    bmi = weight / (height * height);
    daily_calories = (target_weight * 25) + ((age - 30) * 5);


    printf("\nFollowing are the keys for available function :");
    printf("\n'b' for BMI & BMR.");
    printf("\n'w' for Weight Gain/Loss.");
    printf("\n's' to know your Stamina.");
    printf("\n'd' to get recommended Diet Plan.");
    printf("\n'e' to get recommended Exercise Plan.");
    printf("\n'q' to Quit.");

    while(!exit) {
        printf("\n\nEnter desired key. ");
        scanf(" %c",&choice);
        getchar();

        switch (choice)
        {
            case 'b':
                printf("\n\nYour Body Mass Index (BMI) is %.2f\n", bmi);
                printf("\nYour BMR is %.2f calories per day.\n", bmr);
                if (bmi < 18.5)
                {
                    printf("You are underweight.\n");
                    printf("Eat a balanced diet with plenty of fruits and vegetables.\n");
                }
                else if (bmi >= 18.5 && bmi < 25)
                {
                    printf("You are at a healthy weight.\n");
                    printf("Maintain your healthy eating habits and exercise regularly.\n");
                }
                else if (bmi >= 25 && bmi < 30)
                {
                    printf("You are overweight.\n");
                    printf("Eat a balanced diet with fewer calories and exercise regularly.\n");
                }
                else
                {
                    if (bmi >= 30 && bmi < 35)
                    {
                        printf("You are obese, and you are class I obese\n");
                    }
                    else if (bmi >= 35 && bmi < 40)
                    {
                        printf("You are obese, and you are class II obese\n");
                    }
                    else
                    {
                        printf("You are obese, and you are class III obese\n");
                    }

                    printf("Eat a balanced diet with fewer calories and exercise regularly.\n");
                }
                break;

            case 'w':
                printf("\nEnter your target weight in kilograms: ");
                scanf("%f", &target_weight);

                if (target_weight > weight)
                {
                    printf("Enter your desired weight gain per week: ");
                    scanf("%f", &gainPerWeek);

                    totalWeight = weight;
                    weeks = (target_weight - weight) / gainPerWeek;

                    printf("\nWeight Gain Program\n");
                    printf("====================\n");
                    printf("Current weight: %f\n", weight);
                    printf("Target weight: %f\n", target_weight);
                    printf("Desired gain per week: %f\n", gainPerWeek);
                    printf("According to your desired, You can reached your Target Weight in %d weeks\n", weeks);
                }
                else if (target_weight < weight)
                {
                    printf("Enter your desired weight loss per week: ");
                    scanf("%f", &lossPerWeek);

                    totalWeight = weight;
                    weeks = (weight - target_weight) / lossPerWeek;

                    printf("\nWeight Loss Program\n");
                    printf("====================\n");
                    printf("Current weight: %f\n", weight);
                    printf("Target weight: %f\n", target_weight);
                    printf("Desired loss per week: %f\n", lossPerWeek);
                    printf("According to your desired, You can reached your Target Weight in %d weeks\n", weeks);
                }
                printf("\nTo reach your target weight, you should consume %.2f calories per day.\n", daily_calories);
                break;

            case 's':
            printf("\nEnter the time it took you to run 1 kilometer in minutes: ");
            scanf("%f", &time);
            stamina = 0.8 * (220 - age) + 0.2 * (weight / time) - 3;
            printf("Your stamina is: %f", stamina);


            case 'd':
                //code for diet plan here
                printf("diet plan");
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
                printf("\n************ Recommended Daily Intake ************\n\n");
                printf("Calories: %.2f\n", recommendedCalories);
                printf("Fat: %.2f\n", recommendedFat);
                printf("Vitamins: %.2f\n", recommendedVitamins);
                printf("Protein: %.2f\n", recommendedProtein);
                printf("Carbohydrates: %.2f\n", recommendedCarbohydrates);

                // If the person's BMI is in the healthy range, print a healthy diet plan.
                if (bmi < 18.5)
                {
                    printf("Here is a healthy diet plan for you:\n");
                    printf("Breakfast:\n");
                    printf("\t\t* %s (2 servings)\n", foods[0].name);
                    printf("\t\t* %s\n", foods[2].name);
                    printf("\t\t* %s\n", foods[14].name);
                    printf("\t\t* %s\n", foods[11].name);
                    printf("\t\t* %s\n", foods[9].name);
                    printf("Lunch:\n");
                    printf("\t\t* %s (1 serving)\n", foods[3].name);
                    printf("\t\t* %s\n", foods[4].name);
                    printf("\t\t* %s\n", foods[15].name);
                    printf("\t\t* %s\n", foods[10].name);
                    printf("Dinner:\n");
                    printf("\t\t* %s (1 serving)\n", foods[6].name);
                    printf("\t\t* %s\n", foods[5].name);
                    printf("\t\t* %s\n", foods[12].name);
                    printf("\t\t* %s\n", foods[16].name);
                }
                else if (bmi >= 18.5 && bmi <= 24.9)
                {
                    printf("Here is a healthy diet plan for you:\n");
                    printf("Breakfast:\n");
                    printf("\t\t* %s\n", foods[0].name);
                    printf("\t\t* %s\n", foods[1].name);
                    printf("\t\t* %s\n", foods[2].name);
                    printf("Lunch:\n");
                    printf("\t\t* %s\n", foods[3].name);
                    printf("\t\t* %s\n", foods[4].name);
                    printf("\t\t* %s\n", foods[5].name);
                    printf("Dinner:\n");
                    printf("\t\t* %s\n", foods[6].name);
                    printf("\t\t* %s\n", foods[7].name);
                    printf("\t\t* %s\n", foods[8].name);
                }
                else
                {
                    // If the person's BMI is not in the healthy range, print a diet plan to help them lose weight.
                    printf("Here is a diet plan to help you lose weight:\n");
                    printf("Breakfast:\n");
                    printf("\t\t* %s\n", foods[0].name);
                    printf("\t\t* %s\n", foods[2].name);
                    printf("Lunch:\n");
                    printf("\t\t* %s\n", foods[3].name);
                    printf("\t\t* %s\n", foods[4].name);
                    printf("Dinner:\n");
                    printf("\t\t* %s\n", foods[6].name);
                    printf("\t\t* %s\n", foods[8].name);
                }
                 break;

            case 'e':
            printf("\nEnter your fitness level (1: Beginner, 2: Intermediate, 3: Advanced): ");
            scanf("%d", &fitnessLevel);
            recommendExercise(age, bmi, fitnessLevel);
            break;

            case 'q':
                exit = 1;
                printf("\nreport here");
                //code for report here
                break;

            default :
                printf("Invalid choice. Please enter correct key.\n");
                break;
        }
        printf("\n");
    }

    return 0;
}
