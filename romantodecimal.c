#include<stdio.h>
#include<string.h>

// Function to convert a Roman numeral to decimal
int romanToDecimal(char *roman) {
    int total = 0;
    int i = 0;
    while (roman[i] != '\0') {
        // Get value of current Roman character
        int current = 0;
        switch (roman[i]) {
            case 'I': current = 1; break;
            case 'V': current = 5; break;
            case 'X': current = 10; break;
            case 'L': current = 50; break;
            case 'C': current = 100; break;
            case 'D': current = 500; break;
            case 'M': current = 1000; break;
            default: return -1;  // Invalid Roman numeral
        }

        // Look ahead to next character
        int next = 0;
        if (roman[i+1] != '\0') {
            switch (roman[i+1]) {
                case 'I': next = 1; break;
                case 'V': next = 5; break;
                case 'X': next = 10; break;
                case 'L': next = 50; break;
                case 'C': next = 100; break;
                case 'D': next = 500; break;
                case 'M': next = 1000; break;
            }
        }

        // If current value is less than next, subtract it
        if (current < next) {
            total -= current;
        } else {
            total += current;
        }

        i++;  // Move to next character in the Roman numeral
    }

    return total;  // Return the decimal value
}





// Function to perform arithmetic operation
int performOperation(int num1, int num2, char operator) {
    if (operator == '+') {
        return num1 + num2;
    } else if (operator == '-') {
        return num1 - num2;
    } else if (operator == '*') {
        return num1 * num2;
    } else if (operator == '/') {
        return num1 / num2;
    } else {
        return -1;  // Invalid operator
    }
}





// Function to convert a number to words (basic version for numbers up to 9999)
void numberToWords(int num, char *result) {
    const char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    const char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    
    if (num == 0) {
        strcpy(result, "Zero");
        return;
    }

    // Handle thousands
    if (num >= 1000) {
        strcat(result, ones[num / 1000]);
        strcat(result, " Thousand ");
        num %= 1000;
    }

    // Handle hundreds
    if (num >= 100) {
        strcat(result, ones[num / 100]);
        strcat(result, " Hundred ");
        num %= 100;
    }

    // Handle tens and ones
    if (num >= 20) {
        strcat(result, tens[num / 10]);
        strcat(result, " ");
        num %= 10;
    } else if (num >= 10) {
        strcat(result, teens[num - 10]);
        return;
    }

    if (num > 0) {
        strcat(result, ones[num]);
    }
}





// Function to process and compute the expression from a line of input
void processExpression(char *line, FILE *outputFile) {
    char roman1[100], roman2[100], operator;
    int num1, num2, result;
    
    // Check if the line contains an operator
    if (sscanf(line, "%s %c %s", roman1, &operator, roman2) == 3) {
        // If the line contains two Roman numerals and an operator, process normally
        num1 = romanToDecimal(roman1);
        num2 = romanToDecimal(roman2);

        if (num1 == -1 || num2 == -1) {
            return;  // Skip invalid Roman numerals
        }

        result = performOperation(num1, num2, operator);
        if (result == -1) {
            return;  // Skip invalid operation
        }

        char resultInWords[200] = "";
        numberToWords(result, resultInWords);

        fprintf(outputFile, "%d = %s\n", result, resultInWords);
    } else {
        // If no operator is found, assume it's just a single Roman numeral
        int num = romanToDecimal(line);
        if (num != -1) {
            char resultInWords[200] = "";
            numberToWords(num, resultInWords);
            fprintf(outputFile, "%d = %s\n", num, resultInWords);
        }
    }
}





// Function to read from input file and process each line
void processFile(FILE *inputFile, FILE *outputFile) {
    char line[200];
    while (fgets(line, sizeof(line), inputFile)) {
        processExpression(line, outputFile);
    }
}





int main() {
    // Open the input file
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Input file not found.\n");
        return 1;
    }

    // Open the output file
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Unable to open output file.\n");
        fclose(inputFile);
        return 1;
    }

    // Process the file
    processFile(inputFile, outputFile);

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Processing complete. Results saved in Output.txt.\n");
    return 0;
}

final
