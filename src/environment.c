/**
 * @file    environment.c
 * @brief    
 *
 * Copyright (C) 2010-2011 Gummi-Dev Team <alexvandermey@gmail.com>
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

#include "configfile.h"
#include "environment.h"
#include "gui/gui-main.h"
#include "utils.h"

Gummi* gummi = 0;
GummiGui* gui = 0;

Gummi* gummi_init (GuMotion* mo, GuIOFunc* io, GuLatex* latex, GuBiblio* bib,
                   GuTemplate* tpl, GuSnippets* snip) {
    
    Gummi* g = g_new0 (Gummi, 1);
    g->io = io;
    g->motion = mo;
    g->latex = latex;
    g->biblio = bib;
    g->templ = tpl;
    g->snippets = snip;
    return g;
}

void gummi_new_environment (GuEditor* ec, const gchar* filename) {
    editor_fileinfo_update (ec, filename);
    
    slog (L_INFO, "\n");
    slog (L_INFO, "Environment created for:\n");
    slog (L_INFO, "TEX: %s\n", ec->filename);
    slog (L_INFO, "TMP: %s\n", ec->workfile);
    slog (L_INFO, "PDF: %s\n", ec->pdffile); 

    //iofunctions_reset_autosave (filename);
}

GummiGui* gummi_get_gui (void) {
    return gui;
}

GuEditor* gummi_get_active_editor (void) {
    return gui->tabmanagergui->active_editor;
}

GList* gummi_get_all_tabs (void) {
    return gui->tabmanagergui->tabs;
}

GuIOFunc* gummi_get_io (void) {
    return gummi->io;
}

GuMotion* gummi_get_motion (void) {
    return gummi->motion;
}

GuLatex* gummi_get_latex (void) {
    return gummi->latex;
}

GuBiblio* gummi_get_biblio (void) {
    return gummi->biblio;
}

GuTemplate* gummi_get_template (void) {
    return gummi->templ;
}

GuSnippets* gummi_get_snippets (void) {
    return gummi->snippets;
}

