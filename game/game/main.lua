local player = {
	x = 100,
	y = 100,
	width = 100,
	height = 100
}
local dir = 1
local speed = 0.1
local g = zmy.graphics
local rot = 0;
function init( )
	print("init -engine")
	print(g.newImage)
	img = g.newImage("D:\\workspace\\love2d\\Love2D-Template-master\\assets\\sprites\\sprites\\sprite_sheet.png")
	img2 = g.newImage("D:\\workspace\\love2d\\Love2D-Template-master\\assets\\sprites\\sprites\\player1.png")
	print("======",img.width,img.height,img.texture)
	print("======",img2.width,img2.height,img2.texture)
end


function update( dt )
	--print("-update  "..dt)
	
	rot = rot + 0.1;
	player.x = player.x + speed
	if player.x >= 500 then
		speed = -0.1
	end
	if player.x <= 0  then
		speed = 0.1
	end

end



function draw()
	g.drawImage(img2.texture,100,3)
	g.drawImage(img.texture,200,3)
	g.drawImage(img.texture,player.x,player.y,{0,0,100,100},rot,{0,0},true)
	g.setColor(255,255,0,255)
	g.rectangle("fill",player.x,player.y,player.width,player.height)
	g.rectangle("fill",100,200,300,400)

end


function keyDown( keycode )
	print(#keys,keys.key_FIRST,keys.key_w,keycode)
	if keycode == keys.key_w then
		print("====")
	end
	
end
