#include <cdk.h>

/*
 * This program demonstrates the Cdk dialog widget.
 */
int Hola ()
{
   /* *INDENT-EQLS* */
   CDKSCREEN *cdkscreen = 0;
   CDKDIALOG *question  = 0;
   const char *buttons[] =
   {"</B/24>Continue", "</B16>Configure", "</B16>Exit"};
   const char *message[10];
   const char *mesg[3];
   char temp[100];
   int selection;

   cdkscreen = initCDKScreen (NULL);

   /* Start color. */
   initCDKColor ();

   /* Create the message within the dialog box. */
   message[0] = "<C></U>Warning message";
   message[1] = " ";
   message[2] = "<C>An error has occurred while opening port";
   message[3] = "<C>";
   message[4] = "<C>Maybe the connection is not in the selected port ";
   message[5] = "<C> or maybe yo forgot to give sudo permission to the program";
   message[6] = "<C>";

   /* Create the dialog box. */
   question = newCDKDialog (cdkscreen,
			    CENTER,
			    CENTER,
			    (CDK_CSTRING2) message, 7,
			    (CDK_CSTRING2) buttons, 3,
			    COLOR_PAIR (2) | A_REVERSE,
			    TRUE,
			    TRUE,
			    FALSE);

   /* Check if we got a null value back. */
   if (question == 0)
   {
      /* Shut down Cdk. */
      destroyCDKScreen (cdkscreen);
      endCDK ();

      printf ("Cannot create the dialog box. Is the window too small?\n");
      
   }

   /* Activate the dialog box. */
   selection = activateCDKDialog (question, 0);

   /* Tell them what was selected. */
   if (question->exitType == vESCAPE_HIT)
   {
      mesg[0] = "<C>You hit escape. No button selected.";
      mesg[1] = "";
      mesg[2] = "<C>Press any key to continue.";
      popupLabel (cdkscreen, (CDK_CSTRING2) mesg, 3);
   }
   else if (question->exitType == vNORMAL)
   {

      switch(selection) {
         case 0:
            sprintf (temp, "<C>You selected Continue");
            mesg[0] = temp;
            mesg[1] = "";
            mesg[2] = "<C>Press any key to continue.";
            popupLabel (cdkscreen, (CDK_CSTRING2) mesg, 3);
            break;
         case 1:
            sprintf (temp, "<C>You selected Configure");
            mesg[0] = temp;
            mesg[1] = "";
            mesg[2] = "<C>Press any key to continue.";
            popupLabel (cdkscreen, (CDK_CSTRING2) mesg, 3);
            break;
         case 2:
            sprintf (temp, "<C>You selected exit");
            mesg[0] = temp;
            mesg[1] = "";
            mesg[2] = "<C>Press any key to continue.";
            popupLabel (cdkscreen, (CDK_CSTRING2) mesg, 3);
            break;
      }
      
   }

   /* Clean up. */
   destroyCDKDialog (question);
   //destroyCDKScreen (cdkscreen);   
}