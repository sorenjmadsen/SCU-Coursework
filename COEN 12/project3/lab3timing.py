import os
import signal
import sys
from subprocess import Popen, PIPE

def setup_environment():
    # compiler options
    CC = "gcc"
    CFLAGS = "-o"
    LDFLAGS = ""

    global project_path
    project_path = os.getcwd()

    # text files to test with corresponding path
    text_files_path = "$HOME/Documents/examples/"

    global text_files
    text_files = [  
        text_files_path + "Bible.txt",
        text_files_path + "Genesis.txt",
        text_files_path + "GreenEggsAndHam.txt",
        text_files_path + "HoundOfTheBaskervilles.txt",
        text_files_path + "Macbeth.txt",
        text_files_path + "TheCountOfMonteCristo.txt",
        text_files_path + "TheSecretGarden.txt",
        text_files_path + "TheWarOfTheWorlds.txt",
        text_files_path + "TreasureIsland.txt",
        text_files_path + "TwentyThousandLeagues.txt"
    ]

    # expected results
    wordcount_text = " total words"
    unique_text = " distinct words"
    parity_text = " words occur an odd number of times"

    global wordcount_expected_output
    wordcount_expected_output = [
        "766425" + wordcount_text,
        "36145" + wordcount_text,
        "803" + wordcount_text,
        "59508" + wordcount_text,
        "18464" + wordcount_text,
        "463946" + wordcount_text,
        "81307" + wordcount_text,
        "60469" + wordcount_text,
        "68700" + wordcount_text,
        "103769" + wordcount_text
    ]

    global unique_expected_output
    unique_expected_output = [
        "14038" + unique_text,
        "2727" + unique_text,
        "67" + unique_text,
        "5963" + unique_text,
        "3894" + unique_text,
        "17381" + unique_text,
        "5323" + unique_text,
        "7270" + unique_text,
        "6496" + unique_text,
        "9409" + unique_text
    ]

    global parity_expected_output
    parity_expected_output = [
        "8571" + parity_text,
        "1819" + parity_text,
        "39" + parity_text,
        "4066" + parity_text,
        "2900" + parity_text,
        "11154" + parity_text,
        "3531" + parity_text,
        "4965" + parity_text,
        "4500" + parity_text,
        "6329" + parity_text
    ]


def test_strings():

    print "Testing strings..."

    # test strings
    os.chdir(project_path + "/strings")
    os.system("make clean")
    os.system("make")
    print "1 :unique"
    print "2 :parity"
    case = raw_input('Enter which test to run [1-2]:')

    if case =="1":
        print "Testing unique..."
        test_unique()

    if case == "2":
        print "Testing parity..."
        test_parity()
    

    os.chdir(project_path)


def test_generics():

    print "\n"
    print "Testing generics..."

    # test generics
    os.chdir(project_path + "/generic")
    os.system("make clean")
    os.system("make")

    print "1 :unique"
    print "2 :parity"
    case = raw_input('Enter which test to run [1-2]:')

    if case =="1":
        print "Testing unique..."
        test_unique()

    if case == "2":
        print "Testing parity..."
        test_parity()


def test_unique():

    for idx, text_file in enumerate(text_files):
        print "\tTesting " + text_file + "..."
        os.system("time " + "./unique  " + text_files[idx])


def test_parity():
    
    for idx, text_file in enumerate(text_files):
        print "\tTesting " + text_file + "..."
        os.system("time " + "./parity " + text_files[idx])


def test_counts():

    for idx, text_file in enumerate(text_files):
        print "\tTesting " + text_file + "..."
        p = Popen(["./counts", text_files[idx]],stdout=PIPE)

        os.kill(p.pid, signal.SIGTERM)


if __name__ == "__main__":
    setup_environment()
    print "Testing lab 3..."

    # test strings
    print "1 :string"
    print "2 :generic"
    case = raw_input('Enter which test to run [1-2]:')
    if case =="1":
        print "Testing string..."
        test_strings()

    if case == "2":
        print "Testing generic..."
        test_generics()
    
    
