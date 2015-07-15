onload = function(){
    var c = document.getElementById('canvas');
    c.width = 500;
    c.height = 300;

    var gl = c.getContext('webgl') || c.getContext('experimental-webgl');
    
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clearDepth(1.0);  
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    var v_shader = create_shader('vs');  
    var f_shader = create_shader('fs'); 
    
    var prg = create_program(v_shader, f_shader);  
    // attributeLocation�Ļ�ȡ  
    var attLocation = gl.getAttribLocation(prg, 'position'); 
    // attribute��Ԫ������(���ֻʹ�� xyz ��������3)  
    var attStride = 3;  
    // ģ�ͣ����㣩����  
    var vertex_position = [  
         0.0, 1.0, 0.0,  
         1.0, 0.0, 0.0,  
        -1.0, 0.0, 0.0  
    ];  
    
     // ����VBO  
    var vbo = create_vbo(vertex_position);  
    // ��VBO  
    gl.bindBuffer(gl.ARRAY_BUFFER, vbo);  
    // �趨attribute�����Є�  
    gl.enableVertexAttribArray(attLocation);  
    // ���attribute����  
    gl.vertexAttribPointer(attLocation, attStride, gl.FLOAT, false, 0, 0);  
    
    // matIV��������  
    var m = new matIV();  
    // ���־�������ɺͳ�ʼ��  
    var mMatrix = m.identity(m.create());  
    var vMatrix = m.identity(m.create());  
    var pMatrix = m.identity(m.create());  
    var mvpMatrix = m.identity(m.create());  
    // ��ͼ�任�������  
    m.lookAt([0.0, 1.0, 3.0], [0, 0, 0], [0, 1, 0], vMatrix);  
    // ͶӰ����任����  
    m.perspective(90, c.width / c.height, 0.1, 100, pMatrix);  
    // ��������ɣ��õ����յ�����任����  
    m.multiply(pMatrix, vMatrix, mvpMatrix);  
    m.multiply(mvpMatrix, mMatrix, mvpMatrix);  
    
    // uniformLocation�Ļ�ȡ  
    var uniLocation = gl.getUniformLocation(prg, 'mvpMatrix');  
    // ��uniformLocation�д�������任����  
    gl.uniformMatrix4fv(uniLocation, false, mvpMatrix);  
    // ����ģ��  
    gl.drawArrays(gl.TRIANGLES, 0, 3);  
    // context��ˢ��  
    gl.flush();  
    
    
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
};

