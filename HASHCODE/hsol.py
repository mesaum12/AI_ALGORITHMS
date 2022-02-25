#!C:\Users\saura\AppData\Local\Programs\Python\Python39\python.exe

from random import randrange
import random
import sys


def solve(file, skills, contributor, project):
    # print(skills, contributor, project, sep="\n\n")
    skillset = set(skills.keys())
    towrite = []
    ct = 0
    with open("sol/"+file, "w") as f:
        for proj in project:
            c = project[proj]['requirement'][-1]
            s = project[proj]["skills"]
            sn = project[proj]["skillnames"]
            if(not set(s.keys()).issubset(skillset)):
                continue
            names = []
            for skill in sn:
                # print(skill)
                x = []
                for p in skills[skill]:
                    if(skills[skill][p] >= s[skill]):
                        x.append(p)
                # print(skill, x)
                if(len(x) > 0):
                    t = random.choice(x)
                    if(names.count(t) > 0):
                        break
                    names.append(t)
                else:
                    break
            if(len(names) < c):
                continue
            ct += 1
            towrite.append(proj)
            towrite.append(" ".join(names))
        f.write(str(ct)+"\n")
        f.write("\n".join(towrite))


def main():
    if(len(sys.argv) == 1):
        return
    file = sys.argv[1]
    contributor = {}
    skills = {}
    project = {}
    with open(file) as f:
        c, p = map(int, f.readline().split())
        fl = True
        pa = ""
        pb = 0
        while(c >= 0):
            a, b = f.readline().split()
            b = int(b)
            if(fl):
                pa = a
                pb = b
                contributor[pa] = {}
                c -= 1
                fl = False
            else:
                pb -= 1
                skills[a] = {pa: int(b)}
                contributor[pa][a] = int(b)
                if(pb == 0):
                    fl = True
                    if(c == 0):
                        break

        fl = True
        pa = ""
        pb = 0
        while(p >= 0):
            x = f.readline().split()
            if(fl):
                a = x[0]
                b = list(map(int, x[1:]))
                pa = a
                pb = int(b[-1])
                project[a] = {}
                project[a]["requirement"] = b
                project[a]["skills"] = {}
                project[a]["skillnames"] = []
                p -= 1
                fl = False
            else:
                a = x[0]
                b = int(x[1])
                project[pa]["skillnames"].append(a)
                project[pa]["skills"][a] = b
                pb -= 1
                if(pb == 0):
                    if(p == 0):
                        break
                    fl = True
        solve(file, skills, contributor, project)


if __name__ == "__main__":
    main()
