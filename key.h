/* http://www-cms.phys.s.u-tokyo.ac.jp/~naoki/CIPINTRO/CCGI/function.html#getch */
#include <unistd.h>
#include <termios.h>

static struct termios t_orig;

char kbhit(void){
	struct termios t;
	tcgetattr( 0, &t );
	t_orig = t;
	t.c_lflag &= ~(ICANON|ECHO);
	t.c_cc[VMIN] = 0;
	tcsetattr( 0, TCSADRAIN, &t );
	char c;
	int status = read( 0, &c, sizeof(char) );
	return status ? c : (char)status;
	tcsetattr( 0, TCSADRAIN, &t_orig );
}