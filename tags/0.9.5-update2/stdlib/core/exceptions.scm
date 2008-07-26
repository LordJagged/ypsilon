#!core
;;; Ypsilon Scheme System
;;; Copyright (c) 2004-2008 Y.FUJITA, LittleWing Company Limited.
;;; See license.txt for terms and conditions of use.

(library (core exceptions)

  (export with-exception-handler
          guard
          raise
          raise-continuable)

  (import (core primitives))

  ;; Reference:
  ;; SRFI 34: Exception Handling for Programs by Richard Kelsey and Michael Sperber
  ;; http://srfi.schemers.org/srfi-34/

  (define-syntax guard
    (syntax-rules (else)
      ((_ (var clause ... (else e1 e2 ...)) b1 b2 ...)
       (call/cc
        (lambda (cont)
          (with-exception-handler
           (lambda (var)
             (call-with-values
              (lambda () (cond clause ... (else e1 e2 ...)))
              cont))
           (lambda () b1 b2 ...)))))
      ((_ (var clause ...) b1 b2 ...)
       ((call/cc
         (lambda (guard-k)
           (with-exception-handler
            (lambda (condition)
              ((call/cc
                (lambda (handler-k)
                  (guard-k
                   (lambda ()
                     (let ((var condition))
                       (cond clause ...
                             (else (handler-k (lambda () (raise condition))))))))))))
            (lambda ()
              (call-with-values
               (lambda () b1 b2 ...)
               (lambda args (guard-k (lambda () (apply values args)))))))))))))

  ) ;[end]
