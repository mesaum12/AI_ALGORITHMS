#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
using namespace std;
map<string, vector<string>> result;
void assign(string projectname, string namecontributor)
{
    result[projectname].push_back(namecontributor);
}
void solve(map<string, vector<pair<string, int>>> &mp1, map<string, vector<pair<string, int>>> mp2)
{
    // mp2 consists of the projects and the required skill set
    string pname, projectname;
    for (auto itr : mp2)
    {
        projectname = itr.first;
        vector<pair<string, int>> v1 = itr.second;
        for (auto itr4 : v1)
        {
            // picking up one skill from one project at a time
            string nameofskill = itr4.first;
            int lvl = itr4.second;

            for (auto itr2 : mp1)
            {
                vector<pair<string, int>> v = itr2.second;
                string namecontributor = itr2.first;

                // now for a particular contributor we need to assign him/her to a project of his skill level
                bool flag = false;
                for (auto itr3 : v)
                {
                    // get the name of the skill
                    string skillname = itr3.first;
                    // get the level of the skill
                    int level = itr3.second;

                    if (skillname == nameofskill and level >= lvl)
                    {
                        assign(projectname, namecontributor);
                        flag = true;
                        break;
                    }
                }
                bool flag2 = false;
                if (!flag && flag2 == false)
                    for (auto itr3 : v)
                    {
                        // get the name of the skill
                        string skillname = itr3.first;
                        // get the level of the skill
                        int level = itr3.second;

                        if (level >= lvl)
                        {
                            assign(projectname, namecontributor);
                            flag = true;
                            break;
                            flag2 = true;

                            // assign the current project with the name project_name to the user with name nameco
                            // ntributor
                        }
                    }
                if (flag2 == false)
                {
                    int skill_diff = INT_MAX;
                    for (auto itr3 : v)
                    {
                        int level = itr3.second;
                        string contributor;
                        if (lvl - level < skill_diff)
                        {
                            skill_diff = lvl - level;
                            contributor = namecontributor;
                            pname = projectname;
                        }
                        assign(pname, contributor);
                    }
                }
            }
        }
    }
}
void input(map<string, vector<pair<string, int>>> &mp, map<string, vector<pair<string, int>>> &mp2, map<string, int> &mp3)
{
    ifstream indata;
    indata.open("c_collaboration.in");
    int number_of_contributors, number_of_projects;
    indata >> number_of_contributors >> number_of_projects;

    // mp to store the contributor and the number of skills
    while (number_of_contributors--)
    {
        string name;
        indata >> name;
        int skills;
        indata >> skills;
        for (int i = 0; i < skills; i++)
        {
            string skill;
            int level;
            indata >> skill >> level;
            mp[name].push_back({skill, level});
        }
    }
    // we need to map the project skills with the skill level

    while (number_of_projects--)
    {
        string name;
        int duration, score_awarded, best_before, number_of_skills;
        indata >> name >> duration >> score_awarded >> best_before >> number_of_skills;
        mp3[name] = number_of_skills;
        for (int i = 0; i < number_of_skills; i++)
        {
            string skill;
            int level;
            indata >> skill >> level;
            mp2[name].push_back({skill, level});
        }
    }
    indata.close();
}
int main()
{

    map<string, vector<pair<string, int>>> mp;
    map<string, vector<pair<string, int>>> mp2;
    map<string, int> mp3; // map to store project and role

    ofstream outdata;
    outdata.open("example2.dat");
    input(mp, mp2, mp3);

    solve(mp, mp2);

    outdata << result.size() << "\n";
    for (auto itr : result)
    {
        outdata << itr.first << "\n";
        vector<string> v = itr.second;
        int count = 0;
        for (string s : v)
        {
            outdata << s << " ";
            count++;
            if (count == mp3[itr.first])
                break;
        }
        outdata << "\n";
    }
    outdata.close();
    return 0;
}