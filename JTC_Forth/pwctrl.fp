s��        C    B     �    C�                                           Password Control                                 � ��const char *      <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<p class="Body">This instrument driver provides functions for creating and manipulating password controls.</p>

<p class=body>A password control is like a string control except that the password control displays the string that the user types using a mask character so the password cannot be read as the user types it.</p>

<p class=body>The functions in this class are the only functions intended to work for
password controls, except for <span class="Monospace">DiscardCtrl</span>, which discards password controls as well as standard user interface
controls. However, you are free to experiment with the other functions in the User
Interface Library since many of them operate on password controls
successfully. For example, you can use <span class="Monospace">SetCtrlAttribute(panel, passwordCtrl, ATTR_WIDTH, width)</span> to set the width of a password control.</p>

<p class=body>The functions in this instrument driver are multithread-safe.</p>

</BODY>
</HTML>    %    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_Create</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<h1 class="function">PasswordCtrl_Create</h1>

<p class="syntax">int PasswordCtrl_Create (int panel, const char *label, int top, int left);</p>

<h2 class="purpose">Purpose</h2>
<p class="Body">This function creates a new password control.</p>

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibPasswordControl_FunctionTree.htm')">Password Control</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">custctrl\pwctrl.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 4.0 and later</p>

<!-- ADDITIONAL INFO END -->
</body>
</html>

    8^    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_Create</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">passwordControl</td>
<td class="paramDataType">integer</td>

<td>Returns the ID used to specify this control in subsequent function calls. Negative values indicate that an error occurred.<br>

<table class="borderless">
<TR>
<td nowrap><strong>Error Codes:</strong></td><td></td>
</TR>

<TR><td><span  class="nobreak">&#8211;1</span></td>  
<td>The Interface Manager could not be opened.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;2</span></td>
<td>The system font could not be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;3</span></td>
<td>The operation attempted cannot be performed while a pop-up menu is active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;4</span></td>  
<td>Panel, pop-up, menu bar, or plot ID is invalid.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;5</span></td>
<td>Attempted to position panel at an invalid location.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;6</span></td>  
<td>Attempted to make an inoperable control the active control.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;7</span></td>
<td>The operation requires that a panel be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;8</span></td>
<td>The operation requires that a pop-up menu be active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;9</span></td>
<td>The operation requires that a menu bar be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;10</span></td>  
<td>The control is not the type expected by the function.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;11</span></td>  
<td>Invalid menu item ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;12</span></td>
<td>Out of memory.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;13</span></td>
<td>Invalid control ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;14</span></td>
<td>Value is invalid or out of range.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;15</span></td>
<td>File is not a User Interface file or has been corrupted.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;16</span></td>  
<td>File format is out-of-date.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;17</span></td>
<td>PCX image is corrupted or incompatible with current
display type.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;18</span></td>
<td>No user event possible in current configuration.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;19</span></td>  
<td>Unable to open UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;20</span></td>
<td>Error reading UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;21</span></td>  
<td>Error writing UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;22</span></td>  
<td>Error closing UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;23</span></td>  
<td>Panel state file has invalid format.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;24</span></td>
<td>Invalid panel ID or menu bar ID in resource file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;25</span></td>
<td>Error occurred during hardcopy output.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;26</span></td>
<td>Invalid default directory specified in <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviFileSelectPopup.htm')">FileSelectPopup</a></span> or <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviFileSelectPopupEx.htm')">FileSelectPopupEx</a></span> function.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;27</span></td>  
<td>Operation is invalid for specified object.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;28</span></td>  
<td>Unable to find specified string in menu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;29</span></td>  
<td>Palette menu items can only be added to the end of the menu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;30</span></td>
<td>Too many menus in the menu bar.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;31</span></td>
<td>Separators cannot have checkmarks.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;32</span></td>
<td>Separators cannot have submenus.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;33</span></td>
<td>The menu item must be a separator.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;34</span></td>
<td>The menu item cannot be a separator.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;35</span></td>
<td>The menu item already has a submenu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;36</span></td>
<td>The menu item does not have a submenu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;37</span></td>  
<td>The control ID passed must be a menu ID, a menu item ID, or NULL.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;38</span></td>
<td>The control ID passed must be a menu ID or a menu item ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;39</span></td>
<td>The control ID passed was not a submenu ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;40</span></td>
<td>The control ID passed was not a valid ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;41</span></td> 
<td>The ID is not a menu bar ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;42</span></td>  
<td>The ID is not a panel ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;43</span></td>
<td>This operation cannot be performed while this pop-up panel is active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;44</span></td>
<td>This control/panel/menu does not have the specified attribute.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;45</span></td>
<td>The control type passed was not a valid type.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;46</span></td>
<td>The attribute passed is invalid.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;47</span></td>
<td>The fill option must be set to fill above or fill below to paint ring slide's fill color.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;48</span></td>
<td>The fill option must be set to fill above or fill below to paint numeric slide's fill color.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;49</span></td>
<td>The control passed is not a ring slide.</td></TR>
<TR><td><span  class="nobreak">&#8211;50</span></td>
<td>The control passed is not a numeric slide.</td></TR>
<TR><td><span  class="nobreak">&#8211;51</span></td>  
<td>The control passed is not a ring slide with                            inc/dec arrows.</td></TR>
<TR><td><span  class="nobreak">&#8211;52</span></td>  
<td>The control passed is not a numeric slide with inc/dec arrows.</td></TR>
<TR><td><span  class="nobreak">&#8211;53</span></td>
<td>The data type passed in is not a valid data type for the control.</td></TR>
<TR><td><span  class="nobreak">&#8211;54</span></td>
<td>The attribute passed is not valid for the                                                data type of the control.</td></TR>
<TR><td><span  class="nobreak">&#8211;55</span></td>
<td>The index passed is out of range.</td></TR>
<TR><td><span  class="nobreak">&#8211;56</span></td>
<td>There are no items in the list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;57</span></td>
<td>The buffer passed was too small for the operation.</td></TR>
<TR><td><span  class="nobreak">&#8211;58</span></td>
<td>The control does not have a value.</td></TR>
<TR><td><span  class="nobreak">&#8211;59</span></td>
<td>The value passed is not in the list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;60</span></td>
<td>The control passed must be a list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;61</span></td>
<td>The control passed must be a list control or a binary switch.</td></TR>
<TR><td><span  class="nobreak">&#8211;62</span></td>
<td>The data type of the control passed must be set to a string.</td></TR>
<TR><td><span  class="nobreak">&#8211;63</span></td>
<td>That attribute is not a settable attribute.</td></TR>
<TR><td><span  class="nobreak">&#8211;64</span></td>
<td>The value passed is not a valid mode for this control.</td></TR>
<TR><td><span  class="nobreak">&#8211;65</span></td>
<td>A NULL pointer was passed when a non-NULL pointer was expected.</td></TR>
<TR><td><span  class="nobreak">&#8211;66</span></td>
<td>The text background color on a menu ring cannot be set or gotten.</td></TR>
<TR><td><span  class="nobreak">&#8211;67</span></td>
<td>The ring control passed must be one of the menu ring styles.</td></TR>
<TR><td><span  class="nobreak">&#8211;68</span></td>
<td>Text cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;69</span></td>
<td>A value cannot be converted to the specified data type.</td></TR>
<TR><td><span  class="nobreak">&#8211;70</span></td>  
<td>Invalid tab order position for control.</td></TR>
<TR><td><span  class="nobreak">&#8211;71</span></td>
<td>The tab order position of an indicator-only control cannot be set.</td></TR>
<TR><td><span  class="nobreak">&#8211;72</span></td>  
<td>Invalid number.</td></TR>
<TR><td><span  class="nobreak">&#8211;73</span></td>
<td>There is no menu bar installed for the panel.</td></TR>
<TR><td><span  class="nobreak">&#8211;74</span></td>
<td>The control passed is not a text box.</td></TR>
<TR><td><span  class="nobreak">&#8211;75</span></td>  
<td>Invalid scroll mode for chart.</td></TR>
<TR><td><span  class="nobreak">&#8211;76</span></td>
<td>Invalid image type for picture.</td></TR>
<TR><td><span  class="nobreak">&#8211;77</span></td>
<td>The attribute is valid for child panels only. Some attributes of top level panels are determined by the host operating system.</td></TR>
<TR><td><span  class="nobreak">&#8211;78</span></td>
<td>The list control passed is not in check mode.</td></TR>
<TR><td><span  class="nobreak">&#8211;79</span></td>
<td>The control values could not be completely loaded into the panel because the panel has changed.</td></TR>
<TR><td><span  class="nobreak">&#8211;80</span></td>
<td>Maximum value must be greater than minimum value.</td></TR>
<TR><td><span  class="nobreak">&#8211;81</span></td>
<td>Graph does not have that many cursors.</td></TR>
<TR><td><span  class="nobreak">&#8211;82</span></td>  
<td>Invalid plot.</td></TR>
<TR><td><span  class="nobreak">-83</span></td>
<td>New cursor position is outside plot area.</td></TR>
<TR><td><span  class="nobreak">&#8211;84</span></td>
<td>The length of the string exceeds the limit.</td></TR>
<TR><td><span  class="nobreak">&#8211;85</span></td>
<td>The specified callback function does not have the required prototype.</td></TR>
<TR><td><span  class="nobreak">&#8211;86</span></td>
<td>The specified callback function is not a known function.</td></TR>
<TR><td><span  class="nobreak">&#8211;87</span></td>
<td>Graph cannot be in this mode without cursors.</td></TR>
<TR><td><span  class="nobreak">&#8211;88</span></td>
<td>Invalid axis scaling mode for chart.</td></TR>
<TR><td><span  class="nobreak">&#8211;89</span></td>
<td>The font passed is not in font table.</td></TR>
<TR><td><span  class="nobreak">&#8211;90</span></td>
<td>The attribute value passed is not valid.</td></TR>
<TR><td><span  class="nobreak">&#8211;91</span></td>
<td>Too many files are open.</td></TR>
<TR><td><span  class="nobreak">&#8211;92</span></td>
<td>Unexpectedly reached end of file.</td></TR>
<TR><td><span  class="nobreak">&#8211;93</span></td>
<td>Input/Output error.</td></TR>
<TR><td><span  class="nobreak">&#8211;94</span></td>
<td>File not found.</td></TR>
<TR><td><span  class="nobreak">&#8211;95</span></td>
<td>File access permission denied.</td></TR>
<TR><td><span  class="nobreak">&#8211;96</span></td>
<td>File access is not enabled.</td></TR>
<TR><td><span  class="nobreak">&#8211;97</span></td>
<td>Disk is full.</td></TR>
<TR><td><span  class="nobreak">&#8211;98</span></td>
<td>File already exists.</td></TR>
<TR><td><span  class="nobreak">&#8211;99</span></td>
<td>File already open.</td></TR>
<TR><td><span  class="nobreak">&#8211;100</span></td>
<td>Badly formed pathname.</td></TR>
<TR><td><span  class="nobreak">&#8211;101</span></td>
<td>File is damaged.</td></TR>
<TR><td><span  class="nobreak">&#8211;102</span></td>
<td>The format of the resource file is too old to read.</td></TR>
<TR><td><span  class="nobreak">&#8211;103</span></td>
<td>File is corrupted.</td></TR>
<TR><td><span  class="nobreak">&#8211;104</span></td>
<td>The operation could not be performed.</td></TR>
<TR><td><span  class="nobreak">&#8211;105</span></td>
<td>The control passed is not a ring knob, dial, or gauge.</td></TR>
<TR><td><span  class="nobreak">&#8211;106</span></td>
<td>The control passed is not a numeric knob, dial, or gauge.</td></TR>
<TR><td><span  class="nobreak">&#8211;107</span></td>
<td>The count passed is out of range.</td></TR>
<TR><td><span  class="nobreak">&#8211;108</span></td>
<td>The keycode is not valid.</td></TR>
<TR><td><span  class="nobreak">&#8211;109</span></td>
<td>The control passed is not a ring slide with a frame.</td></TR>
<TR><td><span  class="nobreak">&#8211;110</span></td>
<td>Panel background cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;111</span></td>
<td>Title background cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;112</span></td>  
<td>Not enough memory for printing.</td></TR>
<TR><td><span  class="nobreak">&#8211;113</span></td>
<td>The shortcut key passed is reserved.</td></TR>
<TR><td><span  class="nobreak">&#8211;114</span></td>
<td>The format of the file is newer than this version of LabWindows/CVI.</td></TR>
<TR><td><span  class="nobreak">&#8211;115</span></td>
<td>System printing error.</td></TR>
<TR><td><span  class="nobreak">&#8211;116</span></td>
<td>Driver printing error.</td></TR>
<TR><td><span  class="nobreak">&#8211;117</span></td>
<td>The deferred callback queue is full.</td></TR>
<TR><td><span  class="nobreak">&#8211;118</span></td>
<td>The mouse cursor passed is invalid.</td></TR>
<TR><td><span class="nobreak">&#8211;119</span></td>
<td>Printing functions are not reentrant.</td></TR>
<TR><td><span  class="nobreak">&#8211;120</span></td>
<td>Out of Windows GDI space.</td></TR>
</table>

</td>
</tr>
</table>

</body>
</html>
    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_Create</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">panel</td>
<td class="paramDataType">integer</td>

<td>The specifier for a particular panel that is currently in memory.<br><br>

This handle will have been returned by the <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviLoadPanel.htm')">LoadPanel</a></span>, <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviNewPanel.htm')">NewPanel</a></span>, or <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviDuplicatePanel.htm')">DuplicatePanel</a></span> function.</td>
</tr>
</table>

</body>
</html>
    8    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_Create</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">label</td>
<td class="paramDataType">const&nbsp;char&nbsp;*</td>

<td>The label of the password control.<br><br>

Pass &quot;&quot; or 0 for no label.</td>
</tr>
</table>

</body>
</html>
    
    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_Create</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">top</td>
<td class="paramDataType">integer</td>

<td>The vertical coordinate at which the upper left corner of the control (not including labels) is placed.<br><br>  

The coordinate must be an integer value from -32768 to 32767.<br><br>

The origin (0,0) is at the upper-left corner of the panel (directly below the title bar) before the panel is scrolled.</td>
</tr>
</table>

</body>
</html>

      	    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_Create</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">left</td>
<td class="paramDataType">integer</td>

<td>The horizontal coordinate at which the upper left corner of the control (not including labels) is placed.<br><br> 

The coordinate must be an integer value from -32768 to 32767.<br><br>

The origin (0,0) is at the upper-left corner of the panel (directly below the title bar) before the panel is scrolled.</td>
</tr>
</table>

</body>
</html>
    	����    x    Password Control                  B8 = �      x    Panel                             E� = �  x    Label                             H8 � �     x    Top                               KJ �     x    Left                            ���� � f��                                            	                "Label"    0    0    kPassword controls can be discarded using DiscardCtrl() and DiscardPanel()
the same as for other controls.
   	    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_ConvertFromString</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<h1 class="function">PasswordCtrl_ConvertFromString</h1>

<p class="syntax">int PasswordCtrl_ConvertFromString (int panel, int stringControlToConvert);</p>

<h2 class="purpose">Purpose</h2>
<p class="Body">This function converts an existing string control into a password control.</p>

<p class="Body">While you can call <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviPasswordCtrl_Create.htm')">PasswordCtrl_Create</a></span> to create a password control from scratch, it can be more convenient to create and position a string control on a panel in the user interface editor and use this function to convert the string control to a password control after the panel is loaded.</p>

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibPasswordControl_FunctionTree.htm')">Password Control</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">custctrl\pwctrl.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 4.0 and later</p>

<!-- ADDITIONAL INFO END -->
    <!-- EXAMPLE LIST START -->

 <div class="none">
    <h2>Examples</h2>
    <p>Refer to the following examples that use the <span class="Monospace">PasswordCtrl_ConvertFromString</span> function:</p>
    <ul>
    <li><span class="Monospace">internet\ftpclnt\ftpclnt.cws</span><br><br>
    <a STYLE="cursor:hand" STYLE="color:008000" STYLE="text-decoration:underline" onClick="RunSample('internet\\ftpclnt\\ftpclnt.cws');">
    <img src="open.gif" border="0" style="padding-bottom: 4px; vertical-align: middle"></a> Open example </li>
    <li><span class="Monospace">internet\simpftp\simpftp.cws</span><br><br>
    <a STYLE="cursor:hand" STYLE="color:008000" STYLE="text-decoration:underline" onClick="RunSample('internet\\simpftp\\simpftp.cws');">
    <img src="open.gif" border="0" style="padding-bottom: 4px; vertical-align: middle"></a> Open example </li>
    <li><span class="Monospace">userint\custctrl\password\pwsample.cws</span><br><br>
    <a STYLE="cursor:hand" STYLE="color:008000" STYLE="text-decoration:underline" onClick="RunSample('userint\\custctrl\\password\\pwsample.cws');">
    <img src="open.gif" border="0" style="padding-bottom: 4px; vertical-align: middle"></a> Open example </li>
    </ul>
</div>
    <!-- EXAMPLE LIST END -->
</body>
</html>
    :    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_ConvertFromString</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">passwordControl</td>
<td class="paramDataType">integer</td>

<td>Returns the ID used to specify this control in subsequent function calls. Negative values indicate that an error occurred.<br><br>

If the function succeeds, it will return the same ID that was passed in for the <strong>stringControlToConvert</strong> parameter.<br><br>  

This means that if the <strong>stringControlToConvert</strong> was specified using a defined constant (from the UIR header file) which was assigned to the string control in the User Interface Editor, then this constant can now be used to refer to the password control.<br>

<table class="borderless">
<TR>
<td nowrap><strong>Error Codes:</strong></td><td></td>
</TR>

<TR><td><span  class="nobreak">&#8211;1</span></td>  
<td>The Interface Manager could not be opened.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;2</span></td>
<td>The system font could not be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;3</span></td>
<td>The operation attempted cannot be performed while a pop-up menu is active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;4</span></td>  
<td>Panel, pop-up, menu bar, or plot ID is invalid.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;5</span></td>
<td>Attempted to position panel at an invalid location.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;6</span></td>  
<td>Attempted to make an inoperable control the active control.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;7</span></td>
<td>The operation requires that a panel be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;8</span></td>
<td>The operation requires that a pop-up menu be active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;9</span></td>
<td>The operation requires that a menu bar be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;10</span></td>  
<td>The control is not the type expected by the function.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;11</span></td>  
<td>Invalid menu item ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;12</span></td>
<td>Out of memory.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;13</span></td>
<td>Invalid control ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;14</span></td>
<td>Value is invalid or out of range.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;15</span></td>
<td>File is not a User Interface file or has been corrupted.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;16</span></td>  
<td>File format is out-of-date.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;17</span></td>
<td>PCX image is corrupted or incompatible with current
display type.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;18</span></td>
<td>No user event possible in current configuration.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;19</span></td>  
<td>Unable to open UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;20</span></td>
<td>Error reading UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;21</span></td>  
<td>Error writing UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;22</span></td>  
<td>Error closing UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;23</span></td>  
<td>Panel state file has invalid format.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;24</span></td>
<td>Invalid panel ID or menu bar ID in resource file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;25</span></td>
<td>Error occurred during hardcopy output.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;26</span></td>
<td>Invalid default directory specified in <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviFileSelectPopup.htm')">FileSelectPopup</a></span> or <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviFileSelectPopupEx.htm')">FileSelectPopupEx</a></span> function.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;27</span></td>  
<td>Operation is invalid for specified object.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;28</span></td>  
<td>Unable to find specified string in menu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;29</span></td>  
<td>Palette menu items can only be added to the end of the menu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;30</span></td>
<td>Too many menus in the menu bar.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;31</span></td>
<td>Separators cannot have checkmarks.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;32</span></td>
<td>Separators cannot have submenus.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;33</span></td>
<td>The menu item must be a separator.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;34</span></td>
<td>The menu item cannot be a separator.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;35</span></td>
<td>The menu item already has a submenu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;36</span></td>
<td>The menu item does not have a submenu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;37</span></td>  
<td>The control ID passed must be a menu ID, a menu item ID, or NULL.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;38</span></td>
<td>The control ID passed must be a menu ID or a menu item ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;39</span></td>
<td>The control ID passed was not a submenu ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;40</span></td>
<td>The control ID passed was not a valid ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;41</span></td> 
<td>The ID is not a menu bar ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;42</span></td>  
<td>The ID is not a panel ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;43</span></td>
<td>This operation cannot be performed while this pop-up panel is active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;44</span></td>
<td>This control/panel/menu does not have the specified attribute.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;45</span></td>
<td>The control type passed was not a valid type.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;46</span></td>
<td>The attribute passed is invalid.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;47</span></td>
<td>The fill option must be set to fill above or fill below to paint ring slide's fill color.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;48</span></td>
<td>The fill option must be set to fill above or fill below to paint numeric slide's fill color.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;49</span></td>
<td>The control passed is not a ring slide.</td></TR>
<TR><td><span  class="nobreak">&#8211;50</span></td>
<td>The control passed is not a numeric slide.</td></TR>
<TR><td><span  class="nobreak">&#8211;51</span></td>  
<td>The control passed is not a ring slide with                            inc/dec arrows.</td></TR>
<TR><td><span  class="nobreak">&#8211;52</span></td>  
<td>The control passed is not a numeric slide with inc/dec arrows.</td></TR>
<TR><td><span  class="nobreak">&#8211;53</span></td>
<td>The data type passed in is not a valid data type for the control.</td></TR>
<TR><td><span  class="nobreak">&#8211;54</span></td>
<td>The attribute passed is not valid for the                                                data type of the control.</td></TR>
<TR><td><span  class="nobreak">&#8211;55</span></td>
<td>The index passed is out of range.</td></TR>
<TR><td><span  class="nobreak">&#8211;56</span></td>
<td>There are no items in the list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;57</span></td>
<td>The buffer passed was too small for the operation.</td></TR>
<TR><td><span  class="nobreak">&#8211;58</span></td>
<td>The control does not have a value.</td></TR>
<TR><td><span  class="nobreak">&#8211;59</span></td>
<td>The value passed is not in the list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;60</span></td>
<td>The control passed must be a list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;61</span></td>
<td>The control passed must be a list control or a binary switch.</td></TR>
<TR><td><span  class="nobreak">&#8211;62</span></td>
<td>The data type of the control passed must be set to a string.</td></TR>
<TR><td><span  class="nobreak">&#8211;63</span></td>
<td>That attribute is not a settable attribute.</td></TR>
<TR><td><span  class="nobreak">&#8211;64</span></td>
<td>The value passed is not a valid mode for this control.</td></TR>
<TR><td><span  class="nobreak">&#8211;65</span></td>
<td>A NULL pointer was passed when a non-NULL pointer was expected.</td></TR>
<TR><td><span  class="nobreak">&#8211;66</span></td>
<td>The text background color on a menu ring cannot be set or gotten.</td></TR>
<TR><td><span  class="nobreak">&#8211;67</span></td>
<td>The ring control passed must be one of the menu ring styles.</td></TR>
<TR><td><span  class="nobreak">&#8211;68</span></td>
<td>Text cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;69</span></td>
<td>A value cannot be converted to the specified data type.</td></TR>
<TR><td><span  class="nobreak">&#8211;70</span></td>  
<td>Invalid tab order position for control.</td></TR>
<TR><td><span  class="nobreak">&#8211;71</span></td>
<td>The tab order position of an indicator-only control cannot be set.</td></TR>
<TR><td><span  class="nobreak">&#8211;72</span></td>  
<td>Invalid number.</td></TR>
<TR><td><span  class="nobreak">&#8211;73</span></td>
<td>There is no menu bar installed for the panel.</td></TR>
<TR><td><span  class="nobreak">&#8211;74</span></td>
<td>The control passed is not a text box.</td></TR>
<TR><td><span  class="nobreak">&#8211;75</span></td>  
<td>Invalid scroll mode for chart.</td></TR>
<TR><td><span  class="nobreak">&#8211;76</span></td>
<td>Invalid image type for picture.</td></TR>
<TR><td><span  class="nobreak">&#8211;77</span></td>
<td>The attribute is valid for child panels only. Some attributes of top level panels are determined by the host operating system.</td></TR>
<TR><td><span  class="nobreak">&#8211;78</span></td>
<td>The list control passed is not in check mode.</td></TR>
<TR><td><span  class="nobreak">&#8211;79</span></td>
<td>The control values could not be completely loaded into the panel because the panel has changed.</td></TR>
<TR><td><span  class="nobreak">&#8211;80</span></td>
<td>Maximum value must be greater than minimum value.</td></TR>
<TR><td><span  class="nobreak">&#8211;81</span></td>
<td>Graph does not have that many cursors.</td></TR>
<TR><td><span  class="nobreak">&#8211;82</span></td>  
<td>Invalid plot.</td></TR>
<TR><td><span  class="nobreak">-83</span></td>
<td>New cursor position is outside plot area.</td></TR>
<TR><td><span  class="nobreak">&#8211;84</span></td>
<td>The length of the string exceeds the limit.</td></TR>
<TR><td><span  class="nobreak">&#8211;85</span></td>
<td>The specified callback function does not have the required prototype.</td></TR>
<TR><td><span  class="nobreak">&#8211;86</span></td>
<td>The specified callback function is not a known function.</td></TR>
<TR><td><span  class="nobreak">&#8211;87</span></td>
<td>Graph cannot be in this mode without cursors.</td></TR>
<TR><td><span  class="nobreak">&#8211;88</span></td>
<td>Invalid axis scaling mode for chart.</td></TR>
<TR><td><span  class="nobreak">&#8211;89</span></td>
<td>The font passed is not in font table.</td></TR>
<TR><td><span  class="nobreak">&#8211;90</span></td>
<td>The attribute value passed is not valid.</td></TR>
<TR><td><span  class="nobreak">&#8211;91</span></td>
<td>Too many files are open.</td></TR>
<TR><td><span  class="nobreak">&#8211;92</span></td>
<td>Unexpectedly reached end of file.</td></TR>
<TR><td><span  class="nobreak">&#8211;93</span></td>
<td>Input/Output error.</td></TR>
<TR><td><span  class="nobreak">&#8211;94</span></td>
<td>File not found.</td></TR>
<TR><td><span  class="nobreak">&#8211;95</span></td>
<td>File access permission denied.</td></TR>
<TR><td><span  class="nobreak">&#8211;96</span></td>
<td>File access is not enabled.</td></TR>
<TR><td><span  class="nobreak">&#8211;97</span></td>
<td>Disk is full.</td></TR>
<TR><td><span  class="nobreak">&#8211;98</span></td>
<td>File already exists.</td></TR>
<TR><td><span  class="nobreak">&#8211;99</span></td>
<td>File already open.</td></TR>
<TR><td><span  class="nobreak">&#8211;100</span></td>
<td>Badly formed pathname.</td></TR>
<TR><td><span  class="nobreak">&#8211;101</span></td>
<td>File is damaged.</td></TR>
<TR><td><span  class="nobreak">&#8211;102</span></td>
<td>The format of the resource file is too old to read.</td></TR>
<TR><td><span  class="nobreak">&#8211;103</span></td>
<td>File is corrupted.</td></TR>
<TR><td><span  class="nobreak">&#8211;104</span></td>
<td>The operation could not be performed.</td></TR>
<TR><td><span  class="nobreak">&#8211;105</span></td>
<td>The control passed is not a ring knob, dial, or gauge.</td></TR>
<TR><td><span  class="nobreak">&#8211;106</span></td>
<td>The control passed is not a numeric knob, dial, or gauge.</td></TR>
<TR><td><span  class="nobreak">&#8211;107</span></td>
<td>The count passed is out of range.</td></TR>
<TR><td><span  class="nobreak">&#8211;108</span></td>
<td>The keycode is not valid.</td></TR>
<TR><td><span  class="nobreak">&#8211;109</span></td>
<td>The control passed is not a ring slide with a frame.</td></TR>
<TR><td><span  class="nobreak">&#8211;110</span></td>
<td>Panel background cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;111</span></td>
<td>Title background cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;112</span></td>  
<td>Not enough memory for printing.</td></TR>
<TR><td><span  class="nobreak">&#8211;113</span></td>
<td>The shortcut key passed is reserved.</td></TR>
<TR><td><span  class="nobreak">&#8211;114</span></td>
<td>The format of the file is newer than this version of LabWindows/CVI.</td></TR>
<TR><td><span  class="nobreak">&#8211;115</span></td>
<td>System printing error.</td></TR>
<TR><td><span  class="nobreak">&#8211;116</span></td>
<td>Driver printing error.</td></TR>
<TR><td><span  class="nobreak">&#8211;117</span></td>
<td>The deferred callback queue is full.</td></TR>
<TR><td><span  class="nobreak">&#8211;118</span></td>
<td>The mouse cursor passed is invalid.</td></TR>
<TR><td><span class="nobreak">&#8211;119</span></td>
<td>Printing functions are not reentrant.</td></TR>
<TR><td><span  class="nobreak">&#8211;120</span></td>
<td>Out of Windows GDI space.</td></TR>
</table>

</td>
</tr>
</table>

</body>
</html>
    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_ConvertFromString</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">panel</td>
<td class="paramDataType">integer</td>

<td>The specifier for a particular panel that is currently in memory.<br><br> 

This handle will have been returned by the <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviLoadPanel.htm')">LoadPanel</a></span>, <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviNewPanel.htm')">NewPanel</a></span>, or <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviDuplicatePanel.htm')">DuplicatePanel</a></span> function.</td>
</tr>
</table>

</body>
</html>
    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_ConvertFromString</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">stringControlToConvert</td>
<td class="paramDataType">integer</td>

<td>Specifies the string control on the panel that will be converted into a password control.<br><br>

Pass the defined constant (located in the UIR header file) which was assigned to the string control in the User Interface Editor, or an ID returned by the <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviNewCtrl.htm')">NewCtrl</a></span> or <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviDuplicateCtrl.htm')">DuplicateCtrl</a></span> function.</td>
</tr>
</table>

</body>
</html>

    [=���    x    Password Control                ���� � f��                                           �R = �      x    Panel                             � =     x    String Control To Convert          	            kPassword controls can be discarded using DiscardCtrl() and DiscardPanel()
the same as for other controls.
           �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_SetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<h1 class="function">PasswordCtrl_SetAttribute</h1>

<p class="syntax">int PasswordCtrl_SetAttribute (int panel, int passwordControlID, int passwordAttribute, . . .);</p>

<h2 class="purpose">Purpose</h2>
<p class="Body">Sets an attribute for the selected password control.</p>

<p class="Body">Since attributes may take values of different data types with different valid ranges, a list of attributes, their data types and valid values are provided in the help for <strong>attributeValue</strong>.</p>

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibPasswordControl_FunctionTree.htm')">Password Control</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">custctrl\pwctrl.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 4.0 and later</p>

<!-- ADDITIONAL INFO END -->
    <!-- EXAMPLE LIST START -->

 <div class="none">
    <h2>Examples</h2>
    <p>Refer to the following examples that use the <span class="Monospace">PasswordCtrl_SetAttribute</span> function:</p>
    <ul>
    <li><span class="Monospace">internet\ftpclnt\ftpclnt.cws</span><br><br>
    <a STYLE="cursor:hand" STYLE="color:008000" STYLE="text-decoration:underline" onClick="RunSample('internet\\ftpclnt\\ftpclnt.cws');">
    <img src="open.gif" border="0" style="padding-bottom: 4px; vertical-align: middle"></a> Open example </li>
    <li><span class="Monospace">userint\custctrl\password\pwsample.cws</span><br><br>
    <a STYLE="cursor:hand" STYLE="color:008000" STYLE="text-decoration:underline" onClick="RunSample('userint\\custctrl\\password\\pwsample.cws');">
    <img src="open.gif" border="0" style="padding-bottom: 4px; vertical-align: middle"></a> Open example </li>
    </ul>
</div>
    <!-- EXAMPLE LIST END -->
</body>
</html>
    8�    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_SetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">status</td>
<td class="paramDataType">integer</td>

<td>Return value indicating whether the function was successful. A negative number indicates that an error occurred.<br>

<table class="borderless">
<TR>
<td nowrap><strong>Return Values:</strong></td><td></td>
</TR>
<TR>
<td>0</td>
<td nowrap>Success</td>
</TR>
<TR><td><span  class="nobreak">&#8211;1</span></td>  
<td>The Interface Manager could not be opened.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;2</span></td>
<td>The system font could not be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;3</span></td>
<td>The operation attempted cannot be performed while a pop-up menu is active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;4</span></td>  
<td>Panel, pop-up, menu bar, or plot ID is invalid.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;5</span></td>
<td>Attempted to position panel at an invalid location.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;6</span></td>  
<td>Attempted to make an inoperable control the active control.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;7</span></td>
<td>The operation requires that a panel be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;8</span></td>
<td>The operation requires that a pop-up menu be active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;9</span></td>
<td>The operation requires that a menu bar be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;10</span></td>  
<td>The control is not the type expected by the function.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;11</span></td>  
<td>Invalid menu item ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;12</span></td>
<td>Out of memory.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;13</span></td>
<td>Invalid control ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;14</span></td>
<td>Value is invalid or out of range.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;15</span></td>
<td>File is not a User Interface file or has been corrupted.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;16</span></td>  
<td>File format is out-of-date.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;17</span></td>
<td>PCX image is corrupted or incompatible with current
display type.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;18</span></td>
<td>No user event possible in current configuration.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;19</span></td>  
<td>Unable to open UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;20</span></td>
<td>Error reading UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;21</span></td>  
<td>Error writing UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;22</span></td>  
<td>Error closing UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;23</span></td>  
<td>Panel state file has invalid format.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;24</span></td>
<td>Invalid panel ID or menu bar ID in resource file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;25</span></td>
<td>Error occurred during hardcopy output.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;26</span></td>
<td>Invalid default directory specified in <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviFileSelectPopup.htm')">FileSelectPopup</a></span> or <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviFileSelectPopupEx.htm')">FileSelectPopupEx</a></span> function.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;27</span></td>  
<td>Operation is invalid for specified object.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;28</span></td>  
<td>Unable to find specified string in menu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;29</span></td>  
<td>Palette menu items can only be added to the end of the menu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;30</span></td>
<td>Too many menus in the menu bar.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;31</span></td>
<td>Separators cannot have checkmarks.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;32</span></td>
<td>Separators cannot have submenus.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;33</span></td>
<td>The menu item must be a separator.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;34</span></td>
<td>The menu item cannot be a separator.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;35</span></td>
<td>The menu item already has a submenu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;36</span></td>
<td>The menu item does not have a submenu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;37</span></td>  
<td>The control ID passed must be a menu ID, a menu item ID, or NULL.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;38</span></td>
<td>The control ID passed must be a menu ID or a menu item ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;39</span></td>
<td>The control ID passed was not a submenu ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;40</span></td>
<td>The control ID passed was not a valid ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;41</span></td> 
<td>The ID is not a menu bar ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;42</span></td>  
<td>The ID is not a panel ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;43</span></td>
<td>This operation cannot be performed while this pop-up panel is active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;44</span></td>
<td>This control/panel/menu does not have the specified attribute.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;45</span></td>
<td>The control type passed was not a valid type.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;46</span></td>
<td>The attribute passed is invalid.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;47</span></td>
<td>The fill option must be set to fill above or fill below to paint ring slide's fill color.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;48</span></td>
<td>The fill option must be set to fill above or fill below to paint numeric slide's fill color.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;49</span></td>
<td>The control passed is not a ring slide.</td></TR>
<TR><td><span  class="nobreak">&#8211;50</span></td>
<td>The control passed is not a numeric slide.</td></TR>
<TR><td><span  class="nobreak">&#8211;51</span></td>  
<td>The control passed is not a ring slide with                            inc/dec arrows.</td></TR>
<TR><td><span  class="nobreak">&#8211;52</span></td>  
<td>The control passed is not a numeric slide with inc/dec arrows.</td></TR>
<TR><td><span  class="nobreak">&#8211;53</span></td>
<td>The data type passed in is not a valid data type for the control.</td></TR>
<TR><td><span  class="nobreak">&#8211;54</span></td>
<td>The attribute passed is not valid for the                                                data type of the control.</td></TR>
<TR><td><span  class="nobreak">&#8211;55</span></td>
<td>The index passed is out of range.</td></TR>
<TR><td><span  class="nobreak">&#8211;56</span></td>
<td>There are no items in the list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;57</span></td>
<td>The buffer passed was too small for the operation.</td></TR>
<TR><td><span  class="nobreak">&#8211;58</span></td>
<td>The control does not have a value.</td></TR>
<TR><td><span  class="nobreak">&#8211;59</span></td>
<td>The value passed is not in the list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;60</span></td>
<td>The control passed must be a list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;61</span></td>
<td>The control passed must be a list control or a binary switch.</td></TR>
<TR><td><span  class="nobreak">&#8211;62</span></td>
<td>The data type of the control passed must be set to a string.</td></TR>
<TR><td><span  class="nobreak">&#8211;63</span></td>
<td>That attribute is not a settable attribute.</td></TR>
<TR><td><span  class="nobreak">&#8211;64</span></td>
<td>The value passed is not a valid mode for this control.</td></TR>
<TR><td><span  class="nobreak">&#8211;65</span></td>
<td>A NULL pointer was passed when a non-NULL pointer was expected.</td></TR>
<TR><td><span  class="nobreak">&#8211;66</span></td>
<td>The text background color on a menu ring cannot be set or gotten.</td></TR>
<TR><td><span  class="nobreak">&#8211;67</span></td>
<td>The ring control passed must be one of the menu ring styles.</td></TR>
<TR><td><span  class="nobreak">&#8211;68</span></td>
<td>Text cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;69</span></td>
<td>A value cannot be converted to the specified data type.</td></TR>
<TR><td><span  class="nobreak">&#8211;70</span></td>  
<td>Invalid tab order position for control.</td></TR>
<TR><td><span  class="nobreak">&#8211;71</span></td>
<td>The tab order position of an indicator-only control cannot be set.</td></TR>
<TR><td><span  class="nobreak">&#8211;72</span></td>  
<td>Invalid number.</td></TR>
<TR><td><span  class="nobreak">&#8211;73</span></td>
<td>There is no menu bar installed for the panel.</td></TR>
<TR><td><span  class="nobreak">&#8211;74</span></td>
<td>The control passed is not a text box.</td></TR>
<TR><td><span  class="nobreak">&#8211;75</span></td>  
<td>Invalid scroll mode for chart.</td></TR>
<TR><td><span  class="nobreak">&#8211;76</span></td>
<td>Invalid image type for picture.</td></TR>
<TR><td><span  class="nobreak">&#8211;77</span></td>
<td>The attribute is valid for child panels only. Some attributes of top level panels are determined by the host operating system.</td></TR>
<TR><td><span  class="nobreak">&#8211;78</span></td>
<td>The list control passed is not in check mode.</td></TR>
<TR><td><span  class="nobreak">&#8211;79</span></td>
<td>The control values could not be completely loaded into the panel because the panel has changed.</td></TR>
<TR><td><span  class="nobreak">&#8211;80</span></td>
<td>Maximum value must be greater than minimum value.</td></TR>
<TR><td><span  class="nobreak">&#8211;81</span></td>
<td>Graph does not have that many cursors.</td></TR>
<TR><td><span  class="nobreak">&#8211;82</span></td>  
<td>Invalid plot.</td></TR>
<TR><td><span  class="nobreak">-83</span></td>
<td>New cursor position is outside plot area.</td></TR>
<TR><td><span  class="nobreak">&#8211;84</span></td>
<td>The length of the string exceeds the limit.</td></TR>
<TR><td><span  class="nobreak">&#8211;85</span></td>
<td>The specified callback function does not have the required prototype.</td></TR>
<TR><td><span  class="nobreak">&#8211;86</span></td>
<td>The specified callback function is not a known function.</td></TR>
<TR><td><span  class="nobreak">&#8211;87</span></td>
<td>Graph cannot be in this mode without cursors.</td></TR>
<TR><td><span  class="nobreak">&#8211;88</span></td>
<td>Invalid axis scaling mode for chart.</td></TR>
<TR><td><span  class="nobreak">&#8211;89</span></td>
<td>The font passed is not in font table.</td></TR>
<TR><td><span  class="nobreak">&#8211;90</span></td>
<td>The attribute value passed is not valid.</td></TR>
<TR><td><span  class="nobreak">&#8211;91</span></td>
<td>Too many files are open.</td></TR>
<TR><td><span  class="nobreak">&#8211;92</span></td>
<td>Unexpectedly reached end of file.</td></TR>
<TR><td><span  class="nobreak">&#8211;93</span></td>
<td>Input/Output error.</td></TR>
<TR><td><span  class="nobreak">&#8211;94</span></td>
<td>File not found.</td></TR>
<TR><td><span  class="nobreak">&#8211;95</span></td>
<td>File access permission denied.</td></TR>
<TR><td><span  class="nobreak">&#8211;96</span></td>
<td>File access is not enabled.</td></TR>
<TR><td><span  class="nobreak">&#8211;97</span></td>
<td>Disk is full.</td></TR>
<TR><td><span  class="nobreak">&#8211;98</span></td>
<td>File already exists.</td></TR>
<TR><td><span  class="nobreak">&#8211;99</span></td>
<td>File already open.</td></TR>
<TR><td><span  class="nobreak">&#8211;100</span></td>
<td>Badly formed pathname.</td></TR>
<TR><td><span  class="nobreak">&#8211;101</span></td>
<td>File is damaged.</td></TR>
<TR><td><span  class="nobreak">&#8211;102</span></td>
<td>The format of the resource file is too old to read.</td></TR>
<TR><td><span  class="nobreak">&#8211;103</span></td>
<td>File is corrupted.</td></TR>
<TR><td><span  class="nobreak">&#8211;104</span></td>
<td>The operation could not be performed.</td></TR>
<TR><td><span  class="nobreak">&#8211;105</span></td>
<td>The control passed is not a ring knob, dial, or gauge.</td></TR>
<TR><td><span  class="nobreak">&#8211;106</span></td>
<td>The control passed is not a numeric knob, dial, or gauge.</td></TR>
<TR><td><span  class="nobreak">&#8211;107</span></td>
<td>The count passed is out of range.</td></TR>
<TR><td><span  class="nobreak">&#8211;108</span></td>
<td>The keycode is not valid.</td></TR>
<TR><td><span  class="nobreak">&#8211;109</span></td>
<td>The control passed is not a ring slide with a frame.</td></TR>
<TR><td><span  class="nobreak">&#8211;110</span></td>
<td>Panel background cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;111</span></td>
<td>Title background cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;112</span></td>  
<td>Not enough memory for printing.</td></TR>
<TR><td><span  class="nobreak">&#8211;113</span></td>
<td>The shortcut key passed is reserved.</td></TR>
<TR><td><span  class="nobreak">&#8211;114</span></td>
<td>The format of the file is newer than this version of LabWindows/CVI.</td></TR>
<TR><td><span  class="nobreak">&#8211;115</span></td>
<td>System printing error.</td></TR>
<TR><td><span  class="nobreak">&#8211;116</span></td>
<td>Driver printing error.</td></TR>
<TR><td><span  class="nobreak">&#8211;117</span></td>
<td>The deferred callback queue is full.</td></TR>
<TR><td><span  class="nobreak">&#8211;118</span></td>
<td>The mouse cursor passed is invalid.</td></TR>
<TR><td><span class="nobreak">&#8211;119</span></td>
<td>Printing functions are not reentrant.</td></TR>
<TR><td><span  class="nobreak">&#8211;120</span></td>
<td>Out of Windows GDI space.</td></TR>
</table>

</td>
</tr>
</table>

</body>
</html>
    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_SetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">panel</td>
<td class="paramDataType">integer</td>

<td>The specifier for a particular panel that is currently in memory.<br><br>

This handle will have been returned by the <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviLoadPanel.htm')">LoadPanel</a></span>, <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviNewPanel.htm')">NewPanel</a></span>, or <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviDuplicatePanel.htm')">DuplicatePanel</a></span> function.</td>
</tr>
</table>

</body>
</html>
    u    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_SetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">passwordControlID</td>
<td class="paramDataType">integer</td>

<td>The ID returned by the <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviPasswordCtrl_Create.htm')">PasswordCtrl_Create</a></span> or <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviPasswordCtrl_ConvertFromString.htm')">PasswordCtrl_ConvertFromString</a></span> function.</td>
</tr>
</table>

</body>
</html>

        <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">

<title>PasswordCtrl_SetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">passwordAttribute</td>
<td class="paramDataType">integer</td>

<td>The <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ListOfPasswordCtrlAttr.html')">password control attribute</a> value to set.<br><br>

In the function panel, when you click the control or press &lt;Enter&gt;, &lt;Spacebar&gt;, or &lt;Ctrl-down arrow&gt;, a dialog box appears containing a hierarchical list of the available attributes. Attributes whose values cannot be obtained are dimmed. Help text is shown for each attribute. To select an attribute, double-click it or select it and then press &lt;Enter&gt;.<br><br>

If the attribute shown in this ring control has named constants as valid values, you can open a list of them by moving to the Attribute Value control and pressing &lt;Enter&gt;. The Attribute Values dialog box displays the values and value help for the constants.
</td>
</tr>
</table>

</body>
</html>
    |    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">

<title>PasswordCtrl_SetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">attributeValue</td>
<td class="paramDataType">any&nbsp;type (passed by value)</td>

<td>The value of the specified <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ListOfPasswordCtrlAttr.html')">password control attribute</a>.<br><br>

If the attribute shown in this control has named constants as valid values, you can open a list of them by pressing &lt;Enter&gt;. The Attribute Values dialog box displays the values and value help for the constants.
</td>
</tr>
</table>

</body>
</html>
    �4���    x    Status                            ߼ = �      x    Panel                             � =(     x    Password Control ID               �� � p    �    Password Attribute                � �(    x    Attribute Value                    	                                0       �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_GetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<h1 class="function">PasswordCtrl_GetAttribute</h1>

<p class="syntax">int PasswordCtrl_GetAttribute (int panel, int passwordControlID, int passwordAttribute, void *attributeValue);</p>

<h2 class="purpose">Purpose</h2>
<p class="Body">Obtains the value of a password control attribute from the selected panel and control.</p>

<p class="Body">Since attributes may take values of different data types with different valid ranges, a list of attributes, their data types and valid values are provided in the help for <strong>attributeValue</strong>.</p>

<!-- ADDITIONAL INFO START -->

<h2>Additional Information</h2>

<p class="Indent1"><strong>Library:</strong> <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','toolslibPasswordControl_FunctionTree.htm')">Password Control</a></p>

<p class="Indent1"><strong>Include file:</strong> <span class="Monospace">custctrl\pwctrl.h</span></p>

<p class="Indent1"><strong>LabWindows/CVI compatibility:</strong> LabWindows/CVI 4.0 and later</p>

<!-- ADDITIONAL INFO END -->
    <!-- EXAMPLE LIST START -->

 <div class="none">
    <h2>Example</h2>
    <p>Refer to <span class="Monospace">userint\custctrl\password\pwsample.cws</span> for an example of using the <span class="Monospace">PasswordCtrl_GetAttribute</span> function.</p>
    <p class="Body"><a STYLE="cursor:hand" STYLE="color:008000" STYLE="text-decoration:underline" onClick="RunSample('userint\\custctrl\\password\\pwsample.cws');">
    <img src="open.gif" border="0" style="padding-bottom: 4px; vertical-align: middle"></a> Open example </p>
</div>
    <!-- EXAMPLE LIST END -->
</body>
</html>

    8�    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_GetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">status</td>
<td class="paramDataType">integer</td>

<td>Return value indicating whether the function was successful. A negative number indicates that an error occurred.<br>

<table class="borderless">
<TR>
<td nowrap><strong>Return Values:</strong></td><td></td>
</TR>
<TR>
<td>0</td>
<td nowrap>Success</td>
</TR>
<TR><td><span  class="nobreak">&#8211;1</span></td>  
<td>The Interface Manager could not be opened.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;2</span></td>
<td>The system font could not be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;3</span></td>
<td>The operation attempted cannot be performed while a pop-up menu is active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;4</span></td>  
<td>Panel, pop-up, menu bar, or plot ID is invalid.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;5</span></td>
<td>Attempted to position panel at an invalid location.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;6</span></td>  
<td>Attempted to make an inoperable control the active control.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;7</span></td>
<td>The operation requires that a panel be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;8</span></td>
<td>The operation requires that a pop-up menu be active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;9</span></td>
<td>The operation requires that a menu bar be loaded.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;10</span></td>  
<td>The control is not the type expected by the function.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;11</span></td>  
<td>Invalid menu item ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;12</span></td>
<td>Out of memory.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;13</span></td>
<td>Invalid control ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;14</span></td>
<td>Value is invalid or out of range.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;15</span></td>
<td>File is not a User Interface file or has been corrupted.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;16</span></td>  
<td>File format is out-of-date.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;17</span></td>
<td>PCX image is corrupted or incompatible with current
display type.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;18</span></td>
<td>No user event possible in current configuration.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;19</span></td>  
<td>Unable to open UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;20</span></td>
<td>Error reading UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;21</span></td>  
<td>Error writing UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;22</span></td>  
<td>Error closing UIR file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;23</span></td>  
<td>Panel state file has invalid format.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;24</span></td>
<td>Invalid panel ID or menu bar ID in resource file.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;25</span></td>
<td>Error occurred during hardcopy output.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;26</span></td>
<td>Invalid default directory specified in <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviFileSelectPopup.htm')">FileSelectPopup</a></span> or <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviFileSelectPopupEx.htm')">FileSelectPopupEx</a></span> function.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;27</span></td>  
<td>Operation is invalid for specified object.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;28</span></td>  
<td>Unable to find specified string in menu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;29</span></td>  
<td>Palette menu items can only be added to the end of the menu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;30</span></td>
<td>Too many menus in the menu bar.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;31</span></td>
<td>Separators cannot have checkmarks.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;32</span></td>
<td>Separators cannot have submenus.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;33</span></td>
<td>The menu item must be a separator.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;34</span></td>
<td>The menu item cannot be a separator.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;35</span></td>
<td>The menu item already has a submenu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;36</span></td>
<td>The menu item does not have a submenu.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;37</span></td>  
<td>The control ID passed must be a menu ID, a menu item ID, or NULL.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;38</span></td>
<td>The control ID passed must be a menu ID or a menu item ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;39</span></td>
<td>The control ID passed was not a submenu ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;40</span></td>
<td>The control ID passed was not a valid ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;41</span></td> 
<td>The ID is not a menu bar ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;42</span></td>  
<td>The ID is not a panel ID.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;43</span></td>
<td>This operation cannot be performed while this pop-up panel is active.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;44</span></td>
<td>This control/panel/menu does not have the specified attribute.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;45</span></td>
<td>The control type passed was not a valid type.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;46</span></td>
<td>The attribute passed is invalid.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;47</span></td>
<td>The fill option must be set to fill above or fill below to paint ring slide's fill color.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;48</span></td>
<td>The fill option must be set to fill above or fill below to paint numeric slide's fill color.</td>
</TR>
<TR><td><span  class="nobreak">&#8211;49</span></td>
<td>The control passed is not a ring slide.</td></TR>
<TR><td><span  class="nobreak">&#8211;50</span></td>
<td>The control passed is not a numeric slide.</td></TR>
<TR><td><span  class="nobreak">&#8211;51</span></td>  
<td>The control passed is not a ring slide with                            inc/dec arrows.</td></TR>
<TR><td><span  class="nobreak">&#8211;52</span></td>  
<td>The control passed is not a numeric slide with inc/dec arrows.</td></TR>
<TR><td><span  class="nobreak">&#8211;53</span></td>
<td>The data type passed in is not a valid data type for the control.</td></TR>
<TR><td><span  class="nobreak">&#8211;54</span></td>
<td>The attribute passed is not valid for the                                                data type of the control.</td></TR>
<TR><td><span  class="nobreak">&#8211;55</span></td>
<td>The index passed is out of range.</td></TR>
<TR><td><span  class="nobreak">&#8211;56</span></td>
<td>There are no items in the list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;57</span></td>
<td>The buffer passed was too small for the operation.</td></TR>
<TR><td><span  class="nobreak">&#8211;58</span></td>
<td>The control does not have a value.</td></TR>
<TR><td><span  class="nobreak">&#8211;59</span></td>
<td>The value passed is not in the list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;60</span></td>
<td>The control passed must be a list control.</td></TR>
<TR><td><span  class="nobreak">&#8211;61</span></td>
<td>The control passed must be a list control or a binary switch.</td></TR>
<TR><td><span  class="nobreak">&#8211;62</span></td>
<td>The data type of the control passed must be set to a string.</td></TR>
<TR><td><span  class="nobreak">&#8211;63</span></td>
<td>That attribute is not a settable attribute.</td></TR>
<TR><td><span  class="nobreak">&#8211;64</span></td>
<td>The value passed is not a valid mode for this control.</td></TR>
<TR><td><span  class="nobreak">&#8211;65</span></td>
<td>A NULL pointer was passed when a non-NULL pointer was expected.</td></TR>
<TR><td><span  class="nobreak">&#8211;66</span></td>
<td>The text background color on a menu ring cannot be set or gotten.</td></TR>
<TR><td><span  class="nobreak">&#8211;67</span></td>
<td>The ring control passed must be one of the menu ring styles.</td></TR>
<TR><td><span  class="nobreak">&#8211;68</span></td>
<td>Text cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;69</span></td>
<td>A value cannot be converted to the specified data type.</td></TR>
<TR><td><span  class="nobreak">&#8211;70</span></td>  
<td>Invalid tab order position for control.</td></TR>
<TR><td><span  class="nobreak">&#8211;71</span></td>
<td>The tab order position of an indicator-only control cannot be set.</td></TR>
<TR><td><span  class="nobreak">&#8211;72</span></td>  
<td>Invalid number.</td></TR>
<TR><td><span  class="nobreak">&#8211;73</span></td>
<td>There is no menu bar installed for the panel.</td></TR>
<TR><td><span  class="nobreak">&#8211;74</span></td>
<td>The control passed is not a text box.</td></TR>
<TR><td><span  class="nobreak">&#8211;75</span></td>  
<td>Invalid scroll mode for chart.</td></TR>
<TR><td><span  class="nobreak">&#8211;76</span></td>
<td>Invalid image type for picture.</td></TR>
<TR><td><span  class="nobreak">&#8211;77</span></td>
<td>The attribute is valid for child panels only. Some attributes of top level panels are determined by the host operating system.</td></TR>
<TR><td><span  class="nobreak">&#8211;78</span></td>
<td>The list control passed is not in check mode.</td></TR>
<TR><td><span  class="nobreak">&#8211;79</span></td>
<td>The control values could not be completely loaded into the panel because the panel has changed.</td></TR>
<TR><td><span  class="nobreak">&#8211;80</span></td>
<td>Maximum value must be greater than minimum value.</td></TR>
<TR><td><span  class="nobreak">&#8211;81</span></td>
<td>Graph does not have that many cursors.</td></TR>
<TR><td><span  class="nobreak">&#8211;82</span></td>  
<td>Invalid plot.</td></TR>
<TR><td><span  class="nobreak">-83</span></td>
<td>New cursor position is outside plot area.</td></TR>
<TR><td><span  class="nobreak">&#8211;84</span></td>
<td>The length of the string exceeds the limit.</td></TR>
<TR><td><span  class="nobreak">&#8211;85</span></td>
<td>The specified callback function does not have the required prototype.</td></TR>
<TR><td><span  class="nobreak">&#8211;86</span></td>
<td>The specified callback function is not a known function.</td></TR>
<TR><td><span  class="nobreak">&#8211;87</span></td>
<td>Graph cannot be in this mode without cursors.</td></TR>
<TR><td><span  class="nobreak">&#8211;88</span></td>
<td>Invalid axis scaling mode for chart.</td></TR>
<TR><td><span  class="nobreak">&#8211;89</span></td>
<td>The font passed is not in font table.</td></TR>
<TR><td><span  class="nobreak">&#8211;90</span></td>
<td>The attribute value passed is not valid.</td></TR>
<TR><td><span  class="nobreak">&#8211;91</span></td>
<td>Too many files are open.</td></TR>
<TR><td><span  class="nobreak">&#8211;92</span></td>
<td>Unexpectedly reached end of file.</td></TR>
<TR><td><span  class="nobreak">&#8211;93</span></td>
<td>Input/Output error.</td></TR>
<TR><td><span  class="nobreak">&#8211;94</span></td>
<td>File not found.</td></TR>
<TR><td><span  class="nobreak">&#8211;95</span></td>
<td>File access permission denied.</td></TR>
<TR><td><span  class="nobreak">&#8211;96</span></td>
<td>File access is not enabled.</td></TR>
<TR><td><span  class="nobreak">&#8211;97</span></td>
<td>Disk is full.</td></TR>
<TR><td><span  class="nobreak">&#8211;98</span></td>
<td>File already exists.</td></TR>
<TR><td><span  class="nobreak">&#8211;99</span></td>
<td>File already open.</td></TR>
<TR><td><span  class="nobreak">&#8211;100</span></td>
<td>Badly formed pathname.</td></TR>
<TR><td><span  class="nobreak">&#8211;101</span></td>
<td>File is damaged.</td></TR>
<TR><td><span  class="nobreak">&#8211;102</span></td>
<td>The format of the resource file is too old to read.</td></TR>
<TR><td><span  class="nobreak">&#8211;103</span></td>
<td>File is corrupted.</td></TR>
<TR><td><span  class="nobreak">&#8211;104</span></td>
<td>The operation could not be performed.</td></TR>
<TR><td><span  class="nobreak">&#8211;105</span></td>
<td>The control passed is not a ring knob, dial, or gauge.</td></TR>
<TR><td><span  class="nobreak">&#8211;106</span></td>
<td>The control passed is not a numeric knob, dial, or gauge.</td></TR>
<TR><td><span  class="nobreak">&#8211;107</span></td>
<td>The count passed is out of range.</td></TR>
<TR><td><span  class="nobreak">&#8211;108</span></td>
<td>The keycode is not valid.</td></TR>
<TR><td><span  class="nobreak">&#8211;109</span></td>
<td>The control passed is not a ring slide with a frame.</td></TR>
<TR><td><span  class="nobreak">&#8211;110</span></td>
<td>Panel background cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;111</span></td>
<td>Title background cannot be colored transparent.</td></TR>
<TR><td><span  class="nobreak">&#8211;112</span></td>  
<td>Not enough memory for printing.</td></TR>
<TR><td><span  class="nobreak">&#8211;113</span></td>
<td>The shortcut key passed is reserved.</td></TR>
<TR><td><span  class="nobreak">&#8211;114</span></td>
<td>The format of the file is newer than this version of LabWindows/CVI.</td></TR>
<TR><td><span  class="nobreak">&#8211;115</span></td>
<td>System printing error.</td></TR>
<TR><td><span  class="nobreak">&#8211;116</span></td>
<td>Driver printing error.</td></TR>
<TR><td><span  class="nobreak">&#8211;117</span></td>
<td>The deferred callback queue is full.</td></TR>
<TR><td><span  class="nobreak">&#8211;118</span></td>
<td>The mouse cursor passed is invalid.</td></TR>
<TR><td><span class="nobreak">&#8211;119</span></td>
<td>Printing functions are not reentrant.</td></TR>
<TR><td><span  class="nobreak">&#8211;120</span></td>
<td>Out of Windows GDI space.</td></TR>
</table>

</td>
</tr>
</table> 

</body>
</html>
    �    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_GetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">panel</td>
<td class="paramDataType">integer</td>

<td>The specifier for a particular panel that is currently in memory.<br><br> 

This handle will have been returned by the <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviLoadPanel.htm')">LoadPanel</a></span>, <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviNewPanel.htm')">NewPanel</a></span>, or <span class="Monospace"><a href="javascript:LaunchHelp('cvi.chm::/UIRef/cviDuplicatePanel.htm')">DuplicatePanel</a></span> function.</td>
</tr>
</table>

</body>
</html>
    u    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">
<title>PasswordCtrl_GetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">passwordControlID</td>
<td class="paramDataType">integer</td>

<td>The ID returned by the <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviPasswordCtrl_Create.htm')">PasswordCtrl_Create</a></span> or <span class="Monospace"><a href="javascript:LaunchMergedHelp('cvi.chm', 'toolslib.chm', 'FunctionReference/cviPasswordCtrl_ConvertFromString.htm')">PasswordCtrl_ConvertFromString</a></span> function.</td>
</tr>
</table>

</body>
</html>

        <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">

<title>PasswordCtrl_GetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">passwordAttribute</td>
<td class="paramDataType">integer</td>

<td>The <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ListOfPasswordCtrlAttr.html')">password control attribute</a> value to obtain.<br><br>

In the function panel, when you click the control or press &lt;Enter&gt;, &lt;Spacebar&gt;, or &lt;Ctrl-down arrow&gt;, a dialog box appears containing a hierarchical list of the available attributes. Attributes whose values cannot be obtained are dimmed. Help text is shown for each attribute. To select an attribute, double-click it or select it and then press &lt;Enter&gt;.<br><br>

If the attribute shown in this ring control has named constants as valid values, you can open a list of them by moving to the Attribute Value control and pressing &lt;Enter&gt;. The Attribute Values dialog box displays the values and value help for the constants.
</td>
</tr>
</table>

</body>
</html>
    h    <html>
<head>
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=utf-8">

<title>PasswordCtrl_GetAttribute</title>

<link rel="stylesheet" href="styles.css" type="text/css">
<script src="launchhelp.js" type="text/javascript"></script>
<script src="helpSampleInclude.js" type="text/javascript"></script>
</head>

<body>
<table class=borderless><TR>

     <td class="paramName">attributeValue</td>
<td class="paramDataType">void&nbsp;*</td>

<td>The value of the specified <a href="javascript:LaunchMergedHelp('cvi.chm','toolslib.chm','ListOfPasswordCtrlAttr.html')">password control attribute</a>.<br><br>

If the attribute shown in this control has named constants as valid values, you can open a list of them by pressing &lt;Enter&gt;. The Attribute Values dialog box displays the values and value help for the constants.
</td>
</tr>
</table>

</body>
</html>
    �o���    x    Status                           0� = �      x    Panel                            4� =(     x    Password Control ID              8< � p    �    Password Attribute               =V �(    x    Attribute Value                    	                                0    	         ����         �  N[     K.    PasswordCtrl_Create             ����         P,  �     K.    PasswordCtrl_ConvertFromString  ����         �b  �     K.    PasswordCtrl_SetAttribute       ����         �� @�     K.    PasswordCtrl_GetAttribute              �                                     DCreate A Password Control            DConvert String Ctrl To Password      DSet A Password Ctrl Attribute        DGet A Password Ctrl Attribute         toolbox.fp 