using Random
println(1000000)
println(5000000)
for i in 1:1000000
	println(abs(4*rand(Int32)%1000))
end
