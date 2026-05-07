# Project: Arithmetic Expression Evaluator in C++
**Course** EECS 348: Software Engineering I
**Group** 5

## Project Overview
* This project is a C++ program designed to parse and evaluate arithmetic expressions.
* It supports numeric constants and operators like +, -, *, /, % and **
* It calculates the desired operation by following PEMDAS, precedence, and associative rules.

## Latest Submission
* [01_Project_Plan](./docs/01_Project_Plan.pdf)
* [02/08/2026 Meeting Log](./meetinglogs/02_08_2026%20Meeting%20Recap.pdf)
* [02/15/2026 Meeting Log](./meetinglogs/02_15_2026%20Meeting%20Recap.pdf)
* [02/22/2026 Meeting Log](./meetinglogs/02_22_2026%20Meeting%204.pdf)
* [03/01/2026 Meeting Log](./meetinglogs/03_01_2026%20Meeting%205.pdf)
* [03/08/2026 Meeting Log](./meetinglogs/03_08_2026%20Meeting%206.pdf)
* [Arithmetic Expression Evaluator Project Plan and Architecture Guide](./docs/Detailed_Expression_Evaluator_Project_Plan.pdf)
* [02_Software_Requirements_Specifications](./docs/02-Software-Requirements-Spec.docx.pdf)
* [03/29/2026 Meeting Log](./meetinglogs/03_29_2026%20Meeting%207.pdf)
* [03_Software_Architecture_Design](./docs/03_Software_Architecture_Document.pdf)
* [05/03/2026 Meeting Log](./meetignlogs/05_03_2026%20Meeting%208.pdf)
* [04_Test_Cases](./docs/)
* [05_User_Manual](./docs/)

## Structure
This repository follows a clean and logical structure.
* `/docs` - Contains project documentation like our project plan, requirements document, design document, test cases, and user manual.
* `/meetinglogs` - Contains meeting recaps/logs for each meeting held. 
* `/src` - Provides source code for the evaluator.
* `README.md` - Contains project overview and organization of repository.

---

## Git Branch Policy 🔒
To keep the history clean and ensure code review happens, developers **must not push directly to the `main` branch**. Work should be done on feature/topic branches and merged via pull requests.

### Enforcement options
1. **GitHub Branch Protection** (recommended for hosted repositories):
   * Go to the repository Settings → Branches → Add rule for `main`.
   * Enable "Require pull request reviews before merging" and disable "Allow push" for everyone except admins.
   * Optionally enforce status checks or linear history.

2. **Client‑side hook** (for local enforcement):
   * Copy `tools/prevent_direct_main_push.sh` into `.git/hooks/pre-push` and make it executable:
     ```sh
     cp tools/prevent_direct_main_push.sh .git/hooks/pre-push
     chmod +x .git/hooks/pre-push
     ```
   * The script will reject any attempt to push `refs/heads/main` to the remote, printing a message.

> Note: Hooks are not versioned; each contributor must install the hook or use a tooling wrapper such as [Husky](https://typicode.github.io/husky).

## Group Members
* **Alec** - Quality Assurance
* **Alex** - Requirements & Documents Lead
* **Jr** - Front End Lead Developer
* **Lea** - Project Manager
* **Shashwat** - System Architect
* **Zack** - Back End Lead Developer
