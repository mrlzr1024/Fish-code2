/*
 * @Author: your name
 * @Date: 2022-04-18 21:12:10
 * @LastEditTime: 2022-04-19 18:56:52
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \esp32cam-robot - B\esp32cam-robot\html.hpp
 */

#include "Arduino.h"

static const char PROGMEM INDEX_HTML[] = R"rawliteral(<!doctype html>
<html>

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width,initial-scale=1">
    <title>ESP32 CAM Robot</title>
    <style>
        body {
            font-family: Arial, Helvetica, sans-serif;
            background: #181818;
            color: #efefef;
            font-size: 16px;
        }

        h2 {
            font-size: 18px;
        }

        section.main {
            display: flex;
        }

        #menu,
        section.main {
            flex-direction: column;
        }

        #menu {
            display: none;
            flex-wrap: nowrap;
            min-width: 340px;
            background: #363636;
            padding: 8px;
            border-radius: 4px;
            margin-top: -10px;
            margin-right: 10px;
        }

        #content {
            display: flex;
            flex-wrap: wrap;
            align-items: stretch;
        }

        figure {
            padding: 0;
            margin: 0;
            -webkit-margin-before: 0;
            margin-block-start: 0;
            -webkit-margin-after: 0;
            margin-block-end: 0;
            -webkit-margin-start: 0;
            margin-inline-start: 0;
            -webkit-margin-end: 0;
            margin-inline-end: 0;
        }

        figure img {
            display: block;
            width: 100%;
            height: auto;
            border-radius: 4px;
            margin-top: 8px;
        }

        @media (min-width: 800px) and (orientation: landscape) {
            #content {
                display: flex;
                flex-wrap: nowrap;
                align-items: stretch;
            }

            figure img {
                display: block;
                max-width: 100%;
                max-height: calc(100vh - 40px);
                width: auto;
                height: auto;
            }

            figure {
                padding: 0;
                margin: 0;
                -webkit-margin-before: 0;
                margin-block-start: 0;
                -webkit-margin-after: 0;
                margin-block-end: 0;
                -webkit-margin-start: 0;
                margin-inline-start: 0;
                -webkit-margin-end: 0;
                margin-inline-end: 0;
            }
        }

        section #buttons {
            display: flex;
            flex-wrap: nowrap;
            justify-content: space-between;
        }

        #nav-toggle {
            cursor: pointer;
            display: block;
        }

        #nav-toggle-cb {
            outline: 0;
            opacity: 0;
            width: 0;
            height: 0;
        }

        #nav-toggle-cb:checked+#menu {
            display: flex;
        }

        .input-group {
            display: flex;
            flex-wrap: nowrap;
            line-height: 22px;
            margin: 5px 0;
        }

        .input-group>label {
            display: inline-block;
            padding-right: 10px;
            min-width: 47%;
        }

        .input-group input,
        .input-group select {
            flex-grow: 1;
        }

        .range-max,
        .range-min {
            display: inline-block;
            padding: 0 5px;
        }

        .contest {
            /*这是定义图像位置的类*/
            position: relative;
            /*绝对位置*/
            top: 5px;
            /*顶距=50px*/
            left: 40%;
            /*左距=50%整个页面，用px也行*/
            /* margin-right: -50%; */
            /*右边距*/
            /* transform: translate(-50%, -50%); */
            /*定义 2D 转换，沿着 X 和 Y 轴移动元素*/
            /* min-width: 300px; */
            /*最小宽度*/
        }

        button {
            display: block;
            margin: 5px;
            padding: 5px 12px;
            border: 0;
            line-height: 28px;
            cursor: pointer;
            color: rgb(156, 211, 231);
            background: #035806;
            border-radius: 5px;
            font-size: 8px;
            outline: 0;
            width: 50px;

        }

        .button2 {
            background-color: #154504;
            width: 50px;
        }

        /* Blue */
        .button3 {
            background-color: #f44336;
            width: 100px;
        }

        /* Red */
        .button4 {
            background-color: #e7e7e7;
            color: black;
            width: 120px;
        }

        /* Gray */
        .button5 {
            background-color: #555555;
            width: 100px;
        }

        /* Black */
        .button6 {
            visibility: hidden;
            width: 100px;
        }

        /* Black */


        button:hover {
            background: #ff494d;
        }

        button:active {
            background: #f21c21;
        }

        button.disabled {
            cursor: default;
            background: #a0a0a0;
        }

        input[type="range"] {
            -webkit-appearance: none;
            width: 100%;
            height: 22px;
            background: #363636;
            cursor: pointer;
            margin: 0;
        }

        input[type="range"]:focus {
            outline: 0;
        }

        input[type="range"]::-webkit-slider-runnable-track {
            width: 100%;
            height: 2px;
            cursor: pointer;
            background: #efefef;
            border-radius: 0;
            border: 0 solid #efefef;
        }

        input[type="range"]::-webkit-slider-thumb {
            border: 1px solid rgba(0, 0, 30, 0);
            height: 22px;
            width: 22px;
            border-radius: 50px;
            background: #ff3034;
            cursor: pointer;
            -webkit-appearance: none;
            margin-top: -11.5px;
        }

        input[type="range"]:focus::-webkit-slider-runnable-track {
            background: #efefef;
        }

        input[type="range"]::-moz-range-track {
            width: 100%;
            height: 2px;
            cursor: pointer;
            background: #efefef;
            border-radius: 0;
            border: 0 solid #efefef;
        }

        input[type="range"]::-moz-range-thumb {
            border: 1px solid rgba(0, 0, 30, 0);
            height: 22px;
            width: 22px;
            border-radius: 50px;
            background: #ff3034;
            cursor: pointer;
        }

        input[type="range"]::-ms-track {
            width: 100%;
            height: 2px;
            cursor: pointer;
            background: 0 0;
            border-color: transparent;
            color: transparent;
        }

        input[type="range"]::-ms-fill-lower {
            background: #efefef;
            border: 0 solid #efefef;
            border-radius: 0;
        }

        input[type="range"]::-ms-fill-upper {
            background: #efefef;
            border: 0 solid #efefef;
            border-radius: 0;
        }

        input[type="range"]::-ms-thumb {
            border: 1px solid rgba(0, 0, 30, 0);
            height: 22px;
            width: 22px;
            border-radius: 50px;
            background: #ff3034;
            cursor: pointer;
            height: 2px;
        }

        input[type="range"]:focus::-ms-fill-lower {
            background: #efefef;
        }

        input[type="range"]:focus::-ms-fill-upper {
            background: #363636;
        }

        .switch {
            display: block;
            position: relative;
            line-height: 22px;
            font-size: 16px;
            height: 22px;
        }

        .switch input {
            outline: 0;
            opacity: 0;
            width: 0;
            height: 0;
        }

        .slider {
            width: 50px;
            height: 22px;
            border-radius: 22px;
            cursor: pointer;
            background-color: grey;
        }

        .slider,
        .slider:before {
            display: inline-block;
            transition: 0.4s;
        }

        .slider:before {
            position: relative;
            content: "";
            border-radius: 50%;
            height: 16px;
            width: 16px;
            left: 4px;
            top: 3px;
            background-color: #fff;
        }

        input:checked+.slider {
            background-color: #ff3034;
        }

        input:checked+.slider:before {
            -webkit-transform: translateX(26px);
            transform: translateX(26px);
        }

        select {
            border: 1px solid #363636;
            font-size: 14px;
            height: 22px;
            outline: 0;
            border-radius: 5px;
        }

        .image-container {
            /*这是定义图像位置的类*/
            position: absolute;
            /*绝对位置*/
            top: 50%;
            /*顶距=50px*/
            left: 60%;
            /*左距=50%整个页面，用px也行*/
            /* margin-right: -50%; */
            /*右边距*/
            transform: translate(-50%, -50%);
            /*定义 2D 转换，沿着 X 和 Y 轴移动元素*/
            min-width: 300px;
            /*最小宽度*/
        }

        .control-container {
            position: relative;
            top: 450px;
            left: 30%;
            margin-right: -50%;
            transform: translate(-50%, -50%);


        }

        .slider-container {
            /*这是配置滑块位置的类*/
            position: relative;
            /*相对位置*/
            top: 320px;
            right: 10%;
            margin-left: 30%;
            /* transform: translate(-50%, -50%) */
        }

        .close {
            position: absolute;
            right: 5px;
            top: 5px;
            background: #ff3034;
            width: 16px;
            height: 16px;
            border-radius: 100px;
            color: #fff;
            text-align: center;
            line-height: 18px;
            cursor: pointer;
        }

        .hidden {
            display: none;
        }

        .rotate90 {
            -webkit-transform: rotate(270deg);
            -moz-transform: rotate(270deg);
            -o-transform: rotate(270deg);
            -ms-transform: rotate(270deg);
            transform: rotate(270deg);
        }
    </style>
</head>

<body>
    <section id="buttons">

        <div id="controls" class="contest">
            <table>
                <!-- <tr>
                    <td align="center"><button class="button button6" id="get-still">Image</button></td>
                    <td align="center"><button id="toggle-stream">视频流</button></td>
                    <td></td>
                </tr> -->
                <tr>
                    <td></td>
                    <td align="center"><button class="button button2" id="forward"
                            onclick="fetch(document.location.origin+'/control?var=car&val=1');">前进</button></td>
                    <td></td>
                </tr>
                <tr>
                    <td align="center"><button class="button button2" id="turnleft"
                            onclick="fetch(document.location.origin+'/control?var=car&val=4');">向左</button></td>
                            <td align="center"><button class="button button2" id="flash"
                                onclick="fetch(document.location.origin+'/control?var=car&val=3');">复位</button></td>
                        <td></td>
                    <td align="center"><button class="button button2" id="turnright"
                            onclick="fetch(document.location.origin+'/control?var=car&val=2');">向右</button></td>
                </tr>
                <tr>
                    <td></td>
                    <td align="center"><button class="button button2" id="backward"
                            onclick="fetch(document.location.origin+'/control?var=car&val=5');">后台</button></td>
                    <td></td>
                </tr>

                <!--     <td align="center"><button class="button button2" id="flash"
                        onclick="fetch(document.location.origin+'/control?var=flash&val=1');">开灯</button></td>
                <td></td>
                </tr>
                <tr>
                    <td align="center"><button class="button button2" id="flashoff"
                            onclick="fetch(document.location.origin+'/control?var=flashoff&val=0');">关灯</button></td>
                    <td></td>
                </tr>      -->

            </table>
        </div>
        <br>
        <div id="sliders" class="slider-container">
            <table>
                <tr>
                    <td>俗度:</td>
                    <td align="center" colspan="2"><input type="range" id="speed" min="0" max="255" value="200"
                            onchange="try{fetch(document.location.origin+'/control?var=speed&val='+this.value);}catch(e){}">
                    </td>
                </tr>
                <tr>
                    <td>质量:</td>
                    <td align="center" colspan="2"><input type="range" id="quality" min="10" max="63" value="10"
                            onchange="try{fetch(document.location.origin+'/control?var=quality&val='+this.value);}catch(e){}">
                    </td>
                </tr>
                <tr>
                    <td>大小:</td>
                    <td align="center" colspan="2"><input type="range" id="framesize" min="0" max="6" value="5"
                            onchange="try{fetch(document.location.origin+'/control?var=framesize&val='+this.value);}catch(e){}">
                    </td>
                </tr>
                <tr>
                    <td align="center"><button class="button button6" id="get-still">Image</button></td>
                    <td align="center"><button id="toggle-stream">视频流</button></td>
                    <td></td>
                </tr>

            </table>
        </div>
    </section>
    <section class="main">
        <figure>
            <div id="stream-container" class="image-container">
                <div class="close" id="close-stream">x</div>
                <img id="stream" src="">
            </div>
        </figure>
    </section>
    <script>
        document.addEventListener('DOMContentLoaded', function () { function b(B) { let C; switch (B.type) { case 'checkbox': C = B.checked ? 1 : 0; break; case 'range': case 'select-one': C = B.value; break; case 'button': case 'submit': C = '1'; break; default: return; }const D = `${c}/control?var=${B.id}&val=${C}`; fetch(D).then(E => { console.log(`request to ${D} finished, status: ${E.status}`) }) } var c = document.location.origin; const e = B => { B.classList.add('hidden') }, f = B => { B.classList.remove('hidden') }, g = B => { B.classList.add('disabled'), B.disabled = !0 }, h = B => { B.classList.remove('disabled'), B.disabled = !1 }, i = (B, C, D) => { D = !(null != D) || D; let E; 'checkbox' === B.type ? (E = B.checked, C = !!C, B.checked = C) : (E = B.value, B.value = C), D && E !== C ? b(B) : !D && ('aec' === B.id ? C ? e(v) : f(v) : 'agc' === B.id ? C ? (f(t), e(s)) : (e(t), f(s)) : 'awb_gain' === B.id ? C ? f(x) : e(x) : 'face_recognize' === B.id && (C ? h(n) : g(n))) }; document.querySelectorAll('.close').forEach(B => { B.onclick = () => { e(B.parentNode) } }), fetch(`${c}/status`).then(function (B) { return B.json() }).then(function (B) { document.querySelectorAll('.default-action').forEach(C => { i(C, B[C.id], !1) }) }); const j = document.getElementById('stream'), k = document.getElementById('stream-container'), l = document.getElementById('get-still'), m = document.getElementById('toggle-stream'), n = document.getElementById('face_enroll'), o = document.getElementById('close-stream'), p = () => { window.stop(), m.innerHTML = 'Start' }, q = () => { j.src = `${c + ':81'}/stream`, f(k), m.innerHTML = 'Stop' }; l.onclick = () => { p(), j.src = `${c}/capture?_cb=${Date.now()}`, f(k) }, o.onclick = () => { p(), e(k) }, m.onclick = () => { const B = 'Stop' === m.innerHTML; B ? p() : q() }, n.onclick = () => { b(n) }, document.querySelectorAll('.default-action').forEach(B => { B.onchange = () => b(B) }); const r = document.getElementById('agc'), s = document.getElementById('agc_gain-group'), t = document.getElementById('gainceiling-group'); r.onchange = () => { b(r), r.checked ? (f(t), e(s)) : (e(t), f(s)) }; const u = document.getElementById('aec'), v = document.getElementById('aec_value-group'); u.onchange = () => { b(u), u.checked ? e(v) : f(v) }; const w = document.getElementById('awb_gain'), x = document.getElementById('wb_mode-group'); w.onchange = () => { b(w), w.checked ? f(x) : e(x) }; const y = document.getElementById('face_detect'), z = document.getElementById('face_recognize'), A = document.getElementById('framesize'); A.onchange = () => { b(A), 5 < A.value && (i(y, !1), i(z, !1)) }, y.onchange = () => { return 5 < A.value ? (alert('Please select CIF or lower resolution before enabling this feature!'), void i(y, !1)) : void (b(y), !y.checked && (g(n), i(z, !1))) }, z.onchange = () => { return 5 < A.value ? (alert('Please select CIF or lower resolution before enabling this feature!'), void i(z, !1)) : void (b(z), z.checked ? (h(n), i(y, !0)) : g(n)) } });
    </script>
</body>

</html>
)rawliteral";
