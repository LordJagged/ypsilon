#!nobacktrace
(library (concurrent)
  (export call-with-spawn
          current-exception-printer
          define-thread-variable
          future
          mailbox?
          make-mailbox
          make-messenger-bag
          make-shared-bag
          make-shared-queue
          make-uuid
          messenger-bag-get!
          messenger-bag-put!
          messenger-bag?
          recv
          send
          shared-bag-get!
          shared-bag-put!
          shared-bag?
          shared-queue-pop!
          shared-queue-push!
          shared-queue-shutdown
          shared-queue?
          shutdown-mailbox
          shutdown-object?
          spawn
          thread-id
          timeout-object?)
  (import (ypsilon concurrent)))