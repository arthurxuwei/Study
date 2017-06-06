/**
* lufylegend.ui
* @version 0.2.0
* @Explain HTML5开源引擎lufylegend的专用UI
* @author lufy(lufy_legend)
* @blog http://blog.csdn.net/lufy_Legend
* @email lufy.legend@gmail.com
* @homepage http://lufylegend.com/lufylegend
* @svn http://lufylegend.googlecode.com/svn/trunk/
* @github https://github.com/lufylegend/lufylegend.js
*/
function LButtonSample1(name,size,font,color){
	var s = this;
	if(!size)size=16;
	if(!color)color = "white";
	if(!font)font = "黑体";
	s.backgroundColor = "black";
	var btn_up = new LSprite();
	btn_up.shadow = new LSprite();
	btn_up.back = new LSprite();
	btn_up.addChild(btn_up.shadow);
	btn_up.addChild(btn_up.back);
	labelText = new LTextField();
	labelText.color = color;
	labelText.font = font;
	labelText.size = size;
	labelText.x = size*0.5;
	labelText.y = size*0.5;
	labelText.text = name;
	s.labelText = labelText;
	btn_up.back.addChild(labelText);
	var shadow = new LDropShadowFilter(4,45,"#000000",10);
	btn_up.shadow.filters = [shadow];
	var btn_down = new LSprite();
	btn_down.x = btn_down.y = 1;
	labelText = new LTextField();
	labelText.color = color;
	labelText.font = font;
	labelText.size = size;
	labelText.x = size*0.5;
	labelText.y = size*0.5;
	labelText.text = name;
	btn_down.addChild(labelText);
	base(s,LButton,[btn_up,btn_down]);
	s.baseWidth = s.width = labelText.getWidth() + size;
	s.baseHeight = s.height = 2.2*size;
	s.backgroundSet = null;
	s.widthSet = null;
	s.heightSet = null;
	s.xSet = null;
	s.ySet = null;
	s.addEventListener(LEvent.ENTER_FRAME,s._onDraw);
}
LButtonSample1.prototype.clone = function(){
	var s = this,name = s.labelText.text,size = s.labelText.size,font = s.labelText.font,color = s.labelText.color,
	a = new LButtonSample1(name,size,font,color);
	a.backgroundColor = s.backgroundColor;
	return a;
};
LButtonSample1.prototype._onDraw = function(s){
	var co = s.getRootCoordinate(),labelText;
	if(s.backgroundSet == s.backgroundColor && s.widthSet == s.width && s.heightSet == s.height && s.xSet == co.x && s.ySet == co.y)return;
	s.backgroundSet = s.backgroundColor;
	s.widthSet = s.width>s.baseWidth?s.width:s.baseWidth;
	s.heightSet = s.height>s.baseHeight?s.height:s.baseHeight;
	s.width = s.widthSet;
	s.height = s.heightSet;
	s.xSet = co.x;
	s.ySet = co.y;
	labelText = s.bitmap_up.back.getChildAt(0);
	labelText.x = (s.width - s.baseWidth + labelText.size)*0.5;
	labelText.y = (s.height - s.baseHeight + labelText.size)*0.5;
	labelText = s.bitmap_over.getChildAt(0);
	labelText.x = (s.width - s.baseWidth + labelText.size)*0.5;
	labelText.y = (s.height - s.baseHeight + labelText.size)*0.5;
	var grd=LGlobal.canvas.createLinearGradient(0,-s.height*0.5,0,s.height*2);
	grd.addColorStop(0,"white");
	grd.addColorStop(1,s.backgroundColor);
	var grd2=LGlobal.canvas.createLinearGradient(0,-s.height,0,s.height*2);
	grd2.addColorStop(0,"white");
	grd2.addColorStop(1,s.backgroundColor);
	s.bitmap_up.back.graphics.clear();
	s.bitmap_over.graphics.clear();
	s.bitmap_up.shadow.graphics.clear();
	s.bitmap_up.shadow.graphics.drawRoundRect(0,"#000000",[1,1,s.widthSet-2,s.heightSet-2,s.heightSet*0.1],true,"#000000");
	s.bitmap_up.back.graphics.drawRect(1,s.backgroundColor,[0,0,s.widthSet,s.heightSet],true,grd);
	s.bitmap_up.back.graphics.drawRect(0,s.backgroundColor,[1,s.heightSet*0.5,s.widthSet-2,s.heightSet*0.5-1],true,grd2);
	s.bitmap_over.graphics.drawRect(1,s.backgroundColor,[0,0,s.widthSet,s.heightSet],true,grd);
	s.bitmap_over.graphics.drawRect(0,s.backgroundColor,[1,s.heightSet*0.5,s.widthSet-2,s.heightSet*0.5-1],true,grd2);
};
LButtonSample1.prototype.toString = function(){
	return "[LButtonSample1]";
};
function LButtonSample2(name,size,font,color){
	var s = this;
	base(s,LButtonSample1,[name,size,font,color]);
}
LButtonSample2.prototype.clone = function(){
	var s = this,name = s.labelText.text,size = s.labelText.size,font = s.labelText.font,color = s.labelText.color,
	a = new LButtonSample2(name,size,font,color);
	a.backgroundColor = s.backgroundColor;
	return a;
};
LButtonSample2.prototype._onDraw = function(s){
	var co = s.getRootCoordinate();
	if(s.backgroundSet == s.backgroundColor)return;
	s.backgroundSet = s.backgroundColor;
	s.xSet = co.x;
	s.ySet = co.y;
	var grd=LGlobal.canvas.createLinearGradient(0,-s.height*0.5,0,s.height*2);
	grd.addColorStop(0,"white");
	grd.addColorStop(1,s.backgroundColor);
	
	var grd2=LGlobal.canvas.createLinearGradient(0,-s.height,0,s.height*2);
	grd2.addColorStop(0,"white");
	grd2.addColorStop(1,s.backgroundColor);
	
	s.bitmap_up.back.graphics.clear();
	s.bitmap_over.graphics.clear();
	s.bitmap_up.back.graphics.drawRoundRect(1,s.backgroundColor,[0,0,s.width,s.height,s.height*0.1],true,grd);
	s.bitmap_up.back.graphics.drawRoundRect(0,s.backgroundColor,[1,s.height*0.5,s.width-2,s.height*0.5-1,s.height*0.1],true,grd2);
	s.bitmap_over.graphics.drawRoundRect(1,s.backgroundColor,[0,0,s.width,s.height,s.height*0.1],true,grd);
	s.bitmap_over.graphics.drawRoundRect(0,s.backgroundColor,[1,s.height*0.5,s.width-2,s.height*0.5-1,s.height*0.1],true,grd2);
};
LButtonSample2.prototype.toString = function(){
	return "[LButtonSample2]";
};
function LRadioChild(value,layer,layerSelect){
	var s = this;
	base(s,LSprite,[]);
	s.value = value;
	
	if(!layer){
		layer = new LSprite();
		layer.graphics.drawArc(2,"#000000",[0,0,10,0,2*Math.PI],true,"#D3D3D3");
	}
	if(!layerSelect){
		layerSelect = new LSprite();
		layerSelect.graphics.drawArc(0,"#000000",[0,0,4,0,2*Math.PI],true,"#000000");
	}
	s.layer = layer;
	s.layerSelect = layerSelect;
	s.addChild(s.layer);
	s.addChild(s.layerSelect);
	s.layerSelect.visible = false;
	s.checked = false;
	s.addEventListener(LMouseEvent.MOUSE_UP,s._onChange);
}
LRadioChild.prototype.clone = function(){
	var s = this,
	a = new LRadioChild(s.value,s.layer,s.layerSelect);
	a.copyProperty(s);
	return a;
};
LRadioChild.prototype._onChange = function(e){
	var s = e.clickTarget;
	s.parent.setValue(s.value);
};
LRadioChild.prototype.setChecked = function(v){
	this.layerSelect.visible = this.checked = v;
};
LRadioChild.prototype.toString = function(){
	return "[LRadioChild]";
};
function LRadio(){
	base(this,LSprite,[]);
}
LRadio.prototype.setChildRadio = function(value,x,y,layer,layerSelect){
	var s = this;
	var child = new LRadioChild(value,layer,layerSelect);
	child.x = x;
	child.y = y;
	s.addChild(child);
};
LRadio.prototype.push = function(value){
	this.addChild(value);
};
LRadio.prototype.setValue = function(value){
    var s=this,child,k=null;
    for(k in s.childList){
    	child = s.childList[k];
        if(child.setChecked)child.setChecked(false);
        if(child.value == value){
        	s.value = value;
        	child.setChecked(true);
        }
    }
};
LRadio.prototype.clone = function(){
	var s = this,a = new LRadio(),child,k=null;
    for(k in s.childList){
    	child = s.childList[k].clone();
    	a.push(child);
    }
	a.setValue(s.value);
	return a;
};
LRadio.prototype.toString = function(){
	return "[LRadio]";
};

function LCheckBox(layer,layerSelect){
	var s = this;
	base(s,LSprite,[]);
	
	if(!layer){
		layer = new LSprite();
		layer.graphics.drawRect(2,"#000000",[0,0,20,20],true,"#D3D3D3");
	}
	if(!layerSelect){
		layerSelect = new LSprite();
		layerSelect.graphics.drawLine(5,"#000000",[2,10,10,18]);
		layerSelect.graphics.drawLine(5,"#000000",[10,18,18,2]);
	}
	s.layer = layer;
	s.layerSelect = layerSelect;
	s.addChild(s.layer);
	s.addChild(s.layerSelect);
	s.layerSelect.visible = s.checked = false;
	s.addEventListener(LMouseEvent.MOUSE_UP,s._onChange);
}
LCheckBox.prototype._onChange = function(e){
	var s = e.clickTarget;
	s.checked = !s.checked;
	s.layerSelect.visible = s.checked;
};
LCheckBox.prototype.setChecked = function(value){
	var s=this;
	s.checked = value;
	s.layerSelect.visible = s.checked;
};
LCheckBox.prototype.clone = function(){
	var s = this,a = new LCheckBox();
	a.setChecked(s.checked);
	return a;
};
LCheckBox.prototype.toString = function(){
	return "[LCheckBox]";
};
function LComboBox(size,color,font,layer,layerUp,layerDown){
	var s = this;
	base(s,LSprite,[]);
	s.list = [];
	s.selectIndex = 0;
	s.value = null;
	s.selectWidth = 100;
	if(!size)size=16;
	if(!color)color = "black";
	if(!font)font = "黑体";
	s.size = size;
	s.color = color;
	s.font = font;
	s.refreshFlag = false;
	
	if(!layer){
		s.refreshFlag = true;
		layer = new LSprite();
		layerUp = new LSprite();
		layerDown = new LSprite();
		s.layer = layer;
		s.layerUp = layerUp;
		s.layerDown = layerDown;
		s.refresh();
	}
	s.addChild(layer);
	s.addChild(layerUp);
	s.addChild(layerDown);
	s.layer = layer;
	s.layerUp = layerUp;
	s.layerDown = layerDown;
	
	s.runing = false;
	
	s.textLayer = new LSprite();
	s.textLayer.x = 5;
	s._sy = s.size * 0.4;
	s.textLayer.y = s._sy;
	s.addChild(s.textLayer);
	s.layerUp.addEventListener(LMouseEvent.MOUSE_UP,s._onChangeUp);
	s.layerDown.addEventListener(LMouseEvent.MOUSE_UP,s._onChangeDown);
}
LComboBox.ON_CHANGE = "onchange";
LComboBox.prototype.refresh = function(){
	var s = this,k=null;

	for(var k=0,l=s.list.length;k<l;k++){
		s.textLayer.childList[k].visible = false;
		if(s.value == s.list[k].value)s.textLayer.childList[k].visible = true;
		if(s.selectWidth < s.textLayer.childList[k].getWidth() + s.size){
			s.selectWidth = s.textLayer.childList[k].getWidth() + s.size;
		}
	}
	
	s.layer.graphics.clear();
	s.layerUp.graphics.clear();
	s.layerDown.graphics.clear();
	s.layer.graphics.drawRect(2,"#000000",[0,0,s.selectWidth,s.size*2],true,"#D3D3D3");
	s.layerUp.x = s.selectWidth;
	s.layerUp.graphics.drawRect(2,"#000000",[0,0,s.size*2,s.size]);
	s.layerUp.graphics.drawVertices(2,"#000000",[[s.size*0.5*2,s.size*0.2],[s.size*0.2*2,s.size*0.8],[s.size*0.8*2,s.size*0.8]],true,"#000000");
	s.layerDown.x = s.selectWidth;
	s.layerDown.y = s.size;
	s.layerDown.graphics.drawRect(2,"#000000",[0,0,s.size*2,s.size]);
	s.layerDown.graphics.drawVertices(2,"#000000",[[s.size*0.5*2,s.size*0.8],[s.size*0.2*2,s.size*0.2],[s.size*0.8*2,s.size*0.2]],true,"#000000");
};
LComboBox.prototype.setChild = function(child){
	var s = this;
	if(!child || typeof child.value == UNDEFINED || typeof child.label == UNDEFINED){throw "the child must be an object like:{label:a,value:b}"};
	
	var text = new LTextField();
	text.size = s.size;
	text.color = s.color;
	text.font = s.font;
	text.text = child.label;
	text.y = (s.size * 1.5 >>> 0) * s.list.length;
	s.textLayer.addChild(text);
	if(s.list.length == 0){
		s.value = child.value;
	}
	s.list.push(child);
	s.selectWidth = 100;
	s.refresh();
	
};
LComboBox.prototype._onChangeDown = function(e){
	var b = e.clickTarget,s = b.parent;
	if(s.runing)return;
	if(s.selectIndex >= s.list.length - 1)return;
	s.runing = true;
	for(k in s.list){
		s.textLayer.childList[k].visible = true;
	}
	s.selectIndex++;
	s.value = s.list[s.selectIndex].value;
	var mask = new LSprite();
	mask.graphics.drawRect(2,"#000000",[0,0,s.selectWidth,s.size*2]);
	s.textLayer.mask = mask;
	var my = s.textLayer.y - (s.size * 1.5 >>> 0);
	var fun = function(layer){
		var s = layer.parent;
		layer.mask = null;
		s.runing = false;
		s.refresh();
		s.dispatchEvent(LComboBox.ON_CHANGE);
	};
	LTweenLite.to(s.textLayer,0.3,
	{ 
		y:my,
		onComplete:fun,
		ease:Strong.easeOut
	});
};
LComboBox.prototype._onChangeUp = function(e){
	var b = e.clickTarget,s = b.parent;
	if(s.runing)return;
	if(s.selectIndex <= 0)return;
	s.runing = true;
	for(k in s.list){
		s.textLayer.childList[k].visible = true;
	}
	s.selectIndex--;
	s.value = s.list[s.selectIndex].value;
	var mask = new LSprite();
	mask.graphics.drawRect(2,"#000000",[0,0,s.selectWidth,s.size*2]);
	s.textLayer.mask = mask;
	var my = s.textLayer.y + (s.size * 1.5 >>> 0);
	var fun = function(layer){
		var s = layer.parent;
		layer.mask = null;
		s.runing = false;
		s.refresh();
		s.dispatchEvent(LComboBox.ON_CHANGE);
	};
	LTweenLite.to(s.textLayer,0.3,
	{ 
		y:my,
		onComplete:fun,
		ease:Strong.easeOut
	});
};
LComboBox.prototype.setValue = function(value){
	var s = this,c=s.list;
	for(var i=0,l=c.length;i<l;i++){
		if(c[i].value == value){
			s.textLayer.y = s._sy-s.size * 1.5*i;
			s.selectIndex=i;
			s.value = s.list[s.selectIndex].value;
			s.refresh();
			break;
		}
	}
};
LComboBox.prototype.clone = function(){
	var s = this,a = new LComboBox(),k,c;
	for(k in s.list){
		c = s.list[k];
		a.setChild({label:c.label,value:c.value});
	}	
	a.setValue(s.value);
	return a;
};
LComboBox.prototype.toString = function(){
	return "[LComboBox]";
};
function LScrollbar(showObject,maskW,maskH,scrollWidth,wVisible){
	var s = this;
	base(s,LSprite,[]);
	s._showLayer = new LSprite();
	s._mask = new LGraphics();
	s._mask.drawRect(1,"#ffffff",[0,0,maskW,maskH],true,"#ffffff");
	s._showLayer.graphics.drawRect(1,"#ffffff",[0,0,maskW,maskH],true,"#ffffff");
	s._wVisible = typeof wVisible == UNDEFINED?true:wVisible;
	s.addChild(s._showLayer);
	s._width = 0;
	s._height = 0;
	s._showObject = showObject;
	s._showLayer.addChild(showObject);
	s._showObject.mask = s._mask;
	s._scrollWidth = scrollWidth?scrollWidth:20;
	s._tager = {x:0,y:0};
	s._maskW = maskW;
	s._maskH = maskH;
	s.addEventListener(LEvent.ENTER_FRAME,s.onFrame);
}
LScrollbar.prototype.clone = function(){
	var s = this,a = new LScrollbar(s._showObject.clone(),s._maskW,s._maskH,s._scrollWidth,s.wVisible);
	a.copyProperty(s);
	return a;
};
LScrollbar.prototype.onFrame = function(s){
	if(s._wVisible && s._width != s._showObject.getWidth()){
		s._width = s._showObject.getWidth();
		if(s._width > s._mask.getWidth()){
			s.resizeWidth(true);
			s.moveLeft();
		}else{
			s.resizeWidth(false);
		}
	}
	if(s._height != s._showObject.getHeight()){
		s._height = s._showObject.getHeight();
		if(s._height > s._mask.getHeight()){
			s.resizeHeight(true);
			s.moveUp();
		}else{
			s.resizeHeight(false);
		}
	}
	if(s._key == null)return;
	if(s._key["up"]){
		s.moveUp();
	}
	if(s._key["down"]){
		s.moveDown();
	}
	if(s._key["left"]){
		s.moveLeft();
	}
	if(s._key["right"]){
		s.moveRight();
	}
};

LScrollbar.prototype.resizeWidth = function(value){
	var s = this;
	if(!value){
		if(s._scroll_w != null){
			s._scroll_w.parent.removeChild(s._scroll_w);
			s._scroll_w_bar.parent.removeChild(s._scroll_w_bar);
			s._scroll_w = null;
			s._scroll_w_bar = null;
		}
		return;
	}
	var i;
	if(s._scroll_w_bar == null){
		if(s._key == null)s._key = [];
		s._scroll_w = new LSprite();
		s._scroll_w_bar = new LSprite();
		s.addChild(s._scroll_w);
		s.addChild(s._scroll_w_bar);
		var ny = s._scrollWidth*1.5;
		s._scroll_w.x = 0;
		s._scroll_w.y = s._mask.getHeight();
		s._scroll_w_bar.x = s._scrollWidth;
		s._scroll_w_bar.y = s._mask.getHeight();
		s._scroll_w_bar.graphics.drawRect(1,"#000000",[0,0,ny,s._scrollWidth],true,"#cccccc");
		s._scroll_w_bar.graphics.drawLine(1,"#000000",[ny*0.5,s._scrollWidth*0.25,ny*0.5,s._scrollWidth*0.75]);
		s._scroll_w_bar.graphics.drawLine(1,"#000000",[ny*0.5-3,s._scrollWidth*0.25,ny*0.5-3,s._scrollWidth*0.75]);
		s._scroll_w_bar.graphics.drawLine(1,"#000000",[ny*0.5+3,s._scrollWidth*0.25,ny*0.5+3,s._scrollWidth*0.75]);
		s._scroll_w.graphics.drawRect(1,"#000000",[0,0,s._mask.getWidth(),s._scrollWidth],true,"#292929");
		s._scroll_w.graphics.drawRect(1,"#000000",[0,0,s._scrollWidth,s._scrollWidth],true,"#ffffff");
		s._scroll_w.graphics.drawRect(1,"#000000",[s._mask.getWidth() - s._scrollWidth,0,s._scrollWidth,s._scrollWidth],true,"#ffffff");
		s._scroll_w.graphics.drawVertices(1,"#000000",[[s._scrollWidth*0.75,s._scrollWidth*0.25],
			[s._scrollWidth*0.75,s._scrollWidth*0.75],
			[s._scrollWidth*0.25,s._scrollWidth*0.5]],true,"#000000");
		s._scroll_w.graphics.drawVertices(1,"#000000",[[s._mask.getWidth() - s._scrollWidth*0.75,s._scrollWidth*0.25],
			[s._mask.getWidth() - s._scrollWidth*0.75,s._scrollWidth*0.75],
			[s._mask.getWidth() - s._scrollWidth*0.25,s._scrollWidth*0.5]],true,"#000000");
		s._scroll_w.graphics.drawRect(1,"#000000",[0,0,s._mask.getWidth(),s._scrollWidth]);
		s._scroll_w.graphics.drawRect(1,"#000000",[0,0,s._scrollWidth,s._scrollWidth]);
		s._scroll_w.graphics.drawRect(1,"#000000",[s._mask.getWidth() - s._scrollWidth,0,s._scrollWidth,s._scrollWidth]);
		var mouseDownHave = false;
		for(i=0;i<s.mouseList.length;i++){
 			if(s.mouseList[i][0] == LMouseEvent.MOUSE_DOWN){
				mouseDownHave = true;
  				break;
			}
		}
    		if(!mouseDownHave)s.addEventListener(LMouseEvent.MOUSE_DOWN,s.mouseDown);
	}
};
LScrollbar.prototype.resizeHeight = function(value){
	var s = this;
	if(!value){
		if(s._scroll_h != null){
			s._scroll_h.parent.removeChild(s._scroll_h);
			s._scroll_h_bar.parent.removeChild(s._scroll_h_bar);
			s._scroll_h = null;
			s._scroll_h_bar = null;
		}
		return;
	}
	var i;
	if(s._scroll_h_bar == null){
		if(s._key == null)s._key = [];
		s._scroll_h = new LSprite();
		s._scroll_h_bar = new LSprite();
		s.addChild(s._scroll_h);
		s.addChild(s._scroll_h_bar);
		var ny = s._scrollWidth*1.5;
		s._scroll_h.x = s._mask.getWidth();
		s._scroll_h.y = 0;
		s._scroll_h_bar.x = s._mask.getWidth();
		s._scroll_h_bar.y = s._scrollWidth;
		s._scroll_h_bar.graphics.drawRect(1,"#000000",[0,0,s._scrollWidth,s._scrollWidth*1.5],true,"#cccccc");
		s._scroll_h_bar.graphics.drawRect(1,"#000000",[0,0,s._scrollWidth,ny]);
		s._scroll_h_bar.graphics.drawLine(1,"#000000",[s._scrollWidth*0.25,ny*0.5,s._scrollWidth*0.75,ny*0.5]);
		s._scroll_h_bar.graphics.drawLine(1,"#000000",[s._scrollWidth*0.25,ny*0.5-3,s._scrollWidth*0.75,ny*0.5-3]);
		s._scroll_h_bar.graphics.drawLine(1,"#000000",[s._scrollWidth*0.25,ny*0.5+3,s._scrollWidth*0.75,ny*0.5+3]);
		s._scroll_h.graphics.drawRect(1,"#000000",[0,0,s._scrollWidth,s._mask.getHeight()],true,"#292929");
		s._scroll_h.graphics.drawRect(1,"#000000",[0,0,s._scrollWidth,s._scrollWidth],true,"#ffffff");
		s._scroll_h.graphics.drawRect(1,"#000000",[0,s._mask.getHeight() - s._scrollWidth,s._scrollWidth,s._scrollWidth],true,"#ffffff");
		s._scroll_h.graphics.drawVertices(1,"#000000",[[s._scrollWidth/4,s._scrollWidth*0.75],
			[s._scrollWidth/2,s._scrollWidth/4],
			[s._scrollWidth*0.75,s._scrollWidth*0.75]],true,"#000000");
		s._scroll_h.graphics.drawVertices(1,"#000000",[[s._scrollWidth/4,s._mask.getHeight() - s._scrollWidth*0.75],
			[s._scrollWidth/2,s._mask.getHeight() - s._scrollWidth*0.25],
			[s._scrollWidth*0.75,s._mask.getHeight() - s._scrollWidth*0.75]],true,"#000000");
		s._scroll_h.graphics.drawRect(1,"#000000",[0,0,s._scrollWidth,s._mask.getHeight()]);
		s._scroll_h.graphics.drawRect(1,"#000000",[0,0,0,0,s._scrollWidth,s._scrollWidth]);
		s._scroll_h.graphics.drawRect(1,"#000000",[0,s._mask.getHeight() - s._scrollWidth,s._scrollWidth,s._scrollWidth]);
		var mouseDownHave = false;
  		for(i=0;i<s.mouseList.length;i++){
      			if(s.mouseList[i][0] == LMouseEvent.MOUSE_DOWN){
				mouseDownHave = true;
			}
		}
		if(!mouseDownHave){
			s.addEventListener(LMouseEvent.MOUSE_DOWN,s.mouseDown);
		}
	}
};
LScrollbar.prototype.moveLeft = function(){
	var s = this;
	if(!s._key["Dkey"] && s._showObject.x >= s._tager.x){
		s._key["left"] = false;
		s.setScroll_w();
		return;
	}else if(s._showObject.x >= 0){
		s._showObject.x = 0;
		s._key["left"] = false;
		s.setScroll_w();
		return;
	}
	if(s._key["Dkey"])s._speed = 5;
	s._showObject.x += s._speed;
	s.setScroll_w();
	s.setSpeed();
};
LScrollbar.prototype.setScroll_h = function(){
	var s = this;
	var sy = (s._mask.getHeight() - s._scrollWidth*3.5)*s._showObject.y/(s._mask.getHeight() - s._showObject.getHeight());
	if(s._scroll_h_bar){
		s._scroll_h_bar.x = s._mask.getWidth();
		s._scroll_h_bar.y = s._scrollWidth + sy;
	}
};
LScrollbar.prototype.setScroll_w = function(){
	var s = this;
	var sx = (s._mask.getWidth() - s._scrollWidth*3.5)*s._showObject.x/(s._mask.getWidth() - s._showObject.getWidth());
	if(s._scroll_w_bar){
		s._scroll_w_bar.x = s._scrollWidth + sx;
		s._scroll_w_bar.y = s._mask.getHeight();
	}
};
LScrollbar.prototype.moveUp = function(){
	var s = this;
	if(!s._key["Dkey"] && s._showObject.y >= s._tager.y){
		s._key["up"] = false;
		s.setScroll_h();
		return;
	}else if(s._showObject.y >= 0){
		s._showObject.y = 0;
		s._key["up"] = false;
		s.setScroll_h();
		return;
	}
	if(s._key["Dkey"])s._speed = 5;
	s._showObject.y += s._speed;
	s.setScroll_h();
	s.setSpeed();
};
LScrollbar.prototype.moveDown = function(){
	var s = this;
	if(!s._key["Dkey"] && s._showObject.y <= s._tager.y){
		s._key["down"] = false;
		s.setScroll_h();
		return;
	}else if(s._showObject.y <= s._mask.getHeight() - s._showObject.getHeight()){
		s._showObject.y = s._mask.getHeight() - s._showObject.getHeight();
		s._key["down"] = false;
		s.setScroll_h();
		return;
	}
	if(s._key["Dkey"])s._speed = 5;
	s._showObject.y -= s._speed;
	s.setScroll_h();
	s.setSpeed();
};
LScrollbar.prototype.getScrollY = function(){
	return this._showObject.y;
};
LScrollbar.prototype.setScrollY = function(value){
	this._showObject.y = value;
	this.setScroll_h();
};
LScrollbar.prototype.getScrollX = function(){
	return this._showObject.x;
};
LScrollbar.prototype.setScrollX = function(value){
	this._showObject.x = value;
	this.setScroll_w();
};
LScrollbar.prototype.scrollToTop = function(){
	this._showObject.y = 0;
	this.setScroll_h();
};
LScrollbar.prototype.scrollToBottom = function(){
	var s = this;
	s._showObject.y = s._showObject.getHeight()>s._mask.getHeight()?s._mask.getHeight()-s._showObject.getHeight():0;
	s.setScroll_h();
};
LScrollbar.prototype.scrollToLeft = function(){
	this._showObject.x = 0;
	this.setScroll_w();
};
LScrollbar.prototype.scrollToRight = function(){
	var s = this;
	s._showObject.x = s._showObject.getWidth()>s._mask.getWidth()?s._mask.getWidth()-s._showObject.getWidth():0;
	s.setScroll_w();
};
LScrollbar.prototype.moveRight = function(){
	var s = this;
	if(!s._key["Dkey"] && s._showObject.x <= s._tager.x){
		s._key["right"] = false;
		s.setScroll_w();
		return;
	}else if(s._showObject.x <= s._mask.getWidth() - s._showObject.getWidth()){
		s._showObject.x = s._mask.getWidth() - s._showObject.getWidth();
		s._key["right"] = false;
		s.setScroll_w();
		return;
	}
	if(s._key["Dkey"])s._speed = 5;
	s._showObject.x -= s._speed;
	s.setScroll_w();
	s.setSpeed();
};
LScrollbar.prototype.mouseDown = function(event){
	var s = event.clickTarget;
	if(s._scroll_h != null && event.selfX >= s._scroll_h.x && event.selfX <= s._scroll_h.x + s._scrollWidth){
		s.mouseDownH(event,s);
	}
	if(s._scroll_w != null && event.selfY >= s._scroll_w.y && event.selfY <= s._scroll_w.y + s._scrollWidth){
		s.mouseDownW(event,s);
	}
};
LScrollbar.prototype.mouseMoveH = function(event){
	var s = event.clickTarget;
	if(event.selfY < s._scrollWidth || event.selfY > s._mask.getHeight())return;
	var mx = event.selfY - s._key["scroll_y"];
	s._key["up"] = false;
	s._key["down"] = false;
	s._tager.y = (s._mask.getHeight() - s._showObject.getHeight())*(mx - s._scrollWidth)/(s._mask.getHeight() - s._scrollWidth*3.5);
	if(s._tager.y > s._showObject.y){
		s._key["up"] = true;
	}else{
		s._key["down"] = true;
	}
	s._speed = Math.abs(s._tager.y - s._showObject.y);
	s.setSpeed();
};
LScrollbar.prototype.mouseUpH = function(event){
	var s = event.clickTarget;
	s.removeEventListener(LMouseEvent.MOUSE_UP,s.mouseUpH);
	if(s._key["Dkey"]){
		s._key["Dkey"] = false;
	}else{
		s.removeEventListener(LMouseEvent.MOUSE_MOVE,s.mouseMoveH);
		if(s._key["scroll_h"])s._key["scroll_h"] = false;
	}
};
LScrollbar.prototype.mouseUpW = function(event){
	var s = event.clickTarget;
	s.removeEventListener(LMouseEvent.MOUSE_UP,s.mouseUpW);
	if(s._key["Dkey"]){
		s._key["Dkey"] = false;
	}else{
		s.removeEventListener(LMouseEvent.MOUSE_MOVE,s.mouseMoveW);
		if(s._key["scroll_w"])s._key["scroll_w"] = false;
	}
};
LScrollbar.prototype.mouseMoveW = function(event){
	var s = event.clickTarget;
	if(event.selfX < s._scrollWidth || event.selfX > s._mask.getWidth())return;
	var my = event.selfX - s._key["scroll_x"];
	s._key["left"] = false;
	s._key["right"] = false;
	s._tager.x = (s._mask.getWidth()- s._showObject.getWidth())*(my - s._scrollWidth)/(s._mask.getWidth() - s._scrollWidth*3.5);
	if(s._tager.x > s._showObject.x){
		s._key["left"] = true;
	}else{
		s._key["right"] = true;
	}
	s._speed = Math.abs(s._tager.x - s._showObject.x);
	s.setSpeed();
};
LScrollbar.prototype.setSpeed = function(){
	var s = this;
	s._speed = Math.floor(s._speed/2);
	if(s._speed == 0)s._speed = 1;
};
LScrollbar.prototype.mouseDownW = function(event){
	var s = event.clickTarget;
	if(event.selfX >= 0 && event.selfX <= s._scrollWidth){
		if(s._showObject.x >= 0 || s._key["left"])return;
		s._distance = 10;
		if(s._showObject.x + s._distance > 0)s._distance = s._showObject.x;
		s._tager.x = s._showObject.x + s._distance;
		s._key["left"] = true;
		s._key["right"] = false;
		s._key["Dkey"] = true;
		s._speed = s._distance;
		s.setSpeed();
		s.addEventListener(LMouseEvent.MOUSE_UP,s.mouseUpW);
	}else if(event.selfX >= s._mask.getWidth() - s._scrollWidth && event.selfX <= s._mask.getWidth()){
		if(s._showObject.x <= s._mask.getWidth() - s._showObject.getWidth() || s._key["left"])return;
		s._distance = 10;
		if(s._showObject.x-s._distance<s._mask.getWidth()-s._showObject.getWidth())s._distance = s._showObject.x - s._mask.getWidth() + s._showObject.getWidth();
		s._tager.x = s._showObject.x - s._distance;
		s._key["right"] = true;
		s._key["left"] = false;
		s._key["Dkey"] = true;
		s._speed = this._distance;
		s.setSpeed();
		s.addEventListener(LMouseEvent.MOUSE_UP,s.mouseUpW);
	}else if(event.selfX >= s._scroll_w_bar.x && event.selfX <= s._scroll_w_bar.x + s._scroll_w_bar.getWidth() && !s._key["scroll_w"]){
		s._key["scroll_w"] = true;
		s._key["scroll_x"] = event.selfX - s._scroll_w_bar.x;
		s._key["mouseX"] = event.selfX;
       		s.addEventListener(LMouseEvent.MOUSE_MOVE,s.mouseMoveW);
		s.addEventListener(LMouseEvent.MOUSE_UP,s.mouseUpW);
	}else if(event.selfX > 0 && event.selfX < s._mask.getWidth()){
		s._key["left"] = false;
		s._key["right"] = false;
		s._tager.x = (s._mask.getWidth() - s._showObject.getWidth())*(event.selfX - s._scrollWidth)/(s._mask.getWidth() - s._scrollWidth*3.5);
		if(s._tager.x > s._showObject.x){
			s._key["left"] = true;
		}else{
			s._key["right"] = true;
		}
		s._speed = Math.abs(s._tager.x - s._showObject.x);
		s.setSpeed();
	}
};
LScrollbar.prototype.mouseDownH = function(event){
	var s = event.clickTarget;
	if(event.selfY >= 0 && event.selfY <= s._scrollWidth){
		if(s._showObject.y >= 0)return;
		s._distance = 10;
		if(s._showObject.y + s._distance > 0)s._distance = s._showObject.y;
		s._tager.y = s._showObject.y + s._distance;
		s._key["up"] = true;
		s._key["down"] = false;
		s._key["Dkey"] = true;
		s._speed = s._distance;
		s.setSpeed();
		s.addEventListener(LMouseEvent.MOUSE_UP,s.mouseUpH);
	}else if(event.selfY >= s._mask.getHeight() - s._scrollWidth && event.selfY <= s._mask.getHeight()){
		if(s._showObject.y <= s._mask.getHeight() - s._showObject.getHeight())return;
		s._distance = 10;
		if(s._showObject.y-s._distance<s._mask.getHeight()-s._showObject.getHeight())s._distance=s._showObject.y-s._mask.getHeight()+s._showObject.getHeight();
		s._tager.y = s._showObject.y - s._distance;
		s._key["down"] = true;
		s._key["up"] = false;
		s._key["Dkey"] = true;
		s._speed = s._distance;
		s.setSpeed();
		s.addEventListener(LMouseEvent.MOUSE_UP,s.mouseUpH);
	}else if(event.selfY >= s._scroll_h_bar.y && event.selfY <= s._scroll_h_bar.y + s._scroll_h_bar.getHeight() && !s._key["scroll_h"]){
		s._key["scroll_h"] = true;
		s._key["scroll_y"] = event.selfY - s._scroll_h_bar.y;
		s._key["mouseY"] = event.selfY;
		s.addEventListener(LMouseEvent.MOUSE_MOVE,s.mouseMoveH);
		s.addEventListener(LMouseEvent.MOUSE_UP,s.mouseUpH);
	}else if(event.selfY > 0 && event.selfY < s._mask.getHeight()){
		s._key["up"] = false;
		s._key["down"] = false;
		s._tager.y = (s._mask.getHeight() - s._showObject.getHeight())*(event.selfY - s._scrollWidth)/(s._mask.getHeight() - s._scrollWidth*3.5);
		if(s._tager.y > s._showObject.y){
			s._key["up"] = true;
		}else{
			s._key["down"] = true;
		}
		s._speed = Math.abs(s._tager.y - s._showObject.y);
		s.setSpeed();
	}
};
LScrollbar.prototype.toString = function(){
	return "[LScrollbar]";
};
function LWindow(width,height,title){
	var s = this;
	base(s,LSprite);
	s.w = width;
	s.h = height;
	s.bar = new LSprite();
	s.bar.alpha = 0.7;
	s.barColor = "#0000FF";
	s.bar.w = s.w;
	s.bar.h = 30;
	s.addChild(s.bar);
	s.bar.addEventListener(LMouseEvent.MOUSE_DOWN,s._onBarDown);
	s.title = new LTextField();
	s.title.x = s.title.y = 3;
	s.title.size = 16;
	s.title.text = title?title:"";
	s.bar.addChild(s.title);
	
	s.close = new LSprite();
	s.closeColor = "#800000";
	s.close.w = 50;
	s.close.h = 25;
	s.addChild(s.close);
	s.close.addEventListener(LMouseEvent.MOUSE_DOWN,s._onClose);
	s.sign = new LSprite();
	s.signColor = "#FFFFFF";
	s.addChild(s.sign);

	s.layer = new LSprite();
	s.addChild(s.layer);
	s.layerColor = "#FFFFFF";
	s.layer.y = s.bar.h;
	s.layer.h = s.h - s.bar.h;
	var g = new LGraphics();
	g.rect(0,0,s.w,s.layer.h);
	s.layer.mask = g;
	s.graphics.drawRect(1,s.barColor,[0,s.bar.h,s.w,s.layer.h],true,s.layerColor);

	s.addEventListener(LEvent.ENTER_FRAME,s._onDraw);
}
LWindow.CLOSE = "close";
LWindow.prototype.clone = function(){
	var s = this,a = new LWindow(s.w,s.h);
	a.copyProperty(s);
	a.removeChild(a.bar);
	a.bar = s.bar.clone();
	a.addChild(a.bar);
	a.removeChild(a.close);
	a.close = s.close.clone();
	a.addChild(a.close);
	a.removeChild(a.sign);
	a.sign = s.sign.clone();
	a.addChild(a.sign);
	a.removeChild(a.layer);
	a.layer = s.layer.clone();
	a.addChild(a.layer);
	a.bar.addEventListener(LMouseEvent.MOUSE_DOWN,a._onBarDown);
	a.close.addEventListener(LMouseEvent.MOUSE_DOWN,a._onClose);
	return a;
};
LWindow.prototype._onClose = function(event){
	var s = event.clickTarget.parent;
	s.dispatchEvent(LWindow.CLOSE);
	s.parent.removeChild(s);
};
LWindow.prototype._onDraw = function(event){
	var s = event.target;
	var co = s.getRootCoordinate();
	if(s.barColorSet == s.barColor)return;
	s.barColorSet = s.barColor;
	s.xSet = co.x;
	s.ySet = co.y;
	var barGrd=LGlobal.canvas.createLinearGradient(0,-s.bar.h*0.5,0,s.bar.h*2);
	barGrd.addColorStop(0,"white");
	barGrd.addColorStop(1,s.barColor);
	var closeGrd=LGlobal.canvas.createLinearGradient(0,-s.close.h*0.5,0,s.close.h*2);
	closeGrd.addColorStop(0,"white");
	closeGrd.addColorStop(1,s.closeColor);
	s.bar.graphics.clear();
	s.bar.graphics.drawRoundRect(1,s.barColor,[0,0,s.bar.w,s.bar.h,s.bar.h*0.1],true,barGrd);
	s.close.graphics.clear();
	s.close.graphics.drawRoundRect(1,s.closeColor,[s.w - s.close.w,0,s.close.w,s.close.h,s.close.h*0.1],true,closeGrd);
	s.sign.graphics.clear();
	s.sign.graphics.drawLine(4,s.signColor,[s.w - s.close.w + 15,5,s.w - 15,s.close.h-5]);
	s.sign.graphics.drawLine(4,s.signColor,[s.w - s.close.w + 15,s.close.h-5,s.w - 15,5]);
};
LWindow.prototype._onBarDown = function(event){
	var s = event.clickTarget.parent;
	s.bar.addEventListener(LMouseEvent.MOUSE_UP,s._onBarUp);
	s.startDrag();
};
LWindow.prototype._onBarUp = function(event){
	var s = event.clickTarget.parent;
	s.stopDrag();
	s.bar.removeEventListener(LMouseEvent.MOUSE_UP,s._onBarUp);
};
LWindow.prototype.toString = function(){
	return "[LWindow]";
};
function LRange(width){
	var s = this;
	base(s,LSprite);
	s.value = 0;
	s.w = width;
	var grd=LGlobal.canvas.createLinearGradient(0,0,0,s.w*0.13);
	grd.addColorStop(0,"white");
	grd.addColorStop(1,"#CCCCCC");
	s.color = grd;
	s.graphics.drawRect(0,s.color,[-50,0,s.w+100,s.w*0.13]);
	s.graphics.drawRect(1,"#CCCCCC",[0,s.w*0.04,s.w,s.w*0.03],true,s.color);
	s.sign = new LSprite();
	s.sign.graphics.drawVertices(1,"#CCCCCC",[[0,0],[s.w*0.05,0],[s.w*0.05,s.w*0.1],[s.w*0.025,s.w*0.13],[0,s.w*0.1]],true,s.color);
	s.addChild(s.sign);
	s.sign.x = -s.sign.getWidth()*0.5;
	s.addEventListener(LMouseEvent.MOUSE_DOWN,s._onDown);
}
LRange.prototype.clone = function(){
	var s = this,a = new LRange(s.w);
	a.copyProperty(s);
	return a;
};
LRange.prototype._onDown = function(event){
	var s = event.clickTarget;
	if(event.selfX < -s.sign.getWidth()*0.5 || event.selfX>s.w+s.sign.getWidth()*0.5)return;
	if(s.down)return;
	s.down = true;
	s.sign.x = event.selfX - s.sign.getWidth()*0.5;
	if(s.sign.x < -s.sign.getWidth()*0.5)s.sign.x = -s.sign.getWidth()*0.5;
	if(s.sign.x > s.w-s.sign.getWidth()*0.5)s.sign.x = s.w-s.sign.getWidth()*0.5;
	s._DownX = s.sign.x;
	s._OffsetX = event.selfX;
	s._getValue();
	s.addEventListener(LMouseEvent.MOUSE_MOVE,s._onMove);
	s.addEventListener(LMouseEvent.MOUSE_UP,s._onUp);
};
LRange.prototype._getValue = function(){
	var s = this;
	s.value = Math.floor((s.sign.x + s.sign.getWidth()*0.5)*100/s.w);
};
LRange.prototype._onMove = function(event){
	var s = event.clickTarget;
	s.sign.x = s._DownX + event.selfX - s._OffsetX;
	if(s.sign.x < -s.sign.getWidth()*0.5)s.sign.x = -s.sign.getWidth()*0.5;
	if(s.sign.x > s.w-s.sign.getWidth()*0.5)s.sign.x = s.w-s.sign.getWidth()*0.5;
	s._getValue();
};
LRange.prototype._onUp = function(event){
	var s = event.clickTarget;
	s.down = false;
	s.removeEventListener(LMouseEvent.MOUSE_MOVE,s._onMove);
	s.removeEventListener(LMouseEvent.MOUSE_UP,s._onUp);
};
LRange.prototype.toString = function(){
	return "[LRange]";
};
function LMenubar(list,style){
	var s = this;
	base(s,LSprite,[]);
	if(!style)style={};
	if(!style.textSize)style.textSize=20;
	if(!style.spaceHorizontal)style.spaceHorizontal=10;
	if(!style.spaceVertical)style.spaceVertical=5;
	if(!style.textColor)style.textColor="#000000";
	if(!style.lineColor)style.lineColor="#CCCCCC";
	if(!style.backgroundColor)style.backgroundColor="#FFFFFF";
	if(!style.itemBackgroundColor)style.itemBackgroundColor=style.backgroundColor;
	if(!style.selectColor)style.selectColor="#1E90FF";
	s.style = style;
	var back = new LSprite();
	back.graphics.drawRect(0,"#ffffff",[-LGlobal.width,-LGlobal.height,LGlobal.width*2,LGlobal.height*2]);
	s.addChild(back);
	s.back = back;
	s.back.root = s;
	s.back.mainMenu = true;
	s.back.background = true;
	s.back.addEventListener(LMouseEvent.MOUSE_UP,function(e){});
	s.back.addEventListener(LMouseEvent.MOUSE_MOVE,function(e){});
	s.back.addEventListener(LMouseEvent.MOUSE_DOWN,function(e){
		var root = e.clickTarget.root;
		for(var j=0;j<root.childList.length;j++){
			if(root.childList[j].mainMenu){
				if(root.childList[j].background)continue;
				var rW = root.childList[j].getWidth();
				var rH = root.childList[j].getHeight();
				root.childList[j].graphics.clear();
				root.childList[j].graphics.drawRect(0,root.style.lineColor,[0,0,rW,rH],true,root.style.backgroundColor);
				continue;
			}
			root.childList[j].visible = false;
		}
		root.open = false;
		setTimeout(function(){
			root.back.visible = false;
			root.dispatchEvent(LMenubar.MENU_CLOSE);
		},100);
	});
	s.back.visible = false;
	s.setList(s,list,0,0,0);
}
LMenubar.MENU_CLOSE = "menu_close";
LMenubar.prototype.openMainMenu = function(index){
	var self = this;
	self.mousedown({clickTarget:self.getChildAt(index+1)});
};
LMenubar.prototype.mousedown = function(e){
	var target = e.clickTarget;
	var root = target.root;
	if(target.mainMenu){
		if(root.open)return;
		root.open = true;
		root.back.visible = true;
		root.select = target;
		var sW = target.getWidth();
		var sH = target.getHeight();
		target.graphics.clear();
		target.graphics.drawRect(0,root.style.selectColor,[0,0,sW,sH],true,root.style.selectColor);

		if(target.menuList && target.menuList.length){
			for(var j=0;j<target.menuList.length;j++){
				target.menuList[j].visible = true;
				target.menuList[j].graphics.clear();
				target.menuList[j].graphics.drawRect(1,root.style.lineColor,[0,0,target.childWidth,target.childHeight],true,root.style.itemBackgroundColor);
				if(target.menuList[j].arrow){
					target.menuList[j].arrow.x = target.childWidth - root.style.spaceHorizontal*2;
				}
			}
		}
		return;
	}
	if(!target.menuList){
		if(target.click){
			target.click({target:root});
			root.open = false;
			setTimeout(function(){
				root.back.visible = false;
			},100);
		}
		for(var j=0;j<root.childList.length;j++){
			if(root.childList[j].mainMenu)continue;
			root.childList[j].visible = false;
		}
	}
};
LMenubar.prototype.mousemove = function(e){
	var target = e.clickTarget;
	var root = target.root;
	if(!root.open)return;
	if(root.select && root.select.objectIndex == target.objectIndex){
		return;
	}
	if(root.select){
		var rW = root.select.getWidth();
		var rH = root.select.getHeight();
		root.select.graphics.clear();
		root.select.graphics.drawRect(root.select.mainMenu ? 0 : 1,root.style.lineColor,[0,0,rW,rH],true,root.select.mainMenu?root.style.backgroundColor:root.style.itemBackgroundColor);
	}
	var sW = target.getWidth();
	var sH = target.getHeight();
	target.graphics.clear();
	target.graphics.drawRect(target.mainMenu ? 0 : 1,root.style.lineColor,[0,0,sW,sH],true,root.style.backgroundColor);
	target.graphics.drawRect(0,root.style.selectColor,[0,root.style.spaceVertical,sW,sH-root.style.spaceVertical*2],true,root.style.selectColor);
	if(target.mainMenu){
		for(var j=0;j<root.childList.length;j++){
			if(root.childList[j].mainMenu)continue;
			root.childList[j].visible = false;
		}
	}else if(root.select.depth == target.depth){
		if(root.select.menuList && root.select.menuList.length){
			for(var j=0;j<root.select.menuList.length;j++){
				root.select.menuList[j].visible = false;
			}
		}
	}else if(root.select.depth > target.depth){
		if(root.select.upper.menuList && root.select.upper.menuList.length){
			for(var j=0;j<root.select.upper.menuList.length;j++){
				root.select.upper.menuList[j].visible = false;
			}
		}
	}
	if(target.menuList && target.menuList.length){
		for(var j=0;j<target.menuList.length;j++){
			target.menuList[j].visible = true;
			target.menuList[j].graphics.clear();
			target.menuList[j].graphics.drawRect(1,root.style.lineColor,[0,0,target.childWidth,target.childHeight],true,target.menuList[j].mainMenu?root.style.backgroundColor:root.style.itemBackgroundColor);
			if(!target.mainMenu){
				target.menuList[j].x = target.x + target.getWidth();
			}
			if(target.menuList[j].arrow){
				target.menuList[j].arrow.x = target.childWidth - root.style.spaceHorizontal*2;
			}
		}
	}
	root.select = target;
};
LMenubar.prototype.mainMenuHide = function(value){
	var self = this;
	for(var j=0;j<self.childList.length;j++){
		if(self.childList[j].mainMenu){
			self.childList[j].visible = false;
		}
	}
};
LMenubar.prototype.setList = function(layer,list,depth,sx,sy){
	var s = this,w=0,h=0,menuList=[];
	layer.childWidth = 0;
	layer.childHeight = 0;
	for(var i=0;i<list.length;i++){
		var child = list[i];
		var menu = new LSprite();
		menu.depth = depth;
		menuList.push(menu);
		var label = new LTextField();
		menu.root = s;
		menu.upper = layer;
		menu.click = child.click;
		label.size = s.style.textSize;
		label.color = s.style.textColor;
		label.text = child.label;
		label.x = s.style.spaceHorizontal;
		label.y = s.style.spaceVertical;
		menu.addChild(label);
		menu.graphics.drawRect(0,s.style.backgroundColor,[0,0,label.getWidth()+s.style.textSize,label.getHeight()+s.style.textSize],true,s.style.backgroundColor);
		menu.addEventListener(LMouseEvent.MOUSE_DOWN,s.mousedown);
		menu.addEventListener(LMouseEvent.MOUSE_MOVE,s.mousemove);
		if(s.objectIndex == layer.objectIndex){
			menu.x = w + sx;
			menu.y = 0 + sy;
			menu.mainMenu = true;
			w += label.getWidth()+s.style.spaceHorizontal*2;
			h = label.getHeight()+s.style.spaceVertical*2;
			if(layer.childWidth < label.getWidth()+s.style.spaceHorizontal*2){
				layer.childWidth = label.getWidth()+s.style.spaceHorizontal*2;
			}
			if(layer.childHeight < label.getHeight()+s.style.spaceVertical*2){
				layer.childHeight = label.getHeight()+s.style.spaceVertical*2;
			}
		}else{
			menu.x = 0 + sx;
			menu.y = h + sy;
			w = w > label.getWidth()+s.style.spaceHorizontal*4 ? w : label.getWidth()+s.style.spaceHorizontal*4;
			h += label.getHeight()+s.style.spaceVertical*2;
			if(layer.childWidth < label.getWidth()+s.style.spaceHorizontal*4){
				layer.childWidth = label.getWidth()+s.style.spaceHorizontal*4;
			}
			if(layer.childHeight < label.getHeight()+s.style.spaceVertical*2){
				layer.childHeight = label.getHeight()+s.style.spaceVertical*2;
			}
		}
		s.addChild(menu);
		if(child.list && child.list.length > 0){
			if(s.objectIndex == layer.objectIndex){
				s.setList(menu,child.list,depth+1,menu.x,menu.y + menu.getHeight());
			}else{

				var arrow = new LSprite();
				menu.arrow = arrow;
				menu.addChild(arrow);
				arrow.x = label.getWidth()+s.style.spaceHorizontal*2;
				arrow.y = label.y;
				arrow.graphics.drawVertices(0,s.style.textColor,[[0,0],[0,label.getHeight()],[s.style.spaceHorizontal,label.getHeight()*0.5]],true,s.style.textColor);

				s.setList(menu,child.list,depth+1,menu.x+menu.getWidth()+s.style.spaceHorizontal*2,menu.y);
			}
		}
		if(s.objectIndex != layer.objectIndex){
			menu.visible = false;
		}
	}
	layer.menuList = menuList;
};
function LMessageBox(){}
LMessageBox.show = function(properties){
	if(!properties.width)properties.width = 500;
	if(!properties.height)properties.height = 300;
	if(!properties.title)properties.title = "";
	if(!properties.size)properties.size = 16;
	if(!properties.textHeight)properties.textHeight = 35;
	
	if(properties.displayObject){
		properties.width = properties.displayObject.getWidth();
		properties.height = properties.displayObject.getHeight();
	}
	var translucent = new LSprite();
	translucent.graphics.drawRect(0,"#000000",[0,0,LGlobal.width,LGlobal.height],true,"#000000");
	translucent.alpha = 0.5;
	LGlobal.stage.addChild(translucent);
	translucent.addEventListener(LMouseEvent.MOUSE_UP,function(e){});
	translucent.addEventListener(LMouseEvent.MOUSE_DOWN,function(e){});
	translucent.addEventListener(LMouseEvent.MOUSE_MOVE,function(e){});
	translucent.addEventListener(LMouseEvent.MOUSE_OVER,function(e){});
	translucent.addEventListener(LMouseEvent.MOUSE_OUT,function(e){});
	
	var myWindow = new LWindow(properties.width,properties.height,properties.title);
	myWindow.x = (LGlobal.width - myWindow.getWidth())*0.5;
	myWindow.y = (LGlobal.height - myWindow.getHeight())*0.5;
	LGlobal.stage.addChild(myWindow);
	
	myWindow.addEventListener(LWindow.CLOSE,function(e){
		translucent.die();
		translucent.remove();
	});			
	
	if(properties.displayObject){
		myWindow.layer.addChild(properties.displayObject);
		return;
	}
	var msgLabel = new LTextField();
	msgLabel.width = properties.width - 100;
	msgLabel.setWordWrap(true,properties.textHeight);
	msgLabel.text = properties.message;
	msgLabel.x = (properties.width - msgLabel.width)*0.5;
	msgLabel.y = (properties.height - myWindow.bar.getHeight() - msgLabel.getHeight())*0.5;
	myWindow.layer.addChild(msgLabel);
};