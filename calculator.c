#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>
#include<stdbool.h>

typedef struct{
	GtkWidget*dialog;
	GtkWidget*mesh;
	GtkWidget*ButtonToggle[17];
}calculator;

GtkWidget*square;
#define SIZE 10
char BufferInput[100]={0};
char BufferOutput[100]={0};
bool RESET=false;
bool addition=false;
bool subtraction=false;
bool multiplication=false;
bool division=false;
float equivalent=0.0;
static float num[SIZE];
int compute=0;

static void calculate(GtkButton*ButtonToggle, gpointer data){
	const gchar*text = gtk_button_get_label(ButtonToggle);

	if( (strcmp("+", text)==0) ||   (strcmp("-", text)==0) ||  (strcmp("/", text)==0) ||  (strcmp("x", text)==0) ||  (strcmp("=", text)==0) ){	
		num[compute] = atof(BufferInput);
		compute++;
		RESET = true;
		if(strcmp("+",text)==0){
			addition = true;
		}
		if(strcmp("-",text)==0){
			subtraction = true;
		}
		if(strcmp("/",text)==0){
			division = true;
		}
		if(strcmp("x",text)==0){
			multiplication = true;
		}
	}
	if(strcmp("=",text)==0){
		int x = sizeof(num)/sizeof(num[0]);
		if(addition){
			for(int a=0; a<x; a++){
				equivalent += num[a];
			}
		}

		if(division){
			equivalent = num[0]/num[1];
		}

		if(subtraction){
				if(equivalent == 0.0){
					equivalent = num[0]*2;
				}
			for(int a=0; a<x; a++){
				equivalent -= num[a];
			}
		}
	
		if(multiplication){
			equivalent = num[0]*num[1];
		}
		addition=false;
		subtraction=false;
		multiplication=false;
		division=false;
		gtk_entry_set_text(GTK_ENTRY(square), "");
		sprintf(BufferOutput, "%.3f", equivalent);
		gtk_entry_set_text(GTK_ENTRY(square), BufferOutput);
		equivalent = 0.0;
	}
	else{
		if(RESET){
			memset(BufferInput,0,strlen(BufferInput));
			RESET=false;
		}else{
			strncat(BufferInput,text, 1);
		}
		
			strncat(BufferOutput,text, 1);
			gtk_entry_set_text(GTK_ENTRY(square), BufferOutput);
	}
	if(strcmp("C",text)==0){
		gtk_entry_set_text(GTK_ENTRY(square), "");
		memset(BufferInput,0,strlen(BufferInput));
		memset(BufferOutput,0,strlen(BufferOutput));
		compute=0;
		int x = sizeof(num)/sizeof(num[0]);
		for(int a=0; a<x; a++){
				num[a] = 0;
		}
		addition = false;
		multiplication = false;
		division = false;
		subtraction = false;
	}
}

static void activate(GtkApplication*Application, gpointer user_data){
	calculator widget;
	widget.dialog = gtk_application_window_new(Application);
	gtk_window_set_title(GTK_WINDOW(widget.dialog),"Calculator");
	gtk_window_set_position(GTK_WINDOW(widget.dialog),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(widget.dialog), 200, 200);
	gtk_container_set_border_width(GTK_CONTAINER(widget.dialog),10);
	widget.mesh = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(widget.dialog),widget.mesh);
	square=gtk_entry_new();
	gtk_editable_set_editable(GTK_EDITABLE(square), FALSE);
	widget.ButtonToggle[0] = gtk_button_new_with_label("0");
	widget.ButtonToggle[1] = gtk_button_new_with_label("1");
	widget.ButtonToggle[2] = gtk_button_new_with_label("2");
	widget.ButtonToggle[3] = gtk_button_new_with_label("3");
	widget.ButtonToggle[4] = gtk_button_new_with_label("4");
	widget.ButtonToggle[5] = gtk_button_new_with_label("5");
	widget.ButtonToggle[6] = gtk_button_new_with_label("6");
	widget.ButtonToggle[7] = gtk_button_new_with_label("7");
	widget.ButtonToggle[8] = gtk_button_new_with_label("8");
	widget.ButtonToggle[9] = gtk_button_new_with_label("9");
	widget.ButtonToggle[10] = gtk_button_new_with_label(".");
	widget.ButtonToggle[11] = gtk_button_new_with_label("+");
	widget.ButtonToggle[12] = gtk_button_new_with_label("-");
	widget.ButtonToggle[13] = gtk_button_new_with_label("x");
	widget.ButtonToggle[14] = gtk_button_new_with_label("/");
	widget.ButtonToggle[15] = gtk_button_new_with_label("C");
	widget.ButtonToggle[16] = gtk_button_new_with_label("=");
	gtk_grid_attach(GTK_GRID(widget.mesh),square,0,0,4,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[15],0,1,3,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[14],3,1,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[7],0,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[8],1,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[9],2,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[13],3,2,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[4],0,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[5],1,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[6],2,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[12],3,3,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[1],0,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[2],1,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[3],2,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[11],3,4,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[0],0,5,2,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[10],2,5,1,1);
	gtk_grid_attach(GTK_GRID(widget.mesh),widget.ButtonToggle[16],3,5,1,1);
	g_signal_connect(widget.ButtonToggle[0],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[1],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[2],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[3],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[4],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[5],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[6],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[7],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[8],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[9],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[10],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[11],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[12],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[13],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[14],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[15],"clicked",G_CALLBACK(calculate), NULL);
	g_signal_connect(widget.ButtonToggle[16],"clicked",G_CALLBACK(calculate), NULL);
	gtk_widget_show_all(widget.dialog);
}

int main(int argc,char**argv){
	GtkApplication*Application;
	gtk_init(&argc, &argv);
	int position;
	Application = gtk_application_new("org.gtk.calculator", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(Application,"activate", G_CALLBACK(activate), NULL);
	position = g_application_run(G_APPLICATION(Application), argc, argv);
	g_object_unref(Application);

return position;
}

