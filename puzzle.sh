#!/bin/bash

if [ "$1" == "" ] || [ "$2" == "" ] || [ "$3" == "" ]
then
    echo "Usage: $0 <day: number> <part: number> <template: str>"
    exit 1
fi

day="day$1"
part="puzzle$2"
out_path="$day/$part"
template="$3"

create_environment() {
    echo "Path: $out_path is this correct? [Y/n]"
    confirm=""
    read confirm

    if [ "$confirm" != "Y" ] && [ "$confirm" != "y" ]
    then
        echo "Cancelled."
        exit 0
    fi

    if [ ! -d "$day" ]
    then
        mkdir "$day"
    fi

    mkdir "$out_path"
    cp -R "templates/$template/"* "$out_path"
}

if [ ! -d "$out_path" ]
then
    create_environment
    exit 0
else
    echo "Directory already exists."
    exit 1
fi