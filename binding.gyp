{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc", "myobject.cc", "RF24.cpp", "bcm2835.c" ],
      "libraries": ["Release/obj.target/addon/RF24.o","Release/obj.target/addon/bcm2835.o"],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
      ]
    }
  ]
}
