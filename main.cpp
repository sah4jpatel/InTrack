#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

time_t now = time(0);

tm *ltm = localtime(&now);

int currYear = 1900+ltm->tm_year;

struct calendarItem
{
    string time;
    string name;
    string extraDetails;
    int importance;
    string activityType;
};
struct dayObj
{
    vector<calendarItem> activities;
    int dayIter;
    dayObj(int in) {dayIter = in;}
};

vector<vector<dayObj> > months;
string monthNames[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
string dayNames[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void loadMonths()
{
    for(int i = 1; i <= 12; i ++)
    {
        int dayInMonth = 0;
        if( i == 2)
        {
            if((currYear%400==0) || (currYear%4==0 && currYear%100!=0))	
                dayInMonth = 29;
            else	
                dayInMonth = 28;
        }
        //for months which has 31 days
        else if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 ||i == 10 || i==12)	
            dayInMonth = 31;
        else 		
            dayInMonth = 30;
        vector<dayObj> temp;
        for(int j = 1; j <= dayInMonth; j++)
        {
            tm time_in = { 0, 0, 0, j, i-1, currYear};
            time_t timeTemp = mktime(&time_in);
            tm *timeOut = localtime(&timeTemp);
            int iter = timeOut->tm_wday;
            temp.push_back(dayObj(iter));
        }
        months.push_back(temp);
    }
}

struct majorExam
{
    string date;
    string time;
    bool isFinal;
    string someDetails;
};

struct course
{
    private:
    int credits;
        string name;
        bool criticalTracking;
        bool elective;
        bool minor;
        bool genEd_or_audit;
        vector<majorExam> exams;
        
};

class semester
{
    private:
        vector<course> list;
        int totalCredits;
        string term;
};

class AcademicPlanner
{
    public:
        int getCredits() {return totalCredits;}

    private:
        vector<semester> overall;
        int totalCredits;
};

void output()
{
    for(int i = 0; i < 12; i++)
    {
        cout<<monthNames[i]<<endl;
        for(int j = 0; j < months[i].size(); j++)
        {
            for(int k = 0; k < months[i][j].dayIter+1; k++)
                cout<<"\t";
            cout<<j<<"\t";
            if(months[i][j].dayIter == 6)
                cout<<endl;
        }
        cout<<endl<<endl;
    }
}

int main()
{
    loadMonths();
    output();
}