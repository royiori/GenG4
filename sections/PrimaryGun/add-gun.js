const gunTable = document.getElementById('gunTable')

//____________________________________________________________
// Particle Gun页面的控制数据
// "显示标签", "控件种类", "初始化数据", "id/保存进setting的key", "class/根据此来进行输入量检查"
gunContent = {
    "ptype" : ["Type:", "dropdown", "GunType", "GunType", ""],
    "energy": ["Energy:", "input-text", "", "GunEnergy", "parmWithEngUnit"],
    "particle": ["Particle:", "dropdowngrp", "ParticleList", "GunParticle", "gunparticle"],
    "position": ["Position:", "input-text", "", "GunPosition", "parmVector"],
    "direction": ["Direction:", "input-text", "", "GunDirection", "parmVector"],
}

//_________________________________________________
//DOM的事件处理函数，对ID进行响应
//注意调用顺序，必须先调用class对应的函数，再调用ID对应的函数
//1. ID = ParticleList的事件响应
function particleListListener(evt, params) {
    if (!this.eventList) eventList = 0
    if (this.eventList > 1) this.removeEventLisener('change', particleListListener)

    select = clone(params.selected)
    //regex1 = /\(.+(?=\))/g     //.表示任意字符，+表示出现次数至少1次， javascript不支持后行断言，所以输出会包含一个前括号（
    //selcon = select.match(regex1)
    left = select.indexOf('(')
    right= select.indexOf(')')
    select = select.substring(left+1, right)

    energy = document.getElementById("GunEnergy")
    energy.value = select
    store(energy.id, select)
    store(this.id, params.selected)
    this.eventList++
}



