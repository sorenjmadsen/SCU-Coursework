# Name: Soren Madsen
# Date: 9 Jan 2020
# Title: Lab1 – Basic Shell Programming
# Description: This program computes the area of a circle based
# on user credentials and command line input.
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$="$$

user=`whoami`
numusers=`who | wc -l`
echo "Hi, $user! There are $numusers users logged on."

if [ $user = "smadsen" ]
then
    echo "Now you can proceed!"
else
    echo "Check who logged in!"
    exit 1
fi

response="Yes"
while [ $response != "No" ]
do
    echo "Enter radius of the circle: "
    read radius
    pi=3.14159265
    area=$(echo "scale=8;$pi * $radius * $radius" | bc)
    echo "The area of the circle is $area"

    echo "Would you like to repeat for another circle [Yes/No]?"
    read response
done