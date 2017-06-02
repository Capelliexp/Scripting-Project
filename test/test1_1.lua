for i=1,10 do addBox({i,i,i},1.0-i/11.0) end
for k,v in pairs(getNodes()) do print(k,v) end
camera({-10,0,0},{0,2,0})
snapshot("test1.png")
