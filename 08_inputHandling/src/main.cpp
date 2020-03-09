//#include<iostream>
//// #include<conio.h>
//#include <ncurses.h>
//using namespace std;

/*
       Value
Up Key    72
Down Key  80
Right Key 77
Left Key  75

*/
//
//// https://stackoverflow.com/a/912796
//#include <unistd.h>
//#include <termios.h>
//
//char getch() {
//        char buf = 0;
//        struct termios old = {0};
//        if (tcgetattr(0, &old) < 0)
//                perror("tcsetattr()");
//        old.c_lflag &= ~ICANON;
//        old.c_lflag &= ~ECHO;
//        old.c_cc[VMIN] = 1;
//        old.c_cc[VTIME] = 0;
//        if (tcsetattr(0, TCSANOW, &old) < 0)
//                perror("tcsetattr ICANON");
//        if (read(0, &buf, 1) < 0)
//                perror ("read()");
//        old.c_lflag |= ICANON;
//        old.c_lflag |= ECHO;
//        if (tcsetattr(0, TCSADRAIN, &old) < 0)
//                perror ("tcsetattr ~ICANON");
//        return (buf);
//}
//
//
//int main()
//{
//    char key_press;
//    int ascii_value;
//
//    while(ascii_value < 12)
//    {
//		key_press = getch();
//		cout<<"KEY Pressed-> " << key_press << " -> " << key_press << std::endl;
//    	ascii_value += 1;
//    }
//    return 0;
//}
//



// kbhit   ------------------
//---------------------------
// https://stackoverflow.com/a/33201364
#include <stdio.h>
#include <sys/ioctl.h> // For FIONREAD
#include <termios.h>
//#include <stdbool.h>

int kbhit(void) {
    static bool initflag = false;
    static const int STDIN = 0;

    if (!initflag) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initflag = true;
    }

    int nbbytes;
    ioctl(STDIN, FIONREAD, &nbbytes);  // 0 is STDIN
    return nbbytes;
}

#include <unistd.h>
#include <iostream>
int main() {
    char c;
    //setbuf(stdout, NULL); // Optional: No buffering.
    //setbuf(stdin, NULL);  // Optional: No buffering.
//    printf("Press Esc to quit");
    std::cout << "Press Esc to quit" << std::endl;
    while (true) {
    	if (kbhit())
		{
    		c = getchar();
    		int cAsInt = c;

    		printf("Char received:%c (%i)\n", c, cAsInt);
		}
    	if (c == 27)  // Esc
    	{
    		return 0;
    	}
    }

    return 0;
}



// https://stackoverflow.com/a/423643
//#include <sys/filio.h>
//int kbhit()
//{
// int i;
// ioctl(0, FIONREAD, &i);
// return i; /* return a count of chars available to read */
//}
//int main()
//{
//	 int i = 0;
//	 int c='';
//	system("stty raw -echo");
//	// printf("enter 'q' to quit \n");
//	// for (;c!='q';i++) {
//	//    if (kbhit()) {
//	//        c=getchar();
//	//       printf("\n got %c, on iteration %d",c, i);
//	//    }
//	//}
//	system("stty cooked echo");
//
//	return 0;
//}
//
//




