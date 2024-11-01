#include <iostream>
#include <string>
using namespace std;


int main()
{
    // Declaring Variables
    int odometerStart;
    int odometerEnd;
    int rentalDays;
    int startMonth;
    double rentalCharge = 0;
    string customerName;
    string luxuryCar;
    const int luxuryCarRent = 75;
    const int nonluxuryCarRent = 45;
    const double costPerMileRegular = 0.33;
    const double costPerMileSpecial = 0.27;
    const double costPerMileOver600 = 0.21;


    // Asking customer for odometer reading at start of rental
    cout << "Odometer at start: ";
    cin >> odometerStart;
    if (odometerStart < 0)
    {
        cout << "---" << endl;
        cout << "The starting odometer reading must not be negative." << endl;
        return 1;
    }

    // Asking customer for odometer reading at end of rental
    cout << "Odometer at end: ";
    cin >> odometerEnd;
    if (odometerEnd < odometerStart)
    {
        cout << "---" << endl;
        cout << "The ending odometer reading must be at least as large as the starting reading." << endl;
        return 1;
    }
    
    // Asking customer for the number of days the car was rented
    cout << "Rental Days: ";
    cin >> rentalDays;
    //cin.ignore(10000, '\n'); 
    if (rentalDays < 0)
    {
        cout << "---" << endl;
        cout << "The number of rental days must be positive." << endl;
        return 1;
    }

    // Asking customer for their name
    cout << "Customer Name: ";    
    getline(cin, customerName);
    if (customerName.length() == 0)
    {
        cout << "---" << endl;
        cout << "You must enter a customer name." << endl;
        return 1;
    }

    // Asking customer whether or not the car is a luxury car
    cout << "Luxury Car (y/n): ";    
    cin >> luxuryCar;
    if (luxuryCar != "y" && luxuryCar != "n")
    {
        cout << "---" << endl;
        cout << "You must enter y or n." << endl;
        return 1;
    }

    // Asking customer the month the car was rented 
    cout << "Starting Month (1=Jan, 2=Feb, etc.): ";    
    cin >> startMonth;
    if (startMonth <= 0 || startMonth > 12)
    {
        cout << "---" << endl;
        cout << "The month number must be in the range 1 through 12." << endl;
        return 1;
    }

    // Set to display 2 digits after decimal point
    cout.setf(ios::fixed);
	cout.precision(2);

    // Calculating total rental charge
    if (luxuryCar == "y")
    {
        rentalCharge += luxuryCarRent * rentalDays;
    } else {
        rentalCharge += nonluxuryCarRent * rentalDays;
    }

    int odometerDiff = odometerEnd - odometerStart;

    if (odometerDiff > 600)
    {
        rentalCharge += (odometerDiff - 600) * costPerMileOver600;
        odometerDiff = 600;
    }

    if (odometerDiff > 100)
    {
        if (startMonth == 12 || startMonth == 1 || startMonth == 2 || startMonth == 3)
        {
            rentalCharge += (odometerDiff - 100) * costPerMileRegular;
            odometerDiff = 100;
            rentalCharge += odometerDiff * costPerMileRegular;
        } else {
            rentalCharge += (odometerDiff - 100) * costPerMileSpecial;
            odometerDiff = 100;
            rentalCharge += odometerDiff * costPerMileRegular;
        }
    } else {
        rentalCharge += odometerDiff * costPerMileRegular;
    }
    
    //Printing total rental charge
    cout << "---" << endl;    
    cout << "The rental charge for " << customerName << " is $" << rentalCharge << endl;

}
