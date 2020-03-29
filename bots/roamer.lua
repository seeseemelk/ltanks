local distance = 0

function loop()
	if distance <= 0 then
		distance = math.random(10)
		local direction = math.random() * 360;
		move(direction, 1000)
		radar(direction)
	else
		distance = distance - 1
	end
end
