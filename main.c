#include "perspropty.h"
#include "passwgen.h"

int
main (int   argc,
      char *argv[])
{ 
  /*Сборщик, собирает интерфейс на основе .glade xml-файла. */
  GtkBuilder *builder;
  // Главное окно нашего приложения.
  GObject *MainWindow;
  /*Содержит в себе списочные поля-контейнеры для textview_listbox. */
  GObject *listbox;
  GObject *button1;// Указатель на кнопку1
  GObject *button2;// Указатель на кнопку2
  /*Объект, реализующий интерфейс, для работы с CSS-стилями виджетов.*/
  GtkCssProvider* provider;
  /*Указатель на структуру ошибок, которая содержит 
  (или будет содержать) информацию о возникшей ошибке.*/
  GError *error = NULL;

  /*Указатель на интерфейс структуры окна прокрутки scrolled_window.*/
  GObject* scrolled_window;

  /*Объявим указатель на объект структуры AddRowTextView.*/
  struct AddRowTextView adrw;
  /*Обнулим двойной указатель.*/
  adrw.messages = NULL;

  /*Инициализируем установки виджетам, и получаем параметры командной строки. */
  gtk_init (&argc, &argv);

  /*Зададим глобальные свойства стилей, для окна нашего приложения.*/
  provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "styles.css", NULL);
  gtk_style_context_add_provider_for_screen(
    gdk_screen_get_default(), 
    GTK_STYLE_PROVIDER(provider), 
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
  );

  /*Создадим экземпляр GtkBuilder и загрузим 
  описание пользовательского интерфейса */
  builder = gtk_builder_new ();

  /*Если проверка данных для сборщика не пройдена, 
  вернуть сообщение об ошибке.*/
  if (gtk_builder_add_from_file (builder, "uiform_updt.glade", &error) == 0)
  {
    g_printerr ("Error loading file: %s\n", error->message);
    g_clear_error (&error);
    return 1;
  }

  /*Указатель на интерфейс окна прокрутки.*/
  adrw.scrolled_window = gtk_builder_get_object(builder, "scrolled_window");

  /*Получим указатель для работы с контейнером listbox (GtkListBox)*/
  adrw.listbox = gtk_builder_get_object (builder, "listbox");

  /*Подключим обработчики сигналов к созданным виджетам. */
  MainWindow = gtk_builder_get_object (builder, "MainWindow");

  /*Зададим имя главного окна нашего приложения.*/
  gtk_window_set_title(GTK_WINDOW(MainWindow), "Password Generator");

  GdkPixbuf *icon = gdk_pixbuf_new_from_file("key.png", NULL);
  gtk_window_set_icon(GTK_WINDOW(MainWindow), icon);

  // Задает минимальный размер окна, мньше которого сделать нельзя.
  gtk_widget_set_size_request (GTK_WIDGET(MainWindow), 440, 300);
  g_signal_connect (MainWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  /*Подключим обработчик сигнала кнопки к функции "add_row".*/
  button1 = gtk_builder_get_object (builder, "button1");
  g_signal_connect (button1, "clicked", G_CALLBACK (add_row), &adrw);

  /*Подключим обработчик сигнала кнопки1 к функции "print_hello".*/
  button2 = gtk_builder_get_object (builder, "button2");
  g_signal_connect (button2, "clicked", G_CALLBACK (all_destroy), &adrw);

  /*Входим в основной цикл и ждем действий пользователя */
  gtk_main ();

  return 0;
}