/*
   Eiciel - GNOME editor of ACL file permissions.
   Copyright (C) 2004-2019 Roger Ferrer Ibáñez

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
#include "config.h"
#include "eiciel/acl_editor_widget.h"
#include "eiciel/acl_editor_controller.h"
#include "eiciel/acl_list_widget.h"
#include "eiciel/participant_list_widget.h"

namespace eiciel {

// Constructor
ACLEditorWidget::ACLEditorWidget(ACLEditorController *cont) : controller(cont) {
  controller->set_view(this);

  auto refBuilder = Gtk::Builder::create_from_resource(
      "/org/roger_ferrer/eiciel/acl_editor_widget.ui");

  auto top_level = refBuilder->get_object<Gtk::Box>("top-level");
  append(*top_level);

  info_bar = refBuilder->get_object<Gtk::InfoBar>("info-bar");
  info_bar_label = refBuilder->get_object<Gtk::Label>("info-bar-label");
  info_bar_progress = refBuilder->get_object<Gtk::ProgressBar>("info-bar-progress");

  main_box = refBuilder->get_object<Gtk::Box>("main-editor-box");

  auto *acl_list =
      Gtk::make_managed<ACLListWidget>(controller, ACLListWidgetMode::DEFAULT);
  auto box_for_acl_list = refBuilder->get_object<Gtk::Box>("box-for-acl-list");
  box_for_acl_list->append(*acl_list);

  auto *participant_list = Gtk::make_managed<ParticipantListWidget>(
      controller, ParticipantListWidgetMode::SINGLE_PANE);
  auto box_for_participant_list =
      refBuilder->get_object<Gtk::Box>("box-for-participant-list");
  box_for_participant_list->append(*participant_list);

  edit_enclosed_files =
      refBuilder->get_object<Gtk::Button>("edit-enclosed-files");
  edit_enclosed_files->signal_clicked().connect(
      [this]() { controller->edit_enclosed_files(); });

  set_active(false);
}

ACLEditorWidget::~ACLEditorWidget() {}

void ACLEditorWidget::set_active(bool b) { main_box->set_sensitive(b); }

void ACLEditorWidget::show_info_bar()
{
    info_bar->set_visible(true);
}

void ACLEditorWidget::hide_info_bar()
{
    info_bar->set_visible(false);
}

void ACLEditorWidget::set_recursive_progress(double d)
{
    info_bar_progress->set_fraction(d);
}

void ACLEditorWidget::can_edit_enclosed_files(bool b)
{
    edit_enclosed_files->set_sensitive(b);
}

void ACLEditorWidget::do_edit_enclosed_files()
{
    controller->edit_enclosed_files();
}

}
