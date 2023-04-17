#include "perspropty.h"
#include "passwgen.h"
#include <stdio.h>
/*Инициализирует двойной массив для хранения сгенерированных строк паролей.*/
void messages_init(struct AddRowTextView* adrwtv, int* len_passw){
	adrwtv->messages = (char*)calloc(sizeof(char), (*len_passw+1));
	char* password = passwgen(len_passw);
	strcpy (adrwtv->messages, password);
	free(password);
}

/*Расширяет уже инициализированный массив, чтобы можно было добавить новый пароль.*/
void messages_extension(struct AddRowTextView* adrwtv, int* len_passw){
	/*Получаем последний индекс указателя двойного массива.*/
	memset(adrwtv->messages, 0, *len_passw);
	char* password = passwgen(len_passw);
	strcpy (adrwtv->messages, password);
	free(password);
}

/*Освобождает память выделенного двойного массива.*/
void messages_freeing(struct AddRowTextView* adrwtv){
	free(adrwtv->messages);
	adrwtv->messages = NULL;

}


void add_row(GtkWidget *widget,
             gpointer   user_data)
{ 

	GtkTextIter iter;
	GtkWidget* new_row;
	GtkWidget* text_view;
	GtkTextBuffer* buffer;
	GtkCssProvider* provider;
	GtkStyleContext *context_tv, *context_rw;
	int len_passw = 20;//Заданная длина пароля.
	/*Приведем указатель к нужному типу, чтобы не возникло проблем.*/
	struct AddRowTextView* adrw = (struct AddRowTextView*)user_data;
  	/*Получим указатель на GtkListBox.*/
	GObject* _listbox = adrw->listbox;
	/*Автоскроллинг.*/
	GtkAdjustment *adj;

	if(adrw->messages == NULL){
		messages_init(adrw, &len_passw);
	}else{	
		messages_extension(adrw, &len_passw);}

	char*  password = adrw->messages;//#####Пароль#####

	/*Новая строка контейнера ListBox 
	куда будут переданы остальные виджеты*/
	new_row = gtk_list_box_row_new();
	set_row_prop(GTK_WIDGET(new_row));
  
	/*Новый виджет TextView в котором
	будет отображаться строка со сгенерированнным паролем.*/
	text_view = gtk_text_view_new();
	set_textview_prop(GTK_WIDGET(text_view));
	
	/*Добавим в так называемую строку-контейнер новый виджет,
	в данном случае это будет text_view.*/
	gtk_container_add (GTK_CONTAINER(new_row), GTK_WIDGET(text_view));
	//                          +
	//Добавим новую строку, передав ссылку на нее в спец. метод.
	gtk_container_add (GTK_CONTAINER(_listbox), GTK_WIDGET(new_row));

	/*Передадим текст, который будет отображаться в виджете */
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
	gtk_text_buffer_set_text (buffer, "", 0);
	gtk_text_buffer_get_iter_at_offset (buffer, &iter, 1);
	gtk_text_buffer_insert (buffer, &iter, password, -1);

	/*Прокручиваем окно в самый низ.*/
	adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(adrw->scrolled_window));
	gtk_adjustment_set_value(adj, gtk_adjustment_get_upper(adj));
	gtk_widget_queue_draw(GTK_WIDGET(adrw->scrolled_window));



	//Сообщение в консоли.
	g_print ("button1: callback [add_row]\n");
}

/*Удалит все сгенерированнные пароли из контейнера ListBox.*/
void all_destroy(GtkWidget *widget,
        	gpointer   user_data){

	GList *iter, *child_list;
	/*Приведем указатель к нужному типу, чтобы не возникло проблем.*/
	struct AddRowTextView* adrw = (struct AddRowTextView*)user_data;
	GObject* _listbox = adrw->listbox;
	char* messages = adrw->messages;

	child_list = gtk_container_get_children(GTK_CONTAINER(_listbox));

	//Проитерируем список элементов, уничтожим их и освободим память.
	for(iter = child_list; iter != NULL; iter = g_list_next(iter))
		gtk_container_remove(GTK_CONTAINER(_listbox), iter->data);

	// Освобождает всю память используемую child_list (GList структура).
	g_list_free(child_list);

	//Сообщение в консоли.
	g_print ("button2: callback [all_destroy]\n");

	// Освободим двойной массив и его содержимое
	messages_freeing(adrw);
}


/*Определит некоторые параметры для ListBoxRow.*/
void set_row_prop(GtkWidget* new_row){

	gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(new_row), FALSE);
	gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(new_row), FALSE);
	gtk_widget_set_visible(GTK_WIDGET(new_row), TRUE);
	gtk_widget_set_can_focus(GTK_WIDGET(new_row), FALSE);
	gtk_widget_set_margin_start(GTK_WIDGET(new_row), 5);
	gtk_widget_set_margin_end(GTK_WIDGET(new_row), 5);
	gtk_widget_set_margin_top(GTK_WIDGET(new_row), 2);
	gtk_widget_set_margin_bottom(GTK_WIDGET(new_row), 2);

}


/*Определит некоторые параметры для TextView.*/
void set_textview_prop(GtkWidget* text_view){
	/*Задаст имя виджету.*/
	gtk_widget_set_name(GTK_WIDGET(text_view), "commandview");
	/*Отключит перетаскивание текста с виджета.*/
	gtk_drag_dest_unset(GTK_WIDGET(text_view));
	gtk_widget_set_can_default(GTK_WIDGET(text_view), FALSE);
	gtk_widget_set_visible(GTK_WIDGET(text_view), TRUE);
	gtk_widget_set_can_focus(GTK_WIDGET(text_view), TRUE);
	gtk_text_view_set_pixels_above_lines(GTK_TEXT_VIEW(text_view),5);
	gtk_text_view_set_pixels_below_lines(GTK_TEXT_VIEW(text_view),5);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_NONE);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);
}


/*Передаст отображаемый текст в буфер виджета TextVew.*/
void textview_print(GtkWidget* text_view, GtkTextIter iter, const gchar *text){
	GtkTextBuffer* buffer;
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
	gtk_text_buffer_set_text (buffer, "", 0);
	gtk_text_buffer_get_iter_at_offset (buffer, &iter, 1);
	gtk_text_buffer_insert (buffer, &iter, text, -1);
}