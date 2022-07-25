#include<stdio.h>
#include<GL/glut.h>

void display();
void init();
void reshape(int,int);
void timer(int);
void lower();
void box();

int state = 0;
int hi ;
int low = 0;
float higher_x;
float higher_y = -2;
float temp=0 ;
float line;

int pivot;

int search;
int flag = 0;
int check = 0;
int complete = 0;


struct poly{
    float v[4][2];
    int number;
};

typedef struct poly poly;

int n;
float x_pos = -8;
float y_pos = 0;
float x_incre= 0;
float y_incre=0;
poly pol[30];


void initalize()
{
    printf("enter the size of the array\n");
    scanf("%d",&n);
    printf("Please enter the array elements\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pol[i].number);
    }
    int t;
        for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
           if(pol[i].number > pol[j].number) {
               t = pol[i].number;
               pol[i].number = pol[j].number;
               pol[j].number = t;
           }
        }
    }
    hi = n-1;
    pivot = (hi+low)/2;
    for(int i=0;i<n;i++)
        printf("%d->",pol[i].number);
    printf("Enter the search value\n");
    scanf("%d",&search);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(j<=1)
                    y_incre = 2;
                if(j>=2)
                    y_incre = 0;
            for(int k=0;k<2;k++)
            {
                if(k==0)
                {
                   if(j==0 | j==3)
                        pol[i].v[j][k] = x_pos+x_incre;
                   else
                    pol[i].v[j][k] = x_pos+x_incre+1;
                }
                if(k==1)
                {
                   pol[i].v[j][k] = y_pos+y_incre;
                }
            }
        }
        x_incre = x_incre+1.5;
    }

    higher_x = pol[n-1].v[0][0];
    line = higher_x;
}




int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    initalize();

    glutInitWindowPosition(10,10);
    glutInitWindowSize(2560,1440);
    glutCreateWindow("Mohammed Saif");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    binarySearch();
    glutTimerFunc(1000,timer,0);
    glutMainLoop();
}

char str[10];
char index[10];
char indexTxt[10] = "INDEX :";
void polygon1(int i)
{
    glColor3f(1,1,1);
     glBegin(GL_POLYGON);
            glVertex2f(pol[i].v[0][0],pol[i].v[0][1]);
            glVertex2f(pol[i].v[1][0],pol[i].v[1][1]);
            glVertex2f(pol[i].v[2][0],pol[i].v[2][1]);
            glVertex2f(pol[i].v[3][0],pol[i].v[3][1]);
    glEnd();
    sprintf(str,"%d",pol[i].number);
    glColor3f(0,1,0);
    glRasterPos2f(pol[i].v[0][0]+0.2,pol[i].v[0][1]/2);
    for(int i=0;i<strlen(str);i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    sprintf(index,"%d",i);
    glRasterPos2f(pol[i].v[0][0]+0.2,pol[i].v[0][1]-3);
    for(int i=0;i<strlen(index);i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,index[i]);
    glRasterPos2f(-9.5,-1);
    for(int i=0;i<strlen(indexTxt);i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,indexTxt[i]);
}

float arrow_x = -7.5;
float arrow_y = 5;
float half=0;


void arrow()
{

    glLoadIdentity();
    glColor3f(0,1,1);
    glLineWidth(8);
    glBegin(GL_LINES);
        glVertex2f(arrow_x+(half*1.5),arrow_y);
        glVertex2f(arrow_x+(half*1.5),arrow_y-2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex2f(arrow_x-0.5+(half*1.5),arrow_y-2);
        glVertex2f(arrow_x+0.5+(half*1.5),arrow_y-2);
        glVertex2f(arrow_x+(half*1.5),arrow_y-3);

    glEnd();
    char str1[20];
    char str2[50];
    sprintf(str1,"PIVOT = %d",pivot);
    glColor3f(0,1,0);
    glRasterPos2f(arrow_x+(half*1.5)-0.5,arrow_y+0.2);
    for(int i=0;i<strlen(str1);i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str1[i]);

    sprintf(str2,"KEY = %d",search);
    glRasterPos2f(arrow_x+(half*1.5)-0.5,arrow_y+0.7);
    for(int i=0;i<strlen(str2);i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str2[i]);

}

float low_x = -8;
float low_y = -3;
float low_x_incre;

void lower()
{
    glLoadIdentity();
    glLineWidth(5.0);
    glColor3f(1,0,0);
    glBegin(GL_LINES);
        glVertex2f(low_x+(1.5*low_x_incre),low_y);
        glVertex2f(low_x+1+(1.5*low_x_incre),low_y);
    glEnd();
    char lower[50] = "LOW PTR";
    glRasterPos2f(low_x+(1.5*low_x_incre),low_y+0.2);
    for(int i=0;i<strlen(lower);i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,lower[i]);
}




void higher()
{
     glLoadIdentity();

    glLineWidth(5.0);
    glColor3f(1,1,0);
    glBegin(GL_LINES);
        glVertex2f(higher_x,higher_y);
        glVertex2f(higher_x+1,higher_y);
    glEnd();
      char high[50] = "HIGH PTR";
    glRasterPos2f(higher_x,higher_y+0.2);
    for(int i=0;i<strlen(high);i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,high[i]);

}


void box()
{
    glLoadIdentity();
    glLineWidth(4.0);
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(low_x+(1.5*low_x_incre),low_y+5);
        glVertex2f(higher_x+1,higher_y+4);
        glVertex2f(higher_x+1,higher_y+2);
        glVertex2f(low_x+(1.5*low_x_incre),low_y+3);
    glEnd();
}

void pivotChange(int hi, int low){
    pivot = (hi+low)/2;
}


int pre_pivot;
void binarySearch()
{
    if(complete == 0){
    state = 0;
    }
 else
    {
     if(search==pol[pivot].number && check!=flag)
     {
         char finish[50];
        glColor3f(0,1,0);
        glRasterPos2f(-4,-5);
        sprintf(finish,"Found the number at %d index in %d attempts",pivot,flag);
        for(int i=0;i<strlen(finish);i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,finish[i]);
        state = -1;
     }
   if(search<pol[pivot].number  && check!=flag)
   {
       hi = pivot-1;
       pre_pivot = pivot;
        pivotChange(hi,low);
        check++;
        state = 5;
   }
     if(search>pol[pivot].number && check!=flag)
     {
       low = pivot+1;
       printf("\n high %d\n",hi);
    pre_pivot = pivot;
       pivotChange(hi,low);
       check++;
       state = 4;
     }
   }
}
int lockLower=0;
void timer(int x)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
switch(state)
    {
    case 0:
        if(pivot>half){
            half+=0.01;
            printf("half %d",half);
        }
        else{
            flag++;
            complete = 1;
            Sleep(1000);
        }
        break;
        case 1:
        if(pivot<= half)
            half = half-0.01;
        else
        {
        flag++;
        Sleep(2000);
        complete = 2;
        }
        break;
    case 3:
        if(half<=pivot)
            half += 0.01;
        else
        {
            flag++;
            Sleep(2000);
        }
        break;
    case 4:
        if(low_x_incre<=pre_pivot+1)
        {
            low_x_incre+=0.01;
            lockLower = 1;
        }
        else{
            state = 3;
        }
        break;
    case 5:
       if(higher_x>=pol[pre_pivot].v[0][0]-1.5)
            higher_x-=0.01;
        else
            state = 1;
        break;
    }
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    for(int i=0;i<n;i++)
        polygon1(i);
    box();
    arrow();
    lower();
    higher();
    binarySearch();

    glutSwapBuffers();
}
void init()
{
    glClearColor(0.0, 0.0, 0.4, 1.0);
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10+(0.1*n),10+(0.5*n),-10,10);
    glMatrixMode(GL_MODELVIEW);

}

