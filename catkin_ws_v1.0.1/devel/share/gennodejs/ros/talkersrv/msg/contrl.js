// Auto-generated. Do not edit!

// (in-package talkersrv.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let mavros_msgs = _finder('mavros_msgs');

//-----------------------------------------------------------

class contrl {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.flag = null;
      this.mode = null;
      this.number = null;
      this.pose = null;
    }
    else {
      if (initObj.hasOwnProperty('flag')) {
        this.flag = initObj.flag
      }
      else {
        this.flag = 0;
      }
      if (initObj.hasOwnProperty('mode')) {
        this.mode = initObj.mode
      }
      else {
        this.mode = 0;
      }
      if (initObj.hasOwnProperty('number')) {
        this.number = initObj.number
      }
      else {
        this.number = 0;
      }
      if (initObj.hasOwnProperty('pose')) {
        this.pose = initObj.pose
      }
      else {
        this.pose = new mavros_msgs.msg.PositionTarget();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type contrl
    // Serialize message field [flag]
    bufferOffset = _serializer.uint8(obj.flag, buffer, bufferOffset);
    // Serialize message field [mode]
    bufferOffset = _serializer.uint8(obj.mode, buffer, bufferOffset);
    // Serialize message field [number]
    bufferOffset = _serializer.int32(obj.number, buffer, bufferOffset);
    // Serialize message field [pose]
    bufferOffset = mavros_msgs.msg.PositionTarget.serialize(obj.pose, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type contrl
    let len;
    let data = new contrl(null);
    // Deserialize message field [flag]
    data.flag = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [mode]
    data.mode = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [number]
    data.number = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [pose]
    data.pose = mavros_msgs.msg.PositionTarget.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += mavros_msgs.msg.PositionTarget.getMessageSize(object.pose);
    return length + 6;
  }

  static datatype() {
    // Returns string type for a message object
    return 'talkersrv/contrl';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '86c139ad945932fc6cc8e0987ddcb569';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 flag
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
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new contrl(null);
    if (msg.flag !== undefined) {
      resolved.flag = msg.flag;
    }
    else {
      resolved.flag = 0
    }

    if (msg.mode !== undefined) {
      resolved.mode = msg.mode;
    }
    else {
      resolved.mode = 0
    }

    if (msg.number !== undefined) {
      resolved.number = msg.number;
    }
    else {
      resolved.number = 0
    }

    if (msg.pose !== undefined) {
      resolved.pose = mavros_msgs.msg.PositionTarget.Resolve(msg.pose)
    }
    else {
      resolved.pose = new mavros_msgs.msg.PositionTarget()
    }

    return resolved;
    }
};

module.exports = contrl;
