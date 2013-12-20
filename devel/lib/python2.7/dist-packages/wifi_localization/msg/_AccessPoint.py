"""autogenerated by genpy from wifi_localization/AccessPoint.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class AccessPoint(genpy.Message):
  _md5sum = "14566870ce27da9eaacf517d23cded21"
  _type = "wifi_localization/AccessPoint"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """string mac_address # MAC address of an access point
int16 ss           # signal strength [RSSI]
int16 noise        # noise

"""
  __slots__ = ['mac_address','ss','noise']
  _slot_types = ['string','int16','int16']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       mac_address,ss,noise

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(AccessPoint, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.mac_address is None:
        self.mac_address = ''
      if self.ss is None:
        self.ss = 0
      if self.noise is None:
        self.noise = 0
    else:
      self.mac_address = ''
      self.ss = 0
      self.noise = 0

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
      _x = self.mac_address
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2h.pack(_x.ss, _x.noise))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.mac_address = str[start:end].decode('utf-8')
      else:
        self.mac_address = str[start:end]
      _x = self
      start = end
      end += 4
      (_x.ss, _x.noise,) = _struct_2h.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self.mac_address
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2h.pack(_x.ss, _x.noise))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.mac_address = str[start:end].decode('utf-8')
      else:
        self.mac_address = str[start:end]
      _x = self
      start = end
      end += 4
      (_x.ss, _x.noise,) = _struct_2h.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_2h = struct.Struct("<2h")
