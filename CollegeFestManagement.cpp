
#include<bits/stdc++.h>
using namespace std;



class Participant;
class Event;
class User;
class Coordinator;
class CoreMember;
class WorkForceMember;
class CulturalEvent;
class CompetitiveEvent;
class Sponsor;
class OrganisingCommitteeMember;
class Security;


class Event
{
    

    public:
    static int participation;
    string EventName;
    string venue;
    string time;
    string date;

    void displayEventDetails()
    {
        cout<<EventName<<endl;
        cout<<"Venue :"<<venue<<endl;
        cout<<"Date :"<<date<<endl;
        cout<<"Start time :"<<time<<endl;
    }
    
};
class CulturalEvent : public Event
{
    public:
    string host;
    string guest;  


    void displayCultEventDetails()
    {
        this->displayEventDetails();
        cout<<"Host : "<<host<<endl;
        cout<<"Special guest : "<<guest<<endl;
    }
};
class CompetitiveEvent : public Event
{
    public:
    string prizes;
    int entry_fee;
    string winner;

    void setWinner(string winnername)
    {
        winner = winnername;
    }
    void getWinner()
    {
        cout<<"The winner of the event is "<<winner<<endl;
    }

    void displayCompEventDetails()
    {
        this->displayEventDetails();
        cout<<"Prizes :"<<prizes<<endl;
    }
};


class User
{
 protected:
    string name;
    string mobileNumber;
    string email;

    User()
    {
        name = "";
        mobileNumber ="";
        email ="";
    }

    User(string Name, string mobile, string em)
    {
        name = Name;
        mobileNumber = mobile;
        email = em;
    }

    string getName()
    {
        return name;
    }
    string getMobile()
    {
        return mobileNumber;
    }
    string getEmail()
    {
        return email;
    }
};
class Participant : public User
{
    
    public:
    vector <Event*>  participatingEvents;
    bool outsider;
    static int particpant_count;

    Participant() :User()
    {
        particpant_count++;
        outsider = true;
    }

    Participant( string Name ,string mobile, string email , bool out ,vector <Event*> ev ) :User(Name , mobile , email)
    {
        particpant_count++;
        outsider = out;
        for(int i =0 ; i< ev.size(); i++)
        {
            participatingEvents.push_back(ev[i]);
        }
    }

    ~Participant()
    {
        particpant_count--;
        cout<<"Thanks for participating! Hope you had a good time!"<<endl;
    }

    void addEvent(Event* ev)
    {
        participatingEvents.push_back(ev);
        cout<<"You have successfully registered for the event"<<endl;
    }

    void removeEvent(Event* ev)
    {
        auto it = find(participatingEvents.begin(),participatingEvents.end(),ev);
        if(it != participatingEvents.end())
        {
            participatingEvents.erase(it);
            cout<<"You have successfully unregistered for the event"<<endl;
        }

        else 
        {
            cout<<"Sorry you haven't registered for " <<ev->EventName <<endl;
        }
    }
};



class OrganisingCommitteeMember : public User
{
    
    protected:
    int studyYear;
    string degree;

    OrganisingCommitteeMember() : User()
    {
        studyYear = 1;
        degree = "ug";
    }
    OrganisingCommitteeMember(string Name, string mobile , string email , int year , string deg) : User( Name , mobile,  email)
    {
        studyYear = year;
        degree = deg;
    }

    int getYear()
    {
        return studyYear;
    }

    string getDegree()
    {
        return degree;
    }
};


class WorkForceMember : public OrganisingCommitteeMember
{
public:
	Event * WorksInEvent;
	Coordinator * WorksUnder;
    WorkForceMember(string Name , string mobile , string email , int year , string deg , Event * event): OrganisingCommitteeMember( Name ,  mobile , email  , year, deg)
    {
        WorksInEvent = event;
    } 
    void assignCoordinator(Coordinator* coordinator)
    {
        WorksUnder = coordinator;
    }

    
};
class Coordinator : public OrganisingCommitteeMember 
{	
public :
	CoreMember* WorksUnderCoreMember;
	vector<Event*> events;
	vector<WorkForceMember*> supervisesWorker;

    void addworkForceMember(WorkForceMember* member)
    {
        supervisesWorker.push_back(member);
        //cout<<member->name <<" has been added to your team"<<endl;
        member->assignCoordinator(this);
    } 

    void removeworkForceMember(WorkForceMember* member)
    {
        auto it = find(supervisesWorker.begin() , supervisesWorker.end() , member);
        supervisesWorker.erase(it);
        //cout<<member->name <<" has been removed from your team"<<endl;
    } 

    void assignCoreMember(CoreMember* coreMember)
    {
        WorksUnderCoreMember =   coreMember;
    }
};

class CoreMember : public OrganisingCommitteeMember
{
    public:
    string areaOfWork;
    vector <Coordinator*> supervises;

    CoreMember() : OrganisingCommitteeMember()
    {
        areaOfWork ="";
    }
    CoreMember(string Name , string mobile , string email , int year , string deg, string area , vector <Coordinator*> v) : OrganisingCommitteeMember(Name , mobile ,email , year , deg)
    {
        areaOfWork = area;
        for(int i =0 ; i< v.size(); i++)
        {
            supervises.push_back(v[i]);
        }
    }

    void addCoordinator( Coordinator* coordinator)
    {
        supervises.push_back(coordinator);
       // cout<<coordinator->name <<" has been added to your team"<<endl;
        coordinator->assignCoreMember(this);
    }

    void removeCoordinator( Coordinator* coordinator)
    {
        auto it = find(supervises.begin(),supervises.end(),coordinator);
        supervises.erase(it);
       // cout<<coordinator->name <<" has been remove your team"<<endl;
    }

};
class Security
{
    string name;
    string mobile;
    string locationOfDuty;
    string startTime;
    string endTime;

    friend class Coordinator;
    friend class CoreMember;

    public:
    void changeLocation(string location)
    {
        locationOfDuty = location;
        cout<<"The location has been changed to "<<location<<endl;
    }

    string getname()
    {
        return name;
    }

    string getMobile()
    {
        return mobile;
    }
};



class Sponsor
{
    int amount;
    string email;

    public:
    string companyName;
    string category;


    Sponsor()
    {
        cout<<"Thanks for sponsoring!"<<endl;
    }

    Sponsor(string Name ,string Email, int amt , string Category)
    {
        companyName = Name;
        email = Email;
        amount = amt;
        category = Category;
    }

    int getAmount()
    {
        return amount;
    }

    string getEmail()
    {
        return email;
    }
};
int Event::participation = 0;
int Participant::particpant_count = 0;

int main()
{
    
    Participant particpant1 , participant2;
    CoreMember coremember1 , coremember2;
    Coordinator coordinator1, coordinator2;
    CompetitiveEvent comp1 , comp2 ;
    CulturalEvent cult1 , cult2;
    Security security1, security2;
    Sponsor sponsor1, sponsor2;
    Sponsor *sponsor3  = new Sponsor("Decathlon" , "dec@gmail.com" , 100000 , "Title sponsor");
    cout<< sponsor3->companyName << " has sponsored an amount of "<<sponsor3->getAmount()<<endl;
    
}





