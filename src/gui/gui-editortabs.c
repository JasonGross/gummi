/**
 * @file   gui-editortabs.c
 * @brief
 *
 * Copyright (C) 2010 Gummi-Dev Team <alexvandermey@gmail.com>
 * All Rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "gui-editortabs.h"

#include <gtk/gtk.h>

#include "environment.h"
#include "gui/gui-main.h"

extern Gummi* gummi;
extern GummiGui* gui;

GuEditortabsGui* editortabsgui_init (GtkBuilder* builder) {
    g_return_val_if_fail (GTK_IS_BUILDER (builder), NULL);
    
    GuEditortabsGui* et = g_new0 (GuEditortabsGui, 1);
    
    et->tab_notebook =
        GTK_NOTEBOOK (gtk_builder_get_object (builder, "tab_notebook"));
    
    return et;
}



GtkWidget* editortabsgui_create_label (const gchar *filename) {
    GtkWidget *tablabel;
    gchar *tabname;
    
    gint nr_pages = gtk_notebook_get_n_pages (g_tabs_notebook);
    
    if (filename == NULL) 
        tabname = g_strdup_printf ("Unsaved Document %d", (nr_pages+1));
    else 
        tabname = g_path_get_basename (filename);
        
    tablabel = gtk_label_new (tabname);
    gtk_widget_set_tooltip_text (tablabel, filename);
    
    return tablabel;
}

void editortabsgui_change_label (const gchar *filename) {
    GtkWidget *tablabel;
    GtkWidget *tmp;
    
    /* TODO; Fix that GTK warning! */
    gint cur = gtk_notebook_get_current_page(g_tabs_notebook);
    tmp = gtk_notebook_get_nth_page(g_tabs_notebook, cur);
    
    tablabel = editortabsgui_create_label(filename);
    gtk_notebook_set_tab_label (g_tabs_notebook, tmp, tablabel);
    
}


gint editortabsgui_create_page (GuEditor* editor, const gchar* filename) {
    GtkWidget *scrollwindow;
    GtkWidget *tablabel;
    
    /* creating tab object; scrollwindow */
    scrollwindow = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollwindow),
                                    GTK_POLICY_AUTOMATIC, 
                                    GTK_POLICY_AUTOMATIC);
    gtk_container_add (GTK_CONTAINER (scrollwindow), GTK_WIDGET (editor->view));

    tablabel = editortabsgui_create_label(filename);

    /* adding new tab to the gui */
    gint position = gtk_notebook_append_page (
        GTK_NOTEBOOK (g_tabs_notebook), scrollwindow, tablabel);
        
    gtk_widget_show(scrollwindow);
    gtk_widget_show(GTK_WIDGET(editor->view));

    return position;
}



gint editortabsgui_remove_page () {
    gint active_page = gtk_notebook_get_current_page(g_tabs_notebook);
    gtk_notebook_remove_page(g_tabs_notebook, active_page);
    return active_page;
}

