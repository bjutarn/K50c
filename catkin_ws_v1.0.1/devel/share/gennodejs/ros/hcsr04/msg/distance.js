// Auto-generated. Do not edit!

// (in-package hcsr04.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class distance {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.front = null;
      this.down = null;
      this.front_time = null;
      this.down_time = null;
    }
    else {
      if (initObj.hasOwnProperty('front')) {
        this.front = initObj.front
      }
      else {
        this.front = 0.0;
      }
      if (initObj.hasOwnProperty('down')) {
        this.down = initObj.down
      }
      else {
        this.down = 0.0;
      }
      if (initObj.hasOwnProperty('front_time')) {
        this.front_time = initObj.front_time
      }
      else {
        this.front_time = {secs: 0, nsecs: 0};
      }
      if (initObj.hasOwnProperty('down_time')) {
        this.down_time = initObj.down_time
      }
      else {
        this.down_time = {secs: 0, nsecs: 0};
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type distance
    // Serialize message field [front]
    bufferOffset = _serializer.float32(obj.front, buffer, bufferOffset);
    // Serialize message field [down]
    bufferOffset = _serializer.float32(obj.down, buffer, bufferOffset);
    // Serialize message field [front_time]
    bufferOffset = _serializer.time(obj.front_time, buffer, bufferOffset);
    // Serialize message field [down_time]
    bufferOffset = _serializer.time(obj.down_time, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type distance
    let len;
    let data = new distance(null);
    // Deserialize message field [front]
    data.front = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [down]
    data.down = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [front_time]
    data.front_time = _deserializer.time(buffer, bufferOffset);
    // Deserialize message field [down_time]
    data.down_time = _deserializer.time(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hcsr04/distance';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7c475cd559c7cfc2f328489a1905a9e3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    #前后左右
    float32  front 
    float32  down
    time front_time
    time down_time
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new distance(null);
    if (msg.front !== undefined) {
      resolved.front = msg.front;
    }
    else {
      resolved.front = 0.0
    }

    if (msg.down !== undefined) {
      resolved.down = msg.down;
    }
    else {
      resolved.down = 0.0
    }

    if (msg.front_time !== undefined) {
      resolved.front_time = msg.front_time;
    }
    else {
      resolved.front_time = {secs: 0, nsecs: 0}
    }

    if (msg.down_time !== undefined) {
      resolved.down_time = msg.down_time;
    }
    else {
      resolved.down_time = {secs: 0, nsecs: 0}
    }

    return resolved;
    }
};

module.exports = distance;
