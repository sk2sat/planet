global_settings {
	assumed_gamma 1.0
}

#macro CAM(p, l, a)
camera{
	location p
	angle	 a
//	right <-1.33,0,0>
//	direction <0,1,0>
	look_at l
}
#end

#macro LIGHT_SRC(p, at)
light_source{
	p
	color rgb <1,1,1>
	parallel
	point_at at
}
#end

#macro SP(p, r)
sphere{
	p, r
	pigment {
		rgbt <1,1,1,0>
	}
}
#end

//background {color rgb <0,0,1>}

