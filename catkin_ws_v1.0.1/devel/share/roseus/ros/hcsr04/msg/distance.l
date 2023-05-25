;; Auto-generated. Do not edit!


(when (boundp 'hcsr04::distance)
  (if (not (find-package "HCSR04"))
    (make-package "HCSR04"))
  (shadow 'distance (find-package "HCSR04")))
(unless (find-package "HCSR04::DISTANCE")
  (make-package "HCSR04::DISTANCE"))

(in-package "ROS")
;;//! \htmlinclude distance.msg.html


(defclass hcsr04::distance
  :super ros::object
  :slots (_front _down _front_time _down_time ))

(defmethod hcsr04::distance
  (:init
   (&key
    ((:front __front) 0.0)
    ((:down __down) 0.0)
    ((:front_time __front_time) (instance ros::time :init))
    ((:down_time __down_time) (instance ros::time :init))
    )
   (send-super :init)
   (setq _front (float __front))
   (setq _down (float __down))
   (setq _front_time __front_time)
   (setq _down_time __down_time)
   self)
  (:front
   (&optional __front)
   (if __front (setq _front __front)) _front)
  (:down
   (&optional __down)
   (if __down (setq _down __down)) _down)
  (:front_time
   (&optional __front_time)
   (if __front_time (setq _front_time __front_time)) _front_time)
  (:down_time
   (&optional __down_time)
   (if __down_time (setq _down_time __down_time)) _down_time)
  (:serialization-length
   ()
   (+
    ;; float32 _front
    4
    ;; float32 _down
    4
    ;; time _front_time
    8
    ;; time _down_time
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _front
       (sys::poke _front (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _down
       (sys::poke _down (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; time _front_time
       (write-long (send _front_time :sec) s) (write-long (send _front_time :nsec) s)
     ;; time _down_time
       (write-long (send _down_time :sec) s) (write-long (send _down_time :nsec) s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _front
     (setq _front (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _down
     (setq _down (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; time _front_time
     (send _front_time :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _front_time :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; time _down_time
     (send _down_time :sec (sys::peek buf ptr- :integer)) (incf ptr- 4)  (send _down_time :nsec (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get hcsr04::distance :md5sum-) "7c475cd559c7cfc2f328489a1905a9e3")
(setf (get hcsr04::distance :datatype-) "hcsr04/distance")
(setf (get hcsr04::distance :definition-)
      "#前后左右
float32  front 
float32  down
time front_time
time down_time


")



(provide :hcsr04/distance "7c475cd559c7cfc2f328489a1905a9e3")


