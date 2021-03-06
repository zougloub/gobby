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

#ifndef _GOBBY_BROWSER_CONTEXT_COMMANDS_HPP_
#define _GOBBY_BROWSER_CONTEXT_COMMANDS_HPP_

#include "operations/operations.hpp"

#include "dialogs/entry-dialog.hpp"

#include "core/nodewatch.hpp"
#include "core/browser.hpp"
#include "core/filechooser.hpp"

#include <sigc++/trackable.h>

#include <libinfgtk/inf-gtk-account-creation-dialog.h>

namespace Gobby
{

class BrowserContextCommands: public sigc::trackable
{
public:
	BrowserContextCommands(Gtk::Window& parent,
	                       InfIo* io,
	                       Browser& browser, FileChooser& chooser,
	                       Operations& operations,
	                       const CertificateManager& cert_manager,
	                       Preferences& prf);
	~BrowserContextCommands();

protected:
	static void on_populate_popup_static(InfGtkBrowserView* view,
	                                     GtkMenu* menu,
	                                     gpointer user_data)
	{
		static_cast<BrowserContextCommands*>(user_data)->
			on_populate_popup(Glib::wrap(menu));
	}

	static void on_account_created_static(
		InfGtkAccountCreationDialog* dlg,
		gnutls_x509_privkey_t key,
		InfCertificateChain* certificate,
		const InfAclAccount* account,
		gpointer user_data)
	{
		static_cast<BrowserContextCommands*>(user_data)->
			on_account_created(key, certificate, account);
	}

	void on_menu_node_removed();
	void on_menu_deactivate();

	void on_populate_popup(Gtk::Menu* menu);
	void on_popdown();

	// Context commands
	void on_disconnect(InfcBrowser* browser);
	void on_create_account(InfBrowser* browser);
	void on_remove(InfBrowser* browser);

	void on_new(InfBrowser* browser, InfBrowserIter iter,
	            bool directory);
	void on_open(InfBrowser* browser, InfBrowserIter iter);
	void on_permissions(InfBrowser* browser, InfBrowserIter iter);
	void on_delete(InfBrowser* browser, InfBrowserIter iter);

	void on_dialog_node_removed();
	void on_create_account_response(int response_id);
	void on_account_created(gnutls_x509_privkey_t key,
	                        InfCertificateChain* certificate,
	                        const InfAclAccount* account);
	void on_account_created_response(int response_id);
	void on_new_response(int response_id, InfBrowser* browser,
	                     InfBrowserIter iter, bool directory);
	void on_open_response(int response_id, InfBrowser* browser,
	                      InfBrowserIter iter);
	void on_permissions_response(int response_id);

	Gtk::Window& m_parent;
	InfIo* m_io;
	Browser& m_browser;
	FileChooser& m_file_chooser;
	Operations& m_operations;
	const CertificateManager& m_cert_manager;
	Preferences& m_preferences;

	// Browser item for which
	Gtk::Menu* m_popup_menu;
	std::auto_ptr<NodeWatch> m_watch;
	std::auto_ptr<Gtk::Dialog> m_dialog;

	gulong m_populate_popup_handler;
};

}

#endif // _GOBBY_BROWSER_CONTEXT_COMMANDS_HPP_
