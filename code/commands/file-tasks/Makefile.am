noinst_LIBRARIES = libgobby-file-tasks.a

libgobby_file_tasks_a_SOURCES = \
	task-export-html.cpp \
	task-new.cpp \
	task-open.cpp \
	task-open-file.cpp \
	task-open-location.cpp \
	task-open-multiple.cpp \
	task-save.cpp \
	task-save-all.cpp

noinst_HEADERS = \
	task-export-html.hpp \
	task-new.hpp \
	task-open.hpp \
	task-open-file.hpp \
	task-open-location.hpp \
	task-open-multiple.hpp \
	task-save.hpp \
	task-save-all.hpp

appicondir = $(datadir)/pixmaps
pixmapdir = $(datadir)/pixmaps/gobby-0.5

AM_CPPFLAGS = $(gobby_CFLAGS) $(infinote_CFLAGS) \
              -I$(top_srcdir)/code
