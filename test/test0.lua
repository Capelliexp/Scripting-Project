--all print borde ha ett indrag på 3 spaces

--a = 5
--b = 3
--c = a+b
--io.write("   this should print 8: ", c, "\n")

--io.write("   AddMesh({{1,2,3},{4,5,6},{7,8,9}}) \n")
--AddMesh({{1,2,3},{4,5,6},{7,8,9}})

io.write("   AddBox(): \n")
addBox({-20,10,30}, 4, "testBox1")
--AddBox({-20,10,30}, 4)
--AddBox({-20,30}, 4, "testBox1")
--AddBox({-20,10,30})
--AddBox({-20,,10,30})

io.write("\n   AddMesh(): \n")
addMesh({{50,50,50}, {50,70,50}, {50,60,80}})
--AddMesh({"orange"},{},{}) -- Error: non-numeric coordinates
--AddMesh({{1,2,3,4},{1,1,1},{2,2,2}}) -- Error: number of components
--AddMesh({{1,2,3}}) -- Error: not a valid number of vertices

camera({50,50,50}, {0,0,0})

for k,v in pairs(getNodes()) do print(k,v) end
--for k,v in pairs(getNodes()) do for kk,vv in pairs(v) do print(k,kk,vv) end end
