{
   "targets": [
      {
         "target_name": "Module",
         "sources": [
            "source/*.cpp"
         ],
         "defines": [
            "NAPI_DISABLE_CPP_EXCEPTIONS",
            "HLSR_PLATFORM_WINDOWS"
         ],
         "libraries": [
            "../libs/steamworks/steam_api64.lib"
         ],
         "include_dirs": [
            "<!(node -p \"require('node-addon-api').include_dir\")",
            "../include",
            "../source"
         ],
         "conditions": [
            [
               "OS==\"win\"",
               {
                  "copies": [
                     {
                        "destination": "<(module_root_dir)/build/Release/",
                        "files": [
                           "<(module_root_dir)/libs/steamworks/steam_api64.dll",
                           "<(module_root_dir)/libs/steamworks/steam_api.dll"
                        ]
                     }
                  ]
               }
            ]
         ]
      }
   ]
}