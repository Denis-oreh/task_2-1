#include <gtest/gtest.h>

#include "../lib/include/HRDepartment.h"
#include "../lib/include/Person.h"
#include "../lib/include/Employee.h"
#include "../lib/include/Position.h"
#include "../lib/include/Department.h"
#include "../lib/include/PreviousWorkplace.h"

#include <string>
#include <algorithm>

TEST(PersonTest, Getters) {
    Employee p("Иванов Иван Иванович", "12.03.1985", Position("None"), Department("None"), 1.0);
    EXPECT_GT(p.getId(), 0);
    EXPECT_EQ(p.getFullName(), "Иванов Иван Иванович");
    EXPECT_EQ(p.getBirthDate(), "12.03.1985");
}

TEST(PersonTest, GetInfo) {
    Employee p("Иванов Иван Иванович", "12.03.1985", Position("None"), Department("None"), 1.0);
    std::string info = p.getInfo();
    EXPECT_NE(info.find("Иванов Иван Иванович"), std::string::npos);
    EXPECT_NE(info.find("12.03.1985"), std::string::npos);
    EXPECT_NE(info.find("ID:"), std::string::npos);
}

TEST(PositionTest, GetTitle) {
    Position pos("Программист");
    EXPECT_EQ(pos.getTitle(), "Программист");
}

TEST(DepartmentTest, GetName) {
    Department d("IT");
    EXPECT_EQ(d.getName(), "IT");
}

TEST(PreviousWorkplaceTest, GettersAndToString) {
    PreviousWorkplace wp("ООО Ромашка", "Junior", "2010-2013");
    EXPECT_EQ(wp.getCompany(),  "ООО Ромашка");
    EXPECT_EQ(wp.getPosition(), "Junior");
    EXPECT_EQ(wp.getPeriod(),   "2010-2013");
    std::string s = wp.toString();
    EXPECT_NE(s.find("ООО Ромашка"), std::string::npos);
    EXPECT_NE(s.find("Junior"),      std::string::npos);
    EXPECT_NE(s.find("2010-2013"),   std::string::npos);
}

TEST(EmployeeTest, Getters) {
    Employee e("Петрова Анна Петровна", "10.12.1960",
               Position("Бухгалтер"), Department("Бухгалтерия"), 0.5);
    EXPECT_GT(e.getId(), 0);
    EXPECT_EQ(e.getFullName(), "Петрова Анна Петровна");
    EXPECT_EQ(e.getBirthDate(), "10.12.1960");
    EXPECT_EQ(e.getPosition().getTitle(), "Бухгалтер");
    EXPECT_EQ(e.getDepartment().getName(), "Бухгалтерия");
    EXPECT_DOUBLE_EQ(e.getRate(), 0.5);
}

TEST(EmployeeTest, DefaultFlagsAreFalse) {
    Employee e("Иванов Иван Иванович", "12.03.1985",
               Position("Программист"), Department("IT"), 1.0);
    EXPECT_FALSE(e.isPensioner());
    EXPECT_FALSE(e.isDisabled());
    EXPECT_FALSE(e.isOnVacation());
    EXPECT_FALSE(e.isOnMaternityLeave());
    EXPECT_FALSE(e.hasChildren());
}

TEST(EmployeeTest, SetFlags) {
    Employee e("Иванов Иван Иванович", "12.03.1985",
               Position("Программист"), Department("IT"), 1.0);
    e.setFlags(true, false, true, false);
    EXPECT_TRUE(e.isPensioner());
    EXPECT_FALSE(e.isDisabled());
    EXPECT_TRUE(e.isOnVacation());
    EXPECT_FALSE(e.isOnMaternityLeave());
}

TEST(EmployeeTest, Children) {
    Employee e("Сидорова Мария Петровна", "21.11.1986",
               Position("Программист"), Department("IT"), 1.0);
    EXPECT_FALSE(e.hasChildren());
    e.addChildId(100);
    e.addChildId(101);
    EXPECT_TRUE(e.hasChildren());
    ASSERT_EQ(e.getChildrenIds().size(), 2u);
    EXPECT_EQ(e.getChildrenIds()[0], 100);
    EXPECT_EQ(e.getChildrenIds()[1], 101);
}

TEST(EmployeeTest, PreviousWorkplaces) {
    Employee e("Иванов Иван Иванович", "12.03.1985",
               Position("Программист"), Department("IT"), 1.0);
    EXPECT_TRUE(e.getPreviousWorkplaces().empty());
    e.addPreviousWorkplace(PreviousWorkplace("ООО Ромашка", "Junior", "2010-2013"));
    e.addPreviousWorkplace(PreviousWorkplace("ЗАО Лютик", "Middle", "2013-2020"));
    ASSERT_EQ(e.getPreviousWorkplaces().size(), 2u);
    EXPECT_EQ(e.getPreviousWorkplaces()[0].getCompany(), "ООО Ромашка");
    EXPECT_EQ(e.getPreviousWorkplaces()[1].getCompany(), "ЗАО Лютик");
}

TEST(EmployeeTest, GetInfoContainsFields) {
    Employee e("Иванов Иван Иванович", "12.03.1985",
               Position("Программист"), Department("IT"), 1.0);
    e.setFlags(false, false, false, true);
    std::string s = e.getInfo();
    EXPECT_NE(s.find("Иванов Иван Иванович"), std::string::npos);
    EXPECT_NE(s.find("Программист"),          std::string::npos);
    EXPECT_NE(s.find("IT"),                   std::string::npos);
    EXPECT_NE(s.find("декрет"),               std::string::npos);
}

static bool hrHasFullName(const HRDepartment& hr, const std::string& fullName) {
    bool inPeople = std::any_of(hr.getPeople().begin(), hr.getPeople().end(), [&fullName](const Person& p) {
        return p.getFullName() == fullName;
    });
    if (inPeople) return true;
    return std::any_of(hr.getEmployees().begin(), hr.getEmployees().end(), [&fullName](const Employee& e) {
        return e.getFullName() == fullName;
    });
}

template <typename Predicate>
static int countEmployeesWhere(const HRDepartment& hr, Predicate pred) {
    int cnt = 0;
    for (const auto& e : hr.getEmployees()) {
        if (pred(e)) ++cnt;
    }
    return cnt;
}

TEST(HRDepartmentTest, AddAndGetPeople) {
    HRDepartment hr;
    EXPECT_TRUE(hr.getPeople().empty());
    EXPECT_TRUE(hr.getEmployees().empty());

    Employee p("Иванов Иван Иванович", "12.03.1985", Position("None"), Department("None"), 1.0);
    hr.addPerson(p);
    hr.addPerson(p);

    EXPECT_EQ(hr.getPeople().size(), 1u);
    EXPECT_TRUE(hrHasFullName(hr, "Иванов Иван Иванович"));

    Employee e("Петров Пётр Петрович", "01.01.1990", Position("Бухгалтер"), Department("Бухгалтерия"), 1.0);
    hr.addPerson(e);
    hr.addPerson(e);
    hr.addEmployee(e);

    EXPECT_EQ(hr.getEmployees().size(), 1u);
    EXPECT_TRUE(hrHasFullName(hr, "Петров Пётр Петрович"));
}

TEST(HRDepartmentTest, FindByFullName) {
    HRDepartment hr;
    hr.addPerson(Employee(
        "Иванов Иван Иванович", "12.03.1985",
        Position("Программист"), Department("IT"), 1.0));
    hr.addPerson(Employee(
        "Петрова Анна Петровна", "10.12.1960",
        Position("Бухгалтер"), Department("Бухгалтерия"), 0.5));
    EXPECT_EQ(hr.getEmployees().size(), 2u);
    EXPECT_TRUE(hrHasFullName(hr, "Иванов Иван Иванович"));
    EXPECT_TRUE(hrHasFullName(hr, "Петрова Анна Петровна"));
    EXPECT_FALSE(hrHasFullName(hr, "Несуществующий Сотрудник"));
}

TEST(HRDepartmentTest, Filters) {
    HRDepartment hr;

    Employee e1(
        "Иванов Иван Иванович", "12.03.1985",
        Position("Программист"), Department("IT"), 1.0);

    Employee e2(
        "Петрова Анна Петровна", "10.12.1960",
        Position("Бухгалтер"), Department("Бухгалтерия"), 0.5);
    e2.setFlags(true, false, false, false);

    Employee e3(
        "Сидорова Мария Петровна", "21.11.1986",
        Position("Программист"), Department("IT"), 1.0);
    e3.setFlags(false, false, false, true);

    Employee child("Иванов Пётр Иванович", "29.10.2007", Position("None"), Department("None"), 1.0);
    e1.addChildId(child.getId());
    e3.addChildId(child.getId());

    hr.addPerson(e1);
    hr.addPerson(e2);
    hr.addPerson(e3);
    
    hr.addPerson(static_cast<const Person&>(child));

    EXPECT_EQ(hr.getEmployees().size(), 3u);
    EXPECT_EQ(hr.getPeople().size(), 1u);
    EXPECT_TRUE(hrHasFullName(hr, "Иванов Иван Иванович"));
    EXPECT_TRUE(hrHasFullName(hr, "Петрова Анна Петровна"));
    EXPECT_TRUE(hrHasFullName(hr, "Сидорова Мария Петровна"));
    EXPECT_TRUE(hrHasFullName(hr, "Иванов Пётр Иванович"));

    EXPECT_EQ(countEmployeesWhere(hr, [](const Employee& e){ return e.getPosition().getTitle() == "Программист"; }), 2);
    EXPECT_EQ(countEmployeesWhere(hr, [](const Employee& e){ return e.getPosition().getTitle() == "Бухгалтер"; }),   1);
    EXPECT_EQ(countEmployeesWhere(hr, [](const Employee& e){ return e.getRate() == 0.5; }),                         1);
    EXPECT_EQ(countEmployeesWhere(hr, [](const Employee& e){ return e.hasChildren(); }),                            2);
    EXPECT_EQ(countEmployeesWhere(hr, [](const Employee& e){ return e.isPensioner(); }),                            1);
    EXPECT_EQ(countEmployeesWhere(hr, [](const Employee& e){ return e.isOnMaternityLeave(); }),                     1);
    EXPECT_EQ(countEmployeesWhere(hr, [](const Employee& e){ return e.isDisabled(); }),                             0);
    EXPECT_EQ(countEmployeesWhere(hr, [](const Employee& e){ return e.isOnVacation(); }),                           0);
}

TEST(HRDepartmentTest, Polymorphism) {
    Employee p("Иванов Пётр Иванович", "29.10.2007", Position("None"), Department("None"), 1.0);
    Employee e(
        "Иванов Иван Иванович", "12.03.1985",
        Position("Программист"), Department("IT"), 1.0);

    const Person& pRef = p;
    const Person& eRef = e;

    EXPECT_NE(dynamic_cast<const Employee*>(&pRef), nullptr);
    EXPECT_NE(dynamic_cast<const Employee*>(&eRef), nullptr);
    
    EXPECT_EQ(pRef.getInfo().find("Программист"), std::string::npos);
    EXPECT_NE(eRef.getInfo().find("Программист"), std::string::npos);

    HRDepartment hr;
    hr.addPerson(p);
    hr.addPerson(e);

    EXPECT_EQ(hr.getEmployees().size(), 2u);
    EXPECT_EQ(hr.getPeople().size(), 0u);
    EXPECT_TRUE(hrHasFullName(hr, "Иванов Пётр Иванович"));
    EXPECT_TRUE(hrHasFullName(hr, "Иванов Иван Иванович"));
}

TEST(HRDepartmentTest, DepartmentsAndPositionsDeduplication) {
    HRDepartment hr;
    hr.addDepartment(Department("IT"));
    hr.addDepartment(Department("IT"));
    hr.addDepartment(Department("HR"));

    EXPECT_EQ(hr.getDepartments().size(), 2u);
    EXPECT_EQ(hr.getDepartments()[0].getName(), "IT");
    EXPECT_EQ(hr.getDepartments()[1].getName(), "HR");

    hr.addPosition(Position("Программист"));
    hr.addPosition(Position("Программист"));
    hr.addPosition(Position("Бухгалтер"));

    EXPECT_EQ(hr.getPositions().size(), 2u);
    EXPECT_EQ(hr.getPositions()[0].getTitle(), "Программист");
    EXPECT_EQ(hr.getPositions()[1].getTitle(), "Бухгалтер");
}

TEST(HRDepartmentTest, DuplicateIdRejected) {
    HRDepartment hr;
    Employee p1("Иванов Иван", "01.01.2000", Position("None"), Department("None"), 1.0, 100);
    Employee p2("Петров Петр", "02.02.2001", Position("None"), Department("None"), 1.0, 100);
    hr.addPerson(p1);
    hr.addPerson(p2);
    EXPECT_EQ(hr.getEmployees().size(), 1u);
    EXPECT_TRUE(hrHasFullName(hr, "Иванов Иван"));
    EXPECT_FALSE(hrHasFullName(hr, "Петров Петр"));

    Employee e1("Сидоров Сидор", "03.03.1990", Position("IT"), Department("IT"), 1.0, 200);
    Employee e2("Козлов Козма", "04.04.1991", Position("IT"), Department("IT"), 1.0, 200);
    hr.addPerson(e1);
    hr.addPerson(e2);
    EXPECT_EQ(hr.getEmployees().size(), 2u);
    EXPECT_TRUE(hrHasFullName(hr, "Сидоров Сидор"));
    EXPECT_FALSE(hrHasFullName(hr, "Козлов Козма"));
}

TEST(PersonTest, ConstructorWithExplicitId) {
    Employee p("Сидоров Сидор", "01.01.2000", Position("None"), Department("None"), 1.0, 42);
    EXPECT_EQ(p.getId(), 42);
    EXPECT_EQ(p.getFullName(), "Сидоров Сидор");
    EXPECT_EQ(p.getBirthDate(), "01.01.2000");
}

TEST(EmployeeTest, ConstructorWithExplicitId) {
    Employee e("Кузнецов Кузьма", "05.05.1995", Position("DevOps"), Department("IT"), 1.0, 99);
    EXPECT_EQ(e.getId(), 99);
    EXPECT_EQ(e.getFullName(), "Кузнецов Кузьма");
    EXPECT_EQ(e.getPosition().getTitle(), "DevOps");
    EXPECT_EQ(e.getDepartment().getName(), "IT");
}

TEST(PersonTest, DefaultConstructorHasValidId) {
    Employee p;
    EXPECT_GT(p.getId(), 0);
}

TEST(EmployeeTest, DefaultConstructorHasValidId) {
    Employee e;
    EXPECT_GT(e.getId(), 0);
}
