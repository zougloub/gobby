/* Gobby - GTK-based collaborative text editor
 * Copyright (C) 2008-2014 Armin Burgmeier <armin@arbur.net>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "dialogs/connection-dialog.hpp"
#include "util/i18n.hpp"

// TODO: Merge this with entrydialog and passworddialog to a slightly more
// generic entry dialog.

Gobby::ConnectionDialog::ConnectionDialog(Gtk::Window& parent):
	Gtk::Dialog(_("Connect to Server"), parent), m_box(false, 12),
	m_rightbox(false, 6),
	m_promptbox(false, 12),
	m_intro_label(_("Please enter a host name with which "
	                "to establish a connection.")),
	m_prompt_label(_("_Remote Endpoint:"), true)
{
	m_image.set_from_icon_name("network-server", Gtk::ICON_SIZE_DIALOG);
	m_prompt_label.set_mnemonic_widget(m_entry);
	m_promptbox.pack_start(m_prompt_label, Gtk::PACK_SHRINK);
	m_entry.set_activates_default(true);
	m_promptbox.pack_start(m_entry, Gtk::PACK_EXPAND_WIDGET);
	m_rightbox.pack_start(m_intro_label, Gtk::PACK_SHRINK);
	m_rightbox.pack_start(m_promptbox, Gtk::PACK_SHRINK);
	m_box.pack_start(m_image, Gtk::PACK_SHRINK);
	m_box.pack_start(m_rightbox, Gtk::PACK_EXPAND_WIDGET);

	m_box.show_all();

	get_vbox()->set_spacing(6);
	get_vbox()->pack_start(m_box, Gtk::PACK_EXPAND_WIDGET);

	set_resizable(false);
	set_border_width(12);
}

Glib::ustring Gobby::ConnectionDialog::get_host_name() const
{
	return m_entry.get_text();
}

void Gobby::ConnectionDialog::on_show()
{
	Gtk::Dialog::on_show();

	// We can't do this in the constructor, because the buttons are added
	// by the caller after the widget has been constructed.
	set_default_response(Gtk::RESPONSE_ACCEPT);

	m_entry.select_region(0, m_entry.get_text().length());
	m_entry.grab_focus();
}
