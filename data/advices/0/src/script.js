var Event = function() {
	
	var guid = 0;
	
	function fixEvent(e) {
		e = e || window.event;
		if (e.fixed) return e;
		e.fixed = true;
		e.preventDefault = e.preventDefault || function(){this.returnValue = false}
		e.stopPropagation = e.stopPropagation || function(){this.cancelBubble = true}
		if (!e.target) e.target = e.srcElement
		if (!e.relatedTarget && e.fromElement) e.relatedTarget = e.fromElement == e.target ? e.toElement : e.fromElement;
		if (e.clientX) {
			var html = document.documentElement;
			var body = document.body;
			e.pageX = e.clientX + (html && html.scrollLeft || body && body.scrollLeft || 0) - (html.clientLeft || 0);
			e.pageY = e.clientY + (html && html.scrollTop || body && body.scrollTop || 0) - (html.clientTop || 0);
		}
		
		if (!e.which && e.button) e.which = (e.button & 1 ? 1 : ( e.button & 2 ? 3 : ( e.button & 4 ? 2 : 0 ) ));

		return e;

	}

	function commonHandle(e) {

		e = fixEvent(e);

		var handlers = this.events[e.type]

		for (var g in handlers) {
			var handler = handlers[g];
			var ret = handler.call(this, e);
			if ( ret === false ) {
				e.preventDefault()
				e.stopPropagation()
			}
		}
  
	}

	return {

		add: function(el, type, handler) {

			if (el.setInterval && (el != window && !el.frameElement)) {
				el = window;
			}

			if (!handler.guid) {
				handler.guid = ++guid;
			}

			if (!el.events) {
				el.events = {};
				el.handle = function(e) {
					return commonHandle.call(el, e);
				}
			}

			if (!el.events[type]) {
				
				el.events[type] = {}        
				
				if (el.addEventListener)
					el.addEventListener(type, el.handle, false)
				else if (el.attachEvent)
					el.attachEvent("on" + type, el.handle)

			}

			el.events[type][handler.guid] = handler;
		
		},

		remove: function(el, type, handler) {
  
			var handlers = el.events && el.events[type];

			if (!handlers) return;

			if (!handler) {
				for ( var handle in handlers ) {
					delete el.events[type][handle];
				}
				return;
			}
			
			delete handlers[handler.guid];

			for (var any in handlers) return;
				
			if (el.removeEventListener) el.removeEventListener(type, el.handle, false); else if (el.detachEvent) el.detachEvent("on" + type, el.handle);

			delete el.events[type];

			for (var any in el.events) return;

			try {
				delete el.handle;
				delete el.events ;
			} catch(e) {
				el.removeAttribute("handle");
				el.removeAttribute("events");
			}
		} 
	}

}();

var Js = {

	q: !!(document.querySelector && document.querySelectorAll),
	
	id: function(id, el) {
		el = el || document;
		if (Js.q) return el.querySelector('#'+id); else return el.getElementById(id);
	},

	cls: function(c, el) {
		
		el = el || document;
		
		if (Js.q) return el.querySelectorAll('.'+ c);
		
		if(!el.getElementsByClassName) {
			var a = [], re = new RegExp('(^| )'+c+'( |$)'), els = el.getElementsByTagName("*");
			for(var i=0,j=els.length; i<j; i++) {if(re.test(els[i].className))a.push(els[i]);}
			return a;

		} else return el.getElementsByClassName(c);

	},
	
	c_el: function(el, cls, id, dsp, hgt, wid, pos, top, lft, rgt, bot) {
		var e = document.createElement(el);
		if(id) e.id = id;
		if(cls) e.className = cls;
		if(dsp) e.style.display = dsp;
		if(pos) e.style.position = pos;
		if(top) e.style.top = top;
		if(rgt) e.style.right = rgt;
		if(bot) e.style.bottom = bot;
		if(lft) e.style.left = lft;
		if(wid) e.style.width = wid;
		if(hgt) e.style.height = hgt;
		e.ac = function(el){e.appendChild(el); return e;}
		return e;
	},
	
	c_txt: function(t) {
		return document.createTextNode(t);
	},

	remove_element: function(el){
		
		if (typeof el == 'string') el = Js.id(el);
	
		if (typeof el == 'object' && el.parentNode) el.parentNode.removeChild(el);
		
		return false;
	
	}

};

var UI = {
	
	show: function(el) {
		if (typeof el == 'string') el = Js.id(el);
		el.style.display = 'block';
	},
	
	hide: function(el) {
		if (typeof el == 'string') el = Js.id(el);
		el.style.display = 'none';
	},

	i_box: function(el, v) {
		if(el && typeof el == 'object') {
			Event.add(el, 'blur', function(v, el){return (function(){if (el.value == '') el.value = v;return false;})}(v, el));
			Event.add(el, 'focus',function(v, el){return (function(){if (el.value == v) el.value = '';return false;})}(v, el));
		}
	},
	
	login: function(el) {
		
		return function(e) {	
			e.preventDefault();
			if (Js.id('l_username')) return false;
			
			var reg_l = Js.id('l_reg'), i_n = Js.c_el('input', 'textbox', 'l_username'), i_p = Js.c_el('input', 'textbox', 'l_password'), i_a = Js.c_el('input'), i_r = Js.c_el('input'), i_u = Js.c_el('input'), l_f = Js.c_el('form'), i_c = Js.c_el('a').ac(Js.c_txt('Отмена')), i_e = Js.c_el('a').ac(Js.c_txt('Войти'));
			UI.hide(el);
			UI.hide(reg_l);
			l_f.action = '/forum/member.php';
			l_f.method = 'post';
			reg_l.style.display = 'none';
			i_a.name = 'action';
			i_u.name = 'url';
			i_r.name = 'remember';
			i_a.type = i_u.type = i_r.type = 'hidden';
			i_a.value = 'do_login';
			i_u.value = window.location.href;
			i_r.value = 'yes';
			i_n.size = i_p.size = '15';
			i_n.value = 'Ваш логин';
			i_p.value = 'Ваш пароль';
			i_n.type = 'text',
			i_p.type = i_p.name = 'password',
			i_n.name = 'username',
			UI.i_box(i_n, i_n.value);
			UI.i_box(i_p, i_p.value);
			l_f.ac(i_n).ac(i_p).ac(i_a).ac(i_u).ac(i_e).ac(i_r).ac(i_c);
			el.parentNode.insertBefore(l_f, el);			

			Event.add(i_e, 'click', function(){l_f.submit()});
			Event.add(i_c, 'click', function(){Js.remove_element(l_f); UI.show(reg_l); UI.show(el); return false;})
		}
	}

};

window.onload = function() {
	
	if (login = Js.id('l_link')) Event.add(login, 'click', UI.login(login));
	
	UI.i_box(Js.id('search_word'), 'Поиск по сайту...');

	return false;
	
};