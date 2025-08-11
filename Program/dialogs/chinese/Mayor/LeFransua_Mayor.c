// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? 问吧。 ", "我在听, 你有什么问题? "), "这是你第二次尝试提问... ", "这是你第三次尝试提问... ",
                          "这要到什么时候才结束? ! 我是个忙人, 在处理殖民地事务, 而你还在烦我! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不行。 地点和时间不对。 "), "确实... 但以后吧, 不是现在... ",
                      "我会问... 但过一会儿... ", "抱歉, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";

            if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
            {
                if (CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
                {
                    link.l1 = "我想谈谈你的囚犯。 ";
                    link.l1.go = "CapComission1";
                    DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
                }    
                if (CheckAttribute(pchar, "GenQuest.CaptainComission.PirateShips"))
                {
                    link.l1 = "你好, " + Npchar.name+ ", 我来是为了你的囚犯。 ";
                    link.l1.go = "CapComission3";
                }
                if (CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
                {
                    link.l1 = "我想谈谈你的囚犯。 ";
                    link.l1.go = "CapComission6";
                }
            }
            if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
            {
                link.l1 = "我听说你在做与囚犯相关的生意... ";
                link.l1.go = "Marginpassenger";
            }
        break;
        
        
        case "CapComission1":
            dialog.text = "哈哈。 你以为我这里只有一个囚犯吗? 说出他的名字。 ";
            link.l1 = pchar.GenQuest.CaptainComission.SlaveName + "。 他在这里吗? ";
            link.l1.go = "CapComission2";
        break;

        case "CapComission2":
            if (CheckAttribute(pchar, "GenQuest.CaptainComission.DaysLeft"))
            {
                dialog.text = "他之前在这。 一周前巴巴多斯的种植园主毕晓普上校来的时候, 我把他卖给了对方。 ";
                link.l1 = "该死... ";
                link.l1.go = "CapComission2_1";
            }
            else
            {
                pchar.quest.CaptainComission_SellSlave.over = "yes";
                dialog.text = "啊, 终于来了。 我正打算把他卖给巴巴多斯的种植园主, 他一两周后会来... 你有赎金" + GetSexPhrase("", "") + "吗? ";
                link.l1 = "听着, " + Npchar.name+ ", 有个小问题... 其实我没那么多钱。 但我愿意干活抵账。 ";
                link.l1.go = "CapComission2_2";
                if (makeint(pchar.money) > 150000)
                {
                    link.l2 = "幸好你还没卖掉他。 这是15万比索。 我去哪儿接他? ";
                    link.l2.go = "CapComission2_3";
                }    
            }
        break;
        
        case "CapComission2_1":
            dialog.text = "你太慢了... 你为什么关心他? 我之前只和他的亲属谈判过。 ";
            link.l1 = "是他们让我来的。 ";
            link.l1.go = "CapComission2_11";
        break;
        
        case "CapComission2_11":
            dialog.text = "好吧, 你迟到了。 我无能为力。 ";
            link.l1 = "听着, 如果不是秘密的话, 你把他卖了多少钱? ";
            link.l1.go = "CapComission2_12";
        break;
        
        case "CapComission2_12":
            dialog.text = "呃, 这不是秘密。 但我不会告诉你... 我说了你会笑的。 哈哈哈哈! 再见。 ";
            link.l1 = "再见。 ";
            link.l1.go = "exit";
            AddQuestRecord("CaptainComission1", "10");
            AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
            CaptainComission_GenerateManager();
        break;
        
        case "CapComission2_2":
            if (rand(1) == 0)
            {
                dialog.text = "好吧, 好吧... 我有件事... 甚至不知道怎么开口。 我需要解决一个太过分的海盗。 ";
                link.l1 = "不能在丛林里直接解决他吗? ";
                link.l1.go = "CapComission2_2_1";
            }
            else
            {
                dialog.text = "好吧, " +pchar.name+ ", 你知道, 事情不是那样的。 带钱回来你就能带走那个弱者, 哈哈。 ";
                link.l1 = "好吧, 那再见。 ";
                link.l1.go = "exit";
                if (!CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
                {
                    AddQuestRecord("CaptainComission1", "31");
                    AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
                }    
                pchar.GenQuest.CaptainComission.RepeatSpeak = true;
            }
        break;

        case "CapComission2_2_1":
            dialog.text = "你知道, 这不是生意的做法... 我不需要他死, 我需要让某些人知道别碰我的战利品。 但如果他去喂鲨鱼, 我也不会难过。 ";
            link.l1 = "你为什么不派自己的人去? ";
            link.l1.go = "CapComission2_2_2";
        break;
        
        case "CapComission2_2_2":
            CaptainComission_GetRandomShore();
            pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
            pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
            pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
            dialog.text = "嗯... 好吧, " + GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " 说服了一些海盗, 让他们相信战利品会藏在我们离 " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + " 不远的藏匿点。 他们的两艘船‘" + pchar.GenQuest.CaptainComission.ShipName1 + "’和‘" + pchar.GenQuest.CaptainComission.ShipName2 + "’刚起锚驶向 " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl") + "。 现在你明白为什么我不能信任我的人去做这件事了吧? ";
            link.l1 = "我明白了。 我有多少时间? ";
            link.l1.go = "CapComission2_2_3";
        break;
        
        case "CapComission2_2_3":
            dialog.text = "12到15天, 不能更多了。 重要的是他们不能到藏匿点, 如果他们带着贵重货物, 击沉他们就没意义了。 这种情况下, 最好让他们把货物带到这里... ";
            link.l1 = "好的, 我接了。 我会试着抓住他们。 ";
            link.l1.go = "exit";
            AddQuestRecord("CaptainComission1", "24");
            AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
            AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
            AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
            AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
            AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
            pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
            SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);    
            pchar.GenQuest.CaptainComission.PirateShips = "goaway";    
        break;
        
        case "CapComission2_3":
            dialog.text = "别担心。 我的人会把他送到你的船上。 你为什么关心他? ";
            link.l1 = "我不关心。 是他的亲属让我来接他的。 ";
            link.l1.go = "CapComission2_31";
        break;
        
        case "CapComission2_31":
            dialog.text = "啊, 那好吧。 我几乎要为给你那人这么低的价格感到抱歉了。 哈哈哈哈。 再见。 ";
            link.l1 = "再见。 ";
            link.l1.go = "exit";
            AddQuestRecord("CaptainComission1", "9");
            AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
            AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
            AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));            
            addMoneyToCharacter(pchar, -150000);
            AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");    
        break;
        
        case "CapComission3":
            dialog.text = "好吧, " +GetFullName(pchar)+ ", 你解决了我的人吗? 嘿嘿嘿... ";
            if (pchar.GenQuest.CaptainComission.PirateShips == "goaway")
            {
                link.l1 = "没有。 我没抓住他们。 回来的路上也没遇到。 ";
                link.l1.go = "CapComission4";
            }
            else
            {
                if (pchar.GenQuest.CaptainComission.PirateShips == "died")    
                {
                    link.l1 = "解决了。 我把他们送去喂鲨鱼了。 ";
                    link.l1.go = "CapComission5";
                }
            }    
            DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
        break;
        
        case "CapComission4":
            dialog.text = "该死! 不管了, 现在不重要了! 你接下来有什么提议? ";
            link.l1 = "也许你有更简单的活给我? ";
            link.l1.go = "CapComission4_1";
            link.l2 = "听着, " + Npchar.name+ ", 把囚犯的价格降下来... ";
            link.l2.go = "CapComission4_2";
        break;
        
        case "CapComission4_1":
            dialog.text = "没有。 ";
            link.l1 = "那再见... ";
            link.l1.go = "exit";
            ChangeCharacterComplexReputation(pchar, "nobility", -2);
            AddQuestRecord("CaptainComission1", "27");
            AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
            AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
            AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
            AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
            DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");            
        break;
        
        case "CapComission4_2":
            dialog.text = "降价? ! 就因为你的无能, 我刚丢了藏匿点! 现在我可以涨价! 如果你想要, 就付20万比索, 否则滚出去! ";
            link.l1 = "太贵了... 再见... ";
            link.l1.go = "CapComission4_4";
            if (sti(pchar.money) >= 200000)
            {
                link.l2 = "该死的, 好吧, 拿钱。 ";
                link.l2.go = "CapComission4_5";
            }    
        break;
                        
        case "CapComission4_4":
            ChangeCharacterComplexReputation(pchar, "nobility", -2);
            AddQuestRecord("CaptainComission1", "28");
            AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
            AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
            AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
            AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
            DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
            DialogExit();        
        break;
        
        case "CapComission4_5":
            dialog.text = "你可以带走那个弱者... ";
            link.l1 = "再见。 ";
            link.l1.go = "exit";
            addMoneyToCharacter(pchar, -200000);
            AddQuestRecord("CaptainComission1", "29");
            AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
            AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
            AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
            DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
            pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
            AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");    
        break;
                        
        case "CapComission5":
            dialog.text = "吼吼! 干得好! 带走你的弱者吧, 祝你好运。 ";
            link.l1 = "谢谢。 再见。 ";
            link.l1.go = "exit";
            AddQuestRecord("CaptainComission1", "34");
            AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
            AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
            AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
            DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
            AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
        break;

		case "CapComission6":
		    dialog.text = "钱带来了吗, 查尔斯? 我可没开玩笑, 真会把那个人卖到种植园去的。 ";
		    link.l1 = "听着, " + Npchar.name+ ", 有点麻烦... 我的钱不够。 但我愿意干活抵账。 ";
		    link.l1.go = "CapComission2_2";
		    if(makeint(pchar.money) > 150000)
		    {
		        link.l2 = "还好你没把他卖了。 这是15万比索。 我在哪能带走他? ";
		        link.l2.go = "CapComission2_3";
		    }
		break;

		// 劫持乘客
		case "Marginpassenger":
		    dialog.text = "你干嘛关心我在做什么? 你最好赶紧离开... ";
		    link.l1 = "嘘, 冷静点。 我有笔生意想和你谈。 关于你的囚犯。 ";
		    link.l1.go = "Marginpassenger_1";
		break;

		case "Marginpassenger_1":
		    dialog.text = "啊, 好吧。 你想赎谁? ";
		    link.l1 = "等等。 我不是来赎人的, 我是来卖囚犯的。 而且, 你还有机会从他身上拿到赎金。 ";
		    link.l1.go = "Marginpassenger_2";
		break;

		case "Marginpassenger_2":
		    dialog.text = "嗯。 你为什么需要我的中介服务? 你不想自己直接拿赎金吗? ";
		    link.l1 = "这对我来说太冒险了。 我可能会和当局产生麻烦。 ";
		    link.l1.go = "Marginpassenger_3";
		break;

		case "Marginpassenger_3":
		    dialog.text = "哈... 好吧。 让我看看。 你的囚犯是谁? ";
		    link.l1 = "这是" + pchar.GenQuest.Marginpassenger.Text + ", 来自" + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City + "Gen") + "。 ";
		    link.l1.go = "Marginpassenger_4";
		break;

		case "Marginpassenger_4":
		    int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
		    dialog.text = "明白了。 如果你没说谎, 这倒是笔不错的交易。 我可以为这个人付给你" + iTemp + "比索, 或者给你一些有趣的情报。 你选吧。 ";
		    link.l1 = "我还是拿钱吧。 这事儿我受够了... ";
		    link.l1.go = "Marginpassenger_money";
		    link.l2 = "哈! 快说说。 我相信你会给我些有意思的东西。 ";
		    link.l2.go = "Marginpassenger_offer";
		break;

		case "Marginpassenger_money":
		    dialog.text = "那就拿钱。 现在, 这事儿和你没关系了。 把要卖的人送到这儿来。 ";
		    link.l1 = "他应该已经在城门口附近了。 谢谢! 你真帮了我大忙。 ";
		    link.l1.go = "Marginpassenger_money_1";
		break;

		case "Marginpassenger_money_1":
		    iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
		    dialog.text = "不客气, 多给我带些... 再见! ";
		    link.l1 = "祝你好运... ";
		    link.l1.go = "exit";
		    AddMoneyToCharacter(pchar, iTemp);
		    ref sld = characterFromId("MarginPass");
		    RemovePassenger(Pchar, sld);
		    sld.lifeday = 0;
		    AddQuestRecord("Marginpassenger", "12");
		    AddQuestUserData("Marginpassenger", "sSum", iTemp);
		    CloseQuestHeader("Marginpassenger");
		    DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;

		case "Marginpassenger_offer":
		    pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_SANDAL - GOOD_EBONY));
		    pchar.GenQuest.Marginpassenger.GoodsQty = 200 + rand(10)*10;
		    switch (hrand(1))
		    {
		        case 0: // 南岸海湾
		            SelectSouthshore();
		            while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
		            dialog.text = "和聪明人做生意就是好。 现在听着: 几天后, 一支西班牙探险队将从大陆抵达" + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat") + ", 船上满载贵重货物。 他们会等待一艘预定来运货的船。 如果你一周内赶到那里, 就有机会把货物据为己有。 \n如果我是你, 现在就会往船上赶。 把囚犯送到这儿来。 ";
		            link.l1 = "谢谢! 这些货物足以补偿我的麻烦了。 我的乘客应该已经在城门口附近了。 他会被送到你这儿来的。 ";
		            link.l1.go = "Marginpassenger_offer_1";
		        break;
        
		        case 1: // 普通船只
		            SelectSouthcity();
		            pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
		            dialog.text = "和聪明人做生意就是好。 现在听着: 大约一周后, 一艘装满贵重货物的西班牙双桅帆船‘" + pchar.GenQuest.Marginpassenger.ShipName1 + "’将从" + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen") + "驶往" + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Gen") + "。 如果你抓紧时间, 很容易就能截住它。 \n你还在等什么? 如果我是你, 现在就会往船上赶。 把囚犯送到这儿来。 ";
		            link.l1 = "谢谢! 这些货物足以补偿我的麻烦了。 我的乘客应该在城门口附近。 他会被送到你这儿来的。 ";
		            link.l1.go = "Marginpassenger_offer_2";
		        break;
		    }
		    sld = characterFromId("MarginPass");
		    RemovePassenger(Pchar, sld);
		    sld.lifeday = 0;
		    pchar.GenQuest.Marginpassenger = "final";
		break;

		case "Marginpassenger_offer_1":
		    DialogExit();
		    AddQuestRecord("Marginpassenger", "13");
		    AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat"));
		    SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
		    pchar.quest.Marginpassenger.win_condition.l1 = "location";
		    pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
		    pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
 		break;

 		case "Marginpassenger_offer_2":
            DialogExit();
            AddQuestRecord("Marginpassenger", "16");
            AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen"));
            AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Gen"));
            AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
            SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5 + rand(2), false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了执行此卸载
}

void SelectSouthshore()
{
    switch (rand(6))
    {
        case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
        case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
        case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
        case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
        case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
        case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
        case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
    }
}

void SelectSouthcity()
{
    switch (hrand(2))
    {
        case 0: 
            pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
            pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
        break;
        
        case 1:
            pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
            pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
        break;
        
        case 2:
            pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
            pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
        break;
    }
}