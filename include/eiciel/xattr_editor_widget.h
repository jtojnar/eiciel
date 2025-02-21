/*
    Eiciel - GNOME editor of Participant file permissions.
    Copyright (C) 2022 Roger Ferrer Ibáñez

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
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
   USA
*/

#ifndef XATTR_EDITOR_WIDGET_H
#define XATTR_EDITOR_WIDGET_H

#include "config.h"

#include "eiciel/i18n.h"

#include "eiciel/xattr_editor_controller.h"
#include "eiciel/xattr_item.h"
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/columnview.h>
#include <gtkmm/entry.h>
#include <gtkmm/editablelabel.h>
#include <unordered_map>

namespace eiciel {

class XAttrEditorWidget : public Gtk::Box {
public:
  XAttrEditorWidget(XAttrEditorController *controller);
  virtual ~XAttrEditorWidget();
  void set_active(bool b);

  void set_readonly(bool b);

  void clear_attributes();
  void add_attribute(const Glib::ustring &name, const Glib::ustring &value);

private:
  void remove_button_signal(Gtk::Button *btn);
  void keep_button_signal(Gtk::Button *btn, sigc::connection c);
  void remove_label_signal(Gtk::EditableLabel *btn);
  void keep_label_signal(Gtk::EditableLabel *btn, sigc::connection c);

  bool attribute_name_is_used(const Glib::ustring &name);

  XAttrEditorController *controller;

  Glib::RefPtr<XAttrListItemModel> model;

  Glib::RefPtr<Gtk::Box> top_level;
  Glib::RefPtr<Gtk::ColumnView> column_view;
  Glib::RefPtr<Gtk::Entry> entry_name;
  Glib::RefPtr<Gtk::Entry> entry_value;
  Glib::RefPtr<Gtk::Button> button_add;

  std::unordered_map<Gtk::Button *, sigc::connection> button_signal_map;
  std::unordered_map<Gtk::EditableLabel *, sigc::connection> label_signal_map;

  bool readonly_mode = false;

  gulong entry_name_signal_activate;
  gulong entry_value_signal_activate;
};
} // namespace eiciel

#endif // XATTR_EDITOR_WIDGET_H
