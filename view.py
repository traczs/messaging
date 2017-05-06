#!/usr/bin/python3

import sys
import os
import curses

if __name__ == "__main__":
    username = ''
    for i in range(1,len(sys.argv)):
        username += sys.argv[i]
        username += '_'
    with open("StreamList") as f:
        stream = f.readlines()
        stream = [x.strip() for x in stream]
    list =[]
    for i in range(0,len(stream)):
        streamname = ''
        streamname += "messages/"
        streamname += stream[i]
        streamname += "StreamUsers"
        with open(streamname) as f:
            for line in f:
                token=line.split()
                if username in token:
                    print(stream[i],end=" ")
                    list.append(stream[i])
    if len(list) > 0:
        print("all")
    else:
        print("User does not have any stream permissions")
        sys.exit()
    rows,columns = os.popen('stty size','r').read().split()
    while True:
        sys.stdout.write("\x1b[8;{rows};{cols}t".format(rows=24, cols=80))
        choice = input()
        if choice in list or choice=="all":
            screen = curses.initscr()
            curses.noecho()
            curses.cbreak()
            screen.keypad(True)
            screen.clear()
            mypad = curses.newpad(1000,80)
            mypad_pos = 0
            mypad.refresh(mypad_pos,0,0,0,23,80)
            if choice=="all":
                curses.nocbreak()
                screen.keypad(False)
                curses.echo()
                curses.endwin()
                print("Feature not available")
            else:
                stream = ''
                stream += "messages/"
                stream += choice
                stream += "Stream"
                if os.path.isfile(stream) == False:
                    curses.nocbreak()
                    screen.keypad(False)
                    curses.echo()
                    curses.endwin()
                    print("File has not been created, exitting")
                    break
                stream1 = stream + "Users"
                with open(stream1) as f:
                    for line in f:
                        token=line.split()
                        if username in token:
                            mypad_pos = int(token[1])
                with open(stream) as f:
                    i=0
                    for line in f:
                        token=line.split()
                        if "Sender:" in token:
                            mypad.addstr(i,0,"---------------------------------")
                            i = i+1
                            mypad.addstr(i,0,"Stream: " + choice)
                            i = i+1
                        mypad.addstr(i,0,line)
                        i = i+1
                        mypad.refresh(mypad_pos,0,0,0,23,80)
                        screen.addstr(23,0,"Up Down O-order toggle M-mark all S-stream C-check for new")
                        screen.refresh()
                lowestcounter =0
                while True:
                    c = screen.getch()
                    if c == 113:
                        curses.nocbreak()
                        screen.keypad(False)
                        curses.echo()
                        curses.endwin()
                        sys.exit()
                    elif c == curses.KEY_DOWN:
                        if mypad_pos < i-23:
                            mypad_pos += 1
                        mypad.refresh(mypad_pos,0,0,0,23,80)
                        screen.addstr(23,0,"Up Down O-order toggle M-mark all S-stream C-check for new")
                        screen.refresh()
                        file1name = stream + "Users"
                        screen.refresh()
                        file2 = open("messages/output","w")
                        if lowestcounter < mypad_pos:
                            with open(file1name) as f:
                                for line in f:
                                    token2 = line.split()
                                    if username in token2:
                                        string = username + " "+ str(mypad_pos) + "\n"
                                        file2.write(string)
                                    else:
                                        file2.write(line)
                            file2.close()
                            os.rename("messages/output",file1name)
                    elif c == curses.KEY_UP:
                        if mypad_pos >0:
                            mypad_pos -= 1
                        mypad.refresh(mypad_pos,0,0,0,23,80)
                        screen.addstr(23,0,"Up Down O-order toggle M-mark all S-stream C-check for new")
                        screen.refresh()
                    elif c==67 or c==99:
                        mypad.clear()
                        with open(stream) as f:
                            j=0
                            for line in f:
                                token=line.split()
                                if "Sender:" in token:
                                    mypad.addstr(j,0,"---------------------------------")
                                    j = j+1
                                mypad.addstr(i,0,line)
                                j = j+1
                                mypad.refresh(mypad_pos,0,0,0,23,80)
                                screen.addstr(23,0,"Up Down O-order toggle M-mark all S-stream C-check for new")
                                screen.refresh()
                    elif c==109 or c==77:
                        filename = stream + "Users"
                        screen.addstr(23,60,"Saved")
                        screen.refresh()
                        file1 = open("messages/output","w")
                        with open(filename) as f:
                            for line in f:
                                token1 = line.split()
                                if username in token1:
                                    string = username + " "+ str(i-23) + "\n"
                                    file1.write(string)
                                else:
                                    file1.write(line)
                        file1.close()
                        os.rename("messages/output",filename)
                    elif c==83 or c==115:
                        break
            curses.nocbreak()
            screen.keypad(False)
            curses.echo()
            curses.endwin()
            print(', '.join(list), end="")
            print(", all")
        else:
            curses.nocbreak()
            screen.keypad(False)
            curses.echo()
            curses.endwin()
            print("Choice not available")
    sys.stdout.write("\x1b[8;{rows};{cols}t".format(rows=rows, cols=columns))
