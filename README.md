# Fett 3.0
##### He's no good to me dead. #####

      _____       __    __
    _/ ____\_____/  |__/  |_
    \   __\/ __ \   __\   __\
     |  | \  ___/|  |  |  |
     |__|  \___  >__|  |__|
               \/

### Sub Theme Creation ###

**Never modify the Fett base theme.**

The recommended and easiest way to create a sub theme based on Fett is to use
Drush. Use the "fett" command to start the creation process.

*Example: drush fett [name] [machine_name !OPTIONAL] [description !OPTIONAL]*

### SASS ###

This module is best when utilizing SASS. It has been built to work with the
Sonar module (https://github.com/JaceRider/Sonar). Once installing and enabling
this module you will be able to utilize the full power of SASS in your theme.

Adding a new SASS file is the same as adding a CSS file to Drupal. You can use
drupal_add_css(), #attached, or add the file directly to your theme's .info file.

### jQuery ###

Foundation requires no less than jQuery 1.10. Using the jQuery Update module
(https://drupal.org/project/jquery_update) is the recommended way of updating
Drupal's version of jQuery. Currently, the dev version of this module is the
only one that support 1.10.

### Off-Canvas ###

Adding off-canvas elements is incredibly easy. There are theme settings that
allow easy enabling of off-canvas for the main nav as well as the sidebars.

You can easily add your own items by calling:

    fett_offcanvas_add($content)

This will return a link that will trigger the off-canvas block.

                            __QMmm
                          _gMMMMMB~__  _gMma__ .____
                        _MMMMMMMR(MMMmMMMMMMMMMMMMMMMe
                       .MMMMMMMt _MMMMMMMMMMMMMMMMMMMM,
                       _MMMMMMMm  3MMMMMMMMMMMMMMMMMMM)
                       _MMMMMMMMMQMMMMMMMMMMMMMMMMMMMM)
                        _@MMMMMMMMMMMMMMMMMMMMMMMMMMMM
                          3MMMMMMMMMMMMMMMMMMMMMMMMT+` _,
                            7MMMMMMMMMMMMMMMMMMT'     _'
                              /MMMMMMMMMMMMMT`       dME
                                NMMMMMMMMMT`        _MMMp
                     .JMm        MMMMMMMF`          _MMMM~
                     3MMM]        9MMMF            .dMMMM~
                     _MMMm         4ME            _MMMMMT
                      MMMMMm,      JMME       ._QMMMMMF
                      /MMMMMMMe   ._MMB     _gMMMMMMMt
                       3MMMMMMMMe._MMME    (MMMMMMMM%     ._.
              _gMMMm,     dMMMMMM] "MMM.  JMMMMMMMMt    _MMMMMma,
            .JMMMMMMMma   _MMMMMMMMmMMMm. MMMMMMMMP   .JMMMMMMMMMQ,
           _MMMMMMMMMMMm,  JMMMMMMMMMMMMmAMMMMMMMMb _MMMMMMMMMMMMMME
          _MMMMMMMMMMMMMMm  3MMMMMMMMMMMMMMMMMMMME JMMMMMMMMMMMMMMM!
        _MMMMMMMMMMMMMMMME  _MMMMMMMMMMMMMMMMMMMt _MMMMMMMMMMMMMMMmmmA_
       _MMMMMMMMMMMMMMMMM:   MMMMMMMMMMMMMMMME `    (MMMMMMMMMMMMMFMMMM]
      _MMMMMMMMMMMMMMMF'     MMMMMMMMMMMMMMMME        3MMMMMMMMMMMmMMMME
     _MMMMMMMMMMMMMMt        /MMMTMMMMMMMMMMMMA         3MMMMMMMMMMMMMMm
     JMMMMMMMMMMMMT`           `` _MMMMMMT7MMMm           3MMMMMMMMMMMMM)
     dMMMMMMMMMMF~                 (MMMMME_MMMM            .9MMMMMMMMMMM]
     MMMMMMMMMM!                   JMMMF`_MMMMt              3MMMMMMMMMM]
    _MMMMMMMMR`               _gmm _MMMm,_MMM`                3MMMMMMMMME
    _MMMMMMME                _MMMMm_MMV"jMMMb                  _MMMMMMMMM
    dMMMMMME                 _MMMMMe    _MMM:                   dMMMMMMMMEa
    dMMMMMM]                 dMMMMMMp. _MMM|                    _MMMMMMMME
    4MMMMME                  dMMMMMM] _MMMM,                     MMMMMMMME
    _MMMMMM,                 3MMMMMM) (MMMB,                     dMMMMMMM%
     /MMMMMm,                 MMMMME  dMMMM,                    .MMMMMMMt
      3MMMMMM,                 9MMMF  dMMMMb                    _MMMMMM%
       /MMMMMM/.              .. 9M]  _MMMMD                  _gMMMMMM'
         JMMMMMMm___.        /MM] Jm  _MMMT                _gMMMMMMMt
           /VTTT"9""""^      _MM] JM` _MMt _,                 `^^'`
                              MM]  MA _MM` ME
                              3M]  ME  ME  M]
                              _M`  dE  dE  M]
                               7   /E  _E  3b
                                   _b  _$  _m.
                                            J`
