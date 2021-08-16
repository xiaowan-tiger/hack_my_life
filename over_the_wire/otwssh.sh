#!/usr/local/bin/bash

# set -euxo pipefail

if [ $# -lt 2 ]; then
    echo "Usage: $0 SERVER LEVEL"
    exit 1
fi

OTW_PATH=~/workspace/git_repos/hack_my_life/over_the_wire
SERVER=$1
LEVEL=$2
USER=$1$2

PASSWORD_FILE=$OTW_PATH/$SERVER/passwords.txt
PASSWORD=$(cat $PASSWORD_FILE | grep $USER | cut -d ":" -f 2)

declare -A ports='(["narnia"]="2226" ["leviathan"]="2223" ["behemoth"]="2221" ["bandit"]="2220")'
PORT=${ports[$SERVER]}

if [ -z "$PASSWORD" ]; then
    echo "Password for $USER not found!"
    exit 1
fi

sshpass -p $PASSWORD ssh -p $PORT $USER@$SERVER.labs.overthewire.org