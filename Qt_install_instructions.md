# Qt Installation Instructions (Visual Studio 2022)

**1.** Qt is required in order to work on this project and its GUI. (We use open-source Qt on this project)<br/>
   Download link: [Qt Open-Source Installer](https://www.qt.io/download-qt-installer?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4) <br/><br/>

**2.** After opening the installer, it will ask you to create an account before installation. Just use any email you want to sign up and whatever password you want and verify the account through email. <br/><br/>

**3.** After that, follow these images in the Qt installer: <br/><br/>

![image1](https://user-images.githubusercontent.com/61435002/202375325-7deba605-17a9-403b-9c2e-9fac5f97620a.png) <br/>

![image2](https://user-images.githubusercontent.com/61435002/202375337-cebdec8f-c17a-4d7e-ac19-2b8b95b34abd.png) <br/>

![image3](https://user-images.githubusercontent.com/61435002/202375345-700cbe05-3e9d-4747-8d00-2214f8f29142.png) <br/>

![image4](https://user-images.githubusercontent.com/61435002/202375355-496ffecb-c047-4af8-a8ab-3b632d16b1d5.png) <br/>

**4.** After that, agree to the license agreement and the standard 'Qt' start menu shortcut, and install. It should take around 4 to 5GB of space and take some time. <br/><br/>

**5.** After the install finishes, it might open a stand alone Qt editor. Just ignore it and close it. <br/><br/>

**6.** Open Visual Studio and go to Extensions > Manage Extensions, and install this one at the top.<br/><br/>
![image6](https://user-images.githubusercontent.com/61435002/202375775-8cbfdd9c-6039-438e-a436-ab475bd80266.png) <br/>

**7.** After installing the extension, go to **Extensions > Qt VS Tools > Qt Versions** <br/><br/>

**8.** Then to to Versions, and set the path to *C:\Qt\6.4.0\msvc2019_64\bin\qmake.exe* in the explorer window that pops up when setting the path. It should look like this after that: <br/>
![image7](https://user-images.githubusercontent.com/61435002/202376066-b078ef5c-21e9-44d5-8491-4726b8acf58b.png) <br/>

**9.** After that, click OK and restart Visual Studio. You should then be able to modify .ui files for Qt. <br/><br/>

**10.** For reference, the UI for the Qt .ui form designer looks like this in Visual Studio: <br/>
![image8](https://user-images.githubusercontent.com/61435002/202376350-bd7db2e0-dc6a-4178-92e8-9497802d6e62.png) <br/>
