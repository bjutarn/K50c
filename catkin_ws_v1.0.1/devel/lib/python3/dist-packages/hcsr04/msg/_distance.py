# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from hcsr04/distance.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import genpy

class distance(genpy.Message):
  _md5sum = "7c475cd559c7cfc2f328489a1905a9e3"
  _type = "hcsr04/distance"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """#前后左右
float32  front 
float32  down
time front_time
time down_time

"""
  __slots__ = ['front','down','front_time','down_time']
  _slot_types = ['float32','float32','time','time']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       front,down,front_time,down_time

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(distance, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.front is None:
        self.front = 0.
      if self.down is None:
        self.down = 0.
      if self.front_time is None:
        self.front_time = genpy.Time()
      if self.down_time is None:
        self.down_time = genpy.Time()
    else:
      self.front = 0.
      self.down = 0.
      self.front_time = genpy.Time()
      self.down_time = genpy.Time()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_2f4I().pack(_x.front, _x.down, _x.front_time.secs, _x.front_time.nsecs, _x.down_time.secs, _x.down_time.nsecs))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.front_time is None:
        self.front_time = genpy.Time()
      if self.down_time is None:
        self.down_time = genpy.Time()
      end = 0
      _x = self
      start = end
      end += 24
      (_x.front, _x.down, _x.front_time.secs, _x.front_time.nsecs, _x.down_time.secs, _x.down_time.nsecs,) = _get_struct_2f4I().unpack(str[start:end])
      self.front_time.canon()
      self.down_time.canon()
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_2f4I().pack(_x.front, _x.down, _x.front_time.secs, _x.front_time.nsecs, _x.down_time.secs, _x.down_time.nsecs))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.front_time is None:
        self.front_time = genpy.Time()
      if self.down_time is None:
        self.down_time = genpy.Time()
      end = 0
      _x = self
      start = end
      end += 24
      (_x.front, _x.down, _x.front_time.secs, _x.front_time.nsecs, _x.down_time.secs, _x.down_time.nsecs,) = _get_struct_2f4I().unpack(str[start:end])
      self.front_time.canon()
      self.down_time.canon()
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2f4I = None
def _get_struct_2f4I():
    global _struct_2f4I
    if _struct_2f4I is None:
        _struct_2f4I = struct.Struct("<2f4I")
    return _struct_2f4I
