;; Auto-generated. Do not edit!


(when (boundp 'talkersrv::contrl)
  (if (not (find-package "TALKERSRV"))
    (make-package "TALKERSRV"))
  (shadow 'contrl (find-package "TALKERSRV")))
(unless (find-package "TALKERSRV::CONTRL")
  (make-package "TALKERSRV::CONTRL"))

(in-package "ROS")
;;//! \htmlinclude contrl.msg.html
(if (not (find-package "MAVROS_MSGS"))
  (ros::roseus-add-msgs "mavros_msgs"))


(defclass talkersrv::contrl
  :super ros::object
  :slots (_flag _mode _number _pose ))

(defmethod talkersrv::contrl
  (:init
   (&key
    ((:flag __flag) 0)
    ((:mode __mode) 0)
    ((:number __number) 0)
    ((:pose __pose) (instance mavros_msgs::PositionTarget :init))
    )
   (send-super :init)
   (setq _flag (round __flag))
   (setq _mode (round __mode))
   (setq _number (round __number))
   (setq _pose __pose)
   self)
  (:flag
   (&optional __flag)
   (if __flag (setq _flag __flag)) _flag)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:number
   (&optional __number)
   (if __number (setq _number __number)) _number)
  (:pose
   (&rest __pose)
   (if (keywordp (car __pose))
       (send* _pose __pose)
     (progn
       (if __pose (setq _pose (car __pose)))
       _pose)))
  (:serialization-length
   ()
   (+
    ;; uint8 _flag
    1
    ;; uint8 _mode
    1
    ;; int32 _number
    4
    ;; mavros_msgs/PositionTarget _pose
    (send _pose :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _flag
       (write-byte _flag s)
     ;; uint8 _mode
       (write-byte _mode s)
     ;; int32 _number
       (write-long _number s)
     ;; mavros_msgs/PositionTarget _pose
       (send _pose :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _flag
     (setq _flag (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; uint8 _mode
     (setq _mode (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; int32 _number
     (setq _number (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; mavros_msgs/PositionTarget _pose
     (send _pose :deserialize buf ptr-) (incf ptr- (send _pose :serialization-length))
   ;;
   self)
  )

(setf (get talkersrv::contrl :md5sum-) "86c139ad945932fc6cc8e0987ddcb569")
(setf (get talkersrv::contrl :datatype-) "talkersrv/contrl")
(setf (get talkersrv::contrl :definition-)
      "uint8 flag
uint8 mode
int32 number
mavros_msgs/PositionTarget pose
================================================================================
MSG: mavros_msgs/PositionTarget
# Message for SET_POSITION_TARGET_LOCAL_NED
#
# Some complex system requires all feautures that mavlink
# message provide. See issue #402.

std_msgs/Header header

uint8 coordinate_frame
uint8 FRAME_LOCAL_NED = 1
uint8 FRAME_LOCAL_OFFSET_NED = 7
uint8 FRAME_BODY_NED = 8
uint8 FRAME_BODY_OFFSET_NED = 9

uint16 type_mask
uint16 IGNORE_PX = 1	# Position ignore flags
uint16 IGNORE_PY = 2
uint16 IGNORE_PZ = 4
uint16 IGNORE_VX = 8	# Velocity vector ignore flags
uint16 IGNORE_VY = 16
uint16 IGNORE_VZ = 32
uint16 IGNORE_AFX = 64	# Acceleration/Force vector ignore flags
uint16 IGNORE_AFY = 128
uint16 IGNORE_AFZ = 256
uint16 FORCE = 512	# Force in af vector flag
uint16 IGNORE_YAW = 1024
uint16 IGNORE_YAW_RATE = 2048

geometry_msgs/Point position
geometry_msgs/Vector3 velocity
geometry_msgs/Vector3 acceleration_or_force
float32 yaw
float32 yaw_rate

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
")



(provide :talkersrv/contrl "86c139ad945932fc6cc8e0987ddcb569")


