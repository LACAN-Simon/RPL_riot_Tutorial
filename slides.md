---
title: Getting Git right
theme: white
highlightTheme: monokai
---

<!-- .slide: data-background="#205081" -->

![Git](images/git.svg)
## Getting Git Right
_Etienne Profit, Julien Teigny & Julien Vandaele - SED, Inria Lille_

---

## Manage code and history

![file versions](images/file-versions.png)

---

### What is version control?

![Version control](images/version-control.svg)
Practice of tracking and managing changes.

Notes:
- **keeps track** of every modification to the code in a special kind of database.  
- **protects** source code from both catastrophe and the casual degradation of human error and unintended consequences.

Examples: PhD manuscript, scientific paper, prototype, experimentation

---

### Benefits

<ol>
<li class="fragment">complete long-term change history</li> 
<li class="fragment">independant streams of changes</li> 
<li class="fragment">traceability</li> 
</ol>

---

## Getting started

### Install Git

See:
- https://git-scm.com/book/en/v2/Getting-Started-Installing-Git
- https://www.atlassian.com/git/tutorials/install-git

```shell
$ git --version
git version 2.37.0 (Apple Git-136)
$ git config --global user.name "Julien Vandaele"
$ git config --global user.email "julien.vandaele@inria.fr"
```

---

## Getting started

https://gitlab.inria.fr/vandaele/git-sandbox

<br/>

### Now, bring your own resume <!-- .element class="fragment" data-fragment-index="1" -->
1. Request access & clone the git-sandbox project <!-- .element class="fragment" data-fragment-index="1" -->
2. Produce 4 commits (creation, header, dev, tv) <!-- .element class="fragment" data-fragment-index="1" -->
3. Transform to Markdown file with new commit(s) <!-- .element class="fragment" data-fragment-index="2" -->
4. Push <!-- .element class="fragment" data-fragment-index="2" -->
5. Add the emoticons section with new commit(s) <!-- .element class="fragment" data-fragment-index="3" -->
6. Push again <!-- .element class="fragment" data-fragment-index="3" -->

Notes:
1. Create `git-sandbox` project
2. Show steps on how to produce the resume (TXT)
3. Grant access to attendees as developpers.
3. Show Markdown syntax and apply it (MD)
3. Between 4 & 5, run `produce-conflict.sh` 

----

![memorize](images/memorize.png) <!-- .element height="500vh" -->

## Be Kind Rewind <!-- .element class="fragment" -->

----

![init](images/init.svg)
### Setting up a repository
<div style="text-align: left">

**git init** - Create an empty Git repository or reinitialize an existing one  
**git clone** - Clone a repository into a new directory

</div>

----

![saving](images/saving.svg)
### Saving changes
<div style="text-align: left">

**git add** - Add file contents to the index  
**git commit** - Record changes to the repository  

</div>

----

![3 trees](images/3-trees.svg)

----

![inspecting](images/inspecting.svg)<!-- .element height="300vh" -->
### Inspecting a repository

**git status** - Show the working tree status  
**git log** - Show commit logs  
**git diff** - Show changes between commits, commit and working tree, etc

----

![git status git log](images/git-status-log.svg)

----

![syncing](images/syncing.svg) <!-- .element height="300vh" -->

### Syncing

**git push** - Update remote refs along with associated objects  
**git pull** - Fetch from and integrate with another repository or a local branch

---

![Alt text](images/git-log.svg)
### Advanced Git log

<div class="fragment">

Common usefull combination is:
```shell
git log --oneline --decorate --graph
```

[More options](https://www.atlassian.com/git/tutorials/git-log)
</div>

Notes:
Show options:
-2
-p
--stat
--oneline
--decorate
--graph

----

### Rewriting history with

### <code>git commit <span class="fragment hljs-name">--amend</span></code>


<div style="text-align: left" class="fragment">

**Change last commit message**
```shell
$ git commit --amend
```
**Changing last commit content**
```shell
$ git add
$ git commit --amend --no-edit
```
</div>

Notes:
DEMO 
1. edit commit message with
2. update last commit with file
3. option `--no-edit`

----
### Exercise

Save the HTML rendering of your `<login>.md` file locally.

<div>

Then do:
```shell
$ git status
$ git pull
$ git status
```
</div> <!-- .element class="fragment" style="text-align: left" -->

Notes:
In parallel, run the `add_gitignore.sh` script.

----

### .gitignore

common examples are:

- dependency caches (/node_modules or /packages)
- compiled code, such as .o, .pyc, and .class files
- build output directories, such as /bin, /out
- files generated at runtime, such as .log, .lock, .tmp
- hidden system files
- personal IDE config files, such as .idea/workspace.xml

[Patterns](https://www.atlassian.com/git/tutorials/saving-changes/gitignore#git-ignore-patterns)

---

## Source code management

### Best practices (level 1)

- commit often
- ensure you're working from latest version
- make detailed notes

![git log](images/git-log.png) <!-- .element class="fragment" height="300vh" -->

----

### Conventionnal Commit Messages

```
<type>(<scope>): <subject>

<body>

<footer>
```

```
fix(middleware): ensure Range headers adhere more closely to RFC 2616

Add one new dependency, use `range-parser` (Express dependency) to compute
range. It is more well-tested in the wild.

Fixes #2310
```

<small>_source: http://karma-runner.github.io/1.0/dev/git-commit-msg.html_</small>

---

![branches](images/branches.svg)
## Branches

Notes:
In Git, branches are a part of your everyday development process.

----

### Exercice

https://mrmen.com/pages/characters

<div style="text-align: left">

#### Now, bring your own character
1. Work by pair
    - `A` works on branch `<character>`
    - `B` works on branch `<character>-image`
1. Everyone pushes their own branch
1. `A` merges `<character>-image` in `<character>` and pushes
1. `A` merges `<character>` in `main` and pushes
</div>
<!-- .element class="fragment" -->

----

### Be Kind Rewind

![branch](images/branch01.svg)

----

### Creating branches

```shell
$ git branch
* main
  little-feature
```

```shell
$ git branch big-feature
```

```shell
$ git branch
* main
  little-feature
  big-feature
```

----

### Switching branches

```shell
$ git switch big-feature
  main
  little-feature
* big-feature
```

```shell
$ git switch -c <branch>
```

----

### Deleting branches

```shell
$ git branch -d <branch>
```
```shell
$ git branch -D <branch>
```

----

### Merging branches

![git merge](images/git-merge.gif)

----

### Merging branches
#### Preparing to merge
- confirm the receiving branch
- fetch latest remote commits
- merge

```shell
$ git branch
* main
  my-feature-branch
$ git pull
$ git merge my-feature-branch
```
<!-- .element class="fragment" -->

----

### Merging branches
<div style="display: flex">
<div style="flex: 1" class="fragment">

#### Fast Forward Merge

![git merge ff](images/git-merge-ff.svg) <!-- .element height="500vh" -->
</div>
<div style="flex: 1" class="fragment">

#### 3-way merge

![git merge 3 way merge](images/git-merge-3wm.svg) <!-- .element height="500vh" -->
</div>
</div>

----

### Merging branches
#### Resolving conflict

```diff
here is some content not affected by the conflict
<<<<<<< main
this is conflicted text from main
=======
this is conflicted text from feature branch
>>>>>>> feature branch;
```

```shell
$ git add <conflicted-file>
$ git commit
```

----

### Rebasing

![git rebase](images/git-rebase.svg) <!-- .element height="600vh" -->

Notes:
Rebasing is the process of moving or combining a sequence of commits to a new base commit. Rebasing is most useful and easily visualized in the context of a feature branching workflow.  
From a content perspective, rebasing is changing the base of your branch from one commit to another making it appear as if you'd created your branch from a different commit

----

### Merging vs. Rebasing
#### The merge option

```shell
git checkout feature
git merge main
```

![Alt text](images/merging-main-into-feature-branch.svg) <!-- .element height="400vh" -->

Notes:
The `feature` branch will have an extraneous merge commit every time you need to incorporate upstream changes. If `main` is very active, this can pollute your feature branch’s history quite a bit. 

----

### Merging vs. Rebasing

<div style="display:flex">
<div style="flex:1">

#### The rebase option

```shell
git checkout feature
git rebase main
```
![Alt text](images/rebasing-feature-branch-into-main.svg)
</div>
<div style="flex:1" class="fragment">

#### Interactive Rebasing

```shell
git checkout feature
git rebase -i main
```

![Alt text](images/squashing-with-interactive-rebase.svg)
</div>
</div>

Notes:
- The major benefit of rebasing is that you get a much cleaner project history.
- Eliminating insignificant commits like this makes your feature’s history much easier to understand. This is something that git merge simply cannot do.

----

### Merging vs. Rebasing

Golden Rule of Rebasing:
<!-- .element style="color: gold" -->
never use it on _public_ branches.

![rebasing the main branch](images/rebasing-main-branch.svg) <!-- .element height="450vh" style="background-color:white" class="fragment" -->

Notes:
Avoid using git rebase after creating the pull request (the PR is a also public branch).
----

### git pull = git fetch + git merge

**git fetch** - Download objects and refs from another repository  
**git merge** - Join two or more development histories together  

----

### Git pull usage

<div>

![Alt text](images/git-pull.svg) <!-- .element height="240vh" -->
</div>
<div style="display: flex">
<div style="flex: 1">

`git pull --no-rebase` 
<!-- .element style="font-size: small" -->
![Alt text](images/git-pull-merge.svg)
</div>
<div style="flex: 1">

`git pull --rebase`
<!-- .element style="font-size: small" -->
![Alt text](images/git-pull-rebase.png)
</div>
</div>

---

## Let's go further with

### <code>git rebase <span class="hljs-name">-i</span></code>

<div class="fragment">

```shell
git pull
git switch rebasing
git rebase -i main
```
Goal: have 3 commits in the good order (one, two, three).
</div>

Notes:  
Run
```shell
./create-rebasing-branch.sh <dir>

```
Clone the branch before rebasing if you're not sure of what you're doing.

---

## Source code management

### Best practices (level 2)

- ...
- review changes before comitting
- use branches
- agree on a workflow

Notes:
Reminder, first 3 were: 
- commit often
- make detailed notes
- ensure you're working from latest version

---

## Workflows

### Centralized Workflow
<!-- .element: class="fragment fade-in-then-semi-out" -->
### Feature Branch Workflow
<!-- .element: class="fragment fade-in-then-semi-out" -->
### Forking Workflow
<!-- .element: class="fragment fade-in-then-semi-out" -->
### Gitflow Workflow
<!-- .element: class="fragment" -->

Notes:
- centralized: used while producing your resumes
- feature-branch: used while producing mr-men & little miss cards
- forking: close to feature-branch but from your cloned repo (fork)

----

### Gitflow Workflow
<div class="r-stack">
  <div class="fragment fade-out" data-fragment-index="0">
    <h4>Develop and main branches</h4>
    <img src="images/git-workflow-develop.svg" height="500vh"/>
  </div>
  <div class="fragment fade-in-then-out" data-fragment-index="0">
    <h4>Feature branches</h4>
    <img src="images/git-workflow-feature.svg" height="500vh"/>
  </div>
  <div class="fragment fade-in-then-out" data-fragment-index="1">
    <h4>Release branches</h4>
    <img src="images/git-workflow-release.svg" height="500vh"/>
  </div>
  <div class="fragment" data-fragment-index="2">
    <h4>Hotfix branches</h4>
    <img src="images/git-workflow-hotfix.svg" height="500vh"/>
  </div>
</div>

---

## Git remote

![remote repo](images/remote-repo.svg) <!-- .element height="200vh" -->

```shell
git remote
git remote -v
git remote add <name> <url>
git remote rm <name>
git remote rename <old-name> <new-name>
```

```shell
git push <remote-name> <branch-name>
git push <remote-name> <local-branch>:<remote-branch>
```

---

## Refs

![refs](images/refs.svg)

Notes:
- hashes
- branches
- tags
- relative refs

----

### Relative refs

![relative refs](images/relative-refs.svg)

Notes:
~ tilde
^ caret

---

![undoing changes](images/undoing.svg)
## Undoing changes
***Resetting, Checking Out, and Reverting***

<div class="fragment">

**git reset** - Reset current HEAD to the specified state  
**git checkout** - Switch branches or restore working tree files  
**git revert** - Revert some existing commits
</div>

----

### Reverting

![git revert](images/git-revert.svg)

```shell
 $ git revert HEAD~
 $ git log --oneline
 1061e79 Revert "prepend content to demo file"
 1654a23 add documentation to demo file
 86bb32e prepend content to demo file
 299b15f initial commit
```

Notes:
Undo, but by adding a new commit with the resulting inverse content.  
It doesn’t change the project history, which makes it a “safe” operation for commits that have already been published to a shared repository.

----

### Checking out vs. Resetting

![git sequence](images/git-sequence.png)

<div style="display: flex">

<div style="flex:1">

**git checkout b**
![git sequence checkout](images/git-sequence-checkout.png)
```shell
/!\ 'detached HEAD' state
```
</div>
<div style="flex:1">

**git reset b**
![git sequence reset](images/git-sequence-reset.png)
</div>
</div>

Notes:
In addition to updating the commit ref pointers, git reset will modify the state of the three trees.

----

### Resetting

![Alt text](images/git-reset-options.svg) <!-- .element height="500vh" -->

---

## Extra

**git stash** - Stash the changes in a dirty working directory away

<pre><code data-line-numbers="1-3|5-7|9-11|13-14|16">git stash
git stash pop
git stash apply

git stash list
git stash show <stash>
git stash show <stash> -p

git stash [-m] <message>
git stash -u # add untracked files
git stash -a # add ignored files

git stash drop
git stash clear

git stash pop --index

</code></pre>

---

## Oh Shit, Git !?!

> If there's a probleme, there's a solution(s)

https://ohshitgit.com

----

## Extra #2

![cherry-pick](images/git-cherry-pick.png) <!-- .element height="200vh" -->

**git cherry-pick** - Apply the changes introduced by some existing commits

---

## Git cheat sheet

https://www.atlassian.com/git/tutorials/atlassian-git-cheatsheet

## Links
https://git-scm.com/book/en/v2

https://learngitbranching.js.org

---
## Tools

- [Meld](http://meldmerge.org)
- [SourceTree](https://www.sourcetreeapp.com)
- IDE integration

---

source: [Atlassian](https://www.atlassian.com/git)<br/>
<small>https://www.atlassian.com/git</small>
