static void messageError();
static void messageErrorCar();
static void messageSuccessAccountCreation();
static void messageAccountAlreadyExist();
static void messageAccountNotCreated();
static void messageSuccessCancelled();
static void messageSuccessPayment();
static void messageErrorPassword();
static void messageErrorConnection();
static void messageErrorInvalidCC();
static void messageSubscriptionChosen();
static void messageEnterParking();
static void messageLeavingParking();
static void messageSuccessReservation();

//ALL MESSAGE DIALOG POP UP
static void messageError(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "The specified date is wrong");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}

static void messageErrorCar(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "The car number plate is invalid or doesn't exist");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}

static void messageSuccessAccountCreation(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Account created\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your account has been successfully created");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageAccountAlreadyExist(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Account created\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "An account already exist");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageAccountNotCreated(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Account created\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your account cannot be created, please contact an administrator");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageSuccessCancelled(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Cancelled!\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your book has been cancelled successfully!");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageSuccessPayment(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Payment accepted\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your bank account is successfully registered");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}

static void messageErrorPassword(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Warning\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your password is incorrect");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageErrorConnection(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Warning\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Connection failed");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageErrorInvalidCC(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "The specified card number is invalid");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageSubscriptionChosen(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Thank you!\n");
  gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG (dialog), "Your choice has been registered.");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageEnterParking(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Welcome!\n");
  gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG (dialog), "Your car has been parked successfully.");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageLeavingParking(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Goodbye!\n");
  gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG (dialog), "You are leaving the parking.");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageSuccessReservation(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Reservation completed!\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your reservation has been considered. If");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
