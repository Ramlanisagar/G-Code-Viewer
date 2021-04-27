//@Ramlani 21/03/2020- 15/04/2020-----G-Code Viewer
//new edits -- 20/04/2021
// install graphis.h in your system to run this program
// select GCC-32 bit release 
// go to new >> new project >> graphic console >> paste this code >> compile and execute
// g-code files(test1, test2,......or any file) should be in the same folder 
// This program is only limited to 2-D shapes ( G00 , G01, G02, G03 )
#include <bits/stdc++.h> 
#include <graphics.h> 
#include <stdio.h>  
#define MAX_FILE_NAME 100 
#define LSIZ 128 
#define RSIZ 50
#define PI 3.14
using namespace std; 

float* updateArray( string str )      //1//for updation of array
{   
    string word;
    stringstream iss(str);
    static float arr[6] = {0};      //static is used to update previous array
    while(iss >> word)
    {
    cout << "Current word = "<< word << " | Root Word = " << word[0] << endl;
    float val;
    int index;
    switch(word[0])
   	   {
   	   	case 'G':
   	   		cout << "G = ";
   	   		index = 0;
   	   		break;	
   	   	case 'X':
   	   		cout << "X = ";
   	   		index = 1;
   	   		break;
        case 'Y':
		    cout << "Y = ";	
            index = 2;
   	   		break;
   	   	case 'R':
   	   		cout << "R = ";
   	   		index = 3;
   	   		break;	
   	   	case 'I':
   	   		cout << "I = ";
   	   		index = 4;
   	   		break;
        case 'J':	
            cout << "J = ";
   	   		index = 5;
   	   	    break;
   	   	    
	   }    
	        //cout << "word in string" << word; 
	        word.assign(word,1,word.size());
   	   		//cout << "  word in new string" << word <<endl;
   	   		val = stof(word);
   	   		arr[index] = val;
   	   	    cout << arr[index] << endl;
    }
	return arr;
}

//2/// userdefined data ype for returning matrix and number of rows in matrix
typedef struct {
 float matrix[100][6];
 int total;
} arr2d;

arr2d readfile()                             //3//read current file
{
	char line[RSIZ][LSIZ];
	FILE *fptr; 
	int count = 0; 
    int i = 0;
    int tot = 0;                                        // Line counter (result) 
	char filename[MAX_FILE_NAME]; 
	char c;                                             // To store a character read from file 
    arr2d result;
	// Get file name from user. The file should be either in current folder or complete path should be provided 
	cout << "Enter file name: "; 
	cin >> filename; 

	fptr = fopen(filename, "r");        

	if (fptr == NULL)         // Check if file exists  
	{ 
		cout << "Could not open file " << filename; 
		exit(0) ;
	} 
 
	while(fgets(line[i], LSIZ, fptr)) 
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    result.total = i;  
    
    cout << "total no. of lines = " << result.total;
    
    cout << "\n The content of the file are : \n";
    cout <<"************************************" << endl;
	    
    for(i = 0; i < result.total; ++i)
    {
        cout << line[i] << endl;
    }
	//float matrix[result.total][6];
	
	cout <<"************************************" << endl;	    	                              	
    for( int i = 0 ; i < result.total ; i++) 
  {
    float* ptr = updateArray(line[i]);	    //string str = line[i];
   
    for(int s = 0 ; s< 6 ; s++)
    {
    		result.matrix[i][s] = ptr[s]; 
	}
  }
       
    fclose(fptr);
	return result;  
    
}

// driver code 
int main() 
{ 
      // gm is Graphics mode which is a computer display mode that generates image using pixels DETECT is a macro defined in "graphics.h" header file 
     //	        int gd = DETECT, gm; 

	// initgraph initializes the graphics system by loading a graphics driver from disk 
	//         initgraph(&gd, &gm, ""); 
	initwindow(1459, 763);        // 1441,737 >>>>>>>> 9 extra in x and 13 extra in y required for window of size (1450,750)
    int x = getmaxx();            // function for maximum cordinates of x & Y
    int y = getmaxy();  
	cout << "x = " << x << endl;             
	cout << "y = " << y << endl;     
	line(0, y/2, x, y/2);                   //to draw X and Y axis.
    line(x/2, 0, x/2, y);
                     
                     
	arr2d result;
    result = readfile();
    float arr[result.total+1][6];    // 1 extra initial row for proer calculation row 
        cout <<"************************************" << endl;
    	cout << "arr[i][j] = " << endl; 
    
    for( int i = 0 ; i < result.total+1 ; i++) 
  { 	
    for(int j = 0 ; j< 6 ; j++)
    {   
        arr[0][j] = 0;                          // initial row (all zero)
        arr[i+1][j]  = result.matrix[i][j];
    	cout << arr[i][j] << " "; 
	}
	cout << endl;
  } 
	
	 int xl,yl,x1,y1,x2,y2,ex,ey,sx,sy,cx,cy,I,J,start_angle,end_angle;
	 float val,radius;
	for(int i =0; i< result.total+1;i++)
  {
  	int p = arr[i][0];                         // we can't use float variable in switch case so converted into int
	switch(p)                                  //for checking value of G in G-code
	{
	case 0:                                           // case 0 is for for cursor position
	    xl = arr[i][1];
	  	yl = arr[i][2];
	    putpixel(xl*3 + 725, yl*3 + 375, LIGHTBLUE);
	    break;
	case 1:                                                  //case 1 is for a line from (x1,y1) to (x2,y2)
		x1 = arr[i-1][1]; 
		x2 = arr[i][1];
		y1 = arr[i-1][2];
		y2 = arr[i][2];
		line(x1*3 + 725,y1*3 + 375 ,x2*3 + 725,y2*3 +375);     //coordinates are shifted by (725,375) to draw, a esay to read curve
		break;
	case 2:                                                        // case 2 is for circles and arcs(clockwise)
			if(arr[i-1][3] != arr[i][3] )
		{
			circle(arr[i][1]*3 + 725, arr[i][2]*3 + 375, arr[i][3]*3 );     // draw acirle if new radius is available
		}
		else
		{   
		     I = arr[i][4];                        // distance of starting point from centre in x direction >> centre(x) = starting point(x) + I     
		     J = arr[i][5];                        //distance of starting point from centre in y direction >> centre(Y) = starting point(Y) + J     
		     radius =  sqrt(I*I + J*J);            //claculation of radius = i*i + j*j
		   	 cx = arr[i-1][1] + I;                 // x coordinate of centre of arc
		     cy = arr[i-1][2] + J;                 // y coordinate of centre of arc
		     sx = arr[i-1][1];                     // previous x cordinates  or starting x cordinates
		     sy = arr[i-1][2];                     // previous x cordinates  or starting y cordinates
		     ex = arr[i][1];                       // current x cordinates  or ending x cordinates
		     ey = arr[i][2];                       // current x cordinates  or ending x cordinates
		
		 val = 180.0 / PI;        
		 end_angle = atan2(cy-ey, ex-cx) * val;       
		 start_angle = atan2(cy-sy, sx-cx) * val;
		                                 cout << "information related to arc" << endl;
		                                 cout << "radius = " << radius <<endl;
		                                 cout << "cx = " << cx << endl;
		                                 cout << "cy = " << cy << endl;
		                                 cout << "start_angle = " << start_angle << endl;
		                                 cout << "end_angle = " << end_angle << endl; 
		                                
		 arc(cx*3 + 725, cy*3 + 375, end_angle, start_angle, radius*3);
	    }
	    break;
	case 3:
		if(arr[i-1][3] != arr[i][3] )
		{
			circle(arr[i][1]*3 + 725, arr[i][2]*3 + 375, arr[i][3]*3 );    // case 3 is for circles and arcs(anti-clockwise)
		}
		else
		{   
		      
		     I = arr[i][4];                        // distance of starting point from centre in x direction >> centre(x) = starting point(x) + I
		     J = arr[i][5];                        //distance of starting point from centre in y direction >> centre(Y) = starting point(Y) + J       
		     radius =  sqrt(I*I + J*J);            //claculation of radius = i*i + j*j     
		   	 cx = arr[i-1][1] + I;                 // x coordinate of centre of arc
		     cy = arr[i-1][2] + J;                 // y coordinate of centre of arc
		     sx = arr[i-1][1];                     // previous x cordinates  or starting x cordinates
		     sy = arr[i-1][2];                     // previous x cordinates  or starting y cordinates
		     ex = arr[i][1];                       // current x cordinates  or ending x cordinates
		     ey = arr[i][2];                       // current x cordinates  or ending x cordinates
		
		 val = 180.0 / PI;        
		 end_angle = atan2(cy-ey, ex-cx) * val;       
		 start_angle = atan2(cy-sy, sx-cx) * val;
		                                 cout << " information related to arc" << endl;
		                                 cout << "radius = " << radius <<endl;
		                                 cout << "cx = " << cx << endl;
		                                 cout << "cy = " << cy << endl;
		                                 cout << "start_angle = " << start_angle << endl;
		                                 cout << "end_angle = " << end_angle << endl; 
		                                
		 arc(cx*3 + 725, cy*3 + 375 , start_angle, end_angle, radius*3);
		}
		break;		   
	}
	   
}	
    cout << endl <<"See BGI Window for 2D shape >>>>>>>>>" << endl;
	getch(); 
	                        // closegraph function closes the graphics mode and deallocates all memory allocated by graphics system 
	closegraph(); 

	return 0;
} 
