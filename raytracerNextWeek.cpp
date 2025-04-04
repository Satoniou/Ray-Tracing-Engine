#include "rtweek.h"

#include "bvh.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "texture.h"

void bouncing_spheres()
{
	hittable_list world;

	auto checker = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, make_shared<lambertian>(checker)));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9)
			{
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8)
				{
					// diffuse
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					auto center2 = center + vec3(0, random_double(0, .5), 0);
					world.add(make_shared<sphere>(center, center2, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95)
				{
					// metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else
				{
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	world = hittable_list(make_shared<bvh_node>(world));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 1200;
	cam.samples_per_pixel = 500;
	cam.max_depth = 50;

	cam.vfov = 20;
	cam.lookfrom = point3(13, 2, 3);
	cam.lookat = point3(0, 0, 0);
	cam.vup = vec3(0, 1, 0);

	cam.defocus_angle = 0.6;
	cam.focus_dist = 10.0;

	cam.render(world);
}

void checkered_spheres()
{
	hittable_list world;

	auto checker = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));

	world.add(make_shared<sphere>(point3(0, -10, 0), 10, make_shared<lambertian>(checker)));
	world.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 1200;
	cam.samples_per_pixel = 500;
	cam.max_depth = 50;

	cam.vfov = 20;
	cam.lookfrom = point3(13, 2, 3);
	cam.lookat = point3(0, 0, 0);
	cam.vup = vec3(0, 1, 0);

	cam.defocus_angle = 0;

	cam.render(world);
}

void various_spheres() 
{
	hittable_list world;
	
	shared_ptr<metal> material1 = make_shared<metal>(color(0.05, 0.4, 0.3), 0.0);
	shared_ptr<dielectric> material2 = make_shared<dielectric>(1.5);
	shared_ptr<dielectric> material2_5 = make_shared<dielectric>(1 / 1.5);
	shared_ptr<lambertian> material3 = make_shared<lambertian>(color(0.3, 0.05, 0.4));
	shared_ptr<metal> material4 = make_shared<metal>(color(0.5, 0.5, 0.5), 0.0);
	shared_ptr<metal> material5 = make_shared<metal>(color(0.3, 0.5, 0.1), 0.1);

	shared_ptr<lambertian> ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));

	world.add(make_shared<sphere>(point3(-1, 1, 4), 1.0, material1));
	world.add(make_shared<sphere>(point3(2, 1.5, 4), 1.5, material5));
	world.add(make_shared<sphere>(point3(-2.4, 0.3, 3.6), 0.3, material3));
	world.add(make_shared<sphere>(point3(-2.4, 0.3, 3.6), 0.3, material3));
	world.add(make_shared<sphere>(point3(-7, 5.8, 20), 6.0, material4));
	world.add(make_shared<sphere>(point3(-3, 2, 10), 2.0, material2));
	world.add(make_shared<sphere>(point3(-3, 2, 10), 1.95, material2_5));
	world.add(make_shared<sphere>(point3(-0.3, 0.6, 2), 0.6, material2));

	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 1200;
	cam.samples_per_pixel = 500;
	cam.max_depth = 50;

	cam.vfov = 30;
	cam.lookfrom = point3(0, 2, -5);
	cam.lookat = point3(0, 1.5, 0);
	cam.vup = vec3(0, 1, 0);

	cam.defocus_angle = 0;

	cam.render(world);
}


void four_spheres()
{
	hittable_list world;

	shared_ptr<lambertian> material1 = make_shared<lambertian>(color(0.1, 0.4, 0.3));
	shared_ptr<lambertian> material2 = make_shared<lambertian>(color(0.5, 0.15, 0.7));
	shared_ptr<lambertian> material3 = make_shared<lambertian>(color(0.7, 0.6, 0.5));
	shared_ptr<lambertian> material4 = make_shared<lambertian>(color(1.0, 0.843, 0.0));

	world.add(make_shared<sphere>(point3(1, 1, 5), 0.7, material1));
	world.add(make_shared<sphere>(point3(1, -1, 5), 0.7, material2));
	world.add(make_shared<sphere>(point3(-1, -1, 5), 0.7, material3));
	world.add(make_shared<sphere>(point3(-1, 1, 5), 0.7, material4));

	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 1200;
	cam.samples_per_pixel = 500;
	cam.max_depth = 50;

	cam.vfov = 40;
	cam.lookfrom = point3(0, 1, 0);
	cam.lookat = point3(0, 0, 5);
	cam.vup = vec3(0, 1, 0);

	cam.defocus_angle = 0;

	cam.render(world);
}

void mirrored_spheres()
{
	hittable_list world;

	shared_ptr<metal> material1 = make_shared<metal>(color(0.05, 0.4, 0.3), 0.0);
	shared_ptr<metal> material2 = make_shared<metal>(color(0.5, 0.5, 0.5), 0.0);

	world.add(make_shared<sphere>(point3(0, 0, 5), 3.0, material2));
	world.add(make_shared<sphere>(point3(0, 0, -5), 3.0, material2));
	
	camera cam;

	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 400;
	cam.samples_per_pixel = 100;
	cam.max_depth = 50;

	cam.vfov = 20;
	cam.lookfrom = point3(0, 0, 0);
	cam.lookat = point3(0, 0, 1);
	cam.vup = vec3(0, 1, 0);

	cam.defocus_angle = 0;

	cam.render(world);
}

int main()
{
	switch (3)
	{
	case 1:
		bouncing_spheres();
		break;
	case 2:
		checkered_spheres();
		break;
	case 3:
		various_spheres();
		break;
	case 4:
		four_spheres();
		break;
	case 5:
		mirrored_spheres();
		break;
	default:
		break;
	}

	return 0;
}
