{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc", "myobject.cc", "RF24.cpp", "bcm2835.c" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
      ]
    }
  ]
}
