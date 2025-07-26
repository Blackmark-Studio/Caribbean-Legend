// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            if(startHeroType == 4)
            {
                dialog.text = NPCStringReactionRepeat("当然了, 海伦。 什么事? ", "啊, 终于想起你想问什么了? ", "你确定没事吗? 你开始让我担心了。 也许该去看医生? ",
                              "好吧, 海伦。 睡一觉, 呼吸点新鲜空气 --总之休息一下, 然后再来。 嗯? ", "block", 1, npchar, Dialog.CurrentNode);
                link.l1 = HeroStringReactionRepeat("不, 没什么事。 ", "不, 不, 抱歉打扰你了。 ",
                          "你或许说得对... ", "是的, 你或许说得对。 这是最好的办法。 ", npchar, Dialog.CurrentNode);
                link.l1.go = "exit";
            }
            else
            {
                dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你提供什么帮助, " + GetAddress_Form(NPChar) + "? "), "你不久前刚问过我问题, " + GetAddress_Form(NPChar) + "... ", "一整天下来, 这已经是你第三次问这类问题了... ",
                              "我猜你又有问题要问? ", "block", 1, npchar, Dialog.CurrentNode);
                link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么想聊的。 "), "嗯, 我的记性哪去了... ",
                          "是的, 确实是第三次了... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
                link.l1.go = "exit";
            }
            if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
            {
                link.l1 = "听着, " + npchar.name+ ", 谁是扬.斯文森, 我怎么才能找到他? ";
                link.l1.go = "Svenson";
            }    
            //<—— 加斯科涅人的负担
            // 真理守卫
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
            {
                link.l1 = "听着, 有没有一个炼金术士, 或者说医生, 到这个镇上来? 他是意大利人, 三十岁左右, 名叫吉诺.格维内利。 你听说过吗? ";
                link.l1.go = "guardoftruth";
            }
        break;
        
        case "Svenson":
            dialog.text = "我第一次遇到有人不认识‘森林恶魔’。 这绰号是西班牙人给他起的, 十五年前他们曾悬赏 一 整袋黄金要这个普罗维登斯岛私掠者的头颅! 是啊, 岁月飞逝... 人们已经开始忘记我们的扬了。 也许他真的该休息了。 ";
            link.l1 = "我刚到这里, 知道的不多... ";
            link.l1.go = "Svenson_1";            
        break;
        
        case "Svenson_1":
            dialog.text = "如果你对过去感兴趣, 我可以卖给你一本历史书。 很多人会为此一掷千金, 但我... ";
            link.l2 = "别跟我兜圈子! 我问了你一个问题, 我重复一遍: 扬.斯文森住在哪里? 我有要事找他谈。 ";
            link.l2.go = "Svenson_2";
        break;
        
        case "Svenson_2":
            dialog.text = "他住在镇长宅邸对面的大宅里, 喷泉旁边。 但他现在正经历困难时期, 除非事情极其重要, 否则我不建议去打扰他。 ";
            link.l1 = "为什么? ";
            link.l1.go = "Svenson_3";            
        break;
        
        case "Svenson_3":
            dialog.text = "他最疼爱的女孩海伦, 人称‘伦巴’, 是他已故老友肖恩.麦卡瑟的女儿, 愿老人安息... 扬把这个小恶魔视如己出, 因为他自己没有孩子。 但这女孩连同她的纵帆船‘彩虹号’和全体船员一起消失了。 我为这女孩感到难过。 她是个罕见的美人, 也很聪明。 热情似火, 所以才叫她‘伦巴’! 她父亲把毕生所学都教给了她, 她继承了那艘船, 所有船员都留在了她身边, 连最老的航海老手都认可她当船长... ";
            link.l1 = "一位女海盗? 她可能出了什么事? ";
            link.l1.go = "Svenson_4";            
        break;
        
        case "Svenson_4":
            dialog.text = "谁知道呢... 一周时间不算长, 但麦卡瑟的遗孀坚信女儿出事了, 而且她说服了斯文森。 他召集人手, 亲自搜寻, 但至今没有结果。 ‘彩虹号’和船员就这么消失了。 给我一千枚八里亚尔银币, 我就告诉你去哪里找格拉迪斯。 ";
            if (sti(pchar.money) >= 1000)
            {
                link.l1 = "你的情报可真贵, 但你勾起了我的兴趣。 给你钱。 我去哪里找她? ";
                link.l1.go = "Svenson_5";
            }
            else
            {
                link.l1 = "不必了。 如果需要, 我会自己处理。 再见, 谢谢你的故事! ";
                link.l1.go = "Svenson_6";
            }        
        break;
        
        case "Svenson_5":
            AddMoneyToCharacter(pchar, -1000);
            dialog.text = "她的家在码头旁边, 停泊处左边。 但她可能不在家。 她整天都在堡垒墙边徘徊, 守望她心爱的女儿, 恐怕眼泪都快哭干了。 ";
            link.l1 = "谢谢你的故事! 再见, 伙计! ";
            link.l1.go = "Svenson_6";            
        break;
        
        case "Svenson_6"://将格拉迪斯设置到堡垒
            DialogExit();
            ref sld = characterFromId("Gladis");
            ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
            LAi_SetStayType(sld);
            sld.dialog.currentnode = "FindHelena";
            pchar.questTemp.Saga = "gladis";
            sld = characterFromId("JS_girl");
            sld.dialog.currentnode = "js_girl_8";
            DelLandQuestMark(npchar);
            DelLandQuestMark(characterFromId("JS_girl"));
            DelMapQuestMarkCity("SantaCatalina");
        break;
        
        case "guardoftruth":
            dialog.text = LinkRandPhrase("不, 没见过。 我们有草药师和医生, 但没有叫这个名字的。 ","我第一次听到这么奇怪的名字。 不, 从来没有你说的那个人来过。 ","我们这里根本没有炼金术士, 只有医生, 但没有叫这么奇怪名字的。 ");
            link.l1 = "明白了, 真遗憾。 我会继续寻找! ";
            link.l1.go = "exit";
            npchar.quest.jino = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}