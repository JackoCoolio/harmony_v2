
function moveCamera()

	local x, y, x_s, y_s, rot = get_camera_transform()
	local speed = 0.1
	
	local x_d = 0
	local y_d = 0

	if (key_pressed(harmony.key.a)) then
		x_d = -speed
	end
	if (key_pressed(harmony.key.d)) then
		x_d = speed
	end
	
	if (key_pressed(harmony.key.w)) then
		y_d = speed
	end
	
	if (key_pressed(harmony.key.s)) then
		y_d = -speed
	end
	
	set_camera_position(x + x_d, y + y_d)

	-- rotation
	if (key_pressed(harmony.key.q)) then
		set_camera_rotation(rot + speed)
	end
	if (key_pressed(harmony.key.e)) then
		set_camera_rotation(rot - speed / 10)
	end
	
	print(get_camera_transform())
end

function checkForClose()
	if (key_down(harmony.key.escape)) then
		print("closing...")
		close_application()
	end
end

--[[

-- this is how I want to be able to do it!

-- called with every index 1 to num_entities
-- each function still has to perform its own "mask"
function testIncrement(entity)
	if has_components(i, 'transform') then -- the "mask"
		local tf = get_component(i, 'transform')
		tf.x = tf.x + 1
		tf.y = tf.y + 1
	end
end

]]

--[[
function testPrint()
	for i=1,scene_data.num_entities do
		if has_components(i, "transform", "person") then
			local tf = get_component(i, "transform")
			local person = get_component(i, "person")

			print("printing entity " .. i)
			print(person.name .. " is at " .. tf.x .. ", " .. tf.y)

			
		end
	end
end

function test()
	print(has_components(4, "transform", "person"))
end

]]