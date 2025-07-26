// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch(Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = "说吧, 我在听";
            link.l1 = "我搞错了。 再见。 ";
            link.l1.go = "Exit";
            
            // --> Sinistra 旧罪的漫长阴影
            if(CheckAttribute(pchar, "questTemp.DTSG_AntiguaZalog"))
            {
                link.l1 = "最近, 城里的一名士兵逮捕并关押了查理.克尼佩尔。 他还在这里吗? "; 
                link.l1.go = "DTSG_AntiguaZalog_2";
            }
            // <—— 旧罪的漫长阴影
        break;
        
        // --> Sinistra 旧罪的漫长阴影
        case "DTSG_AntiguaZalog_2":
            dialog.text = "没错, 但你为什么问这个? ";
            link.l1 = "事情是这样的, 查理是我的一名军官。 我想知道他被指控了什么。 逮捕他的士兵什么也没告诉我。 "; 
            link.l1.go = "DTSG_AntiguaZalog_3";
            DelLandQuestMark(npchar);
        break;
        
        case "DTSG_AntiguaZalog_3":
            dialog.text = "对。 这不是公开的消息。 不幸的是, 对你也是如此。 这是国家机密, 先生。 ";
            link.l1 = "那么, 我想保释是不可能的了? "; 
            link.l1.go = "DTSG_AntiguaZalog_4";
        break;
        
        case "DTSG_AntiguaZalog_4":
            dialog.text = "正是。 我知道失去一个有价值的船员很不愉快, 但你我都无能为力。 非常抱歉, 船长。 ";
            link.l1 = "不能保释, 我明白了。 那么... 补偿呢? 我可以多给一些。 给你和你所有的人, 这样没人会被落下。 "; 
            link.l1.go = "DTSG_AntiguaZalog_5";
        break;
        
        case "DTSG_AntiguaZalog_5":
            dialog.text = "贿赂? 你胆子真大, 船长, 但再多的钱也无法让我们免受那些发现我们放了查理的人的愤怒。 ";
            link.l1 = "也许... 但我至少能和他谈谈吗? "; 
            link.l1.go = "DTSG_AntiguaZalog_6";
        break;
        
        case "DTSG_AntiguaZalog_6":
            dialog.text = "为什么不呢? 你救不了他, 也帮不了他逃跑, 所以... 去吧。 他在其中一个牢房里。 ";
            link.l1 = "哈, 如果他告诉我他被指控了什么, 并透露了你如此担心的那个国家机密呢, 军官? "; 
            link.l1.go = "DTSG_AntiguaZalog_7";
        break;
        
        case "DTSG_AntiguaZalog_7":
            dialog.text = "我不担心那个。 你会明白为什么的。 在我改变主意之前, 去和你以前的军官谈谈吧。 ";
            link.l1 = "谢谢你。 "; 
            link.l1.go = "DTSG_AntiguaZalog_8";
        break;
        
        case "DTSG_AntiguaZalog_8":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
            pchar.questTemp.jailCanMove = true;
            
            sld = CharacterFromID("Knippel");
            LAi_SetActorType(sld);
            ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
            
            sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
            sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
            sld.dialog.currentnode = "DTSG_Killer";
            LAi_SetStayType(sld);
            sld.talker = 5;
            GiveItem2Character(sld, "blade_14");
            EquipCharacterbyItem(sld, "blade_14");
            GiveItem2Character(sld, "pistol4");
            EquipCharacterbyItem(sld, "pistol4");
            AddItems(sld, "purse2", 1);
            sld.SaveItemsForDead = true;
            sld.DontClearDead = true;
            ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
            sld.rank = 30;
            SetSelfSkill(sld, 80, 80, 80, 80, 80);
            LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
            LAi_SetImmortal(sld, true);
        break;
        
        case "DTSG_AntiguaTrevoga_2":
            dialog.text = "没必要, 船长。 正如我所说, 你会和那个傻瓜查理被扔进同一个牢房。 但是, 首先, 总督欣赏你没有抗拒逮捕, 其次, 他对放债人最近的来访很不高兴, 那人的尖叫几乎震碎了宫殿的窗户... ";
            link.l1 = "他要求逮捕我? "; 
            link.l1.go = "DTSG_AntiguaTrevoga_3";
            DelLandQuestMark(npchar);
        break;
        
        case "DTSG_AntiguaTrevoga_3":
            dialog.text = "他不是要求 --而是命令。 总督阁下不喜欢被人命令任何事情。 因此, 那个高利贷者被赶了出去。 ";
            link.l1 = "真有趣。 现在... "; 
            link.l1.go = "DTSG_AntiguaTrevoga_4";
        break;
        
        case "DTSG_AntiguaTrevoga_4":
            dialog.text = "现在我建议你也这么做, 德莫尔船长。 不要问你不会得到答案的问题。 ";
            link.l1 = "没有查理.克尼佩尔, 我不会离开这里。 "; 
            link.l1.go = "DTSG_AntiguaTrevoga_H1";
            link.l2 = "求求你, 先生, 让我和查理.克尼佩尔谈谈。 或者至少知道什么... "; 
            link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
        break;
        
        case "DTSG_AntiguaTrevoga_H1":
            dialog.text = "既然如此, 那就和他一起。 不是在牢房里, 而是在来生。 ";
            link.l1 = "这么说, 他死了... "; 
            link.l1.go = "DTSG_AntiguaTrevoga_H2";
            ChangeCharacterComplexReputation(pchar, "authority", 1);
        break;
        
        case "DTSG_AntiguaTrevoga_H2":
            dialog.text = "你真敏锐, 船长。 我希望你意识到我不会告诉你是谁干的, 也不会告诉你为什么。 ";
            link.l1 = "是这样吗? "; 
            link.l1.go = "DTSG_AntiguaTrevoga_H3";
        break;
        
        case "DTSG_AntiguaTrevoga_H3":
            dialog.text = "正是。 现在不要考验我的耐心 --在我下令把你扔进牢房, 因为你杀了一名英国士兵之前。 ";
            link.l1 = "考虑到没有多少人能从你的牢房里出来, 我可不想死在那里。 我就不祝你今天愉快了。 "; 
            link.l1.go = "DTSG_AntiguaTrevoga_5";
        break;
        
        case "DTSG_AntiguaTrevoga_Ch1":
            dialog.text = "查理.克尼佩尔不会和任何人说话。 也许除了造物主... ";
            link.l1 = "他死了? "; 
            link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
        break;
        
        case "DTSG_AntiguaTrevoga_Ch2":
            dialog.text = "判决已经执行。 我不能给你任何细节。 我希望你不要坚持 --这可能会给你带来不好的结果。 不仅仅是进牢房。 我说清楚了吗, 德莫尔船长? ";
            link.l1 = "非常清楚。 再见。 "; 
            link.l1.go = "DTSG_AntiguaTrevoga_5";
        break;
        
        case "DTSG_AntiguaTrevoga_5":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
            AddQuestRecord("DTSG", "10");
            CloseQuestHeader("DTSG");
            ChangeCharacterComplexReputation(pchar, "authority", -10);
            AddCrewMorale(Pchar, -30);
        break;
        // <-- 旧罪的漫长阴影
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}