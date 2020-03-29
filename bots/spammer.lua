local distance = 0

function loop()
	local direction = math.random() * 360;
	radar(direction)
	fire(direction, 5000)
end
