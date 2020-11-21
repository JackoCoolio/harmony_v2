scene_data = {
	num_entities = 0,
	components = {}
}

function add_entity(e)
	scene_data.num_entities = scene_data.num_entities + 1
	for component, data in pairs(e.components) do
		if scene_data.components[component] == nil then
			scene_data.components[component] = {}
		end
		if #scene_data.components[component] ~= scene_data.num_entities - 1 then
			for i = #scene_data.components[component] + 1, scene_data.num_entities - 1 do
				scene_data.components[component][i] = 0
			end
		end
		table.insert(scene_data.components[component], data)
	end
end

function has_components(index, ...)
	local arg = {...}
	for _, componentName in ipairs(arg) do
		if scene_data.components[componentName] == nil or type(scene_data.components[componentName][index]) ~= 'table' then
			return false
		end
	end
	return true
end

function get_component(index, componentName)
	return scene_data.components[componentName][index]
end

-- INPUT HELPER FUNCTIONS --

function click_released(button)
	return (get_click_state(button) <= -1)
end

function click_up(button)
	return (get_click_state(button) == -1)
end

function click_down(button)
	return (get_click_state(button) == 1)
end

function click_pressed(button)
	return (get_click_state(button) >= 1)
end

function key_released(key)
	return (get_key_state(key) <= -1)
end

function key_up(key)
	return (get_key_state(key) == -1)
end

function key_down(key)
	return (get_key_state(key) == 1)
end

function key_pressed(key)
	return (get_key_state(key) >= 1)
end

-- INPUT HELPER FUNCTIONS

-- CAMERA HELPER FUNCTIONS

function set_camera_position(x, y)
	local a, b, x_s, y_s, rot = get_camera_transform()
	set_camera_transform(x, y, x_s, y_s, rot)
end

function set_camera_scale(x_s, y_s)
	local x, y, a, b, rot = get_camera_transform()
	set_camera_transform(x, y, x_s, y_s, rot)
end

function set_camera_rotation(rot)
	local x, y, x_s, y_s, a = get_camera_transform()
	set_camera_transform(x, y, x_s, y_s, rot)
end

-- CAMERA HELPER FUNCTIONS

-- RENDERER HELPER FUNCTIONS

-- RENDERER HELPER FUNCTIONS

-- HARMONY CONSTANTS --

harmony = {
	mouse = {
		left = 0,
		right = 1,
		middle = 2
	},
	button = {
		released = -2,
		up = -1,
		unseen = 0,
		down = 1,
		pressed = 2
	},
	key = {}
}

-- HARMONY CONSTANTS --
