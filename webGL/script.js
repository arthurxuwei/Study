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
    // attributeLocation�Ļ�ȡ
    var attLocation = new Array(2);  
    attLocation[0] = gl.getAttribLocation(prg, 'position');
    attLocation[1] = gl.getAttribLocation(prg, 'color');
    
    // attribute��Ԫ������
    var attStride = new Array(2); 
    attStride[0] = 3;
    attStride[1] = 4;
 
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
    // ���涥�������������  
    var index = [  
        0, 1, 2,  
        1, 2, 3  
    ];  
    var box_pos_vbo = create_vbo(box_position);  
    var box_col_vbo = create_vbo(box_color);  
       
    set_attribute([box_pos_vbo, box_col_vbo], attLocation, attStride); 
    var ibo = create_ibo(index);  
    // IBO���а󶨲����  
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, ibo); 
    
    // uniformLocation�Ļ�ȡ  
    var uniLocation = gl.getUniformLocation(prg, 'mvpMatrix'); 
    // matIV��������  
    var m = new matIV();  
    // ���־�������ɺͳ�ʼ��  
    var mMatrix = m.identity(m.create());  
    var vMatrix = m.identity(m.create());  
    var pMatrix = m.identity(m.create());  
    var tmpMatrix = m.identity(m.create());
    var mvpMatrix = m.identity(m.create());  
    // ��ͼ�任�������  
    m.lookAt([0.0, 0.0, 3.0], [0, 0, 0], [0, 1, 0], vMatrix);  
    // ͶӰ����任����  
    m.perspective(90, c.width / c.height, 0.1, 100, pMatrix);  
    // ��������ˣ��õ����յ�����任����  
    m.multiply(pMatrix, vMatrix, tmpMatrix);  
    
    var count = 0;
    (function(){
        gl.enable(gl.CULL_FACE);
        gl.frontFace(gl.CW);
        gl.enable(gl.DEPTH_TEST);
        
        gl.clearColor(0.0, 0.0, 0.0, 1.0);
        gl.clearDepth(1.0);
        gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        
        count++;
        
        var rad = (count % 360) * Math.PI / 180;
        var x = Math.cos(rad);
        var z = Math.sin(rad);

        m.identity(mMatrix);
        m.translate(mMatrix, [x, 0.0, z], mMatrix);
        m.rotate(mMatrix, rad, [1, 0, 0], mMatrix);
        m.multiply(tmpMatrix, mMatrix, mvpMatrix);
        gl.uniformMatrix4fv(uniLocation, false, mvpMatrix);
        gl.drawElements(gl.TRIANGLES, index.length, gl.UNSIGNED_SHORT, 0);
        
        m.identity(mMatrix);
        m.translate(mMatrix, [-x, 0.0, -z], mMatrix);
        m.rotate(mMatrix, rad, [0, 1, 0], mMatrix);
        m.multiply(tmpMatrix, mMatrix, mvpMatrix);
        gl.uniformMatrix4fv(uniLocation, false, mvpMatrix);
        gl.drawElements(gl.TRIANGLES, index.length, gl.UNSIGNED_SHORT, 0);
        
        gl.flush();
        setTimeout(arguments.callee, 1000/30);
    })();

    
    
    function create_shader(id){
        // ����������ɫ���ı���
        var shader;
        // ����id��HTML�л�ȡָ����script��ǩ
        var scriptElement = document.getElementById(id);
        // ���ָ����script��ǩ�����ڣ��򷵻�
        if(!scriptElement){return;}
        // �ж�script��ǩ��type����
        switch(scriptElement.type){
            // ������ɫ����ʱ��
            case 'x-shader/x-vertex':
                shader = gl.createShader(gl.VERTEX_SHADER);
                break;
            // Ƭ����ɫ����ʱ��
            case 'x-shader/x-fragment':
                shader = gl.createShader(gl.FRAGMENT_SHADER);
                break;
            default :
                return;
        }
        // ����ǩ�еĴ����������ɵ���ɫ��
        gl.shaderSource(shader, scriptElement.text);
        // ������ɫ��
        gl.compileShader(shader);
        // �ж�һ����ɫ���Ƿ����ɹ�
        if(gl.getShaderParameter(shader, gl.COMPILE_STATUS)){
            // ����ɹ����򷵻���ɫ��
            return shader;
        }else{
            // ����ʧ�ܣ�����������Ϣ
            alert(gl.getShaderInfoLog(shader));
        }
    }

    function create_program(vs, fs){
        // ������������
        var program = gl.createProgram();
        // ���������������ɫ��
        gl.attachShader(program, vs);
        gl.attachShader(program, fs);
        // ����ɫ������
        gl.linkProgram(program);
        // �ж���ɫ���������Ƿ�ɹ�
        if(gl.getProgramParameter(program, gl.LINK_STATUS)){
            // �ɹ��Ļ����������������Ϊ��Ч
            gl.useProgram(program);
            // ���س������
            return program;
        }else{
            // ���ʧ�ܣ�����������Ϣ
            alert(gl.getProgramInfoLog(program));
        }
    }

    function create_vbo(data){
        // ���ɻ������
        var vbo = gl.createBuffer();
        // �󶨻���
        gl.bindBuffer(gl.ARRAY_BUFFER, vbo);
        // �򻺴���д������
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(data), gl.STATIC_DRAW);
        // ���󶨵Ļ�����Ϊ��Ч
        gl.bindBuffer(gl.ARRAY_BUFFER, null);
        // �������ɵ�VBO
        return vbo;
    }
    
    // IBO�����ɺ���
    function create_ibo(data){
        // ���ɻ������
        var ibo = gl.createBuffer();
        // �󶨻���
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, ibo);
        // �򻺴���д������
        gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Int16Array(data), gl.STATIC_DRAW);
        // ������İ���Ч��
        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
        // �������ɵ�IBO
        return ibo;
    }
    
    // ��VBO��صĺ���  
    function set_attribute(vbo, attL, attS){  
    // ����Ӳ����еõ�������  
        for(var i in vbo){  
            // �󶨻���  
            gl.bindBuffer(gl.ARRAY_BUFFER, vbo[i]);  
            // ��attributeLocation����Ϊ��Ч  
            gl.enableVertexAttribArray(attL[i]);  
            //֪ͨ�����attributeLocation  
            gl.vertexAttribPointer(attL[i], attS[i], gl.FLOAT, false, 0, 0);  
        }  
    } 
};

