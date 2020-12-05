#!/usr/bin/env bash

git config core.hooksPath tools/git_hooks/
git config --global commit.template tools/git_hooks/git_message.txt
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status
git config --global alias.amend "commit --amend"
git config --global alias.fork "push -f fork"
# rebase by default
git config --global pull.rebase true
git config --global alias.last "diff HEAD~1..HEAD"
git config --global alias.cp "cherry-pick"
git config --global alias.rbc "rebase --continue"
git config --global alias.rbs "rebase --skip"
