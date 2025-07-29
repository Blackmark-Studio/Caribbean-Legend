// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你提供什么帮助, " + GetAddress_Form(NPChar) + "? "), "你不久前刚问过我问题, " + GetAddress_Form(NPChar) + "... ", "一整天下来, 这已经是你第三次问这类问题了... ",
                          "我猜你又有问题要问? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么想聊的。 "), "嗯, 我的记性哪去了... ",
                      "是的, 确实是第三次了... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            //Jason, 传奇, 过往阴影
            if (CheckAttribute(PChar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "sentjons")
            {
                link.l1 = "我在找雷蒙德.贝克, 一个前刽子手。 你知道他是否还活着, 我在哪里可以找到他吗? ";
                link.l1.go = "baker";
            }
            //Jason, 海龟汤
            if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
            {
                link.l1 = "我在找琼斯先生。 伙计, 你能帮我找找吗? ";
                link.l1.go = "terrapin";
            }
            // 真理守卫
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok")
            {
                link.l1 = "听着, 有没有一个炼金术士, 或者说医生, 到这个镇上来? 他是意大利人, 三十岁左右, 名叫吉诺.格维内利。 你听说过吗? ";
                link.l1.go = "guardoftruth";
            }
        break;
        
        //传奇, 过往阴影
        case "baker":
            dialog.text = "我们亲爱的胖子现在比福克斯上校还受欢迎! 他还活着, 可怜的家伙。 但他现在不在镇上。 雷蒙德发现像你这样的重要人物在关注他后, 就匆匆忙忙把他的破房子贱卖了, 然后就消失得无影无踪。 ";
            link.l1 = "无影无踪? 去哪里了? ";
            link.l1.go = "baker_1";
        break;
        
        case "baker_1":
            dialog.text = "哦, 谁知道呢。 他随第一艘来的船去当船上的医生了。 只是那艘船今天刚回来, 还没人看见贝克上岸。 ";
            link.l1 = "我怎么找到船长? ";
            link.l1.go = "baker_2";
        break;
        
        case "baker_2":
            dialog.text = "你为什么觉得需要找他? 我敢肯定他已经在船舱里喝得酩酊大醉了。 他那艘破船叫‘卡洛韦.梅吉’。 什么样的船长, 就有什么样的船名... ";
            link.l1 = "谢谢你的帮助, 伙计! ";
            link.l1.go = "baker_3";
        break;
        
        case "baker_3":
            DialogExit();
            AddQuestRecord("Shadows", "2");
            pchar.questTemp.Saga.Shadows = "baldmaggy";
            pchar.quest.Saga_ShadowsMaggy.win_condition.l1 = "location";
            pchar.quest.Saga_ShadowsMaggy.win_condition.l1.location = "Antigua";
            pchar.quest.Saga_ShadowsMaggy.function = "Saga_SetBaldMaggy";
        break;
        
        //海龟汤
        case "terrapin":
            dialog.text = "琼斯先生? 你在开玩笑吧, 伙计。 你知道这个岛上有多少该死的琼斯吗? 你得说得更具体一点。 ";
            link.l1 = "他有个成年姐姐莫莉。 人们说她美极了。 ";
            link.l1.go = "terrapin_1";
        break;
        
        case "terrapin_1":
            dialog.text = "不, 我没想到有这样的人。 抱歉, 伙计... ";
            link.l1 = "好吧, 如果你不知道, 那就是不知道... ";
            link.l1.go = "exit";
            npchar.quest.terrapin = "true";
        break;
        
        case "guardoftruth":
            dialog.text = "不, 我没听说过。 我们镇上只有一个炼金术士, 药剂师约翰.默多克。 他有神奇的药水 —能治愈任何疾病。 ";
            link.l1 = "你觉得这些药水是他自己配制的吗? ";
            link.l1.go = "guardoftruth_1";
        break;
        
        case "guardoftruth_1":
            dialog.text = "问得好。 我时不时会问自己这个问题。 约翰一点也不像个精通医学器皿。 草药和药粉的人。 他更像个退役士兵, 一个雇佣兵... 这更接近事实。 ";
            link.l1 = "嗯, 我想这个人有点大材小用了... ";
            link.l1.go = "guardoftruth_2";
        break;
        
        case "guardoftruth_2":
            dialog.text = "也许吧。 但有一件事我可以肯定, 他的二楼住着某个人。 窗户总是挂着窗帘。 即使约翰在楼下, 也会有玻璃小瓶和瓶子的叮当声, 还有煮草药的味道, 而且晚上灯也不熄。 所以我怀疑那个房间的居住者才是为约翰配制待售药品的人。 ";
            link.l1 = "嗯。 观察得很有趣。 谢谢你, 伙计! ";
            link.l1.go = "exit";
            pchar.questTemp.Guardoftruth = "merdok1";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}