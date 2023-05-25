; Auto-generated. Do not edit!


(cl:in-package hcsr04-msg)


;//! \htmlinclude distance.msg.html

(cl:defclass <distance> (roslisp-msg-protocol:ros-message)
  ((front
    :reader front
    :initarg :front
    :type cl:float
    :initform 0.0)
   (down
    :reader down
    :initarg :down
    :type cl:float
    :initform 0.0)
   (front_time
    :reader front_time
    :initarg :front_time
    :type cl:real
    :initform 0)
   (down_time
    :reader down_time
    :initarg :down_time
    :type cl:real
    :initform 0))
)

(cl:defclass distance (<distance>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <distance>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'distance)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name hcsr04-msg:<distance> is deprecated: use hcsr04-msg:distance instead.")))

(cl:ensure-generic-function 'front-val :lambda-list '(m))
(cl:defmethod front-val ((m <distance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcsr04-msg:front-val is deprecated.  Use hcsr04-msg:front instead.")
  (front m))

(cl:ensure-generic-function 'down-val :lambda-list '(m))
(cl:defmethod down-val ((m <distance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcsr04-msg:down-val is deprecated.  Use hcsr04-msg:down instead.")
  (down m))

(cl:ensure-generic-function 'front_time-val :lambda-list '(m))
(cl:defmethod front_time-val ((m <distance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcsr04-msg:front_time-val is deprecated.  Use hcsr04-msg:front_time instead.")
  (front_time m))

(cl:ensure-generic-function 'down_time-val :lambda-list '(m))
(cl:defmethod down_time-val ((m <distance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader hcsr04-msg:down_time-val is deprecated.  Use hcsr04-msg:down_time instead.")
  (down_time m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <distance>) ostream)
  "Serializes a message object of type '<distance>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'front))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'down))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'front_time)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'front_time) (cl:floor (cl:slot-value msg 'front_time)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'down_time)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'down_time) (cl:floor (cl:slot-value msg 'down_time)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <distance>) istream)
  "Deserializes a message object of type '<distance>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'front) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'down) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'front_time) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'down_time) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<distance>)))
  "Returns string type for a message object of type '<distance>"
  "hcsr04/distance")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'distance)))
  "Returns string type for a message object of type 'distance"
  "hcsr04/distance")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<distance>)))
  "Returns md5sum for a message object of type '<distance>"
  "7c475cd559c7cfc2f328489a1905a9e3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'distance)))
  "Returns md5sum for a message object of type 'distance"
  "7c475cd559c7cfc2f328489a1905a9e3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<distance>)))
  "Returns full string definition for message of type '<distance>"
  (cl:format cl:nil "#前后左右~%float32  front ~%float32  down~%time front_time~%time down_time~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'distance)))
  "Returns full string definition for message of type 'distance"
  (cl:format cl:nil "#前后左右~%float32  front ~%float32  down~%time front_time~%time down_time~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <distance>))
  (cl:+ 0
     4
     4
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <distance>))
  "Converts a ROS message object to a list"
  (cl:list 'distance
    (cl:cons ':front (front msg))
    (cl:cons ':down (down msg))
    (cl:cons ':front_time (front_time msg))
    (cl:cons ':down_time (down_time msg))
))
