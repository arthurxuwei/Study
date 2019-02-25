onload = function(){
    var c = document.getElementById('canvas');
    c.width = 500;
    c.height = 300;

    var gl = c.getContext('webgl') || c.getContext('experimental-webgl');
    
    // gl.clearColor(0.0, 0.0, 0.0, 1.0);
    // gl.clearDepth(1.0);  
    // gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    var v_shader = create_shader('vs');  
    var f_shader = create_shader('fs'); 
    
    var prg = create_program(v_shader, f_shader);  
    // attributeLocation的获取
    var attLocation = new Array(2);  
    attLocation[0] = gl.getAttribLocation(prg, 'position');
    attLocation[1] = gl.getAttribLocation(prg, 'color');
    attLocation[2] = gl.getAttribLocation(prg, 'textureCoord');
    // attribute的元素数量
    var attStride = new Array(2); 
    attStride[0] = 3;
    attStride[1] = 4;
    attStride[2] = 2;
    
    var box_position = [  
         0.0,  1.0,  0.0,  
         1.0,  0.0,  0.0,  
        -1.0,  0.0,  0.0,  
         0.0, -1.0,  0.0  
    ];
    var box_color = [  
        1.0, 0.0, 0.0, 1.0,  
        0.0, 1.0, 0.0, 1.0,  
        0.0, 0.0, 1.0, 1.0,  
        1.0, 1.0, 1.0, 1.0  
    ];
    var textureCoord = [
        0.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 1.0
    ];
    // 保存顶点的索引的数组  
    var index = [  
        0, 1, 2,  
        3, 2, 1  
    ];  
    var box_pos_vbo = create_vbo(box_position);  
    var box_col_vbo = create_vbo(box_color);  
    var vTextureCoord = create_vbo(textureCoord);
    var VBOList       = [box_pos_vbo, box_col_vbo, vTextureCoord];
    var ibo = create_ibo(index);  
    // IBO进行绑定并添加  
    set_attribute(VBOList, attLocation, attStride);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, ibo);
    
    // uniformLocation的获取  
    var uniLocation = new Array();
    uniLocation[0]  = gl.getUniformLocation(prg, 'mvpMatrix')
    uniLocation[1]  = gl.getUniformLocation(prg, 'texture');
    // matIV对象生成  
    var m = new matIV();  
    // 各种矩阵的生成和初始化  
    var mMatrix = m.identity(m.create());  
    var vMatrix = m.identity(m.create());  
    var pMatrix = m.identity(m.create());  
    var tmpMatrix = m.identity(m.create());
    var mvpMatrix = m.identity(m.create());  
    // 视图变换坐标矩阵  
    m.lookAt([0.0, 0.0, 3.0], [0, 0, 0], [0, 1, 0], vMatrix);  
    // 投影坐标变换矩阵  
    m.perspective(90, c.width / c.height, 0.1, 100, pMatrix);  
    // 各矩阵相乘，得到最终的坐标变换矩阵  
    m.multiply(pMatrix, vMatrix, tmpMatrix);  
    gl.enable(gl.CULL_FACE);
    gl.frontFace(gl.CW);
    gl.enable(gl.DEPTH_TEST);
    
    gl.activeTexture(gl.TEXTURE0);
    var texture = null;
    create_texture('texture_.png');
    
    var count = 0;
    (function(){
        
        
        gl.clearColor(0.0, 0.0, 0.0, 1.0);
        gl.clearDepth(1.0);
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        
        count++;
        
        var rad = (count % 360) * Math.PI / 180;
        var x = Math.cos(rad);
        var z = Math.sin(rad);
        gl.bindTexture(gl.TEXTURE_2D, texture);
        
        m.identity(mMatrix);
        m.translate(mMatrix, [x, 0.0, z], mMatrix);
        m.rotate(mMatrix, rad, [1, 0, 0], mMatrix);
        m.multiply(tmpMatrix, mMatrix, mvpMatrix);
        gl.uniformMatrix4fv(uniLocation[0], false, mvpMatrix);
        gl.drawElements(gl.TRIANGLES, index.length, gl.UNSIGNED_SHORT, 0);
        
        m.identity(mMatrix);
        m.translate(mMatrix, [-x, 0.0, -z], mMatrix);
        m.rotate(mMatrix, rad, [0, 1, 0], mMatrix);
        m.multiply(tmpMatrix, mMatrix, mvpMatrix);
        gl.uniformMatrix4fv(uniLocation[0], false, mvpMatrix);
        gl.drawElements(gl.TRIANGLES, index.length, gl.UNSIGNED_SHORT, 0);
        
        gl.flush();
        setTimeout(arguments.callee, 1000/30);
    })();

    
    
    function create_shader(id){
        // 用来保存着色器的变量
        var shader;
        // 根据id从HTML中获取指定的script标签
        var scriptElement = document.getElementById(id);
        // 如果指定的script标签不存在，则返回
        if(!scriptElement){return;}
        // 判断script标签的type属性
        switch(scriptElement.type){
            // 顶点着色器的时候
            case 'x-shader/x-vertex':
                shader = gl.createShader(gl.VERTEX_SHADER);
                break;
            // 片段着色器的时候
            case 'x-shader/x-fragment':
                shader = gl.createShader(gl.FRAGMENT_SHADER);
                break;
            default :
                return;
        }
        // 将标签中的代码分配给生成的着色器
        gl.shaderSource(shader, scriptElement.text);
        // 编译着色器
        gl.compileShader(shader);
        // 判断一下着色器是否编译成功
        if(gl.getShaderParameter(shader, gl.COMPILE_STATUS)){
            // 编译成功，则返回着色器
            return shader;
        }else{
            // 编译失败，弹出错误消息
            alert(gl.getShaderInfoLog(shader));
        }
    }

    function create_program(vs, fs){
        // 程序对象的生成
        var program = gl.createProgram();
        // 向程序对象里分配着色器
        gl.attachShader(program, vs);
        gl.attachShader(program, fs);
        // 将着色器连接
        gl.linkProgram(program);
        // 判断着色器的连接是否成功
        if(gl.getProgramParameter(program, gl.LINK_STATUS)){
            // 成功的话，将程序对象设置为有效
            gl.useProgram(program);
            // 返回程序对象
            return program;
        }else{
            // 如果失败，弹出错误信息
            alert(gl.getProgramInfoLog(program));
        }
    }

    function create_vbo(data){
        // 生成缓存对象
        var vbo = gl.createBuffer();
        // 绑定缓存
        gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
        // 向缓存中写入数据
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(data), gl.STATIC_DRAW);
        // 将绑定的缓存设为无效
        gl.bindBuffer(gl.ARRAY_BUFFER, null);
        // 返回生成的VBO
        return vbo;
    }
    
    // IBO的生成函数
    function create_ibo(data){
        // 生成缓存对象
        var ibo = gl.createBuffer();
        // 绑定缓存
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, ibo);
        // 向缓存中写入数据
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Int16Array(data), gl.STATIC_DRAW);
        // 将缓存的绑定无效化
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
        // 返回生成的IBO
        return ibo;
    }
    
    // 绑定VBO相关的函数  
    function set_attribute(vbo, attL, attS){  
    // 处理从参数中得到的数组  
        for(var i in vbo){  
            // 绑定缓存  
            gl.bindBuffer(gl.ARRAY_BUFFER, vbo[i]);  
            // 将attributeLocation设置为有效  
            gl.enableVertexAttribArray(attL[i]);  
            //通知并添加attributeLocation  
            gl.vertexAttribPointer(attL[i], attS[i], gl.FLOAT, false, 0, 0);  
        }  
    } 
    function create_texture(source){
        var img = new Image();
        img.onload = function(){
            var tex = gl.createTexture();
            gl.bindTexture(gl.TEXTURE_2D, tex);
            gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, img);
            gl.generateMipmap(gl.TEXTURE_2D);
            gl.bindTexture(gl.TEXTURE_2D, null);
            texture = tex;
        };
        img.src = source;
    }
};

