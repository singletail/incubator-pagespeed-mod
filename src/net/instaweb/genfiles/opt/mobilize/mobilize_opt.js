(function(){var n,q=this;
function aa(a){var b=typeof a;if("object"==b)if(a){if(a instanceof Array)return"array";if(a instanceof Object)return b;var c=Object.prototype.toString.call(a);if("[object Window]"==c)return"object";if("[object Array]"==c||"number"==typeof a.length&&"undefined"!=typeof a.splice&&"undefined"!=typeof a.propertyIsEnumerable&&!a.propertyIsEnumerable("splice"))return"array";if("[object Function]"==c||"undefined"!=typeof a.call&&"undefined"!=typeof a.propertyIsEnumerable&&!a.propertyIsEnumerable("call"))return"function"}else return"null";else if("function"==
b&&"undefined"==typeof a.call)return"object";return b}function r(a){return"string"==typeof a}function t(a){var b=typeof a;return"object"==b&&null!=a||"function"==b}function ba(a,b,c){return a.call.apply(a.bind,arguments)}function ca(a,b,c){if(!a)throw Error();if(2<arguments.length){var d=Array.prototype.slice.call(arguments,2);return function(){var c=Array.prototype.slice.call(arguments);Array.prototype.unshift.apply(c,d);return a.apply(b,c)}}return function(){return a.apply(b,arguments)}}
function v(a,b,c){v=Function.prototype.bind&&-1!=Function.prototype.bind.toString().indexOf("native code")?ba:ca;return v.apply(null,arguments)}function w(a,b){var c=a.split("."),d=q;c[0]in d||!d.execScript||d.execScript("var "+c[0]);for(var e;c.length&&(e=c.shift());)c.length||void 0===b?d=d[e]?d[e]:d[e]={}:d[e]=b};var da=String.prototype.trim?function(a){return a.trim()}:function(a){return a.replace(/^[\s\xa0]+|[\s\xa0]+$/g,"")};function x(a,b){return-1!=a.toLowerCase().indexOf(b.toLowerCase())}function y(a,b){return a<b?-1:a>b?1:0};var z;a:{var ea=q.navigator;if(ea){var fa=ea.userAgent;if(fa){z=fa;break a}}z=""};var A=Array.prototype,ga=A.indexOf?function(a,b,c){return A.indexOf.call(a,b,c)}:function(a,b,c){c=null==c?0:0>c?Math.max(0,a.length+c):c;if(r(a))return r(b)&&1==b.length?a.indexOf(b,c):-1;for(;c<a.length;c++)if(c in a&&a[c]===b)return c;return-1},ha=A.filter?function(a,b,c){return A.filter.call(a,b,c)}:function(a,b,c){for(var d=a.length,e=[],g=0,f=r(a)?a.split(""):a,k=0;k<d;k++)if(k in f){var h=f[k];b.call(c,h,k,a)&&(e[g++]=h)}return e};function ia(a){return A.concat.apply(A,arguments)}
function ja(a){return A.concat.apply(A,arguments)};function ka(a,b,c){var d=0,e=0,g=0;if(0==b)g=e=d=c;else{var f=Math.floor(a/60),k=a/60-f;a=c*(1-b);var h=c*(1-b*k);b=c*(1-b*(1-k));switch(f){case 1:d=h;e=c;g=a;break;case 2:d=a;e=c;g=b;break;case 3:d=a;e=h;g=c;break;case 4:d=b;e=a;g=c;break;case 5:d=c;e=a;g=h;break;case 6:case 0:d=c,e=b,g=a}}return[Math.floor(d),Math.floor(e),Math.floor(g)]}
function B(a,b,c){var d=Math.max(Math.max(a,b),c),e=Math.min(Math.min(a,b),c);if(e==d)e=a=0;else{var g=d-e,e=g/d;a=60*(a==d?(b-c)/g:b==d?2+(c-a)/g:4+(a-b)/g);0>a&&(a+=360);360<a&&(a-=360)}return[a,e,d]};function C(a,b,c,d){this.top=a;this.right=b;this.bottom=c;this.left=d}n=C.prototype;n.clone=function(){return new C(this.top,this.right,this.bottom,this.left)};n.toString=function(){return"("+this.top+"t, "+this.right+"r, "+this.bottom+"b, "+this.left+"l)"};n.contains=function(a){return this&&a?a instanceof C?a.left>=this.left&&a.right<=this.right&&a.top>=this.top&&a.bottom<=this.bottom:a.x>=this.left&&a.x<=this.right&&a.y>=this.top&&a.y<=this.bottom:!1};
n.expand=function(a,b,c,d){t(a)?(this.top-=a.top,this.right+=a.right,this.bottom+=a.bottom,this.left-=a.left):(this.top-=a,this.right+=b,this.bottom+=c,this.left-=d);return this};n.ceil=function(){this.top=Math.ceil(this.top);this.right=Math.ceil(this.right);this.bottom=Math.ceil(this.bottom);this.left=Math.ceil(this.left);return this};n.floor=function(){this.top=Math.floor(this.top);this.right=Math.floor(this.right);this.bottom=Math.floor(this.bottom);this.left=Math.floor(this.left);return this};
n.round=function(){this.top=Math.round(this.top);this.right=Math.round(this.right);this.bottom=Math.round(this.bottom);this.left=Math.round(this.left);return this};n.translate=function(a,b){this.left+=a;this.right+=a;"number"==typeof b&&(this.top+=b,this.bottom+=b);return this};n.scale=function(a,b){var c="number"==typeof b?b:a;this.left*=a;this.right*=a;this.top*=c;this.bottom*=c;return this};var la=-1!=z.indexOf("Opera")||-1!=z.indexOf("OPR"),D=-1!=z.indexOf("Trident")||-1!=z.indexOf("MSIE"),E=-1!=z.indexOf("Gecko")&&!x(z,"WebKit")&&!(-1!=z.indexOf("Trident")||-1!=z.indexOf("MSIE")),ma=x(z,"WebKit");function na(){var a=q.document;return a?a.documentMode:void 0}
var oa=function(){var a="",b;if(la&&q.opera)return a=q.opera.version,"function"==aa(a)?a():a;E?b=/rv\:([^\);]+)(\)|;)/:D?b=/\b(?:MSIE|rv)[: ]([^\);]+)(\)|;)/:ma&&(b=/WebKit\/(\S+)/);b&&(a=(a=b.exec(z))?a[1]:"");return D&&(b=na(),b>parseFloat(a))?String(b):a}(),pa={};
function qa(a){if(!pa[a]){for(var b=0,c=da(String(oa)).split("."),d=da(String(a)).split("."),e=Math.max(c.length,d.length),g=0;0==b&&g<e;g++){var f=c[g]||"",k=d[g]||"",h=RegExp("(\\d*)(\\D*)","g"),l=RegExp("(\\d*)(\\D*)","g");do{var m=h.exec(f)||["","",""],p=l.exec(k)||["","",""];if(0==m[0].length&&0==p[0].length)break;b=y(0==m[1].length?0:parseInt(m[1],10),0==p[1].length?0:parseInt(p[1],10))||y(0==m[2].length,0==p[2].length)||y(m[2],p[2])}while(0==b)}pa[a]=0<=b}}
var ra=q.document,sa=ra&&D?na()||("CSS1Compat"==ra.compatMode?parseInt(oa,10):5):void 0;function ta(a){if(a.classList)return a.classList;a=a.className;return r(a)&&a.match(/\S+/g)||[]}function F(a,b){var c;a.classList?c=a.classList.contains(b):(c=ta(a),c=0<=ga(c,b));return c}function G(a,b){a.classList?a.classList.add(b):F(a,b)||(a.className+=0<a.className.length?" "+b:b)}function ua(a,b){a.classList?a.classList.remove(b):F(a,b)&&(a.className=ha(ta(a),function(a){return a!=b}).join(" "))}function H(a,b){F(a,b)?ua(a,b):G(a,b)};var va;if(!(va=!E&&!D)){var wa;if(wa=D)wa=D&&9<=sa;va=wa}va||E&&qa("1.9.1");D&&qa("9");function xa(){this.height=this.width=this.bottom=this.right=this.left=this.top=0}function ya(a){var b=null;a&&(b=a.indexOf("px"),-1!=b&&(a=a.substring(0,b)),b=parseInt(a,10),isNaN(b)&&(b=null));return b}function I(a,b){var c=null;a&&(c=ya(a.getPropertyValue(b)));return c}function J(a,b){a.style&&a.style.removeProperty(b);a.removeAttribute(b)}function za(a,b){var c=null;a.style&&(c=ya(a.style.getPropertyValue(b)));null==c&&(c=ya(a.getAttribute(b)));return c}
function K(a,b,c){a.style.setProperty(b,c,"important")}function Aa(a,b){if(b&&0!=b.length){var c=a.getAttribute("style")||"";0<c.length&&";"!=c[c.length-1]&&(c+=";");a.setAttribute("style",c+b)}}function Ba(a){a=a.getBoundingClientRect();var b=document.body,c=document.documentElement||b.parentNode||b,b="pageXOffset"in window?window.pageXOffset:c.scrollLeft,c="pageYOffset"in window?window.pageYOffset:c.scrollTop;return new C(a.top+c,a.right+b,a.bottom+c,a.left+b)}
function L(a){var b=null;"SCRIPT"!=a.tagName&&"STYLE"!=a.tagName&&a.style&&(a=window.getComputedStyle(a))&&(b=a.getPropertyValue("background-image"),"none"==b&&(b=null),b&&5<b.length&&0==b.indexOf("url(")&&")"==b[b.length-1]&&(b=b.substring(4,b.length-1)));return b}function Ca(){if(null!=window.parent&&window!=window.parent)try{if(window.parent.document.domain==document.domain)return!0}catch(a){}return!1}function Da(a){var b=1;for(a=a.firstChild;a;a=a.nextSibling)b+=Da(a);return b}
function M(a){return t(a)&&1==a.nodeType?a:null}var N={ma:"IMG",na:"SVG",la:"background-image"};w("pagespeed.MobUtil.ImageSource",N);function Ea(a,b,c){this.q=a;this.O=b;this.ga=c}function Fa(a){for(var b="#",c=0,d=a.length;c<d;++c){var e=Math.round(a[c]);0>e?e=0:255<e&&(e=255);e=e.toString(16);1==e.length&&(e="0"+e);b+=e}return b}function O(a){a=a.toLowerCase();for(var b="",c=0,d=a.length;c<d;++c){var e=a.charAt(c);if("a"<=e&&"z">=e||"0"<=e&&"9">=e)b+=e}return b}
function Ga(a){if(!a)return"";if(!Ha(a))return a;var b=document.domain,c;c=b.length;for(var d=0;2>d;++d){var e=b.lastIndexOf(".",c-1);if(0<=e)c=e;else break}c=0<=e?b.substring(0,c):b;d=null;0==c.indexOf("www.")&&0>a.indexOf("//www.")&&(e=c.substring(4),d=a.indexOf(e),0<=d&&(a=a.substring(0,d)+c+a.substring(d+e.length)));if(!Ha(a))return a;d=a.indexOf(c);0<=d&&(a=a.substring(0,d)+b+a.substring(d+c.length,a.length));return a}
function P(a,b){var c=null;switch(b){case "IMG":a.tagName==b&&(c=a.src);break;case "SVG":a.tagName==b&&(c=(new XMLSerializer).serializeToString(a),c=(self.URL||self.webkitURL||self).createObjectURL(new Blob([c],{type:"image/svg+xml;charset=utf-8"})));break;case "background-image":c=L(a)}return c?Ga(c):null}function Ha(a){return 0!=a.lastIndexOf(document.location.origin+"/",0)&&0!=a.lastIndexOf("data:image/",0)}
function Ia(a){a=Ba(a);var b=new xa;b.top=a.top;b.bottom=a.bottom;b.left=a.left;b.right=a.right;b.height=a.bottom-a.top;b.width=a.right-a.left;return b};function Q(){this.t=0;this.l=this.p=null}Q.prototype.D=1E-10;Q.prototype.m=3;function Ja(a,b){this.background=a;this.M=b}function Ka(a,b){if(3!=a.length||3!=b.length)return Infinity;var c=a[0]-b[0],d=a[1]-b[1],e=a[2]-b[2];return Math.sqrt(c*c+d*d+e*e)}function R(a){a/=255;return a=.03928>=a?a/12.92:Math.pow((a+.055)/1.055,2.4)}
function La(a,b){var c=b.background,d=b.M,e=.2126*R(c[0])+.7152*R(c[1])+.0722*R(c[2]),g=.2126*R(d[0])+.7152*R(d[1])+.0722*R(d[2]);if(e<a.D&&g<a.D)return b;e=g/e;1>e&&(e=1/e);if(e>a.m)return b;c=B(c[0],c[1],c[2]);d=B(d[0],d[1],d[2]);g=e=null;c[2]<d[2]?(e=c[2],g=d[2]):(e=d[2],g=c[2]);var f=(a.m*e-g)/(a.m+1),e=e>f?e-f:0,g=g<1-2*f?g+2*f:255;c[2]<d[2]?(c[2]=e,d[2]=g):(d[2]=e,c[2]=g);c=ka(c[0],c[1],c[2]);d=ka(d[0],d[1],d[2]);return new Ja(c,d)}
function Ma(a,b,c,d,e){var g=[],f,k,h;for(k=0;k<e;++k)for(f=0;f<d;++f){var l=4*(k*d+f);h=3*(k*d+f);var m=b[l+3]/255,p=1-m;g[h]=m*b[l]+p*c[0];g[h+1]=m*b[l+1]+p*c[1];g[h+2]=m*b[l+2]+p*c[2]}l=[0,0,0];for(f=m=k=0;f<d;++f)h=3*((e-1)*d+f),l[0]+=g[h],l[1]+=g[h+1],l[2]+=g[h+2],m+=b[h+3],++k;if(m>127.5*k)for(f=0;3>f;++f)l[f]/=k;else l=c;b=Math.floor(.25*d);c=Math.floor(.75*d);m=Math.floor(.25*e);e=Math.floor(.75*e);var p=0,u=[];for(k=m;k<=e;++k)for(f=b;f<=c;++f)h=3*(k*d+f),u[p]=Ka(g.slice(h,h+3),l),++p;f=
u.sort(function(a,b){return a-b});var gb=Math.max(1,f[Math.floor(.75*p)]),p=0,u=[0,0,0];for(k=m;k<=e;++k)for(f=b;f<=c;++f)h=3*(k*d+f),Ka(g.slice(h,h+3),l)>=gb&&(u[0]+=g[h],u[1]+=g[h+1],u[2]+=g[h+2],++p);if(0<p)for(f=0;3>f;++f)u[f]=Math.floor(u[f]/p);return La(a,new Ja(l,u))}
Q.prototype.w=function(){--this.t;if(!(0<this.t)){var a=[255,255,255],b=[0,0,0],c=this.p;this.l&&this.l.data&&c&&c.c&&c.backgroundColor?(b=Ma(this,this.l.data,c.backgroundColor,c.c.width,c.c.height),a=b.background,b=b.M):c&&c.backgroundColor&&(a=c.backgroundColor,b=178.5<B(a[0],a[1],a[2])[2]?[0,0,0]:[255,255,255]);console.log("Theme color. Background: "+a+" foreground: "+b);this.J(this.p,Fa(a),Fa(b))}};
function Na(a,b,c){var d=new Image;d.onload=v(function(){var a=document.createElement("canvas"),b=null,f=null;c&&0<c.width&&0<c.height?(b=c.width,f=c.height):(b=d.naturalWidth,f=d.naturalHeight);a.width=b;a.height=f;a=a.getContext("2d");a.drawImage(d,0,0);this.l=a.getImageData(0,0,b,f);this.w()},a);d.onerror=v(a.w,a);d.src=b}
Q.prototype.run=function(a,b){this.p=a;this.J&&alert("A callback which was supposed to run after extracting theme color  was not executed.");this.J=b;a&&a.d&&!Ha(a.d)?(this.t=1,Na(this,a.d,a.c),console.log("Found logo. Theme color will be computed from logo.")):(a&&a.d?console.log("Found logo but its origin is different that of HTML. Use default color."):console.log("Could not find logo. Use default color."),this.w())};function S(a){this.v=a;this.K={};if(a=document.documentElement.clientWidth)for(var b=window.getComputedStyle(document.body),c=["padding-left","padding-right"],d=0;d<c.length;++d){var e=I(b,c[d]);e&&(a-=e)}else a=400;this.b=a;console.log("window.pagespeed.MobLayout.maxWidth="+this.b)}
var Oa="padding-left padding-bottom padding-right padding-top margin-left margin-bottom margin-right margin-top border-left-width border-bottom-width border-right-width border-top-width left top".split(" "),Pa={A:!0,DIV:!0,FORM:!0,H1:!0,H2:!0,H3:!0,H4:!0,P:!0,SPAN:!0,TBODY:!0,TD:!0,TFOOT:!0,TH:!0,THEAD:!0,TR:!0},Qa=["left","width"];
function Ra(a,b){if(!b)return!0;var c=b.tagName.toUpperCase();return"SCRIPT"==c||"STYLE"==c||"IFRAME"==c||b.id&&a.K[b.id]||b.classList.contains("psmob-nav-panel")||b.classList.contains("psmob-header-bar")||b.classList.contains("psmob-header-spacer-div")||b.classList.contains("psmob-logo-span")}function T(a,b){var c=M(b);return Ra(a,c)?null:c}function U(a){var b=[];for(a=a.firstChild;a;a=a.nextSibling)null!=M(a)&&b.push(a);return b}
function Sa(a,b,c){for(b=b.firstChild;b;b=b.nextSibling)null!=T(a,b)&&c.call(a,b)}n=S.prototype;
n.T=function(a){var b=window.getComputedStyle(a),c=L(a);if(c&&(c=this.v.i[c])&&c.width&&c.height&&"none"==b.getPropertyValue("background-position")){var d=c.height;if(c.width>this.b){var d=Math.round(this.b/c.width*c.height),e="background-size:"+this.b+"px "+d+"px;background-repeat:no-repeat;",g=I(b,"height");c.height==g&&(e+="height:"+d+"px;");Aa(a,e)}K(a,"min-height",""+d+"px")}if("PRE"==a.tagName.toUpperCase()||"pre"==b.getPropertyValue("white-space")&&a.offsetWidth>this.b)a.style.overflowX="scroll";
Sa(this,a,this.T)};function Ta(a){K(a,"overflow-x","auto");K(a,"width","auto");K(a,"display","block")}n.ja=function(a){Ua(this,a,0)};
function Ua(a,b,c){var d;if(d=Ba(b))c=d.top,d=d.bottom;else{if(b.offsetParent==b.parentNode)c+=b.offsetTop;else if(b.offsetParent!=b.parentNode.parentNode)return null;d=c+b.offsetHeight-1}if(Ra(a,b))return d;d=c-1;var e=window.getComputedStyle(b);if(!e)return null;var g=I(e,"min-height");null!=g&&(d+=g);for(var g=c+b.offsetHeight-1,f=!1,k=!1,h,l=b.firstChild;l;l=l.nextSibling)if(h=M(l)){var m=window.getComputedStyle(h);m&&"absolute"==m.position&&"0px"!=m.getPropertyValue("height")&&"hidden"!=m.getPropertyValue("visibility")&&
(k=!0);h=Ua(a,h,c);null!=h&&(f=!0,d=Math.max(d,h))}if("fixed"==e.getPropertyValue("position")&&f)return null;a=b.tagName.toUpperCase();"BODY"!=a&&(e=g-c+1,f?d!=g&&(k?K(b,"height",""+(d-c+1)+"px"):K(b,"height","auto")):("IMG"!=a&&0<e&&""==b.style.backgroundSize&&(J(b,"height"),K(b,"height","auto"),b.offsetHeight&&(g=c+b.offsetHeight)),d=g));return d}
n.S=function(a){for(var b=U(a),c=0;c<b.length;++c)this.S(b[c]);if(!(a.offsetWidth<=this.b))if(b=a.tagName.toUpperCase(),"TABLE"==b){a:{b=0;for(c=a.firstChild;c;c=c.nextSibling)for(var d=c.firstChild;d;d=d.nextSibling){var e=c.tagName.toUpperCase();if("THEAD"==e||"TFOOT"==e){b=!0;break a}for(e=d.firstChild;e;e=e.nextSibling){if(e.tagName&&"TH"==e.tagName.toUpperCase()){b=!0;break a}++b}}b=3*Va(this,a)>b?!1:!0}if(b)Ta(a);else if("CSS1Compat"!==document.compatMode){var g,f,k,h=document.createElement("DIV");
h.style.display="inline-block";for(var l=U(a),b=0;b<l.length;++b)for(var m=U(l[b]),c=0;c<m.length;++c)for(var p=U(m[c]),d=0;d<p.length;++d)if(f=p[d],1==f.childNodes.length)g=f.childNodes[0],f.removeChild(g),h.appendChild(g);else if(1<f.childNodes.length){k=document.createElement("DIV");k.style.display="inline-block";for(var u=U(f),e=0;e<u.length;++e)g=u[e],f.removeChild(g),k.appendChild(g);h.appendChild(k)}a.parentNode.replaceChild(h,a)}else for(J(a,"width"),K(a,"max-width","100%"),a=a.firstChild;a;a=
a.nextSibling)if(b=M(a),null!=b)for(J(b,"width"),K(b,"max-width","100%"),b=b.firstChild;b;b=b.nextSibling)if(c=M(b),null!=c&&"TR"==c.tagName.toUpperCase())for(J(c,"width"),K(c,"max-width","100%"),c=c.firstChild;c;c=c.nextSibling)d=M(c),null!=d&&"TD"==d.tagName.toUpperCase()&&(K(d,"max-width","100%"),K(d,"display","inline-block"))}else{c=null;d=a.offsetWidth;e=a.offsetHeight;g="img";if("IMG"==b)c=a.getAttribute("src");else if(g="background-image",c=L(a),f=null==c?null:this.v.i[c])d=f.width,e=f.height;
null!=c?(f=d/this.b,1<f&&(f=e/f,console.log("Shrinking "+g+" "+c+" from "+d+"x"+e+" to "+this.b+"x"+f),"IMG"==b?(K(a,"width",""+this.b+"px"),K(a,"height",""+f+"px")):K(a,"background-size",""+this.b+"px "+f+"px"))):"CODE"==b||"PRE"==b||"UL"==b?Ta(a):Pa[b]?(K(a,"max-width","100%"),J(a,"width")):console.log("Punting on resize of "+b+" which wants to be "+a.offsetWidth+" but this.maxWidth_="+this.b)}};
function Va(a,b){var c=0,d=b.tagName.toUpperCase();"DIV"!=d&&"TABLE"!=d&&"UL"!=d||++c;for(d=b.firstChild;d;d=d.nextSibling){var e=M(d);null!=e&&(c+=Va(a,e))}return c}n.da=function(a){var b=document.body.style.display;document.body.style.display="none";this.H(a);document.body.style.display=b};
n.H=function(a){var b=window.getComputedStyle(a);"nowrap"==b.getPropertyValue("white-space")&&K(a,"white-space","normal");Sa(this,a,this.H);var b=window.getComputedStyle(a),c,d,e;for(c=0;c<Qa.length;++c)d=Qa[c],(e=b.getPropertyValue(d))&&"100%"!=e&&"auto"!=e&&0<e.length&&"%"==e[e.length-1]&&K(a,d,"auto");c=a.tagName.toUpperCase();var g="UL"==c||"OL"==c,f="BODY"==c,k=!1,h="";for(c=0;c<Oa.length;++c){d=Oa[c];if(e=g)e=d.length-5,e=0<=e&&d.indexOf("-left",e)==e;e||f&&0==d.lastIndexOf("margin-",0)||(e=
I(b,d),null!=e&&(4<e?h+=d+":4px !important;":0>e&&(k=!0,"margin-bottom"==d&&(k=-30<e),k?h+=d+":0px !important;":a.setAttribute("data-pagespeed-negative-bottom-margin","1"))))}Aa(a,h)};
n.R=function(a){Sa(this,a,this.R);if("IMG"==a.tagName.toUpperCase()){var b=window.getComputedStyle(a),c=za(a,"width"),d=za(a,"height");if(c&&d&&b){var e=I(b,"width"),b=I(b,"height");if(e&&b&&(e/=c,b/=d,.95<(e>b?b/e:e/b)||(console.log("aspect ratio problem for "+a.getAttribute("src")),1==a.naturalHeight&&1==a.naturalWidth?(b=Math.min(e,b),J(a,"width"),J(a,"height"),a.style.width=c*b,a.style.height=d*b):e>b?J(a,"height"):(J(a,"width"),J(a,"height"),a.style.maxHeight=d)),.25>e)){for(console.log("overshrinkage for "+
a.getAttribute("src"));a&&a.tagName&&"TD"!=a.tagName.toUpperCase();)a=a.parentNode;if(a&&(c=a.parentNode)){d=0;for(a=c.firstChild;a;a=a.nextSibling)a.tagName&&"TD"==a.tagName.toUpperCase()&&++d;if(1<d)for(d="width:"+Math.round(100/d)+"%;",c=c.firstChild;c;c=c.nextSibling)a=M(c),null!=a&&"TD"==a.tagName.toUpperCase()&&Aa(a,d)}}}}};
n.U=function(a){var b=window.getComputedStyle(a).getPropertyValue("position");if("fixed"==b)return"fixed";var c,d,e,g,f=[];c=null;var k,h=[],l=!1;for(d=a.firstChild;d;d=d.nextSibling)if(e=T(this,d),null!=e&&(g=this.U(e),"fixed"!=g&&null!=T(this,e)))if("absolute"==g)h.push(e);else{var m=window.getComputedStyle(e);g=m.getPropertyValue("float");var p="right"==g;k="inline-block";if(p||"left"==g)p&&"right"==m.getPropertyValue("clear")&&(p=!1,k="block",c&&l&&K(c,"margin-bottom","0px")),K(e,"float","none"),
"none"!=m.getPropertyValue("display")&&K(e,"display",k);p&&f.push(e);c=e;e=I(m,"margin-bottom");l=null!=e&&0>e}for(c=f.length-1;0<=c;--c)d=f[c],a.removeChild(d);for(c=f.length-1;0<=c;--c)d=f[c],a.appendChild(d);return b};
n.L=function(a){if("fixed"!=window.getComputedStyle(a).getPropertyValue("position")){var b,c,d,e=[],g=[];for(c=a.firstChild;c;c=c.nextSibling)if(d=T(this,c),null!=d){b=window.getComputedStyle(d);var f=b.getPropertyValue("position");"fixed"!=f&&"absolute"!=f&&0!=c.offsetWidth&&(e.push(d),g.push(b))}var k=null;for(c=0;c<e.length;++c)d=e[c],b=c<e.length-1?e[c+1]:null,f=d.offsetLeft+d.offsetWidth,(null==k||d.offsetLeft<k)&&(null==b||b.offsetLeft<f)&&(b=d,k=b.tagName.toUpperCase(),"INPUT"!=k&&"SELECT"!=
k&&(""==b.style.backgroundSize&&"auto"!=g[c].width&&K(b,"width","auto"),"IMG"!=k&&b.removeAttribute("width"),J(b,"border-left"),J(b,"border-right"),J(b,"margin-left"),J(b,"margin-right"),J(b,"padding-left"),J(b,"padding-right"),b.className=""!=b.className?b.className+" psSingleColumn":"psSingleColumn"),this.L(d)),a.getAttribute("data-pagespeed-negative-bottom-margin")&&(a.removeAttribute("data-pagespeed-negative-bottom-margin"),b=window.getComputedStyle(a),d=I(b,"height"),null!=d&&K(a,"margin-bottom",
""+-d+"px")),k=f}};var V=[S.prototype.T,"shrink wide elements",S.prototype.U,"string floats",S.prototype.da,"cleanup styles",S.prototype.R,"repair distored images",S.prototype.S,"resize if too wide",S.prototype.L,"expand columns",S.prototype.ja,"resize vertically"];function Wa(){this.k=[]}function Xa(){this.j=-1;this.g=this.ia=null;this.d="";this.backgroundColor=this.ca=this.backgroundImage=this.aa=this.c=this.h=null}n=Wa.prototype;n.Z=20;n.X=10;n.F=200;n.Y=400;n.G=6E3;n.$=.5;
function W(a,b,c,d,e){var g=Ia(b);Ya(b);var f=g.width*g.height;if(g.width>a.Z&&g.height>a.X&&f>a.Y&&g.top<a.G&&g.height<a.F&&f>=c&&f<=d){var k=f=null,h;for(h in N)if(k=P(b,N[h]))return f=N[h],"IMG"==f&&(g.width=b.naturalWidth,g.height=b.naturalHeight),a=new Xa,a.d=k,a.g=b,a.h=f,a.c=g,a}if(e)for(b=b.firstChild;b;b=b.nextSibling){if(g=M(b),null!=g&&(g=W(a,g,c,d,e)))return g}else if(b.parentNode&&(b=M(b.parentNode),null!=b))return W(a,b,c,d,e);return null}
function Za(a,b,c){var d;a:{var e=Ia(b);Ya(b);if(e.top<a.G&&e.height<a.F){d=0;b.title&&(d+=x(b.title,"logo"));b.id&&(d+=x(b.id,"logo"));b.className&&(d+=x(b.className,"logo"));b.alt&&(d+=x(b.alt,"logo"));var g;g=document.domain.toLowerCase().split(".");var f=g.length;g=4<f&&2==g[f-3].length?g[f-5]:3<f?g[f-4]:null;f=0;g&&(b.id&&(d+=x(b.id,g)),b.className&&(d+=x(b.className,g)),b.title&&(f+=0<=O(b.title).indexOf(O(g))?1:0),b.alt&&(f+=0<=O(b.alt).indexOf(O(g))?1:0));var k=e.width*e.height;(e=W(a,b,k*
a.$,k,!0))||(e=W(a,b,k,Infinity,!1));if(e){k=e.d;if(!k||0<=k.indexOf("data:image/"))k="";else{var h=k.lastIndexOf("/");0>h?h=0:++h;var l=k.indexOf(".",h);0>l&&(l=k.length);k=k.substring(h,l)}b:{if(h=k)if(h=h.toLowerCase(),0<=h.indexOf("logo")&&0>h.indexOf("logout")&&0>h.indexOf("no_logo")&&0>h.indexOf("no-logo")){h=1;break b}h=0}k&&g&&(f+=0<=O(k).indexOf(O(g))?1:0);d=d+h+f;if(0<d){e.j=d;e.ia=b;d=e;break a}}}d=null}d&&(a.k=a.k.concat(d),++c);for(b=b.firstChild;b;b=b.nextSibling)d=M(b),null!=d&&Za(a,
d,c)}
function $a(a){var b=null;if(0==a.k.length)return null;var c=a.k;if(1==c.length)return b=c[0];var d=0,e=0,g=Infinity;for(a=0;b=c[a];++a)var f=b.c,g=Math.min(g,f.top),e=Math.max(e,f.bottom),d=Math.max(d,f.width*f.height);for(a=0;b=c[a];++a)f=b.c,b.j=f.width*f.height/d*b.j*(1-(f.top-g)/(e-g));for(a=f=0;b=c[a];++a)f=Math.max(f,b.j);d=[];for(a=0;b=c[a];++a)b.j==f&&(d=d.concat(b));if(1==d.length)return b=d[0];c=d[0];e=c.c;for(a=1;b=d[a];++a)if(f=b.c,e.top>f.top||e.top==f.top&&e.left>f.left||e.top==f.top&&
e.left==f.left&&e.width*e.height>f.width*f.height)c=b,e=c.c;return c}function ab(a){if(a=document.defaultView.getComputedStyle(a,null))if(a=a.getPropertyValue("background-color")){a:{var b=a.indexOf("("),c=a.lastIndexOf(")");a=(0<=b&&c>b?a.substring(b+1,c):null).split(", ");for(var b=[],c=0,d=a.length;c<d;++c)if(b[c]=parseInt(a[c],10),isNaN(b[c])){a=null;break a}a=b}if(3==a.length||4==a.length&&0!=a[3])return a}return null}
n.run=function(){if(!document.body)return null;Za(this,document.body,0);var a;if((a=$a(this))&&a.g){var b=a.g,c=null;if("IMG"==a.h||"SVG"==a.h)c=P(b,"background-image");var d=ab(b),e=null;for(b.parentNode&&(e=M(b.parentNode));e&&!c&&!d;)b=e,c=P(b,"IMG")||P(b,"SVG")||P(b,"background-image"),d=ab(b),e=b.parentNode?M(b.parentNode):null;a.aa=b;a.backgroundImage=c;a.backgroundColor=d||[255,255,255];a.ca=Ia(b)}else a=null;return a};w("pagespeed.MobLogo.prototype.run",Wa.prototype.run);function bb(){this.s=[];this.V=!0}bb.prototype.W="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAJAAAACQCAQAAABNTyozAAAAIGNIUk0AAHomAACAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAACYktHRAD/h4/MvwAAAAlwSFlzAAALEwAACxMBAJqcGAAAATdJREFUeNrt0klOBTEQREHfDI7FTEn/4M2GBULQo22wK+ICKT1lKQAAAAAAAAAAAAAAAAAA/Jm7rmv3o+W5laU8d1uLspQYLc/SLVF8rsVoefokii9rMVqe9oni21qMlqdtovhhLUbL0y5R/LIWo+VZylKeuuX5t4nW8tRPFBtrMV6gmolic+t9xA/VSjRonl6JBs7TI9HgeVonmiDPvkSPmfO0SjRRnhaJJstTO9GEeWom2s7zVgZVI9HEeWokmjzPvkQPmfNcSZQkz9lEifKcSZQsz9FECfMcSZQ0z95E23ley8S2E6XOcz3R9HmuJUqR53yiNHnOJUqV53iidHmOJUqZZ3+itHn2JXopyd3kOZ9IntVE8qwmkmc1kTyrieRZTSTPaiJ5AAAAAAAAAAAAAAAAAGjgA62rM0XB6dNxAAAAAElFTkSuQmCC";
function cb(a,b,c){var d=[];for(b=b.firstChild;b;b=b.nextSibling)"UL"==b.tagName?d=ja(d,cb(a,b,c+1)):("A"==b.tagName&&(b.setAttribute("data-mobilize-nav-level",c),d.push(b)),d=ja(d,cb(a,b,c)));return d}function db(){var a=document.querySelector(".psmob-nav-panel"),b=document.querySelector(".psmob-header-bar");H(b,"open");H(a,"open");H(document.body,"noscroll")}
function eb(a){var b=document.querySelector(".psmob-menu-button");document.body.addEventListener("click",function(a){if(b.contains(a.target))db();else{var d=document.querySelector(".psmob-nav-panel");F(d,"open")&&!d.contains(a.target)&&(db(),a.stopPropagation(),a.preventDefault())}}.bind(a),!0)}
function fb(){document.querySelector("nav.psmob-nav-panel > ul").addEventListener("click",function(a){var b=a.target;a=t(b)&&1==b.nodeType&&F(a.target,"psmob-menu-expand-icon")?a.target.parentNode:a.target;"DIV"==a.tagName&&(H(a.nextSibling,"open"),H(a.firstChild,"open"))})};function hb(){this.N=null}
hb.prototype.ea=function(a,b,c){var d=document.createElement("span");d.classList.add("psmob-logo-span");if(a&&a.d){var e=document.createElement("IMG");e.src=a.d;e.style.backgroundColor=b;e.setAttribute("data-mobile-role","logo");d.appendChild(e)}else d.innerHTML=window.location.host;var e=String(Math.floor(7)),g=String(Math.floor(14)),f=String(Math.floor(21)),e='<button class="psmob-menu-button">'+('<svg height="28px" width="28px" style="stroke:'+c+";stroke-width:"+String(Math.floor(4.2))+'px" ><line x1="4px" y1="'+
e+'px" x2="24px" y2="'+e+'px"/><line x1="4px" y1="'+g+'px" x2="24px" y2="'+g+'px"/><line x1="4px" y1="'+f+'px" x2="24px" y2="'+f+'px"/></svg>')+"</button>";document.body.appendChild(d);b=new Ea(c,b,e);if(a&&a.g&&a.h)switch(c=a.g,a.h){case "IMG":case "SVG":c.parentNode.removeChild(c);break;case "background-image":c.style.backgroundImage="none"}this.fa(b)};function X(){this.n=0;this.i={};this.ka=Date.now();this.I=!1;this.f=this.B=this.Q=this.a=this.e=0;this.r=!1;this.C=this.u=0;this.o=new S(this);this.o.K["ps-progress-scrim"]=!0}function ib(a){if(0==a.f)if(console.log("mobilizing site"),window.psNavMode&&!Ca()){++a.u;var b=a.i;(a=a.ha.bind(a))||alert("Not expecting to start onloads after the callback is called");var c=new hb;c.fa=a;c.N=(new Wa).run(b);(new Q).run(c.N,v(c.ea,c))}else jb(a);else a.r=!0}
X.prototype.ha=function(a){--this.u;Y(this,this.e,"extract theme");var b=new bb;console.log("Starting nav resynthesis.");var c;if(pagespeedNavigationalIds){c=Array(pagespeedNavigationalIds.length);for(var d=0,e;e=pagespeedNavigationalIds[d];d++)c[d]=document.getElementById(e)}else c=[];d=document.querySelectorAll(".topNavList");e=d.length;if(0<e){for(var g=Array(e),f=0;f<e;f++)g[f]=d[f];d=g}else d=[];b.s=ia(c,d);c=document.getElementsByTagName("*");for(d=0;e=c[d];d++)g=window.getComputedStyle(e),
"fixed"==g.getPropertyValue("position")&&(f=e.getBoundingClientRect().top,e.style.top=String(60+f)+"px"),999999<=g.getPropertyValue("z-index")&&(console.log("Element z-index exceeded 999999, setting to 999998."),e.style.zIndex=999998);d=document.createElement("div");document.body.insertBefore(d,document.body.childNodes[0]);G(d,"psmob-header-spacer-div");c=document.createElement("header");document.body.insertBefore(c,d);G(c,"psmob-header-bar");c.innerHTML=a.ga;c.style.borderBottom="thin solid "+a.q;
(d=document.getElementsByClassName("psmob-logo-span")[0])&&c.appendChild(d);if(d=document.querySelector('[data-mobile-role="logo"]'))c.style.backgroundColor=d.style.backgroundColor;c=b.V&&a.O?a.O:"#3c78d8";a=".psmob-header-bar { background-color: "+c+" }\n.psmob-nav-panel { background-color: "+(b.V&&a.q?a.q:"white")+" }\n.psmob-nav-panel > ul li { color: "+c+" }\n.psmob-nav-panel > ul li a { color: "+c+" }\n";c=document.createElement("style");c.type="text/css";c.appendChild(document.createTextNode(a));
document.head.appendChild(c);if(0!=b.s.length&&!Ca()){a=document.body.insertBefore(document.createElement("nav"),document.getElementsByClassName("psmob-header-bar")[0].nextSibling);G(a,"psmob-nav-panel");a=a.appendChild(document.createElement("ul"));G(a,"open");for(c=0;d=b.s[c];c++){d.setAttribute("data-mobilize-nav-section",c);e=cb(b,d,0);g=[];g.push(a);for(var f=0,k=e.length;f<k;f++){var h=e[f].getAttribute("data-mobilize-nav-level"),l=f+1==k?h:e[f+1].getAttribute("data-mobilize-nav-level");if(h<
l){var m=document.createElement("li"),h=m.appendChild(document.createElement("div")),l=h.appendChild(document.createElement("img"));l.setAttribute("src",b.W);G(l,"psmob-menu-expand-icon");h.appendChild(document.createTextNode(e[f].textContent||e[f].innerText));g[g.length-1].appendChild(m);h=document.createElement("ul");m.appendChild(h);g.push(h)}else for(m=document.createElement("li"),g[g.length-1].appendChild(m),m.appendChild(e[f].cloneNode(!0)),m=h-l;0<m&&1<g.length;)g.pop(),m--}d.parentNode.removeChild(d)}d=
document.querySelector(".psmob-nav-panel > ul a");e={};a=[];for(c=0;g=d[c];c++)g.href in e?(f=g.innerHTML.toLowerCase(),-1==e[g.href].indexOf(f)?e[g.href].push(f):"LI"==g.parentNode.tagName&&a.push(g.parentNode)):(e[g.href]=[],e[g.href].push(g.innerHTML.toLowerCase()));for(c=0;d=a[c];c++)d.parentNode.removeChild(d);c=document.querySelectorAll(".psmob-nav-panel *");for(a=0;d=c[a];a++)d.removeAttribute("style"),d.removeAttribute("width"),d.removeAttribute("height"),"A"==d.tagName&&""==d.innerText&&
d.hasAttribute("title")&&d.appendChild(document.createTextNode(d.getAttribute("title")));c=document.querySelectorAll(".psmob-nav-panel img:not(.psmob-menu-expand-icon)");for(a=0;d=c[a];++a)e=Math.min(2*d.naturalHeight,40),d.setAttribute("height",e);eb(b);fb()}Y(this,this.e,"navigation");jb(this)};X.prototype.ba=function(){--this.f;Y(this,1E3,"background image");0==this.f&&this.r&&(ib(this),this.r=!1)};
function kb(a,b){var c=T(a.o,b);if(null!=c){var d=L(c);if(d&&(0==d.lastIndexOf("http://",0)||0==d.lastIndexOf("https://",0))&&!a.i[d]){var e=new Image;++a.f;e.onload=a.ba.bind(a);e.onerror=e.onload;e.src=d;a.i[d]=e}for(c=c.firstChild;c;c=c.nextSibling)kb(a,c)}}X.prototype.xhrSendHook=function(){++this.n};X.prototype.xhrResponseHook=function(){--this.n;this.a+=this.C;jb(this)};
function jb(a){if(0==a.n&&0==a.u&&0==a.f){var b=a.o;if(null!=document.body)for(var c=0;c<V.length;++c){V[c].call(b,document.body);++c;var d=b.v;Y(d,d.e,V[c])}if(a.I){if(a=document.getElementById("ps-progress-remove"))a.textContent="Remove Progress Bar and show mobilized site"}else lb()}}function mb(a){Z.I=a;var b=document.getElementById("ps-progress-log");b&&(b.style.color=a?"#333":"white");a&&(a=document.getElementById("ps-progress-show-log"))&&(a.style.display="none")}
function Ya(a){a.getAttribute("ps-save-visibility")||(a=window.getComputedStyle(a))&&a.getPropertyValue("visibility")}function Y(a,b,c){a.B+=b;b=100;0<a.a&&(b=Math.round(100*a.B/a.a),100<b&&(b=100));if(b!=a.Q){var d=document.getElementById("ps-progress-span");d&&(d.style.width=b+"%");a.Q=b}a=""+b+"% "+(Date.now()-a.ka)+"ms: "+c;console.log(a);if(c=document.getElementById("ps-progress-log"))c.textContent+=a+"\n"}
function lb(){var a=document.getElementById("ps-progress-scrim");a&&(a.style.display="none",a.parentNode.removeChild(a))}var Z=new X;mb(window.psDebugMode);Z.e=Da(document.body);Z.C=V.length/2*Z.e;Z.a+=Z.C;window.psNavMode&&Ca()&&(Z.a+=Z.e,Z.a+=Z.e);null!=document.body&&kb(Z,document.body);Z.a+=1E3*Z.f;window.pagespeedXhrHijackSetListener(Z);ib(Z);w("psGetVisiblity",function(a){Ya(a)});w("psSetDebugMode",function(){mb(!0)});w("psRemoveProgressBar",function(){lb()});})();
