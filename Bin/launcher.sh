## launcher.sh for zappy launcher in /home/busina_b/Projet/Zappy-Unix/Zappy/AI/
## 
## Made by benjamin businaro
## Login   <busina_b@epitech.net>
## 
## Started on  Sat Jul 14 18:04:26 2012 benjamin businaro
## Last update Sat Jul 14 20:12:27 2012 benjamin businaro
##
#!/bin/sh
##
## launcher.sh
##
## benjamin businaro
## Sat Jul 14 2012

if [ $# -lt 4 ]
then
    echo "Usage : ./launcher.sh <nb_client> <team_name> <host> <port>"
else
    j=0
    while [ $j -lt $1 ]
    do
	./ai_client -n $2 -h $3 -p $4 -s&
        j=$(($j+1))
    done
fi


