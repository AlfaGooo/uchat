#include "uchat.h"

#define IMAGE_USER_1 user1.jpg

//мой
 typedef struct s_user {
    GtkApplication *app;
    GtkWidget *euser, *epass, *epass2, *email, *sex1, *entry1, *entry2;
    GtkWidget *ap_entry1, *ap_entry2;
    GtkWidget *a_label4, *a_label6;
    GtkWidget *chat_label1;
    GtkWidget *chat_entry;
    GtkWidget *main_window, *e_window, *reg_window, *reg_right_wind, *a_window, *ap_window, *chat_window;
    const char *user ;
    const char *pass ;
    const char *pass2 ;
    const char *email1 ;
    const char *sex;
    int fl;
    const char *name;
    const char *surname;
    const char *current;
    int theme;
    int deth;
    char **argv;
    int sfd;
    int f_exit;
    pthread_mutex_t Lock;
    int bufsize;
    char *snd, *rcv;
}   t_user;


// static GtkWidget *make_box( gboolean homogeneous,
//                             gint     spacing,
//                             gboolean expand,
//                             gboolean fill,
//                             guint    padding ) 
// {

void mx_open_dialog(GtkWidget *button, void *void_client) {
    t_client_main *c = (t_client_main*)void_client;
    
    gtk_widget_show_all(c->but);
}

// GtkWidget *user, *pass;
//     GtkWidget *button_1;
//     GtkWidget *box_left, *box_center, *box_right, *frame;
//     GtkWidget *log1, *log2, *log3, *log4;
//     GtkWidget *label, *label1, *label2, *label3, *label4;

//     main = gtk_application_window_new(c->win);
//     gtk_window_new(GTK_WINDOW_TOPLEVEL);
//     gtk_window_set_position(GTK_WINDOW(main), GTK_WIN_POS_CENTER);
//     gtk_window_set_title(GTK_WINDOW(main), "UCHAT");
//     gtk_window_set_default_size(GTK_WINDOW(main), WINDOW_MAIN_WEIGHT, WINDOW_MAIN_HEIGHT);

//     button = gtk_button_new_with_label ("Open dialog");
//     g_signal_connect(c->but, "clicked", G_CALLBACK(mx_open_dialog), c);   

//     //mycode
//     GtkCssProvider *provider = gtk_css_provider_new();
//     GtkStyleContext *context = gtk_widget_get_style_context(box_left);
//     gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider), "* {\n background-color: RGB(4,9,82);\n }\n", -1, NULL); //темний
//     gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

//     // t_user *s = (t_user*)data;
//     // label = gtk_label_new("Это пример виджета метки");
//     label = gtk_label_new("Логин");
//     label1 = gtk_label_new("ROOM1");
//     label2 = gtk_label_new("ROOM2");

//     box_left = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//     box_center = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//     box_right = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

//     log1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//     log2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);


void gtk_loop(GtkWidget *window, void *void_client) {
    t_client_main *c = (t_client_main*)void_client;
    GtkWidget *button = NULL;
    GtkWidget *main = NULL;

    GtkWidget *user, *pass;
    GtkWidget *button_1, *button_2;
    GtkWidget *box_left, *box_center, *box_right, *label, *boxnew, *label2, *label3, *label4, *box;
    GtkWidget *button1, *button2, *button3, *button4, *button_out, *mesage;

    main = gtk_application_window_new(c->win);
    gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(main), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(main), "UCHAT");
    gtk_window_set_default_size(GTK_WINDOW(main), WINDOW_MAIN_WEIGHT, WINDOW_MAIN_HEIGHT);

    button = gtk_button_new_with_label ("Open dialog");
    g_signal_connect(c->but, "clicked", G_CALLBACK(mx_open_dialog), c);   

    //mycode
    // GtkCssProvider *provider = gtk_css_provider_new();
    // GtkStyleContext *context = gtk_widget_get_style_context(box_left);
    // gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider), "* {\n background-color: RGB(4,9,82);\n }\n", -1, NULL); //темний
    // gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // t_user *s = (t_user*)data;
    // label = gtk_label_new("Это пример виджета метки");
    label = gtk_label_new("Логин");
    label2 = gtk_label_new("wind");
    label3 = gtk_label_new("user");
    label4 = gtk_label_new("dop");
    // label1 = gtk_label_new("ROOM1");
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    box_left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    box_center = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    box_right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    boxnew = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    button_2 = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    mesage = gtk_button_new_with_label("Отправить");
    // log1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_set_border_width(GTK_CONTAINER(box_left), 20);

    gtk_box_get_baseline_position (GTK_BOX(box_left));
    gtk_box_set_spacing(GTK_BOX(box_left), 200);
    // gtk_container_set_border_width(GTK_CONTAINER(box_left), 20);

    gtk_container_add(GTK_CONTAINER(main), box_left);
    button1 = gtk_button_new_with_label("Все пользователи");
    button2 = gtk_button_new_with_label("Невролог");
    button3 = gtk_button_new_with_label("Хирург");
    mesage = gtk_button_new_with_label("Отправить");
    g_signal_connect(button1, "clicked", G_CALLBACK(NULL), box_left);
    gtk_container_add(GTK_CONTAINER(box_left), label);
    gtk_container_add(GTK_CONTAINER(box_left), button1);
    gtk_container_add(GTK_CONTAINER(box_left), button2);
    gtk_container_add(GTK_CONTAINER(box_left), button3);
    gtk_container_add(GTK_CONTAINER(box_center), label2);

    gtk_container_add(GTK_CONTAINER(box_right), button_2);
    gtk_container_add(GTK_CONTAINER(boxnew), box_left);
    gtk_container_add(GTK_CONTAINER(boxnew), box_center);

    gtk_box_pack_start(GTK_BOX(box), boxnew, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(box), box_right);
    // button_1 = gtk_button_new_with_label ("Зарегистрироваться");
    // g_signal_connect(button_1, "clicked", G_CALLBACK(NULL), box_left);
    
    // gtk_container_add(GTK_CONTAINER(box_left), button_1);
    

    // gtk_box_pack_start (GTK_BOX (box_left), gtk_label_new ("Окно"), TRUE, FALSE, 100);
    // gtk_box_pack_start (GTK_BOX (box_left), gtk_label_new ("Юзеры"), TRUE, TRUE, 0);
//     GtkWidget *grid, *child1, *child2, *log1 ;
//     log1 = gtk_label_new("full");

//this segment
//     grid = gtk_grid_new ();
//     gtk_widget_set_hexpand (log1, TRUE);
//     gtk_widget_set_halign (log1, GTK_ALIGN_CENTER);
//     gtk_grid_attach (GTK_GRID (grid), log1, 0, 0, 1, 1);
//     child2 = gtk_label_new ("Два");
//     gtk_widget_set_hexpand (child2, TRUE);
//   gtk_widget_set_halign (child1, GTK_ALIGN_FILL);
//   gtk_grid_attach_next_to (GTK_GRID (grid), child2, child1, GTK_POS_RIGHT, 1, 1);

//   gtk_container_add(GTK_CONTAINER(box_left), label);
//   gtk_container_add(GTK_CONTAINER(log1), label1);
    
    // gtk_container_add(GTK_CONTAINER(box_left), button);
    
    

    // GtkWidget *box;
    // box = gtk_hbox_new (homogeneous, spacing);
    // gtk_container_add(GTK_CONTAINER(main), box);
    // gtk_container_set_border_width(GTK_CONTAINER(box), 40);

    // gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);

    // gpointer data;
    // t_user *s = (t_user*)data;
    // s->user = gtk_entry_get_text(GTK_ENTRY(s->euser)); //поле ввод сообщения

    //mycode

    gtk_widget_show_all(main);
}





void *mx_run_gtk(void *void_client) {
    t_client_main *c = (t_client_main*)void_client;
    int status = 0;

    c = malloc(sizeof(t_client_main));
    gtk_init(NULL, NULL);
    c->win = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE); 
    g_signal_connect(c->win, "activate", G_CALLBACK(gtk_loop), c);
    status = g_application_run(G_APPLICATION(c->win), 0, NULL);
    g_object_unref(c->win);
    return NULL;
}

int main(int argc, char *argv[]) {
    void *client = NULL;
    pthread_t thread_send = 0;
    pthread_t thread_recv = 0;

    if (argc != 3)
        mx_print_error("Usage ./uchat_client %IP adress %port\n", 1, true);

    //connect to server

    mx_run_gtk((void*)client);
}
