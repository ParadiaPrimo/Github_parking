static void messageError();
static void messageErrorCar();
static void messageSuccessAccountCreation();
static void messageAccountAlreadyExist();
static void messageBookingAlreadyExist();
static void messageAccountNotCreated();
static void messageBookingNotCreated();
static void messageAccountNotFound();
static void messageSuccessCancelled();
static void messageSuccessPayment();
static void messageErrorPassword();
static void messageErrorConnection();
static void messageErrorInvalidCC();
static void messageSubscriptionChosen();
static void messageEnterParking();
static void messageLeavingParking();
static void messageSuccessReservation();
static void messageSuccessSubscribeChange();
static void messageCarIsNotRegistered();
static void messageBookingAlreadyActive();

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

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "An account already exist.");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageBookingAlreadyExist(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Another booking is already registered");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageAccountNotCreated(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your account cannot be created, please contact an administrator");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageBookingNotCreated(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your booking cannot be found, please contact an administrator");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageAccountNotFound(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your account cannot be found, please contact an administrator");
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

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Payment registered\n");
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

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Thank you!\n");
  gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG (dialog), "Your choice has been registered.");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageEnterParking(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Welcome!\n");
  gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG (dialog), "Your car has been parked successfully.");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageLeavingParking(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Goodbye!\n");
  gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG (dialog), "You are leaving the parking. Please don't forget your bill .");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageSuccessReservation(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Reservation completed!\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your booking has been created.");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}

static void messageSuccessSubscribeChange(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, "Reservation completed!\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "Your account has been successfully updated");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageCarIsNotRegistered(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Car isn't registered!\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "The specified car isn't registered.");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
static void messageBookingAlreadyActive(){

  GtkWidget *dialog;
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_POPUP);

  dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error!\n");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "The booking is already active.");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy (dialog);

}
