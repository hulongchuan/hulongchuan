#!/bin/bash
cd ~/hulongchuan/
echo -n "plz input commit msg: "
read -e MSG
echo -n "running git add"
git add .
echo  "---------------done"
git commit -a -m "${MSG:-defaut-msg}"

echo "git commit ------------done"
echo
echo -n "Want to push to remote master(Y/n): "
read AAA
#be sure to have a blank between "[" and "$AAA"
if [ "${AAA:-y}" = "y" ];then
       echo pushing ...
      git push
       echo ...done
else
       echo pass
fi
