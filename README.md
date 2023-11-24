# AdventOfCode
Advent Of Code by @topaz

Some solutions to raised problems on [Advent Of Code Web Page](https://adventofcode.com/), **!!warning!!** aren't the most efficient solutions

### <a name="Steps">Steps📄
```
$ mkdir build
$ cd build
$ cmake .. -G "Visual Studio 15 2017 Win64" //where you can choose your compiler
$ cmake .. -G "Visual Studio 16 2019"
```
- **Build** folder is a solution folder, in my case use visual studio 
- In my case **deploy** folder is a compile results (exe file), you can change in DayX/CMakeLists file


### <a name="Info">Info ​ℹ️​
In year 2023, I included the auto download input files and tests.

- You can copy-paste directly your input data in inputs folder (input01.txt, input02.txt, ...), but if you want to activate auto download 
you have to create a new file "cookie" with web cookie number and to fill the COOKIE_PATH() in <a href=https://github.com/JulyMaker/AdventOfCode/blob/main/2023/utils/paths.h.in>paths.h.in</a>

- The tests use the example folder files (inputExample01.txt, inputExample02.txt, ...). You need to modify the file <a href=https://github.com/JulyMaker/AdventOfCode/blob/main/2023/gtest/src/adventOfCode2023_test.cpp>adventOfCode2023_test.cpp</a>
with your own solutions.

### <a name="Author">Author ✒️

* **July Maker** - *Initial work and documentation* - [JulyMaker](https://github.com/JulyMaker)

<!-- También puedes mirar la lista de todos los [contribuyentes](https://github.com/your/project/contributors) quíenes han participado en este proyecto.--> 

### <a name="Thankyou">Thank you 🎁

 <!-- 📢 🍺 🤓 📄 📌 🖇️ 🔧 ⌨️ 🔩 ⚙️ 🚀 📋-->

[Advent Web page](https://adventofcode.com/) - @topaz
