
camera{
	location <1000, 100, 100>
	sky	 <0, 0, 1>
	look_at	 <0, 0, 0>
	angle	 45
}

light_source{
	<2,3,5>
	color rgb 1.5 * <1,1,1>
	parallel
	point_at <0,0,0>
}

#macro SP(p, r)
sphere{
	p, r*10
	pigment {
		rgbt <1,1,1,0>
	}
}
#end

