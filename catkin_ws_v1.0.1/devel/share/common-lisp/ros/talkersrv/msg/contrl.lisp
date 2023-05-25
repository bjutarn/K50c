; Auto-generated. Do not edit!


(cl:in-package talkersrv-msg)


;//! \htmlinclude contrl.msg.html

(cl:defclass <contrl> (roslisp-msg-protocol:ros-message)
  ((flag
    :reader flag
    :initarg :flag
    :type cl:fixnum
    :initform 0)
   (mode
    :reader mode
    :initarg :mode
    :type cl:fixnum
    :initform 0)
   (number
    :reader number
    :initarg :number
    :type cl:integer
    :initform 0)
   (pose
    :reader pose
    :initarg :pose
    :type mavros_msgs-msg:PositionTarget
    :initform (cl:make-instance 'mavros_msgs-msg:PositionTarget)))
)

(cl:defclass contrl (<contrl>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <contrl>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'contrl)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name talkersrv-msg:<contrl> is deprecated: use talkersrv-msg:contrl instead.")))

(cl:ensure-generic-function 'flag-val :lambda-list '(m))
(cl:defmethod flag-val ((m <contrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader talkersrv-msg:flag-val is deprecated.  Use talkersrv-msg:flag instead.")
  (flag m))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <contrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader talkersrv-msg:mode-val is deprecated.  Use talkersrv-msg:mode instead.")
  (mode m))

(cl:ensure-generic-function 'number-val :lambda-list '(m))
(cl:defmethod number-val ((m <contrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader talkersrv-msg:number-val is deprecated.  Use talkersrv-msg:number instead.")
  (number m))

(cl:ensure-generic-function 'pose-val :lambda-list '(m))
(cl:defmethod pose-val ((m <contrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader talkersrv-msg:pose-val is deprecated.  Use talkersrv-msg:pose instead.")
  (pose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <contrl>) ostream)
  "Serializes a message object of type '<contrl>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'flag)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'number)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pose) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <contrl>) istream)
  "Deserializes a message object of type '<contrl>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'flag)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mode)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'number) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pose) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<contrl>)))
  "Returns string type for a message object of type '<contrl>"
  "talkersrv/contrl")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'contrl)))
  "Returns string type for a message object of type 'contrl"
  "talkersrv/contrl")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<contrl>)))
  "Returns md5sum for a message object of type '<contrl>"
  "86c139ad945932fc6cc8e0987ddcb569")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'contrl)))
  "Returns md5sum for a message object of type 'contrl"
  "86c139ad945932fc6cc8e0987ddcb569")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<contrl>)))
  "Returns full string definition for message of type '<contrl>"
  (cl:format cl:nil "uint8 flag~%uint8 mode~%int32 number~%mavros_msgs/PositionTarget pose~%================================================================================~%MSG: mavros_msgs/PositionTarget~%# Message for SET_POSITION_TARGET_LOCAL_NED~%#~%# Some complex system requires all feautures that mavlink~%# message provide. See issue #402.~%~%std_msgs/Header header~%~%uint8 coordinate_frame~%uint8 FRAME_LOCAL_NED = 1~%uint8 FRAME_LOCAL_OFFSET_NED = 7~%uint8 FRAME_BODY_NED = 8~%uint8 FRAME_BODY_OFFSET_NED = 9~%~%uint16 type_mask~%uint16 IGNORE_PX = 1	# Position ignore flags~%uint16 IGNORE_PY = 2~%uint16 IGNORE_PZ = 4~%uint16 IGNORE_VX = 8	# Velocity vector ignore flags~%uint16 IGNORE_VY = 16~%uint16 IGNORE_VZ = 32~%uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags~%uint16 IGNORE_AFY = 128~%uint16 IGNORE_AFZ = 256~%uint16 FORCE = 512	# Force in af vector flag~%uint16 IGNORE_YAW = 1024~%uint16 IGNORE_YAW_RATE = 2048~%~%geometry_msgs/Point position~%geometry_msgs/Vector3 velocity~%geometry_msgs/Vector3 acceleration_or_force~%float32 yaw~%float32 yaw_rate~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'contrl)))
  "Returns full string definition for message of type 'contrl"
  (cl:format cl:nil "uint8 flag~%uint8 mode~%int32 number~%mavros_msgs/PositionTarget pose~%================================================================================~%MSG: mavros_msgs/PositionTarget~%# Message for SET_POSITION_TARGET_LOCAL_NED~%#~%# Some complex system requires all feautures that mavlink~%# message provide. See issue #402.~%~%std_msgs/Header header~%~%uint8 coordinate_frame~%uint8 FRAME_LOCAL_NED = 1~%uint8 FRAME_LOCAL_OFFSET_NED = 7~%uint8 FRAME_BODY_NED = 8~%uint8 FRAME_BODY_OFFSET_NED = 9~%~%uint16 type_mask~%uint16 IGNORE_PX = 1	# Position ignore flags~%uint16 IGNORE_PY = 2~%uint16 IGNORE_PZ = 4~%uint16 IGNORE_VX = 8	# Velocity vector ignore flags~%uint16 IGNORE_VY = 16~%uint16 IGNORE_VZ = 32~%uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags~%uint16 IGNORE_AFY = 128~%uint16 IGNORE_AFZ = 256~%uint16 FORCE = 512	# Force in af vector flag~%uint16 IGNORE_YAW = 1024~%uint16 IGNORE_YAW_RATE = 2048~%~%geometry_msgs/Point position~%geometry_msgs/Vector3 velocity~%geometry_msgs/Vector3 acceleration_or_force~%float32 yaw~%float32 yaw_rate~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <contrl>))
  (cl:+ 0
     1
     1
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pose))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <contrl>))
  "Converts a ROS message object to a list"
  (cl:list 'contrl
    (cl:cons ':flag (flag msg))
    (cl:cons ':mode (mode msg))
    (cl:cons ':number (number msg))
    (cl:cons ':pose (pose msg))
))
