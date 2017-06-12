--all print borde ha ett indrag på 3 spaces

--a = 5
--b = 3
--c = a+b
--io.write("   this should print 8: ", c, "\n")

--io.write("   AddMesh({{1,2,3},{4,5,6},{7,8,9}}) \n")


io.write("   addBox(): \n")
addBox({0,0,0}, 4, "testBox1")
addBox({-20,10,30}, 4, "testBox1")
addBox({-20,10,30}, 4)
addBox({-20,30}, 4, "testBox1")
addBox({-20,10,30})
addBox({-20,,10,30})

io.write("\n   addMesh(): \n")
addMesh({{1,2,3},{4,5,6},{7,8,9} , {6,7,8},{9,10,11},{12,13,14}})
addMesh({{50,50,50}, {50,70,50}, {50,60,80}})
addMesh({{orange},{},{}}) -- Error: non-numeric coordinates
addMesh({{"orange",2,3},{1,2,3},{1,2,3}}) -- Error: non-numeric coordinates
addMesh({{1,2,3,4},{1,1,1},{2,2,2}}) -- Error: number of components
addMesh({{1,2,3}}) -- Error: not a valid number of vertices

addMesh({{5,4,3},{2,1,0},{6,6,6} , {9,8,7},{6,5,4},{10,11,12} , {23,25,21},{18,16,25},{30,25,32}})
addMesh({{1000,2000,3000},{4000,5000,6000},{7000,8000,9000} , {6000,7000,8000},{9000,10000,11000},{12000,13000,14000}})
addMesh({{1,2,3},{4,5,6},{7,8,9} , {15,15,15},{20,20,20},{15,20,40} , {10,11,12},{13,14,15},{16,17,19} , {15,23,13},{97,34,19},{25,32,10}})

io.write("\n   camera(): \n")
camera({50,50,50}, {0,0,0})
--camera({50,50,}, {0,0,0})
--camera({50,50}, {0,0,0})
--camera({50,50,50}, {0,0})
--camera({,50,50}, {0,,0})
camera({10,50,50}, {haha})
camera({10,50,50}, {"haha"})

for i=1,10 do addBox({i,i,i},1.0-i/11.0) end
addBox({0,0,0}, 4, "testBox1")
addMesh({{1,2,3},{4,5,6},{7,8,9} , {6,7,8},{9,10,11},{12,13,14}})
camera({50,50,50}, {0,0,0})
for k,v in pairs(getNodes()) do for kk,vv in pairs(v) do print(k,kk,vv) end end
