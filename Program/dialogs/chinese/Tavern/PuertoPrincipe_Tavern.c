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
            //-->旧账
            if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
            {
                link.l1 = "听说有人偷了你珍贵的杜松子酒。 难道是谣言吗? ";
                link.l1.go = "OS_Tavern1_1";
            }
            if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
            {
                link.l1 = "好消息, " + npchar.name+ "! 我找回了你的木桶! ";
                link.l1.go = "OS_Tavern3_1";
            }
        //<--旧账
        break;

        //-->旧账
        case "OS_Tavern1_1":
            dialog.text = "老天啊, 是真的。 你还听说了什么? 你知道些什么吗? 我求你了, 说你知道去哪里找它。 如果我找不回来... 我要么自己溜出这个镇, 要么就装在松木盒子里被抬出去。 ";
            link.l1 = "的确, 朋友, 你的处境看起来很糟糕。 不, 我只是听到了一些关于你遭遇不幸的传言。 这么贵重的货物怎么会从你手里溜走的? ";
            link.l1.go = "OS_Tavern1_2";
            DelLandQuestMark(npchar);
        break;

        case "OS_Tavern1_2":
            dialog.text = "该死的... 我能说什么? 就在我眼皮底下被偷了! 早上木桶肯定还在这里。 它是两天前运到的, 为了安全起见, 我晚上把它带回家了。 早上我把它带回来, 藏在柜台下面。 到了晚上, 它就无影无踪了! 根本没人看到或听到任何动静。 ";
            link.l1 = "好吧, 真该死... ";
            link.l1.go = "OS_Tavern1_3";
        break;

        case "OS_Tavern1_3":
            dialog.text = "要是我有一点点线索, 我早就去追了。 但唉, 什么都没有 --好像那个木桶太精美了, 不属于这个凡间, 被天堂收走了。 谁把它带回来, 我就付一百五十枚达布隆。 不仅如此, 我还会在我的酒馆里挂一块刻有他们名字的牌匾, 让所有人都知道他们的英雄事迹! ";
            link.l1 = "我会看看我能做什么。 我们稍后再谈这块牌匾的事。 先告诉我谁知道这个木桶? 除了你之外, 还有谁可能在柜台后面? ";
            link.l1.go = "OS_Tavern1_4";
            link.l2 = "一个木桶一百五十枚达布隆? 真有趣。 但你的麻烦不是我的。 你自己解决吧。 ";
            link.l2.go = "OS_Tavern1_end";
        break;

        case "OS_Tavern1_end":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
            CloseQuestHeader("OS");

            for (i=1; i<=3; i++)
            {
                if (CharacterIsAlive("OS_Matros_"+i))
                {
                    sld = CharacterFromID("OS_Matros_"+i);
                    sld.lifeday = 0;
                }
            }
            sld = CharacterFromID("OS_Pirate");
            sld.lifeday = 0;
        break;

        case "OS_Tavern1_4":
            dialog.text = "几乎没人! 也许除了我的女服务员, 但那不可能。 那天酒馆里热闹非凡 --‘海兽号’的船员带着丰厚的战利品打猎回来了。 她一刻也没休息, 更别说有时间溜到我柜台后面了。 ";
            link.l1 = "你确定吗? ";
            link.l1.go = "OS_Tavern1_5";
        break;

        case "OS_Tavern1_5":
            dialog.text = "毫无疑问! 不停地工作不符合她的脾气, 到了晚上她就紧张得像弹簧一样。 当一个水手对她示好时, 她大吵大闹, 几乎把整个酒馆的人都吵聋了。 我不得不离开岗位去维持秩序。 不过奇怪的是 --她通常处理这种示好要冷静得多。 ";
            link.l1 = "就这些吗? 那天没有其他不寻常的事了? ";
            link.l1.go = "OS_Tavern1_6";
        break;

        case "OS_Tavern1_6":
            dialog.text = "当我平息第一次骚动时, 另一场骚动又爆发了 --两个水手在角落里打了起来。 不过打斗没持续多久; 他们好像是同船的伙伴, 很快就被分开了。 在那之后, 一切真的平静下来了, 没有什么值得一提的了。 ";
            link.l1 = "很好, 我会开始搜索。 等等。 我想很快木桶就会回到你, 咳咳... 警惕的目光下了。 ";
            link.l1.go = "OS_Tavern1_7";
        break;
        //<--旧账
        
        case "OS_Tavern1_7":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
            AddQuestRecord("OS", "2");
			
            sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
            sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
            sld.dialog.currentnode = "OS_Matros";
            LAi_SetImmortal(sld, true);
            sld.City = "PuertoPrincipe";
            ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
            LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
            AddLandQuestMark(sld, "questmarkmain");
        break;
        
        case "OS_Tavern3_1":
            dialog.text = "你找到了? ! 真的吗? 船长, 你救了我的命! 是谁干的? 我必须知道那个恶棍的名字! ";
            link.l1 = "这是一个精心策划的阴谋, 由一个叫杰克.维尔斯的人策划, 与‘海兽号’的船长合作。 他们招募了他们的水手, 上演了一场精心策划的转移注意力的戏码, 把你引开。 当你离开岗位时, 木桶无人看管, 他们很容易就把它偷走了。 ";
            link.l1.go = "OS_Tavern3_2";
            DelLandQuestMark(npchar);
            pchar.questTemp.CameraDialogMode = true;
        break;

        case "OS_Tavern3_2":
            dialog.text = "天哪! 杰克.维尔斯! 这么说他回来了... 看来他是想通过这种卑鄙的手段夺回酒馆。 那只狐狸从不认输! ";
            link.l1 = "这么说他曾经是这家店的老板? 放心, 他不会再耍阴谋了。 我已经送他去见造物主了。 ";
            link.l1.go = "OS_Tavern3_3";
        break;

        case "OS_Tavern3_3":
            dialog.text = "船长! 这太不可思议了! 你... 你把我从一直笼罩着我的恐惧中解放出来了! 我就知道他迟早会回来的... 几年前, 我们是这家酒馆的竞争对手, 他设法打败了我\n但胜利的喜悦却成了他的祸根 --在庆祝的狂欢中, 他不知不觉地把这个地方通过扑克牌赌给了我。 当然, 第二天早上, 他跑来找我, 乞求收回酒馆, 答应什么都给我\n但我还没傻到同意这样的条件。 然后他就消失了... 我知道他不会就此罢休。 我感觉他总有一天会回来。 现在, 这一天来了。 ";
            link.l1 = "该表扬的还是要表扬 --他的计划执行得很狡猾。 ";
            link.l1.go = "OS_Tavern3_4";
        break;

        case "OS_Tavern3_4":
            dialog.text = "等一下! 他怎么会知道木桶的事? 看来... 看来我开始明白了! 那个女服务员! 这就是为什么她像被烫伤的猫一样逃走了, 连一声告别都没有。 她一定是听说你已经解决了杰克。 现在一切都清楚了。 船长, 我欠你的恩情无法衡量, 你... ";
            link.l1 = "... ";
            link.l1.go = "OS_Tavern3_5";
        break;
        
        case "OS_Tavern3_5":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
            ChangeShowIntarface();
			
            sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
            sld.name = GetCharacterName("Zachary");
            sld.lastname = GetCharacterName("Marlow");
            ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
            TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
            sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
            sld.dialog.currentnode = "Zaharia_1";
            LAi_SetActorType(sld);
            LAi_ActorDialog(sld, pchar, "", 0, 0);
        break;
		
		
        //<--旧账
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}