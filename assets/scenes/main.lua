scene_data.name = "Main"

add_entity({
    components = {
        transform = {
            x = 5,
            y = 7
        },
        person = {
            name = "john"
        }
    }
})

add_entity({
    components = {
        transform = {
            x = 12,
            y = 0
        },
        person = {
            name = "greg"
        }
    }
})

add_entity({
    components = {
        enemy = {
            name = "evil man"
        }
    }
})

add_entity({
    components = {
        transform = {
            x = -1,
            y = 2000
        },
        enemy = {
            name = "test"
        }
    }
})

load_script("assets/ecs.lua")

add_system("moveCamera")
add_system("checkForClose")

set_camera_transform(0, 0, 1, 1, 0)
