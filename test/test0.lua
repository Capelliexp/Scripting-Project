--all print borde ha ett indrag på 3 spaces

--a = 5
--b = 3
--c = a+b
--io.write("   this should print 8: ", c, "\n")

--io.write("   AddMesh({{1,2,3},{4,5,6},{7,8,9}}) \n")


io.write("   addBox(): \n")
addBox({-20,10,30}, 4, "testBox1")
--addBox({-20,10,30}, 4)
--addBox({-20,30}, 4, "testBox1")
--addBox({-20,10,30})
--addBox({-20,,10,30})

io.write("\n   addMesh(): \n")
addMesh({{1,2,3},{4,5,6},{7,8,9} , {6,7,8},{9,10,11},{12,13,14}})
--addMesh({{1,2,3},{4,5,6},{7,8,9} , {15,15,15},{20,20,20},{15,20,40} , {10,11,12},{13,14,15},{16,17,19}})
--addMesh({{50,50,50}, {50,70,50}, {50,60,80}})
--addMesh({"orange"},{},{}) -- Error: non-numeric coordinates
--addMesh({{1,2,3,4},{1,1,1},{2,2,2}}) -- Error: number of components
--addMesh({{1,2,3}}) -- Error: not a valid number of vertices

io.write("\n   camera(): \n")
camera({50,50,50}, {0,0,0})
--camera({50,50,}, {0,0,0})
--camera({50,50}, {0,0,0})
--camera({50,50,50}, {0,0})
--camera({,50,50}, {0,,0})

--addBox({0,0,0}, 4, "testBox1")
--addMesh({{1,2,3},{4,5,6},{7,8,9} , {6,7,8},{9,10,11},{12,13,14}})
--camera({50,50,50}, {0,0,0})
--for k,v in pairs(getNodes()) do for kk,vv in pairs(v) do print(k,kk,vv) end end
