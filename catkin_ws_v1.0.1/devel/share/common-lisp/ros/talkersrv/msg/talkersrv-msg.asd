
(cl:in-package :asdf)

(defsystem "talkersrv-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :mavros_msgs-msg
)
  :components ((:file "_package")
    (:file "contrl" :depends-on ("_package_contrl"))
    (:file "_package_contrl" :depends-on ("_package"))
  ))