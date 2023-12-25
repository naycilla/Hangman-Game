// clear screen after delay 1 sec
void clrscr(){
	sleep(1);
	system("cls");
}


// print hangman pic
void hngmn(unsigned int attempts) {
    switch (attempts) {
        case 0:
            printf("  ____\n");
            printf(" |    |\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            break;
        case 1:
            printf("  ____\n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            break;
        case 2:
            printf("  ____\n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |    |\n");
            printf(" |\n");
            printf(" |\n");
            break;
        case 3:
            printf("  ____\n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |   /|\n");
            printf(" |\n");
            printf(" |\n");
            break;
        case 4:
            printf("  ____\n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |\n");
            printf(" |\n");
            break;
        case 5:
            printf("  ____\n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |   /\n");
            printf(" |\n");
            break;
        case 6:
            printf("  ____\n");
            printf(" |    |\n");
            printf(" |    O\n");
            printf(" |   /|\\\n");
            printf(" |   / \\\n");
            printf(" |\n");
            break;
    }
}
