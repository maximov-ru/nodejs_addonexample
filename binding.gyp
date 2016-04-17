{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc", "myobject.cc", "RF24.cpp", "bcm2835.c" ],
      "libraries": ["../librf24-bcm.so.1.0"],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
      ]
    }
  ]
}
