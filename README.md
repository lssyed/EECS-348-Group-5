# Project: Arithmetic Expression Evaluator in C++
**Course** EECS 348: Software Engineering I
**Group** Group 5

## Project Overview
* This project is a C++ program designed to parse and evaluate arithmetic expressions.
* It supports numeric constants and operators like +, -, *, /, % and **.
* It calculates the desired operation by following PEMDAS, precedence, and associative rules.

## Latest Submission
* [01_Project_Plan](./docs/01_Project_Plan.pdf)
* [02/08/2026 Meeting Log](./meetinglogs/02_08_2026%20Meeting%20Recap.pdf)
* [02/15/2026 Meeting Log](./meetinglogs/02_15_2026%20Meeting%20Recap.pdf)

## Structure
This repository follows a clean and logical structure.
* `/docs` - Contains project documentation like our project plan, requirements document, and design document.
* `/meetinglogs` - Contains meeting recap/log for each meeting held. 
* `/src` - Provides source code for the evaluator. (Later on...)
* `/test` - Unit tests, integration tests. (Later on...)
* `/local.config` - Contains local configuration related to setup on local machine. (Later on...)
* `/script.build` - Contains all scripts related to build process. (Later on...)
* `/dep` - Directory where all dependencies are stored. (Later on...)
* `/samples` - Code that supports the documentation. (Later on...)
* `/tools` - Contains scripts to automate tasks in the project. (Later on...)
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
