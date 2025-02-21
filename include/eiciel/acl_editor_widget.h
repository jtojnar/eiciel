
/*
    Eiciel - GNOME editor of ACL file permissions.
    Copyright (C) 2004-2022 Roger Ferrer Ibáñez

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,  USA
*/
#ifndef EICIEL_MAIN_WINDOW_HPP
#define EICIEL_MAIN_WINDOW_HPP

#include "config.h"

#include "eiciel/i18n.h"

#include "eiciel/acl_element_kind.h"
#include "eiciel/acl_list_widget.h"
#include "eiciel/participant_list_widget.h"
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/infobar.h>
#include <gtkmm/label.h>
#include <gtkmm/progressbar.h>
#include <set>
#include <string>

namespace eiciel {

class ACLEditorController;

class ACLEditorWidget : public Gtk::Box {
public:
    ACLEditorWidget(ACLEditorController* cont);
    virtual ~ACLEditorWidget();

    void initialize(const Glib::ustring& s);
    bool opened_file();

    void set_active(bool b);

    Glib::ustring last_error();

    void show_info_bar();
    void hide_info_bar();

    void can_edit_enclosed_files(bool b);
    void set_recursive_progress(double);

private:
    ACLEditorController* controller;
    Glib::RefPtr<Gtk::InfoBar> info_bar;
    Glib::RefPtr<Gtk::Label> info_bar_label;
    Glib::RefPtr<Gtk::ProgressBar> info_bar_progress;
    Glib::RefPtr<Gtk::Box> main_box;
    Glib::RefPtr<Gtk::Button> edit_enclosed_files;

    void there_is_no_file();
    void do_edit_enclosed_files();
};

}

#endif
