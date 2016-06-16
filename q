[33mcommit bea0a273474282a843983fd661c33fd1e37fdd95[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Tue Jun 14 17:55:30 2016 +0200

    Added delegates for the filter list views; timestamp filtering now adapts the respective other filter if an impossible combination of timestamps is set; autocompletion for the filter list views editing and the single message send introduced (//ToDO send single messages needs to parse the input in the respective text fields)

[33mcommit ede96f74df718c0353a2b440300cb0c0657a19a9[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Wed Jun 8 18:35:58 2016 +0200

    Send message does not work as expected since only every second message is sent by the hardware; Hardware and Firmware debugging is in process; added short nonsense matrix for matrix transmit testing

[33mcommit 9d97cad6d6808620f0665914c58dbf96675c4429[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Tue Jun 7 17:47:24 2016 +0200

    Fixed auto reload on scroll in MsgTableView; cleaned up sending messages; send packets button implemented --- NEEDS SOME MORE WORK... only every second msg is sent

[33mcommit f0dcc2ff3e5a123e85100e276a0b8ce56038bd76[m
Merge: 2cba6ad 620026a
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Tue Jun 7 11:38:07 2016 +0200

    merged with updated but somehow conflicting remote version

[33mcommit 620026a84d195b5fdaea76ee2b3b31ff9e64a40d[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Tue Jun 7 02:32:56 2016 +0200

    high performance filtering and limiting done inside the view by setting rows visible/invisible; included timestamp filtering; introduced performance driven filtering

[33mcommit 2cba6ad2f12a163ade20fed27b1997f7980af74f[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Fri Jun 3 17:06:16 2016 +0200

    improved MsgFilterModel; added parsing of hex/dec/strings to IDFilter and CodeFilter listViews

[33mcommit 7ca49d71c616e99d888ccffbf00b43b46b5d5811[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Fri Jun 3 11:31:16 2016 +0200

    trying to connect MsgFilterProxyModel reset to MsgProxyModel reset

[33mcommit 71a1500b5d269bdaec9ffd8b00ba4a595941d407[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Fri Jun 3 11:13:39 2016 +0200

    restructed MessageConfig Filter for a nice and clean look; implemented models for id and code filtering; connected id filter view to id filter model; connected id filter model to MsgFilterProxyModel; chained MsgProxyModel and MsgFilterProxyModel to MsgModel

[33mcommit 7c3ea7b9cd9e4b177361fdc5f9e15f9e6f1eb510[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Thu Jun 2 18:33:16 2016 +0200

    added reloading of content in the proxymodel triggered by the view's scrollbar; optimized scrollToBottom of the view; updated MsgProxyModel and MainWindow to fit the new needs

[33mcommit 1636eb1f0a69a5e8533793059a6c23cfb3b1a555[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Thu Jun 2 02:35:01 2016 +0200

    found alternative (way better) solution... needs rework

[33mcommit 5cb2075976685dcb1aaa866825bd8f1a2c37a18f[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Thu Jun 2 02:24:45 2016 +0200

    FOUGHT with the proxymodel -- got it running; it's late... good night

[33mcommit f46ce84654a7f589762c1fd517cb85c4c5ed9ad4[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Wed Jun 1 18:36:52 2016 +0200

    added sorting to IDTable and MsgTypeTable; tried to add MsgProxyModel -> needs WORK! ; Introduced receiving and displaying of CAN messages!

[33mcommit 692c33e555ae117a740ea6d42adcd6e5619e1def[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Wed Jun 1 02:36:28 2016 +0200

    separated widgets form tabWidget for more flexibility; implemented all previous functionalities; added applyRole to all widgets, thus they can handle the UserRoles themselves (e.g. enable/disable elements); adapted QMake files and stuff

[33mcommit e479d699865f09c163670c37b9a8167dc4a5dbba[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Wed Jun 1 00:14:08 2016 +0200

    added NormalUser/Admin roles to hide/show advanced options

[33mcommit 43c53adca62261de7b6fde0add64758964b1376a[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Tue May 31 18:29:34 2016 +0200

    Restructured R_Visualizer directory structure to feature a seperate project for the GUI and the USB Driver

[33mcommit 837dbc7b0c0899abaf100b4bde93d4ad4a008975[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Tue May 31 18:22:20 2016 +0200

    included DeviceDriver for CAN-Analyser usb device; example connect and send

[33mcommit 87280712a24d859145b5548f33309830d3e559ac[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Tue May 31 17:00:45 2016 +0200

    added tooltips and locales to all dialogs and widgets; added specific input masks and input parsing for number input according to the input numbers base (ComboBox selection)

[33mcommit 954516c53bb8526c8b5d56155b3ebdcd9a3c5ce0[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Tue May 31 00:01:55 2016 +0200

    corrected regular expression to parse nested operations; added HEX/OCT/BIN number parsing; added some test files

[33mcommit fb85ff06c382e484504faaea9549fe3fb5d1b881[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Mon May 30 18:20:25 2016 +0200

    added MessageFormat to MsgType for parsed messages; fixed row height sizing to dynamic content aware resizing (might need some additional work/BugFixes); implemented a simple arithmetic operation parser for the MessageFormat strings; Added a GUI for easy MessageFormat string creation; some minor BugFixes

[33mcommit d45938dfdd51e5439672bda2e7e8a4562862f593[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Mon May 30 07:10:40 2016 +0200

    modified mainwindow.cpp

[33mcommit e433fed0b67b9fc35b33a45ea986a44bea218183[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Sat May 28 17:05:10 2016 +0200

    unified MsgTypeDelegate and IDDelegate for the MsgModel to MsgDelegate; Introduced packet send management; introduced csv file parsing for csv marices

[33mcommit c6eecbd595aea41ae2b455aa459fae3dca5bc56f[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Fri May 27 10:56:41 2016 +0200

    added msgtype and id functionality to update, parse and alter the visual representation of incoming and existing messages; add functionality with custom widgets for ids and message types; editing functionalites for the id and msgtype model; //ToDO remove entries from id and msgtype models; //ToDO csv parser for message package files; //ToDO create msgs from message package files and send messages

[33mcommit 9c399308e79febeb23c2f17c847fc44f3064b631[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Wed May 25 03:23:40 2016 +0200

    changed msg to a more precise structure; edited the data storage mechanisms for msgTypes and IDs; Introduced coloring and naming of messages according to msgTypes and IDs specified in their respective models

[33mcommit e499da8dbe3ac95caf6dc8290651b02d5fbd517d[m
Author: Christian Neuberger <neverknewthename@googlemail.com>
Date:   Tue May 24 10:53:57 2016 +0200

    added ID model and MsgType model; introduced json save and load file for ID and MsgType models

[33mcommit 760aface23d2d5ddbb32078ea6c3f2b00ab14e91[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Mon May 23 18:43:58 2016 +0200

    cleaned up sources; introduced tableview with custom model; introduced json file handling (unfinished); introduced single messages to hold data for model

[33mcommit 140cb7dc290b91259497db3ca9cd17ef20e01526[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Fri May 20 17:00:00 2016 +0200

    added a simple square to demonstrate the QGraphicsItem capabilites

[33mcommit 9943e412dab48525b9885e52b3c1d84a6eb44a22[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Wed May 18 17:26:46 2016 +0200

    added shortcuts to file operation menu; introduced simple file handling

[33mcommit cad0040d9c11a0b306d46dba04ada8263d89773a[m
Author: Christian Neuberger <neubergerch50344@th-nuernberg.de>
Date:   Wed May 18 12:10:28 2016 +0200

    initial commit
