(function (global, factory) {
  typeof exports === 'object' && typeof module !== 'undefined' ? module.exports = factory() :
  typeof define === 'function' && define.amd ? define(factory) :
  (global = typeof globalThis !== 'undefined' ? globalThis : global || self, global.Vue = factory());
})(this, (function () { 'use strict';

  function _iterableToArrayLimit(r, l) {
    var t = null == r ? null : "undefined" != typeof Symbol && r[Symbol.iterator] || r["@@iterator"];
    if (null != t) {
      var e,
        n,
        i,
        u,
        a = [],
        f = !0,
        o = !1;
      try {
        if (i = (t = t.call(r)).next, 0 === l) {
          if (Object(t) !== t) return;
          f = !1;
        } else for (; !(f = (e = i.call(t)).done) && (a.push(e.value), a.length !== l); f = !0);
      } catch (r) {
        o = !0, n = r;
      } finally {
        try {
          if (!f && null != t.return && (u = t.return(), Object(u) !== u)) return;
        } finally {
          if (o) throw n;
        }
      }
      return a;
    }
  }
  function _typeof(o) {
    "@babel/helpers - typeof";

    return _typeof = "function" == typeof Symbol && "symbol" == typeof Symbol.iterator ? function (o) {
      return typeof o;
    } : function (o) {
      return o && "function" == typeof Symbol && o.constructor === Symbol && o !== Symbol.prototype ? "symbol" : typeof o;
    }, _typeof(o);
  }
  function _classCallCheck(instance, Constructor) {
    if (!(instance instanceof Constructor)) {
      throw new TypeError("Cannot call a class as a function");
    }
  }
  function _defineProperties(target, props) {
    for (var i = 0; i < props.length; i++) {
      var descriptor = props[i];
      descriptor.enumerable = descriptor.enumerable || false;
      descriptor.configurable = true;
      if ("value" in descriptor) descriptor.writable = true;
      Object.defineProperty(target, _toPropertyKey(descriptor.key), descriptor);
    }
  }
  function _createClass(Constructor, protoProps, staticProps) {
    if (protoProps) _defineProperties(Constructor.prototype, protoProps);
    if (staticProps) _defineProperties(Constructor, staticProps);
    Object.defineProperty(Constructor, "prototype", {
      writable: false
    });
    return Constructor;
  }
  function _slicedToArray(arr, i) {
    return _arrayWithHoles(arr) || _iterableToArrayLimit(arr, i) || _unsupportedIterableToArray(arr, i) || _nonIterableRest();
  }
  function _arrayWithHoles(arr) {
    if (Array.isArray(arr)) return arr;
  }
  function _unsupportedIterableToArray(o, minLen) {
    if (!o) return;
    if (typeof o === "string") return _arrayLikeToArray(o, minLen);
    var n = Object.prototype.toString.call(o).slice(8, -1);
    if (n === "Object" && o.constructor) n = o.constructor.name;
    if (n === "Map" || n === "Set") return Array.from(o);
    if (n === "Arguments" || /^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(n)) return _arrayLikeToArray(o, minLen);
  }
  function _arrayLikeToArray(arr, len) {
    if (len == null || len > arr.length) len = arr.length;
    for (var i = 0, arr2 = new Array(len); i < len; i++) arr2[i] = arr[i];
    return arr2;
  }
  function _nonIterableRest() {
    throw new TypeError("Invalid attempt to destructure non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.");
  }
  function _toPrimitive(input, hint) {
    if (typeof input !== "object" || input === null) return input;
    var prim = input[Symbol.toPrimitive];
    if (prim !== undefined) {
      var res = prim.call(input, hint || "default");
      if (typeof res !== "object") return res;
      throw new TypeError("@@toPrimitive must return a primitive value.");
    }
    return (hint === "string" ? String : Number)(input);
  }
  function _toPropertyKey(arg) {
    var key = _toPrimitive(arg, "string");
    return typeof key === "symbol" ? key : String(key);
  }

  //重写数组的部分方法

  var oldArrayProto = Array.prototype; //获取数组的原型
  var newArrayProto = Object.create(oldArrayProto); //将原有的原型加在新数组原型上

  //找到所有的变异方法

  var methods = ['push', 'pop', 'shift', 'unshift', 'splice', 'sort', 'reverse'];
  methods.forEach(function (method) {
    //arr.push(1,2,3)
    newArrayProto[method] = function () {
      var _oldArrayProto$method;
      for (var _len = arguments.length, args = new Array(_len), _key = 0; _key < _len; _key++) {
        args[_key] = arguments[_key];
      }
      //调用原来的方法修改数组，函数的劫持，切片编程
      var result = (_oldArrayProto$method = oldArrayProto[method]).call.apply(_oldArrayProto$method, [this].concat(args));

      // console.log('method',method);

      //对新增的数据再次进行劫持
      var inserted;
      var ob = this.__ob__;
      switch (method) {
        case 'push':
        case 'unshift':
          inserted = args;
          break;
        case 'splice':
          //arr.splice(0,1,{a:1})//第一个是删除的位置，第二个是个数
          inserted = args.slice(2);
          break;
      }
      if (inserted) {
        //对新增内容再次进行观测,这是新的数组，可以使用observeArray进行观测，那么可以将Observer的实例对象，放在data的某一个值上
        ob.observeArray(inserted);
      }
      ob.dep.notify();
      return result;
    };
  });

  var id$1 = 0;
  var Dep = /*#__PURE__*/function () {
    function Dep() {
      _classCallCheck(this, Dep);
      this.id = id$1++; //属性的dep需要收集watcher
      this.subs = []; //存放着当前属性对应的watcher有哪些
    }
    _createClass(Dep, [{
      key: "depend",
      value: function depend() {
        //为了避免一个模板中使用两个数据导致重复收集,除了dep->watcher还希望watcher->dep
        // this.subs.push(Dep.target);//收集watcher这样写会重复
        Dep.target.addDep(this); //收集dep,先让watcher收集到dep,再让dep存储watcher
        // 一个组件中由多个属性组成(那么对应一个watcher监视多个dep)
      }
    }, {
      key: "addSub",
      value: function addSub(watcher) {
        this.subs.push(watcher);
      }
    }, {
      key: "notify",
      value: function notify() {
        this.subs.forEach(function (watcher) {
          return watcher.update();
        }); //让视图去更新
      }
    }]);
    return Dep;
  }();
  Dep.target = null;
  var stack = [];
  function pushTarget(watcher) {
    stack.push(watcher);
    Dep.target = watcher;
    // 渲染时会将watcher入栈，渲染完就出栈
  }

  function popTarget() {
    stack.pop();
    Dep.target = stack[stack.length - 1];
  }

  var Observer = /*#__PURE__*/function () {
    function Observer(data) {
      _classCallCheck(this, Observer);
      // 给每个对象做收集功能 
      this.dep = new Dep();
      //数组单独处理
      data.__ob__ = this; //这里可以给data添加一个__ob__属性，这个属性指向Observer实例，这样就可以通过__ob__属性访问Observer实例了
      Object.defineProperty(data, '__ob__', {
        value: this,
        enumerable: false //将ob变为不可枚举否则会陷入死循环，因为进入data后枚举到其__ob__属性（实际回到了本身），那么就会出现问题
      });
      // 同时给数据加了标识，数据上有ob那么对象被代理过，但是也需要其变成不可枚举属性
      if (Array.isArray(data)) {
        //这里我们可以重写数组中的七个编译方法，可以修改数组本身的。除此之外还有数组内的引用方法也应该劫持，比如一个对象作为数组的内容
        //同时保留其他的方法，因此需要在array.js里面重写
        data.__proto__ = newArrayProto;
        this.observeArray(data); //观测数组
      } else {
        this.walk(data);
      }
    }
    _createClass(Observer, [{
      key: "walk",
      value: function walk(data) {
        Object.keys(data).forEach(function (key) {
          return defineReactive(data, key, data[key]);
        });
      }
    }, {
      key: "observeArray",
      value: function observeArray(data) {
        data.forEach(function (item) {
          return observe(item);
        });
      }
      //剩下的和之前一样
    }]);
    return Observer;
  }();
  function dependArray(val) {
    for (var i = 0; i < val.length; i++) {
      var current = val[i];
      // console.log(current);
      if (Array.isArray(current)) {
        //如果还是数组
        dependArray(current);
        current.__ob__.dep.depend(); //收集数组中数组依赖
      }
    }
  }

  function defineReactive(data, key, val) {
    //形成闭包，值不会消失
    //如果数据是对象那么再次递归处理进行劫持
    var childOb = observe(val); //对所有的对象都进行属性劫持,childOb.dep 用来收集依赖
    var dep = new Dep(); //每一个属性都有dep
    Object.defineProperty(data, key, {
      get: function get() {
        //取值会执行get
        if (Dep.target) {
          dep.depend(); //让这个属性的收集器记住当前的watcher
          if (childOb) {
            //比如对象,数组类
            childOb.dep.depend(); //让数组或者对象本身进行依赖收集
            if (Array.isArray(val)) {
              dependArray(val);
            }
          }
        }
        return val;
      },
      set: function set(newVal) {
        if (newVal !== val) {
          val = newVal;
          dep.notify(); //通知更新
        }
      }
    });
  }

  function observe(data) {
    if (_typeof(data) !== 'object' || data === null) return; //只对对象劫持
    //如果一个对象被劫持了，那么就不需要再被劫持了（判断一个对象是否被劫持过，可以添加一个实例，用实例进行判定）

    if (data.__ob__ instanceof Observer) {
      //说明被代理过，直接返回它的实例对象
      return data.__ob__;
    }
    return new Observer(data);
  }

  var id = 0;

  // 1)当我们创建渲染watcher的时候我们会把当前的渲染watcher放在Dep.target上
  // 2)调用_render()会取值走到get上
  var Watcher = /*#__PURE__*/function () {
    //不同组件有不同的watcher
    function Watcher(vm, exprOrFn, options, cb) {
      _classCallCheck(this, Watcher);
      this.cb = cb; //对于watch
      if (typeof exprOrFn === 'string') {
        this.getter = function () {
          return vm[exprOrFn];
        }; //将字符串变为函数
      } else {
        this.getter = exprOrFn; //getter意味调用这个函数可以发生取值操作
      }

      this.id = id++;
      this.renderWatcher = options;
      this.deps = []; //收集依赖
      this.depsId = new Set(); //收集依赖的id
      this.vm = vm; //防止在计算属性取得getter时,调用的this不是对应的this

      this.lazy = options.lazy;
      this.dirty = this.lazy; //缓存值
      this.oldValue = this.lazy ? undefined : this.get(); // 
      //value是旧值
    }
    _createClass(Watcher, [{
      key: "evalaute",
      value: function evalaute() {
        this.value = this.get(); //获取到用户函数的返回值,并且还要标识为脏
        this.dirty = false;
      }
    }, {
      key: "get",
      value: function get() {
        pushTarget(this); //静态属性只有一份
        var val = this.getter.call(this.vm); //会去vm上取值,当渲染时就会有取值操作触发getter,然后在getter里面操作
        popTarget(); //渲染完成就清空,只是在模板中收集的时候才会做依赖收集
        return val;
      }
    }, {
      key: "addDep",
      value: function addDep(dep) {
        //一个组件对应多个属性,重复的属性无需记录
        var id = dep.id;
        if (!this.depsId.has(id)) {
          this.deps.push(dep);
          this.depsId.add(id);
          dep.addSub(this);
        }
      }
    }, {
      key: "depend",
      value: function depend() {
        var i = this.deps.length;
        while (i--) {
          this.deps[i].depend(); //让计算属性watcher也收集渲染watcher
        }
      }
    }, {
      key: "update",
      value: function update() {
        if (this.lazy) {
          //如果是计算属性,依赖属性变化了,就标识是脏值
          this.dirty = true;
        } else {
          queueWatcher(this); //暂存watcher
          this.run(); //重新更新
        }
      }
    }, {
      key: "run",
      value: function run() {
        var newValue = this.get();
        if (this.user) {
          this.cb.call(this.vm, newValue, this.oldValue);
        }
      }
    }]);
    return Watcher;
  }();
  var queue = []; //因为可能更新同一属性多次，那么需要去重，只保留最后一个
  var has = {}; //使用对象去重，或者set去重
  var pending = false; //进行防抖操作，无论调用多少次，只执行一次

  function flushSchedulerQueue() {
    var flushQueue = queue.slice(0); //拷贝一下queue
    flushQueue.forEach(function (q) {
      return q.run();
    }); //在刷新过程中可能存在新的watcher，重新被放回在队列中
    queue = [];
    has = {};
    pending = false;
  }
  function queueWatcher(watcher) {
    var id = watcher.id; //取出每个监视器的唯一标识id
    if (has[id] == null) {
      queue.push(watcher);
      has[id] = true;
      //可能有多个组件不管update多少次，最终只执行一次刷新操作
      if (!pending) {
        nextTick(flushSchedulerQueue); //刷新调度队列
        pending = true;
      }
    }
  }
  var callbacks = [];
  var waiting = false;
  function flushCallbacks() {
    waiting = false;
    var cbs = callbacks.slice(0);
    callbacks = [];
    cbs.forEach(function (cb) {
      return cb();
    });
  }
  var timerFunc;
  if (Promise) {
    timerFunc = function timerFunc(flushCallbacks) {
      Promise.resolve().then(flushCallbacks);
    };
  } else if (MutationObserver) {
    var observer = new MutationObserver(flushCallbacks); //这里传入的回调是异步执行的
    var textNode = document.createTextNode(1);
    observer.observe(textNode, {
      characterData: true
    }); //让observer监控文本,如果数据变化,那么就执行cb任务
    timerFunc = function timerFunc() {
      textNode.textContent = 2;
    };
  } else if (setImmediate) {
    timerFunc = function timerFunc() {
      setImmediate(flushCallbacks);
    };
  } else {
    timerFunc = function timerFunc() {
      setTimeout(flushCallbacks, 0);
    };
  }

  //nextTick中没有直接使用某个api,而是采用优雅降级的方式
  // 内部采用promise(ie不兼容)降级为MutationObserver(h5的api) 可以再降级为ie专享setImmediate   降级为 setTimeout 
  function nextTick(cb) {
    //先内部还是先用户
    callbacks.push(cb); //维护nextTick中的callback方法,同步操作
    if (!waiting) {
      // debugger;
      timerFunc();
      waiting = true;
    }
  }

  function initState(vm) {
    var opts = vm.$options; //获取所有的选项
    if (opts.data) {
      //如果有data选项那么初始化data
      initData(vm);
    }
    if (opts.computed) {
      initComputed(vm);
    }
    if (opts.watch) {
      initWatch(vm);
    }
  }
  function initWatch(vm) {
    var watch = vm.$options.watch;
    for (var key in watch) {
      //字符串,数组,函数
      var handler = watch[key];
      if (Array.isArray(handler)) {
        for (var i = 0; i < handler.length; i++) {
          createWatcher(vm, key, handler[i]);
        }
      } else {
        createWatcher(vm, key, handler);
      }
    }
  }
  function createWatcher(vm, key, handler) {
    //字符串,数组,函数(还有可能是对象)
    if (typeof handler === 'string') {
      handler = vm[handler];
    }
    return vm.$watch(key, handler);
  }

  // function proxy(vm,target,key){
  //   Object.defineProperty(vm,key,{
  //     get(){
  //       return vm[target][key];
  //     },
  //     set(newVal){
  //       vm[target][key] = newVal;
  //     }
  //   })
  // }

  function proxy(vm, target) {
    Object.keys(vm[target]).forEach(function (key) {
      Object.defineProperty(vm, key, {
        get: function get() {
          return vm[target][key];
        },
        set: function set(newVal) {
          vm[target][key] = newVal;
        }
      });
    });
  }
  function initData(vm) {
    var data = vm.$options.data; //data可能是函数，可能是对象
    // debugger;
    data = typeof data === 'function' ? data.call(vm) : data; //call进行执行函数  data是用户的属性
    vm._data = data; //将data挂载到vm._data
    //对数据进行劫持，Vue2使用defineProperty
    observe(data);

    // 将vm._data用vm代理即可直接使用vm访问到,比如vm.xxx实际上是访问到的 vm._data.xxx
    // for(let key in data){
    //   proxy(vm,'_data',key);
    // }
    proxy(vm, '_data');
  }
  function initComputed(vm) {
    var computed = vm.$options.computed;
    var watchers = vm._computedWatchers = {}; //将计算属性watcher保存到vm上
    //循环对象
    for (var key in computed) {
      var userDef = computed[key];
      //userDef 可能是对象可能是函数
      //需要监控计算属性中get的变化,传入值,监视的实例,方法,配置项
      var fn = typeof userDef === 'function' ? userDef : userDef.get;
      watchers[key] = new Watcher(vm, fn, {
        lazy: true
      });
      defineComputed(vm, key, userDef);
    }
  }
  function defineComputed(target, key, userDef) {
    //   const getter = typeof userDef === 'function' ? userDef :userDef.get;
    var setter = userDef.set || function () {};
    Object.defineProperty(target, key, {
      get: createComputedGetter(key),
      //希望当重复取值时不会调用getter
      set: setter
    });
  }
  function createComputedGetter(key) {
    //我们需要检测是否执行这个getter
    return function () {
      var watcher = this._computedWatchers[key]; //获取到对应属性的watcher
      if (watcher.dirty) {
        //如果是脏的就去执行用户传入的函数
        watcher.evalaute(); //求值后 dirty变为false,下次取值,就不求值了
      }

      if (Dep.target) {
        //计算属性出栈后还有渲染 watcher,应该也让计算属性中的watcher去收集上一层watcher
        watcher.depend();
      }
      return watcher.value; //这样就不用每次取值都是get来取,可以从缓存中来取
    };
  }

  function initStateMixin(Vue) {
    Vue.prototype.$nextTick = nextTick;
    Vue.prototype.$watch = function (exprOrFn, cb) {
      //还有deep:true,immediate等
      // firstname
      // ()=>{}
      new Watcher(this, exprOrFn, {
        user: true
      }, cb);
    };
  }

  var ncname = "[a-zA-Z_][\\-\\.0-9_a-zA-Z]*";
  var qnameCapture = "((?:".concat(ncname, "\\:)?").concat(ncname, ")");
  var startTagOpen = new RegExp("^<".concat(qnameCapture)); //它匹配到的分组是一个标签名<xxx> 匹配开始标签名
  var endTag = new RegExp("^<\\/".concat(qnameCapture, "[^>]*>")); //匹配的是</xxx> 最终匹配到结束标签名 分组1是标签名
  var attribute = /^\s*([^\s"'<>\/=]+)(?:\s*(=)\s*(?:"([^"]*)"+|'([^']*)'+|([^\s"'=<>`]+)))?/; //匹配属性 a="xxxx" b  =  'xxx' c = xxx
  //第一个分组是属性的key，value是分组3或分组4或者分组5
  var startTagClose = /^\s*(\/?)>/; //可以匹配<div>或者<br/>

  function parseHTML(html) {
    // html最开始肯定是一个<
    //最终需要转化为一颗抽象的语法树

    var ELEMENT_TYPE = 1; //元素类型1
    var TEXT_TYPE = 3; //文本类型3
    var stack = []; //存放标签的栈
    var currentParent = null; //指向栈中的最后一个
    var root = null; //根节点

    function createASTElement(tag, attrs) {
      return {
        tag: tag,
        type: ELEMENT_TYPE,
        children: [],
        attrs: attrs,
        parent: null
      };
    }
    function start(tag, attrs) {
      //给标签名和属性
      var node = createASTElement(tag, attrs); //创造ast结点
      if (!root) {
        root = node; //如果树为空，则为根节点
      }

      if (currentParent) {
        node.parent = currentParent; //当前结点的父节点是当前的父节点
        currentParent.children.push(node); //把它父亲结点的儿子指向它；
      }

      stack.push(node); //把当前的标签名压入栈中
      currentParent = node;
    }
    function chars(text) {
      //文本放在当前结点中
      text = text.replace(/\s/g, ''); //如果空格超过两个以上就删除两个以上
      text && currentParent.children.push({
        type: TEXT_TYPE,
        text: text,
        parent: currentParent
      });
    }
    function end(tag) {
      stack.pop(); //弹出最后一个
      currentParent = stack[stack.length - 1];
    }
    function advance(len) {
      html = html.substring(len);
    }
    function parseStartTag() {
      var start = html.match(startTagOpen); //
      if (start) {
        var match = {
          tagName: start[1],
          attrs: []
          // start: index
        };

        advance(start[0].length); //匹配上了就进行截取
        // console.log(match,html);
        var attr, _end;
        while (!(_end = html.match(startTagClose)) && (attr = html.match(attribute))) {
          advance(attr[0].length);
          match.attrs.push({
            name: attr[1],
            value: attr[3] || attr[4] || attr[5] || true
          }); //true是为了弄disabled
        }

        if (_end) advance(_end[0].length); //结束的尖角号
        return match;
      }
      //如果不是开始标签的结束就一直匹配

      // console.log(html);
      return false;
    }
    while (html) {
      //如果textEnd为0，说明是一个开始标签或者结束标签   如果textEnd>0说明就是文本的结束位置
      var textEnd = html.indexOf('<'); //如果indexOf中的索引是0，则说明是个标签
      if (textEnd === 0) {
        var startTagMatch = parseStartTag(); //开始标签的匹配结果 
        if (startTagMatch) {
          //解析到开始标签
          start(startTagMatch.tagName, startTagMatch.attrs);
          continue;
        }
        var endTagMatch = html.match(endTag); //匹配结束标签
        if (endTagMatch) {
          advance(endTagMatch[0].length);
          end(endTagMatch[1]);
          // console.log(endTagMatch);
          continue;
        }
      }
      if (textEnd > 0) {
        var text = html.substring(0, textEnd); //文本内容
        if (text) {
          chars(text); //将文本内容传递给chars
          advance(text.length);
        }
      }
    }
    // console.log(root);
    return root;
  }

  function genProps(attrs) {
    var str = '';
    var _loop = function _loop() {
      var attr = attrs[i];
      if (attr.name === 'style') {
        //  color:red ==> {color:'red'}
        var obj = {};
        attr.value.split(';').forEach(function (item) {
          //qs库
          var _item$split = item.split(':'),
            _item$split2 = _slicedToArray(_item$split, 2),
            key = _item$split2[0],
            value = _item$split2[1];
          obj[key] = value;
        });
        attr.value = obj;
      }
      str += "".concat(attr.name, ":").concat(JSON.stringify(attr.value), ",");
    };
    for (var i = 0; i < attrs.length; i++) {
      _loop();
    }
    return "{".concat(str.slice(0, -1), "}"); //去掉最后一个逗号
  }

  var defaultTagRE = /\{\{((?:.|\r?\n)+?)\}\}/g; //匹配双括号，内容是表达式的变量
  function gen(node) {
    if (node.type === 1) {
      //说明是元素
      return codegen(node);
    } else {
      //文本两种情况
      var text = node.text;
      if (!defaultTagRE.test(text)) {
        //纯文本
        return "_v(".concat(JSON.stringify(text), ")");
      } else {
        //_v(_s(name)+'hello'+_s(age))
        var tokens = [];
        var match;
        defaultTagRE.lastIndex = 0; //从文本开头执行匹配,每次exec后,lastIndex都会更新为下一次匹配开始的位置
        var lastIndex = 0; //最后匹配的位置
        while (match = defaultTagRE.exec(text)) {
          //使用正则来捕获文本
          var index = match.index; //匹配的位置
          if (index > lastIndex) {
            //比如 {{name}} hello {{age}},取得就是 hello 这段
            tokens.push(JSON.stringify(text.slice(lastIndex, index)));
          }
          tokens.push("_s(".concat(match[1].trim(), ")"));
          lastIndex = index + match[0].length; //更新最后匹配的位置
        }
        // 防止插入语法后面还存在一些文本
        if (lastIndex < text.length) {
          tokens.push(JSON.stringify(text.slice(lastIndex)));
        }
        return "_v(".concat(tokens.join('+'), ")");
      }
    }
  }
  function genChildren(children) {
    return children.map(function (item) {
      return gen(item);
    });
  }

  /**
   * 为给定的抽象语法树生成代码
   * @param {Object} ast - 抽象语法树
   * @returns {string} - 生成的代码字符串
   */
  function codegen(ast) {
    //TODO:指令解析
    var children = genChildren(ast.children);
    var code = "_c('".concat(ast.tag, "',").concat(ast.attrs.length > 0 ? genProps(ast.attrs) : 'null').concat(ast.children.length > 0 ? ",".concat(children) : ',null', ")");
    return code;
  }
  function compileToFunction(template) {
    //1.将template转化为ast语法树
    var ast = parseHTML(template);
    // console.log(ast);
    // 2.生成render函数（render方法执行后返回的结果是虚拟DOM）
    //将ast树生成为类似于下面的字符串
    //  _c('div',{id:'app'},_c('div',{style:{color:'red'}},_v(_s(name)+'hello'),_c('span',undefine,_v(_s(age)))))
    // 
    var code = codegen(ast);
    code = "with(this){return ".concat(code, "}");
    var render = new Function(code); //根据代码生成render函数
    return render;
  }

  // h函数,_c函数都是调用这些

  var isReservedTag = function isReservedTag(tag) {
    return ["a", "ul", "ol", "li", "div", "span", "p", "img", "input", "button", "textarea", "h1", "h2", "h3", "h4", "h5", "h6", "table", "tr", "td", "th", "tbody", "thead", "tfoot", "tr", "th", "td", "select", "option", "form"].includes(tag);
  };
  function createElementVNode(vm, tag, data) {
    if (data == null) {
      data = {};
    }
    var key = data.key || null;
    if (key) {
      delete data.key;
    }

    //判断是否为原生标签
    for (var _len = arguments.length, children = new Array(_len > 3 ? _len - 3 : 0), _key = 3; _key < _len; _key++) {
      children[_key - 3] = arguments[_key];
    }
    if (isReservedTag(tag)) {
      return VNode(vm, tag, key, data, children);
    } else {
      //创建组件的虚拟结点
      // 需要包含组件的构造函数
      var Ctor = vm.$options.components[tag];
      // Ctor可能是组件的定义，可能是一个Sub类，还有可能是组件的component选项
      return createComponentVnode(vm, tag, key, data, children, Ctor);
    }
  }
  function createComponentVnode(vm, tag, key, data, children, Ctor) {
    if (_typeof(Ctor) === 'object') {
      Ctor = vm.$options._base.extend(Ctor); //将对象转化一下得到构造函数，_base声明于globalAPI上面的
    }

    data.hook = {
      init: function init(vnode) {
        //稍后创造真实节点的时候，如果是组件则调用此init方法
        //保存组件的实例到虚拟节点
        var instance = vnode.componentInstance = new vnode.componentOptions.Ctor();
        instance.$mount();
      }
    };
    return VNode(vm, tag, key, data, children, null, {
      Ctor: Ctor
    });
  }

  // _v
  function createTextNodeVNode(vm, text) {
    return VNode(vm, undefined, undefined, undefined, undefined, text);
  }
  // 创建虚拟DOM,和ast一样吗?
  // ast是做的语法上的转化,他描述的是语法本身(可以描述js css html)
  // 虚拟DOM是描述的dom元素,可以增加一些自定义属性(描述dom)
  function VNode(vm, tag, key, data, children, text, componentOptions) {
    return {
      vm: vm,
      tag: tag,
      key: key,
      data: data,
      children: children,
      text: text,
      componentOptions: componentOptions //组件的构造函数
    };
  }

  function isSameVnode(vnode1, vnode2) {
    return vnode1.tag === vnode2.tag && vnode1.key === vnode2.key;
  }

  function createComponent(vnode) {
    var i = vnode.data;
    if ((i = i.hook) && (i = i.init)) {
      i(vnode);
    }
    if (vnode.componentInstance) {
      return true; // 说明是组件
    }
  }

  function createElm(vnode) {
    var tag = vnode.tag,
      data = vnode.data,
      children = vnode.children,
      text = vnode.text;
    if (typeof tag === 'string') {
      //标签
      //创建真实元素也要区分组件还是元素
      if (createComponent(vnode)) {
        //组件
        return vnode.componentInstance.$el; //返回组件对应的真实元素
      }

      vnode.el = document.createElement(tag); // 这里将真实节点和虚拟节点对应起来，后续如果修改属性了
      patchProps(vnode.el, {}, data); // 处理data
      children.forEach(function (child) {
        vnode.el.appendChild(createElm(child)); //会将组件创建的元素，插入到父元素中
      });
    } else {
      //就是创建文本
      vnode.el = document.createTextNode(text);
    }
    return vnode.el;
  }
  function patchProps(el) {
    var oldProps = arguments.length > 1 && arguments[1] !== undefined ? arguments[1] : {};
    var props = arguments.length > 2 && arguments[2] !== undefined ? arguments[2] : {};
    //可能老的属性有而新的属性没有的情况需要去除老的
    var oldStyle = oldProps.style || {};
    var newStyle = props.style || {};
    for (var key in oldStyle) {
      //老的样式中有而新的样式中没有，则删除
      if (!newStyle[key]) {
        el.style[key] = '';
      }
    }
    for (var _key in oldProps) {
      if (!props[_key]) {
        el.removeAttribute(_key); //老的属性中有而新的没有，则删除属性
      }
    }

    for (var _key2 in props) {
      //styly{color:'red'}       使用新的覆盖老的
      if (_key2 === 'style') {
        for (var styleName in props.style) {
          el.style[styleName] = props.style[styleName];
        }
      } else {
        el.setAttribute(_key2, props[_key2]); //这里将属性都设置到真实dom上
      }
    }
  }

  function patch(oldVNode, vnode) {
    if (!oldVNode) {
      //这就是组件的挂载
      return createElm(vnode); //vm.$el  对应的就是组件渲染的结果了
    }
    //初渲染和后面的diff渲染一样的
    var isRealElement = oldVNode.nodeType; //nodeType是js原生属性,如果是元素节点的那么值就是1
    if (isRealElement) {
      var elm = oldVNode; //这里oldVNode是真实dom
      var parentElm = elm.parentNode; //拿到真实元素
      var newElm = createElm(vnode);
      parentElm.insertBefore(newElm, elm); //将新节点插入到老节点后面
      parentElm.removeChild(elm); //删除老节点
      return newElm;
    } else {
      // diff算法
      //1.两个节点不是同一个节点      直接删除老的
      // 2.两个节点是同一个节点(判断节点的tag和节点的key)比较两个节点的属性是否由差异（复用老节点，将差异的属性更新）
      // 节点比较完毕就需要比较两人的儿子
      patchVnode(oldVNode, vnode);
    }
  }
  function patchVnode(oldVNode, vnode) {
    if (!isSameVnode(oldVNode, vnode)) {
      //使用老节点的父亲进行替换
      var _el = createElm(vnode);
      oldVNode.el.parentNode.replaceChild(_el, oldVNode.el);
      return _el;
    }
    //文本情况,期望对文本内容进行比较
    var el = vnode.el = oldVNode.el; //复用老节点的元素
    if (!oldVNode.tag) {
      //是文本
      if (oldVNode.text !== vnode.text) {
        el.textContent = vnode.text; //用新的文本覆盖掉老的
      }
    }
    //是标签        需要比对标签的属性
    patchProps(el, oldVNode.data, vnode.data);

    //比较儿子节点      比较一方有儿子，一方没有儿子        两方都有儿子

    var oldChildren = oldVNode.children || [];
    var newChildren = vnode.children || [];
    if (oldChildren.length > 0 && newChildren.length > 0) {
      //完整的diff算法（需要比较两个人的儿子）
      updateChildren(el, oldChildren, newChildren);
    } else if (newChildren.length > 0) {
      //没有老的儿子直接插入
      mountChildren(el, newChildren);
    } else if (oldChildren.length > 0) {
      //新的没有，老的有，需要删除
      el.innerHTML = ''; //也可以循环删除
    }

    return el;
  }
  function mountChildren(el, newChildren) {
    for (var i = 0; i < newChildren.length; i++) {
      var child = newChildren[i];
      el.appendChild(createElm(child));
    }
  }
  function updateChildren(el, oldChildren, newChildren) {
    //比较两个儿子的时候，为了增高性能会有优化手段
    var oldStartIndex = 0; //老儿子开始的位置
    var newStartIndex = 0; //新儿子开始的位置
    var oldEndIndex = oldChildren.length - 1; //老儿子结束的位置
    var newEndIndex = newChildren.length - 1; //新儿子结束的位置
    var oldStartVnode = oldChildren[oldStartIndex];
    var oldEndVnode = oldChildren[oldEndIndex];
    var newStartVnode = newChildren[newStartIndex];
    var newEndVnode = newChildren[newEndIndex];
    function makeIndexByKey(children) {
      var map = {};
      children.forEach(function (child, index) {
        map[child.key] = index;
      });
      return map;
    }
    var map = makeIndexByKey(oldChildren);
    while (oldStartIndex <= oldEndIndex && newStartIndex <= newEndIndex) {
      if (!oldStartVnode) {
        oldStartVnode = oldChildren[++oldStartIndex];
      } else if (!oldEndVnode) {
        oldEndVnode = oldChildren[--oldEndIndex];
      }
      //有一方大于尾指针就停止
      else if (isSameVnode(oldStartVnode, newStartVnode)) {
        patchVnode(oldStartVnode, newStartVnode); // 如果是相同节点，则递归比较子节点
        oldStartVnode = oldChildren[++oldStartIndex];
        newStartVnode = newChildren[++newStartIndex];
      } else if (isSameVnode(oldEndVnode, newEndVnode)) {
        //比较尾节点
        patchVnode(oldStartVnode, newStartVnode); // 如果是相同节点，则递归比较子节点
        oldEndVnode = oldChildren[--oldEndIndex];
        newEndVnode = newChildren[--newEndIndex];
      }

      // 交叉比较 abcd -> dabc
      // 头尾比对和尾头比对,同时处理的倒序的情况
      else if (isSameVnode(oldEndVnode, newStartVnode)) {
        patchVnode(oldEndVnode, newStartVnode);
        el.insertBefore(oldEndVnode.el, oldStartVnode.el); //将老的后面的节点插入到开头节点的前面

        oldEndVnode = oldChildren[--oldEndIndex];
        newStartVnode = newChildren[++newStartIndex];
      } else if (isSameVnode(oldStartVnode, newEndVnode)) {
        patchVnode(oldStartVnode, newEndVnode);
        el.insertBefore(oldStartVnode.el, oldEndVnode.el.nextSibling); //将老头节点放在尾节点之后
        oldStartVnode = oldChildren[++oldStartIndex];
        newEndVnode = newChildren[--newEndIndex];
      }
      // 在给动态列表添加key时,尽可能避免使用索引,无论你怎么改变索引都是从0开始非常容易错乱
      else {
        // 乱序比对
        var moveIndex = map[newStartVnode.key]; //如果拿到则说明是要移动的索引
        if (moveIndex !== undefined) {
          var moveVnode = oldChildren[moveIndex]; //找到对应的虚拟节点 ,复用
          el.insertBefore(moveVnode.el, oldStartVnode.el);
          oldChildren[moveIndex] = undefined; //标识这个节点清空了
          patch(moveVnode, newStartVnode);
        } else {
          //找不到的情况
          el.insertBefore(createElm(newStartVnode), oldStartVnode.el);
        }
      }
    }
    if (newStartIndex <= newEndIndex) {
      //多余的塞进去
      for (var i = newStartIndex; i <= newEndIndex; i++) {
        var childEl = createElm(newChildren[i]);
        // 可能像后追加,可能向前追加
        // el.appendChild(childEl)
        var anchor = newChildren[newEndIndex + 1] ? newChildren[newEndIndex + 1].el : null; //获取下一个元素
        el.insertBefore(childEl, anchor); //当anchor为null的时候,就会认为是appendChild
      }
    }

    if (oldStartIndex <= oldEndIndex) {
      for (var _i = oldStartIndex; _i <= oldEndIndex; _i++) {
        if (oldChildren[_i]) {
          el.removeChild(oldChildren[_i].el);
        }
      }
    }
  }

  function initLifeCycle(Vue) {
    Vue.prototype._updata = function (vnode) {
      //将虚拟DOM转化为真实DOM
      var vm = this;
      var el = vm.$el;
      //这里vnode是虚拟节点,是真实节点
      var preVnode = vm._vnode;
      vm._vnode = vnode; //把组件第一次产生的虚拟节点保存到_vnode上
      if (preVnode) {
        //之前渲染 
        vm.$el = patch(preVnode, vnode);
      } else {
        vm.$el = patch(el, vnode); //使用vnode,更新出真正的dom
      }
      //patch既有初始化的功能,又有更新的功能
    };

    Vue.prototype._c = function () {
      return createElementVNode.apply(void 0, [this].concat(Array.prototype.slice.call(arguments)));
    };
    // _c('div',{},...children)
    Vue.prototype._v = function () {
      return createTextNodeVNode.apply(void 0, [this].concat(Array.prototype.slice.call(arguments)));
    };
    // _v(text)
    Vue.prototype._s = function (value) {
      if (_typeof(value) !== 'object') return value;
      return JSON.stringify(value);
    };
    Vue.prototype._render = function () {
      var vm = this;
      // 让with中的this指向vm
      // console.log(vm.name,vm.age);
      return vm.$options.render.call(vm); //通过ast语法转义后生成的render方法
    };
  }

  function callHook(vm, hook) {
    var handlers = vm.$options[hook];
    console.log(handlers);
    if (handlers) {
      handlers.forEach(function (handler) {
        handler.call(vm);
      });
    }
  }
  function mountComponent(vm, el) {
    //这里的el是通过querySelector处理过的
    vm.$el = el;
    //调用render方法产生虚拟DOM
    var updateComponent = function updateComponent() {
      vm._updata(vm._render());
    }; //vm.$options.render()渲染虚拟结点,vm._update()生成真实DOM
    // 根据虚拟DOM产生真实DOM
    // 3.插入到el元素中
    new Watcher(vm, updateComponent, true); //这里的true标识着一个渲染过程
    // console.log(watcher);
  }

  function mergeOptions() {
    var ops = arguments.length > 0 && arguments[0] !== undefined ? arguments[0] : {};
    var mixin = arguments.length > 1 ? arguments[1] : undefined;
    // 创建一个空对象作为合并后的结果
    var options = {};
    // 定义一个合并策略对象，存放不同属性名对应的合并策略函数
    var strats = {};
    // 定义一个默认的合并策略函数，如果没有找到对应的策略函数，就使用它
    var defaultStrat = function defaultStrat(parentVal, childVal) {
      // 如果子选项有值，就使用子选项的值，否则就使用父选项的值
      return childVal === undefined ? parentVal : childVal;
    };
    // 定义一个合并字段的函数，用于遍历属性并调用合并策略函数
    function mergeField(key) {
      // 根据属性名查找合并策略对象，如果没有找到，就使用默认的合并策略函数
      var strat = strats.hasOwnProperty(key) ? strats[key] : defaultStrat;
      // 调用合并策略函数，传入父选项和子选项的属性值，以及当前的属性名
      options[key] = strat(ops[key], mixin[key], key);
    }
    // 遍历父选项的所有属性，并调用合并字段的函数
    for (var key in ops) {
      mergeField(key);
    }
    // 遍历子选项的所有属性，并调用合并字段的函数
    for (var _key in mixin) {
      // 如果父选项没有该属性，才需要调用合并字段的函数
      if (!Object.hasOwn(ops, _key)) {
        mergeField(_key);
      }
    }
    // 返回合并后的结果对象
    return options;
  }

  function initMixin(Vue) {
    //给Vue 增加init方法
    Vue.prototype._init = function (options) {
      //用于初始化操作
      //vue vm.$options 就是获取用户的配置 
      var vm = this; //
      vm.$options = mergeOptions(this.constructor.options, options); //把用户配置赋值给vm.,挂载到vm身上 使用$标识表示这是vue里面的
      callHook(vm, 'beforeCreate');
      //初始化状态
      initState(vm);
      callHook(vm, 'created');
      //判断是否由el属性
      if (options.el) {
        vm.$mount(options.el); //挂载 
      }
    };

    Vue.prototype.$mount = function (el) {
      var vm = this;
      el = document.querySelector(el);
      var op = vm.$options;
      if (!op.render) {
        //如果没有render函数
        var template; //没有render看是否写了template。没有写template采用外部的template
        if (!op.template && el) {
          //没有模版但是有el
          template = el.outerHTML;
        } else {
          template = op.template; //如果有el则采用模版
        }
        // console.log(template);
        if (template) {
          //存在模版就对模版进行编译
          var render = compileToFunction(template);
          op.render = render; //把编译后的render函数赋值给render
        }
      }
      // console.log(op.render);
      mountComponent(vm, el); //组件挂载

      //script标签引用的vue.global.js这个编译过程是在浏览器进行的，runtime是不包含模版编译的，整个编译是打包的时候通过loader来转义.vue文件的
      //用runtime的时候不能使用template模版的
    };
  }

  function initGlobalAPI(Vue) {
    // config
    var configDef = {};
    configDef.get = function () {
      return config;
    };
    Object.defineProperty(Vue, 'config', configDef);

    // exposed util methods.
    // NOTE: these are not considered part of the public API - avoid relying on
    // them unless you are aware of the risk.

    // 2.6 explicit observable API
    Vue.observable = function (obj) {
      observe(obj);
      return obj;
    };
    Vue.options = Object.create(null);

    // this is used to identify the "base" constructor to extend all plain-object
    // components with in Weex's multi-instance scenarios.
    Vue.options = {
      _base: Vue
    };
    Vue.mixin = function (mixin) {
      this.options = mergeOptions(this.options, mixin);
      return this;
    };
    Vue.extend = function (options) {
      //实现根据用户的参数返回一个构造函数
      function Sub() {
        var options = arguments.length > 0 && arguments[0] !== undefined ? arguments[0] : {};
        //调用Vue的构造函数
        this._init(options);
      }
      Sub.prototype = Object.create(this.prototype); //Sub.protoytype.__proto__ = Vue.protoType
      Sub.prototype.constructor = Sub;
      //将用户传递的参数和全局的Vue.options来合并
      Sub.options = mergeOptions(Vue.options, options);
      return Sub;
    };
    Vue.options.components = {}; //全局的指令  Vue.options.directives
    Vue.components = function (id, definition) {
      //如果是函数直接返回，不是函数就进行包装
      definition = typeof definition === 'function' ? definition : Vue.extend(definition);
      Vue.options.components[id] = definition;
    };
  }

  //将所有的方法耦合在一起
  function Vue(options) {
    //options就是用户的选项
    this._init(options); //初始化操作
  }

  initMixin(Vue); //扩展了init方法 
  initLifeCycle(Vue); //扩展了生命周期方法
  initGlobalAPI(Vue);
  initStateMixin(Vue); //实现了nextTick和$watch

  return Vue;

}));
//# sourceMappingURL=vue.js.map
