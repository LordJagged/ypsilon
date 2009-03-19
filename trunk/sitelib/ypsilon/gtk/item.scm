#!nobacktrace
;;; Ypsilon Scheme System
;;; Copyright (c) 2004-2009 Y.FUJITA / LittleWing Company Limited.
;;; See license.txt for terms and conditions of use.

(library (ypsilon gtk item)

  (export gtk_item_deselect
          gtk_item_get_type
          gtk_item_select
          gtk_item_toggle)

  (import (rnrs) (ypsilon ffi))

  (define lib-name
    (cond (on-darwin  "Gtk.framework/Gtk")
          (on-linux   "libgtk-x11-2.0.so.0")
          (on-freebsd "libgtk-x11-2.0.so.0")
          (on-openbsd "libgtk-x11-2.0.so.0")
          (on-windows "libgtk-win32-2.0-0.dll")
          (else
           (assertion-violation #f "can not locate GTK library, unknown operating system"))))

  (define lib (load-shared-object lib-name))

  (define-syntax define-function
    (syntax-rules ()
      ((_ ret name args)
       (define name (c-function lib lib-name ret name args)))))

  (define-syntax define-function/va_list
    (syntax-rules ()
      ((_ ret name args)
      (define name (lambda x (assertion-violation 'name "va_list argument not supported"))))))

  ;; void gtk_item_deselect (GtkItem* item)
  (define-function void gtk_item_deselect (void*))

  ;; GType gtk_item_get_type (void)
  (define-function unsigned-long gtk_item_get_type ())

  ;; void gtk_item_select (GtkItem* item)
  (define-function void gtk_item_select (void*))

  ;; void gtk_item_toggle (GtkItem* item)
  (define-function void gtk_item_toggle (void*))

  ) ;[end]
