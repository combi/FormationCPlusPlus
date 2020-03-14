#!/bin/sh

date=`date '+%Y.%m.%d_%Hh%Mm'`
file=/home/combi/DEV/C++/workspace_$date.tar.gz
# mail=zezebubulonlon@gmail.com

cd /home/combi/DEV/C++/
tar -h -cvzf $file --exclude 'Build' --exclude 'build' --exclude '.metadata' workspace

# echo "Backup de /u/rigstuff/users/combi/workspace/mgRig => $file" | mail -s "[BACKUP MGRIG] - $file" -a $file $mail
