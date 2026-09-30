/****************
20237341
Nghiem Phu Quang Hung
****************/


#include<iostream>
#include<string>
#include<vector>


using namespace std;

class Employee {
    
    protected:
    
    string id = "UNKNOWN";
    string fullName = "Unamed Employee";
    double baseSalary = 0;

    public:
    
    // Constructor
    Employee() {
        string id = "UNKNOWN";
        string fullName = "Unamed Employee";
        double baseSalary = 0;
    };

    Employee(const string& id, const string& fullName) {
        if (id.empty() == 1 || fullName.empty() == 1) {
            cout << "ID and Name must not be empty!" << endl;
            this->~Employee();
        } else {
            this->id = id;
            this->fullName = fullName;
        };
    };

    Employee(string id, string fullName, double baseSalary) {
        if (id.empty() == 1 || fullName.empty() == 1 || baseSalary < 0) {
            cout << "ID and Name must not be empty! Salary must not be negative!" << endl;
            this->~Employee();
        } else {
            this->id = id;
            this->fullName = fullName;
            this->baseSalary = baseSalary;
        };
    };
    
    // Getter
    auto getId() {
        return id;
    };

    auto getFullName() {
        return fullName;
    };

    auto getBaseSalary() {
        return baseSalary;
    };
    
    // Method
    void increaseSalary(double amount) {
        if (amount <= 0) {
            cout << "Increase value must be positive!" << endl;
        } else {
            baseSalary+= amount;
        };
    };

    void increaseSalary(double value, bool byPercentage) {
        if (value <= 0) {
            cout << "Increase value must be positive!" << endl;
        } else if (byPercentage == 0) {
            baseSalary+= value;
        } else {
            baseSalary *= (1 + value);
        };
    };
    
    virtual double calculateMonthlyCost() {
        return baseSalary;
    };

    virtual void displayInfo() {
        cout << "Employee found alive!" << endl <<
                "Id: " << id << endl <<
                "Name: " << fullName << endl <<
                "Salary: " << baseSalary << endl;
    };

    // Destructor
    virtual ~Employee() {
        cout << "Employee Id: " << id << " found dead." << endl;
    };

};

class SoftwareEngineer : public Employee {

    private:

    string primaryLanguage;
    double technicalAllowance = 0;

    public:

    // Constructor
    SoftwareEngineer(const string& id, const string& fullName, const string& primaryLanguage) {
        if (id.empty() == 1 || fullName.empty() == 1 || primaryLanguage.empty() == 1) {
            cout << "ID, Name and Primary Language must not be empty!" << endl;
            this->~SoftwareEngineer();
        } else {
            this->id = id;
            this->fullName = fullName;
            this->primaryLanguage = primaryLanguage;
        };
    };
    
    SoftwareEngineer(const string& id, const string& fullName, double baseSalary, const string& primaryLanguage, double technicalAllowance) {
        if (id.empty() == 1 || fullName.empty() == 1 || primaryLanguage.empty() == 1 || baseSalary < 0 || technicalAllowance < 0) {
            cout << "ID, Name and Primary Language must not be empty! Salary and Allowance must not be negative" << endl;
            this->~SoftwareEngineer();
        } else {
            this->id = id;
            this->fullName = fullName;
            this->baseSalary = baseSalary;
            this->primaryLanguage = primaryLanguage;
            this->technicalAllowance = technicalAllowance;
        };
    };

    // Method override
    double calculateMonthlyCost() {
        return baseSalary + technicalAllowance;
    };

    void displayInfo() {
        cout << "Software Engineer found!" << endl <<
                "Id: " << id << endl <<
                "Name: " << fullName << endl <<
                "Salary: " << baseSalary << endl <<
                "Primary Language: " << primaryLanguage << endl <<
                "Technical Allowance: " << technicalAllowance << endl;
    };

    ~SoftwareEngineer() {
        cout << "Software Engineer ID: " << id << " found dead." << endl;
    }

};

class ProjectTeam {

    private:

    string projectCode = "UNKNOWN";
    string projectName = "Unnamed Project";
    Employee* leader = new Employee();
    vector<Employee*> projectMemberList;
    
    public:

    // Constructor
    ProjectTeam(const string& projectCode, const string& projectName) {
        this->projectCode = projectCode;
        this->projectName = projectName;
    };

    ProjectTeam(const string& projectCode, const string& projectName, Employee& leader) {
        this->projectCode = projectCode;
        this->projectName = projectName;
        this->leader = &leader;
        projectMemberList.push_back(&leader);
    };

    // Method
    bool addMember(Employee& employee) {
        for (auto memeber : projectMemberList) {
            if ((&employee) == memeber || employee.getId() == memeber->getId()) {
                return 0;
            };
        };
        projectMemberList.push_back(&employee);
        return 1;
    };

    bool addMember(Employee& employee, bool makeLeader) {
        for (auto memeber : projectMemberList) {
            if ((&employee) == memeber || employee.getId() == memeber->getId()) {
                return 0;
            };
        };
        projectMemberList.push_back(&employee);
        if (makeLeader == 1) {
            leader = &employee;
        };
        return 1;
    };

    void removeMember(const string& employeeID) {
        int iter = 0;
        for (auto memeber : projectMemberList) {
            if (memeber->getId() == employeeID) {
                if (leader->getId() == employeeID) {
                    cout << "Can not remove Team Leader from member list!" << endl;
                } else {
                    projectMemberList.erase(projectMemberList.begin() + iter);
                }
            }
            iter++;
        }
    };

    void changeLeader(Employee& employee) {
        leader = &employee;
        for (auto memeber : projectMemberList) {
            if ((&employee) == memeber || employee.getId() == memeber->getId()) {
                return;
            };
        };
        projectMemberList.push_back(&employee);
    };

    double calculateTotalMonthlyCost() {
        double totalCost = 0;
        for (auto memeber : projectMemberList) {
            totalCost += memeber->calculateMonthlyCost();
        };
        return totalCost;
    };

    void displayTeam() {
        cout << "Project Team found!" << endl <<
                "Code: " << projectCode << endl <<
                "Name: " << projectName << endl <<
                "Leader ID: " << leader->getId() << endl <<
                "Leader Name: " << leader->getFullName() << endl <<
                "Team Members\' Id: " << endl;
        for (auto memeber : projectMemberList) {
            cout << memeber->getId() << ", ";
        };
        cout << endl;
    };

    ~ProjectTeam() {
        // delete leader;
        // delete &projectMemberList;
        cout << "The whole Project Team code: " << projectCode << " have gone missing." << endl;
    }
};

int main() {

    // Create 2 employee with 2 diff constructors
    Employee employee1("001", "Zon Employ");
    employee1.displayInfo();
    Employee employee2("002", "Zen Employ", 3500);
    employee2.displayInfo();

    cout << endl;

    // Same with 2 software engineers
    SoftwareEngineer engineer1("003", "Don Engi", "C++");
    engineer1.displayInfo();
    SoftwareEngineer engineer2("004", "Den Engi", 6000, "C++", 1000);
    engineer2.displayInfo();

    cout << endl;

    // Increase Zon Employ's salary from 0 to 4000
    employee1.increaseSalary(4000);
    cout << employee1.getBaseSalary() << endl;

    cout << endl;

    // Increase Den Engi's salary by 5% to 6300
    engineer2.increaseSalary(0.05, true);
    cout << engineer2.getBaseSalary() << endl;

    cout << endl;

    // Create a team wo leader
    ProjectTeam teamA("OOOA", "Project A");
    teamA.displayTeam();

    cout << endl;

    // Add Zon Employ as a non leader member
    teamA.addMember(employee1);
    teamA.displayTeam();

    cout << endl;

    // Add Den Engi as the leader engineer
    teamA.addMember(engineer2, true);
    teamA.displayTeam();

    cout << endl;

    // Try to add Den again
    teamA.addMember(engineer2);
    teamA.displayTeam();

    cout << endl;

    // Calculate the total expense for Team OOOA salary
    cout << teamA.calculateTotalMonthlyCost() << endl;

    cout << endl;

    // Try to remvove the leader
    teamA.removeMember("004");
    teamA.displayTeam();

    cout << endl;

    // Make Zon the leader then remove Den
    teamA.changeLeader(employee1);
    teamA.removeMember("004");
    teamA.displayTeam();

    cout << endl;

    // Create another team in a local and add Zon and Don
    do {
        ProjectTeam teamB("OOOB", "Project B", engineer1);
        teamB.addMember(employee1);
        teamB.displayTeam();
    
    cout << endl;

        // Delete Team OOOB 
    } while (0==1);

    cout << endl;

    // Zon and Don are magically saved?
    employee1.displayInfo();
    engineer1.displayInfo();

};