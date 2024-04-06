
### main.lua 回调
初始化，会在循环更新和绘制前执行
```lua
function init()

end
```

循环更新，会每帧执行 dt
```lua
function update(dt)

end
```
绘制
```lua
function draw()

end
```
按键按下
```lua
function keyDown(keyCode)

end
```

### conf.lua
```lua
conf = {
	width = 800,
	height = 600,
	title = "game"
}
```

## 绘制API
绘制矩形
```lua
zmy.graphics.rectangle("line", x, y, w, h)
```
创建texture
```lua
local img = zmy.graphics.newImage(path) -- 返回table,{texture,width,height}
```
绘制texture,img.texture, x, y必传，后面的顺序填写，不填默认,{ox,oy}旋转的中心点，默认是中心
```lua
zmy.graphics.draw(img.texture, x, y，{qx,qy,qw,qh},rot,{ox,oy},flip)
```
设置颜色 r,g,b,a
```lua
zmy.graphics.setColor(255,255,0,255)
```



