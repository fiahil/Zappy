## launcher.sh for zappy launcher in /home/busina_b/Projet/Zappy-Unix/Zappy/AI/
## 
## Made by benjamin businaro
## Login   <busina_b@epitech.net>
## 
## Started on  Sat Jul 14 18:04:26 2012 benjamin businaro
## Last update Sat Jul 14 18:13:07 2012 benjamin businaro
##
#!/bin/sh
##
## launcher.sh
##
## benjamin businaro
## Sat Jul 14 2012

if [ $# -lt 3 ]
then
    echo "Usage : ./launcher.sh <team_name> <host> <port>"
else
    for i in {0..7}
    do
	./ai_client -n $1 -h $2 -p $3 -s&
    done
fi


