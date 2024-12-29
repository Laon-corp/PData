<?xml version="1.0" encoding="UTF-8"?>
<distribution version="20.0.0" name="Main" type="MSI">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{C72AFB54-CC38-47BC-AA9C-AF022F6EE5E3}">
		<general appName="Main" outputLocation="e:\@PROJECT_P\CVI2020\JTC_Forth\cvidistkit.Main" relOutputLocation="cvidistkit.Main" outputLocationWithVars="e:\@PROJECT_P\CVI2020\JTC_Forth\cvidistkit.%name" relOutputLocationWithVars="cvidistkit.%name" upgradeBehavior="1" autoIncrement="true" version="1.0.28">
			<arp company="LAON-CORP" companyURL="" supportURL="" contact="" phone="" comments=""/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="Korean" showPaths="true" showRuntimeOnly="true" readMe="" license="">
			<dlgstrings welcomeTitle="Main" welcomeText=""/></userinterface>
		<dirs appDirID="101">
			<installDir name="Main" dirID="100" parentID="7" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Main" dirID="101" parentID="2" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="[Program Files]" dirID="2" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="e:\@PROJECT_P\CVI2020\JTC_Forth\cvibuild.Main\Release\Main.exe" targetDir="101" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput targetType="0" dirID="101" projectID="0">
				<fileID>0</fileID></projectOutput>
			<projectDependencies dirID="101" projectID="0"/></fileGroups>
		<shortcuts>
			<shortcut name="Main" targetFileID="0" destDirID="100" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules/>
		<products/>
		<runtimeEngine installToAppDir="false" activeXsup="false" analysis="true" cvirte="true" dotnetsup="true" instrsup="true" lowlevelsup="true" lvrt="true" netvarsup="true" rtutilsup="true">
			<hasSoftDeps/>
			<doNotAutoSelect>
			<component>activeXsup</component>
			</doNotAutoSelect></runtimeEngine><sxsRuntimeEngine>
			<selected>true</selected>
			<doNotAutoSelect>false</doNotAutoSelect></sxsRuntimeEngine>
		<advanced mediaSize="650">
			<exeName>install.exe</exeName>
			<launchConditions>
				<condition>MINOS_WIN7_SP1</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<baselineProducts>
			<product name="NI LabWindows/CVI Shared Runtime 2020 f2" UC="{80D3D303-75B9-4607-9312-E5FC68E5BFD2}" productID="{DE72BF5F-7980-4210-BE46-772981ED334C}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="20.2.49152">
				<dependencies>
					<productID>{07298686-C518-4981-9AE1-6E62273BF43A}</productID>
					<productID>{0B476064-821E-4BA8-A0A8-489ECDDAAD55}</productID>
					<productID>{0FFFDCED-4232-4312-BBDB-179F9FDAB7EA}</productID>
					<productID>{192594FE-5397-4F45-8137-A5C487CE3849}</productID>
					<productID>{1C79B8BD-F5F8-4825-8BC8-78098A726AE1}</productID>
					<productID>{249C8903-A1E5-4CC7-A564-2FD4C268BDC4}</productID>
					<productID>{28B285EA-90C8-4C3A-94C0-B0196A3FEF07}</productID>
					<productID>{39CB13EF-8677-4FF8-942D-20021AFD7AB6}</productID>
					<productID>{3F36AC37-CC28-4780-AF19-D80ACEDE0323}</productID>
					<productID>{41BDEA25-514E-4BDA-AC47-186E97C9D3F7}</productID>
					<productID>{43C6873A-8548-4944-AF22-8B1C3312A070}</productID>
					<productID>{4C351C60-5ECC-4920-AEB6-DFE60EA14283}</productID>
					<productID>{539F08CF-F2FD-482C-A5ED-65FD2620789D}</productID>
					<productID>{62418E99-C730-4D5D-96B2-B4DDB810A652}</productID>
					<productID>{64ECB814-3A6A-4E48-9D2F-D6C2EDD725B7}</productID>
					<productID>{67CFC7DD-BF77-4D45-9AE9-742AA8658AE7}</productID>
					<productID>{69586F66-56DA-43BD-BB8E-A6DAE9A4DF6D}</productID>
					<productID>{866E5D39-AB76-4536-B1CA-554BC66A1900}</productID>
					<productID>{9905478F-5785-468A-A35A-D84325D61EB8}</productID>
					<productID>{A12FB799-41BF-4A9A-98F2-2FE4F333B718}</productID>
					<productID>{A59D9F6E-27DE-410C-9820-9D844DC78D05}</productID>
					<productID>{A7BC6F18-28B4-4D26-9C6C-802B3A8DA0F8}</productID>
					<productID>{AFC999BB-F270-46EF-B748-AE755EC75322}</productID>
					<productID>{B524884D-C3AC-417A-939E-34A16118A14C}</productID>
					<productID>{C0A9F5E2-DCD5-44C1-8B03-C560F4C06D6C}</productID>
					<productID>{C1771155-665A-4C7F-B85D-D4AACF786223}</productID>
					<productID>{C18DA001-CF46-48A5-8DDB-322EA6DBFB4F}</productID>
					<productID>{D8F71C3E-C0AE-4D69-920E-7D927C950A1A}</productID>
					<productID>{DCCB918E-584B-4FAF-BDA4-EF5A7B90C4C1}</productID>
					<productID>{DEDA7399-29FE-40A5-8B64-F630D40EF8C0}</productID>
					<productID>{EB6C9E35-CBA2-4C2B-8958-55EA6F0EA707}</productID>
					<productID>{EDEDDCAE-21E6-4A82-9B58-8E6337386685}</productID>
					<productID>{EFC648C5-F3BC-4096-9AFE-23121EF06828}</productID>
					<productID>{F2EEE63A-0DCA-41BF-A243-4E4C0DFA38A4}</productID></dependencies></product>
			<product name="NI LabWindows/CVI SQL Toolkit Runtime 2.4" UC="{8DA1044F-11DE-49F4-9025-80D29C697004}" productID="{D2679C2C-17AF-4DB0-8F0B-C7F8C58252B8}" path="(None)" flavorID="Full" flavorName="Full" verRestr="false" coreVer="2.40.49152">
				<dependencies>
					<productID>{07298686-C518-4981-9AE1-6E62273BF43A}</productID>
					<productID>{1C79B8BD-F5F8-4825-8BC8-78098A726AE1}</productID>
					<productID>{64ECB814-3A6A-4E48-9D2F-D6C2EDD725B7}</productID>
					<productID>{866E5D39-AB76-4536-B1CA-554BC66A1900}</productID></dependencies></product>
			<product name="NI LabWindows/CVI Side-By-Side Runtime (Current Version)" UC="{CF830703-BC3D-4feb-891F-6FF27153C204}" productID="{C35FAD11-FC79-4FEC-A961-639B21367D73}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="20.1.49155">
				<dependencies>
					<productID>{07298686-C518-4981-9AE1-6E62273BF43A}</productID>
					<productID>{0D22F8E4-086C-4836-8091-D46FE500C463}</productID>
					<productID>{0FFFDCED-4232-4312-BBDB-179F9FDAB7EA}</productID>
					<productID>{1861267F-4109-4317-8FC2-7143B2B2135E}</productID>
					<productID>{192594FE-5397-4F45-8137-A5C487CE3849}</productID>
					<productID>{1956734F-D50E-46B8-970C-B6826C48FF72}</productID>
					<productID>{1C79B8BD-F5F8-4825-8BC8-78098A726AE1}</productID>
					<productID>{249C8903-A1E5-4CC7-A564-2FD4C268BDC4}</productID>
					<productID>{39CB13EF-8677-4FF8-942D-20021AFD7AB6}</productID>
					<productID>{41BDEA25-514E-4BDA-AC47-186E97C9D3F7}</productID>
					<productID>{4C351C60-5ECC-4920-AEB6-DFE60EA14283}</productID>
					<productID>{4FCA6CDA-7080-4672-91FE-83D90A9324EE}</productID>
					<productID>{5FBBCE69-5C20-4C52-881D-0CCD8A4419A3}</productID>
					<productID>{62418E99-C730-4D5D-96B2-B4DDB810A652}</productID>
					<productID>{64ECB814-3A6A-4E48-9D2F-D6C2EDD725B7}</productID>
					<productID>{67D37779-0192-487F-B306-730E1900B42B}</productID>
					<productID>{69586F66-56DA-43BD-BB8E-A6DAE9A4DF6D}</productID>
					<productID>{72B66836-C0E3-4636-935A-664148B502C2}</productID>
					<productID>{866E5D39-AB76-4536-B1CA-554BC66A1900}</productID>
					<productID>{A12FB799-41BF-4A9A-98F2-2FE4F333B718}</productID>
					<productID>{A59D9F6E-27DE-410C-9820-9D844DC78D05}</productID>
					<productID>{AFC999BB-F270-46EF-B748-AE755EC75322}</productID>
					<productID>{B6EB7403-B407-441E-800F-4DCDEF772F81}</productID>
					<productID>{C0A9F5E2-DCD5-44C1-8B03-C560F4C06D6C}</productID>
					<productID>{C1771155-665A-4C7F-B85D-D4AACF786223}</productID>
					<productID>{D0372445-91B2-47BA-BC6E-5AC55AA12028}</productID>
					<productID>{D6B32C2F-8858-4891-919D-DD54B3673956}</productID>
					<productID>{EA58F2B7-F3F0-43D7-8A9C-0B5DDFDD6874}</productID>
					<productID>{EB6C9E35-CBA2-4C2B-8958-55EA6F0EA707}</productID>
					<productID>{EFC648C5-F3BC-4096-9AFE-23121EF06828}</productID>
					<productID>{F2EEE63A-0DCA-41BF-A243-4E4C0DFA38A4}</productID>
					<productID>{F5F37752-3659-40EF-AC86-D1D287E670DA}</productID></dependencies></product>
			<product name="NI LabWindows/CVI Side-By-Side Runtime 2020 f1" UC="{7E4ADDFD-9FFB-4C37-8CEC-FEC9395C38F7}" productID="{C35FAD11-FC79-4FEC-A961-639B21367D73}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="20.1.49155">
				<dependencies>
					<productID>{07298686-C518-4981-9AE1-6E62273BF43A}</productID>
					<productID>{0D22F8E4-086C-4836-8091-D46FE500C463}</productID>
					<productID>{0FFFDCED-4232-4312-BBDB-179F9FDAB7EA}</productID>
					<productID>{1861267F-4109-4317-8FC2-7143B2B2135E}</productID>
					<productID>{192594FE-5397-4F45-8137-A5C487CE3849}</productID>
					<productID>{1956734F-D50E-46B8-970C-B6826C48FF72}</productID>
					<productID>{1C79B8BD-F5F8-4825-8BC8-78098A726AE1}</productID>
					<productID>{249C8903-A1E5-4CC7-A564-2FD4C268BDC4}</productID>
					<productID>{39CB13EF-8677-4FF8-942D-20021AFD7AB6}</productID>
					<productID>{41BDEA25-514E-4BDA-AC47-186E97C9D3F7}</productID>
					<productID>{4C351C60-5ECC-4920-AEB6-DFE60EA14283}</productID>
					<productID>{4FCA6CDA-7080-4672-91FE-83D90A9324EE}</productID>
					<productID>{5FBBCE69-5C20-4C52-881D-0CCD8A4419A3}</productID>
					<productID>{62418E99-C730-4D5D-96B2-B4DDB810A652}</productID>
					<productID>{64ECB814-3A6A-4E48-9D2F-D6C2EDD725B7}</productID>
					<productID>{67D37779-0192-487F-B306-730E1900B42B}</productID>
					<productID>{69586F66-56DA-43BD-BB8E-A6DAE9A4DF6D}</productID>
					<productID>{72B66836-C0E3-4636-935A-664148B502C2}</productID>
					<productID>{866E5D39-AB76-4536-B1CA-554BC66A1900}</productID>
					<productID>{A12FB799-41BF-4A9A-98F2-2FE4F333B718}</productID>
					<productID>{A59D9F6E-27DE-410C-9820-9D844DC78D05}</productID>
					<productID>{AFC999BB-F270-46EF-B748-AE755EC75322}</productID>
					<productID>{B6EB7403-B407-441E-800F-4DCDEF772F81}</productID>
					<productID>{C0A9F5E2-DCD5-44C1-8B03-C560F4C06D6C}</productID>
					<productID>{C1771155-665A-4C7F-B85D-D4AACF786223}</productID>
					<productID>{D0372445-91B2-47BA-BC6E-5AC55AA12028}</productID>
					<productID>{D6B32C2F-8858-4891-919D-DD54B3673956}</productID>
					<productID>{EA58F2B7-F3F0-43D7-8A9C-0B5DDFDD6874}</productID>
					<productID>{EB6C9E35-CBA2-4C2B-8958-55EA6F0EA707}</productID>
					<productID>{EFC648C5-F3BC-4096-9AFE-23121EF06828}</productID>
					<productID>{F2EEE63A-0DCA-41BF-A243-4E4C0DFA38A4}</productID>
					<productID>{F5F37752-3659-40EF-AC86-D1D287E670DA}</productID></dependencies></product></baselineProducts>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="e:\@PROJECT_P\CVI2020\JTC_Forth\Main.prj" ProjectRelativePath="Main.prj"/></Projects>
		<buildData progressBarRate="4.181235453086812">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>0.274213316289316</ProductsAdded>
				<DPConfigured>1.611973279561986</DPConfigured>
				<DPMergeModulesAdded>1.812216046573626</DPMergeModulesAdded>
				<DPClosed>2.193203756351218</DPClosed>
				<DistributionsCopied>2.306474536021262</DistributionsCopied>
				<End>23.916376181631829</End></progressTimes></buildData>
	</msi>
</distribution>
