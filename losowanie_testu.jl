for j in 1:4
	println(100000*Int32(floor(j+1/2)))
	println(1000000*(j%8+1))
	for i in 1:(100000*Int32(floor(j+1/2)))
		println(rand(UInt32)%11519 + rand(UInt32)%100*11411 + rand(UInt32)%2)
	end
end