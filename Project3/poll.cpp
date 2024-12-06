#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

//checks if stateCode is valid and returns true or false
bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NJ.NH.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  
            codes.find(stateCode) != string::npos);  
}

// function that checks if pollData is in right format
bool hasRightSyntax(string pollData)
{
    while(pollData.size() != 0)
    {
        char temp = tolower(pollData.at(0));
        if(isalpha(temp)) //checks if first char represent a party
        {
            if(isdigit(pollData.at(1))) //checks if item at index 1 is a digit
            {
                if(isdigit(pollData.at(2))) //checks if item at index 2 is a digit
                {
                    if(pollData.size() > 4)
                    {
                        // format stateCode for check
                        string temp2 = "";
                        temp2 += toupper(pollData.at(3));
                        temp2 += toupper(pollData.at(4));
                        
                        if(isValidUppercaseStateCode(temp2)) // checks stateCode
                        {   
                            pollData = pollData.substr(5, pollData.size()-5); // substr pollData to  unchecked poll data
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else { // case where vote is a 1 digit number
                    if (pollData.size() > 3)
                    {
                        string temp2 = "";
                        temp2 += toupper(pollData.at(2));
                        temp2 += toupper(pollData.at(3));
                        if(isValidUppercaseStateCode(temp2)) // checks stateCode
                        {
                            pollData = pollData.substr(4, pollData.size()-4); // substr pollData to unchecked poll data
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

// checks for 0s in the string
bool checkZeros(string pollData) 
{
    for (size_t i = 1; i < pollData.size();) //loops through poll data
    {
        if (pollData.at(i) == '0') // checks if pos at i is equal to 0
        {
            if (i + 1 < pollData.size() && pollData.at(i + 1) == '0') // checks for '00'
            {
                return true;
            }
            // checks if the '0' is alone by itself by checking in front and behind
            else if (i + 1 < pollData.size() && !isdigit(pollData.at(i + 1)) && (i == 0 || pollData.at(i - 1) != '0')) { 
                return true;
            }
        }
        // determine how much to add to i to place pos at first digit
        if (i + 2 < pollData.size() && isdigit(pollData.at(i + 1)) && isdigit(pollData.at(i + 2))) // case for 2 digit
        {
            i += 5;
        }
        else if (i + 1 < pollData.size() && isdigit(pollData.at(i + 1))) { // case for 1 digit
            i += 4;
        }
        else {
            return false;
        }
    }
    return false; 
}

// calculates the votes of the passed party in the pollData
int computeVotes(string pollData, char party, int& voteCount)
{
    if(!hasRightSyntax(pollData)) // returns 1 if pollData doesn't have the right syntax
    {
        return 1;
    } else if (!isalpha(party)){ // retruns 3 if the pary char isn't an abc letter 
        return 3;
    } else if (pollData.size() == 0) { // sets votes to 0 and return 0 is poll data is empty string
        voteCount = 0;
        return 0;
    } else if (checkZeros(pollData)) { // checks if there are 0s
        return 2;
    }
    voteCount = 0;
    for(string::size_type i = 0; i != pollData.size(); i++)
    {
        i = 0;
        if (pollData.size() == 0) // breaks if poll data is empty
        {
            break;
        }
        if(tolower(pollData.at(i)) == tolower(party)) // checks if given party char matches string char
        {
            if(isdigit(pollData.at(i+2))){ // checks if votes is 1 or 2 digit
                voteCount += stoi(pollData.substr(i+1,2)); //adds 2 digit vote
            } else {
                voteCount += stoi(pollData.substr(i+1,1)); //adds 1 digit vote
            }
        }
        if(isdigit(pollData.at(i+2))){  // checks if vote is 1 or 2 digit
            pollData = pollData.substr(i+5, pollData.size()-(i+5)); //substr pollData to unchecked poll data
        } else {
            pollData = pollData.substr(i+4, pollData.size()-(i+4)); // substr pollData to unchecked poll data
        }
    } 
    return 0;
}

// int main()
// {
//     assert(hasRightSyntax("R40TXD54CA") == true);  
//     assert(hasRightSyntax("D5MER1Me") == true);      
//     assert(hasRightSyntax("R40MXD54CA") == false);    
//     assert(hasRightSyntax("D55C") == false);          
//     assert(hasRightSyntax("") == true);   
//     int votes;
//     int result;

//     // Test 1: Empty pollData string
//     votes = 9999;
//     result = computeVotes("", 'D', votes);
//     assert(result == 0 && votes == 0);
//     cout << "Test 1 passed!" << endl;

//     // Test 2: Lowercase state codes and party
//     votes = 9999;
//     result = computeVotes("d28nyr40txd4hi", 'd', votes);
//     assert(result == 0 && votes == 32);
//     cout << "Test 2 passed!" << endl;

//     // Test 3: Invalid state code in the middle
//     votes = 9999;
//     result = computeVotes("D28NY@40TXD4HI", 'D', votes);
//     assert(result == 1 && votes == 9999);  // Invalid pollData
//     cout << "Test 3 passed!" << endl;

//     // Test 4: Valid pollData with non-alphabet character for party
//     votes = 9999;
//     result = computeVotes("D28NYR40TXD4HI", '@', votes);
//     assert(result == 3 && votes == 9999);  // Invalid party character
//     cout << "Test 4 passed!" << endl;

//     // Test 5: Valid pollData with zero votes
//     votes = 9999;
//     result = computeVotes("D00CA", 'D', votes);
//     assert(result == 2 && votes == 9999);  // Zero votes is invalid
//     cout << "Test 5 passed!" << endl;

//     // Test 6: Valid pollData, specific party count
//     votes = 9999;
//     result = computeVotes("D10TXR15CA", 'R', votes);
//     assert(result == 0 && votes == 15);
//     cout << "Test 6 passed!" << endl;

//     // Test 7: PollData with missing state code characters
//     votes = 9999;
//     result = computeVotes("D28N", 'D', votes);
//     assert(result == 1 && votes == 9999);  // Incomplete state code
//     cout << "Test 7 passed!" << endl;

//     // Test 8: Mixed case state codes
//     votes = 9999;
//     result = computeVotes("d28nYr40TxD4Hi", 'D', votes);
//     assert(result == 0 && votes == 32);
//     cout << "Test 8 passed!" << endl;
// }

void testone(int n)
{
    int v = 666;
    switch (n)
    {
                     default: {
        cout << "Bad argument" << endl;
            } break; case  1: {
        assert(!hasRightSyntax("R"));
            } break; case  2: {
        assert(!hasRightSyntax("3"));
            } break; case  3: {
        assert(!hasRightSyntax("#"));
            } break; case  4: {
        assert(!hasRightSyntax("3RID"));
            } break; case  5: {
        assert(!hasRightSyntax("73RID"));
            } break; case  6: {
        assert(!hasRightSyntax("CA3D"));
            } break; case  7: {
        assert(!hasRightSyntax("CA73D"));
            } break; case  8: {
        assert(!hasRightSyntax("RID3"));
            } break; case  9: {
        assert(!hasRightSyntax("RID73"));
            } break; case 10: {
        assert(!hasRightSyntax("3RI"));
            } break; case 11: {
        assert(!hasRightSyntax("RID"));
            } break; case 12: {
        assert(!hasRightSyntax("@3ID"));
            } break; case 13: {
        assert(!hasRightSyntax("*73ID"));
            } break; case 14: {
        assert(!hasRightSyntax("D3"));
            } break; case 15: {
        assert(!hasRightSyntax("DE"));
            } break; case 16: {
        assert(!hasRightSyntax("D$"));
            } break; case 17: {
        assert(!hasRightSyntax("D73"));
            } break; case 18: {
        assert(!hasRightSyntax("D7C"));
            } break; case 19: {
        assert(!hasRightSyntax("D7%"));
            } break; case 20: {
        assert(!hasRightSyntax("D738"));
            } break; case 21: {
        assert(!hasRightSyntax("D738CA"));
            } break; case 22: {
        assert(!hasRightSyntax("D007CA"));
            } break; case 23: {
        assert(!hasRightSyntax("D73C"));
            } break; case 24: {
        assert(!hasRightSyntax("D73%"));
            } break; case 25: {
        assert(!hasRightSyntax("D73C%"));
            } break; case 26: {
        assert(!hasRightSyntax("D73TV"));
            } break; case 27: {
        assert(!hasRightSyntax("D73Tv"));
            } break; case 28: {
        assert(!hasRightSyntax("D73tV"));
            } break; case 29: {
        assert(!hasRightSyntax("D73tv"));
            } break; case 30: {
        assert(!hasRightSyntax("D 54CA"));
            } break; case 31: {
        assert(!hasRightSyntax("D54 CA"));
            } break; case 32: {
        assert(!hasRightSyntax("R13MD6"));
            } break; case 33: {
        assert(!hasRightSyntax("R3MD6AR"));
            } break; case 34: {
        assert(!hasRightSyntax("R13MD6AR"));
            } break; case 35: {
        assert(!hasRightSyntax("D54CA#6UT"));
            } break; case 36: {
        assert(!hasRightSyntax("R16GAD3D3VT"));
            } break; case 37: {
        assert(!hasRightSyntax("R16GAD73D3VT"));
            } break; case 38: {
        assert(!hasRightSyntax("R16GAD738D3VT"));
            } break; case 39: {
        assert(!hasRightSyntax("R16GAD7MD3VT"));
            } break; case 40: {
        assert(!hasRightSyntax("R6UT,D4HI"));
            } break; case 41: {
        assert(!hasRightSyntax("R3WY D5NMD3VT"));
            } break; case 42: {
        assert(!hasRightSyntax("R3WYD5NM D3VT"));
            } break; case 43: {
        assert(hasRightSyntax(""));
            } break; case 44: {
        assert(hasRightSyntax("D4Ca"));
            } break; case 45: {
        assert(hasRightSyntax("D4cA"));
            } break; case 46: {
        assert(hasRightSyntax("D4ca"));
            } break; case 47: {
        assert(hasRightSyntax("D54CA"));
            } break; case 48: {
        assert(hasRightSyntax("D54Ca"));
            } break; case 49: {
        assert(hasRightSyntax("D54cA"));
            } break; case 50: {
        assert(hasRightSyntax("D54ca"));
            } break; case 51: {
        assert(hasRightSyntax("D9CA"));
            } break; case 52: {
        assert(hasRightSyntax("D4CA"));
            } break; case 53: {
        assert(hasRightSyntax("D0CA"));
            } break; case 54: {
        assert(hasRightSyntax("D89CA"));
            } break; case 55: {
        assert(hasRightSyntax("D09CA"));
            } break; case 56: {
        assert(hasRightSyntax("D00CA"));
            } break; case 57: {
        assert(hasRightSyntax("d4CA"));
            } break; case 58: {
        assert(hasRightSyntax("d54CA"));
            } break; case 59: {
        assert(hasRightSyntax("A4CA"));
            } break; case 60: {
        assert(hasRightSyntax("A54CA"));
            } break; case 61: {
        assert(hasRightSyntax("Z4CA"));
            } break; case 62: {
        assert(hasRightSyntax("Z42CA"));
            } break; case 63: {
        assert(hasRightSyntax("D3DC"));
            } break; case 64: {
        assert(hasRightSyntax("R3WYD7CT"));
            } break; case 65: {
        assert(hasRightSyntax("R3WYD7CTR4ID"));
            } break; case 66: {
        assert(hasRightSyntax("D54CAR11TNR40TX"));
            } break; case 67: {
        assert(hasRightSyntax("D54CAR4IDR6KSD12WA"));
            } break; case 68: {
        assert(hasRightSyntax("R3NDD7CTD8ORR4IDR3SDD4RI"));
            } break; case 69: {
        assert(computeVotes("QQ#3## 3QQ###", 'D', v) == 1);
            } break; case 70: {
        computeVotes("QQ#3## 3QQ###", 'D', v);
        assert(v == 666);
            } break; case 71: {
        assert(computeVotes("D0CA", 'D', v) == 2);
            } break; case 72: {
        computeVotes("D0CA", 'D', v);
        assert(v == 666);
            } break; case 73: {
        assert(computeVotes("D00CA", 'D', v) == 2);
            } break; case 74: {
        computeVotes("D00CA", 'D', v);
        assert(v == 666);
            } break; case 75: {
        assert(computeVotes("R3NDD7CTD0CAR3SD", 'D', v) == 2);
            } break; case 76: {
        assert(computeVotes("R40TXD28NYD00CAR11TN", 'D', v) == 2);
            } break; case 77: {
        assert(computeVotes("D0CA", 'R', v) == 2);
            } break; case 78: {
        assert(computeVotes("D00CA", 'R', v) == 2);
            } break; case 79: {
        assert(computeVotes("R3NDD7CTD0CAR3SD", 'R', v) == 2);
            } break; case 80: {
        assert(computeVotes("R40TXD28NYD00CAR11TN", 'R', v) == 2);
            } break; case 81: {
        assert(computeVotes("R4WV", '4', v) == 3);
            } break; case 82: {
        computeVotes("R4WV", '4', v);
        assert(v == 666);
            } break; case 83: {
        assert(computeVotes("R40TX", '5', v) == 3);
            } break; case 84: {
        computeVotes("R40TX", '5', v);
        assert(v == 666);
            } break; case 85: {
        int r = computeVotes("QQ#3## 3QQ###", '#', v);
        assert(r == 1  ||  r == 3);
            } break; case 86: {
        int r = computeVotes("D0CA", '%', v);
        assert(r == 2  ||  r == 3);
            } break; case 87: {
        assert(computeVotes("", 'R', v) == 0);
            } break; case 88: {
        computeVotes("", 'R', v);
        assert(v == 0);
            } break; case 89: {
        assert(computeVotes("R3SD", 'D', v) == 0);
            } break; case 90: {
        computeVotes("R3SD", 'D', v);
        assert(v == 0);
            } break; case 91: {
        assert(computeVotes("R3SD", 'R', v) == 0);
            } break; case 92: {
        computeVotes("R3SD", 'R', v);
        assert(v == 3);
            } break; case 93: {
        assert(computeVotes("r3SD", 'R', v) == 0  &&  v == 3);
            } break; case 94: {
        assert(computeVotes("R3SD", 'r', v) == 0  &&  v == 3);
            } break; case 95: {
        assert(computeVotes("r3SD", 'r', v) == 0  &&  v == 3);
            } break; case 96: {
        assert(computeVotes("D28NY", 'D', v) == 0);
            } break; case 97: {
        computeVotes("D28NY", 'D', v);
        assert(v == 28);
            } break; case 98: {
        assert(computeVotes("d28NY", 'D', v) == 0  &&  v == 28);
            } break; case 99: {
        assert(computeVotes("D28NY", 'd', v) == 0  &&  v == 28);
            } break; case 100: {
        assert(computeVotes("d28NY", 'd', v) == 0  &&  v == 28);
            } break; case 101: {
        assert(computeVotes("L6UT", 'D', v) == 0  &&  v == 0);
            } break; case 102: {
        assert(computeVotes("G11WA", 'D', v) == 0  &&  v == 0);
            } break; case 103: {
        assert(computeVotes("L6UT", 'L', v) == 0  &&  v == 6);
            } break; case 104: {
        assert(computeVotes("Y14WA", 'Y', v) == 0  &&  v == 14);
            } break; case 105: {
        assert(computeVotes("B3VTY6KSX4WV", 'Y', v) == 0  &&  v == 6);
            } break; case 106: {
        assert(computeVotes("D10MDD3DE", 'D', v) == 0  &&  v == 13);
            } break; case 107: {
        assert(computeVotes("R3NDD7CTD8ORR4IDR3SDD4RI", 'D', v) == 0  &&  v == 19);
            } break; case 108: {
        assert(computeVotes("R3NDD7CTD8ORR4IDR3SDD4RI", 'R', v) == 0  &&  v == 10);
            } break; case 109: {
        assert(computeVotes("R3NDD7CTD8ORR4IDR3SDD4RI", 'Z', v) == 0  &&  v == 0);
            } break; case 110: {
        assert(computeVotes("D54CAD12WAR40TXR10MOR11TND10MND28NY", 'D', v) == 0  &&  v == 104);
            } break; case 111: {
        assert(computeVotes("D54CAD12WAR40TXR10MOR11TND10MND28NY", 'R', v) == 0  &&  v == 61);
            } break; case 112: {
        assert(computeVotes("D54CAD12WAR40TXR10MOR11TND10MND28NY", 'Z', v) == 0  &&  v == 0);
            } break; case 113: {
        assert(computeVotes("D54CAD12WAR40TXR10MOR11TND10MND28NYR3NDD7CTD8ORR4IDR3SDD4RI", 'D', v) == 0  &&  v == 123);
            } break; case 114: {
        assert(computeVotes(
        "R3AKR6AKR9ALR11AZD54CAD10COD7CTD3DCD3DER30FLR16GAD4HIR6IAR4IDD19IL"
        "R11INR6KSR8KYR8LAD11MAD10MDD4MER15MID10MNR10MOR6MSR4MTR16NCR3NDR5NE"
        "D4NHD14NJD5NMR6NVD28NYR17OHR7OKD8ORR19PAD4RIR9SCR3SDR11TNR40TXR6UT"
        "D13VAD3VTD12WAR10WIR4WVR3WY", 'D', v) == 0  &&  v == 226);
            } break; case 115: {
        assert(computeVotes(
        "R3AKR6AKR9ALR11AZD54CAD10COD7CTD3DCD3DER30FLR16GAD4HIR6IAR4IDD19IL"
        "R11INR6KSR8KYR8LAD11MAD10MDD4MER15MID10MNR10MOR6MSR4MTR16NCR3NDR5NE"
        "D4NHD14NJD5NMR6NVD28NYR17OHR7OKD8ORR19PAD4RIR9SCR3SDR11TNR40TXR6UT"
        "D13VAD3VTD12WAR10WIR4WVR3WY", 'R', v) == 0  &&  v == 312);
            } break; case 116: {
        assert(computeVotes(
        "R3AKR6AKR9ALR11AZD54CAD10COD7CTD3DCD3DER30FLR16GAD4HIR6IAR4IDD19IL"
        "R11INR6KSR8KYR8LAD11MAD10MDD4MER15MID10MNR10MOR6MSR4MTR16NCR3NDR5NE"
        "D4NHD14NJD5NMR6NVD28NYR17OHR7OKD8ORR19PAD4RIR9SCR3SDR11TNR40TXR6UT"
        "D13VAD3VTD12WAR10WIR4WVR3WY", 'I', v) == 0  &&  v == 0);
            }
    }
}

int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed if there was no undefined behavior." << endl;
}